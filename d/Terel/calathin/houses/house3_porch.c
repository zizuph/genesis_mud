/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house3a_porch.c
 *
 * Calathin external house.
 * 09/30/1999 -- Tomas
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
    set_short("porch");
    set_long("You stand on the front porch of an abandoned " +
       "house.\n");

    add_exit(CALATHIN_DIR + "houses/house3","south",0,1);
   
    door = clone_object(CALATHIN_DIR + "houses/obj/house3_door");
       door->move(TO);

     reset_room();

}

