#pragma no_clone
#pragma no_inherit
#pragma strict_types
#pragma save_binary
inherit "/d/Ansalon/std/map_map";

public string *Map2 = ({});

/* Function name: query_local_map2
 * Description:	  Gives symbol on secondary map for given coordinates
 * Argument:	  x,y - coordinates of room on map
 * Returns:	  string of lenght 1 giving representing symbol on Map2
 */
public nomask string
query_local_map2(int x, int y)
{
    if ((y > -1) && (x > -1) && (y < sizeof(Map2)) && (x < strlen(Map2[y])))
	return Map2[y][x..x];
    return " ";
}

public nomask void
set_map()
{
    Map = ({
/*  0 */"  pppvvpppphppppppc",
/*  1 */" pppvvvvppppupppppwcccc",
/*  2 */" pppvvvvvEppppwwwwwwZwwc",
/*  3 */" pupvvvvD Bppphhhwwhwwhwc",
/*  4 */" wppvvvvvCv1ppphhwwwhhwc",
/*  5 */"  ppvvvvv1vv1pphhwwwhwwwc",
/*  6 */"   ppvvvv1vvv1phphwhwwwwc",
/*  7 */"   puvvvv1vvv1ppphwhwwwc",
/*  8 */"   ppvvvv1vv1pwpphhhw",
/*  9 */"   p11111vvvv1ppphhw",
/* 10 */"  O1hKjppvvvv1ppphhh",
/* 11 */"   hh3p1ppvvvpMpphhhhhX",
/* 12 */"   h3hhp11111L Aphhhhh3wc",
/* 13 */"  hh3hhp1ppwppSp1hpph3wwc",
/* 14 */"  hh3hh1pppppp1ph1111hwc",
/* 15 */"  hh3h1pphppp1pphhphhwwc",
/* 16 */"  h3Tspppupp1phhhhhhhwwc",
/* 17 */" G111pwphpp1pphhhhphwwwc",
/* 18 */"    1ppwppp1pphhhhhhwwwc",
/* 19 */"   1ppppp1Ypppuuuhhhwwc",
/* 20 */"    1ppp1pppppuuuuhhhc",
/* 21 */"    1pp1ppppppuuuuuhhc",
/* 22 */"     11ppppppcccccccc",
/* 23 */"     1cccpppc",
/* 24 */"    N    ccc",
	  });

    /*
    // Map2 is used for determining warfare area here
    Areas:
    .		North Abanasinian Plains (Que-Kiri npcs)
    ;		Central Abanasinian Plains (Que-Shu npcs)
    /		Solace Area (removed by Arman)
    -		Newports Area (Que-Teh npcs)
    */
    Map2 = ({
/*  0 */"  .................",
/*  1 */" ......................",
/*  2 */" ........E..............",
/*  3 */" .......D B..............",
/*  4 */" ........C..............",
/*  5 */"  .......................",
/*  6 */"   ......................",
/*  7 */"   ......;;;;;;.........",
/*  8 */"   ...;;;;;;;;;;;....",
/*  9 */"   ;;;;;;;;;;;;;;;;;",
/* 10 */"  O;;;;;;;;;;;;;;;;;",
/* 11 */"   ;;;;;;;;;;;M;;;;;;;X",
/* 12 */"   ;;;;;;;;;;L A;;;;;;;;;",
/* 13 */"  ;;;;;;;;;;;;S;;;;;;;;;;",
/* 14 */"  ------;;;;;;;;;;;;;;;;",
/* 15 */"  ------;;;;;;;;;;;;;;;;",
/* 16 */"  -------;;;;;;;;;;;;;;;",
/* 17 */" G-------;;;;;;;;;;;;;;;",
/* 18 */"    ------;;;;;;;;;;;;;;",
/* 19 */"   -------Y-------;;;;;",
/* 20 */"    ------------------",
/* 21 */"    ------------------",
/* 22 */"     ----------------",
/* 23 */"     --------",
/* 24 */"    N    ---",
	  });
}

/*
The plains with the Sageway.
s - swamp  ???

1 - Sageway
3 - Valley
c - coast
h - hills
p - Plains
u - undulating country
v - burnt plains!
w - woods
Y - refugee
Z - clearing
t - Village of Que Teh  (entry point)
T - Village of Que Teh  // accessible only from "t"
k - Village of Que Kiri (entry point)
K - Village of Que Kiri // accessible only from "k"


Entry points (not map rooms):

O - Solace
G - Gateway
N - Newports
X - Xak Tsaroth

S - Village of Que Shu (south)
M                      (north)
A                      (east)
L                      (west)

C - Camp               (south)
E                      (north)
B                      (east)
D                      (west)

*/

