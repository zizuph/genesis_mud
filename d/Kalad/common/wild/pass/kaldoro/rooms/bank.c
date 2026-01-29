/* 
 * /d/Kalad/common/wild/pass/kaldoro/rooms/bank.c
 * Purpose    : The bank of the Village of Kaldoro.
 * Located    : 
 * Created By : Rico 20.Feb.94
 * Modified By: 
 */ 

inherit "/d/Kalad/room_std.c";
inherit "/lib/bank.c";

#include "/d/Kalad/defs.h"

#define NUM sizeof(MONEY_TYPES)

object ob1;
object ob2;
object ob3;

create_room()
{
   set_short("Kaldoro Bank");
   set_long("   You are standing in Kaldoro's one "+
      "and only banking office.  You can take care "+
      "of most of your banking needs here.  There "+
      "is a sign with instructions posted on the "+
      "wall next to the clerk's counter.\n");
   
   add_cmd_item(({ "sign", "instructions" }),
      "read", "@@standard_bank_sign");
   
   config_default_trade();
   config_trade_data();
   
   set_bank_fee(20);  /* Rate charged to customers. */
   
   add_prop(ROOM_I_INSIDE, 1);
   
   set_money_give_out(({   100000,100000,100000,100000}));
   set_money_give_reduce(({     0,     0,     0,     0}));
   set_money_give_max(1000000000);
   
   clone_object("/d/Genesis/obj/deposit") -> move(this_object());
   
   ob1 = clone_object(KALDORO(npc/kleater));
   ob1 -> move_living("xxx", TO);

   ob2 = clone_object(KALDORO(npc/sprokter));
   ob2 -> move_living("xxx", TO);

   ob3 = clone_object(KALDORO(npc/buffy));
   ob3 -> move_living("xxx", TO);
   
   add_exit(KALDORO(rooms/kv25), "northeast");
}

reset_room()
{
   if(!ob1)
   {
      ob1 = clone_object(KALDORO(npc/kleater));
      ob1 -> move_living("xxx", TO);
   }
   if(!ob2)
   {
      ob2 = clone_object(KALDORO(npc/sprokter));
      ob2 -> move_living("xxx", TO);
   }
   if(!ob3)
   {
      ob3 = clone_object(KALDORO(npc/buffy));
      ob3 -> move_living("xxx", TO);
   }
}

init()
{
   ::init();
   bank_init();  /* To add the commands for the bank. */
}
