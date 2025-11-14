import Foundation

func requiredWrappingPaper(l: Int, w: Int, h: Int) -> Int {
    let sides = [l*w, w*h, h*l]
    let surfaceArea = 2 * sides.reduce(0, +)
    return surfaceArea + sides.min()!
}

func requiredRibbon(l: Int, w: Int, h: Int) -> Int {
    let sides = [l, w, h].sorted()
    let wrap = sides[0]*2 + sides[1]*2
    let bow = l*w*h
    return wrap + bow
}

func main() {
    let filePath = "/Users/cv/projects/aoc/inputs/2015/day2.txt"
    
    guard let content = try? String(contentsOfFile: filePath, encoding: .utf8) else {
        print("Error reading file")
        return
    }
    
    var totalPaper = 0
    var totalRibbon = 0
    
    for line in content.split(separator: "\n") {
        let dimensions = line.split(separator: "x").compactMap { Int($0) }
        guard dimensions.count == 3 else { continue }
        
        let (l, w, h) = (dimensions[0], dimensions[1], dimensions[2])
        totalPaper += requiredWrappingPaper(l: l, w: w, h: h)
        totalRibbon += requiredRibbon(l: l, w: w, h: h)
    }
    
    print("The elves should order \(totalPaper) square feet of wrapping paper")
    print("The elves require \(totalRibbon) feet of ribbon")
}

main()