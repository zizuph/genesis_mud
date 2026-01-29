 // Fisherman      (/d/Avenir/common/bazaar/NPCS/fisherman.c)
 // creator(s):    Glinda may -95
 // last update:
 // purpose:       Has a small quest..Catch him some fish with his net.
 //                Net might be used in other quests too
 // note:      Sells his fish in ~bazaar/extr/str12
 // bug(s):
 // to-do:

// Call_for_help drags killers to the pillory.
inherit "/d/Avenir/common/bazaar/NPCS/call_for_help";
inherit "/d/Avenir/inherit/quest";

#include "../bazaar.h"
#include "/sys/money.h"
#include <language.h>

#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Avenir/include/relation.h"

#define QLOG "/d/Avenir/log/quest/help_fisherman"

int no;
int counting;


create_monster()
{
   ::create_monster();
   set_name("fisherman");
   add_name("man");
   add_adj(({"young"}));
   set_short("young fisherman");
   set_race_name("fisherman");

   default_config_npc(35);
   set_skill(SS_UNARM_COMBAT,30);
   set_skill(SS_DEFENCE,30);
   set_skill(SS_AWARENESS,30);

   set_act_time(1);
   add_act("shout Fish for sale!");
   add_act("shout Only one silver coin!");
   add_act("shout Buy your fish here!");

   add_ask(({"fish","buy","sell","sale","business","money","coin","coins"}),
             "say Just gimme a silver and you'll get a fish!",1);
   add_ask(({"help","quest","task","assignment"}),
             "say The only thing I need is customers!",1);
   set_default_answer("The young fisherman says: I'd rather discuss " +
             "business.\n");

   remove_prop(NPC_M_NO_ACCEPT_GIVE);
   seteuid(getuid());
   enable_reset();
   reset();

}

reset_monster()
{
   object ob;
   object *obs;
   int i=0;

   if( !(present("net",TO)) )
   {
      ob=clone_object( MISC + "net" );
      ob->move(TO);
   }

   //first i remove all the fish since the obs are heaps
   obs=all_inventory(TO);
   while (i < sizeof(obs) )
   {
      if(obs[i]->id("fish"))
         obs[i]->remove_object();
      i++;
   }

   // then i make three new fish
   no=0;
   while( no < 3 )
   {
      ob=clone_object( FOOD + "net_fish" );
      ob->move(TO);
      no++;
   }
}

void
arm_me()
{
   object ob;
   ob = clone_object( WORN + "codpiece" );
   ob->move(TO);
   ob = clone_object( WORN + "pbelt" );
   ob->move(TO);
   command("wear all");
}

public int
special_attack(object who)
{
   if(random(2))
      return 0;
   say("The young fisherman slaps " + QTNAME(who) +
       " over the eyes with a fish!\n");
   write("The young fisherman slaps you over the eyes with a fish!\n");
   who->heal_hp(-random(30));
   return 0;
}


int
count_fish()
{
   object *obs;
   int i;
   int count = 0;

   obs=all_inventory(TO);
   while(i<(sizeof(obs)))
   {
      if( obs[i]->id("fish") )
         count=count + obs[i]->num_heap();
      i++;
   }
   return count;
}


sell_fish(object ob, object from)
{
   if(count_fish())
   {
      command("emote bites the the silver coin.");
      command("smile");
      command("give fish to " + from->QRN);
      no=no-1;
      return 1;
   }
   if(present("net",TO))
   {
      command("say I've run out of fish!");
      command("say Would you do me a favour and go fish some for me?");
      command("say You can use this...");
      command("give net to " + from->QRN);
      write_file(QLOG, from->QRN + " got the fishnet " + ctime(time()) 
              + ".\n");
      return 1;
   }
   else
   {
      command("give silver coin to " + from->QRN);
      command("say I've run out of fish.");
      command("say And the guy who got my net hasn't returned.");
      command("say He was supposed to get me some new fish.");
      command("say Maybe I will have some fish for you later!");
      command("smile hope");
      return 1;
   }
}

void
give_token(object from)
{
    object token;
    string str;

    token = clone_object("/d/Avenir/common/obj/syb_coin");
    token->move(from);
    str = token->short();
    from->catch_msg(QCTNAME(TO) + " digs into a pocket and "+
        "gives you one of his most treasured possessions, " + str + ".\n");
    tell_room(ENV(TO), QCTNAME(TO) + " digs into his pocket "+
        "and gives "+ str +" to " + QTNAME(from) + ".\n", ({ from }));
}

finish_quest(object ob, object from)
{
   no=count_fish();
   if(!(no>(random(10) + 6)))
   {
      command("say Thank you, but that won't keep me in business for long.");
      counting=0;
      return;
   }
   if(!from->query_prop("_has_fished_with_avenir_net"))
   {
      command("say Hey this fish is old.");
      command("say Try catching it yourself next time.");
      counting=0;
      return;
   }
   if(!from->test_bit("Avenir",0,6))
   {
      command("thank " +from->QRN);

      reward_quest("Help Fisherman", from, 0, 6, 1000);

      MONEY_MAKE_CC(random(66))->move(this_object());
      command("give copper coins to " +from->QRN);
      write_file(QLOG, from->QRN + "  " + ctime(time()) +  "   got 1000 "
                + "xp!\n");
      give_token(from);
      counting=0;
      return;
   }
   command("say Thanks again!");
   command("shake " + from->QRN);
   MONEY_MAKE_CC(random(66))->move(this_object());
   command("give copper coins to " +from->QRN);
   counting=0;
}

void
enter_inv(object ob, object from)
{
   ::enter_inv(ob,from);
   if(!from)
      return;   //if he gives away something enter_env is called with from=0

   if (IS_INFIDEL(from))
   {
        command("say Go away, you!");
        command("say I don't trade with Infidels!");
        return;
   }        

   if(ob->id("silver coin"))
   {
      set_alarm(1.0,0.0,&sell_fish(ob,from));
      return;
   }
   if(counting)
      return;
   if(ob->id("fish"))
   {
      counting=1;
      set_alarm(1.0,0.0,&finish_quest(ob,from));
   }
   else
      set_alarm(1.0,0.0,&command("thank " + from->QRN));
}

