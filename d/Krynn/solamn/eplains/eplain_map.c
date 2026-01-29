/*
 The Solamnian Plains with the road to Kalaman
*/
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

/*
V - Ferry/Ford to Vingaard Keep
K - Kalaman
D - Dargaard Mountains/Dargaard Keep
T - Road to Throtl (goblins)
W - Waterfall / + Stream
L - Dragon lair entrance
S - Road to Solanthus
Q - Spring of small stream/Cave with refugees
R - Refugees
U - Ruins of a Village
F - Ford
C - Drac Camp
E - Drac Camp
X - Stream joins Vingaard River
P - Crossroads

1-4 Road

p - Plains
m - mountains/can't pass
r - river (shore)/can't pass
s - stream
*/

public nomask void
set_map()
{
    Map = ({
/*  0 */"              rrrrrrrrrr",
/*  1 */"            rrp11111P111r",
/*  2 */"           rpp1ppppp3pppK",
/*  3 */"           rp1ppppp3pppp",
/*  4 */"           r1pppppp3pmm",
/*  5 */"          r1pppppppmD",
/*  6 */"         r1ppppppppm",
/*  7 */"         r1ppppppppm",
/*  8 */"         r1pppCpppppm",
/*  9 */"        Ws1pppppppppm",   
/* 10 */"      rrp1spppppppsppmL",
/* 11 */"    rrpp1Upsspppsspsppm",
/* 12 */"    Fppp1ppppspspppsppm",
/* 13 */"    rppp1pppppsppppspsQ",
/* 14 */"    rppps1ppppppppppsm",
/* 15 */"   rppps1sspppppppppm",       
/* 16 */"    Xss1pppspssppEpppm",
/* 17 */"   rpp1pppppsppsppppppmmm",
/* 18 */"    r1pppppppppspppppppppm",
/* 19 */"    r1ppppppppppsppsspppppm",
/* 20 */"    1ppppppppppppssppsRppm",
/* 21 */"    V1pppppppppppppppspppm",
/* 22 */"    rp11ppppp111pppppspmm",
/* 23 */"    rp1p11111ppp1pppppsm",
/* 24 */"    rp1pppppppppp1ppp11T",
/* 25 */"   rppSppppppppppp111ppp",
	  });

/* warfare areas:
   - Nightlund
   / Guardlund
   . Throtyl pass
*/
    Map2 = ({
/*  0 */"              ----------",
/*  1 */"            -------------",
/*  2 */"           -------------K",
/*  3 */"           -------------",
/*  4 */"           ------------",
/*  5 */"          ----------D",
/*  6 */"         -----------",
/*  7 */"         -----------",
/*  8 */"         ------------",
/*  9 */"        -------------",   
/* 10 */"      //////////------L",
/* 11 */"    //////////////..---",
/* 12 */"    ////////////.....--",
/* 13 */"    /////////..........",
/* 14 */"    ///////////.......",
/* 15 */"   ///////////.......",       
/* 16 */"    //////////........",
/* 17 */"   ///////////...........",
/* 18 */"    ///////////...........",
/* 19 */"    ///////////............",
/* 20 */"    //////////............",
/* 21 */"    ////////..............",
/* 22 */"    ////////.............",
/* 23 */"    /////////...........",
/* 24 */"    /////////..........T",
/* 25 */"   ///S///..............",
	  });
}