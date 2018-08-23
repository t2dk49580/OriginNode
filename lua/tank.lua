_G['os'] = nil
_G['io'] = nil
json = require 'json'

gUser    = nil
gOwner   = nil
gName    = 'TANK'
gSymbol  = 'TANK'
gIcon    = ''
gTimeout = 0
gPlayer  = {}
gPlayerMax = 2
gBalance = {}
gTotal   = 100000000
gRoom    = {}
gQueue   = {}
gTick    = {}
gPlayerNum = 0
gMsg     = {}

function _setUser(pUser)
    gUser = pUser
end

function init()
    gOwner = gUser
    return 'ok'
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