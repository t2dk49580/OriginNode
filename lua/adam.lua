_G['os'] = nil
_G['io'] = nil
json = require 'json'

gUser    = nil
gOwner   = nil
gName    = 'ADAM DEMO'
gSymbol  = 'ADAM'
gIcon    = ''
gTotal   = 10000000
gData    = {}
gID      = 1

function _setUser(pUser)
    gUser = pUser
end

function init()
    if gOwner ~= nil then
        return 'fail'
    end
    gOwner = gUser
    return 'ok'
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
    return gSymbol
end

function getIntPart(x)
    if x <= 0 then
       return math.ceil(x);
    end
    
    if math.ceil(x) == x then
       x = math.ceil(x);
    else
       x = math.ceil(x) - 1;
    end
    return x;
end

function  addBaby(subname,pid)
    local i
    for i=1,#gData[subname],1 do
        if gData[subname][i]['id'] == tonumber(pid) then
            gData[subname][i]['babyNum'] = gData[subname][i]['babyNum']+1
            return 'ok'
        end
    end
    return 'fail'
end

function  addOpus(subname,pid)
    local i
    for i=1,#gData[subname],1 do
        if gData[subname][i]['id'] == tonumber(pid) then
            gData[subname][i]['opusNum'] = gData[subname][i]['opusNum']+1
            return 'ok'
        end
    end
    return 'fail'
end

function setStatus(subname,pid,value,name)
    local i
    for i=1,#gData[subname],1 do
        if gData[subname][i]['id'] == tonumber(pid) then
            gData[subname][i]['status']['value'] = value
            gData[subname][i]['status']['name']  = name
            return 'ok'
        end
    end
    return 'fail'
end

function setDetails(subname,pid,value)
    -- body
end

function addSubject(subname,name,mainPic,startDate,endDate)
    local curSubject = {}
    curSubject['id'] = gID
    curSubject['name'] = name
    curSubject['mainPic'] = mainPic
    curSubject['startDate'] = startDate
    curSubject['endDate'] = endDate
    curSubject['babyNum'] = 0
    curSubject['opusNum'] = 0
    curSubject['isParticipant'] = false
    curSubject['isClass'] = true
    curSubject['status'] = {}
    curSubject['status']['value'] = 'not set'
    curSubject['status']['name']  = 'not set'
    curSubject['timeCreated'] = 'not set'
    if gData[subname] == nil then
        gData[subname] = {}
    end
    table.insert( gData[subname], 1, curSubject )
    gID = gID + 1
    return 'ok'
end

function getPage(pageNumber,pageSize,subname,effect)
    local i
    local start = (tonumber(pageNumber)*tonumber(pageSize) - tonumber(pageSize))+1
    local result = {}
    result['page'] = {}
    result['page']['sort'] = {}
    result['page']['sort']['sorted'] = true
    result['page']['sort']['unsorted'] = false
    result['page']['pageSize'] = tonumber(pageSize)
    result['page']['pageNumber'] = tonumber(pageNumber)
    result['page']['offset'] = 0
    result['page']['paged'] = true
    result['page']['unpaged'] = false
    result['page']['effect'] = effect
    result['page']['totalElements'] = #gData[subname]
    local l,r = math.modf(#gData[subname]/tonumber(pageSize))
    if r > 0 then
        result['page']['totalPages'] = l+1
    else
        result['page']['totalPages'] = l
    end
    result['page']['data'] = {}
    for i=start,#gData[subname],1 do
        table.insert( result['page']['data'], gData[subname][i] )
    end
    return json.encode(result)
end


_setUser('0x1234')
addSubject('baby','baby test1','http1','time1','time2')
addSubject('baby','baby test2','http2','time1','time2')
addSubject('baby','baby test3','http3','time1','time2')
addSubject('baby','baby test4','http4','time1','time2')
addSubject('baby','baby test5','http5','time1','time2')
addSubject('baby','baby test6','http6','time1','time2')
addBaby('baby','1')
addBaby('baby','1')
addBaby('baby','1')
addBaby('baby','1')
print(getPage('1','5','baby','true'))