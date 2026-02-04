/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house4_sv3.c  servants quarters
 * Calathin external house.
 * 11/17/1999 -- TOMAS
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>

inherit STDROOM;
#include <stdproperties.h>

object door;
object guard;

public void
create_room()
{
    ::create_room();

    set_short("servants quarters");
    set_long("Servants quarters hallway.\n");

    
 
    add_exit(CALATHIN_DIR + "houses/house4_sv2","west",0,1);
    add_exit(CALATHIN_DIR + "houses/house4_sv8","east",0,1);
    
    door = clone_object(CALATHIN_DIR + "houses/obj/house4_sv3_door1");
       door->move(TO);
    door = clone_object(CALATHIN_DIR + "houses/obj/house4_sv3_door2");
       door->move(TO);

    reset_room();

}


void
reset_room()
{
    if(!guard)
    {
       guard = clone_object(CALATHIN_DIR + "houses/npc/house4_guard");
       guard->move(TO);
       guard = clone_object(CALATHIN_DIR + "houses/npc/house4_guard");
       guard->move(TO);
  
    }

}