/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house3_tree.c
 *
 * Calathin external house.
 * 09/30/1999 -- TOMAS
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>

inherit STDROOM;
#include <stdproperties.h>
object door;
int climb_down(string str);

public void
create_room()
{
    ::create_room();
    set_short("treetop");
    set_long("You stand on one of the larger branches " +
       "of the west oak tree. The roof of the house " +
       "is just out of reach to the north. Above you " +
       "is the wooden flooring of a well concealed " +
       "treehouse. You might be able to climb down " +
       "to the ground from here.\n");
     
    add_item(({"branch","branches"}),"The branches vary " +
       "in their size from large to small.\n");
    add_item(({"west oak tree","oak tree","tree"}),
       "A very large oak tree. Its difficult to guess " +
       "just how long its been here.\n");
    add_item(("roof"),"The edge of the roof is just out of " +
       "arms reach. Its a wonder you made the jump without " +
       "falling and breaking your arm!\n");
    add_item(({"wooden flooring","flooring","floor"}),
       "Wooden planks made of oak to help hide it from " +
       "prying eyes from below. A trapdoor is centered " +
       "in the floor.\n");
    add_item(("ground"),"The ground is just below you. " +
       "You figure you can climb down from here.\n");
    add_item(({"trapdoor","trap door","door"}),
       "The trapdoor is made of oak. It leads into the " +
       "small treehouse above you.\n");
    add_item(("treehouse"),"The small treehouse has been " +
       "well hidden from the ground below.\n");

    
    add_cmd_item("roof","jump","You decide that the angle of " +
       "jump would be impossible to make.\n");
    add_cmd_item("down","climb",climb_down);


    door = clone_object(CALATHIN_DIR + "houses/obj/house3_th_door");
                door->move(TO);

    reset_room();
}


int
climb_down(string str)
{
   write("Wrapping your arms around the massive trunk, you slide " +
      "to the ground below.\n");
   TP->move_living("sliding down the length of the trunk to the ground below", 
   CALATHIN_DIR + "houses/house3.c",1,0);
 return 1;
}
