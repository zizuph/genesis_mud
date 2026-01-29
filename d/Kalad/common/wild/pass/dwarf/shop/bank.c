inherit "/d/Kalad/room_std";
inherit "/lib/bank";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/money.h"
#define NUM sizeof(MONEY_TYPES)
object ob1;
/* modified version of the Re Albi Bank in Roke */
   /* by Antharanos */
   /* nicked by korat */
create_room() {
   set_short("The money-changer's shop");
   set_long("All along the western wall, you see a large counter "+
      "with @@bank_owner@@. No doubt this must be the "+
      "local bank in Underhome. Probably all the "+
      "profit from it ends up in the King's pocket "+
      "and from there straight into equipment and payment "+
      "of his armies. A small plaque is attached to the wall.\n");
   add_item("plaque","@@standard_bank_sign");
   add_cmd_item("plaque","read","@@standard_bank_sign");
   add_exit(CPASS(dwarf/shop/m2),"east",0,-1,-1);
   add_prop(ROOM_I_INSIDE,1);
   config_default_trade();
   set_bank_fee(35);
   config_trade_data();
   set_money_give_out(   ({100000,100000,100000,100000}));
   set_money_give_reduce(({     0,     0,     0,     0}));
   set_money_give_max(1000000000);
   clone_object("/d/Genesis/obj/deposit") -> move(this_object());
   ob1 = clone_object(CPASS(dwarf/npc/banker));
   ob1 -> move_living("xxx", TO);
}
init() {
   ::init();
   bank_init();
}
void
bank_hook_minimized(string pay_text, string get_text)
{
   write("You place your coins on the counter, and ask the banker "+
      "to minimize them for you.\n");
   say(QCTNAME(TP) + " places "+ TP->query_possessive() + "coins on the counter.\n");
   tell_room(TO,"The banker starts to count the coins.\n");
   tell_room(TO,"The banker says: Thats was "+ pay_text +
      " and that means you shall have "+ get_text + " back.\n");
   write("The banker hands you the money.\n");
   tell_room(TO,"The banker gives "+QTNAME(TP)+" some money.\n",TP);
   switch(random(4))
   {
      case 0:
         tell_room(TO,"You notice that the banker slides some coins "+
         "quietly into his own purse.\n");
      break;
      default: break;
   }
}
string
bank_owner()
{
   if(objectp(ob1))
      return "a deep dwarf standing behind it counting coins";
   return "no-one behind it";
}
