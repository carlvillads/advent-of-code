function required_wrapping_paper(l, w, h)
    sides = [l*w, w*h, h*l]
    surface_area = 2 * sum(sides)
    return surface_area + minimum(sides)
end

function required_ribbon(l, w, h)
    sides = sort([l,w,h])
    wrap = sides[1]*2 + sides[2]*2
    bow = l*w*h
    return wrap + bow
end

function main()
    total_rwp = 0
    total_ribbon = 0
    for line in eachline("/Users/cv/projects/aoc/inputs/2015/day2.txt")
        package_dimensions = parse.(Int, split(line, 'x'))
        l, w, h = package_dimensions
        total_rwp += required_wrapping_paper(l, w, h)
        total_ribbon += required_ribbon(l,w,h)
    end

    println("The elves should order $(total_rwp) square feet of wrapping paper")
    println("The elves require $(total_ribbon) feet of ribbon")
end

main()