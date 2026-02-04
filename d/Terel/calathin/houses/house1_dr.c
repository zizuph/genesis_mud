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


inherit STDROOM;
object hutch;

#include <stdproperties.h>


public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("dining room");
    set_long("The dining room contains a round table placed " +
       "in the middle of the room. There are four wooden chairs " +
       "placed around the table. Against the east wall is a small " +
       "china hutch. To the east is the kitchen, south leads back " +
       "to the living room.\n");

    add_item(({"round table","table"}),"The dining room table is " +
       "bare except for a single candlestick holder located " +
       "in the center.\n");

    add_item(({"wooden chairs","chairs"}),"The dining room chairs " +
       "match the decor of the dining room. You see nothing else " +
       "interesting about them.\n");

    add_item(({"china hutch","hutch"}),"The hutch is made of wood. " +
       "There are two doors that open outwards exposing the interior " +
       "of the cabinet. There are various decorative carvings " +
       "on the doors.\n");
    add_item(("candlestick"),"The candlestick is used to hold candles.\n");

   
    add_cmd_item(({"hutch","china hutch","china cabinet","cabinet"}),
                 ("open"),
                 ("Some plates sit on the shelves inside the cabinet. You " +
                  "see nothing else of interest and close the doors.\n"));
    add_cmd_item(({"wooden chair","chair"}), 
                 ("sit"),
                 ("You pause to sit down on the dining room chair but decide " +
       "to move on.\n"));
    add_cmd_item("candle","remove","The candles are stuck firmly to the candlesticks " +
       "you are unable to remove them.\n");
    add_cmd_item(("candlestick"),"get","Removing the candlesticks are out of the question.\n");

    add_exit(CALATHIN_DIR + "houses/house1_kitchen","east",0,1);
    add_exit(CALATHIN_DIR + "houses/house1_lr","south",0,1);

    reset_room();

}


