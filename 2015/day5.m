function day5
    lines = readlines("inputs/day5.txt");
    niceStrings = 0;
    newNiceStrings = 0;

    for i = 1:length(lines)
        line = strtrim(lines(i));
        if isNice(line)
            niceStrings = niceStrings + 1;
        end

        if newIsNice(line)
            newNiceStrings = newNiceStrings + 1;
        end
    end

    fprintf("There are %d nice strings\n", niceStrings)
    fprintf("There are %d nice strings when using the new method\n", newNiceStrings)
end


function result = isNice(line)
    vowels = "aeiou";
    disallowed = ["ab", "cd", "pq", "xy"];
    vowelCount = 0;
    doubleLetterPresent = false;

    for i = 1:strlength(line)
        char = extractBetween(line, i, i);
        
        if contains(vowels, char)
            vowelCount = vowelCount + 1;
        end

        if i > strlength(line) - 1
            continue;
        end

        if char == extractBetween(line, i+1, i+1)
            doubleLetterPresent = true;
        end

        pair = extractBetween(line, i, i+1);
        if any(strcmp(pair, disallowed))
            result = false;
            return;
        end
    end

    result = vowelCount >= 3 && doubleLetterPresent;
end

function result = repeatsPresent(str)
    for i = 1:strlength(str) - 2
        pair = extractBetween(str, i, i+1);
        rest = extractAfter(str, i+1);

        if contains(rest, pair)
            result = true;
            return;
        end
    end

    result = false;
end

function result = newIsNice(str)
    doubleLetterPresent = false;
    repeats = repeatsPresent(str);

    for i = 1:strlength(str) - 2
        if extractBetween(str, i, i) == extractBetween(str, i+2, i+2)
            doubleLetterPresent = true;
            break;
        end
    end

    result = repeats && doubleLetterPresent;
end