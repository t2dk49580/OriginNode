json = require 'json'

gUser = nil
gInfo = {}

function _addResult(pUser,pMethod,pResult,pMsg,pAll)
    local buffer = {}
    local result = pAll
    buffer['method'] = pMethod
    buffer['result'] = pResult
    buffer['msg']    = pMsg
    buffer['owner']  = pUser
    buffer['symbol'] = gInfo['symbol']
    table.insert(result,buffer)
    return result
end

function _getResult(pUser,pMethod,pResult,pMsg)
    local buffer = {}
    local result = _addResult(pUser,pMethod,pResult,pMsg,buffer)
    return json.encode(result)
end

function _setUser(pUser)
    gUser = pUser
end

function _getIndex(t,v)
    if t[1] < v then
        return 1
    end
    local left = 1
    local right = #t
    local mid = math.ceil((left + right)/2)
    if t[right] > v then
        return right+1
    end
    while right ~= mid do
        print(left,right,mid)
        if t[mid] == v then
            break;
        elseif t[mid] > v then
            left = mid + 1
        else 
            right = mid - 1
        end

        mid = math.ceil((left + right)/2)
    end
    print(left,right,mid)
    return mid,t[mid]
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

function _init()
    gInfo['ct']       = {}
    gInfo['name']     = 'origin node network'
    gInfo['symbol']   = '0'
    gInfo['owner']    = gUser
    gInfo['maker']    = gUser
    gInfo['total']    = 1000000000
    gInfo['fee']      = 0.01
    gInfo['top']      = 0
    gInfo['dumper']   = {}
    gInfo['dumper'][gUser]  = true
    gInfo['balance']  = {}
    gInfo['balance'][gUser] = 1000000000
    gInfo['peers']          = {}
    gInfo['miss']           = {}
    gInfo[gUser]            = {}
    gInfo[gUser][gInfo['symbol']]            = true
    gInfo['ct'][gInfo['symbol']]             = {}
    gInfo['ct'][gInfo['symbol']]['name']     = 'origin node network'
    gInfo['ct'][gInfo['symbol']]['symbol']   = gInfo['symbol']
    gInfo['ct'][gInfo['symbol']]['owner']    = gUser
    gInfo['ct'][gInfo['symbol']]['maker']    = gUser
    gInfo['ct'][gInfo['symbol']]['total']    = 1000000000
    gInfo['ct'][gInfo['symbol']]['fee']      = 0.01
    gInfo['ct'][gInfo['symbol']]['top']      = 0
    return _getResult(gUser,'init',true,'origin node network started')
end

function getContract(pContract)
    return _getResult(gUser,'getContract',true,gInfo['ct'][pContract])
end

function getBalance(pUser)
    return _getResult(gUser,'getBalance',true,gInfo['balance'][pUser])
end

function _addBlockTop()
    gInfo['top'] = gInfo['top']+1
    gInfo['ct'][gInfo['symbol']]['top'] = gInfo['top']
    return 'ok'
end

function transfer(pTo,pAmount)
    local curAmount = tonumber(pAmount)
    if curAmount > gInfo['balance'][gUser]+gInfo['fee'] then
        return 'fail'
    end
    if gInfo['balance'][pTo] == nil then
        gInfo['balance'][pTo] = 0
    end
    local curResult = {}
    gInfo['balance'][gUser] = gInfo['balance'][gUser] - (curAmount+gInfo['fee'])
    gInfo['balance'][pTo]   = gInfo['balance'][pTo]   + curAmount
    gInfo['balance'][gInfo['maker']] = gInfo['balance'][gInfo['maker']]+gInfo['fee']
    _addResult(gUser,'getBalance',true,gInfo['balance'][gUser],curResult)
    _addResult(pTo,'getBalance',true,gInfo['balance'][pTo],curResult)
    _addBlockTop()
    return json.encode(curResult)
end

function setMaker(pContract,pUser)
    if gInfo['ct'][pContract]['owner'] ~= gUser then
        return 'fail'
    end
    local curResult = transfer(pUser,'1')
    if curResult == 'fail' then
        return 'fail'
    end
    if gInfo[pUser] == nil then
        gInfo[pUser] = {}
    end
    gInfo['miss'][pContract] = nil
    gInfo[pUser][pContract] = true
    gInfo['ct'][pContract]['maker'] = pUser
    _addBlockTop()
    return _getResult(gUser,'setMaker',true,pContract..':'..pUser)
end

function destroy(pContract)
    if #pContract <= 3 then
        return 'fail'
    end
    if gUser ~= gInfo['ct'][pContract]['owner'] then
        return 'fail'
    end
    _removeMaker(pContract)
    gInfo['ct'][pContract] = nil
    _addBlockTop()
    return _getResult(gUser,'destroy',true,pContract)
end

function _removeMaker(pContract)
    if gInfo['ct'][pContract] == nil then
        return 'fail'
    end
    gInfo['miss'][pContract] = true
    local curMaker = gInfo['ct'][pContract]['maker']
    gInfo['ct'][pContract]['maker'] = nil
    if gInfo[curMaker] == nil then
        return 'ok'
    end
    gInfo[curMaker][pContract] = nil
    return 'ok'
end
--
function _deploy(pContract,pName,pMaker,pSize)
    if gInfo['ct'][pContract] ~= nil then
        return 'fail'
    end
    if #pContract >= 10 or #pName >= 256 then
        return 'fail'
    end
    if #pContract <= 3 and gUser ~= gInfo['owner'] then
        return 'fail'
    end
    local curResult = transfer(gInfo['owner'],pSize)
    if curResult == 'fail' then
        return 'fail'
    end
    if gInfo[pMaker] == nil then
        gInfo[pMaker] = {}
    end
    gInfo[pMaker][pContract] = true
    gInfo['ct'][pContract] = {}
    gInfo['ct'][pContract]['name']   = pName
    gInfo['ct'][pContract]['symbol'] = pContract
    gInfo['ct'][pContract]['owner']  = gUser
    gInfo['ct'][pContract]['maker']  = pMaker
    _addBlockTop()
    return 'ok'
end

function _addPeer(pUser,pTime)
    if gUser ~= gInfo['maker'] then
        return 'fail'
    end
    gInfo['peers'][pUser] = pTime
    _addBlockTop()
    return 'ok'
end

function _delPeer(pUser)
    if gUser ~= gInfo['maker'] then
        return 'fail'
    end
    gInfo['peers'][pUser] = nil
    if gInfo[pUser] == nil then
        _addBlockTop()
        return '[]'
    end
    local k,v
    local curList = {}
    for k,v in pairs(gInfo[pUser]) do
        print(k,v)
        table.insert( curList, k )
    end
    local curIndex = 1
    for curIndex=1,#curList,1 do
        _removeMaker(curList[curIndex])
    end
    gInfo[pUser] = nil
    _addBlockTop()
    return json.encode(curList)
end

--原生产者离线，全网发起选举后产生一个新生产者
function _changeMaker(pContract,pMaker)
    if #pContract <= 3 then
        return 'fail'
    end
    gInfo['ct'][pContract]['maker'] = pMaker
    gInfo[pMaker][pContract] = true
    _addBlockTop()
    return 'ok'
end

function addDumper(pUser)
    if gUser ~= gInfo['owner'] then
        return 'fail'
    end
    gInfo['dumper'][pUser] = true
    return _getResult(gUser,'addDumper',true,pUser)
end

function delDumper(pUser)
    if gUser ~= gInfo['owner'] then
        return 'fail'
    end
    gInfo['dumper'][pUser] = nil
    return _getResult(gUser,'delDumper',true,pUser)
end

function getDump()
    if gInfo['dumper'][gUser] == nil then
        return _getResult(gUser,'getDump',false,pContract)
    end
    return _getResult(gUser,'getDump',true,gInfo)
end

function setDump(pInfo)
    if gUser ~= gInfo['owner'] then
        return 'fail'
    end
    if gInfo['top'] > 0 then
        return 'fail'
    end
    gInfo = nil
    gInfo = _clone(json.decode(pInfo))
    return _getResult(gUser,'setDump',true,gInfo['symbol'])
end

_setUser('0xabcd')
print(_init())
print(_addPeer('0xabcd','20181028'))
print(_deploy('hash','kv contract','0xabcd','999'))
print(getDump())
print(_addPeer('user0','20181029'))
print(transfer('0x1111','100'))
_setUser('0x1111')
print(transfer('0x2222','10'))
_setUser('0xabcd')
print(_delPeer('0xabcd'))
print(getDump())
print(setMaker('0','user0'))
print(getDump())
print(destroy('hash'))
print(getDump())
--local array = {45,40,35,19,13,9,5,2}
--local curIndex = getIndex(array,2)
--print(curIndex)
--table.insert( array, curIndex, 2 )
--print(json.encode(array))