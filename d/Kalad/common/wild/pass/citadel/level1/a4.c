/*
 * Made by Korat
 * may 1996
 *
*/

inherit "/d/Kalad/room_std";
inherit "/d/Kalad/std/shop_list";
#include "/d/Kalad/defs.h"

#define STORE_ROOM "/d/Kalad/common/wild/pass/citadel/level1/store"

object brigand;
object rat1;
object rat2;
object rat3;

void
create_room()
{

   ::create_room();

   /* set up the shop */
   config_default_trade();
   set_money_greed_sell(130);
   set_money_greed_buy(130);
   set_money_give_max(1000);
   set_money_give_out(({10000, 500, 10, 2}));
   set_money_give_reduce(({0, 4, 20, 15}));
   set_store_room(STORE_ROOM);

   set_short("dwarven Citadel");
   set_long("You are inside an ancient citadel, long abandoned "+
      "by their masters and makers, the deep dwarves. "+
      "Even though the citadel has clear marks of decay from "+
      "the centuries of abandonment, the masonry is of such "+
      "quality that you still have problems finding the "+
      "cracks inbetween the stoneblocks. "+
      "This room has just one exit to the west, "+
      "and contains not much of interest except some large "+
       "barrels in the northeastern corner. You see a sign hanging "+
      "on one of them.\n");
   add_item("sign","It looks like the signs you have seen in "+
      "shops all over the world. It must have been stolen from "+
      "Kalad this one, because you just can't imagine one of the "+
      "ogres able to write.\n");

   add_item(({"barrel","barrels"}),
      "The barrels are stuffed with all kinds of equipment. "+
      "Most of it seems kind of ruined, but here and there "+
      "you see useful things; weapons and armours probably "+
      "looted off corpses at the caravan road.\n");
   add_item(({"cobweb","web","silky network","silky web"}),
      "They are woven, silky networks spun by spiders through "+
      "time. All of them look to be abandoned by their creators, "+
      "much like the citadel itself; left alone to slowly be "+
      "grinned down by the sand carried along with the wind.\n");
   add_item(({"wall","walls","ceiling","roof"}),
      "Both the walls and the ceiling looks to be made by "+
      "brilliant craftsmen. This citadel was made to last ... "+
      "for thousands of years.\n");
   add_item("floor","The floor is covered with fine-grained, white "+
      "sand that must have been carried in here with the wind from the "+
      "great Kaladian waste.\n");
   add_item("citadel","The citadel you are inside is a masterpiece "+
      "of construction. Time has managed to mark it with signs of age, "+
      "but that only mystifies it more than its centuries of abandonment "+
      "manages to do alone.\n");

   /* gives random darkness descriptions. 'A dark room' is so boring. */
   add_prop(ROOM_S_DARK_LONG,"@@dark_description");

   add_exit(CPASS(citadel/level1/a3),"west",0,-1);
   add_exit(CPASS(citadel/level1/store),"northeast","@@wiz_check",-1,1);
   set_alarm(0.0,0.0,"reset_room");
}

void
init()
{
   ::init();
   init_shop();
}
 
/* only allow wizzes into the storeroom */
int
wiz_check()
{
   if(TP->query_wiz_level())
      return 0;
   write("You walk towards the barrels, look into them and walk back.\n");
   say(QCTNAME(TP)+ " walks towards the barrels, looks into them and returns.\n");
   return 1;
}

reset_room()
{
   if (!objectp(brigand))
   {
      brigand=clone_object("/d/Kalad/common/wild/pass/citadel/npc/ogre_salesman");
      brigand->arm_me();
      brigand->move_living("M",TO);
      brigand->command("emote grins greedily.");
   }
   if (!objectp(rat1))
   {
      rat1=clone_object("/d/Kalad/common/wild/pass/citadel/npc/rat");
      rat1->move_living("M",TO);
   }
   if (!objectp(rat2))
   {
      rat2=clone_object("/d/Kalad/common/wild/pass/citadel/npc/rat");
      rat2->move_living("M",TO);
   }
   if (!objectp(rat3))
   {
      rat3=clone_object("/d/Kalad/common/wild/pass/citadel/npc/rat");
      rat3->move_living("M",TO);
      rat1->team_join(rat2);
      rat1->team_join(rat3);
   }   
}

/* returns a random darkroom description */
dark_description()
{
   string desc;
   switch (random(5))
   {
      case 0:
         desc = "You find yourself inside utter darkness.\n";
         break;
      case 1:
         desc = "A weak and chilling wind is all breaks the darkness.\n";
         break;
      case 2:
         desc = "You think you hear some sounds in front of you, but "+
                "without vision you cannot know what it comes from.\n";
         break;
      case 3:
         desc = "A dark room that envelopes you like a cloak of death.\n";
         break;
      case 4:
         desc = "You touch the wall to make sure you walk in the right "+
                "direction.\n";
         break;
      default: break;
   }
   
   return desc;
}
