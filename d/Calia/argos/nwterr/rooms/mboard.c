/*
 * This room contains the temporary board for discussion of the Mystic
 * Memorial (Zima, 3/27/95)
 * Permission given by Keeper Mrpr and AoD Tepisch to make this room
 * a temp start location (Zima, 4/3/95)
 */
inherit "/std/room";
#include <stdproperties.h>
#include "defs.h"
 
/* prototypes */
void    load_board();
 
void create_room() {
   set_short("A forgotten ruin");
   set_long(
      "You are standing in the center of the forgotten ruin of an old "+
      "shrine. Twelve pillars encircle the edges of a large round dias, "+
      "in the center of which rests a stone altar. The surrounding forest "+
      "encroaches the ruin on all sides, threatening to swallow it "+
      "up.\n");
   add_item(({"ruin","shrine"}),
      "It is an ancient structure, crumbling from years of attack by "+
      "weather, forest and time, consisting of a circular dias "+
      "guarded by twelve crumbling pillars centering upon a stone "+
      "altar.\n");
   add_item("pillars",
      "They are tall pillars of crumbling marble enshrouded in "+
      "strangling vines which grow from the surrounding forest "+
      "floor.\n");
   add_item("forest",
      "It is a dense forest of towering oaks and maples, their canopy "+
      "of branches and leaves constructing the only shelter for the "+
      "ruin.\n");
   add_item("dias",
      "It is a large flat stone dias worn smoothe by centuries of "+
      "rain and wind. It is the floor of the shrine.\n");
   add_item("altar",
      "It is a crumbling altar of stone, its rectangular top worn "+
      "smoothe. An emblem has been sculpted into the top of the "+
      "altar which looks to be a very recent addition.\n");
   add_item("emblem",
      "Sculpted onto the top of the altar, it is a four-pointed star "+
      "encompassed by a circle.\n");
 
   /* room properties */
   add_prop(ROOM_I_INSIDE,1);
 
   /* exits */
    add_exit(ROOM_DIR+"sfor3","out",0);
   load_board();
}
 
void load_board() {
    object bb;
    seteuid(getuid(this_object()));
    bb = clone_object(ROOM_DIR+"mboard/board");
    bb->move(this_object());
}
 
int query_prevent_snoop() { return 1; }
 
int start (string where) {
   if (where != "here") return 0;
   this_player()->
      set_default_start_location("/d/Calia/zima/argos/nwterr/rooms/mboard");
   write("Thou shalt enter this world in this forgotten place now.\n");
   return 1;
}
 
void init() {
   ::init();
   add_action("start","start");
}
