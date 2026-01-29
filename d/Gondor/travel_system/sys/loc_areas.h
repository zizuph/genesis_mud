#ifndef ARDA_LOC_AREAS

#define DIVISION_EXAMPLE     (1 << 25)
#define AREA_EXAMPLE_FOREST      (1 << 23 | DIVISION_EXAMPLE)
#define AREA_EXAMPLE_RBANK       (1 << 22 | DIVISION_EXAMPLE)
#define AREA_EXAMPLE_FORTS       (1 << 21 | DIVISION_EXAMPLE)
#define AREA_EXAMPLE_CAMP        (1 << 20 | DIVISION_EXAMPLE)

#define DIVISION_WEST        (1 << 30)
#define AREA_WEST_TROLLGARD      (1 << 23 | DIVISION_WEST)

#define DIVISION_NORTH       (1 << 29)
#define DIVISION_SOUTH       (1 << 28)
#define DIVISION_N_ISLAND    (1 << 27)
#define DIVISION_S_ISLAND    (1 << 26)

#define ARDA_LOC_AREAS
#endif
