health = 60

function sq(val)
	return val * val
end

num = 0

function setNum(initNum)
	num = initNum
end

function foo()
	num = incAndReturn(num)
	num = incAndReturn(num)
	num = incAndReturn(num)
end

function healthDec()
	health = health - 1
	if health <= 0 then
		health = 60
		return 1
	end
	return 0
end
