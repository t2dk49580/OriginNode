json = require 'json'

gUser = nil

banker = 'P1'
bonusRate = 0.3
hashPriceIncreaceRate = 1.01
initHashRatePrice = 1000

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
gWithdrawal = {}
gEtheraddress = {}

function withDrawal(pEtheraddress,pAmount)
    local curAmount = tonumber(pAmount)
    if gBalance[gUser] < curAmount then
        return 'fail'
    end
    if gList[gUser] == nil then
        return 'fail'
    end
    gBalance[gUser] = gBalance[gUser]-curAmount
    gList[gUser]['freezen'] = gList[gUser]['freezen']+curAmount
    local curData = {}
    curData['id'] = gTickID
    curData['etheraddress'] = pEtheraddress
    curData['amount'] = curAmount
    curData['user'] = gUser
    gList[gUser]['deposite']['unfinish'][tostring(gTickID)] = curData
    gWithdrawal[tostring(gTickID)] = curData
    gTickID = gTickID+1
    return 'ok'
end

function getWithdrawal()
    if gUser == banker then
        return json.encode(gWithdrawal)
    end
    return 'only owner can get this info'
end

function updWithdrawal(pUser,pTickid,pHash)
    if gUser ~= banker then
        return 'fail:only owner can update'
    end
    if gList[pUser]['withdrawal']['unfinish'][pTickid] == nil then
        return 'fail:'..pUser..'-withdrawal-unfinish-'..pTickid..'-nil'
    end
    if gWithdrawal[pTickid] == nil then
        return 'fail:'..pTickid..'-withdrawal-nil'
    end
    local curData = {}
    curData['id'] = gWithdrawal[pTickid][id]
    curData['etheraddress'] = gWithdrawal[pTickid]['etheraddress']
    curData['amount'] = gWithdrawal[pTickid]['amount']
    curData['user'] = gWithdrawal[pTickid]['user']
    if curData['user'] ~= pUser then
        return 'fail:'..curData['user']..'~='..pUser
    end
    if curData['id'] ~= tonumber(pTickid) then
        return 'fail:'..curData['id']..'~='..tonumber(pTickid)
    end
    gList[gUser]['freezen'] = gList[gUser]['freezen']-curData['amount']
    gWithdrawal[pTickid] = pTickid
    gList[pUser]['withdrawal']['unfinish'][tonumber(pTickid)] = nil
    gList[pUser]['withdrawal']['finish'][tonumber(pTickid)] = curData
    return 'ok'
end

function addEtheraddress(pEtheraddress)
    if gUser ~= banker then
        return 'fail:only owner can addEtheraddress'
    end
    table.insert( gEtheraddress, pEtheraddress )
    return 'ok'
end

function register()
    if #gEtheraddress == 0 then
        return 'fail'
    end
    if gList[gUser] ~= nil then
        return 'fail'
    end
    gList[gUser] = {}
    gList[gUser]['freezen'] = 0
    gList[gUser]['withdrawal'] = {}
    gList[gUser]['withdrawal']['finish'] = {}
    gList[gUser]['withdrawal']['unfinish'] = {}
    gList[gUser]['ethaddress'] = gEtheraddress[1]
    table.remove( gEtheraddress, 1 )
    return 'ok'
end

function removeUser(pUser)
    if gUser ~= banker then
        return 'fail:only owner can removeUser'
    end
    gList[pUser] = {}
    return 'ok'
end

function init()
    _Reset()
    banker = gUser
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
		return _toJson('balanceOf',0)
	end
	return _toJson('balanceOf',gBalance[pUser])
end

function _Reset()
    print('Hello Crazy Miner!')
    MinePool = 0
    BonusPool = 0
    totalHashRate = 0
    totalPlayer = 0
    hashPrice = initHashRatePrice
    for key,v in pairs(gHashRate) do
        gHashRate[key] = 0
    end
    isPlaying = false
end

function _timeout()
    Tick = Tick + 1;
    _tick()
end

function _tick()
    if(isPlaying) then
        if(totalHashRate<=MinePool) then
            MinePool = MinePool - totalHashRate;
            local key,v
            for key,v in pairs(gBalance) do
                gBalance[key] = v + gHashRate[key]
            end
        else
            local key,v
            for key,v in pairs(gBalance) do
                MinePool = MinePool - gHashRate[key];
                gBalance[key] = v + gHashRate[key]
                if(MinePool<=0) then
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
end

function _tickTest(cnt)
    for i = 1,cnt do
        _timeout()
    end
end

function BuyHash()
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
        hashPrice = math.floor(hashPrice * hashPriceIncreaceRate)
        lastIncoming = gUser
        isPlaying = true;
    end

    local size = 0
    for key,v in pairs(gHashRate) do
        size = size + 1
    end
    TotalPlayer = size
end

function Recharge(pUser,amount)
    if gUser ~= banker then
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
end

function getInfo(addr) 
    return json.encode({
    Tick = Tick,
    Round = Round,
    IsPlaying = isPlaying,
    Banker = banker,
    LastIncoming = lastIncoming,
    TotalPlayer = totalPlayer,
    TotalCalcPower = totalHashRate,
    CalcPowerPrice = hashPrice,
    MinePool = MinePool,
    BonusPool = BonusPool,
    LocalAddr = gUser,
    Balance = gBalance[addr],
    CalcPower = gHashRate[addr],
    Freezen = gList[addr]['freezen'],
    Wfinish = gList[gUser]['withdrawal']['finish'],
    Wunfinish = gList[gUser]['withdrawal']['unfinish'],
    Dfinish = gList[gUser]['deposite']['finish'],
    Dunfinish = gList[gUser]['deposite']['unfinish']
})
end

function getLadderInfo()
    return json.encode(ladder)
end

function _Print()
    print('All Balance')
    for key,v in pairs(gBalance) do
        print(key)
        print(v)
        print(gHashRate[key])
    end
    print(getInfo('P1'))
    print(getLadderInfo())
end

function test()
    _setUser('1234')
    init()
    _setUser('P1')
    register()
    _setUser('P2')
    register()
    _Reset()
    Recharge('P1',10000)
    Recharge('P2',10000) 
    _setUser('P1')
    BuyHash()
    BuyHash()
    BuyHash()
    BuyHash()
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
    Recharge('P1',10000)
    Recharge('P2',10000) 
    Recharge('P1',10000)
    Recharge('P2',10000) 
    BuyHash()
    _Print()
end

test()