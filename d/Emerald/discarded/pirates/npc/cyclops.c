inherit "/std/monster";

#include "/sys/stdproperties.h"
#include "/sys/global/money.c"
#include "defs.h"

#define LOST_EYE_SUBLOC "_lost_eye"
#define PIR_I_KILLED_CYCLOPS "_pir_i_killed_cyclops"
#define CYCLOPS_GIFT "_cyclops_gift"
#define SAID_YES "_said_yes"

int awake;

void
create_monster()
{
   set_name("cyclops");
   add_name("giant");
   set_race_name("giant");
   set_short("cyclops");
   
   set_long("@@sleeping");
   
   set_stats(({90,96,94,35,29,82}));
   set_alignment(0);
   
   heal_hp(10000);
   
   set_all_hitloc_unarmed(0); /* Inherent AC of 60 */
   
   add_prop(OBJ_I_WEIGHT, 5000);
   
   add_prop(CONT_I_MAX_WEIGHT, 180000);
   add_prop(OBJ_I_VOLUME, 89000);
   add_prop(LIVE_O_ENEMY_CLING, 1);
   add_prop(CONT_I_MAX_VOLUME, 100000);
   
   awake = 0;
}

string
sleeping()
{
   string str1, str2;
   str1 = "It is a one-eyed giant. His beard is crusted with "+
   "dried blood and old bones.";
   if(awake)
      str2 = "";
   if(TO->query_attack())
      str2 = "He is sleeping soundly.\n";
   else
      str2 = "He is sleeping soundly.\n";
   return break_string(str1+"\n",74)+str2;
}

void
init_living()
{
   ::init_living();
   add_action("do_ask","ask");
   add_action("do_wake","wake");
}

int
do_wake(string arg)
{
   notify_fail("Wake who?\n");
   if(!arg && arg != "cyclops" && arg != "up cyclops" && arg != "cyclops up")
      return 0;
   awake = 1;
   tell_room(ENV(TO),CAP(QCTNAME(TP))+" does something to the cyclops.\n",TP);
   tell_room(ENV(TO),"The cyclops awakens from his nap.\n");
   tell_room(ENV(TO),"The cyclops bellows: You woke me up, you "+
      "stinking little "+TP->query_race_name()+"!!!\n");
   tell_room(ENV(TO),"The cyclops bellows: What do you want?!?!?\n");
   return 1;
   set_alarm(120.0,0.0,"back_to_sleep");
}

int
do_ask(string arg)
{
   object wine, *items, lost_eye;
   int cash, i;
   if(arg && !awake)
      {
      tell_room(ENV(TO),QCTNAME(TP)+" asks the cyclops something.\n",TP);
      tell_room(ENV(TO),"The cyclops awakens from his nap.\n");
      tell_room(ENV(TO),"The cyclops bellows: You woke me up, you "+
         "stinking little "+TP->query_race_name()+"!!!\n");
      tell_room(ENV(TO),"The cyclops bellows: What do you want?!?!?\n");
      awake = 1;
      set_alarm(120.0,0.0,"back_to_sleep");
      return 1;
   }
   if(arg && awake && TP->query_prop(CYCLOPS_GIFT))
      {
      tell_room(ENV(TO),QCTNAME(TP)+" asks the cyclops something.\n",TP);
      tell_room(ENV(TO),"The cyclops bellows: Get out of here you "+
         "anyoying little "+TP->query_race_name()+"!\n");
      tell_room(ENV(TP),"The cyclops throws "+QCTNAME(TP)+" back up the "+
         "hill.\n",TP);
      write("The cyclops throws you back up the hill.\n");
      TP->move_living("M",PIRATES_DIR+"quest/is12");
      set_alarm(1.0,0.0,"back_to_sleep");
      return 1;
   }
   if(arg && awake && !(TP->query_prop(CYCLOPS_GIFT)))
      {
      tell_room(ENV(TO),QCTNAME(TP)+" asks the cyclops something.\n",TP);
      tell_room(ENV(TO),"The cyclops turns red in the face.\n");
      if(TP->query_prop(SAID_YES))
         {
         tell_room(ENV(TO),"The cyclops bellows: I want your eye!\n");
         tell_room(ENV(TP),"The cyclops rips "+QCTNAME(TP)+"'s eye from "+
            "its socket!\n",TP);
         write("The cyclops rips your eye from its socket!\n");
         lost_eye = clone_object(PIRATES_DIR+"obj/lost_eye");
         lost_eye ->move(TP);
         TP->add_subloc(LOST_EYE_SUBLOC,lost_eye);
         tell_room(ENV(TO),"The cyclops eats an eye.\n");
         tell_room(ENV(TP),"The cyclops tells "+QCTNAME(TP)+" something.\n",TP);
         write("The cyclops tells you: In return for your eye, you can have "+
            "one of my goats!!!\n");
         tell_room(ENV(TO),"The cyclops chuckles cruelly.\n");
         TP->add_prop(CYCLOPS_GIFT,1);
         call_out("back_to_sleep",3);
      }
      else
         {
         tell_room(ENV(TO),"The cyclops bellows: What do "+
            "have in there?!?!?\n");
         tell_room(ENV(TP),"The cyclops looks through "+
            QCTNAME(TP)+"'s pockets.\n",TP);
         write("The cyclops pokes around in your pockets.\n");
         if(present("wine",TP))
            {
            write("The cyclops takes your wine.\n");
            tell_room(ENV(TO),"Takes something from "+
               QCTNAME(TP)+"\n",TP);
            write("The cyclops tells you: So you brought me "+
               "some wine!?!?!\n");
            wine = present("wine",TP);
            wine->remove_object();
            tell_room(ENV(TO),"The cyclops drinks some thick wine.\n");
            tell_room(ENV(TO),"The cyclops goes: Ahhhhhhhh!!!\n");
            TO->command("burps rudely");
            write("The cyclops tells you: This looks like a fair price "+
               "for one of my goats!\n");
            tell_room(ENV(TP),"The cyclops tells "+QCTNAME(TP)+
               "something.\n",TP);
            TO->command("laugh rudely");
            TP->add_prop(CYCLOPS_GIFT,1);
            call_out("back_to_sleep",3);
            return 1; 
         }  
         cash = MONEY_FN->total_money(TP)/2;
         take_money(TP,cash);
         write("The cyclops took half your money!\n");
         tell_room(ENV(TP),"The cyclops some of "+
            QCTNAME(TP)+"'s money!\n",TP);
         i = sizeof(items);
         write("The cyclops tells you: This looks like a fair price "+
            "for one of my goats!\n");
         tell_room(ENV(TP),"The cyclops tells "+QCTNAME(TP)+
            " something.\n",TP);
         TO->command("laugh rudely");
         TP->add_prop(CYCLOPS_GIFT,1);
         set_alarm(3.0,0.0,"back_to_sleep");
      }
   }
   return 1;
}

int
back_to_sleep()
{
   if(!awake)         /* just a check */
      return 1;
   awake = 0;
   tell_room(ENV(TO),"The cyclops goes back to sleep.\n");
   return 1;
}

void
do_die(object killer)
{
   object neptune;
   neptune = clone_object(PIRATES_DIR+"npc/neptune2.c");
   neptune -> move_living("M",ENV(killer));
   killer->add_prop(PIR_I_KILLED_CYCLOPS, 1);
   ::do_die();
   return;
}
