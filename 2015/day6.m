function day6
    lights = false(1000, 1000);
    brightLights = zeros(1000, 1000);

    instructions = readlines("inputs/day6.txt");
    for i = 1:length(instructions)
        line = strtrim(instructions(i));

        if startsWith(line, "toggle")
            lights = lightToggle(line, lights);
            brightLights = lightBrighten(line, brightLights);
        elseif startsWith(line, "turn on")
            lights = lightOn(line, lights);
            brightLights = lightIncrease(line, brightLights);
        elseif startsWith(line, "turn off")
            lights = lightOff(line, lights);
            brightLights = lightDim(line, brightLights);
        end
    end

    litLights = sum(lights, "all");
    fprintf("There are %d lights lit\n", litLights);

    totalBrightness = sum(brightLights, "all");
    fprintf("The total brightness is %d\n", totalBrightness);
end


function [rows, cols] = parseCoordinates(instruction)
    tokens = regexp(instruction, '(\d+),(\d+) through (\d+),(\d+)', 'tokens');
    numbers = cellfun(@str2double, tokens{1});
    x1 = numbers(1) + 1;
    y1 = numbers(2) + 1;
    x2 = numbers(3) + 1;
    y2 = numbers(4) + 1;

    rows = x1:x2;
    cols = y1:y2;
end

function lights = lightToggle(instruction, lights)
    [rows, cols] = parseCoordinates(instruction);
    lights(rows, cols) = ~lights(rows, cols);
end

function lights = lightOff(instruction, lights)
    [rows, cols] = parseCoordinates(instruction);
    lights(rows, cols) = false;
end

function lights = lightOn(instruction, lights)
    [rows, cols] = parseCoordinates(instruction);
    lights(rows, cols) = true;
end

function brightLights = lightBrighten(instruction, brightLights)
    [rows, cols] = parseCoordinates(instruction);
    brightLights(rows, cols) = brightLights(rows, cols) + 2;
end

function brightLights = lightDim(instruction, brightLights)
    [rows, cols] = parseCoordinates(instruction);
    brightLights(rows, cols) = max(brightLights(rows, cols) - 1, 0);
end

function brightLights = lightIncrease(instruction, brightLights)
    [rows, cols] = parseCoordinates(instruction);
    brightLights(rows, cols) = brightLights(rows, cols) + 1;
end