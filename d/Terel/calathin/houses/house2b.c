/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house2b.c
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

    set_short("bedroom");
    set_long("The bedroom is unkempt. There are piles of " +
       "filthy clothes thrown about the room. The bed is " +
       "unmade. Clearly, this room could use a good cleaning.\n");


    add_item(("clothes"),"Various items of clothes litter " +
       "the room. They dont look or smell as if they " +
       "have been washed in sometime.\n");
    add_item(("bed"),"The bed is unmade. It looks as if " +
       "the owner left in a hurry.\n");

    door = clone_object(CALATHIN_DIR + "houses/obj/house2_bedrm1a_door");
       door->move(TO);

    reset_room();

}

