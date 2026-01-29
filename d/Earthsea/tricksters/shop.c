#include <cmdparse.h>
#include <macros.h>

#include "defs.h"

inherit TRICKSTER_STD_ROOM;
inherit "/lib/trade";

object keeper;

void create_room()
{
 set_short("An alchemist's shop");
 set_long(BS(
   "You have entered the Alchemist's shop in the Trickster guild hall. "+
   "The room is filled with bubbling noises coming from multi-coloured, "+
   "liquid-filled flasks. There is a counter here where the resident "+
   "alchemist can usually be found sitting behind, serving the needs of "+
   "the Tricksters, when they come by and pay him a visit. Torches cast "+
   "long shadows in the room, giving it an unsettling presence.  There "+
   "is a sign against the counter providing some instructions.\n"));

 add_item("flasks","You wonder in amazement what strange potions these "+
   "flasks could contain. If the have the power make you grow, or "+
   "shrink or possibly the power to turn you into a newt!\n");
 add_item("counter","On this counter lies various alchemical devices "+
   "used for making the tools of mischief that the alchemist hands out "+
   "to the Tricksters, for a price of course.\n");
 add_item(({"torch","torches"}),"The torches cast a sinister shadow in "+
   "the room, along with the strange noises coming from the bubbling "+
   "flasks, the entire room gives you a queer feeling.\n");
 add_item("sign","Read it silly.\n");
 add_cmd_item("sign","read",
   "Welcome to the Tricksters Alchemy Shop!\n\n"+
   "This is where you can receive the various Trickster\n"+
   "Mischief from Rumple the alchemist, for a price of course.\n\n"+
   "You will receive these objects in this order if you are\n"+
   "tricky enough to get your hands on them.\n\n"+
   "        Sneezepowder    Itchingpowder   Smokebomb\n"+
   "        Stinksplash liquid      and     Laughing gas.\n"+
   "You can only have a maximum of 4 of each type at one time.\n\n"+
   "Disguise material can also be purchased here as well.\n\n"+
   "        To use this shop type: <outfit stick/kit>\n\n"+
   "You can also <recover> stick , kit and rumel here.\n"+
   "Or you can <change rumel> if you think you deserve a new one.\n");
 
 add_exit(TRICKSTERS+"hall","west");
 reset_room();
 config_default_trade();
}

void init()
{
 ::init();
 add_action("do_outfit","outfit");
 add_action("do_recover","recover");
 add_action("do_change","change");
}

void reset_room()
{
 if(!keeper)
  {
   keeper=clone_object(TRICKSTERS+"npc/shopkeeper");
   keeper->move(TO);
  }
}

int do_outfit(string what)
{
 object o;
 int *max,*now,price,*pay_res;

 NF("Outfit what??\n");
 if(!what || (what!="stick" && what!="kit")) return 0;

 NF("There is no shopkeeper here!\n");
 if(!keeper) return 0;

 if(what=="stick")
  {
   max=TP->query_max_stick();
   o=present(STICK_DESC,TP);
   NF("But you don't have stick! You'd better go and recover it!\n");
   if(!o) return 0;

   now=o->get_contents();
   price=(max[0]-now[0])*25+(max[1]-now[1])*50+(max[2]-now[2])*100+
         (max[3]-now[3])*200+(max[4]-now[4])*400;
  }

 if(what=="kit")
  {
   o=present(KIT_DESC,TP);
   NF("But you don't have kit! You'd better go and recover it!\n");
   if(!o) return 0;

   price=(TP->query_max_kit()-o->get_contents())*500;
  }

 if(price==0)
  {
   keeper->command("bonk "+TP->query_real_name());
   keeper->command("say Quit wasting my time!! Your "+what+" does not "+
     "need more outfitting! Now leave me alone!");
   return 1;
  }

 pay_res=pay(price,TP,0,1,0,0,0);
 if(pay_res[0]==3)
  {
   keeper->command("tlaugh");
   keeper->command("say Nice try...  But you can't pull that one on me!");
   keeper->command(sprintf("say You need %d copper coins if you want "+
     "me to outfit your %s.",price,what));
   return 1;
  } 

 pay(price,TP,0,0,0,0,0);
 write(sprintf("You pay the alchemist %d copper coins.\n",price));
 if(what=="stick")
  {
   write(keeper->query_The_name(TP)+" quicky grabs your stick from "+
     "your hand, he then starts to tinker with it, adding various "+
     "things. He then promptly returns your stick to you, having "+
     "completed his work.\n");
   say(QTNAME(keeper)+" quicky grabs stick from "+QTPNAME(TP)+
     " hand, he then starts to tinker with it, adding various things. "+
     "He then promptly returns "+POS(TP)+" stick to "+OBJ(TP)+
     ", having completed his work.\n");
   keeper->command("say I wish I could see the face of who you play "+
     "these tricks on.");
   keeper->command("pout");
  }
 if(what=="kit")
  {
   keeper->command("tgrin");
   keeper->command("say Here you go "+TP->query_nonmet_name()+
     ", hope you enjoy yourself and fool all the crusaders!!");
  }

 o->outfit();
 return 1;
}

int do_recover(string what)
{
 object ob;
 string name;

 switch(what)
  {
   case "stick": name="_trickster_stick_";break;
   case "kit": name="_trickster_kit_"; break;
   case "rumel": name="_trickster_rumel_"; break;
   default: name="nothing";
  }

 if(name=="nothing") 
  {
   keeper->command("poke "+TP->query_real_name()+" nose");
   keeper->command("say Say what?? Recover what ?!?");
   keeper->command("peer angr "+TP->query_real_name());
   return 1;
  }

 if(present(name,TP))
  {
   keeper->command("bonk "+TP->query_real_name());
   keeper->command("say You already have your "+what+"!");
   return 1;
  }

 if((SERVER)->query_punished(TP->query_name()))
  {
   keeper->command("tlaugh "+TP->query_real_name());
   keeper->command("say You have been punished by Council!");
   keeper->command("say Trying to fool me?");
   keeper->command("growl "+TP->query_real_name());
   return 1;
  }

 ob=clone_object(TRICKSTERS+"obj/"+what);
 ob->move(TP);
 keeper->command("say here ya go , "+TP->query_the_name(keeper)+"!");
 write(keeper->query_The_name(TP)+" hands you new "+what+".\n");
 say(QCTNAME(keeper)+" hands new "+what+" to "+QTNAME(TP)+".\n");
 keeper->command("tup "+TP->query_real_name());
 return 1;
}

int do_change(string what)
{
 object rumel;

 if(!what || what!="rumel")
  {
   keeper->command("poke "+TP->query_real_name()+" eye");
   keeper->command("say Say what?!? Change what?? Rumel maybe??");
   keeper->command("tpeer");
   return 1;
  }

 rumel=present(RUMEL_DESC,TP);
 if(!rumel)
  {
   keeper->command("peer "+TP->query_real_name());
   keeper->command("say But you don't have any rumel!");
   keeper->command("bonk "+TP->query_real_name());
   keeper->command("say Recover it first before you bother me!");
   return 1;
  }

 if(TP->query_rumel_color()==rumel->get_color())
  {
   keeper->command("tlaugh");
   keeper->command("say Don't try to fool me!");
   keeper->command("say You don't deserve new rumel yet!");
   keeper->command("tdown "+TP->query_real_name());
   return 1;
  }

 keeper->command("congrat "+TP->query_real_name());
 keeper->command("say Here you go , "+TP->query_name()+" , brand new "+
   "rumel!");
 write(QTN(keeper,TP)+" takes your "+rumel->get_color()+" rumel and "+
   "gives you brand new "+TP->query_rumel_color()+" rumel.\n");
 say(QCTNAME(keeper)+" takes "+QTPNAME(TP)+" "+rumel->get_color()+
   " rumel and gives "+OBJ(TP)+" brand new "+TP->query_rumel_color()+
   " rumel.\n");
 keeper->command("tup "+TP->query_real_name());
 rumel->update_level();

 return 1;
}

void greet(object ob)
{
 keeper->command("meet "+ob->query_real_name());
}

void enter_inv(object ob,object from)
{
 ::enter_inv(ob,from);
 set_alarm(0.5,0.0,&greet(ob));
}

