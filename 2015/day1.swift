import Foundation

func guideSanta(directions: String) -> Int {
    var floor = 0

    for char in directions {
        if char == "(" {
            floor += 1
        } else if char == ")" {
            floor -= 1
        }
    }

    return floor
}

func findBasement(directions: String) -> Int {
    var floor = 0
    var position = 0

    for char in directions {
        position += 1

        if char == "(" {
            floor += 1
        } else if char == ")" {
            floor -= 1
        }

        if floor == -1 {
            break
        }
    }

    return position
}

let filePath = "/Users/cv/projects/aoc/inputs/2015/day1.txt"
if let givenDirections = try? String(contentsOfFile: filePath, encoding: .utf8) {
    let lastFloor = guideSanta(directions: givenDirections)
    print("Santa will end on floor \(lastFloor)")

    let lastPosition = findBasement(directions: givenDirections)
    print("Santa enters the basement from instruction no. \(lastPosition)")
} else {
    print("Error reading file")
}
