givenInstruction = fileread("inputs/2015/day1.txt");
GuideSanta(givenInstruction)
FindBasement(givenInstruction)


function floor = GuideSanta(directions)
    floor = 0;
    
    for i = 1:length(directions)
        char = directions(i);

        if char == '('
            floor = floor + 1;
        elseif char == ')'
            floor = floor - 1;
        end
    end
end

% Part 2

function position = FindBasement(directions)
    floor = 0;

    for i = 1:length(directions)
        char = directions(i);

        if char == '('
            floor = floor + 1;
        elseif char == ')'
            floor = floor - 1;
        end

        if floor == -1
            position = i;
            break;
        end
    end
end
