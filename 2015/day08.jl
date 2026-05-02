input_data = readlines("inputs/day8.txt")

total_diff_part1 = sum(length(line) - length(eval(Meta.parse(line))) for line in input_data)
println("Part 1 diff: $total_diff_part1")

total_diff_part2 = 0

for line in input_data
    extra_chars = 2 + count(c -> c == '"' || c == '\\', line)
    global total_diff_part2 += extra_chars
end

println("Part 2 diff: $total_diff_part2")
