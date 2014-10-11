import "stdio"

func hello() {
	
	name := "Doge"

	print("Hello, world")

	println("Hello %s", name)

}

func main() {
	
	i := 1+1/2*3

	var input String

	println("Number: %d", i)

	for {

	    input(">> ", input)

	    println("Input: %s\n", input)

	    if input == "doge" {

	        println("Doge!")

	    }

	}

	hello()

}