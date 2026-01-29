/* rd_sw_02: middle of southern Stadium Way, Serpine-2/16/96. */
 
#pragma strict_types
 
inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/std/block.h"
 
 
void
create_room()
{
    ::create_room();
    set_short("middle of southern Stadium Way");
    set_long("Midway between the arena and the Gladiatorial Gate that "
            +"leads south out of Tyr, this road also runs along the "
            +"stone wall marking the border between two districts. The "
            +"wild yelling of elven traders in the shadowy Market "
            +"District on one side is an interesting contrast with the "
            +"somber quiet of the governmental district, the 'Golden "
            +"City,' that towers to the east. Added to the unearthly "
            +"glare of the sun reflecting off the Ziggurat, this is a "
            +"picturesque spot indeed.\n");
 
    add_item("arena", "It looks like a huge stone box from here.\n");
    add_item(({"gate", "gladiatorial gate"}), "The gate is carved to "
            +"resemble the head of the Dragon. Not much detail can be "
            +"made out at this distance however.\n");
    add_item(({"wall", "stone wall"}), "As tall as Athasian giants can "
            +"reach, the wall is unbreachable by smaller beings.\n");
    add_item(({"golden city", "governmental district"}),
             "You can't make anything out over such a high wall.\n");
    add_item(({"market district", "shadowy market district"}),
             "A row of large buildings blocks a clear view west.\n");
    add_item(({"district", "districts"}), "Which one?\n");
    add_cmd_item(({"elf", "trader", "elven traders", "traders","to elf",
                 "to elven traders", "to traders", "to trader"}),
                 "listen", "The traders are hawking merchandise.\n");
 
    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM
 
    add_exit(TZ_MARKET+"rd_sw_03.c", "north", 0, 1);
    add_exit(TZ_GATES+"gate_ts.c", "east", "@@block_exit@@", 1);
    add_exit(TZ_MARKET+"rd_sw_01.c", "south", 0, 1);
    reset_room();
}
