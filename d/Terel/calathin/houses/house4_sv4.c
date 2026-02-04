/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house4a.c
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
object servant = 0;

public void
create_room()
{
    ::create_room();

    set_short("servants quarters");
    set_long("Standard servants bedroom. A bunkbed and nightstand " +
       "can be seen against the far wall. To the west is a chest " +
       "of drawers with a washbasin sitting on top.\n");
    INSIDE;

    add_item(("bunkbed"),"Two small wooden beds stacked on each other " +
       "not much more than a pallet.\n");

    add_item(("nightstand"),"A small candle can be seen on the nightstand.\n");

    add_item(({"chest of drawers","drawer","drawers","washbasin"}),
       "The chest of drawers contains typical commoner clothing. " +
       "A ceramic washbasin rests on top of the drawer.\n");
    
    door = clone_object(CALATHIN_DIR + "houses/obj/house4_sv2_door1a");
       door->move(TO);

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

