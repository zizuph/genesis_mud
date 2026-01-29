#include "defs.h"

inherit PARTY_BASE;
inherit "/lib/trade";

#include <money.h>

#define PIGEON       "/d/Genesis/start/hobbit/v/pigeon"
#define PIGEON_VALUE  24
#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

void
create_party_room()
{
    add_prop(ROOM_S_MAP_FILE, "party.txt");

   set_short("A small, quiet tent");
   set_long("This tent is serving as a post office, so that party goers "+
      "may send messages to other persons in the lands of Genesis or read them "+
      "if they should get any during the party.  Within the tent the cooing "+
      "of pigeons can be heard, and you notice a small wooden sign posted "+
      "against the side of the tent.  North leads you to a grand pavilion "+
      "where the main party activities take place, to the northeast the booming "+
      "sounds of fireworks can be heard and mouth-watering smells waft from "+
      "the northwest.\n");
   
   add_item( "tent", 
"This tent is made of white canvas, and appears to be kept immaculately "+
"clean. It doesn't really have flaps, per se: the entire north wall "+
"is open for people to pass in and out.\n");
   add_item("sign","Perhaps you should read it?\n");
   
   add_cmd_item("sign","read","@@sign@@");
   
   add_prop(ROOM_I_INSIDE,1);
   
   add_exit(PARTY_DIR+"podium","north");
   add_exit(PARTY_DIR+"field","northeast");
   add_exit(PARTY_DIR+"dinner","northwest");
   
   config_default_trade();  /* Set up the trading system */
   /* Copper Silver Gold Platinum  */
   set_money_give_out(   ({ 10000,    32,   2,    1 })); /* Max_pay   */
   set_money_give_reduce(({     0,     4,   2,    1 })); /* Threshold */
}

string
sign()
{
   return "**************************\n"+
   "**   Pigeons for hire.  **\n"+
   "**          "+PIGEON_VALUE+" cc       **\n"+
   "**************************\n\n";
}
void
init()
{
   ::init();
   add_action("do_hire","hire");
}

//  Hire command taken from /d/Genesis/start/hobbit/v/p_house.c
int
do_hire(string str)
{
   object pigeon;
   string item_name, pay_type, get_type, coin_pay_text, coin_get_text;
   int *money_arr;
   
   
   if (sscanf(str, "%s for %s and get %s",item_name,pay_type,get_type) != 3)
      {
      get_type = "";
      /* Hmmm... Maybe he only wishes to pay with a certain type */
      if (sscanf(str, "%s for %s", item_name, pay_type) != 2)
         {
         pay_type = "";  
         item_name = str;
       }
   }
   if (!(item_name == "pigeon" || item_name == "carrier pigeon"))
      {
      write("Hire what?\n");
      return 1;
   }
   if (sizeof(money_arr = pay(PIGEON_VALUE,TP,pay_type,0,0,get_type)) == 1)
      {
      write("You are unable to pay for the pigeon.\n");
      return 1;
   }
   /* Okay, the pigeon is paid for, now give it to the player */   
   setuid(); seteuid(getuid());
   pigeon = clone_object(PIGEON);
   if(pigeon->move(TP))
      {
      write("You cannot carry that much!\n");
      pigeon->move(ENV(TP));
      return 1;
   }
   coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
   coin_get_text = text(exclude_array(money_arr, 0, NUM-1));     
   
   write("You pay " +coin_pay_text+ " and hire yourself a pigeon.\n");
   if (coin_get_text)  
      write("You get " + coin_get_text + " back.\n");
   say(QCTNAME(TP) + " hires " + HIM_HER(TP) 
      + "self a carrier pigeon.\n");
   return 1;   
}

void
enter_inv(object ob,object from)
{
   ::enter_inv(ob,from);
   if (!interactive(ob))
      return;
   if (!present("_reader_",ob))
      clone_object("/secure/mail_reader")->move(ob,1);
}

void
leave_inv(object ob,object to)
{
   object reader;
   
   ::leave_inv(ob,to);
   //   We don't take readers away from Wizards
   if (ob->query_wiz_level())
      return;
   if (reader =  present("_reader_",ob))
      reader->remove_object();
}
