function guide_santa(directions::String)
    floor = 0

    for char in directions
        if char == '('
            floor += 1
        elseif char == ')'
            floor -= 1
        end
    end

    return floor
end

given_directions = read("/Users/cv/projects/aoc/inputs/2015/day1.txt", String)
last_floor = guide_santa(given_directions)
println("Santa will end on floor $(last_floor)")

# PART TWO
function find_basement(directions::String)
    floor = 0
    position = 0

    for char in directions
        position += 1

        if char == '('
            floor += 1
        elseif char == ')'
            floor -= 1
        end

        if floor == -1
            break
        end
    end

    return position
end

last_position = find_basement(given_directions)
println("Santa enters the basement from instruction no. $(last_position)")
