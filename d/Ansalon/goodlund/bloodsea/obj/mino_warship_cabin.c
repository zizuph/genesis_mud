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
             "a minotaur warship. The room is richly furnished " +
             "yet very functional on a ship. At the end of the " +
             "cabin is a large window overlooking the vast ocean " +
             "outside. A heavy wooden desk stands to its left and " +
             "a tidy canopy bed to its right. The walls are " +
             "decorated with various objects and paintings while a " +
             "thick blood red carpet lines the floor. A doorway " +
             "leads back out to the main deck.\n");
            
    add_item(({"window", "ocean", "vast ocean"}),
               "From here you have a splendid view of the " +
               "surrounding ocean. The reflections of the " +
               "dark red waters of the Bloodsea gives the " +
               "entire room an ominous feel.\n");
               
     add_item(({"water", "waters", "dark waters", "red waters",
                "dark red waters"}),
                "The restless waves crash against " +
                "the hull of the ship below the windows.\n");              

    add_item(({"desk", "wooden desk", "heavy desk", "heavy wooden desk"}),
               "It is tightly secured to the floor and made from " +
               "dark well-polished wood. The only thing of interest " +
               "on it is a map of some kind. \n");               
   
    add_item(({"map", "chart", "mithas", "khotas", "karthay"}),
               "Upon closer examination this seems to be a standard " +
               "chart over the waters around the islands Mithas, Khotas " +
               "and Karthay. \n");

    add_item(({"bed", "tidy bed", "canopy bed", "tidy canopy bed"}),
               "The bed seem to have been built when the ship was " +
               "built since its actually a part of the wall. It does " +
               "look quite comfortable and there is plenty of space. \n");

    add_item(({"wall", "walls"}),
               "Dark sleep wooden planks make up the walls of this " +
               "cabin. \n"); 
               
    add_item(({"objects", "paintings", "painting"}),
               "Nothing really catches your eye. \n");               

    add_item(({"carpet", "blood red carpet", "red carpet", "floor"}),
               "The wooden floor is almost entirely covered by a " +
               "blood red carpet. You notice a few spots with deeper " +
               "red color in the center of the carpet. \n"); 
 
     add_item(({"spot", "spots", "color", "stain", "stains"}),
                "It is not easy to notice since the carpet is red, but " +
                "this appears to be stains of blood. Apparently fighting " +
                "has taken place even in this room, and not long ago. \n"); 
               
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