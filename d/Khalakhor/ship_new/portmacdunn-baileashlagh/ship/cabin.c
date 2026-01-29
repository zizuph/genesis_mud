/* File:          /d/Khalakhor/ship/macdunn/ashlagh/cabin.c
 * Creator:       Zima (copied from Teth)
 * Date:          June 18, 1998
 * Purpose:       The cabin is a room on the MacDunn/Baile-Ashlagh line
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/ashlagh/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:
 */
#pragma save_binary
#pragma strict_types
 
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"
 
#include <stdproperties.h>
#include "/d/Khalakhor/sys/terrains.h"

inherit STDSHIPROOM;

public void create_room()
{
  ::create_shiproom();
  set_short("the cabin of the Aigne Deas");
  set_long("   This is the cabin of the Aigne Deas. Constructed of "+
           "thick oak beams detailed with shining brass, the cabin is "+
           "in great condition though it is sparsely furnished with only "+
           "a bed in the corner and a table and chair in the center, "+
           "all of which are nailed to the floor.\n");
  add_item(({"cabin","quarters","cramped quarters",}),"@@query_long");
  add_item(({"timber","surrounding timber","wall","walls"}),
           "The walls are made of a sturdy timber, that would resist " +
           "any oceanic storm.\n");
  add_item("ceiling","The ceiling is constructed of wooden beams.\n");
  add_item(({"beams","wooden beams"}),"The hefty beams of wood are " +
           "constructed of oak.\n");
  add_item("oak","The oak tree is a typical wood used for ship " +
           "construction.\n");
  add_item("floor","The floor is made of sturdy planks.\n");
  add_item(({"planks","sturdy planks"}),"The sturdy planks appear to " +
           "be constructed of oak.\n");
  add_item(({"walls","wooden walls","wall"}),"Each wall is made of " +
           "oak.\n");
  add_item("bed","The bed is used by the captain of the ship.\n");
  add_cmd_item(({"on bed","down on bed","bed"}),({"lie","rest"}),
               "You rest on the bed for a moment, then stand back up.\n");
  add_item("table","The table is covered with navigational charts, " +
           "and a blob of melted wax.\n");
  add_item(({"charts","navigational charts"}),"They appear to only " +
           "be good for the MacDunn to Baile Ashlagh ship route. One of "+
           "them looks like a map.\n");
  add_cmd_item(({"charts","map","navigational charts"}),({"get","take"}),
               "Taking the charts would only make sense if you were the " +
               "captain of a ship running between MacDunn and Baile Ashlagh!\n");
  add_item("chart","Each chart appears similar. Perhaps looking at all " +
           "the charts may give you a better idea. One looks like a map.\n");
  add_item("deck","The main deck of the ship lies outside the cabin.\n");
  add_item(({"wax","melted wax","blob","blob of melted wax",
             "blob of wax"}),"The blob of melted wax is a combination of " +
           "colours, perhaps from a series of leaking candles.\n");
  add_item("chair","It's just a simple chair in front of the table.\n");
  add_item("map",
           "+---------------------------------------------------------+\n"+
           "|..........   Rhemouth                         . NE       |\n"+
           "|MEIDH........x..            Northeast Sea     .. Isles   |\n"+
           "|...................                             .        |\n"+
           "|.....................                          .         |\n"+
           "|..........SE...........                                  |\n"+
           "|..........SPEIR.........x-Baile Ashlagh      ..x-Kheldour|\n"+
           "|      .................x...               ......         |\n"+
           "|    Port--x..........Ardmaugh..................          |\n"+
           "| MacDunn    ................................             |\n"+
           "|               ..........................    .           |\n"+
           "|                    ...................     ..           |\n"+
           "|  South Sea               .......            . South     |\n"+
           "|                                          ..   Isles     |\n"+
           "+---------------------------------------------------------+\n");
  
  add_exit("deck","deck");
  add_prop(ROOM_I_INSIDE, 1);
  add_prop(ROOM_I_LIGHT, 1);
  add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_INSHIP);
  set_cabin_sound("@@sounds");
  set_is_deck(0);
}

public string
sounds ()
{
    if(random(2))
        return "The ship barrels through the cold waters at top speed.\n";
    return "The ship rises slightly as it slices through a huge wave.\n";
}
