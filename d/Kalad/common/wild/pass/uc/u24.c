inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
#define KG "/d/Kalad/common/wild/pass/uc/npc/kob_guard"
object ob1;
object ob2;
object ob3;
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A large chamber");
   set_long("You are inside of a large chamber.\n"+
      "Stone as black as the hopes of murdered men lies in every conceivable direction, "+
      "enclosing you in its cold and unyielding embrace. Vague thoughts of "+
      "the thousands of tons of rock overhead leaves you somewhat weak and "+
      "weary. Littered about the chamber are numerous piles of bones, aside "+
      "which are mounds of feces. At the far end lies a white throne, "+
      "beside which is a giant boulder.\n"+
      "A passage leads to the southwest.\n");
   add_item(({"large chamber","chamber"}),
      "A great, hollowed-out area of the surrounding rock and stone.\n");
   add_item(({"passage"}),
      "A tunnel located far beneath the realm of light, the realm of the sun.\n");
   add_item(({"stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_item(({"mounds","mound","feces"}),
      "Kobold dung, it is the cause of the horrible smell here.\n");
   add_item(({"piles","pile","bones","bone"}),
      "The horrible remnants of, judging by the size and shape of them, "+
      "gnomes.\n");
   add_item(({"white throne","throne"}),
      "Upon closer inspection you realize your mistake, it is not a throne, "+
      "it is in fact a large collection of skulls in the shape of a throne.\n");
   add_item(({"skulls","skull"}),
      "From the size and shape of them, they appear to be gnomish skulls.\n");
   add_item(({"giant boulder","boulder"}),
      "A five foot wide boulder that stands nearly three feet in height. "+
      "It seems to serve no purpose, other than perhaps as a speaking "+
      "stand.\n");
   add_exit(CPASS(uc/u34),"southwest",0,2,1);
   set_alarm(1.0,0.0,"reset_room");
}
void
init()
{
   ::init();
   AA(stand,stand);
   AA(sit,sit);
}
int
stand(string str)
{
   if(!str || str != "on the boulder")
      {
      NF("Stand where? On the boulder?\n");
      return 0;
   }
   write("You stand on the giant boulder, as if ready to give a speech.\n");
   say(QCTNAME(TP) + " stands on the giant boulder, as if ready to give a speech.\n");
   set_alarm(3.0,0.0,"do_standing");
   return 1;
}
void
do_standing()
{
   if(TP->query_base_stat(SS_DEX) < 50)
      {
      write("You lose your balance and slip from the giant boulder!\n");
      say(QCTNAME(TP) + " loses " + TP->query_possessive() + " balance and "+
         "slips from the giant boulder!\n");
   }
   else
      {
      write("You nearly slip from the giant boulder, but manage to keep your balance.\n");
      say(QCTNAME(TP) + " nearly slips from the giant boulder, but manages to "+
         "keep " + TP->query_possessive() + " balance.\n");
   }
   return;
}
int
sit(string str)
{
   if(!str || str != "in the throne")
      {
      NF("Sit where? In the throne?\n");
      return 0;
   }
   write("You start to sit in the throne but get your rear pierced by "+
      "some sharp bones! You quickly get up!\n");
   say(QCTNAME(TP) + " starts to sit in the throne but gets " + TP->query_possessive() + " rear "+
      "pierced by some sharp bones! " + capitalize(TP->query_pronoun()) + " quickly "+
      "gets up!\n");
   TP->command("scream");
   return 1;
}
void
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(uc/npc/kob_chief));
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(KG);
      ob2 -> arm_me();
      ob2 -> move_living("M",TO);
   }
   if(!ob3)
      {
      ob3 = clone_object(KG);
      ob3 -> arm_me();
      ob3 -> move_living("M",TO);
      ob1 -> team_join(ob2);
      ob1 -> team_join(ob3);
      tell_room(TO,"A large kobold appears from behind the white throne as "+
         "two other smaller kobolds jump out from behind the pile of bones.\n");
   }
}
