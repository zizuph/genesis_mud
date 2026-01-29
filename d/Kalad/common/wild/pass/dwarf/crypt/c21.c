inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Within the dwarven city of Underhome");
   set_long("You have entered an old crypt of stone. The first thing "+
      "you notice is an acidious smell drifting towards you from "+
      "the south, carrying with it a chill that penetrates through "+
      "your clothes. You shiver. It seems to come from a dark area "+
      "further south where your lightsource doesn't manage to penetrate. "+
      "At the borders of the circle of light, you see the crypt widen out "+
      "to the southwest, south and southeast. But you think it might be "+
      "wiser to leave this place of death through the portal north.\n");
   add_item(({"tombstone","tombstones","stones","pillars","pillar","rubble"}),
      "Just a few hole stones can be seen but the letters on them are "+
      "unreadable. Except from them the rest are cracked and ruined "+
      "after decades of decay.\n");
   add_item(({"yard","graveyard"}),"You know the old graveyard, "+
      "dating back to the terrible wars of ancient times when the dwarves "+
      "lost so many of their men in violent combat is to the north.\n");
   add_item(({"circle","circle of light","light"}),"It is the area "+
      "your lightsource manage to fight off the everlasting darkness "+
      "down here.\n");
   add_item(({"smell","acidious smell"}),"The smell seems to come from "+
      "the southern area.\n");
   add_item(({"dark area","area"}),"The dark area is out of vision, so "+
      "all you really know about it is the chilling and acidious smell "+
      "the draft carries with it from there.\n");
   add_item("crypt","It is an old stone building, probably housing a long dead "+
      "hero or a lucky dwarf that found a gold-rich vein. The place gives you "+
      "a creepy feeling though.\n");
   add_exit(CPASS(dwarf/g7),"north");
   add_exit(CPASS(dwarf/crypt/c22),"southwest",0,-1,-1);
   add_exit(CPASS(dwarf/crypt/c23),"south",0,-1,-1);
   add_exit(CPASS(dwarf/crypt/c24),"southeast",0,-1,-1);
   
   set_noshow_obvious(1);
}
