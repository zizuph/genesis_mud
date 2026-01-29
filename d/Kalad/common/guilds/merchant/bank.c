inherit "/d/Kalad/room_std";
inherit "/lib/bank";
#include "/d/Kalad/defs.h"
#define NUM sizeof(MONEY_TYPES)
object ob1;
create_room()
{
   ::create_room();
   hear_bell = 1;
   INSIDE;
   set_short("Private bank of the Merchants Guild");
   set_long("You are within the private bank of the Merchants Guild of "+
      "Kabal, where only guild members may go to change and deposit their "+
      "earnings. The marble floor has been polished here to a brilliant "+
      "shine, its surface almost like a mirror. A teak counter on the "+
      "western side is lined with gold, its obvious monetary value "+
      "enough to feed dozens of poor families. An entranceway lies to the "+
      "east, heading back to the central hallway of the guild.\n"+
      "A gold-lined plaque hangs over the counter.\n");
   add_item(({"marble floor","floor"}),"Built from an amazingly pure "+
      "white type of marble, the reflective quality of it is quite amazing.\n");
   add_item(({"teak counter","counter"}),"An expensive wooden counter, "+
      "behind which the guild banker works.\n");
   add_item(({"entranceway"}),"An open archway leading to the northeast.\n");
   add_item(({"gold-lined plaque","plaque"}),"@@standard_bank_sign");
   add_cmd_item(({"gold-lined plaque","plaque"}),"read","@@standard_bank_sign");
   config_default_trade();
   set_bank_fee(13);
   config_trade_data();
   set_money_give_out(   ({100000,100000,100000,100000}));
   set_money_give_reduce(({     0,     0,     0,     0}));
   set_money_give_max(1000000000);
   add_exit(CVAN(guild/hall1),"east",0,-1,-1);
   clone_object("/d/Genesis/obj/deposit")->move(TO);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CVAN(guild/banker));
      ob1 -> move_living("M",TO);
      tell_room(TO,"The banker suddenly pops up from behind the counter.\n");
   }
}
init() {
   ::init();
   bank_init();
}
void
bank_hook_minimized(string pay_text, string get_text)
{
   write("You minimize your "+ pay_text+ " and get "+ get_text+ ".\n");
   say(QCTNAME(TP) + " minimized " + TP->query_possessive() + " coins.\n");
}
