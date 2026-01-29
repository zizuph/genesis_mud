/*
 The Sparkle Sea Map by Arman, January 2021
*/
#pragma no_clone
#pragma no_inherit
#pragma strict_types
#pragma save_binary

#include "local.h"

inherit MAP_HANDLER;

/*
s - Pen Sea
b - Blue Bottom Bay
c - coastline
m - coastline (moors)
j - coastline (Jade Forest)
d - docks
x - exit room to Toroid High Seas
t - Toroid High Sea (transit sailing)
k - Krynn sea link
n - north link (unused)
e - east link (unused)
*/

public nomask void
set_map()
{
    Map = ({

/* file naming convention: */
/* sparkle_sea-a-b-map_letter  */

/* 'b'  'a' ->   */ 
/*  |    012345678901234567890*/
/*  0 */"",
/*  1 */"    msss   nnn",
/*  2 */"   mssss ttttttt",
/*  3 */" msssssxttt   tte",
/*  4 */"  ddsssxtt     te",
/*  5 */"   dsssxttt   tte",
/*  6 */"   cssss ttttttt",
/*  7 */"   cssss   kkk",
/*  8 */"  csssss",
/*  9 */"   cbbbb",
/* 10 */"  cbbbbb",
/* 11 */" cbbbbbb",
/* 12 */" jbbbbbb",
/* 13 */" jbbbbbb",
/* 14 */"jbbbbbbb",
/* 15 */"jbbbbbbb",
	  });
}