player_pos_x = {135}
player_pos_y = {150}

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

function loadPlayerX(level)
	return player_pos_x[level]
end

function loadPlayerY(level)
	return player_pos_y[level]
end

function healthDec()
	health = health - 1
	if health <= 0 then
		health = 60
		return 1
	end
	return 0
end
