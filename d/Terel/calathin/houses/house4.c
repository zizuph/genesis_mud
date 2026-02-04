/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house4.c
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
object citizen = 0;

public void
create_room()
{
    ::create_room();

    set_short("large house");
    set_long("As you proceed down the path you can't help " + 
       "but admire the two story house that stands before you. Even " +
       "in the depths of winter the house appears well " +
       "maintained. The massive exposed timbers that form the frame " +
       "of the house have been waxed and polished to a fine sheen. " +
       "The outer walls are of beautifully aged cedar shingles. " +
       "The snow has recently fallen from most of the roof giving " +
       "you a view of the slate roof which has a distinct coloration. " +
       "From the lower level of the house a warm golden light spills " +
       "forth from the windows.\n");
 
    add_item(("shingles"),"White shingles cover the exterior of the " +
       "windows.\n");

    add_item(("timbers"),"Massive timbers used to form the frame " +
       "of the house. \n");
    
    add_item(({"walls","cedar shingles"}),"The shingles that form " +
       "the outer walls are stunning.\n");

    add_item(("snow"),"A thick blanket of snow covers everything.\n");

    add_item(({"window","windows"}),"Several large bay sized windows " +
       "are distributed evenly throughout the house. A golden light " +
       "can be seen through the glass from the inside.\n");

    add_item(({"roof","slate"}),
       "The recently fallen snow gives you a view of the slate roof " +
       "which has a distinct coloration to them. None of the other slate " +
       "roofs you have seen in the area have the same coloration. " +
       "You can only assume its been shipped in from a distant quarry, " +
       "a sure indicator of the occupants wealth. Four separate chimneys " +
       "ranging in various sizes can be seen about the roof.\n");

    add_item(("path"),"The path has been cleared of snow " +
       "and fresh gravel has been spread to prevent visitors " +
       "from slipping on the ice that frequently forms.\n");


    add_cmd_item(({"window","pane"}),
                 ("break"),
                 ("You cant do that!\n"));


    add_exit(CALATHIN_DIR + "paths/path_w03","southeast",0,1);

    door = clone_object(CALATHIN_DIR + "houses/obj/house4_door");
       door->move(TO);

    reset_room();

}


void
reset_room()
{    
  
    if(!citizen)
    {
       citizen = clone_object(CALATHIN_DIR + "npc/std_citizen");
       citizen->move(TO);
       citizen = clone_object(CALATHIN_DIR + "npc/std_citizen");
       citizen->move(TO);
   
    }
}
