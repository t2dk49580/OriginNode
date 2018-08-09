_G['os'] = nil
_G['io'] = nil
json = require 'json'

gUser    = nil
gOwner   = nil
gName    = 'TANK DEMO'
gSymbol  = 'TANK'
gIcon    = ''
gTimeout = 0
gPlayer  = {}
gPlayerMax = 2
gBalance = {}
gTotal   = 10000
gQueue   = {}
gTotal   = 10000000
gTick    = {}

function _setUser(pUser)
    gUser = pUser
end

function init()
    gOwner = gUser
end

function getIcon()
    return _getResult(gUser,'getIcon',true,gIcon)
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

function _getOwner()
    return gOwner
end

function _getTotal()
    return gTotal
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

function timeout()
    --if gUser ~= gOwner then
    --    return 'fail'
    --end
    gTimeout = gTimeout+1
    local curQueue = _clone(gQueue)
    gQueue = {}
    table.insert( gTick, curQueue )
    return 'fail'
end

function setPlayerMax(pMax)
    if gUser ~= gOwner then
        return 'fail'
    end
    gPlayerMax = pMax
    return _getResult('*','setPlayerMax',true,pMax)
end

function joinGame()
    if #gPlayer >= 2 then
        return 'fail'
    end
    table.insert(gPlayer,gUser)
    if #gPlayer >= 2 then
        return _getResult('*','startGame',true,gPlayer)
    else
        return _getResult('*','joinGame',true,gUser)
    end
end

function play(pData)
    table.insert(gQueue, pData)
    --return _getResult(gUser,'play',true,pData)
    return 'fail'
end

function getTick(pIndex)
    if tonumber(pIndex) > #gTick then
        return 'null'
    end
    return json.encode(gTick[tonumber(pIndex)])
end

function getStat()
    if #gPlayer < gPlayerMax then
        return 'null'
    end
    return json.encode(gPlayer)
end

function closeGame()
    gPlayer = 0
    gPlayer = {}
    gTimeout = 0
    gQueue = {}
    gTick = {}
    return _getResult(gUser,'closeGame',true,0)
end

_setUser('root')
init()
_setUser('user1')
print(joinGame())

_setUser('user2')
print(joinGame())

print(getStat())

_setUser('user1')
print(play('{"ID":"User1","CMDS":[{"Vertical":1.0,"Horizontal":-0.6000000238418579,"Fire":false}'))

_setUser('user2')
print(play('{"ID":"User1","CMDS":[{"Vertical":1.0,"Horizontal":-0.6000000238418579,"Fire":false}'))

_setUser('root')
print(timeout())
print(getTick('1'))