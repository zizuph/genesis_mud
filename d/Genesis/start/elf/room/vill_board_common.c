#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "vill_road.h"

#pragma save_binary

inherit ELFROOM;

#define UP     ROOMDIR + "vill_board"

#define NAT_SHORT "In the cellar of the bulletin board building"
#define FOR_SHORT "In the cellar of a small gazebo"

#define NAT_LONG \
  "You are in a dug-out cellar beneath a small wooden building. Light " + \
  "filters down between the broad planks in the ceiling, and the smell " + \
  "of damp earth from the floor and walls permeates the air. A " + \
  "strange-looking bulletin board sits on one of the pillars that supports " +\
  "the building, and the board is lit by flickering sparks of green " + \
  "light.\n"
#define FOR_LONG NAT_LONG


#define PLANKS_ITEM ({"planks"})
#define PLANKS_DESC \
  "The planks in the roof are wide, and made out of, well, wood.\n"

#define FLOOR_ITEM ({"earth", "floor", "walls", "wall"})
#define FLOOR_DESC \
  "The floor and walls are formed by dark, damp earth.\n"

#define PILLAR_ITEM ({"pillar", "pillars"})
#define PILLAR_DESC \
  "The pillars are eight in number and made of wood.\n"

#define ROOF_ITEM ({"roof", "ceiling"})
#define ROOF_DESC \
  "The roof is octagonal, made of broad, wooden planks.\n"
  
create_room()
{
  set_short(N_KNOW(NAT_SHORT, FOR_SHORT));
  set_long( N_KNOW(WRAP(NAT_LONG),
		   WRAP(FOR_LONG)));

  add_item(  FLOOR_ITEM, WRAP(  FLOOR_DESC));
  add_item( PILLAR_ITEM, WRAP( PILLAR_DESC));
  add_item(   ROOF_ITEM, WRAP(   ROOF_DESC));
  add_item( PLANKS_ITEM, WRAP( PLANKS_DESC));

  add_prop(ROOM_I_INSIDE, 1);  
  
  add_exit(UP, "up", 0);

  stock();
}


stock()
{
  object obj;
  
  if (!present("board", this_object()) &&
      (obj = clone_object("/d/Genesis/obj/board")) != 0) {
    obj->move(this_object());
  }
}