/*
 *   cave05x09.c
 * 
 *  Small cave.
 *
 * Baldacin@Genesis, Sep 2003
 *
 *  2003/12/04      ?               Last update
 *  2010/09/04      Lavellan        Moved rat-man cloning from create_room to
 *                                      reset_room   
 */

#pragma strict_types
#include <stdproperties.h>
#include "ldefs.h"
inherit "/std/room";

public void
create_room()
{   
    set_short("A damp cave");
    set_long("In a damp cave. Only a few rays of light arrives "+
      "through the southern opening, shedding some light. The cave continues "+
      "north, further into the darkness.\n");

    add_item("moss","It is a green slimy moss.\n");
    add_item(({"wall", "walls"}), "The walls are covered " +
             "with moss.\n");
    
    add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_S_DARK_LONG, "In a damp cave. Only a few rays of light arrives "+
      "through the southern opening, shedding some light.\n");
	
    add_exit(SFDIR + "cave05x11.c", "north");
    add_exit(SFDIR + "forest05x07.c", "south");
    
    reset_room();
}

public void
reset_room()
{
    object *rats = filter(all_inventory(TO), &->id("ratman"));
    object rat;
    
    if (sizeof(rats) < 2)
    {
       setuid();
       seteuid(getuid());
       
       if (sizeof(rats) < 2)
       {
           rat = clone_object(SFLIVDIR+"ratman.c");
           rat->move(TO, 1);
       }       
       rat = clone_object(SFLIVDIR+"ratman.c");
       rat->move(TO, 1);
    }    
}