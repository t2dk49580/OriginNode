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
    if type(nNum) ~= 'number' then
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
        if type( object ) ~= 'table' then
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
    return _getResult(gUser,'getDump',true,gData)
end

function putDump(pData)
    if gUser ~= gData['owner'] then
        return 'fail'
    end
    gData = nil
    gData = json.decode(pData)
    return _getBroadResult(gUser,'putDump',true,'ok')
end

function init()
    gData = {}
    gData['owner'] = gUser
    gData['version'] = 0.01
    gData['total'] = 10000*100000000
    gData['name'] = {}
    gData['system'] = {}
    gData['system']['unit'] = {}
    gData['system']['country'] = {}
    gData['system']['scene'] = {}
    gData['system']['player'] = {}
    gData['system']['role'] = {}
    gData['system']['city'] = {}
    gData['system']['building'] = {}
    gData['system']['weapon'] = {}
    gData['system']['armor'] = {}
    gData['system']['potion'] = {}
    return _getBroadResult(gUser,'init',true,'ok')
end

function addUserProperty(pKey,pData)
    if gUser ~= gData['owner'] then
        return 'fail 1'
    end
    if pKey == nil or pData == nil then
        return 'fail 2'
    end
    gData[pKey] = pData
    return _getBroadResult(gUser,'addUserProperty',true,'ok')
end

function addSystemProperty(pKey,pData)
    if gUser ~= gData['owner'] then
        return 'fail 1'
    end
    if pKey == nil or pData == nil then
        return 'fail 2'
    end
    gData['system'][pKey] = pData
    return _getBroadResult(gUser,'addSystemProperty',true,'ok')
end

function addCountry(pData)
    if gUser ~= gData['owner'] then
        return 'fail 1'
    end
    local check = {'id','name','tid'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail 2'
    end
    curJson['scene'] = {}
    gData['system']['country'][curJson['id']] = curJson
    return _getBroadResult(gUser,'addCountry',true,curJson)
end

function addScene(pData)
    if gUser ~= gData['owner'] then
        return 'fail 1'
    end
    local check = {'id','name','cid','cx','cy','w','h','image'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail 2'
    end
    if gData['system']['country'][curJson['cid']] == nil then
        return 'fail 3'
    end
    curJson['player'] = {}
    curJson['monster'] = {}
    curJson['city'] = {}
    gData['system']['scene'][curJson['id']] = curJson
    table.insert( gData['system']['country'][curJson['cid']]['scene'], gData['system']['scene'][curJson['id']] )
    return _getBroadResult(gUser,'addScene',true,curJson)
end

function addUnit(pData)
    if gUser ~= gData['owner'] then
        return 'fail 1'
    end
    local check = {'id','cid','name','type','image','w','h','wb','hb'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail 2'
    end
    if gData['system']['country'][curJson['cid']] == nil then
        return 'fail 3'
    end
    gData['system']['unit'][curJson['id']] = curJson
    return _getBroadResult(gUser,'addUnit',true,curJson)
end

function addRole(pData)
    if gUser ~= gData['owner'] then
        return 'fail 1'
    end
    local check = {'id','uid','head','st','hp','wt','exp','expm','lv','spd','able','power','price'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail 2'
    end
    if gData['system']['unit'][curJson['uid']] == nil then
        return 'fail 3'
    end
    curJson['unit'] = _clone(gData['system']['unit'][curJson['uid']])
    curJson['goods'] = {}
    curJson['equipment'] = {}
    gData['system']['role'][curJson['id']] = curJson
    return _getBroadResult(gUser,'addRole',true,curJson)
end

function _addPlayer(pData)
    local check = {'id','sid','rid0','name','power','limit','finance','x','y','xt','yt','movetime','stat','online'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail 1'
    end
    if gData['system']['scene'][curJson['sid']] == nil then
        return 'fail 2'
    end
    if gData['system']['role'][curJson['rid0']] == nil then
        return 'fail 3'
    end
    curJson['roles'] = {}
    curJson['role']  = curJson['rid0']
    curJson['roles'][curJson['rid0']] = _clone(gData['system']['role'][curJson['rid0']])
    gData[gUser] = curJson
    gData['system']['player'][curJson['id']] = gData[gUser]
    gData['system']['scene'][curJson['sid']]['player'][gUser] = gData[gUser]
    return '_addPlayer ok'
end

function addCity(pData)
    if gUser ~= gData['owner'] then
        return 'fail 1'
    end
    local check = {'id','uid','sid','x','y','pp','inside'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail 2'
    end
    if gData['system']['scene'][curJson['sid']] == nil then
        return 'fail 3'
    end
    if gData['system']['unit'][curJson['uid']] == nil then
        return 'fail 4'
    end
    curJson['building'] = {}
    curJson['unit'] = _clone(gData['system']['unit'][curJson['uid']])
    gData['system']['city'][curJson['id']] = curJson
    table.insert( gData['system']['scene'][curJson['sid']]['city'], gData['system']['city'][curJson['id']] )
    return _getBroadResult(gUser,'addCity',true,curJson)
end

function addBuilding(pData)
    if gUser ~= gData['owner'] then
        return 'fail 1'
    end
    local check = {'id','uid','tid','x','y'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail 2'
    end
    if gData['system']['city'][curJson['tid']] == nil then
        return 'fail 3'
    end
    if gData['system']['unit'][curJson['uid']] == nil then
        return 'fail 4'
    end
    curJson['goods'] = {}
    curJson['unit'] = _clone(gData['system']['unit'][curJson['uid']])
    gData['system']['building'][curJson['id']] = curJson
    table.insert( gData['system']['city'][curJson['tid']]['building'], gData['system']['building'][curJson['id']] )
    return _getBroadResult(gUser,'addBuilding',true,curJson)
end

function addWeapon(pData)
    if gUser ~= gData['owner'] then
        return 'fail 1'
    end
    local check = {'id','uid','bid','at','rg','wt','bk','sk'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail 2'
    end
    if gData['system']['unit'][curJson['uid']] == nil then
        return 'fail 3'
    end
    if gData['system']['building'][curJson['bid']] == nil then
        return 'fail 4'
    end
    curJson['unit'] = _clone(gData['system']['unit'][curJson['uid']])
    gData['system']['weapon'][curJson['id']] = curJson
    table.insert( gData['system']['building'][curJson['bid']]['goods'], gData['system']['weapon'][curJson['id']] )
    return _getBroadResult(gUser,'addWeapon',true,curJson)
end

function addArmor(pData)
    if gUser ~= gData['owner'] then
        return 'fail 1'
    end
    local check = {'id','uid','bid','hp','wt','bk','sk'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail 2'
    end
    if gData['system']['unit'][curJson['uid']] == nil then
        return 'fail 3'
    end
    if gData['system']['building'][curJson['bid']] == nil then
        return 'fail 4'
    end
    curJson['unit'] = _clone(gData['system']['unit'][curJson['uid']])
    gData['system']['armor'][curJson['id']] = curJson
    table.insert( gData['system']['building'][curJson['bid']]['goods'], gData['system']['armor'][curJson['id']] )
    return _getBroadResult(gUser,'addArmor',true,curJson)
end

function addPotion(pData)
    if gUser ~= gData['owner'] then
        return 'fail 1'
    end
    local check = {'id','uid','bid','hp','wt','bk','sk'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail 2'
    end
    if gData['system']['unit'][curJson['uid']] == nil then
        return 'fail 3'
    end
    if gData['system']['building'][curJson['bid']] == nil then
        return 'fail 4'
    end
    curJson['unit'] = _clone(gData['system']['unit'][curJson['uid']])
    gData['system']['potion'][curJson['id']] = curJson
    table.insert( gData['system']['building'][curJson['bid']]['goods'], gData['system']['potion'][curJson['id']] )
    return _getBroadResult(gUser,'addPotion',true,curJson)
end

function createPlayer(pData)
    if gData[gUser] ~= nil then
        return 'fail 0'
    end
    local check = {'rid','name'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail 1'
    end
    if gData['system']['role'][curJson['rid']] == nil then
        return 'fail 2'
    end
    if gData['name'][curJson['name']] ~= nil then
        return 'fail 3'
    end
    local curUid = gData['system']['role'][curJson['rid']]['uid']
    local curCid = gData['system']['unit'][curUid]['cid']
    local curTid = gData['system']['country'][curCid]['tid']
    local curSid = gData['system']['city'][curTid]['sid']
    cur = {id=gUser,sid=curSid,rid0=curJson['rid'],rid1='',type='player',name=curJson['name'],power='0',limit='3',finance='1000',x='0',y='0',xt='0',yt='0',movetime='0',stat=curTid,online='N'}
    ret = _addPlayer(json.encode(cur))
    if string.sub(ret,0,4) == 'fail' then
        return 'fail 4'
    end
    gData['name'][curJson['name']] = gUser
    curJson['id'] = gUser
    return _getBroadResult(gUser,'createPlayer',true,curJson)
end
-----------------------------------------------------------------------
function getInfo(pData)
    return _getResult(gUser,'get'..pData,true,gData['system'][pData])
end

function getCountry(pData)
    return _getResult(gUser,'getCountry',true,gData['system']['country'][pData])
end

function getScene(pData)
    return _getResult(gUser,'getScene',true,gData['system']['scene'][pData])
end

function getUnit(pData)
    return _getResult(gUser,'getUnit',true,gData['system']['unit'][pData])
end

function getPlayer(pData)
    return _getResult(gUser,'getPlayer',true,gData[pData])
end

function getCity(pData)
    return _getResult(gUser,'getCity',true,gData['system']['city'][pData])
end

function getBuilding(pData)
    return _getResult(gUser,'getBuilding',true,gData['system']['building'][pData])
end

function getWeapon(pData)
    return _getResult(gUser,'getWeapon',true,gData['system']['weapon'][pData])
end

function getArmor(pData)
    return _getResult(gUser,'getArmor',true,gData['system']['armor'][pData])
end

function getPotion(pData)
    return _getResult(gUser,'getPotion',true,gData['system']['potion'][pData])
end

function setCountry(pData)
    if gUser ~= gData['owner'] then
        return 'fail 1'
    end
    local curJson = json.decode(pData)
    gData['system']['country'][curJson['id']] = nil
    gData['system']['country'][curJson['id']] = curJson
    return _getResult(gUser,'setCountry',true,curJson)
end

function setScene(pData)
    if gUser ~= gData['owner'] then
        return 'fail 1'
    end
    local curJson = json.decode(pData)
    gData['system']['scene'][curJson['id']] = nil
    gData['system']['scene'][curJson['id']] = curJson
    return _getResult(gUser,'setScene',true,curJson)
end

function setUnit(pData)
    if gUser ~= gData['owner'] then
        return 'fail 1'
    end
    local curJson = json.decode(pData)
    gData['system']['unit'][curJson['id']] = nil
    gData['system']['unit'][curJson['id']] = curJson
    return _getResult(gUser,'setUnit',true,curJson)
end

function setPlayer(pData)
    if gUser ~= gData['owner'] then
        return 'fail 1'
    end
    local curJson = json.decode(pData)
    gData[gUser] = nil
    gData[gUser] = curJson
    return _getResult(gUser,'setPlayer',true,curJson)
end

function setCity(pData)
    if gUser ~= gData['owner'] then
        return 'fail 1'
    end
    local curJson = json.decode(pData)
    gData['system']['city'][curJson['id']] = nil
    gData['system']['city'][curJson['id']] = curJson
    return _getResult(gUser,'setCity',true,curJson)
end

function setBuilding(pData)
    if gUser ~= gData['owner'] then
        return 'fail 1'
    end
    local curJson = json.decode(pData)
    gData['system']['building'][curJson['id']] = nil
    gData['system']['building'][curJson['id']] = curJson
    return _getResult(gUser,'setBuilding',true,curJson)
end

function setWeapon(pData)
    if gUser ~= gData['owner'] then
        return 'fail 1'
    end
    local curJson = json.decode(pData)
    gData['system']['weapon'][curJson['id']] = nil
    gData['system']['weapon'][curJson['id']] = curJson
    return _getResult(gUser,'setWeapon',true,curJson)
end

function setArmor(pData)
    if gUser ~= gData['owner'] then
        return 'fail 1'
    end
    local curJson = json.decode(pData)
    gData['system']['armor'][curJson['id']] = nil
    gData['system']['armor'][curJson['id']] = curJson
    return _getResult(gUser,'setArmor',true,curJson)
end

function setPotion(pData)
    if gUser ~= gData['owner'] then
        return 'fail 1'
    end
    local curJson = json.decode(pData)
    gData['system']['potion'][curJson['id']] = nil
    gData['system']['potion'][curJson['id']] = curJson
    return _getResult(gUser,'setPotion',true,curJson)
end

function login()
    if gData[gUser] == nil then
        return 'fail 1'
    end
    --if gData[gUser]['online'] == 'Y' then
    --    return 'fail 1'
    --end
    gData[gUser]['online'] = 'Y'
    return _getBroadResult(gUser,'login',true,gData[gUser])
end

function logout()
    if gData[gUser] == nil then
        return 'fail 1'
    end
    if gData[gUser]['online'] == 'N' then
        return 'fail 2'
    end
    gData[gUser]['online'] = 'N'
    return _getResult(gUser,'logout',true,gData[gUser])
end

function forceLogout(pData)
    if gUser ~= gData['owner'] then
        return 'fail 1'
    end
    gData[gUser]['online'] = 'N'
    return _getBroadResult(gUser,'forceLogout',true,gData[gUser])
end

function leave()
    if gData[gUser] == nil then
        return 'fail 1'
    end
    if gData[gUser]['online'] == 'N' then
        return 'fail 2'
    end
    local curTid = gData[gUser]['stat']
    local ox = gData['system']['city'][curTid]['outx']
    local oy = gData['system']['city'][curTid]['outy']
    gData[gUser]['x'] = ox
    gData[gUser]['y'] = oy
    gData[gUser]['xt'] = ox
    gData[gUser]['yt'] = oy
    gData[gUser]['stat'] = 'wait'
    gData['system']['scene'][gData[gUser]['sid']]['player'][gUser] = nil
    gData['system']['scene'][gData[gUser]['sid']]['player'][gUser] = gData[gUser]
    return _getBroadResult(gUser,'leave',true,gData[gUser])
end

function _collision(obj0,obj1,obj2)
    local obj1Left = obj0['w']-(obj0['w']-obj1['x']);
    local obj1Right = obj0['w']-(obj0['w']-obj1['x'])+obj1['wb'];
    local obj1Top = obj0['h']-(obj0['h']-obj1['y']);
    local obj1Bottom = obj0['h']-(obj0['h']-obj1['y'])+obj1['hb'];

    local obj2Left = obj0['w']-(obj0['w']-obj2['x']);
    local obj2Right = obj0['w']-(obj0['w']-obj2['x'])+obj2['wb'];
    local obj2Top = obj0['h']-(obj0['h']-obj2['y']);
    local obj2Bottom = obj0['h']-(obj0['h']-obj2['y'])+obj2['hb'];

    if obj1Right < obj2Left or obj1Left > obj2Right or obj1Bottom < obj2Top or obj1Top > obj2Bottom then
        return false;
    else
        return true;
    end
end

function enter(pData)
    if gData[gUser] == nil then
        return 'fail 0'
    end
    local check = {'tid'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail 1'
    end
    if gData[gUser]['online'] == 'N' then
        return 'fail 2'
    end
    if gData[gUser]['stat'] == 'fight' then
        return 'fail 3'
    end
    local curSid = gData[gUser]['sid']
    local curTid = curJson['tid']

    local obj1 = {}
    obj1['x'] = gData[gUser]['x']
    obj1['y'] = gData[gUser]['y']
    obj1['wb'] = gData[gUser]['roles'][gData[gUser]['rid0']]['unit']['wb']
    obj1['hb'] = gData[gUser]['roles'][gData[gUser]['rid0']]['unit']['hb']

    local obj2= {}
    obj2['x'] = gData['system']['city'][curTid]['x']
    obj2['y'] = gData['system']['city'][curTid]['y']
    obj2['wb'] = gData['system']['city'][curTid]['unit']['wb']
    obj2['hb'] = gData['system']['city'][curTid]['unit']['hb']

    local curResult = _collision(gData['system']['scene'][curSid],obj1,obj2)
    if curResult == false then
        return 'fail 4'
    end
    gData[gUser]['stat'] = curTid
    gData[gUser]['x'] = 0
    gData[gUser]['y'] = 0
    gData[gUser]['xt'] = 0
    gData[gUser]['yt'] = 0
    return _getBroadResult(gUser,'enter',true,gData[gUser])
end

function move(pData)
    if gData[gUser] == nil then
        return 'fail 0'
    end
    local check = {'x','y','xt','yt'}
    local curJson = json.decode(pData)
    if _check(check,curJson) == false then
        return 'fail 1'
    end
    if gData[gUser]['online'] == 'N' then
        return 'fail 2'
    end
    local curStat = gData[gUser]['stat']
    if curStat == 'fight' then
        return 'fail 3'
    end
    if gData['system']['city'][curStat] ~= nil then
        return 'fail 4'
    end
    gData[gUser]['x'] = curJson['x']
    gData[gUser]['y'] = curJson['y']
    gData[gUser]['xt'] = curJson['xt']
    gData[gUser]['yt'] = curJson['yt']
    gData['system']['scene'][gData[gUser]['sid']]['player'][gUser] = nil
    gData['system']['scene'][gData[gUser]['sid']]['player'][gUser] = gData[gUser]
    return _getBroadResult(gUser,'move',false,gData[gUser])
end

function reset()
    if gData['owner'] ~= gUser then
        return 'fail 0'
    end
    local ret
    local cur = {}

    cur = {id='null',name='null',tid='null'}
    ret = addCountry(json.encode(cur))
    print(json.encode(cur))
    --print(getDump())

    cur = {id='ming',name='ming chao',tid='city0'}
    ret = addCountry(json.encode(cur))
    print(json.encode(cur))
    --print(getDump())

    cur = {id='huadong',name='huadong',cid='ming',cx='0',cy='0',w='2000',h='2000',image='scene/huadong.png'}
    ret = addScene(json.encode(cur))
    print(json.encode(cur))
    --print(getDump())
    --role main
    cur = {id='r0',cid='ming',name='wang',type='man',image='role/wang',w='50',h='100',wb='50',hb='20'}
    ret = addUnit(json.encode(cur))
    print(json.encode(cur))
    --print(getDump())
    --role soldier
    cur = {id='s0',cid='ming',name='dadao',type='soldier',image='role/dadao',w='50',h='100',wb='50',hb='20'}
    ret = addUnit(json.encode(cur))
    print(json.encode(cur))
    --print(getDump())
    --role monster
    cur = {id='m0',cid='ming',name='snake',type='monster',image='role/snake',w='20',h='60',wb='20',hb='10'}
    ret = addUnit(json.encode(cur))
    print(json.encode(cur))
    --print(getDump())
    --city
    cur = {id='c0',cid='null',name='shanghai',type='city',image='city/shanghai',w='200',h='200',wb='200',hb='100'}
    ret = addUnit(json.encode(cur))
    print(json.encode(cur))
    --print(getDump())
    --building
    cur = {id='b0',cid='null',name='room',type='building',image='building/room',w='200',h='150',wb='null',hb='null'}
    ret = addUnit(json.encode(cur))
    print(json.encode(cur))
    --print(getDump())
    --weapon
    cur = {id='w0',cid='null',name='dao',type='weapon',image='weapon/dao',w='null',h='null',wb='null',hb='null'}
    ret = addUnit(json.encode(cur))
    print(json.encode(cur))
    --print(getDump())
    --armor
    cur = {id='a0',cid='null',name='yifu',type='armor',image='armor/yifu',w='null',h='null',wb='null',hb='null'}
    ret = addUnit(json.encode(cur))
    print(json.encode(cur))
    --print(getDump())
    --potion
    cur = {id='p0',cid='null',name='hong',type='potion',image='potion/hong',w='null',h='null',wb='null',hb='null'}
    ret = addUnit(json.encode(cur))
    print(json.encode(cur))
    --print(getDump())

    --main role
    cur = {id='main0',uid='r0',head='role/headwang',st='5',hp='5',wt='5',exp='0',expm='10',lv='1',spd='300',able='15',power='0',price='0'}
    ret = addRole(json.encode(cur))
    print(json.encode(cur))
    --print(getDump())
    --soldier
    cur = {id='soldier0',uid='s0',head='role/headdadao',st='15',hp='10',wt='5',exp='0',expm='10',lv='1',spd='300',able='0',power='0',price='100'}
    ret = addRole(json.encode(cur))
    print(json.encode(cur))
    --print(getDump())
    --monster
    cur = {id='monster0',uid='m0',head='role/headsnake',st='5',hp='10',wt='5',exp='0',expm='10',lv='1',spd='300',able='0',power='0',price='100'}
    ret = addRole(json.encode(cur))
    print(json.encode(cur))
    --print(getDump())

    cur = {id='city0',uid='c0',sid='huadong',x='200',y='200',outx='150',outy='200',pp='10000',inside='inside/city0'}
    ret = addCity(json.encode(cur))
    print(json.encode(cur))
    --print(getDump())

    --cur = {id='player0 address',sid='huadong',rid0='main0',rid1='',name='haha',power='0',limit='3',finance='1000',x='0',y='0',xt='0',yt='0',movetime='0',stat='city0',online='N'}
    --ret = _addPlayer(json.encode(cur))
    --print(json.encode(cur))
    --print(getDump())

    cur = {id='building0',uid='b0',tid='city0',x='100',y='200'}
    ret = addBuilding(json.encode(cur))
    print(json.encode(cur))
    --print(getDump())

    cur = {id='building1',uid='b0',tid='city0',x='200',y='300'}
    ret = addBuilding(json.encode(cur))
    print(json.encode(cur))
    --print(getDump())

    cur = {id='building2',uid='b0',tid='city0',x='300',y='400'}
    ret = addBuilding(json.encode(cur))
    print(json.encode(cur))
    --print(getDump())

    cur = {id='weapon0',uid='w0',bid='building0',at='5',rg='1',wt='5',bk='10',sk='2'}
    ret = addWeapon(json.encode(cur))
    print(json.encode(cur))
    --print(getDump())

    cur = {id='armor0',uid='a0',bid='building1',hp='10',wt='5',bk='10',sk='2'}
    ret = addArmor(json.encode(cur))
    print(json.encode(cur))
    --print(getDump())

    cur = {id='potion0',uid='p0',bid='building2',hp='10',wt='1',bk='2',sk='0'}
    ret = addPotion(json.encode(cur))
    print(json.encode(cur))
    return _getBroadResult(gUser,'reset',true,'ok')
end

_setUser('5d531b93d1f8874527262c9376b31dd461eaa6aa')
init()
local ret
local cur = {}

cur = {id='null',name='null',tid='null'}
ret = addCountry(json.encode(cur))
print(json.encode(cur))
--print(getDump())

cur = {id='ming',name='ming chao',tid='city0'}
ret = addCountry(json.encode(cur))
print(json.encode(cur))
--print(getDump())

cur = {id='huadong',name='huadong',cid='ming',cx='0',cy='0',w='2000',h='2000',image='scene/huadong.png'}
ret = addScene(json.encode(cur))
print(json.encode(cur))
--print(getDump())
--role main
cur = {id='r0',cid='ming',name='wang',type='man',image='role/wang',w='50',h='100',wb='50',hb='20'}
ret = addUnit(json.encode(cur))
print(json.encode(cur))
--print(getDump())
--role soldier
cur = {id='s0',cid='ming',name='dadao',type='soldier',image='role/dadao',w='50',h='100',wb='50',hb='20'}
ret = addUnit(json.encode(cur))
print(json.encode(cur))
--print(getDump())
--role monster
cur = {id='m0',cid='ming',name='snake',type='monster',image='role/snake',w='20',h='60',wb='20',hb='10'}
ret = addUnit(json.encode(cur))
print(json.encode(cur))
--print(getDump())
--city
cur = {id='c0',cid='null',name='shanghai',type='city',image='city/shanghai',w='200',h='200',wb='200',hb='100'}
ret = addUnit(json.encode(cur))
print(json.encode(cur))
--print(getDump())
--building
cur = {id='b0',cid='null',name='room',type='building',image='building/room',w='200',h='150',wb='null',hb='null'}
ret = addUnit(json.encode(cur))
print(json.encode(cur))
--print(getDump())
--weapon
cur = {id='w0',cid='null',name='dao',type='weapon',image='weapon/dao',w='null',h='null',wb='null',hb='null'}
ret = addUnit(json.encode(cur))
print(json.encode(cur))
--print(getDump())
--armor
cur = {id='a0',cid='null',name='yifu',type='armor',image='armor/yifu',w='null',h='null',wb='null',hb='null'}
ret = addUnit(json.encode(cur))
print(json.encode(cur))
--print(getDump())
--potion
cur = {id='p0',cid='null',name='hong',type='potion',image='potion/hong',w='null',h='null',wb='null',hb='null'}
ret = addUnit(json.encode(cur))
print(json.encode(cur))
--print(getDump())

--main role
cur = {id='main0',uid='r0',head='role/headwang',st='5',hp='5',wt='5',exp='0',expm='10',lv='1',spd='300',able='15',power='0',price='0'}
ret = addRole(json.encode(cur))
print(json.encode(cur))
--print(getDump())
--soldier
cur = {id='soldier0',uid='s0',head='role/headdadao',st='15',hp='10',wt='5',exp='0',expm='10',lv='1',spd='300',able='0',power='0',price='100'}
ret = addRole(json.encode(cur))
print(json.encode(cur))
--print(getDump())
--monster
cur = {id='monster0',uid='m0',head='role/headsnake',st='5',hp='10',wt='5',exp='0',expm='10',lv='1',spd='300',able='0',power='0',price='100'}
ret = addRole(json.encode(cur))
print(json.encode(cur))
--print(getDump())

cur = {id='city0',uid='c0',sid='huadong',x='200',y='200',outx='150',outy='200',pp='10000',inside='inside/city0'}
ret = addCity(json.encode(cur))
print(json.encode(cur))
--print(getDump())

--cur = {id='player0 address',sid='huadong',rid0='main0',rid1='',name='haha',power='0',limit='3',finance='1000',x='0',y='0',xt='0',yt='0',movetime='0',stat='city0',online='N'}
--ret = _addPlayer(json.encode(cur))
--print(json.encode(cur))
--print(getDump())

cur = {id='building0',uid='b0',tid='city0',x='100',y='200'}
ret = addBuilding(json.encode(cur))
print(json.encode(cur))
--print(getDump())

cur = {id='building1',uid='b0',tid='city0',x='200',y='300'}
ret = addBuilding(json.encode(cur))
print(json.encode(cur))
--print(getDump())

cur = {id='building2',uid='b0',tid='city0',x='300',y='400'}
ret = addBuilding(json.encode(cur))
print(json.encode(cur))
--print(getDump())

cur = {id='weapon0',uid='w0',bid='building0',at='5',rg='1',wt='5',bk='10',sk='2'}
ret = addWeapon(json.encode(cur))
print(json.encode(cur))
--print(getDump())

cur = {id='armor0',uid='a0',bid='building1',hp='10',wt='5',bk='10',sk='2'}
ret = addArmor(json.encode(cur))
print(json.encode(cur))
--print(getDump())

cur = {id='potion0',uid='p0',bid='building2',hp='10',wt='1',bk='2',sk='0'}
ret = addPotion(json.encode(cur))
print(json.encode(cur))
--print(getDump())

cur = {rid='main0',name='55'}
ret = createPlayer(json.encode(cur))
print("createPlayer")
print(ret)
print(json.encode(cur))

cur = {}
ret = login()
print(json.encode(cur))

cur = {}
ret = leave()
print(json.encode(cur))
print(json.encode(ret))

cur = {tid='city0'}
ret = enter(json.encode(cur))
print(json.encode(cur))

cur = {}
ret = leave()
print(json.encode(cur))

cur = {tid='city0'}
ret = enter(json.encode(cur))
print(json.encode(cur))

cur = {}
ret = leave()
print(json.encode(cur))

cur = {}
--ret = logout()
print(json.encode(cur))

cur = json.decode(getDump())
--print(json.encode(cur['data'][1]['msg']))
--print("end")
--ret = putDump(json.encode(cur['data'][1]['msg']))
--print(json.encode(ret))
--print("end1")
--print(getDump())

cur = {x='150',y='210',xt='200',yt='300'}
ret = move(json.encode(cur))
print(json.encode(ret))