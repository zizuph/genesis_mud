/* rd_sw_01: south end of Stadium Way, Serpine 12/24/96. */
 
#pragma strict_types
 
inherit "/std/room";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "/d/Cirath/std/block.h"


void
create_room()
{
    ::create_room();
    set_short("south end of Stadium Way");
    set_long("Few areas of Tyr demonstrate the contrasts of the city so "
            +"well as the Gladiatorial Gate. Wealthy visitors from far "
            +"off lands arrive here from the south to witness the grim "
            +"spectacle of the arena to the north, while spiritless "
            +"slaves file out to work in the fields surrounding the "
            +"city. The gate itself is a rather beautiful, albeit "
            +"massive, carving of the most destructive force in Athas: "
            +"The Dragon. And drifting from the west are the sounds and "
            +"smells of the Shadow Market, a center of commerce and good "
            +"place to wind up with a poisoned dagger in your back.\n");
 
    add_item(({"gate","gladiatorial gate","dragon","carving"}),
             "Large triangular stones mimic teeth, and two huge jagged "
            +"slabs sit just inside the wall to plug it in times of war. "
            +"The nostrils of the carving appear hollow and have stains "
            +"as if something burning poured out of them at some point.\n");
    add_item(({"slave","slaves","spiritless slave","spiritless slaves"}),
             "Many will never return, and will just serve the city as "
            +"fertilizer.\n");
    add_item(({"visitor","visitors","wealthy visitor","wealthy visitors"}),
             "From the other city-states, from Chukel, and even from "
            +"such mythical places as Ri-Albi and Solace they come. Few "
            +"groups of people can totally subvert the lust to see blood "
            +"spilled.\n");
 
    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM
 
    add_exit(TYR_MARKET+"rd_sw_02.c","north",0,1);
    add_exit(TYR_GATES+"gladgate.c","south","@@block_exit@@",1);
    add_exit(TYR_MARKET+"rd_mr_03.c","west",0,1);
}                                              
