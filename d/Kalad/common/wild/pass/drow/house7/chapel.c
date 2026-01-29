inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   set_short("A chapel devoted to Lolth");
   set_long("A chapel devoted to Lolth.\n"+
      "A smoke and incense-filled octagonal room, a dimly burning brazier "+
      "lies at each side of the room., save for the southern side, where "+
      "a large stone altar lies. The floor has been etched and decorated "+
      "with many intricate runes and glyphs, all wrought from faerie fire. "+
      "At the very center of this chapel is a single, blood-red column of "+
      "light, which rises from the floor and up into the dark ceiling above.\n");
   add_item(({"chapel"}),
      "It is where you are presently located, a location filled with the "+
      "negative emotions so thrived upon by Lolth, the Spider Queen.\n");
   add_item(({"smoke"}),
      "Thin grey clouds of it are visible all over this room.\n");
   add_item(({"dimly burning brazier","burning brazier","brazier"}),
      "A container used to hold the burning incense that fills the room.\n");
   add_item(({"large stone altar","large altar","stone altar","altar"}),
      "A great slab of strange dark rock where even darker stains lie.\n");
   add_item(({"stains","stain"}),
      "Unidentifiable dark spots on the altar.\n");
   add_item(({"floor"}),
      "The ebony-colored floor has been marked with numerous runes and "+
      "glyphs of faerie fire.\n");
   add_item(({"intricate runes","runes","rune","intricate glyphs","glyphs","glyph","faerie fire","fire"}),
      "Twisted, deformed shapes of a very ancient variety unknown to you.\n");
   add_item(({"single column","single light","column","light","blood-red column","blood-red light"}),
      "A five foot wide beam of scarlet energy that rises from the floor "+
      "and through the ceiling above.\n");
   add_item(({"dark ceiling","ceiling"}),
      "The featureless black space above is punctured only by the single, "+
      "blood-red column of light that passes through it.\n");
   add_exit(CPASS(drow/house7/main_hall),"north",0,-1,-1);
   add_exit(CPASS(drow/house7/priest_chamber),"up","@@check",-1,-1);
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/h7_priest2));
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
      tell_room(TO,"A patch of darkness shifts, alerting you to someone's "+
         "presence.\n");
   }
}
check()
{
   object *ob;
   int pres,i;
   ob = FILTER_LIVE(all_inventory(this_room()));
   pres = 0;
   for(i = 0; i < sizeof(ob); i++)
   {
      if(ob[i]->query_name() == "Laele")
         {
         pres = 1;
       }
   }
   if(pres == 1)
      {
      write("The priestess prevents you from stepping into the blood red light!\n");
      say(QCTNAME(TP) + " tries to go up but is prevented by the priestess!\n");
   }
   if(pres != 1)
      {
      write("You step into the blood red light and are transported up.\n");
      say(QCTNAME(TP) + " steps into the blood red light and is transported up.\n");
   }
   return pres;
}
