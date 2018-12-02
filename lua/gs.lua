json = require 'json'

gUser = nil
gModify = '20181201'
gData = {}

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
    local final = {}
    final['broad'] = 'N'
    final['data'] = result
    return json.encode(final)
end

function _getBroadResult(pUser,pMethod,pResult,pMsg)
    local buffer = {}
    local result = _addResult(pUser,pMethod,pResult,pMsg,buffer)
    local final = {}
    final['broad'] = 'Y'
    final['data'] = result
    return json.encode(final)
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

function init()
    gData['role'] = {}
    gData['owner'] = gUser
    gData['user'] = {}
    gData['version'] = 0.01
    gData['map'] = {}
    gData['map']['china'] = {}
    gData['map']['china']['width'] = 800
    gData['map']['china']['height'] = 600
    gData['map']['china']['user'] = {}
    gData['map']['china']['moving'] = {}
    return _getBroadResult(gUser,"init",true,"ok")
end

function _setUser(pUser)
    gUser = pUser 
end

function _getTotal()
    return 100000
end

function _getOwner()
    return gData['owner']
end

function _getLenght(pX0,pY0,pX1,pY1)
    return math.sqrt((math.abs(pX0-pX1)*math.abs(pX0-pX1)+math.abs(pY0-pY1)*math.abs(pY0-pY1)))
end

function getDump()
    if gUser ~= gData['owner'] then
        return 'fail'
    end
    return _getResult(gUser,"getDump",true,gData)
end

function doTimeout()
    if gUser ~= gData['owner'] then
        return 'fail'
    end
    local flag = 'N'
    local k,v,r
    local curResult = {}
    for k,v in pairs(gData['map']['china']['moving']) do
        flag = 'Y'
        gData['user'][k]['count'] = 0
        if gData['user'][k]['y'] == gData['user'][k]['yt'] and gData['user'][k]['x'] == gData['user'][k]['xt'] then
            table.insert( curResult, k )
        end
        local curLen = _getLenght(v['x'],v['y'],v['xn'],v['yn'])
        if math.ceil(curLen) <= gData['user'][k]['speed'] then
            gData['user'][k]['x'] = gData['user'][k]['xn']
            gData['user'][k]['y'] = gData['user'][k]['yn']
        end
    end
    if flag == 'N' then
        return 'fail'
    end
    for r in pairs(curResult) do
        gData['map']['china']['moving'][r] = nil
    end
    return _getBroadResult(gUser,"doTimeout",true,gData['map']['china'])
end

function addRole(pName,pData)
    if gUser ~= gData['owner'] then
        return 'fail'
    end
    gData['role'][pName] = pData
    return _getResult(gUser,"addRole",true,pName)
end

function getRole(pName)
    return _getResult(gUser,"getRole",true,gData['role'][pName])
end

function login(pName,pRole)
    if gData['role'][pRole] == nil then
        return 'fail'
    end
    if gData['user'][gUser] == nil then
        gData['user'][gUser] = {}
        gData['user'][gUser]['name'] = pName
        gData['user'][gUser]['role'] = pRole
        gData['user'][gUser]['balance'] = 0
        gData['user'][gUser]['count'] = 0
        gData['user'][gUser]['speed'] = 100.0
        gData['user'][gUser]['x'] = 400
        gData['user'][gUser]['y'] = 300
        gData['user'][gUser]['xn'] = 400
        gData['user'][gUser]['yn'] = 300
        gData['user'][gUser]['xt'] = 400
        gData['user'][gUser]['yt'] = 300
    end
    if gData['user'][gUser]['online'] == 'Y' then
        return 'fail'
    end
    gData['user'][gUser]['online'] = 'Y'
    gData['map']['china']['user'][gUser] = gData['user'][gUser]

    return _getBroadResult(gUser,"startPlay",true,gData['user'][gUser])
end

function forceLogout(pUser)
    if gUser ~= gData['owner'] then
        return 'fail'
    end
    gData['user'][pUser]['online'] = 'N'
    gData['user'][pUser]['count'] = 0
    gData['map']['china']['moving'][pUser] = nil
    gData['map']['china']['user'][pUser] = nil
    return _getResult(gUser,"logout",true,pUser)
end

function logout()
    if gData['user'][gUser]['online'] == 'N' then
        return 'fail'
    end
    gData['user'][gUser]['online'] = 'N'
    gData['user'][gUser]['count'] = 0
    gData['map']['china']['moving'][gUser] = nil
    gData['map']['china']['user'][gUser] = nil
    return _getResult(gUser,"logout",true,gUser)
end

function getMap(pMap)
    return _getResult(gUser,"getMap",true,gData['map'][pMap])
end

function moveTo(pX,pY)
    gData['user'][gUser]['xt'] = tonumber(pX)
    gData['user'][gUser]['yt'] = tonumber(pY)
    gData['map']['china']['moving'][gUser] = gData['user'][gUser]

    return _getResult(gUser,"moveTo",true,gData['user'][gUser])
end

function run(pX,pY)
    if gData['map']['china']['moving'][gUser] == nil then
        return 'fail'
    end
    if gData['user'][gUser]['x'] == tonumber(pX) and gData['user'][gUser]['y'] == tonumber(pY) then
        return 'fail'
    end
    if gData['user'][gUser]['count'] > 0 then
        return 'fail'
    end
    gData['user'][gUser]['xn'] = tonumber(pX)
    gData['user'][gUser]['yn'] = tonumber(pY)
    gData['user'][gUser]['count'] = gData['user'][gUser]['count']+1
    return 'fail'
end

_setUser('GM')
print(init())
addRole('monster0','hp=100')
addRole('monster1','hp=100')
addRole('monster2','hp=100')
addRole('monster3','hp=100')
for i=1,100,1 do
login('HAHA','monster0')
getMap('china')
moveTo('0','0')
run('350','350')
doTimeout()
run('300','300')
doTimeout()
json.encode(gData['map']['china']['user'])
logout()

end
print(getDump())
