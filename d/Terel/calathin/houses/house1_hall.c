/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house1_hall.c
 *
 * Calathin external house.
 * 09/30/1999 -- TOMAS
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
    set_short("hallway");
    set_long("The hallway leads east from the living room. There are sconces " +
       "on either side of the hallway.\n");
     
    add_item(("sconces"),"Wall sconces used to hold candles.\n");

    add_exit(CALATHIN_DIR + "houses/house1_lr","west",0,1);


    door = clone_object(CALATHIN_DIR + "houses/obj/house1_bedrm2a_door");
       door->move(TO);
    
    door = clone_object(CALATHIN_DIR + "houses/obj/house1_bedrm1a_door");
       door->move(TO);

    reset_room();
}

