/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house4_sv2.c  servants quarters
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

public void
create_room()
{
    ::create_room();

    set_short("servants quarters");
    set_long("Servants quarters hallway.\n");

    INSIDE;
    
 
    add_exit(CALATHIN_DIR + "houses/house4_sv1","west",0,1);
    add_exit(CALATHIN_DIR + "houses/house4_sv3","east",0,1);
    
    door = clone_object(CALATHIN_DIR + "houses/obj/house4_sv2_door1");
       door->move(TO);
    door = clone_object(CALATHIN_DIR + "houses/obj/house4_sv2_door2");
       door->move(TO);


    reset_room();

}

