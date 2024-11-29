Objective of the program is to find ways to stack four cubes as a vertical column so that each side of the column is showing all four colors.

Input: 
- string of comma seperated cube definitions. 
- Sides are encoded in following sequence: front, back, left, right, top, bottom
- Colors are: red (R), green (G), yellow (Y) and blue (B)

Output:
printed each combination that correspond to the objective. Between the combinations is one empty line. Each combination is printed with one cube on a single line.

example:
Input: RBGYBY,RGGYBB,YBRGYR,YGBRRR

Output:
YBBRGY
GYRGBB
RGYBRY
BRGYRR

BYBRYG
YGRGBB
GRYBYR
RBGYRR

YBRBYG
GYGRBB
RGBYYR
BRYGRR

BYRBGY
YGGRBB
GRBYRY
RBYGRR

RBBYYG
GRYGBB
BYGRYR
YGRBRR

BRYBYG
RGGYBB
YBRGYR
GYBRRR

RBYBGY
GRGYBB
BYRGRY
YGBRRR

BRBYGY
RGYGBB
YBGRRY
GYRBRR
