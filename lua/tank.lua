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
    regTankType('light')
    regTankType('naive')
    regTankType('mid')
    regTankType('heavy')
    regGameType('1v1','all','map0','2')
    regGameType('3v3','all','map0','6')
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
    local key,v
    print(json.encode(gStarting))
    for key,v in pairs(gStarting) do
        local curKey = tostring(key)
        print(curKey)
        gRoom[curKey]['time'] = gRoom[curKey]['time']+1
        local curQueue = {}
        if #gRoom[curKey]['queue'] > 0 then
            curQueue = _clone(gRoom[curKey]['queue'])
        end
        gRoom[curKey]['queue'] = {}
        gRoom[curKey]['time'] = gRoom[curKey]['time']+1
        table.insert( gRoom[curKey]['tick'], curQueue )
    end
    return 'system timeout'
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

function getGameType()
    local curResult = {}
    curResult['method'] = 'getGameType'
    curResult['data'] = gGameType
    return json.encode(curResult)
end

function regTankType(pTypeID)
    if gTankType[pTypeID] ~= nil then
        return 'fail'
    end
    gTankType[pTypeID] = true
    return 'ok'
end

function getTankType()
    local curResult = {}
    curResult['method'] = 'getTankType'
    curResult['data'] = gTankType
    return json.encode(curResult)
end

function _regPlayer()
    if gPlayer[gUser] ~= nil then
        return 'fail'
    end
    gPlayer[gUser] = {}
    gPlayer[gUser]['balance'] = 0
    gPlayer[gUser]['naive'] = true;
    gPlayer[gUser]['mid'] = true;
    gPlayer[gUser]['heavy'] = true;
    gPlayer[gUser]['light'] = true;
    gPlayer[gUser]['room']  = '0'
    gPlayer[gUser]['playcount'] = 0
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
    gRoom[curIndex]['player'] = {}
    gRoom[curIndex]['time'] = 0
    gRoom[curIndex]['playcount'] = 0
    gRoom[curIndex]['playercount'] = 1
    --gRoomIndex = tostring(tonumber(gRoomIndex) + 1)
    return curIndex
end

function _joinRoom(pRoomIndex)
    local curGameType = gRoom[pRoomIndex]['type']
    local curPlayerMax= gGameType[curGameType]['playermax']
    gRoom[pRoomIndex]['playercount'] = gRoom[pRoomIndex]['playercount']+1
    if gRoom[pRoomIndex]['playercount'] >= curPlayerMax then
        gRoom[pRoomIndex]['stat'] = 'start'
        gStarting[pRoomIndex] = true
    end
end

function joinGame(pName,pGameType,pTankType,pData)
    _regPlayer()
    print(debug.getinfo(1).currentline,debug.getinfo(1).name,pName,pGameType,pTankType,pData)
    if gGameType[pGameType] == nil then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name,pGameType)
        return 'fail'
    end
    if gTankType[pTankType] == nil then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name,pTankType)
        return 'fail'
    end
    if gPlayer[gUser][pTankType] == nil then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name,gPlayer[gUser][pTankType])
        return 'fail'
    end
    if gPlayer[gUser]['room'] ~= '0' then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name,gPlayer[gUser]['room'])
        return 'fail'
    end
    local curRoomIndex = '1'
    if gRoom[gRoomIndex] == nil then
        curRoomIndex = _createRoom(pGameType)
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
    table.insert(gRoom[curRoomIndex]['player'], gUser)
    return curRoomIndex
end

function getStartRoom()
    return json.encode(gStarting)
end

function getRoom(pRoomID)
    local curResult = {}
    curResult['method'] = 'getRoom'
    curResult['data'] = gRoom[pRoomID]
    return json.encode(curResult)
end

function getStat()
    local curResult = {}
    curResult['owner'] = gUser
    curResult['method'] = 'getStat'
    curResult['room']  = gPlayer[gUser]['room']
    print(debug.getinfo(1).currentline,debug.getinfo(1).name)
    if curResult['room'] ~= '0' then
        curResult['stat'] = gRoom[curResult['room']]['stat']
        curResult['playercount'] = gRoom[curResult['room']]['playercount']
        curResult['data'] = gRoom[curResult['room']]['data']
    end
    return json.encode(curResult)
end

function getUserStat(pUser)
    local curResult = {}
    curResult['owner'] = pUser
    curResult['method'] = 'getStat'
    curResult['room']  = gPlayer[pUser]['room']
    print(debug.getinfo(1).currentline,debug.getinfo(1).name)
    if curResult['room'] ~= '0' then
        curResult['stat'] = gRoom[curResult['room']]['stat']
        curResult['playercount'] = gRoom[curResult['room']]['playercount']
        curResult['data'] = gRoom[curResult['room']]['data']
    end
    return json.encode(curResult)
end

function getPlay(pData)
    local curRoom = gPlayer[gUser]['room']
    if curRoom == '0' then
        return 'null'
    end
    if gRoom[curRoom]['stat'] ~= 'start' then
        return 'null'
    end
    gPlayer[gUser]['playcount'] = gPlayer[gUser]['playcount']+1
    table.insert( gRoom[curRoom]['queue'], pData )
    return 'null'
end

function getTick(pIndex)
    local curResult = {}
    curResult['index'] = tonumber(pIndex)
    curResult['method']  = 'getTick'
    local curRoom = gPlayer[gUser]['room']
    if curRoom == '0' then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        curResult['reason'] = 'player room == 0'
        return json.encode(curResult)
    end
    if tonumber(pIndex) >= #gRoom[curRoom]['tick']+1 then
        curResult['reason'] = pIndex..'>='..tostring(#gRoom[curRoom]['tick']+1)
        return json.encode(curResult)
    end
    curResult['data']  = gRoom[curRoom]['tick'][tonumber(pIndex)]
    return json.encode(curResult)
end

function closeGame()
    local curRoom = gPlayer[gUser]['room']
    if curRoom == '0' then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    if gRoom[curRoom]['stat'] ~= 'start' then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    for key in pairs(gRoom[curRoom]['player']) do
        gPlayer[gRoom[curRoom]['player'][key]]['room'] = '0'
    end
    gStarting[curRoom] = nil
    gRoom[curRoom] = nil
    return 'ok'
end

function forceClose(pRoomID)
    local curRoom = pRoomID
    if curRoom == '0' then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    if gRoom[curRoom]['stat'] ~= 'start' then
        print(debug.getinfo(1).currentline,debug.getinfo(1).name)
        return 'fail'
    end
    for key in pairs(gRoom[curRoom]['player']) do
        gPlayer[gRoom[curRoom]['player'][key]]['room'] = '0'
    end
    gStarting[curRoom] = nil
    gRoom[curRoom] = nil
    return 'ok'
end

_setUser('1111')
init()

_setUser('1111')
print(joinGame('user0','1v1','naive','{user0-data}'))
_setUser('2222')
print(joinGame('user1','1v1','naive','{user1-data}'))

print(getStat())
print(getRoom('1'))
print(getPlay('haha1'))
print(_timeout())
print(getPlay('haha2'))
print(_timeout())
print(getTick('1'))
print(getTick('2'))
print(closeGame())


