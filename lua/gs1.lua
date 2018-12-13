json = require 'json'

gUser = nil
gModify = '20181201'
gData = {}

function _addResult(pUser,pMethod,pMsg,pAll)
    local buffer = {}
    local result = pAll
    buffer['method'] = pMethod
    buffer['msg']    = pMsg
    buffer['owner']  = pUser
    buffer['symbol'] = gSymbol
    table.insert(result,buffer)
    return result
end

function _getResult(pUser,pMethod,pResult,pMsg)
    local buffer = {}
    local result = _addResult(pUser,pMethod,pMsg,buffer)
    local final = {}
    final['broad'] = 'N'
    final['result'] = pResult
    final['data'] = result
    return json.encode(final)
end

function _getBroadResult(pUser,pMethod,pResult,pMsg)
    local buffer = {}
    local result = _addResult(pUser,pMethod,pMsg,buffer)
    local final = {}
    final['broad'] = 'Y'
    final['result'] = pResult
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

function _check(pData,pJson)
    local k,v
    for k,v in pairs(pData) do
        if pJson[v] == nil then
            return false
        end
    end
    return true
end

function getDump()
    if gUser ~= gData['owner'] then
        return 'fail'
    end
    return _getResult(gUser,"getDump",true,gData)
end

function init()
    gData['owner'] = gUser
    gData['version'] = 0.01
    gData['total'] = 10000*100000000
    gData['system'] = {}
    gData['system']['country'] = {}
    gData['system']['scene'] = {}
    gData['system']['player'] = {}
    gData['system']['role'] = {}
    gData['system']['soldier'] = {}
    gData['system']['monster'] = {}
    gData['system']['city'] = {}
    gData['system']['building'] = {}
    gData['system']['weapon'] = {}
    gData['system']['armor'] = {}
    gData['system']['potion'] = {}
    return _getBroadResult(gUser,"init",true,"ok")
end

function addCountry(pData)
    if gUser ~= gData['owner'] then
        return 'fail'
    end
    local check = {'id','name'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail'
    end
    if gData['system']['country'][curJson['id']] ~= nil then
        return 'fail'
    end
    curJson['scene'] = {}
    gData['system']['country'][curJson['id']] = curJson
    return _getBroadResult(gUser,"addCountry",true,curJson)
end

function addScene(pData)
    if gUser ~= gData['owner'] then
        return 'fail'
    end
    local check = {'id','name','cid','cx','cy','w','h','image'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail'
    end
    if gData['system']['country'][curJson['cid']] == nil then
        return 'fail'
    end
    if gData['system']['scene'][curJson['id']] ~= nil then
        return 'fail'
    end
    curJson['player'] = {}
    curJson['monster'] = {}
    curJson['building'] = {}
    gData['system']['scene'][curJson['id']] = curJson
    table.insert( gData['system']['country'][curJson['cid']]['scene'], gData['system']['scene'][curJson['id']] )
    return _getBroadResult(gUser,"addScene",true,curJson)
end

function addRole(pData)
    if gUser ~= gData['owner'] then
        return 'fail'
    end
    local check = {'id','cid','sex','image','w','h','wb','hb'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail'
    end
    if gData['system']['country'][curJson['cid']] == nil then
        return 'fail'
    end
    if gData['system']['role'][curJson['id']] ~= nil then
        return 'fail'
    end
    gData['system']['role'][curJson['id']] = curJson
    return _getBroadResult(gUser,"addRole",true,curJson)
end

function addSoldier(pData)
    if gUser ~= gData['owner'] then
        return 'fail'
    end
    local check = {'id','cid','sex','name','image','w','h','wb','hb','st','hp','weight','exp','expm','lv','spd','able','power','price'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail'
    end
    if gData['system']['country'][curJson['cid']] == nil then
        return 'fail'
    end
    if gData['system']['soldier'][curJson['id']] ~= nil then
        return 'fail'
    end
    gData['system']['soldier'][curJson['id']] = curJson
    return _getBroadResult(gUser,"addSoldier",true,curJson)
end

function addMonster(pData)
    if gUser ~= gData['owner'] then
        return 'fail'
    end
    local check = {'id','name','image','w','h','wb','hb','st','hp','weight','exp','expm','lv','spd','able','power','price'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail'
    end
    if gData['system']['monster'][curJson['id']] ~= nil then
        return 'fail'
    end
    gData['system']['monster'][curJson['id']] = curJson
    return _getBroadResult(gUser,"addMonster",true,curJson)
end

function addCity(pData)
    if gUser ~= gData['owner'] then
        return 'fail'
    end
    local check = {'id','cid','sid','x','y','name','image','w','h','wb','hb','pp'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail'
    end
    if gData['system']['country'][curJson['cid']] == nil then
        return 'fail'
    end
    if gData['system']['scene'][curJson['sid']] == nil then
        return 'fail'
    end
    if gData['system']['city'][curJson['id']] ~= nil then
        return 'fail'
    end
    curJson['building'] = {}
    gData['system']['city'][curJson['id']] = curJson
    return _getBroadResult(gUser,"addCity",true,curJson)
end

function setCity(pData)
    if gUser ~= gData['owner'] then
        return 'fail'
    end
    local check = {'cid','sid','tid','x','y'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail'
    end
    if gData['system']['country'][curJson['cid']] == nil then
        return 'fail'
    end
    if gData['system']['scene'][curJson['sid']] == nil then
        return 'fail'
    end
    if gData['system']['scene'][curJson['tid']] == nil then
        return 'fail'
    end
    gData['system']['scene'][curJson['tid']]['x'] = curJson['x']
    gData['system']['scene'][curJson['tid']]['y'] = curJson['y']
    return _getBroadResult(gUser,"setCity",true,curJson)
end

function addBuilding(pData)
    if gUser ~= gData['owner'] then
        return 'fail'
    end
    local check = {'id','x','y','name','image','w','h'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail'
    end
    if gData['system']['building'][curJson['id']] ~= nil then
        return 'fail'
    end
    curJson['goods'] = {}
    gData['system']['building'][curJson['id']] = curJson
    return _getBroadResult(gUser,"addBuilding",true,curJson)
end

function addWeapon(pData)
    if gUser ~= gData['owner'] then
        return 'fail'
    end
    local check = {'id','name','image','at','rg','wt','buy','sell'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail'
    end
    if gData['system']['weapon'][curJson['id']] ~= nil then
        return 'fail'
    end
    gData['system']['weapon'][curJson['id']] = curJson
    return _getBroadResult(gUser,"addWeapon",true,curJson)
end

function addArmor(pData)
    if gUser ~= gData['owner'] then
        return 'fail'
    end
    local check = {'id','name','image','hp','wt','buy','sell'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail'
    end
    if gData['system']['armor'][curJson['id']] ~= nil then
        return 'fail'
    end
    gData['system']['armor'][curJson['id']] = curJson
    return _getBroadResult(gUser,"addArmor",true,curJson)
end

function addPotion(pData)
    if gUser ~= gData['owner'] then
        return 'fail'
    end
    local check = {'id','name','image','hp','wt','buy','sell'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail'
    end
    if gData['system']['potion'][curJson['id']] ~= nil then
        return 'fail'
    end
    gData['system']['potion'][curJson['id']] = curJson
    return _getBroadResult(gUser,"addPotion",true,curJson)
end

_setUser('root')
init()
local ret
local cur = {}
cur['id'] = '1'
cur['name'] = 'ming chao'
ret = addCountry(json.encode(cur))

local cur1 = {}
cur1['id'] = '1-1'
cur1['name'] = 'map0'
cur1['cid'] = '1'
cur1['cx'] = '0'
cur1['cy'] = '0'
cur1['w'] = '500'
cur1['h'] = '500'
cur1['image'] = 'chees.jpg'
ret = addScene(json.encode(cur1))

local cur2 = {}
cur2['id'] = 'jinjiao'
cur2['cid'] = '1'
cur2['sex'] = 'man'
cur2['w'] = '50'
cur2['h'] = '100'
cur2['wb'] = '50'
cur2['hb'] = '20'
cur2['image'] = 'role0.jpg'
ret = addRole(json.encode(cur2))

local cur3 = {id='dao',cid='1',sex='man',name='wang',image='wang.png',w='50',h='100',wb='50',hb='20',st='15',hp='10',weight='5',exp='0',expm='10',lv='0',spd='300',able='0',power='25',price='25'}
ret = addRole(json.encode(cur3))

local cur4 = {id='m0',name='gangar',image='gangar.png',w='100',h='100',wb='100',hb='50',st='10',hp='30',weight='60',exp='0',expm='0',lv='0',spd='200',able='0',power='70',price='70'}
ret = addMonster(json.encode(cur4))

local cur5 = {id='c0',cid='1',sid='1-1',x='100',y='100',name='shanghai',image='sh.png',w='200',h='200',wb='200',hb='100',pp='50000'}
ret = addCity(json.encode(cur5))

local cur6 = {id='b0',x='50',y='50',name='weapon store',image='ws.png',w='80',h='50'}
ret = addBuilding(json.encode(cur6))

local cur7 = {id='w0',name='dao',image='dao.png',at='5',rg='1',wt='2',buy='5',sell='1'}
ret = addWeapon(json.encode(cur7))

local cur8 = {id='a0',name='yifu',image='yifu.png',hp='10',wt='2',buy='10',sell='2'}
ret = addArmor(json.encode(cur8))

local cur9 = {id='p0',name='red',image='red.png',hp='20',wt='1',buy='1',sell='0'}
ret = addPotion(json.encode(cur9))

print(ret)
