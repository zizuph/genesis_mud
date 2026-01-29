inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Within the dwarven city of Underhome");
   set_long("You seem to be at something that once was a small "+
      "plaza situated inbetween several temples that now has "+
      "suffered the destiny of destruction and pillaging. To "+
      "the north you can see the outline of such a ruin "+
      "and you still remember another one further northwestwards. "+
      "Your lightsource doesn't reach far enough eastwards, "+
      "but you suspect to find another one in that direction. "+
      "From here you can walk both to the northeast and northwest, "+
      "making a turn around "+
      "some ruins in the center of this old plaza.\n");
   add_item(({"temple","temples","temple ruin","temple ruins"}),
      "Just a few whole stones can be seen of the northern one, making "+
      "fairly unaccessable. You suspect to find another one further east.\n");
   add_item("plaza","The plaza seems to be surrounded by old temple-ruins, "+
      "and is fairly deserted for life. In the center you see yet more "+
      "cracked stone-blocks that once might have been a statue or monument.\n");
   add_item(({"path","street","streets"}),"Among all the rubble you can "+
      "walk along a small trodden path that the dwarven boots has "+
      "managed to clear.\n");
   add_item(({"monument","statue"}),
      "Among all the cracked stone-blocks you can see something resembling "+
      "a body wearing an armour in stone.\n");
   add_item(({"body","armour in stone","armour"}),
      "It is all cracked up and partly covered in greyish moss. "+
      "The armour has been masoned to resemble a platemail with several "+
      "ornated decorations.\n");
   add_item(({"decorations","decoration","platemail","ornated platemail","ornated decorations"}),
      "It has been smoothed out during time."+
      " You do "+
      "understand that when this statue once was new, it was "+
      "a work of art. But that must be decades ago.\n");      
   add_exit(CPASS(dwarf/temple/t1),"northwest");
   add_exit(CPASS(dwarf/temple/t3),"northeast");

   set_noshow_obvious(1);
}
