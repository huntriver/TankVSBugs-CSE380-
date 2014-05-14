player_pos_x = {135,135,1955}
player_pos_y = {150,150,1772}
num_of_tree = {1,0,2}
tree_init_spawn_rate = {300, 0, 600}
tree_spawn_rate_diff = {100, 0, 200}
spawn_rate_change_interval = {200,0,1000}
trees_pos_x = {200,  0, 0, 0, 0, 0, 0, 0, 0, 0, 190, 775, 2960,2300}
trees_pos_y = {1730, 0, 0, 0, 0, 0, 0, 0, 0, 0, 192, 3650, 770,3393}
trees_pos_x_off = {170 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 170,0, 0,170}
trees_pos_y_off = {   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-170, -170,0}

function getInitSpawnRate(level)
	return tree_init_spawn_rate[level]
end

function getInitSpawnRateDiff(level)
	return tree_spawn_rate_diff[level]
end
	
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
