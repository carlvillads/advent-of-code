using MD5

function findcoin(key::String, targetprefix::String)
    n = 1

    while true
        inputstring = key * string(n)
        hash = md5(inputstring)
        hashhex = bytes2hex(hash)

        if startswith(hashhex, targetprefix)
            println("Found a match for '$(key)': $(hashhex)")
            return n
        end

        n += 1
    end
end

function findcoin_threaded(key::String, targetprefix::String)
    println("Running search on $(Threads.nthreads()) threads...")
    chunksize = 10_000
    n = 1

    while true
        result = Threads.Atomic{Int}(0)  # Thread safe integer

        Threads.@threads for i in n:(n + chunksize - 1)  # Split range into chunks
            if result[] > 0  # Check if another thread found the result
                continue
            end

            inputstring = key * string(i)
            hash = md5(inputstring)
            hashhex = bytes2hex(hash)

            if startswith(hashhex, targetprefix)
                Threads.atomic_cas!(result, 0, i)  # compare-and-swap
            end
        end

        if result[] > 0
            println("Found a match for '$(key)': $(bytes2hex(md5(key * string(result[]))))")
            return result[]
        end

        n += chunksize
    end
end

function main()
    givenkey = read("2015/inputs/day4.txt", String)

    println("Single threaded search:")
    time1 = @elapsed lowestnumber = findcoin(givenkey, "00000")
    println("The lowest positive number to match the key is: '$(lowestnumber)' (found in $(round(time1, digits=3))s)")
    time2 = @elapsed lowestnumber_six = findcoin(givenkey, "000000")
    println("The lowest positive number to match the key with 6 zeros is: '$(lowestnumber_six)' (found in $(round(time2, digits=3))s)\n")

    println("Multi threaded search:")
    time3 = @elapsed lowestnumber_threaded = findcoin_threaded(givenkey, "00000")
    println("The lowest positive number to match the key is: '$(lowestnumber_threaded)' (found in $(round(time3, digits=3))s)")
    time4 = @elapsed lowestnumber_threaded_six = findcoin_threaded(givenkey, "000000")
    println("The lowest positive number to match the key with 6 zeros is: '$(lowestnumber_threaded_six)' (found in $(round(time4, digits=3))s)")
end

main()