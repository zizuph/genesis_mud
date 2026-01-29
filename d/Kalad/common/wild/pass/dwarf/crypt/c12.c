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
      "down the stairway. You shiver. It seems to come from a dark area "+
      "your clothes. You shiver. It seems to come from a dark area "+
      "below you where your lightsource doesn't manage to penetrate. "+
      "But then again, those tombstones outside this crypt does not "+
      "look much better the way all those shadows plays around them "+
      "at the border of the circle of light.\n");
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
   add_item("crypt","It is an old stone building, probably housing a long dead "+
      "hero or a lucky dwarf that found a gold-rich vein. The place gives you "+
      "a creepy feeling though.\n");
   add_exit(CPASS(dwarf/g3),"east");
   add_exit(CPASS(dwarf/crypt/c11),"down",0,-1,-1);
   
}
