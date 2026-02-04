/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house4c.c
 * Calathin external house.
 * 09/30/1999 -- TOMAS
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>

inherit STDROOM;
#include <stdproperties.h>
object door;

public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("hallway");
    set_long("To the south is the main entrance. The kitchen " +
       "can be seen to the west and to the east is the dining room.\n");


    add_item(({"walls", "paneling"}),
       "The walls have been covered with a dark walnut wood stained " +
       "with a slight reddish tint. The trim at the floor and ceiling " +
       "are stained darker to be almost black and have been carved " +
       "with elaborate patterns. A piece of trim also circles around the " +
       "room at waist level it too is stained a darked color. Eight crystal " +
       "lamps, two to a wall are evenly spaced around the room. In three of " +
       "the walls is a niche containing a statue, the fourth wall is dominated " +
       "by a large fireplace.\n");

    add_exit(CALATHIN_DIR + "houses/house4f","west",0,1);
    add_exit(CALATHIN_DIR + "houses/house4e","east",0,1);
    add_exit(CALATHIN_DIR + "houses/house4a","south",0,1);

 


    add_cmd_item(({"book"}),
                 ("read"),
                 ("You would rather not, there isn't a bed nearby and " +
                  "no doubt reading this would put you to sleep in " +
                  "short order.\n"));

   door = clone_object(CALATHIN_DIR + "houses/obj/house4d_door");
       door->move(TO);


    reset_room();

}

