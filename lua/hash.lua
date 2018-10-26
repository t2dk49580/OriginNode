json = require 'json'

gName  = 'hash'
gOwner = nil
gUser  = nil
gData  = {}
gBalance = {}
gTotal = 10000

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

function init()
    gOwner = gUser
    gBalance[gUser] = gTotal
    local curResult = {}
    curResult['contract'] = gName
    curResult['function'] = 'init'
    curResult['user'] = gUser
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

