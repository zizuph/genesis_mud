/* 
 * /d/Kalad/common/wild/pass/desert/mount/banished2.c
 * Purpose    : This is where the genie of fire ~pass/npc/genie_fire.c, is banished when the player shows the right item
 * Located    : In the mountain desert ~desert/mount/
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,10);
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("Within the elemental plane of Fire");
   set_long("Roaring, twisting and exploding flames fill your vision "+
      "everywhere you turn your gaze, however you feel no heat. It appears as "+
      "if you are trapped within a great air bubble within the elemental "+
      "plane of Fire.\n");
   add_item(({"fire","flames","flame"}),
      "It is all around you and seems to move with a conscious of its own.\n");
}
