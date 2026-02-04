/*   adv_guild.c    Styles   Wed Jan 22 1992
 *
 *   NOTE.
 *   The player can't advance more than one level at the time.
 *         This is intentional and not a bug. The players should
 *   experience the effort of gaining each level. Thus they
 *         will recieve each new rank that comes along with the level.
 *
 *   If the guild is closed you can toggle this by doing,
 *   > Call teacher close_open
 *   This is a quick way to close/open it if needed
 *
 *   /Styles.
 */

inherit "/lib/trade";
inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";
inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"

#define NF(str)            notify_fail(str)
#define TP                 this_player()
#define TO                 this_object()
#define NUM                sizeof(query_money_types(-1))
#define BS(xxx)            break_string(xxx,70)
#define BSN(xxx)           break_string(xxx+"\n",70)
#define CLOSED             0      /* 1 = closed,   0 = open.  */
#define ALIGN              0

int closed;
object meditate;


create_monster() { 
   
   closed = CLOSED; 
   
   set_name("culbert");
   add_name("teacher");
   set_short("absentminded teacher");
   set_adj("absentminded");
   set_long(BSN(
       "It's an absentminded old teacher. He may perhaps "+
       "share some of his knowledge with you."
   ));
   set_race_name("human");
   set_stats(({20,20,20,80,80,20}));
   set_hp(9999);
   set_mana(9999);
   set_gender(0);
   set_alignment(ALIGN);
   set_all_hitloc_unarmed(30);
   set_all_attack_unarmed(10, 10);
   set_skill(SS_DEFENCE, 30);
   set_skill(SS_AWARENESS, 30);
   set_skill(SS_LANGUAGE, 30);
   set_skill(SS_SPELLCRAFT, 30);
   
   add_prop(OBJ_S_WIZINFO, "@@wizinfo");
   
   set_up_skills();
}

wizinfo() {
   return ("If there should be due cause to close down the teacher, do so by\n"+
      "typing:  Call teacher close_open\n"+
      "This will temporarily prevent mortals from entering. After a\n"+
      "reboot, the teacher will be open by default. Please send me some\n"+
      "mail if there is anything that needs to be fixed.\n\n  /Mortricia.\n");
}

enter_inv(ob, from) {
   ::enter_inv(ob, from);
   
   if (!interactive(ob) || !closed)
      return;
   
   if (ob->query_wiz_level()) 
      write("\n\nWARNING!\nYou shouldn't be here. "+
      "I'm doing some work on the teacher.\n");
   else {
      write("The teacher is asleep. Come back later.\n");
      ob->move(environment(TO));
   }
}


init_living() {
   add_action("improve", "teach");
   add_action("improve", "improve");
   add_action("improve", "learn");
   config_default_trade();
   ::init_living();
}

close_open() {
   if (closed) {
      closed = 0;
      return "  **The teacher is now open**";
   }
   closed = 1;
   return "  **The teacher is now closed**";
}

query_closed() { return closed; }

set_up_skills() {
   
   sk_init();
   /* Add skill that can be trained. Do not add all skills, and vary a bit */
   
   sk_add_train(SS_SPELLCRAFT, train_text(SS_SPELLCRAFT)[0],    0,0,15 );
   sk_add_train(SS_LANGUAGE,   train_text(SS_LANGUAGE)[0],      0,0,40 );
}

train_text(skill) {
   string what, does, *text;
   
   switch(skill) {
      
      case SS_SPELLCRAFT:
      what="use spellcraft";
      does = what;
      break;
      
      case SS_LANGUAGE:
      what="read and understand languages";
      does =  what;
      break;
      
      default:
      what="do nothing. THIS IS A BUG";
      does = "meditate";
      break;
   }
   text = ({"You improve your ability to "+ what +".\n", does}) ;
   return text;
}

lessf(a,b) {
   if (a <= b) return 1;
   return 0;
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
   
   if (closed) {
       NF("The teacher is asleep. Don't disturb him!\n");
       return 0;
   }

   /* Determine what skills the player and the teacher knows. */
   guild_sk = my_sort(sk_query_train());
   known_sk = my_sort(TP->query_all_skill_types());
   if (!known_sk) known_sk = ({});
   
   header = "  Skill:                Cost:      "+
   "Next level:           Max level:\n"+
   "--------------------------------------"+
   "--------------------------------------\n";
   
   sk_to_learn = ({});
   sk_to_improve = ({});
   
   /* Determine wich skills we need to learn and wich we can improve. */
   for (i=0 ; i<sizeof(guild_sk) ; i++) {
      if (member_array(guild_sk[i], known_sk) < 0)
         sk_to_learn = sk_to_learn + ({guild_sk[i]}) ;
      else {
         snum = sk_find_skill(guild_sk[i]);
         if (TP->query_base_skill(snum) < sk_query_max(snum)) {
            sk_to_improve = sk_to_improve + ({guild_sk[i]}) ;
         }
        }
   }
   
   /* Arrange the skills neatly in a way that looks good. */
   learn_sk = implode(map(sk_to_learn, "fix_cost", TO), "\n")+"\n\n";
   improve_sk = implode(map(sk_to_improve, "fix_cost", TO), "\n")+"\n\n";
   verb = query_verb();
   
   if (!sk) {/* We wish to see the list of skills */
      if (verb == "learn") {/* Skills to learn listed.*/
         if (sizeof(sk_to_learn)) {
            write("\nYou are able to learn the following skills.\n\n"+
               header + learn_sk);
            return 1;
          }
         write("\nThe teacher has no unknown skills to learn you.\n"+
            "You might try to improve the ones you have or seek out\n"+
            "new ones elsewhere. Its a big world you know...\n");
         return 1;
       }
      /* Skills that can be improved are listed. */
      if (sizeof(sk_to_improve)) {
         write("\nThese are the skills which you are able to improve.\n"+
            header + improve_sk); 
         return 1;
       }
      write("\nThe teacher explains that he can't teach you any more."+
         "\nYou should go out and seek new wisdom elsewhere.\n\n");
      return 1;
   }
   
   /* We wish to gain a skill level. */
   
   snum = sk_find_skill(sk);
   sk_present_level = TP->query_base_skill(snum);
   
   if (snum<0) {/* Does this skill exist at all? */
      NF("I have never heard of such a skill. "+
         "Maybe it can be taught elsewhere.\n");
      return 0;
   }
   
   if (verb == "learn") {
      if (member_array(sk, sk_to_improve) >=0) { /* Learning a known skill. */
         NF("You already know that skill. "+
            "Maybe you should improve it.\n");
         return 0;
       }
   }
   if (verb == "improve") {
      if (member_array(sk, sk_to_learn) >= 0) {  /* Skill not learned. */
         NF("You have to learn that skill before you can improve it.\n");
         return 0;
       }
      else if (sk_present_level >= sk_query_max(snum)) { /* No more of this */
         NF("You can not advance that skill any more here. "+
            "Seek that knowledge elsewhere.\n");
         return 0;
       }
   }
   
   to_lev = sk_present_level + 1;
   cost = sk_cost(snum, sk_present_level, to_lev);
   write("\nThe teacher charges you "+ cost +" copper for the service.\n");
   
   if (sizeof(pay_arr = pay(cost, TP)) == 1) {
      NF("You can not pay and recieve no training.\n");
      return 0;
   }
   
   write("You pay " + text(exclude_array(pay_arr, NUM, NUM * 2 - 1)) );
   if (text(exclude_array(pay_arr, 0, NUM - 1)))
      write(" and get " + text(exclude_array(pay_arr, 0, NUM - 1)) +
      " in return.\n");
   else
      write(".\n");
   
   sk_do_train(snum, TP, to_lev);
   write("You achieve the rank of "+ sk_rank(to_lev) +".\n");
   long_str = QCTNAME(TP)+ " improves " + TP->query_possessive() +
   " ability to "+ train_text(snum)[1] +" and recieves the rank of "+
   sk_rank(to_lev) +".";
   say(BS("\n"+ long_str +"\n"));
   return 1;
}
