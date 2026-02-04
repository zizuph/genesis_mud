/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 *
 * Dwarven Stronghold
 * Tomas  -- Jan. 2000
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>

inherit STDROOM;
inherit "/d/Terel/std/room_tell.c";

init()
{
    ::init();
    start_room_tells();
}


public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("Holy cave");
    set_long("Before you is an altar, dedicated to the Dwarven " +
       "God, Mahal. The altar is made of solid rock and is " +
       "ornamented with mithril. Several candles burn from candleholders " +
       "and candelabra about the room.\n");

    add_item(({"candelabra","candleholder","candleholders",
               "candle","candles"}),
               "Several candles burn within silver plated " +
               "candelabra and from candleholders placed about " +
               "the altar.\n");

    add_item(("altar"),"The altar is made of solid stone ornamented " +
       "in mithril inlay. It looks quite impressive!\n");

    add_item(({"ceiling","walls","wall"}),
       "The ceiling and walls are carved from solid stone. Several " +
       "candles hang from candelabra on the walls.\n");

    add_item(("stone"),"The entire room including the altar is made " +
       "of stone.\n");

    add_exit(MOUNTAIN_DIR + "stronghld/fortf","south",0,1);
    
    add_cmd_item(({"altar","mahal"}),({"pray"}),"@@altar");
    add_cmd_item(({"candle"}),({"take","get"}),
       "You reach out to steal a candle from its sacred resting place " +
       "then suddenly feel something that you have never felt before, " +
       "but probably should have: shame.. You put it back.\n");

    set_tell_time(200 + random(200));
    add_tell("You get a strange feeling that you are not " +
       "alone as the flames from the candles flicker in unison..\n");

    reset_room();

}


altar()
{
  if(TP->query_race_name() != "dwarf")
  {
     write("You pray before the great altar of Mahal. " +
        "But feel nothing in return.\n");
     return 1;
  }
     write("You feel your faith strengthened as you perform " +
         "your duties to Mahal.\n");
   return 1;
}  
  
