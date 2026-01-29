// file name: d/Avenir/common/village/merc/01.c
// creator(s): Lilith June 2004
// last update: Zizuph May 2023
// purpose:   
// note:	
// bug(s):
// to-do:       

#pragma strict_types

#include "../village.h"  
inherit MERC_BASE;

#define SEE_NORTH  ({ MERC + "conn_n"})
#define SEE_SOUTH  ({ MERC + "09"})

public string north_view()
{
  object *inv, *live, room;
  int i;
 
  inv = ({ });
  for(i = 0; i < sizeof(SEE_NORTH); i++)
    if((room = find_object(SEE_NORTH[i])))
      inv += all_inventory(room);
 
  if(sizeof(inv)) 
  {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if(sizeof(live))
       return " Inside the guards quarters is "
          + COMPOSITE_LIVE(live) + ".";
  }
  return "";
}


public string south_view()
{
  object *inv, *live, room;
  int i;
 
  inv = ({ });
  for(i = 0; i < sizeof(SEE_SOUTH); i++)
    if((room = find_object(SEE_SOUTH[i])))
      inv += all_inventory(room);
 
  if(sizeof(inv)) 
  {
    live = FILTER_LIVE(inv);
    live = FILTER_CAN_SEE(live, TP);
    if(sizeof(live))
       return "where you can see "
          + COMPOSITE_LIVE(live) + ".";
  }
  return ".";
}

static void
create_merc_room(void)
{
    set_short("near the north entrance of the Merchantile District");
    set_long("This cobblestone pathway leads north toward the exit "+
    "from the Merchantile District while sloping downward toward a "+
    "bowl-shaped berm which encircles the open-air market at the "+
    "center of the area. There appears to be a main intersection "+
	"just to the south@@south_view@@"+
	
/*	
	"Cobblestone pathways criss-cross here, at the "+
	"north end of the garment district. A sloped lane "+
	"rises north, back towards the bazaar. South stands a fountain "+
	"and the center of this district. Off to the east and west the "+
	"cobbled pathways rise a few steps onto berm earthenworks which "+
	"is fenced in by a stone wall. Stalls run along the face of  "+
	"the wall and are fronted by hawking merchants. The wall and "+
	"and berm are graded off as they make contact with the inclined "+
	"slope and merge into the hedged lane.\n");
*/
    add_item(({"lane", "sloped lane"}), "The lane is an extra-wide path "+
	"of cobbles that slopes uphill out of the merchantile district.\n");
    add_item(({"stall", "stalls", "merchant stall", "merchant stalls",
	"merchant", "merchants"}), "Merchants and their stalls are "+
	"lined up to the east and west, hawking their various garment "+
	"wares.\n");

    add_hedge();

    add_exit("conn_n", "north", 0);
    add_exit(  "09",   "south", 0);

void create_merc_room()
{
    set_short("a room in a pale");
    set_long("This is the long for room 03"+
        " "+
        " "+
        " "+
        " "+
        " "+
        " "+
        ".\n");
       
    add_exit(PALE + "","east", 0);
    add_exit(PALE + "","west", 0);
    add_exit(PALE + "","south", 0);

    add_exit(PALE + "","southeast", 0);
    add_exit(PALE + "","southwest", 0);

    // See base file for functionality
    add_exit_views();

} // create_room()

