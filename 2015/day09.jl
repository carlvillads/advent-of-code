using Combinatorics

function find_shortest_route(input_data::String)
    distances = Dict{Tuple{String,String},Int}()
    places = Set{String}()

    # parse input
    for line in split(strip(input_data), "\n")
        parts = split(line)
        city1, city2 = parts[1], parts[3]
        dist = parse(Int, parts[5])
        distances[(city1, city2)] = dist
        distances[(city2, city1)] = dist

        push!(places, city1, city2)
    end

    shortest_dist = typemax(Int)
    for route in permutations(collect(places))
        current_dist = 0
        for i in 1:(length(route)-1)
            current_dist += distances[(route[i], route[i+1])]
        end
        shortest_dist = min(shortest_dist, current_dist)
    end

    return shortest_dist
end

function find_longest_route(input_data::String)
    distances = Dict{Tuple{String,String},Int}()
    places = Set{String}()

    for line in split(strip(input_data), "\n")
        parts = split(line)
        city1, city2 = parts[1], parts[3]
        dist = parse(Int, parts[5])

        distances[(city1, city2)] = dist
        distances[(city2, city1)] = dist
        push!(places, city1, city2)
    end

    longest_dist = 0
    for route in permutations(collect(places))
        current_dist = 0
        for i in 1:(length(route)-1)
            current_dist += distances[(route[i], route[i+1])]
        end
        longest_dist = max(longest_dist, current_dist)
    end

    return longest_dist
end

input_data = read("inputs/day9.txt", String)
answer = find_shortest_route(input_data)
println("The shortest route has a distance of ", answer)
answer2 = find_longest_route(input_data)
println("The longest route has a distance of ", answer2)