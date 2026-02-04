/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house4e.c  -- dining room
 * Calathin external house.
 * 11/07/1999 -- TOMAS
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>

inherit STDROOM;
#include <stdproperties.h>
object servant = 0;

public void
create_room()
{
    ::create_room();
    INSIDE;

    set_short("dining room");
    set_long("The dining room is quite large. In the middle of the room " +
       "is a long table which stretches from the door to an enormous " +
       "fireplace on the east wall. Several high backed wooden chairs " +
       "are positioned equally about the dining room table. " +
       "Resting before the fireplace are two leather chairs sitting " +
       "upon a plush animal throw rug. A large painting hangs above the " +
       "fireplace mantle.\n");
      
    add_item(({"table","long table","dining room table"}),
       "The long table is made from dark walnut. Four candelabra " +
       "sit upon the dining room table. Several dark walnut high backed " +
       "chairs are positioned about the table.\n");

    add_item(("chairs"),"Which chairs do you want to look at, the leather chairs " +
       "or the wooden chairs?\n");

    add_item(({"wooden chair","wooden chairs"}),
       "The high backed wooden chairs surround the long dining room table. " +
       "The appear to be made of the same wood that the table was made from.\n");
  
    add_item(({"leather chairs","leather chair"}),
       "Two overstuffed leather chairs sit on opposite sides of the enormous " +
       "fireplace. They look quite comfortable.\n");

    add_item(({"fireplace","enormous fireplace"}),
       "The fireplace is large enough to stand in. Two large pieces of firewood " +
       "rest in the fireplace.\n");

    add_item(({"walls", "paneling"}),
       "The walls have been covered with a dark walnut wood stained " +
       "with a slight reddish tint. The trim at the floor and ceiling " +
       "are stained darker to be almost black and have been carved " +
       "with elaborate patterns. A piece of trim also circles around the " +
       "room at waist level it too is stained a darked color. Eight crystal " +
       "lamps, two to a wall are evenly spaced around the room.\n");

    add_item(({"crystal lamps","crystal","lamps"}),
       "Several crystal lamps hang evenly about the walls of the room, providing " +
       "light.\n");

    add_item(({"large painting","painting"}),
       "The painting is of a lovely woman dressed in a floor length gown. " +
       "The artist spent alot of time and detail on the painting, it looks " +
       "almost lifelike.\n");

    
    add_exit(CALATHIN_DIR + "houses/house4d","west",0,1);
    
 
    add_cmd_item(({"fireplace"}),
                 ("stand"),
                 ("You step towards the fireplace then decide not to get your " +
                  "clothes dirty by standing in the fireplace.\n"));


    reset_room();

}

void
reset_room()
{    
  
    if(!servant)
    {
       servant = clone_object(CALATHIN_DIR + "houses/npc/servant");
       servant->move(TO);
   
    }
}
