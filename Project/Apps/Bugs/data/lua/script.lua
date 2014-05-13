player_pos_x = {135}
player_pos_y = {150}
num_of_tree = {1,2,3}
spawn_rate_change_interval = {200,0,0}
trees_pos_x = {200,  0, 0, 0, 0}
trees_pos_y = {1730, 0, 0, 0, 0}
trees_pos_x_off = {170 , 0, 0, 0, 0}
trees_pos_y_off = {0, 0, 0, 0, 0}

function getSpawnRateInterval(level)
	return spawn_rate_change_interval[level]
end

function getNumOfTree(level)
	if level == 0 then
		return 0
	end
	return num_of_tree[level]
end

function getTreeX(index)
	return trees_pos_x[index]
end

function getTreeY(index)
	return trees_pos_y[index]
end

function getTreeXOff(index)
	return trees_pos_x_off[index]
end

function getTreeYOff(index)
	return trees_pos_y_off[index]
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
	if level == 0 then
		return 135
	end
	return player_pos_x[level]
end

function loadPlayerY(level)
	if level == 0 then
		return 150
	end
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
