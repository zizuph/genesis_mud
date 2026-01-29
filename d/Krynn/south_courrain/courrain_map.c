/*
 The Southern Courrain Sea by Arman, January 2021
*/
#pragma no_clone
#pragma no_inherit
#pragma strict_types
#pragma save_binary
inherit "/d/Ansalon/std/map_map";

/*
B - Bloodsea of Istar rooms
s - open sea
p - passage between Mithas and Kothas
c - northern Goodlund coast
d - passage to south Courrain
e - eastern Dairly Plains coastline
f - southern Dairly Plains coastline
g - southern Goodlund coastline
h - Bay of Balifor
i - Silvanesti Coastline
x - northern open sea border
y - eastern open sea border
z - southern open sea border
*/

public nomask void
set_map()
{
    Map = ({

/* file naming convention: */
/* s_courrain-a-b-map_letter  */

/* 'b'  'a' ->   */ 
/*  | */
/*  0 */"                BBB",
/*  1 */"                BBB",
/*  2 */"                BBB",
/*  3 */"                BBB",
/*  4 */"                BBB",
/*  5 */"                BBB",
/*  6 */"                BBB",
/*  7 */"                BBBpppppp",
/*  8 */"                BBB",
/*  9 */"                BBB",
/* 10 */"                BBB",
/* 11 */"                BBB",
/* 12 */"              BBBBBBBB",
/* 13 */"            ccccccccdd",
/* 14 */"                    dd",
/* 15 */"                  essssssy",
/* 16 */"                  essssssy",
/* 17 */"   h              essssssy",
/* 18 */"hhhhh    gggff    essssssy",
/* 19 */"ihhhhhhggsssssfffffsssssssxxy",
/* 20 */" iiiihssssssssssssssssssssssy",
/* 21 */"     iisssssssssssssssssssssy",
/* 22 */"        izzzzzzzzzzzzzzzzzzzz",
	  });
}