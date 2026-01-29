/* Modified by Morrigan, 12 July 2002 to include a merc poster */

#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "vill_road.h"

#pragma save_binary

inherit ELFROOM;

#define WEST     ROOMDIR + "vill_road_8"
#define DOWN     ROOMDIR + "vill_board_common"


#define NAT_SHORT "In the bulletin board building"
#define FOR_SHORT "In a small gazebo"

#define NAT_LONG \
  "You are in a small wooden building, consisting of " + \
  "an octagonal roof on eight " + \
  "pillars. It has many gingerbread wood-carvings patterned after flowers " + \
  "and leaves, and it looks mostly like a gazebo, protecting more from " + \
  "rain and sun than from wind.\n"
#define FOR_LONG NAT_LONG


#define CARVING_ITEM ({"gingerbread", "wood-carvings", "carvings"})
#define CARVING_DESC \
  "The carvings look like stylizised flowers and leaves.\n"

#define PILLAR_ITEM ({"pillar", "pillars"})
#define PILLAR_DESC \
  "The pillars are eight in number and made of wood.\n"

#define ROOF_ITEM ({"roof", "cieling"})
#define ROOF_DESC \
  "The roof is octagonal, made of wood and lined with gingerbread " + \
  "wood-carvings around the edges.\n"
  
create_room()
{
  set_short(N_KNOW(NAT_SHORT, FOR_SHORT));
  set_long( N_KNOW(WRAP(NAT_LONG),
		   WRAP(FOR_LONG)));

  add_item(CARVING_ITEM, WRAP(CARVING_DESC));
  add_item( PILLAR_ITEM, WRAP( PILLAR_DESC));
  add_item(   ROOF_ITEM, WRAP(   ROOF_DESC));

  add_prop(ROOM_I_INSIDE, 1);  /* Questionable if it really is inside, 
				*  but it is under roof...
				*/

  add_exit(WEST,      "west", 0);
  add_exit(DOWN,      "down", 0);

  stock();
}


stock()
{
  object obj;
  object poster;

  if (!poster)
  {
    poster = clone_object("/d/Genesis/guilds/merc/obj/merc_poster");
    poster->move(this_object());
  }
  
  if (!present("board", this_object()) &&
      (obj = clone_object("/std/board")) != 0) {
    obj->set_board_name(BBOARDDIR);
    obj->set_num_notes(20);   
    obj->set_anonymous(1);    
    obj->set_silent(0);   
    obj->set_show_lvl(0); 
    obj->set_remove_lvl(0);
    obj->set_remove_str("You somehow failed.");
    obj->move(this_object());
  }
}
