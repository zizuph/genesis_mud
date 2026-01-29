/*Created by Stevenson*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

object sign;

void 
reset_icewall_room() 
{
   if (!sign) 
      {
      sign = clone_object(ICE_CAST_O+"kender_sign");
      sign->move(TO);
   }
}

void 
enter_inv(object who, object from) 
{
   set_alarm(2.0,0.0,"kender_quest",who);
   ::enter_inv(who, from);
}

void 
kender_quest(object who) 
{
   object box;
   int sum;
   
   if (who->test_bit("Krynn",2,19)) return; /* already did quest */
   if ((box = P("kender_box",who)) && P("kender_spirit",box))
      {
      box->remove_object();
      write("You hear a loud squawk from above.\n\n"
         + "A very large bird swoops down and snatches "
         + "the nice box from your inventory.\n"
         + "As it flies away, an apparition "
         + "of the deceased kender appears before you "
         + "and says: Thank you.\n"
         + "You feel more experienced.\n");
      say("A large bird swoops down and steals something from "
         + QTNAME(who) + ".\n");
      /* add the experience and set the quest bit */
      who->set_bit(2,19);
      if (who->query_average_stat() > 100)
         sum = KENDER_EXP / 4;
      else sum = KENDER_EXP;
      who->add_exp(sum, 0);
      
      K_QUEST_LOG("quest", "Icewall Kender quest", who, sum);
   }
}

void 
create_icewall_room() 
{
   set_short("Mountain Cliff");
   set_long("You are standing on a cliff which overlooks the entire valley. "
      + "Far to the west you see a large mansion. North is a vast plain "
      + "and immediately to the west is the forest.\n");
   
   add_item("valley","It is the Valley of Icewall.\n");
   add_item("forest","It looks quite dense in places "
      + "and is covered with snow.\n");
   add_cmd_item("sign","read","Just examine it.\n");
   add_item("plain","The plains are spread out at the northern "
      + "end of the valley. "
      + "Occasionally you can detect movement.\n");
   add_item("cliff","You are on cliff situated such that it "
      + "overlooks much of Icewall.\n");
   add_item("mansion","It is the house you saw after going down "
      + "from the griffon landing.\n");
   
   add_exit(ICE_FOREST+"forest_12","down","@@climb");
   seteuid(getuid());
   reset_icewall_room();
}

int
climb() 
{
   write("You climb back down carefully, using the footholds.\n");
   return 0;
}
