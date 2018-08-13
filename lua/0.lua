_G['os'] = nil
_G['io'] = nil
json = require 'json'
gLastModify = '2018 0706 10:00'
gUser    = nil
gMaker   = nil
gName    = 'boss contract'
gSymbol  = 'boss'
gBalance = {}
gFreezen = {}
gTotal   = 1000000000
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
        return "ok"
    end
    if gDestroy[pSymbol] > 0 then
        return 'fail'
    end
    if gFreezen[gBoss[pSymbol]['owner']] > 1 then
        return 'fail'
    end
end

function _getNextBoss(pBalance)
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
        if gBalance[curList[i]] ~= nil and gBalance[curList[i]] > tonumber(pBalance) then
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

function _setNextBoss(pSymbol,pBalance)
    if gBoss[pSymbol] == nil then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    local curNext = _getNextBoss(pBalance)
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

function _setRate(pSymbol)
    gBoss[pSymbol]['rate']  = string.format('%.0f', gBoss[pSymbol]['total']/gFreezen[gBoss[pSymbol]['owner']])
end

function _setDeployBoss(pSymbol,pBalance,pTotal,pFreezen)
    if _transferToFreezenSelf(gUser,pFreezen) == 'fail' then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    if gFreezen[gUser] == nil then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    if tonumber(string.format('%.0f', gFreezen[gUser]/tonumber(pTotal))) > 100000 then
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
    local curNext = _getNextBoss(pBalance)
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
    if tonumber(pTotal) <= 0 then
        gBoss[pSymbol]['rate']  = 0
    else
        _setRate(pSymbol)
    end
    
    gSeed = gSeed+1
    return curNext
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

function getOrder()
    if gOrder[gUser] == nil then
        return _getResult(gUser,'getOrder',true,'null')
    end
    return _getResult(gUser,'getOrder',true,gOrder[gUser])
end

function getBossMaker(pSymbol)
    if gBoss[pSymbol]['maker'] == nil then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
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

function transferToBoss(pSymbol,pAmount)
    local curAmount = tonumber(pAmount)
    if gBoss[pSymbol] == nil then
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
    if _transferToFreezenSelf(gBoss[pSymbol]['owner'],pAmount) == 'fail' then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    _setRate(pSymbol)
    local curResult = {}
    _addResult(gUser,'transferToBoss',true,pAmount,curResult)
    _addResult(gUser,'getRate',true,gBoss[pSymbol]['rate'],curResult)
    return json.encode(curResult)
end

function _transferToFreezenSelf(pTo,pAmount)
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
    if gFreezen[pTo] == nil then
	    gFreezen[pTo] = 0
    end
    local curResult = {}
    gFeePool = gFeePool + gFee
    gBalance[gUser] = gBalance[gUser] - curAmount
    gBalance[gUser] = gBalance[gUser] - gFee
    gFreezen[pTo] = gFreezen[pTo] + curAmount
    _addResult(gUser,'getBalanceOf',true,gBalance[gUser],curResult)
    _addResult(pTo,'getFreezen',true,gFreezen[pTo],curResult)
    return json.encode(curResult)
end

function getFreezen()
    return _getResult(gUser,'getFreezen',true,gFreezen[gUser])
end

function getRate(pSymbol)
    if gBoss[pSymbol] == nil then
        return _getResult(gUser,'getRate',true,0)
    else
        return _getResult(gUser,'getRate',true,gBoss[pSymbol]['rate'])
    end
end

function _setTokenOwner(pSymbol,pUser)
    if gBoss[pSymbol] == nil then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    gBoss[pSymbol]['owner'] = pUser
    return 'ok'
end

function _transferToFreezen(pSymbol,pUser,pAmount)
    if gBoss[pSymbol] == nil then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    if gBalance[gUser] < tonumber(pAmount)+gFee then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    gBalance[gUser] = gBalance[gUser]-(tonumber(pAmount)+gFee)
    gFreezen[pUser] = gFreezen[pUser]+(tonumber(pAmount))
    return 'ok'
end

function _transferToBalance(pSymbol,pFrom,pTo,pAmount)
    if gBoss[pSymbol] == nil then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    if gFreezen[pFrom] < tonumber(pAmount) then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    if gBalance[gUser] < gFee then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    gBalance[gUser] = gBalance[gUser]-gFee
    gFreezen[pFrom] = gFreezen[pFrom]-tonumber(pAmount)
    gBalance[pTo] = gBalance[pTo]+tonumber(pAmount)
    return 'ok'
end

function tokenBuy(pSymbol,pAmount)
    if pSymbol == '0' then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    if gBoss[pSymbol]['unuse'] < tonumber(pAmount) then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    local curOwner  = gBoss[pSymbol]['owner']
    if curOwner == gUser then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    local needUse0  = string.format( "%.2f",(1/gBoss[pSymbol]['rate'])*pAmount)
    print(needUse0)
    if tonumber(needUse0) < 1 then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    local curResult = _transferToFreezen(pSymbol,curOwner,needUse0)
    if curResult == 'fail' then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end

    gFeePool = gFeePool + gFee

    gOrder[gOrderID] = {}
    gOrder[gOrderID]['user']   = gUser
    gOrder[gOrderID]['owner']  = curOwner
    gOrder[gOrderID]['direct'] = 'buy'
    gOrder[gOrderID]['symbol'] = pSymbol
    gOrder[gOrderID]['amount'] = pAmount
    gOrder[gOrderID]['needuse']= needUse0

    gBoss[pSymbol]['unuse'] = gBoss[pSymbol]['unuse']-pAmount
    
    if gOrder[gUser] == nil then
        gOrder[gUser] = {}
    end
    table.insert(gOrder[gUser],gOrderID)
    local curBroad = {}
    _addResult(gUser,'tokenBuy',true,gOrderID,curBroad)
    _addResult(curOwner,'tokenBuy',true,gOrderID,curBroad)
    gOrderID = string.format( "%.0f",gOrderID+1 )
    return json.encode(curBroad)
end

function tokenSell(pSymbol,pAmount)
    if pSymbol == '0' then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    local curOwner  = gBoss[pSymbol]['owner']
    if curOwner == gUser then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end

    if gBalance[gUser] < gFee then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    local needUse0  = string.format( "%.2f",(1/gBoss[pSymbol]['rate'])*pAmount)
    print(needUse0)
    if tonumber(needUse0) < 1 then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end

    if gFreezen[curOwner] < tonumber(needUse0) then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end

    gBalance[gUser] = gBalance[gUser]-gFee
    gFeePool = gFeePool+gFee

    gOrder[gOrderID] = {}
    gOrder[gOrderID]['user']   = gUser
    gOrder[gOrderID]['owner']  = curOwner
    gOrder[gOrderID]['direct'] = 'sell'
    gOrder[gOrderID]['symbol'] = pSymbol
    gOrder[gOrderID]['amount'] = pAmount
    gOrder[gOrderID]['needuse']= needUse0

    print(gOrderID)

    if gOrder[gUser] == nil then
        gOrder[gUser] = {}
    end
    table.insert(gOrder[gUser],gOrderID)
    local curBroad = {}
    _addResult(gUser,'tokenSell',true,gOrderID,curBroad)
    _addResult(curOwner,'tokenSell',true,gOrderID,curBroad)
    gOrderID = string.format( "%.0f",gOrderID+1 )
    return json.encode(curBroad)
end

function _removeOrder(pUser,pOrderID)
    gOrder[gOrderID] = nil
    for i=1,#gOrder[pUser],1 do
        if gOrder[pUser][i] == pOrderID then
            print('_removeOrder',i,pOrderID)
            table.remove( gOrder[pUser], i )
            break
        end
    end
end

function tokenConfirm(pOrderID)
    local curOrder = gOrder[pOrderID]
    local curOwner = curOrder['owner']
    local curSymbol= curOrder['symbol']
    local curBroad = {}
    if curOrder['direct'] == 'buy' then
        if gUser ~= curOrder['user'] then
            print(debug.getinfo(1).currentline,debug.getinfo(1).name)
            return 'fail'
        end
        local curResult1 = _transferToBalance(curOrder['symbol'],curOrder['owner'],curOrder['owner'],curOrder['needuse'])
        if curResult1 == 'fail' then
            print(debug.getinfo(1).currentline,debug.getinfo(1).name)
            return 'fail'
        end
        _removeOrder(gUser,pOrderID)
        _addResult(gUser,'tokenConfirm',true,pOrderID,curBroad)
        _addResult(curOwner,'getBalanceOf',true,gBalance[curOwner],curBroad)
        return json.encode(curBroad)
    else if curOrder['direct'] == 'sell' then
        if gUser ~= curOrder['owner'] then
            print(debug.getinfo(1).currentline,debug.getinfo(1).name)
            return 'fail'
        end
        if gBoss[curSymbol]['total'] < gBoss[curSymbol]['unuse']+curOrder['amount'] then
            print(debug.getinfo(1).currentline,debug.getinfo(1).name)
            return 'fail'
        end
        local curResult2 = _transferToBalance(curOrder['symbol'],curOrder['owner'],curOrder['user'],curOrder['needuse'])
        if curResult2 == 'fail' then
            print(debug.getinfo(1).currentline,debug.getinfo(1).name)
            return 'fail'
        end

        gBoss[curSymbol]['unuse'] = gBoss[curSymbol]['unuse']+curOrder['amount']
        _setRate(curSymbol)

        _removeOrder(curOrder['user'],pOrderID)
        _addResult(curOwner,'tokenConfirm',true,pOrderID,curBroad)
        _addResult(curOrder['user'],'getBalanceOf',true,gBalance[curOrder['user']],curBroad)
        return json.encode(curBroad)
    else
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
end
end


_setUser('1234')
init()
_setPeers('1234,5678,aaaa,bbbb,cccc,dddd,eeee')
transfer('5678','50000')
transfer('aaaa','110000')
transfer('bbbb','60000')
transfer('cccc','110000')
transfer('dddd','6000')
transfer('eeee','16000')

print(getBalanceOf('1234'))
print(getBalanceOf('5678'))
print(getBalanceOf('aaaa'))
print(getBalanceOf('bbbb'))

_setUser('5678')
print(_setDeployBoss('b0','10000','100000000','5000'))
_setUser('aaaa')
print(_setDeployBoss('b1','10000','100000000','6000'))
_setUser('bbbb')
print(_setDeployBoss('b2','10000','100000000','7000'))
_setUser('cccc')
print(_setDeployBoss('b3','10000','100000000','8000'))
_setUser('dddd')
print(_setDeployBoss('b4','10000','100000000','9000'))

print(getRate('b0'))
print(getRate('b1'))
print(getRate('b2'))
print(getRate('b3'))
print(getRate('b4'))

_setUser('dddd')
print(tokenBuy('b1','100000'))
print(getOrder())
_setUser('dddd')
print(tokenConfirm('1'))
print(getBalanceOf('dddd'))

_setUser('dddd')
print(tokenSell('b1','100000'))
_setUser('aaaa')
print(tokenConfirm('2'))
print(getBalanceOf('aaaa'))

print(gBoss['b1']['rate'])

print(transferToBoss('b1','20000'))
print(gBoss['b1']['rate'])
print(gBoss['b1']['maker'])
print(gBoss['b1']['owner'])

print(json.encode(gIdentity))

_setUser('aaaa')
print(setBossMaker('b1','cccc'))
print(json.encode(gIdentity))