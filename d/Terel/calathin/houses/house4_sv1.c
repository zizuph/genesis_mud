/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house4_sv1.c  -- servants/guard house
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

    set_short("servants quarters");
    set_long("The servants quarters is basically spartan. " +
       "To the east is a hallway leading to other rooms.\n");
    INSIDE;

    add_exit(CALATHIN_DIR + "houses/house4_sv2","east",0,1);
    

    door = clone_object(CALATHIN_DIR + "houses/obj/house4_sv1_door2");
       door->move(TO);

    reset_room();

}

