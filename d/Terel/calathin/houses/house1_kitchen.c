/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house1.c
 *
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

object citizen = 0;


public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("kitchen");
    set_long("The kitchen is well kept. Some cabinets are set into the north wall. " +
       "The pantry can be seen to the south and a large wooden table sits in the middle " +
       "of the room.\n");

    add_item(("cabinets"),"The cabinets are made of wood. They contain " +
       "various kitchen related items.\n");
    add_item(("pantry"),"The pantry looks bare, perhaps someone forgot to buy food?\n");
    add_item(("table"),"The table looks like it is designed for preparing food on.\n");

    set_up_herbs( ({ ONE_OF_LIST(SPICE_HERBS),
                     ONE_OF_LIST(SPICE_HERBS),
                     ONE_OF_LIST(SPICE_HERBS),
                  }),
                  ({"pantry"}) , 
                   3 );


    add_exit(CALATHIN_DIR + "houses/house1_dr","west",0,1);

    reset_room();
   
}

void
reset_room()
{    
  
    if(!citizen)
    {
       citizen = clone_object(CALATHIN_DIR + "npc/std_citizen");
       citizen->move(TO);
   
    }
}

