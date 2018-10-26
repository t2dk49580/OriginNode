json = require 'json'

gUser = nil
gModify = '20181022 111800'

financer = 'P0'
banker = 'P1'
bonusRate = 0.3
hashPriceIncreaceRate = 1
initHashRatePrice = 1000

gSpeed = 1
Round = 1
Tick = 1
totalHashRate = 0
totalPlayer = 0
hashPrice = 0
lastIncoming = ''
MinePool = 0
BonusPool = 0
isPlaying = false
gBalance = {}
gHashRate = {}
ladder = {}

gTickID = 0
gList = {}
gFreezen = {}
gDepositeU = {}
gDepositeF = {}
gWithdrawalU = {}
gWithdrawalF = {}

gWithdrawalMin = 100
gFee = 10

function setWithdrawalmin(pMin)
    if gUser ~= banker and gUser ~= financer then
        return 'fail'
    end
    gWithdrawalMin = tonumber(pMin)
    return 'ok'
end

function setWithdrawalfee(pFee)
    if gUser ~= banker and gUser ~= financer then
        return 'fail'
    end
    gFee = tonumber(pFee)
    return 'ok'
end

function getMcInfo()
    local curResult = {}
    curResult['fee'] = gFee
    curResult['wmin'] = gWithdrawalMin
    return json.encode(curResult)
end

function withDrawal(pEtheraddress,pAmount)
    local curAmount = tonumber(pAmount)
    curAmount = _getFloat(curAmount,6)
    if curAmount < gWithdrawalMin then
        return 'fail'
    end
    if gBalance[gUser] < curAmount then
        return 'fail'
    end
    if gFreezen[gUser] == nil then
        gFreezen[gUser] = 0
    end
    if gWithdrawalU[gUser] ~= nil then
        local key,v,size
        size = 0
        for key,v in pairs(gWithdrawalU[gUser]) do
            size = size + 1
        end
        if size > 10 then
            return 'fail'
        end
    end
    gBalance[gUser] = gBalance[gUser]-curAmount
    gFreezen[gUser] = gFreezen[gUser]+curAmount
    local curData = {}
    curData['id'] = gTickID
    curData['etheraddress'] = pEtheraddress
    curData['amount'] = curAmount
    curData['user'] = gUser
    curData['stat'] = 'unfinish'
    curData['type'] = 'withdrawal'
    curData['fee']  = gFee
    if gWithdrawalU[gUser] == nil then
        gWithdrawalU[gUser] = {}
    end
    gWithdrawalU[gUser][tostring(gTickID)] = curData
    gTickID = gTickID+1
    curResult['user'] = gUser
    curResult['tick'] = gTickID
    curResult['result'] = true
    return json.encode(curResult) 
end

function removedWithdrawal(pUser,pTickid)
    if gUser ~= banker and gUser ~= financer then
        return 'fail:only owner can update'
    end
    local curTick = tonumber(pTickid)
    local curData = gWithdrawalU[pUser][pTickid]
    gFreezen[gUser] = gFreezen[gUser]-curData['amount']
    gBalance[gUser] = gBalance[gUser]+curData['amount']
    gWithdrawalU[pUser][pTickid] = nil
    local curResult = {}
    curResult['user'] = pUser
    curResult['tick'] = pTickid
    curResult['result'] = true
    return json.encode(curResult) 
end

function updWithdrawal(pUser,pTickid,pHash)
    if gUser ~= banker and gUser ~= financer then
        return 'fail:only owner can update'
    end
    if gWithdrawalU[pUser][pTickid] == nil then
        return 'fail:'..pUser..'-withdrawal-unfinish-'..pTickid..'-nil'
    end
    if gWithdrawalU[pUser][pTickid]['type'] == 'finish' then
        return 'fail:'..pUser..'-withdrawal-is finish-'..pTickid
    end
    local curData = {}
    curData['id'] = gWithdrawalU[pUser][pTickid]['id']
    curData['etheraddress'] = gWithdrawalU[pUser][pTickid]['etheraddress']
    curData['amount'] = gWithdrawalU[pUser][pTickid]['amount']
    curData['user'] = gWithdrawalU[pUser][pTickid]['user']
    curData['stat'] = gWithdrawalU[pUser][pTickid]['stat']
    if curData['user'] ~= pUser then
        return 'fail:'..curData['user']..'~='..pUser
    end
    if curData['id'] ~= tonumber(pTickid) then
        return 'fail:'..curData['id']..'~='..pTickid
    end
    curData['type'] = 'finish'
    curData['hash'] = pHash
    curData['realamount'] = curData['amount']-curData['fee']
    gFreezen[gUser] = gFreezen[gUser]-curData['amount']
    gWithdrawalU[pUser][pTickid] = nil
    if gWithdrawalF[pUser] == nil then
        gWithdrawalF[pUser] = {}
    end
    table.insert(gWithdrawalF[pUser],curData)
    if #gWithdrawalF[pUser] > 10 then
        table.remove( gWithdrawalF[pUser], 1 )
    end
    gBalance[banker] = gBalance[banker]+curData['fee']
    local curResult = {}
    curResult['user'] = pUser
    curResult['tick'] = pTickid
    curResult['hash'] = pHash
    curResult['result'] = true
    return json.encode(curResult) 
end

function getWithdrawal()
    if gUser == banker or gUser == financer then
        return json.encode(gWithdrawalU)
    end
    return 'only owner can get this info'
end

function _getFloat(nNum, n)
    if type(nNum) ~= "number" then
        return nNum;
    end
    n = n or 0;
    n = math.floor(n)
    if n < 0 then
        n = 0;
    end
    local nDecimal = 10 ^ n
    local nTemp = math.floor(nNum * nDecimal);
    local nRet = nTemp / nDecimal;
    return nRet;
end

function init()
    _Reset()
    financer = gUser
    banker = gUser
    local curResult = {}
    curResult['user'] = gUser
    curResult['init'] = true
    curResult['result'] = true
    return json.encode(curResult)
end

function setFinancer(pUser)
    if gUser ~= banker then
        return 'fail'
    end
    financer = pUser
    local curResult = {}
    curResult['financer'] = financer
    curResult['result'] = true
    return json.encode(curResult)
end

function getFinancer()
    return financer
end

function _setUser(pUser)
    gUser = pUser 
end

function _getTotal()
    return 100000
end

function _getOwner()
    return Banker
end

function getBalance(pUser)
    if gBalance[pUser] == nil then
		return 0
	end
	return gBalance[pUser]
end

function _Reset()
    print('Hello Crazy Miner!')
    MinePool = 0
    BonusPool = 0
    totalHashRate = 0
    totalPlayer = 0
    hashPrice = initHashRatePrice
    gHashRate = {}
    isPlaying = false
end

function doTimeout()
    if gUser ~= financer then
        return 'fail'
    end
    if isPlaying ~= true then
        return 'fail'
    end
    _timeout()
    return 'ok'
end

function _timeout()
    Tick = Tick + 1;
    _tick()
end

function _tick()
    if isPlaying ~= true then
        return 'fail'
    end
    if totalHashRate<=MinePool  then
        MinePool = MinePool - totalHashRate
        local key,v
        for key,v in pairs(gHashRate) do
            gBalance[key] = gBalance[key] + v
        end
    else

        local key,v
        for key,v in pairs(gHashRate) do
            MinePool = MinePool - gHashRate[key];
            gBalance[key] = gBalance[key] + v
            if MinePool<=0 then
                print(gBalance[key],MinePool,gBalance[key] + MinePool)
                gBalance[key] = gBalance[key] + MinePool 
                break
            end
        end

        gBalance[lastIncoming] = gBalance[lastIncoming] + BonusPool
                
        local winner = {}
        winner['Round'] = Round
        winner['Addr'] = lastIncoming
        winner['Bonus'] = BonusPool
        table.insert( ladder, winner)

        if #ladder > 10 then
            table.remove( ladder, 1)
        end
        
        Round = Round + 1
        _Reset()
    end
end


function _tickTest(cnt)
	local i
    for i = 1,cnt do
        _timeout()
    end
end

function BuyHash()
    if(gBalance[gUser] == nil) then
        print('no balance addr!')
        return 'fail'
    end

    if(gBalance[gUser]>hashPrice) then
        if gHashRate[gUser] == nil then
            gHashRate[gUser] = 0
        end
        gBalance[gUser] = gBalance[gUser] - hashPrice
        gHashRate[gUser] = gHashRate[gUser] + 1
        totalHashRate = totalHashRate + 1

        local minePart = math.floor(hashPrice * (1 - bonusRate))
        local bonusPart = hashPrice - minePart
        MinePool = MinePool + minePart
        BonusPool = BonusPool + bonusPart
        hashPrice = hashPrice + hashPriceIncreaceRate
        lastIncoming = gUser
        isPlaying = true;
    else
        return 'fail'
    end

    local size = 0
	local key,v
    for key,v in pairs(gHashRate) do
        size = size + 1
    end
    totalPlayer = size
end

function Recharge(pUser,amount,pHash)
    print(gUser,financer,pUser,amount,pHash)
    if gUser ~= financer and gUser ~= banker then
        return 'fail'
    end
    
    if gBalance[pUser] == nil then
        gBalance[pUser] = tonumber(amount)
    else
        gBalance[pUser] = gBalance[pUser] + tonumber(amount)
    end

    if gHashRate[pUser] == nil then
        gHashRate[pUser] = 0
    end

    if gDepositeF[pUser] == nil then
        gDepositeF[pUser] = {}
    end

    local curData = {}
    curData['woker'] = gUser
    curData['amount'] = tonumber(amount)
    curData['hash'] = pHash
    table.insert( gDepositeF[pUser], curData )
    if #gDepositeF[pUser] > 10 then
        table.remove( gDepositeF[pUser], 1 )
    end
    return 'ok'
end

function getInfo(addr) 
    local result = {}
    result['Tick'] = Tick
    result['Round'] = Round
    result['IsPlaying'] = isPlaying
    result['Banker'] = banker
    result['LastIncoming'] = lastIncoming
    result['TotalPlayer'] = totalPlayer
    result['TotalCalcPower'] = totalHashRate
    result['CalcPowerPrice'] = hashPrice
    result['MinePool'] = MinePool
    result['BonusPool'] = BonusPool
    result['LocalAddr'] = gUser
    result['Balance'] = gBalance[addr]
    result['CalcPower'] = gHashRate[addr]
    return json.encode(result)
end

function getHistory(pUser)
    local result = {}
    result['user'] = pUser
    if gWithdrawalF[addpUserr] ~= nil then
        result['wfinish'] = gWithdrawalF[pUser]
    end
    if gWithdrawalU[pUser] ~= nil then
        result['wunfinish'] = gWithdrawalU[pUser]
    end
    if gDepositeF[pUser] ~= nil then
        result['dfinish'] = gDepositeF[pUser]
    end
    return json.encode(result)
end

function getLadderInfo()
    return json.encode(ladder)
end

function _Print()
    print('All Balance')
	local key,v
    for key,v in pairs(gBalance) do
        print(key)
        print(v)
        print(gHashRate[key])
    end
    for key,v in pairs(gHashRate) do
        print(key)
        print(v)
    end
    print(getInfo('P1'))
    print(getLadderInfo())
end

function test()
    _setUser('P1')
    init()
    Recharge('P1','10000','0x111')
    Recharge('P2','10000','0x222') 
    _setUser('P1')
    BuyHash()
    BuyHash()
    BuyHash()
    BuyHash()
    _Print()
    _timeout();
    _timeout();
    _timeout();
    _setUser('P2')
    BuyHash()
    BuyHash()
    BuyHash()
    BuyHash()
    BuyHash()
    BuyHash()
    BuyHash()
    BuyHash()
    
    _tickTest(1000);
    BuyHash()
    _tickTest(1000);
    BuyHash()
    _tickTest(1000);
    BuyHash()
    _tickTest(1000);
    BuyHash()
    _tickTest(1000);
    BuyHash()
    _tickTest(1000);
    BuyHash()
    _tickTest(1000);
    BuyHash()
    _tickTest(1000);
    BuyHash()
    _tickTest(1000);
    BuyHash()
    _tickTest(1000);
    Recharge('P1','10000','0x111')
    Recharge('P2','10000','0x111') 
    Recharge('P1','10000','0x111')
    Recharge('P2','10000','0x111') 
    BuyHash()
    _Print()
end

function _clone( object )
    local lookup_table = {}
    local function copyObj( object )
        if type( object ) ~= "table" then
            return object
        elseif lookup_table[object] then
            return lookup_table[object]
        end
        
        local new_table = {}
        lookup_table[object] = new_table
        for key, value in pairs( object ) do
            new_table[copyObj( key )] = copyObj( value )
        end
        return setmetatable( new_table, getmetatable( object ) )
    end
    return copyObj( object )
end

function _reset()
    -- body
end

local k,v
aaa = 1
local i
for i=1,5000,1 do
local _T=_clone(_G)
end
print('end')