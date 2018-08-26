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
gBalance = {}
gTotal   = 100000000
gRoomIndex = '1'
gRoom    = {}
gQueue   = {}
gTick    = {}
gMsg     = {}
gGameType= {}
gTankType= {}
gStarting= {}

function _setUser(pUser)
    gUser = pUser
end

function init()
    gOwner = gUser
    regTankType('tank0')
    regGameType('3v3','team','map0','6')
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

function _timeout()
    if #gStarting == 0 then
        return 'fail 0'
    end

    for key in pairs(gStarting) do
        local curKey = tostring(key)
        gRoom[curKey]['tick'] = {}
        gRoom[curKey]['time'] = gRoom[curKey]['time']+1
        local curQueue = {}
        if #gRoom[curKey]['queue'] > 0 then
            curQueue = _clone(gRoom[curKey]['queue'])
        end
        gRoom[curKey]['queue'] = {}
        table.insert( gRoom[curKey]['tick'], curQueue )
    end
    return 'fail 1'
end

function regGameType(pTypeID,pFightID,pMapID,pPlayerMax)
    if gGameType[pTypeID] ~= nil then
        return 'fail'
    end
    gGameType[pTypeID] = {}
    gGameType[pTypeID]['fight'] = pFightID
    gGameType[pTypeID]['map']   = pMapID
    gGameType[pTypeID]['playermax'] = tonumber(pPlayerMax)
    return 'ok'
end

function regTankType(pTypeID)
    if gTankType[pTypeID] ~= nil then
        return 'fail'
    end
    gTankType[pTypeID] = true
    return 'ok'
end

function _regPlayer()
    if gPlayer[gUser] ~= nil then
        return 'fail'
    end
    gPlayer[gUser] = {}
    gPlayer[gUser]['balance'] = 0
    gPlayer[gUser]['tank0'] = true;
    gPlayer[gUser]['room']  = '0'
    return 'ok'
end

function _createRoom(pGameType)
    local curIndex= gRoomIndex
    gRoom[curIndex] = {}
    gRoom[curIndex]['id'] = curIndex
    gRoom[curIndex]['type'] = pGameType
    gRoom[curIndex]['stat'] = 'wait'
    gRoom[curIndex]['data'] = {}
    gRoom[curIndex]['queue']= {}
    gRoom[curIndex]['tick'] = {}
    gRoom[curIndex]['time'] = 0
    gRoom[curIndex]['playercount'] = 1
    --gRoomIndex = tostring(tonumber(gRoomIndex) + 1)
    print(json.encode(gRoom[curIndex]))
    print(json.encode(gRoom['1']))
    return curIndex
end

function _joinRoom(pRoomIndex)
    local curGameType = gRoom[pRoomIndex][type]
    local curPlayerMax= gGameType[curGameType]
    gRoom[pRoomIndex]['playercount'] = gRoom[pRoomIndex]['playercount']+1
    if gRoom[pRoomIndex]['playercount'] >= curPlayerMax then
        gRoom[pRoomIndex]['stat'] = 'start'
        table.insert( gStarting, pRoomIndex )
    end
end

function joinGame(pName,pGameType,pTankType,pData)
    _regPlayer()
    if gGameType[pGameType] == nil then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    if gTankType[pTankType] == nil then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    if gPlayer[gUser][pTankType] == nil then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    if gPlayer[gUser]['room'] ~= '0' then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    local curRoomIndex = '1'
    if gRoom[gRoomIndex] == nil then
        curRoomIndex = _createRoom(pGameType)
        print(json.encode(gRoom['1']))
    else
        if gRoom[gRoomIndex]['stat'] == 'wait' then
            curRoomIndex = gRoomIndex
            _joinRoom(curRoomIndex)
        else
            gRoomIndex = tostring(tonumber(gRoomIndex) + 1)
            curRoomIndex = _createRoom(pGameType)
        end
    end
    gPlayer[gUser]['room'] = tostring(curRoomIndex)
    table.insert(gRoom[curRoomIndex]['data'], pData)
    return curRoomIndex
end

function getRoom(pRoomID)
    return json.encode(gRoom[pRoomID])
end

function getStat()
    local curResult = {}
    curResult['owner'] = gUser
    curResult['room']  = gPlayer[gUser]['room']
    if curResult['room'] ~= '0' then
        curResult['stat'] = gRoom[curResult['room']]['stat']
        curResult['playercount'] = gRoom[curResult['room']]['playercount']
    end
    return json.encode(curResult)
end

_setUser('1234')
init()
regTankType('tank1')
regTankType('tank2')

print(joinGame('user0','3v3','tank0','{user0-data}'))

print(getStat())
print(getRoom('1'))
table.insert( gStarting,'1' )
print(_timeout())