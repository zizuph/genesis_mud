inherit "/d/Kalad/room_std";
inherit "/lib/trade";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/red_fang/default.h"
#define NUM sizeof(MONEY_TYPES)
#pragma save_binary
#pragma strict_types

string messages;
int new_mail;

void
create_room()
{
   ::create_room();
   INSIDE;
   set_short("The post-office of the Red Fang");
   set_long("\n   This is the place where you can send messages to "+
   "other people in far away lands. A small hole is in the wall "+
   "where little weasels come and go, delivering mail. "+
   "There is a sign on the wall.\n\n");
   add_item("sign","@@sign");
   add_cmd_item("sign","read","@@sign");
   add_exit(FANG_DIR(rooms/hall),"east",0,-1);
   config_default_trade();
}

string
sign()
{
   return "In this post office you can do the following\n"+
   "read:          Read from the mailbox.\n"+
   "mail <name>:   Mail to <name>.\n"+
   "from:          List all headers.\n"+
   "buy weasel:    Buy a messenger weasel (1 gold).\n";
}

void
init() 
{
    ::init();
    AA(do_buy,buy);
    clone_object("/secure/mail_reader")->move(TP,1);
}

int
do_buy(string str)
{
    string what, for_c, get_c, change;
    int *result, m_res, price;
    NF("Buy what?\n");
    if(str != "weasel")
        return 0;
   price=144; /* 12 silver */
   result=pay(price,this_player(),for_c,0,0,get_c);
   if (sizeof(result)==1) 
      return 0;
   write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
   if (change)
      write("You get " + change + " as change.\n");
   if(!clone_object(FANG_DIR(obj/weasel))->move(TP))
   {    
       write("You get your weasel.\n");
       return 1;
   }
   else
   {
      write("You drop the weasel, its too heavy.\n");
      clone_object(FANG_DIR(obj/weasel))->move(E(TP));
      return 1;
    }
}
    
void
leave_inv(object ob, object to)
{
   object reader;
   ::leave_inv(ob);
   
   reader = present("mailread", ob);
   if (reader) reader->remove_object();
   
}
