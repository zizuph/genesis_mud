/*
 The Throtyl road to Sanction by Arman, June 2020
*/
#pragma no_clone
#pragma no_inherit
#pragma strict_types
#pragma save_binary
inherit "/d/Ansalon/std/map_map";

/*
R - ?
P - Solamnian east plains link
S - Sanction link
E - Estwilde link
K - East Keep
T - dwarven tomb

1 - Road (Throtyl forest)
2 - Road (Throtyl pass)
3 - Road (marshy bog)
4 - Road (Khalkist mountain range)
5 - Road (Doom Range)

f - Stormshire Forest
v - mountains
m - moors
*/

public nomask void
set_map()
{
    Map = ({

/* file naming convention: */
/* throtyl-a-b-map_letter  */

/* 'b'  'a' ->   */ 
/*  | */
/*  0 */"     fffff",
/*  1 */"    fffffff",
/*  2 */"    P1fffff",
/*  3 */"    ff11fff",
/*  4 */"     fff1f     E",
/*  5 */"         2   Tvm",
/*  6 */"          2 vvmm",
/*  7 */"          m3mmmm",
/*  8 */"         mmm3mmm",
/*  9 */"        mmmmm3mm",
/* 10 */"        mmm  4",
/* 11 */"        K     4",
/* 12 */"               4",
/* 13 */"               5",
/* 14 */"               5",
/* 15 */"                5",
/* 16 */"                5",
	  });
}