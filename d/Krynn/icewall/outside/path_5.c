/* Put A White Dragon Here
Have Two separate room descriptions based
on the presence or absence of the dragon.
*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

string room_desc;
object dragon, corpse;

reset_icewall_room() {
   if (!corpse) {
      corpse = clone_object(ICE_CAST_O+"corpse");
      corpse->move(TO);
   }
   if (!dragon) {
      dragon = clone_object(KRNPC + "sleet");
      dragon->move(TO);
   }
}

create_icewall_room() {
   set_short("Wide, flat path");
   set_long("@@here");
   
   add_item("snow","It makes Icewall white.\n");
   add_item("plains","They are north of here somewhere.\n");
   add_item("tracks","They are dragon tracks.\n");
   add_item("path","It shows the signs of a struggle.\n");
   add_exit(ICE_OUT+"path_4","southwest");
   add_exit(ICE_OUT + "path_6", "east");
   
   add_item("shadow","The moving shadow is rather large and could "
      + "be made by only one thing... a dragon.\n");
   add_cmd_item("up","look","You see a large shape hovering above you.\n");
   add_item("sky","Why not look up?\n");
   add_item("shape","You better run before it decides to land.\n");
   
   reset_icewall_room();
}

string here() {
   if (P("dragon",TO) && dragon)
      room_desc =
   "You work your way along the path and feel a sudden "
   + "sense of dread course through your limbs. Directly in "
   + "front of you is a very large dragon which is feeding "
   + "on a corpse. She doesn't seem to notice you which might "
   + "be very fortunate.";
   
   else room_desc =
      "You are on a path which seems heavily trampled upon. On "
   + "the ground are tracks and signs of a struggle. There is "
   + "a fresh corpse here and a strange shadow on the ground "
   + "which seems to be moving...";
   
   room_desc = room_desc + "\n";
   
   return room_desc;
}

