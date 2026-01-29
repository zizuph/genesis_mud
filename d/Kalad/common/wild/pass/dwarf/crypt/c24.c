inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */
object ob1;
object ob2;
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Within the dwarven city of Underhome");
   set_long("You are within an old crypt of stone. The first thing "+
      "you notice is an acidious smell drifting towards you from "+
      "somewhere downwards, carrying with it a chill that penetrates through "+
      "your clothes. You shiver. It seems to come from a dark area "+
      "further down where your lightsource doesn't manage to penetrate "+
      "except to the first steps of a stairway of stone. "+
      "At the borders of the circle of light, you see the crypt narrow "+
      "both to the northwest and downwards.\n");
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
   add_item("stairway","You can see that the first step of it is "+
      "cut out of the mountain itself, and seems to go deep down "+
      "further into the mountain. Maybe to its roots?\n");
   add_exit(CPASS(dwarf/crypt/c21),"northwest",0,-1,-1);
   add_exit(CPASS(dwarf/crypt/c25),"down","@@ghouls",-1,-1);
   
   set_noshow_obvious(1);
   set_alarm(0.0,0.0,"reset_room");
}

reset_room()
{
   if(!objectp(ob1))
      {
      ob1 = clone_object("/d/Kalad/common/wild/pass/dwarf/npc/ghoul");
      ob1 -> move_living("M", TO);
      tell_room(TO,"A creature comes walking out of the shadows.\n");
   }
   if(!objectp(ob2))
      {
      ob2 = clone_object("/d/Kalad/common/wild/pass/dwarf/npc/ghoul");
      ob2 -> move_living("M",TO);
   }
}

ghouls()
{
   if (objectp(ob1) || objectp(ob2))
      {
      if (!CAN_SEE(ob1,TP) && !CAN_SEE(ob2,TP))
         {
         TP->catch_msg("With your heart in your throat you walk past the "+
            "ghouls without being detected!\n");
         return 0;
       }
      ob1->command("say Thouu shall not pass me Aliiive!");
      ob2->command("emote slides between you and the stairway, blocking "+
         "it with its decaying flesh.");
      return 1;
   }
   TP->catch_msg("You carefully decend the stairway, feeling the "+
      "cold breeze in your face.\n");
   return 0;
}