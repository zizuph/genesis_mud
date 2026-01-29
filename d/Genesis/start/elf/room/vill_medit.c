#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "vill_road.h"

#pragma save_binary

inherit ELFROOM;
inherit "/lib/guild_support"; 

object *meditaters;

#define OUT     ROOMDIR + "vill_park_3"

#define NAT_SHORT "In the House of Meditation"
#define FOR_SHORT "In a marble building"

#define NAT_LONG \
"You are in the House of Meditation. Inside it is just a large hall, " + \
  "with a very high ceiling, and high, narrow window-openings. Several " + \
  "doorways lead out to the surrounding park, and through the windows " + \
  "light and the smell of flowers is streaming in.\n" + \
  "This house was built for introspection, and here you can <meditate> " + \
  "to find out your inner strengths and weaknesses, as well as where " + \
  "your priorites lie. The floor is covered by a large, blue carpet, " + \
  "thick and soft, the perfect surface for that purpose.\n"
#define FOR_LONG \
  "You are in a small marble building. Inside it is just a large hall, " + \
  "with a very high ceiling, and high, narrow window-openings. Several " + \
  "doorways lead out, and the floor is covered by a large, blue carpet.\n" 

#define CEILING_ITEM ({"ceiling", "roof", "dome"})
#define CEILING_DESC \
  "The dome-shaped ceiling is sky blue and high above you.\n"

#define WALL_ITEM ({"wall", "walls"})
#define WALL_DESC \
  "The walls are made of white marble, polished to an almost gemlike " + \
  "glossines. With regular intervals, doorways and window-openings break " + \
  "the smooth surface.\n"

#define FLOOR_ITEM ({"floor", "carpet", "blue carpet", "ground"})
#define FLOOR_DESC \
  "The floor is covered by a thick, soft, dark blue carpet, with subtle " + \
  "geometric patterns in slightly lighter blue shades seeming to sink " + \
  "below the surface.\n"

#define WINDOW_ITEM ({"window", "windows", "openings", "window-openings"})
#define WINDOW_DESC \
  "Through the window-openings the green crowns of the surrounding " + \
  "oaks can be seen against the blue sky.\n"

#define DOOR_ITEM ({"door", "doorway", "doors", "doorways" })
#define DOOR_DESC \
  "The open doorways leads out to the surrounding park.\n"
  
create_room()
{
  set_short(N_KNOW(NAT_SHORT, FOR_SHORT));
  set_long( N_KNOW(WRAP(NAT_LONG),
		   WRAP(FOR_LONG)));

  add_item(CEILING_ITEM, WRAP(CEILING_DESC));
  add_item(   WALL_ITEM, WRAP(   WALL_DESC));
  add_item(  FLOOR_ITEM, WRAP(  FLOOR_DESC));
  add_item( WINDOW_ITEM, WRAP( WINDOW_DESC));
  add_item(   DOOR_ITEM, WRAP(   DOOR_DESC)); 

  add_prop(ROOM_I_INSIDE, 1);
  
  add_exit(OUT,      "out", 0);

}

init() 
{
  init_guild_support();
  ::init();
}

void leave_inv(object obj, object destination)
{
  gs_leave_inv(obj, destination);
  ::leave_inv(obj, destination);
}
