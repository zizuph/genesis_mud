/* 
 * /d/Kalad/common/wild/pass/desert/mount/banished1.c
 * Purpose    : There is where the genie of earth ~pass/npc/geneie_earth.c, is banished when the players shows the right item
 * Located    : In the mountain desert ~desert/munt/
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
   add_prop(ROOM_I_LIGHT,-10);
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("Within the elemental plane of Earth");
   set_long("Only darkness can be seen here, for you are trapped within an "+
      "air bubble within the elemental plane of Earth.\n");
   add_item(({"darkness"}),
      "It is dark, so terribly dark.\n");
}
