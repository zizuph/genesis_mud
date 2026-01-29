inherit "/std/monster";

inherit "/lib/trade";
inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>

#define NF(str) notify_fail(str)
#define TO this_object()
#define NUM sizeof(query_money_types(-1))
#define BS(xxx) break_string(xxx,68)
#define CLOSED 0/* 1 = closed,   0 = open.  */

#define GUILD_TYPE "occupational"
#define GUILD_STYLE "mystic"
#define GUILD_NAME "The Ancient Mystic Order"
#define STAND_DIR "/d/Terel/mecien/valley/guild/"
#define SHADOW "/d/Terel/mecien/valley/guild/mystic_sh"
#define TP this_player()

int closed;
object meditate;

/*
* Prototypes
*/
void set_up_skills();
string *train_text(int skill);

void
create_monster()
{ 

set_race_name("faerie");
set_name("Eyisti");
add_name("teacher");
add_name("eyisti");
   
   
   set_up_skills();
   
}


void
init_living()
{
   ::init_living();
   config_default_trade();
   add_action("improve", "learn");
   add_action("improve", "advance");
}


void
set_up_skills()
{
   
   sk_init();
   
   sk_add_train(SS_FORM_DIVINATION,  train_text(SS_FORM_DIVINATION)[0],0, 0, 90);
}

string *
train_text(int skill)
{
   string what, does, *text;
   
   switch(skill)
   {
      case SS_FORM_DIVINATION:
      what = "divinations";
      does = what;
      break;
      
      default:
      what = "do nothing. THIS IS A BUG";
      does = "meditate";
      break;
   }
   text = ({"Eyisti teaches you the deep secrets of " + what + ".\n", does}) ;
   return text;
}


int
lessf(int a, int b)
{
   return a <= b ? 1 : 0;
}

my_sort(arr_in) {
   return map(sort_array(arr_in, "lessf", TO),
      "sk_query_name", TO);
}

fix_cost(sk) {
   int i, snum, this_level, next_level;
   string next_rank, max_rank;
   
   snum = sk_find_skill(sk);
   this_level = TP->query_base_skill(snum);
   next_level = this_level + 1;
   i = sk_cost(snum, this_level, next_level);
   next_rank = sk_rank(next_level);
   max_rank = sk_rank(sk_query_max(snum));
   
   return sprintf("  %-16s %13s   %-20s %-20s", sk, i+" copper",
      next_rank, max_rank);
}

improve(sk) {
   string *guild_sk, *known_sk, *sk_to_learn, *sk_to_improve, *pay_arr;
   string *how;
   string learn_sk, improve_sk, verb, header, long_str;
   int i, to_lev, sk_present_level, snum, cost;
   
   if(TP->query_guild_name_occ()!=GUILD_NAME){
      write("Eyisti whispers: I will not teach you....\n");
      return 1;
   }
   
   /* Determine what skills the player and the guild knows. */
   guild_sk = my_sort(sk_query_train());
   known_sk = my_sort(TP->query_all_skill_types());
   if (!known_sk)
      known_sk = ({});
   
   header = guild_sk;
   
   sk_to_learn = ({});
   sk_to_improve = ({});
   
   /* Determine which skills we need to learn and which we can improve. */
   for (i = 0 ; i < sizeof(guild_sk); i++)
   {
      if (member_array(guild_sk[i], known_sk) < 0)
         sk_to_learn = sk_to_learn + ({guild_sk[i]}) ;
      else
         {
         snum = sk_find_skill(guild_sk[i]);
         if (TP->query_base_skill(snum) < sk_query_max(snum)) 
            sk_to_improve = sk_to_improve + ({guild_sk[i]}) ;
        }
   }
   
   /* Arrange the skills neatly in a way that looks good. */
   learn_sk = implode(map(sk_to_learn, "fix_cost", TO), "\n")+"\n\n";
   improve_sk = implode(map(sk_to_improve, "fix_cost", TO), "\n")+"\n\n";
   verb = query_verb();
   
   if (!sk)
      {/* We wish to see the list of skills */
      if (verb == "learn")
         {/* Skills to learn listed.*/
         if (sizeof(sk_to_learn))
            {
            write("\nEyisti sings: I can teach you " +
               header + " to " + learn_sk + "\n");
            return 1;
          }
         write("\nEyisti cries: I have no more to teach you!\n");
         return 1;
       }
      /* Skills that can be improved are listed. */
      if (sizeof(sk_to_improve))
         { 
   write("Eyisti sings: I can teach you the secrets of " + header +
     "\n");
         return 1;
   }
      write("\nYou have learned all you can here.\n");
      return 1;
   }
   
   /* We wish to gain a skill level. */
   
   snum = sk_find_skill(sk);
   sk_present_level = TP->query_base_skill(snum);
   
   if (snum<0)
      {/* Does this skill exist at all? */
      NF("Eyisti looks confused.\n");
      return 0;
   }
   
   if (verb == "learn")
      {
      if (member_array(sk, sk_to_improve) >=0) { /* Learning a known skill. */
         NF("You have studied that subject before.\n");
         return 0;
       }
   }
   if (verb == "improve")
      {
      if (member_array(sk, sk_to_learn) >= 0)
         {  /* Skill not learned. */
         NF("You must begin your studies first.\n");
         return 0;
       }
      else if (sk_present_level >= sk_query_max(snum))
         { /* No more of this */
         NF("You cannot study that skill any more here. " +
            "Seek that knowledge elsewhere.\n");
         return 0;
       }
   }
   
   to_lev = sk_present_level + 1;
   cost = sk_cost(snum, sk_present_level, to_lev);
   
#ifdef UNDEF /* CPU sucker */
      if (sizeof(pay_arr = pay(cost, TP)) == 1)
      {
      NF("Eyisti sings: I must insist upon a fee\n");
      return 0;
   }
   
   write("You give " + text(exclude_array(pay_arr, NUM, NUM * 2 - 1)) );
   if (text(exclude_array(pay_arr, 0, NUM - 1)))
      write("to Eysiti and receiveive " + text(exclude_array(pay_arr, 0, NUM - 1)) +
      " in return.\n");
   else
      write(".\n");
#else
      if (!MONEY_ADD(TP, -cost))
      {
      NF("You do not have the funds for the sacrifice.\n");
      return 0;
   }
#endif
      
   sk_do_train(snum, TP, to_lev);
   write("You achieve the rank of "+ sk_rank(to_lev) +".\n");
   long_str = QCTNAME(TP)+ " studies " 
   + train_text(snum)[1] +" and recieves the rank of "+
   sk_rank(to_lev) +".";
   say(BS("\n"+ long_str +"\n"));
   return 1;
}
