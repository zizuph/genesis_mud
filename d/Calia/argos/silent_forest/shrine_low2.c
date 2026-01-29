/*
 *   shrine_low2.c
 * 
 *  Dark underground chamber.
 *
 * Baldacin@Genesis, Sep 2003
 */

#pragma strict_types
#include <stdproperties.h>
#include <macros.h>
#include "ldefs.h"
inherit "/std/room";

int load_the_bloody_room() {return 1;}

void
reset_room()
{
    int i;
    object stand, chest;
    object *livings = all_inventory(this_object());

    setuid();
    seteuid(getuid());
        
    if (present("c_chest"))
		present("c_chest")->remove_object();

    chest = clone_object(SFOBJDIR+"chest.c");
	chest->move(TO, 1);

    
	if (present("c_stand"))
		present("c_stand")->remove_object();

	stand = clone_object(SFOBJDIR+"weapon_stand.c");
	stand->move(TO, 1);

    

    for (i=0;i < sizeof(livings);i++)
    {
        if (interactive(livings[i]))
        {            
            tell_room(SFDIR + "shrine_low1.c", "Suddenly "+QTNAME(livings[i])+
              " arrives flying from the north.\n");
            write("Suddenly you slip on a small pebble and fall out "+
              "of the room.\n");
            livings[i]->move(SFDIR + "shrine_low1.c");
            tell_room(this_object(), "Suddenly "+QTNAME(livings[i])+
              " slips on a small pebble and fall out of the room.\n");
        }
    }

	(SFDIR + "shrine_low1.c")->reset_room(); /* To make sure that the
                                 undead guardian is guarding the room */
}

public void
create_room()
{   
    set_short("A small, dark backroom");
    set_long("In a small and dark backroom. This dark room-space is "+
      "empty except for a grand looking crystal weapon stand, leaning "+
      "against the western wall and an iron chest. A small opening in "+
      "the southern wall is the only obvious exit out of here.\n");
    
    add_item("western wall","Leaning against the western wall is an weapon stand, "+
      "very elegant and made out of crystal.\n");
    add_item(({"wall", "walls", "rocky walls"}),"The low, rocky walls are "+
      "made of some sort of greyish rock, some moldy lichens and mosses.\n");
    add_item(({"lichens", "mosses"}),"The lichens and mosses are "+
      "leafy-stemmed and crustlike, they grow in clusters.\n");
    add_item("opening","A small opening in the southern wall leads back out to "+
      "the chamber.\n");
    
    add_prop(ROOM_I_LIGHT, -1);
    
    add_exit(SFDIR + "shrine_low1.c", "south");
    
    reset_room();
}

