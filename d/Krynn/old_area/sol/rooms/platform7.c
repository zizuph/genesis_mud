/*
 * The village Solace
 *
 * By Rastlin
 */
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM;

create_solace_room()
{
    set_place(PLATFORM);

    set_long_desc("The platform has three bridge-walks connected to it, " +
		  "and a stairway leading down to the ground. The limbs of " +
		  "the mighty Vallenwood trees interwines and forms a " +
		  "thick canopy overhead.");
    
    add_exit(TDIR + "bridge_walk20", "northeast");
    add_exit(TDIR + "bridge_walk22", "southeast");
    add_exit(TDIR + "bridge_walk23", "northwest");
    add_exit(TDIR + "clearing1", "down");
}
