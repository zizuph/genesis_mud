/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house1_bedrm2.c
 *
 * Calathin external house.
 * 09/30/1999 -- TOMAS
 *
 *  Modified: 30 Apr 2003, by Bleys
 *      - fixed a typo in an add_item()
 *
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>


inherit STDROOM;
object door;

#include <stdproperties.h>


public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("master bedroom");
    set_long("This is the master bedroom. To the south is a small window. " +
       "A large bed is pushed against the west wall. Clothes hang on hooks " +
       "against the east wall.\n");

    add_item(({"large bed","bed"}),"The bed looks like it could sleep " +
       "two comfortably. The wooden headboard rests behind the bed.\n");
    add_item(({"wooden headboard","headboard","oak headboad"}),
       "The headboard is made from oak. Someone has carved a rose " +
       "pattern around the edge of the headboard.\n");
    add_item(({"rose pattern","pattern"}),"Quality woodwork. You're impressed. " +
       "Someone spent a lot of time carving roses into the oak headboard.\n");
    add_item(("clothes"),"Workmens clothes mostly. You decide they wouldn't look " +
       "good on you.\n");
    add_item(("window"),"The window is closed with the shutters drawn to keep " +
       "the elements outside.\n");

    add_cmd_item(({"drape", "window","curtain"}),
                 ({"tear","rip","open"}),
                 ("It's cold enough inside, why would you want to do that?\n"));
    add_cmd_item(("clothes"),
                 ({"wear","get","take"}),
                 ("The clothes are for honest hardworking folk, unlike " +
                  "yourself.\n"));




    door = clone_object(CALATHIN_DIR + "houses/obj/house1_bedrm2_door");
       door->move(TO);

    reset_room();
}

