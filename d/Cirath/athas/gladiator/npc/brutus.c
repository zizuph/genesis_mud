/* brutus.c: Brutus the Guardian of The Gladiators: By many.
 *     Corrupted by Serpine, 4-24-95.
 *     Further influenced by Decius, June 30,1997
 *     Guruquest returned, with new foes, Casimir, April 2001.
 *     Stopped logging non-Glad Brutus attacks, Rhyn, September 2001.
 *     Added 100 to each stat. Damaris 10/07.
 */

inherit "/std/monster.c";

#include "defs.h"
#include "/d/Cirath/common/introfnc.h"
#include "/d/Cirath/quest_handler/quest_handler.h"
#include <wa_types.h>
#include "../guruquest.h"

#define MAIN_ASK(x) ("@@askmost:"+file_name(TO)+"|"+x+"@@")

string askmost(string subject);

void
create_monster()
{
    seteuid(getuid());

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
    set_stats(({275,250,275,200,225,275}));
    set_skill(SS_DEFENCE,200);
    set_skill(SS_PARRY,200);
    set_skill(SS_WEP_AXE,200);
    set_skill(SS_BLIND_COMBAT,200);
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
    add_ask(({"champions"}),
	    "say I have selected a champion each of the humans, elves "+
	    "dwarves and little peoples who must overcome in single "+
	    "combat before I deem anyone to be a guru of the "+
	    "Arena.", 1);
    add_ask(({"champion of the elves", "elven champion", "Myrdoth",
		"elf champion", "myrdoth", "champion elf"}),
	    "say Seek out Myrdoth, the champion of the Mikla Noth,  "+
	    "a tribe of elven bandits. Defeat him in mortal combat if "+
	    "you would presume to be a guru of the Arena.", 1);
    add_ask(({"champion of the dwarves", "dwarven champion", "Derryn",
		"dwarf champion", "derryn", "champion dwarf"}),
	    "say A few years ago, an excellent dwarven gladiator by the "+
	    "name of Derryn escaped from the Arena. He was good, very good "+
	    " ... almost as good as I. I'm quite certain he is still "+
	    "around, hiding someplace out in the wilderness. Defeat him "+
	    "if you wish to prove yourself ready to become a guru.", 1);
    add_ask(({"champion of the humans", "human champion", "Lyden",
		"champion human", "lyden"}),
	    "say The legendary human gladiator Lyden bought his freedom "+
	    "after a spectacular match. You must defeat him, if you are "+
	    "to be considered worthy of consideration as a guru of the "+
	    "Arena.", 1);
    add_ask(({"champion of the little peoples", "little champion", "Avena",
		"halfling champion", "champion of the halflings", "avena",
		"champion halfling", "champion little person"}),
	    "say I have seen the streetbrawler named Avena, clearly she was "+
	    "once a gladiator and definitely a worthy foe for any who "+
	    "would like to claim the title of guru. By now, I am sure "+
	    "you know enough not to judge an opponent by her size ...", 1);   
}

int query_knight_prestige()    { return -5; }
public int query_init_master() { return  1; }

void
arm_me()
{
    clone_object(GLAD_OBJ  +"brut_axe.c")->move(TO);
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

    hitresult = enemy->hit_me(750, W_BLUDGEON, me, -1);
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
attacked_by(object ob)
{
    ::attacked_by(ob);

    if (IS_MEMBER(ob))
    {
	command("' You are a disgrace to this guild.");
        MANAGER->add_brutus_attacker(ob);
    }
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

    if(MANAGER->query_brutus_attacker(who))
    {
	command("growl");
	command("' Base slime!");
	command("' Anakore dung!");
	command("' First you attack me, now you ask for a quest?");
	command("shout NEVER! I would kill you first!");
	command("shout Fellow Gladiators! Come!");
	command("shout Teach this "+(CAP(who->query_real_name()))+
		" a lesson!");
	command("kill "+lower_case(who->query_real_name()));
	return "";
    }

    if(query_attack())
    {
        command("' Help me get rid of these fools and I'll consider it!");
        command("roar");
        return "";
    }

    if(!IS_MEMBER(who))
    {
	command("' I do not offer such things to the likes of you.");
	command("emote growls.");
	return "";
    }

    if (MANAGER->guru_quest(who->query_real_name()))
    {
        command("say I have already told you what you must do to advance "+
		"your skills to the next level! Face and slay each of the "+
		"champions I have named in single combat, alone and "+
		"unwavering. Only when you have done that should you ask me "+
		"about a reward!");
        return "";
    }

// give a gladiator the quest
    if (!QH_QUERY_QUEST_COMPLETED(who, "guru_axe_quest"))
    {
	command("say If you wish to prove yourself a true champion, then "+
		"you must best a champion of the humans, the dwarves, "+
		"the elves and of the little peoples. Defeat each of them in "+
		"a single mortal combat, to the death,  and then I will know "+
		"that you are "+
		"ready to become a guru of the arena. Ask me for a reward at "+
		"that time ... should you still live.");
	MANAGER->guru_quest_set(who->query_real_name(), GOT_QUEST);
	return ""; 
    }

// gladiator already has guru quest
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

    if(query_attack())
    {
        command("' Help me get rid of these fools and I'll consider it!");
        command("roar");
        return "";
    }

    if(!IS_MEMBER(TP))
    { //player asking for a reward was not a gladiator
	command("' Get lost!");
	return "";
    }

    if (QH_QUERY_QUEST_COMPLETED(this_player(), "guru_axe_quest"))
    {
	command("' You have already been declared a guru!");
	return "";
    }

    if (MANAGER->guru_quest_done(this_player()->query_real_name()))
    {

	QH_QUEST_COMPLETED(this_player(), "guru_axe_quest");
        MANAGER->guru_quest_clear(this_player()->query_real_name());
        command("say Excellent! I will inform Barkara that you have "+
		"proven yourself to be a guru of the Arena. Go, now, "+
		"and spill more blood upon her sands!");
        return "";     	
    }

    if (MANAGER->guru_quest(this_player()->query_real_name()))
    {
	command("laugh harsh");
	command("say You have not proven yourself worthy! Only a gladiator "+
		"who can slay the best outside of this arena in single "+
		"combat, alone and without cowardice, deserves the title "+
		"of guru!\n");
	command("say Now, leave me, and train harder!");
    }

    // player has not gotten the guru quest
    command("say Do not bother me, unless you truly think you are ready "+
	    "to become a guru of the arena!\n");
    return "";
}



















