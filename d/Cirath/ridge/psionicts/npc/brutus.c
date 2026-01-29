/* brutus.c: Brutus the Guardian of The Gladiators: By many.
 *     Corrupted by Serpine, 4-24-95.
 *     Further influenced by Decius, June 30,1997
 */
 
inherit "/std/monster.c";

#include "defs.h"
#include "/d/Cirath/common/introfnc.h"
#include "/d/Cirath/quest_handler/quest_handler.h"
#include <wa_types.h>

#define MAIN_ASK(x) ("@@askmost:"+file_name(TO)+"|"+x+"@@")
#define DEBUG(x)        find_player("luther")->catch_tell(x);


string *attackers;

string askmost(string subject);

void
create_monster()
{
  seteuid(getuid());
  restore_object(PSION_LOG+"brutus_attacker");

  set_name("brutus");
  set_living_name("brutus");
  add_name("gladiator");
  set_title("the Guardian of the Gladiators");
  set_race_name("dwarf");
  set_adj("grizzled");
  add_adj("powerful");
  set_long("A dangerous warrior in his youth, this weathered being has "+
           "taken it as his dwarven life-goal, his Focus, to defend "+
           "the guild of Gladiators from any who would attack it. He "+
           "does his job well.\n"+
           "His ear is pierced with obsidian shards.\n"+
           "He has the brutal scars of a Gladiator\n");

  add_chat("I might have a task for you.");
  add_cact("emote works himself into a wild battlerage.");
  add_cact("emote breaks into a sweat as his breathing becomes heavier.");
  set_cact_time(4);
  set_chat_time(25); 

  set_alignment(100);
  set_stats(({175,150,175,100,125,175}));
  set_skill(SS_DEFENCE,100);
  set_skill(SS_PARRY,100);
  set_skill(SS_WEP_AXE,100);
  set_skill(SS_BLIND_COMBAT,100);
  set_default_answer(MAIN_ASK("huh"));

  add_ask(({"task","about task","job","about job","quest","about quest",
        "assignment","about assignment"}),VBFC_ME("asktask"));
  add_ask(({"reward","about reward","for reward","for the reward",
            "for my reward"}),VBFC_ME("reward"));
  add_ask(({"warriors","about warriors"}), MAIN_ASK("warriors"));
  add_ask(({"mages","about mages"}),MAIN_ASK("mages"));
  add_ask(({"clerics","about clerics","priests","about priests"}),
            MAIN_ASK("clerics"));
  add_ask(({"gladiator","about gladiators","gladiator","about gladiator"}),
            MAIN_ASK("glads"));
  add_ask(({"tyr","about tyr","about city","city"}), MAIN_ASK("tyr"));
  add_ask(({"king","about king","about the king"}), MAIN_ASK("king"));
  add_ask(({"gnome","about gnome","pandora","about pandora"}),
        MAIN_ASK("criminals"));
  add_ask(({"slave","slaves","about slaves","about slave"}),
        MAIN_ASK("slaves"));
  add_ask(({"arena","stadium","about arena","about stadium"}),
            MAIN_ASK("arena"));

}

int query_knight_prestige()    { return -5; }
public int query_init_master() { return  1; }

void
arm_me()
{
    clone_object(PSION_OBJ  +"brut_axe.c")->move(TO);
    clone_object(TYR+"arm/body_chn.c")->move(TO);
    clone_object(TYR+"arm/arms_hid.c")->move(TO);
    command("wield all");
    command("wear all");
}

// **************** BRUTUS CHARGES! ******************** 
int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
 
    me=this_object();
 
    if(random(5)) return 0;
 
    hitresult = enemy->hit_me(250 + random(250), W_BLUDGEON, me, -1);
    how = "amazed by such a feeble attack";
    if (hitresult[0] > 0) how = "dazed";
    if (hitresult[0] > 15) how = "injured";
    if (hitresult[0] > 30) how = "hurt";
    if (hitresult[0] > 50) how = "severely hurt";
    if (hitresult[0] > 75) how = "on the verge of collapse";
 
    enemy->catch_msg(QCTNAME(me) + " strikes you with "+
                     HIS_HER(me) + " charge.\n");
    enemy->catch_msg("You feel " + how + ".\n");
 
    tell_watcher(QCTNAME(me)+" strikes "+QCTNAME(enemy)+
                 " with " + HIS_HER(me) + " charge.\n",
                 me, enemy);
 
    if(enemy->query_hp() <= 0) enemy->do_die(me);
 
    return 1;
}

// *****************REMEMBER ATTACKERS CODE*****************
void
no_train(string who)
{
  int i;
  i=member_array(who,attackers);
  if(!sizeof(attackers))
    { 
      attackers = ({});
    }
  if(i<0)
    {
      attackers +=({who});
    }

  seteuid(getuid());
  save_object(PSION_LOG+"brutus_attacker");
}

string remove_attacker(string name)
{
  int i;
  if ((i=member_array(name,attackers)) == -1)
    return "No one with that name has attacked Brutus lately.";
  attackers = exclude_array(attackers, i,i);
  save_object(PSION_LOG+"brutus_attacker");
  return "Removed from the Brutus killer list.";
}

void
attacked_by(object ob)
{
  ::attacked_by(ob);

  if (IS_MEMBER(ob))
    {
      command("' You are a disgrace to this guild.");
      /* Some punishment */
    }
      no_train(ob->query_real_name());
}
mixed
return_killers()
{
   return attackers;
}



// *************************GENERAL ANSWER FUNCTION**************
string
askmost(string subject)
{
   object who;
   who=PO;
  
   switch(subject)
   {
      case "huh":
         command("peer "+lower_case(who->query_name()));
         return "";
      case "warriors":
         command("' The Gladiators are the greatest of all fighters!");
         command("' However there are some other powerful folks in "+
                 "out-of-the-way places.");
         return "";
      case "mages":
         command("emote scowls bitterly.");
         command("' Mages are the ones who reduced Athas to desert!");
         command("' I'd like to take my axe against any one of them!");
         return "";
      case "clerics":         
         command("' The Templars are the closest thing we have.");
         return "";
      case "glads":
         command("' The Gladiators of Athas are indeed a fine guild!");
         command("' Only we understand the meaning of glory and pride.");
         return "";
      case "tyr":
         command("' Tyr is the greatest city in Athas, or anywhere.");
         return "";
      case "king":
         command("' Kalak rules Tyr and the Gladiators both.");
         command("' He is practically a god.");
         return "";
      case "criminals":
         command("' Pandora and her gnome accomplice were betrayed "+
                     "by her butler. We don't talk about them anymore.");
         return "";
      case "slaves":
         command("' Slaves are sold, bought, or end up in the arena.");
         command("' The Gladiators of Athas are all slaves to Kalak.");
         return "";
      case "arena":
         command("' The arena is a Gladiators second home.");
         command("' Triumph or die: That is our way.");
         return "";
      default: return "";
   }
}

// *************** GLAD GURU QUEST CODE ********************* 

string
asktask()
{
    object who, cuir;

    who = TP;

    if((member_array(who->query_real_name(), attackers)) > -1)
    {
        command("growl");
        command("' Base slime!");
        command("' Anakore dung!");
        command("' First you attack me, now you ask for a quest?");
        command("shout NEVER! I would kill you first!");
        command("shout Fellow Gladiators! Come!");
        command("shout Teach this "+(CAP(who->query_real_name()))+" a lesson!");
        command("kill "+lower_case(who->query_real_name()));
        return "";
    }

    if(!IS_MEMBER(who))
    {
        command("' I do not offer such things to the likes of you.");
        command("emote growls.");
        return "";
    }


    if (!QH_QUERY_QUEST_COMPLETED(who, "guru_axe_quest"))
    {
     command("' Hmmmmm....");
     command("' The plague has destroyed many of our greats.");
     command("' And the rise of the Earthsea has eliminated those who once were acceptable.");
     command("' I will tell you when I have found worthy opponents for you.");
     return ""; 
    }

    command("' You have proven yourself worthy time and again.");
    command("' Go forth and lay waste to your enemies, Warrior.");
    command("' I have no further tasks to set before you.");
    command("grin");
    return "";
}

string
reward()
{
    object who;

    who = TP;

    if(!IS_MEMBER(who))
    {
        command("' Get lost!");
        return "";
    }

    if (QH_QUERY_QUEST_COMPLETED(who, "guru_axe_quest"))
    {
        command("' You have already been declared a guru!");
        return "";
    }

    command("' Not today.");
    return "";
}



