function day4()
    givenKey = fileread('inputs/day4.txt');

    fprintf("Executing single threaded search...\n");
    tic;
    lowestNumber1 = findCoin(givenKey, '00000');
    time1 = toc;
    fprintf("The lowest positive integer to match the given key (5 zero start): '%d' (found in %.3fs)\n", lowestNumber1, time1);

    tic;
    lowestNumber2 = findCoin(givenKey, '000000');
    time2 = toc;
    fprintf("The lowest positive integer to match the given key (6 zero start): '%d' (found in %.3fs)\n", lowestNumber2, time2);

    fprintf("Executing multi threaded search...\n");
    tic;
    lowestNumber3 = findCoinThreaded(givenKey, '00000');
    time3 = toc;
    fprintf("The lowest positive integer to match the given key (5 zero start): '%d' (found in %.3fs)\n", lowestNumber3, time3);

    tic;
    lowestNumber4 = findCoinThreaded(givenKey, '000000');
    time4 = toc;
    fprintf("The lowest positive integer to match the given key (6 zero start): '%d' (found in %.3fs)\n", lowestNumber4, time4);
end


function n = findCoin(key, targetPrefix)
    n = 1;

    while true
        inputString = [key, num2str(n)];
        hashHex = mlreportgen.utils.hash(inputString);

        if startsWith(hashHex, targetPrefix)
            fprintf("Found a match for '%s': %s\n", key, hashHex);
            return;
        end

        n = n + 1;
    end
end

function n = findCoinThreaded(key, targetPrefix)
    n = 1;
    chunkSize = 10000;

    while true
        results = zeros(chunkSize, 1);

        % parallel for loop
        parfor i = 1:chunkSize
            nCurrent = n + i - 1;
            inputString = [key, num2str(nCurrent)];
            hashHex = mlreportgen.utils.hash(inputString);

            if startsWith(hashHex, targetPrefix)
                results(i) = nCurrent;
            end
        end

        % check if a worker found a match
        matches = results(results > 0);
        if ~isempty(matches)
            result = min(matches);
            foundHash = mlreportgen.utils.hash([key, num2str(result)]);
            fprintf("Found a match for '%s': %s\n", key, foundHash);
            n = result;
            return;
        end

        n = n + chunkSize;
    end
end