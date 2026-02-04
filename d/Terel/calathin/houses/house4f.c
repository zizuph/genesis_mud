/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house4f.c
 * Calathin external house.
 * 09/30/1999 -- TOMAS
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include "/d/Terel/include/herb_arrs.h"
#include <stdproperties.h>

inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])

object door;
object cook = 0;

public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("kitchen");
    set_long("The kitchen is spotless. Marble countertops " +
       "line up against the east wall next to the door. " +
       "Several pots and pans hang over " +
       "a wood burning stove which is set into the west wall. " +
       "A pantry can be seen to the south. A large cutting table " +
       "sits in the middle of the room.\n");

    add_item(({"countertops","countertop"}),"Wood countertops covered in white marble.\n");
   
    add_item(({"pots","pans"}),"Several iron pots and pans " +
       "hang from hooks above the stove.\n");
  
    add_item(({"wood stove","stove"}),
       "A large wood burning stove made of iron " +
       "rests against the west wall.\n");

    add_item(("pantry"),"The pantry is stocked with various " +
       "meats, cheeses and other various foodstuffs.\n");

    add_item(({"cutting table","table"}),
       "The large cutting table is made of oak. Several kitchen knives " +
       "varying in size are sheathed into slots along the side " +
       "of the table.\n");

    add_item(({"kitchen knives","knives"}),
       "Various kitchen knives can be seen on the cutting table.\n");

    add_item(({"walls", "paneling"}),
       "The walls have been covered with a dark walnut wood stained " +
       "with a slight reddish tint. The trim at the floor and ceiling " +
       "are stained darker to be almost black and have been carved " +
       "with elaborate patterns. A piece of trim also circles around the " +
       "room at waist level it too is stained a darked color. Eight crystal " +
       "lamps, two to a wall are evenly spaced around the room. In three of " +
       "the walls is a niche containing a statue, the fourth wall is dominated " +
       "by a large fireplace.\n");


    set_up_herbs( ({ ONE_OF_LIST(SPICE_HERBS),
                     ONE_OF_LIST(SPICE_HERBS),
                     ONE_OF_LIST(SPICE_HERBS),
                  }),
                  ({"pantry"}) , 
                   3 );



    
    add_exit(CALATHIN_DIR + "houses/house4d","east",0,1);
 
   
    door = clone_object(CALATHIN_DIR + "houses/obj/house4f_door");
       door->move(TO);


    reset_room();

}

void
reset_room()
{    
  
    if(!cook)
    {
       cook = clone_object(CALATHIN_DIR + "houses/npc/cook");
       cook->move(TO);
   
    }
}

