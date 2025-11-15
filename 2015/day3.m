function day3
    d = fileread('inputs/day3.txt');
    deliverPresents(d)
    deliverWithRoboSanta(d)
end


function n = deliverPresents(directions)
    presentsDelivered = 1;
    visitedHouses = [0, 0];
    currentCoordinates = [0, 0];

    for i = 1:length(directions)
        step = directions(i);

        if step == '^'
            currentCoordinates(1) = currentCoordinates(1) + 1;
        elseif step == 'v'
            currentCoordinates(1) = currentCoordinates(1) - 1;
        elseif step == '<'
            currentCoordinates(2) = currentCoordinates(2) - 1;
        elseif step == '>'
            currentCoordinates(2) = currentCoordinates(2) + 1;
        end

        presentsDelivered = presentsDelivered + 1;

        if ~ismember(currentCoordinates, visitedHouses, 'rows')
            visitedHouses = [visitedHouses; currentCoordinates]; %#ok<AGROW>
        end
    end

    n = size(visitedHouses, 1);
end


function n = deliverWithRoboSanta(directions)
    presentsDelivered = 1;
    visitedHouses = [0, 0];
    currentSantaCoordinates = [0, 0];
    currentRoboSantaCoordinates = [0, 0];

    for i = 1:length(directions)
        step = directions(i);

        if mod(i, 2) == 1  % Santa
            if step == '^'
                currentSantaCoordinates(1) = currentSantaCoordinates(1) + 1;
            elseif step == 'v'
                currentSantaCoordinates(1) = currentSantaCoordinates(1) - 1;
            elseif step == '<'
                currentSantaCoordinates(2) = currentSantaCoordinates(2) - 1;
            elseif step == '>'
                currentSantaCoordinates(2) = currentSantaCoordinates(2) + 1;
            end

            if ~ismember(currentSantaCoordinates, visitedHouses, 'rows')
                visitedHouses = [visitedHouses; currentSantaCoordinates]; %#ok<AGROW>
            end
        else  % RoboSanta
            if step == '^'
                currentRoboSantaCoordinates(1) = currentRoboSantaCoordinates(1) + 1;
            elseif step == 'v'
                currentRoboSantaCoordinates(1) = currentRoboSantaCoordinates(1) - 1;
            elseif step == '<'
                currentRoboSantaCoordinates(2) = currentRoboSantaCoordinates(2) - 1;
            elseif step == '>'
                currentRoboSantaCoordinates(2) = currentRoboSantaCoordinates(2) + 1;
            end

            if ~ismember(currentRoboSantaCoordinates, visitedHouses, 'rows')
                visitedHouses = [visitedHouses; currentRoboSantaCoordinates]; %#ok<AGROW>
            end
        end

        presentsDelivered = presentsDelivered + 1;
    end

    n = size(visitedHouses, 1);
end