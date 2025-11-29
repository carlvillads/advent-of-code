lines = readlines("2015/inputs/day7.txt")
instructions = Dict{String, Any}()
wires = Dict{String, UInt16}()

for line in lines
    source, destination = split(line, " -> ")
    if occursin(" AND ", source)
        a,b = split(source, " AND ")
        instructions[destination] = ("AND", a, b)
    elseif occursin(" OR ", source)
        a,b = split(source, " OR ")
        instructions[destination] = ("OR", a, b)
    elseif occursin(" LSHIFT ", source)
        a,n = split(source, " LSHIFT ")
        instructions[destination] = ("LSHIFT", a, parse(Int, n))
    elseif occursin(" RSHIFT ", source)
        a,n = split(source, " RSHIFT ")
        instructions[destination] = ("RSHIFT", a, parse(Int, n))
    elseif occursin("NOT ", source) # Fixed: swapped arguments
        x = split(source)[2]
        instructions[destination] = ("NOT", x)
    else
        instructions[destination] = ("ASSIGN", source)
    end
end


isnum(s) = all(isdigit, s)

function getvalue(token, instructions, wires)
    if isnum(token)
        return UInt16(parse(Int,  token))
    end
    
    if haskey(wires, token)
        return wires[token]
    end

    wirerule = instructions[token]
    operator = wirerule[1]

    result = nothing

    if operator == "ASSIGN"
        source = wirerule[2]
        result = getvalue(source, instructions, wires)
    elseif operator == "AND"
        a, b = wirerule[2], wirerule[3]
        result = getvalue(a, instructions, wires) & getvalue(b, instructions, wires)
    elseif operator == "OR"
        a, b = wirerule[2], wirerule[3]
        result = getvalue(a, instructions, wires) | getvalue(b, instructions, wires)
    elseif operator == "LSHIFT"
        a, n = wirerule[2], wirerule[3]
        result = (getvalue(a, instructions, wires) << n) & 0xFFFF
    elseif operator == "RSHIFT"
        a, n = wirerule[2], wirerule[3]
        result = (getvalue(a, instructions, wires) >> n) & 0xFFFF
    elseif operator == "NOT"
        a = wirerule[2]
        result = (~getvalue(a, instructions, wires)) & 0xFFFF
    end

    wires[token] = UInt16(result)
    return wires[token]
end

result_a = getvalue("a", instructions, wires)
println("Signal// filepath: /Users/cv/projects/aoc/2015/day7.jl")
lines = readlines("2015/inputs/day7.txt")
instructions = Dict{String, Any}()
wires = Dict{String, UInt16}()

for line in lines
    source, destination = split(line, " -> ")
    if occursin(" AND ", source)
        a,b = split(source, " AND ")
        instructions[destination] = ("AND", a, b)
    elseif occursin(" OR ", source)
        a,b = split(source, " OR ")
        instructions[destination] = ("OR", a, b)
    elseif occursin(" LSHIFT ", source)
        a,n = split(source, " LSHIFT ")
        instructions[destination] = ("LSHIFT", a, parse(Int, n))
    elseif occursin(" RSHIFT ", source)
        a,n = split(source, " RSHIFT ")
        instructions[destination] = ("RSHIFT", a, parse(Int, n))
    elseif occursin("NOT ", source)
        x = split(source)[2]
        instructions[destination] = ("NOT", x)
    else
        instructions[destination] = ("ASSIGN", source)
    end
end


isnum(s) = all(isdigit, s)

function getvalue(token, instructions, wires)
    if isnum(token)
        return UInt16(parse(Int,  token))
    end
    
    if haskey(wires, token)
        return wires[token]
    end

    wirerule = instructions[token]
    operator = wirerule[1]

    result = nothing

    if operator == "ASSIGN"
        source = wirerule[2]
        result = getvalue(source, instructions, wires)
    elseif operator == "AND"
        a, b = wirerule[2], wirerule[3]
        result = getvalue(a, instructions, wires) & getvalue(b, instructions, wires)
    elseif operator == "OR"
        a, b = wirerule[2], wirerule[3]
        result = getvalue(a, instructions, wires) | getvalue(b, instructions, wires)
    elseif operator == "LSHIFT"
        a, n = wirerule[2], wirerule[3]
        result = (getvalue(a, instructions, wires) << n) & 0xFFFF
    elseif operator == "RSHIFT"
        a, n = wirerule[2], wirerule[3]
        result = (getvalue(a, instructions, wires) >> n) & 0xFFFF
    elseif operator == "NOT"
        a = wirerule[2]
        result = (~getvalue(a, instructions, wires)) & 0xFFFF
    end

    wires[token] = UInt16(result)
    return wires[token]
end

# Part 1
result_a = getvalue("a", instructions, wires)
println("Signal on wire a: $result_a")

# part 2
empty!(wires)
wires["b"] = result_a
new_result_a = getvalue("a", instructions, wires)
println("New signal on wire a: $new_result_a")