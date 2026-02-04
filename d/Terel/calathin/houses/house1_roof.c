/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house1_roof.c
 *
 * Calathin external house.
 * 10/02/1999 -- TOMAS
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
    INSIDE;
    set_short("roof");
    set_long("You are standing on the roof.\n");

    add_item(("roof"),"The roof is covered in snow. You " +
       "decide that it probably isn't the safest place to be " +
       "right now.\n");
    add_item(("snow"),"The snow blankets the entire area.\n");
    add_item(({"window","ventilation window"}),
       "The window appears to be used to ventilate the house.\n");
   
    add_exit(CALATHIN_DIR + "houses/house1","down",0,1);

    door = clone_object(CALATHIN_DIR + "houses/obj/house1_roof_window");
       door->move(TO);
 
    reset_room();

}