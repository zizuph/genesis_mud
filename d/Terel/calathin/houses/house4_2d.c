/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house4_2d.c
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
    set_long("The hallway ends before a small window overlooking the " +
       "backyard.\n");

    add_item(("window"),"The round window is made of colored glass. " +
       "The light passing through the glass creates an array of different " +
       "colored rays illuminating the hallway.\n");

    add_item(({"walls", "paneling"}),
       "The walls have been covered with a dark walnut wood stained " +
       "with a slight reddish tint. The trim at the floor and ceiling " +
       "are stained darker to be almost black and have been carved " +
       "with elaborate patterns. A piece of trim also circles around the " +
       "room at waist level it too is stained a darked color. Eight crystal " +
       "lamps, two to a wall are evenly spaced around the room.\n");


    add_exit(CALATHIN_DIR + "houses/house4_2a","south",0,1);
   
 
    door = clone_object(CALATHIN_DIR + "houses/obj/house4_2d_door");
       door->move(TO);

    door = clone_object(CALATHIN_DIR + "houses/obj/house4_2db_door");
       door->move(TO);



    reset_room();

}

