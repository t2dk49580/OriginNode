json = require 'json'

gUser = nil

Banker = '01234567890'
bonusRate = 0.1
hashPriceIncreaceRate = 0.01
initHashRatePrice = 100000 

Round = 1
lastRoundWinner = ''
totalHashRate = 0
hashPrice = 0
lastIncoming = ''
MinePool = 0
BonusPool = 0
isPlaying = false
size = 0
gBalance = {}
gHashRate = {}

function init()
    _Reset()
    Banker = gUser
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
    hashPrice = initHashRatePrice
    for key,v in pairs(gBalance) do
        gBalance[key] = 0
    end
    isPlaying = false
end

function _timeout()
    _tick()
end

function _tick()
    if(isPlaying) then
        if(totalHashRate<=MinePool) then
            MinePool = MinePool - totalHashRate;
            for key,v in pairs(gBalance) do
                gBalance[key] = v + gHashRate[key]
            end
        else
            for key,v in pairs(gBalance) do
                MinePool = MinePool - gHashRate[i];
                gBalance[key] = v + gHashRate[key]
                if(MinePool<=0) then
                    break
                end
            end
            gBalance[lastIncoming] = gBalance[lastIncoming] + BonusPool
            _Reset()
            Round = Round + 1
            lastRoundWinner = lastIncoming
        end
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
        MinePool = hashPrice * (1 - bonusRate)
        BonusPool = hashPrice * bonusRate
        hashPrice = hashPrice * hashPriceIncreaceRate
        lastIncoming = gUser
        isPlaying = true;
    end
end

function Recharge(pUser,amount)
    gBalance[pUser] = tonumber(amount)
    if gHashRate[pUser] == nil then
        gHashRate[pUser] = 0
    end
    size = size + 1
end

function getInfo(addr) 
    return json.encode({Round=Round,
    LastWinner = lastRoundWinner,
    LastIncoming = lastIncoming,
    TotalHash = totalHashRate,
    HashPrice = hashPrice,
    MinePool = MinePool,
    BonusPool = BonusPool,
    IsPlaying = isPlaying,
    Balance = gBalance[addr],
    HashRate = gHashRate[addr]
})
end

function _Print()
    print('All Balance')
    for key,v in pairs(gBalance) do
        print(key)
        print(v)
        print(gHashRate[key])
    end
    print(getInfo('P1'))
end

function test()
    _Reset()
    Recharge('P1',1000000)
    Recharge('P2',1000000)
    
    _setUser('P1')
    BuyHash()
    _timeout();
    _timeout();
    _timeout();
    _setUser('P2')
    BuyHash()
    _timeout();
    _timeout();
    _Print()
end

test()