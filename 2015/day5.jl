vowels = "aeiou"
disallowed = ["ab", "cd", "pq", "xy"]

function is_nice(str::String)::Bool
    vowelcount = 0
    doubleletter = false

    for (i, char) in enumerate(str)

        if char ∈ vowels
            vowelcount += 1
        end

        if i == length(str)
            continue
        end

        if char == str[i+1]
            doubleletter = true
        end

        if str[i:i+1] ∈ disallowed
            return false
        end
    end

    return vowelcount >= 3 && doubleletter
end


function repeatspresent(str::String)::Bool
    for i in 1:length(str) - 2
        pair = str[i:i+1]
        if occursin(pair, str[i+2:end])
            return true
        end
    end
    return false
end


function new_is_nice(str::String)::Bool
    doubleletter = false
    repeats = repeatspresent(str)

    for i in 1:length(str) - 2
        if str[i] == str[i+2]
            doubleletter = true
            break
        end
    end

    return repeats && doubleletter
end

function main()
    nicestrings = 0
    for line in eachline("2015/inputs/day5.txt")
        if is_nice(line)
            nicestrings += 1
        end
    end
    println("There are $(nicestrings) nice strings")

    new_nicestrings = 0
    for line in eachline("2015/inputs/day5.txt")
        if new_is_nice(line)
            new_nicestrings += 1
        end
    end
    println("There are $(new_nicestrings) nice strings with the new rules")
end

main()