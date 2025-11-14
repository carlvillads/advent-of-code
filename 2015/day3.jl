function deliver_presents(directions::String)
    presents_delivered = 1
    visited_houses = []
    starting_coordinates = [0,0]

    push!(visited_houses, copy(starting_coordinates))
    current_coordinates = copy(starting_coordinates)
    for step in directions
        if step == '^'
            current_coordinates[1] += 1
        elseif step == 'v'
            current_coordinates[1] -= 1
        elseif step == '<'
            current_coordinates[2] -= 1
        elseif step == '>'
            current_coordinates[2] += 1
        end

        presents_delivered += 1

        if !(current_coordinates in visited_houses)
            push!(visited_houses, copy(current_coordinates))
        end
    end

    return length(visited_houses)
end

function deliver_with_robosanta(directions::String)
    presents_delivered = 1
    visited_houses = []
    starting_coordinates = [0,0]
    push!(visited_houses, copy(starting_coordinates))

    coordinates_santa = copy(starting_coordinates)
    coordinates_robosanta = copy(starting_coordinates)

    for (i, step) in enumerate(directions)
        if i % 2 == 1  # santa
            if step == '^'
                coordinates_santa[1] += 1
            elseif step == 'v'
                coordinates_santa[1] -= 1
            elseif step == '<'
                coordinates_santa[2] -= 1
            elseif step == '>'
                coordinates_santa[2] += 1
            end

            if !(coordinates_santa in visited_houses)
                push!(visited_houses, copy(coordinates_santa))
            end
        else  # robosanta
            if step == '^'
                coordinates_robosanta[1] += 1
            elseif step == 'v'
                coordinates_robosanta[1] -= 1
            elseif step == '<'
                coordinates_robosanta[2] -= 1
            elseif step == '>'
                coordinates_robosanta[2] += 1
            end

            if !(coordinates_robosanta in visited_houses)
                push!(visited_houses, copy(coordinates_robosanta))
            end
        end

        presents_delivered += 1
    end

    return length(visited_houses)
end

function main()
    given_directions = read("2015/inputs/day3.txt", String)
    no_of_houses_visited = deliver_presents(given_directions)
    println("$(no_of_houses_visited) houses recieved at least one package")
    with_robosanta = deliver_with_robosanta(given_directions)
    println("$(with_robosanta) houses recieved at least one package when delivering with robosanta")
end

main()