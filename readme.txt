=== Journey Through the Genome Game ===

Contributors:
	Joey McKeown
	Liam Ridenour
	
Emails:
	Joey.Mckeown@colorado.edu
	Liam.Ridenour@colorado.edu
	
Compiling:
	Requires at least C++11
	Compile with: 
		g++ -std=c++11  main.cpp Board.cpp Player.cpp Scientists.cpp gameFeatures.cpp animateText.cpp -o game

        note: '-std+c++11' tells the compiler to use C++11 standards. I needed this on my Mac, but not my Windows, 
                so I'm not entirely sure why my Mac uses differemt standards.
                
                If you don't need it, you can just run 
                g++ main.cpp Board.cpp Player.cpp Scientists.cpp gameFeatures.cpp animateText.cpp -o game
                - Joey

Run Exe:
    ./game

        
	
