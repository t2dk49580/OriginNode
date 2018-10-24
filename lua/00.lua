json = require 'json'
gLastModify = '2018 0706 10:00'
gUser    = nil
gMaker   = nil
gName    = 'Origin Node Network'
gSymbol  = '0'
gBalance = {}
gFreezen = {}
gTotal   = 1000000000
gLevel   = 10000000
gOwner   = nil
gFee     = 0.1
gFeePool = 0
gIcon    = ''
gBoss    = {}
gPeers   = ''
gSeed    = 0
gOrder   = {}
gOrderID = '1'
gIdentity= {}
gDestroy = {}

function setLevel(pLevel)
    if gUser ~= gOwner then
        return 'fail'
    end
    gLevel = tonumber(pLevel)
end

function getLevel()
    return gLevel
end

function _setUser(pUser)
    gUser = pUser
end

function _getUser()
    return gUser
end

function _setMaker(pUser)
    gMaker= pUser
end

function _setPeers(pList)
    gPeers = pList
end

function _doRand(pMax)
    math.randomseed(gSeed)
    return math.random(1,pMax)
end

function _getBalanceOf(pUser)
    if gBalance[pUser] == nil then
	    return 0
    end
        return gBalance[pUser]
end

function _getTotal()
    return gTotal
end

function _destroy(pSymbol)
    if gUser == gBoss[pSymbol]['owner'] then
        gIdentity[gBoss[pSymbol]['maker']] = nil
        if gFreezen[gBoss[pSymbol]['owner']] <= 1 then
            gBalance[gOwner] = gBalance[gOwner] + gFreezen[gBoss[pSymbol]['owner']]
            gFreezen[gBoss[pSymbol]['owner']] = 0
        else
            local curPay = gFreezen[gBoss[pSymbol]['owner']]/2
            gBalance[gOwner] = gBalance[gOwner] + curPay
            gBalance[gBoss[pSymbol]['owner']] = gBalance[gBoss[pSymbol]['owner']] + (gFreezen[gBoss[pSymbol]['owner']]-curPay)
            gFreezen[gBoss[pSymbol]['owner']] = 0
        end
        return "ok"
    end
    if gFreezen[gBoss[pSymbol]['owner']] > 1 then
        return 'fail'
    end
    gBalance[gOwner] = gBalance[gOwner] + gFreezen[gBoss[pSymbol]['owner']]
    gFreezen[gBoss[pSymbol]['owner']] = 0
    return "ok"
end

function _getNextBoss()
    local curList = _split(gPeers, ',')
    if #curList == 0 then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    print(json.encode(curList))
    local i = 1
    local tgtList = {}
    local tgtList1 = {}
    while i <= #curList do
        if gBalance[curList[i]] ~= nil and gBalance[curList[i]] > gLevel then
            table.insert( tgtList, curList[i] )
            if gIdentity[curList[i]] == nil or gIdentity[curList[i]] == 0 then
                table.insert( tgtList1, curList[i] )
            end
        end
        i = i+1
    end
    local curCount = #tgtList
    if curCount == 0 then
        return curList[1]
    end
    local curCount1 = #tgtList1
    --print(json.encode(tgtList))
    if curCount1 > 0 then
        local curIndex1 = _doRand(curCount1)
        return tgtList1[curIndex1]
    else
        local curIndex = _doRand(curCount)
        return tgtList[curIndex]
    end
end

function _setNextBoss(pSymbol)
    if gBoss[pSymbol] == nil then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    local curNext = _getNextBoss(gLevel)
    if curNext == 'fail' then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    local curMaker= gBoss[pSymbol]['maker']
    gIdentity[curMaker] = gIdentity[curMaker]-1
    if gIdentity[curNext] == nil then
        gIdentity[curNext] = 0
    end
    gIdentity[curNext]  = gIdentity[curNext]+1
    gBoss[pSymbol]['maker'] = curNext
    return curNext
end

function _setDeployBoss(pSymbol,pTotal,pBalance)
    if transfer(gOwner,pBalance) == 'fail' then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    if gBoss[pSymbol] ~= nil then
        print(json.encode(gBoss[pSymbol]))
        --return _getResult(gUser,'_setDeployBoss',false,'boss exist')
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    gBoss[pSymbol] = {}
    local curNext = _getNextBoss(gLevel)
    if curNext == 'fail' then
        --return _getResult(gUser,'_setDeployBoss',false,'curNext fail')
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    if gIdentity[curNext] == nil then
        gIdentity[curNext] = 0
    end
    gIdentity[curNext] = gIdentity[curNext]+1
    gBoss[pSymbol]['maker'] = curNext
    gBoss[pSymbol]['total'] = tonumber(pTotal)
    gBoss[pSymbol]['unuse'] = tonumber(pTotal)
    _setTokenOwner(pSymbol,gUser)
    gBoss[pSymbol]['rate']  = 0
    
    gSeed = gSeed+1
    return curNext
end

function _setTokenOwner(pSymbol,pUser)
    if gBoss[pSymbol] == nil then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    gBoss[pSymbol]['owner'] = pUser
    return 'ok'
end

function _split(str, delimiter)
	if str==nil or str=='' or delimiter==nil then
		return nil
	end
	
    local result = {}
    for match in (str..delimiter):gmatch("(.-)"..delimiter) do
        table.insert(result, match)
    end
    return result
end

function _addResult(pUser,pMethod,pResult,pMsg,pAll)
    local buffer = {}
    local result = pAll
    buffer['method'] = pMethod
    buffer['result'] = pResult
    buffer['msg']    = pMsg
    buffer['owner']  = pUser
    buffer['symbol'] = gSymbol
    table.insert(result,buffer)
    return result
end

function _getResult(pUser,pMethod,pResult,pMsg)
    local buffer = {}
    local result = _addResult(pUser,pMethod,pResult,pMsg,buffer)
    return json.encode(result)
end

function _IsInTable(value, tbl)
    for k,v in ipairs(tbl) do
        if v == value then
            return true;
        end
    end
    return false;
end

function _getOwner()
    return gOwner
end

function init()
    if gOwner ~= nil then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    print(gUser)
    gOwner = gUser
    gBalance[gUser] = gTotal

    gBoss[gSymbol] = {}
    gBoss[gSymbol]['maker'] = gUser
    gBoss[gSymbol]['total'] = gTotal

    gSeed = gSeed+1

    local curResult = {}
    _addResult(gUser,'init',true,gBoss[gSymbol],curResult)
    _addResult(gUser,'getBalanceOf',true,gBalance[gUser],curResult)
    return json.encode(curResult)
end

function setFee(pFee)
    if gUser ~= gOwner then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    local curFee = tonumber(pFee)
    if curFee < 0 then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    if curFee > 1 then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    gFee = tonumber(pFee)
    return _getResult(gUser,'setFee',true,gFee)
end

function takeFeePool()
    if gUser ~= gOwner then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    if gFeePool < 1 then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    gBalance[gUser] = gBalance[gUser]+gFeePool
    gFeePool = 0
    return _getResult(gUser,'getBalanceOf',true,gBalance[gUser])
end

function setBossMaker(pSymbol,pUser)
    if gBoss[pSymbol]['owner'] ~= gUser then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    if gIdentity[pUser] ~= nil and gIdentity[pUser] > 0 then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    if gBoss[pSymbol]['maker'] == nil then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    if gBalance[gUser] < 1+gFee then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    local curMaker = gBoss[pSymbol]['maker']
    gBoss[pSymbol]['maker'] = pUser
    gIdentity[curMaker] = gIdentity[curMaker]-1
    if gIdentity[pUser] == nil then
        gIdentity[pUser] = 0
    end
    gIdentity[pUser]    = gIdentity[pUser]+1
    local tResult = transfer(curMaker,1)
    local curResult = {}
    _addResult(curMaker,'setBossMaker',true,pSymbol..'?'..pUser,curResult)
    _addResult(pUser,'setBossMaker',true,pSymbol..'?'..pUser,curResult)
    _addResult(gUser,'setBossMaker',true,pSymbol..'?'..pUser,curResult)
    _addResult('*','setBossMaker',true,tResult,curResult)
    return json.encode(curResult)
end

function getBossMaker(pSymbol)
    if gBoss[pSymbol] == nil then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return _getResult(gUser,'getBossMaker',true,'null')
    end
    if gBoss[pSymbol]['maker'] == nil then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return _getResult(gUser,'getBossMaker',true,'null')
    end
    return _getResult(gUser,'getBossMaker',true,gBoss[pSymbol]['maker'])
end

function getFee()
    local curResult = {}
    _addResult(gUser,'getFee',true,gFee,curResult)
    _addResult(gUser,'getFeePool',true,gFeePool,curResult)
    return json.encode(curResult)
end

function getSymbol()
    return _getResult(gUser,'getSymbol',true,gSymbol)
end

function getTotalSupply()
    return _getResult(gUser,'getTotalSupply',true,gTotal)
end

function getName()
    return _getResult(gUser,'getName',true,gName)
end

function getBalanceOf(pUser)
    if gBalance[pUser] == nil then
	    return _getResult(gUser,'getBalanceOf',true,0)
    end
        return _getResult(gUser,'getBalanceOf',true,gBalance[pUser])
end

function getIcon()
    return _getResult(gUser,'getIcon',true,gIcon)
end

function setIcon(pIcon)
    if gOwner ~= gUser then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    if string.len( pIcon ) > 2048 then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    gIcon = pIcon
end

function transfer(pTo,pAmount)
    local curAmount = tonumber(pAmount)
    if curAmount > gTotal then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    if curAmount <= gFee then
        --return _getResult(gUser,'transfer',false,'amount <= 0')
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    if gBalance[gUser] < curAmount+gFee then
        --return _getResult(gUser,'transfer',false,'sender amount < curAmount')
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    if gIdentity[gUser] ~= nil then
        local curTotal = gBalance[gUser] - curAmount
        if curTotal < gIdentity[gUser] * 10000 then
            print(debug.getinfo(1).currentline,debug.getinfo(1).name)
            return 'fail'
        end
    end
    if gBalance[pTo] == nil then
	    gBalance[pTo] = 0
    end
    local curResult = {}
    gFeePool = gFeePool + gFee
    gBalance[gUser] = gBalance[gUser] - curAmount
    gBalance[gUser] = gBalance[gUser] - gFee
    gBalance[pTo] = gBalance[pTo] + curAmount
    _addResult(gUser,'getBalanceOf',true,gBalance[gUser],curResult)
    _addResult(pTo,'getBalanceOf',true,gBalance[pTo],curResult)
    gSeed = gSeed+1
    return json.encode(curResult)
end

_setUser('1234')
init()
local index = 0
for index=0,10,1 do
    print(index,transfer('5678','1'))
end

_setPeers('1234,5678,aaaa,bbbb,cccc,dddd,eeee')
transfer('5678','50000')
transfer('aaaa','110000000')
transfer('bbbb','60000')
transfer('cccc','110000')
transfer('dddd','6000')
transfer('eeee','16000')

print(getBalanceOf('1234'))
print(getBalanceOf('5678'))
print(getBalanceOf('aaaa'))
print(getBalanceOf('bbbb'))

_setUser('5678')
print(_setDeployBoss('b0','10000','5000'))
_setUser('aaaa')
print(_setDeployBoss('b1','10000','6000'))
_setUser('bbbb')
print(_setDeployBoss('b2','10000','7000'))
_setUser('cccc')
print(_setDeployBoss('b3','10000','8000'))
_setUser('dddd')
print(_setDeployBoss('b4','10000','9000'))

print(getBossMaker('b0'))
print(getBossMaker('b1'))
print(getBossMaker('b2'))
print(getBossMaker('b3'))
print(getBossMaker('b4'))

print(getBalanceOf('aaaa'))
_setUser('aaaa')
print(setBossMaker('b1','cccc'))
print(json.encode(gIdentity))
