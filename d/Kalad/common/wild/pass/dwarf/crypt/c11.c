inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Within the dwarven city of Underhome, a crypt");
   set_long("This vault both looks and feels dead, empty and forgotten. "+
      "The arching ceiling almost crushes you with its silence as it wraps itself "+
      "above you like the lid of a closed sarcophagus; A burrial place with "+
      "fresh and living blood within it. @@undead@@ "+
      "In passing you notice the dust settling down around you, "+
      "covering the footprints you have made.\n");
   add_item(({"dust","footprints"}),"@@dwarf@@");
   add_item("ceiling","The ceiling looks very solid, being made of "+
      "granite. This crypt must have been cut out from solid rock and "+
      "polished down with skilled hands.\n");
   add_item(({"yard","graveyard"}),"You know the old graveyard, "+
      "dating back to the terrible wars of ancient times when the dwarves "+
      "lost so many of their men in violent combat is to the north.\n");
   add_item(({"circle","circle of light","light"}),"It is the area "+
      "your lightsource manage to fight off the everlasting darkness "+
      "down here.\n");
   add_item(({"dark area","area"}),"The dark area is out of vision, so "+
      "all you really know about it is the chilling and acidious smell "+
      "the draft carries with it from there.\n");
   add_item("crypt","It is an old stone building, probably housing a long dead "+
      "hero or a lucky dwarf that found a gold-rich vein. "+
      "It is empty though, probably robbed of its riches ages ago.\n");
   add_item("crystal","@@crystal@@");
   add_exit(CPASS(dwarf/crypt/c12.c),"up");
   
}

string
crystal()
{
   if (TP->query_race() == "dwarf")
      return "It is a small crystal, firmly attached to the floor.\n";
   return "You find no crystal here.\n";
}
string
undead()
{
   if(TP->query_prop(LIVE_I_UNDEAD)>0)
      return
   "The atmosphere fills you with a silent peace of mind, "+
   "only to be broken by the stairway upwards that you "+
   "know will lead you out of this chamber that clothes you "+
   "in a veil of darkness, being deprived of life as you are.";
   return
   "The atmosphere fills you with a wish to leave it as "+
   "soon as possible, so you notice the stairway going up "+
   "at once. Maybe you will find a world with the burning "+
   "sun to warm the chill that so sudden entered your body.";
}
string
dwarf()
{
   if (TP->query_race() == "dwarf")
      return "The footprints has made a path from the center "+
   "of the crypt and up the stairway. This puzzles you "+
   "enough to study the center. You see a small crystal in it, attached "+
   "to the floor. You hesitate to touch it, but also feel "+
   "some unknown force making you want to touch it too.\n";
   return 
   "The footprints all go from the center and then "+
   "leaves the crypt up the stairway. But how "+
   "did they get in?\n";
}
init()
{
   ::init();
   add_action("touch","touch");
}
int
touch(string str)
{
   object *team;
   int index, size;
   notify_fail("What?\n");
  if (TP->query_race() == "dwarf")
      {
      notify_fail("Touch what?\n");
      if(!str || str!="crystal") return 0;
      write("You touch the crystal, and suddenly you feel "+
         "yourself dragged through the ceiling and out of the crypt.\n");
      say(QCTNAME(TP)+" touches something on the floor, and dissapears!\n");
      TP->move_living("M",CPASS(citadel/cellar/e6));
      if (size = sizeof(team = TP->query_team()))
         {
         
         /* move the team too */
         index = -1;
         while(++index < size)
         {
            if (environment(team[index]) == TO)
               {
               team[index]->catch_msg("You feel yourself "+
                  "dragged through the ceiling and out of the crypt.\n");
               tell_room(TO,QCTNAME(team[index])+
                  " suddenly dissapears!\n",team[index]);
               team[index]->move_living("M",CPASS(citadel/cellar/e6));
               }
          }
      }
      return 1;
   }
   return 0;
}
