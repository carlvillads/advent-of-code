lines = readlines("/Users/cv/projects/aoc/inputs/2015/day2.txt");
totalPaper = 0;
totalRibbon = 0;

for i = 1:length(lines)
    line = strtrim(lines(i));
    if strlength(line) == 0
        continue;
    end
    parts = split(line, 'x');
    d = str2double(parts);
    totalPaper = totalPaper + requiredWrappingPaper(d(1),d(2),d(3));
    totalRibbon = totalRibbon + requiredRibbon(d(1),d(2),d(3));
end
fprintf("The elves should order %d squre feet of wrapping paper\n", totalPaper)
fprintf("The elves should order %d feet of ribbon\n", totalRibbon)


function a = requiredWrappingPaper(l,w,h)
    sides = [l*w, w*h, h*l];
    surfaceArea = 2 * sum(sides);
    a = surfaceArea + min(sides);
end

function r = requiredRibbon(l,w,h)
    sides = sort([l,w,h]);
    wrap = sides(1)*2 + sides(2)*2;
    bow = l*w*h;
    r = wrap + bow;
end
