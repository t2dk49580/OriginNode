json = require 'json'

gName  = 'hash'
gOwner = nil
gUser  = nil
gData  = {}
gTotal = 1
gBalance = {}

function init()
    gOwner = gUser
    gBalance[gUser] = gTotal
    local curResult = {}
    curResult['contract'] = gName
    curResult['function'] = 'init'
    curResult['user'] = gUser
    return json.encode(curResult)
end

function _setUser(pUser)
    gUser = pUser
end

function _getTotal()
    return gTotal
end

function _getOwner()
    return gOwner
end

function getOwner()
    return _getOwner()
end

function getTotal()
    return _getTotal()
end

function getBalance()
    local curResult = {}
    curResult['contract'] = gName
    curResult['function'] = 'getBalance'
    curResult['user'] = gUser
    curResult['balance'] = gBalance[gUser]
    return json.encode(curResult)
end

function enable(pUser)
    if gUser ~= gOwner then
        return 'fail'
    end
    gBalance[pUser] = 1
    local curResult = {}
    curResult['contract'] = gName
    curResult['function'] = 'enable'
    curResult['user'] = pUser
    curResult['balance'] = gBalance[pUser]
    return json.encode(curResult)
end

function insert(pKey,pVar)
    if gBalance[gUser] < 1 then
        return 'fail'
    end
    if gData[pKey] == nil then
        gData[pKey] = {}
        gData[pKey]['key'] = pKey
        gData[pKey]['owner'] = gUser
    end
    if gData[pKey]['owner'] ~= gUser then
        return 'fail'
    end
    gBalance[gUser] = 0
    gData[pKey]['value'] = pVar
    local curResult = {}
    curResult['contract'] = gName
    curResult['function'] = 'insert'
    curResult['user'] = gUser
    curResult['key'] = pKey
    curResult['value'] = pVar
    return json.encode(curResult)
end

function getValue(pKey)
    local curResult = {}
    curResult['contract'] = gName
    curResult['function'] = 'getValue'
    curResult['user'] = gUser
    curResult['key'] = pKey
    curResult['value'] = gData[pKey]['value']
    return json.encode(curResult)
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

function getDump()
    local curResult = {}
    if gUser ~= gOwner then
        curResult['data'] = 'null'
        return json.encode(curResult)
    end
    local curResult = {}
    curResult['data'] = gData
    curResult['owner'] = gOwner
    curResult['total'] = gTotal
    curResult['balance'] = gBalance
    return json.encode(curResult)
end

function setData(pData)
    if gUser ~= gOwner then
        return 'fail'
    end
    local curData = json.decode(pData)
    gData = nil
    gBalance= nil
    gData = _clone(curData['data'])
    gOwner = curData['owner']
    gTotal = curData['total']
    gBalance = _clone(curData['balance'])
    local curResult = {}
    curResult['result'] = true
    return json.encode(curResult)
end

_setUser('1234')
init()
enable('aaaa')
print(getDump())
_setUser('aaaa')
insert('CM','CM10')
_setUser('1234')
print(getDump())
enable('aaaa')
_setUser('aaaa')
insert('CM','CM11')
_setUser('1234')
print(getDump())