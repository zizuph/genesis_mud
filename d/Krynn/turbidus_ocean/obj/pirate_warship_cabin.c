/*
 * Cabin on the minotaur warship sailing the bloodsea.
 * Made by Cherek Jan 2007.
 */
 
#include "../local.h"
#include "/sys/stdproperties.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"
#include <composite.h>
#include <filter_funs.h>
inherit "/std/room.c";

void set_exit(string exit_name);

void
create_room() 
{

    set_short("Inside a cabin");
    set_long("You stand inside a quite spacious cabin aboard " +
        "a pirate warship. The room is richly furnished " +
        "yet very functional on a ship. At the end of the " +
        "cabin is a large window overlooking the vast ocean " +
        "outside. A doorway leads back out to the main deck.\n");
            
    add_item(({"window", "ocean", "vast ocean"}),
               "From here you have a splendid view of the " +
               "surrounding ocean.\n");                      
               
    add_item("cabin",
             "It probably belongs to the captain of the ship. \n");               

    add_item("view",
             "No land in sight. No nothing in sight. Only water. \n"); 
             
    add_item("doorway",
             "You can see most of the main deck from here. \n");               

    add_item(({"deck", "main deck"}),
               "You see nothing special about it. \n"); 
               
     add_item(({"ship", "warship"}),
                "Everything on this ship seem to have been very " +
                "carefully designed. \n");               

    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}

void set_exit(string exit_name)
{
    remove_exit("out");
    add_exit(exit_name, "out", 0, 1);
}

void clean_loot()
{
    cleanup_loot();
}