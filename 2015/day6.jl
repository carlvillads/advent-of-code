function parsecoordinates(instruction::String)
    numbers = parse.(Int, match(r"(\d+),(\d+) through (\d+),(\d+)", instruction).captures)
    x1, y1, x2, y2 = numbers .+ 1  # broadcast +1 across elements to account for 0 indexing
    return x1:x2, y1:y2
end

function lighttoggle!(instruction::String, lights::BitMatrix)
    rows, cols = parsecoordinates(instruction)
    lights[rows, cols] .= .!lights[rows, cols]  # Broadcasts the not operator (!) across the selected rows and cols
end

function lightoff!(instruction::String, lights::BitMatrix)
    rows, cols = parsecoordinates(instruction)
    lights[rows, cols] .= false
end

function lighton!(instruction::String, lights::BitMatrix)
    rows, cols = parsecoordinates(instruction)
    lights[rows, cols] .= true
end

# part 2

function lightbrighten!(instruction::String, brightlights::Matrix)
    rows, cols = parsecoordinates(instruction)
    brightlights[rows, cols] .+= 2
end

function lightdim!(instruction::String, brightlights::Matrix)
    rows, cols = parsecoordinates(instruction)
    brightlights[rows, cols] .= max.(brightlights[rows, cols] .- 1, 0)
end

function lightincrease!(instruction::String, brightlights::Matrix)
    rows, cols = parsecoordinates(instruction)
    brightlights[rows, cols] .+= 1
end


function main()
    lights = falses(1000, 1000)
    brightlights = zeros(Int, 1000, 1000)

    for line in readlines("2015/inputs/day6.txt")
        if startswith(line, "toggle")
            lighttoggle!(line, lights)
            lightbrighten!(line, brightlights)
        elseif startswith(line, "turn on")
            lighton!(line, lights)
            lightincrease!(line, brightlights)
        elseif startswith(line, "turn off")
            lightoff!(line, lights)
            lightdim!(line, brightlights)
        end
    end

    litlights = count(lights)
    println("There are $(litlights) lights lit")

    totalbrightness = sum(brightlights)
    println("The total brightness is $(totalbrightness)")
end

main()