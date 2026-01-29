/*
 * This is prisoner used in CAVE_DIR
 * 
 * Made by Milan
 * 
 * Updated by Igneous
 */

#include "../local.h"
#include <ss_types.h>
#include <filter_funs.h>
#include <language.h>
#include BITS_FILE

inherit SHIRE_MONSTER;

#define INTRO  0
#define ASKED  1
#define NODDED 2

// Prototypes
void return_introduce(string who);
void capture_prisoner();
void react_gift(object *foo);
void give_back(object *foo);

// Global Vars
mapping list = ([]);
string leader;
int filip_has_sword, filip_has_armour, no_of_pushes, ate_food, drank_drink;
object ob_leader, gShadow;

void
create_shire_monster()
{
    set_name("cerindel");
    set_pname("elves");
    set_race_name("elf"); 
    set_living_name("_misty_prisoner_");
    set_adj("starved");
    add_adj("skinny");
    set_title("Experienced Traveller");
    add_prop(LIVE_I_SEE_DARK, 3);
    add_prop(CONT_I_WEIGHT,48000);   /* 48 Kg */
    add_prop(CONT_I_HEIGHT,123);      /* 123 cm */

    set_stats(({ 61, 50, 65, 45, 40, 44}));

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_skill(SS_AWARENESS, 100);

    set_alignment(500);

    set_act_time(5); 
    add_act("say Please, help me out of here."); 
    add_act("say I am starving to death!"); 
    add_act("say Goblins took all my equipment."); 
    add_act("say I hate these goblins!!!");
    add_act("say Goblin lord imprisoned us..."); 


    add_ask("help", VBFC_ME("answer_help"));
}

int
query_knight_prestige(){return -200;}

void 
add_introduced(string who)
{
    who = lower_case(who);
    if (!pointerp(list[who]))
	list[who] = ({1,0,0});

    set_alarm(2.0, 0.0, &return_introduce(who));
}

void
return_introduce(string who)
{
    object player;

    player = present(who, ENV(TO));
    if (!player->query_met(TO)) 
    {
	command("introduce me to "+ who);
	command("bow to "+ who);
    }
}

string
answer_help()
{
    string who_ask = TP->query_real_name();

    if (CHECK_QUEST(TP, "prisoner4"))
    {
	command("whisper "+who_ask+" Please, let the others do "+
	  "the quest now.");
	command("pat "+who_ask);
	return "";
    }
    if (!list[who_ask] || !list[who_ask][INTRO])
    {
	command("say Please introduce yourself first... "+
	  "I can't trust everyone.");
	return "";
    }
    if (list[who_ask][ASKED])
    {
	command("say "+capitalize(who_ask)+", are you deaf??? "+
	  "I have already told you!!!");
	command("pat "+who_ask);
	return "";
    }
    if (leader)
    {
	command("whisper "+who_ask+" Thank you for your concern but now "+
	  "I don't need anything.");
	command("whisper "+who_ask+" Maybe later.");
	command("smile "+who_ask);
	return "";
    }
    list[who_ask][ASKED] = 1; /* now he has asked first time */
    command("whisper "+who_ask+" I have been captured by these cursed goblins.");
    command("whisper "+who_ask+" I have tried to escape from here "+
      "but they caught me again.");
    command("whisper "+who_ask+" Next time it may be my death... ");
    command("whisper "+who_ask+" But I won't give up! Maybe you can "+
      "lead me out.");
    command("whisper "+who_ask+" Will you try it? Please!");
    command("peer "+who_ask);
    return "";
}

void 
emote_hook(string emote, object actor, string adverb)
{
    string who;

    if (emote != "nod") 
	return;

    who = lower_case(actor->query_real_name());
    if (list[who][ASKED])
    {
	if (leader && (leader != who))
	{
	    set_alarm(1.0,0.0,&command("whisper "+who+" Thank you but "+
		"I already have another leader."));
	    return;
	}
	if (list[who][NODDED])
	{
	    set_alarm(1.0,0.0,&command("ask "+who+" Why are you nodding "+
		"at me again?"));
	    set_alarm(2.0,0.0,&command("whisper "+who+" I have already "+
		"told you everything!"));
	    set_alarm(3.0,0.0,&command("whisper "+who+" I won't repeat "+
		"it! Someone may overhear us."));
	    set_alarm(4.0,0.0,&command("emote looks suspisiously around."));
	    return;
	}
	list[who][NODDED] = 1; /* now he agreed to help Cerindel */

	if (CHECK_QUEST(TP, "prisoner1"))
	{
	    leader = who;
	    ob_leader = present(find_player(leader), environment());
	    if (!objectp(gShadow))
	    {
		setuid(); seteuid(getuid());
		gShadow = clone_object(MISTY_OBJ_DIR + "follow");
		gShadow->follow(ob_leader,TO);
	    }
	    monster_act = ({ });  /* shut Cerindel up */

	    set_alarm(2.0,0.0, &command("ponder"));
	    set_alarm(4.0,0.0, &command("think"));
	    set_alarm(5.0,0.0, &command("peer "+who));
	    set_alarm(6.0,0.0, &command("whisper "+who+
		" O.K. You will be again my leader."));
	    set_alarm(7.0,0.0, &command("whisper "+who+
		" This time you must do better than you did."));
	    set_alarm(8.0,0.0, &command("pat "+who));
	    set_alarm(9.0,0.0, &command("whisper "+who+" I will again "+
		"follow you wherever you go."));
	    set_alarm(10.0, 0.0, &command("whisper "+who+
		" When you lose me, please find me as soon as possible."));
	    set_alarm(11.0,0.0, &command("whisper "+who+" Otherwise "+
		"goblins may capture me again."));
	    set_alarm(2000.0,0.0, capture_prisoner);
	    return;
	}

	set_alarm(1.0,0.0, &command("whisper "+who+" Thank you!"));
	set_alarm(2.0,0.0, &command("whisper "+who+" But I want you "+
	    "to find out where is my friend first."));
	set_alarm(3.0,0.0, &command("whisper "+who+" We were captured "+
	    "together..."));
	set_alarm(4.0,0.0, &command("whisper "+who+" and I haven't seen "+
	    "him since."));
	set_alarm(5.0,0.0, &command("sigh"));
	set_alarm(6.0,0.0, &command("whisper "+who+" When you do this "+
	    "for me, I will trust you."));
	return;
    }
    set_alarm(1.0,0.0, &command("ask "+who+" Why are you nodding at me?"));
    set_alarm(2.0, 0.0, &command("peer "+who));
    return;
}

void
enter_inv(object what, object from)
{
    ::enter_inv(what, from);

    if (!from) /* Perhaps it was cloned and moved to me... */
	return;

    set_alarm(2.0,0.0, &react_gift(({ from, what })));
}

void
react_gift(object *foo)
{
    object from, what;
    string what_thing, from_who, to_write;

    from = foo[0];
    what = foo[1];
    what_thing = LANG_THESHORT(what);
    from_who = from->query_real_name();
    setuid(); seteuid(getuid());

    if(!objectp(what)) return;
 
    if (!pointerp(list[from_who]))
    {
	set_alarm(2.0,0.0, &give_back(({what,from})));
	return;
    }
    if ((list[from_who][NODDED]) &&
      (what->query_key() == "_rusty_gcaves_quest_key_"))
    {
	if (from_who == leader)
	{
	    command("whisper "+from_who+" You didn't have to do this again!");
	    command("pat "+from_who);
	    return;
	}
	set_alarm(2.0,0.0, &command("whisper "+from_who+" Yes! I know "+
	    "this key. My friend had it."));
	set_alarm(3.0,0.0, &command("ask "+from_who+" Where did you find "+
	    "it? In a pot with soup?"));
	set_alarm(4.0,0.0, &command("whisper "+from_who+" I am afraid we "+
	    "can't help my friend anymore."));
	set_alarm(5.0,0.0, &command("sigh"));
	set_alarm(6.0,0.0, &command("whisper "+from_who+" This is was "+
	    "the only reason for me not to try escape from here!"));

	/****************************************/
	/*   HERE I REWARD FOR SOLVING FRIEND   */
	/****************************************/
	if (REWARD_QUEST(from, "prisoner1"))
	{
	    from->catch_msg("\nYou feel more experienced.\n\n");
	}

	leader = from_who;
	ob_leader = from;
	if (!objectp(gShadow)) 
	{
	    gShadow = clone_object(MISTY_OBJ_DIR + "follow");
	    gShadow->follow(ob_leader, TO);
	}
	monster_act = ({ });  /* shut Cerindel up */
	set_alarm(8.0, 0.0, &command("whisper "+from_who+
	    " Now you will be my leader."));
	set_alarm(9.0, 0.0, &command("whisper "+from_who+
	    " I will try to follow you wherever you go."));
	set_alarm(10.0, 0.0, &command("whisper "+from_who+
	    " If you lose me, please find me as soon as possible."));
	set_alarm(11.0, 0.0, &command("whisper "+from_who+
	    " Otherwise goblins may capture me again."));
	set_alarm(2000.0, 0.0, capture_prisoner);
	return;
    }

    if (from_who != leader)
    {
	set_alarm(2.0,0.0, &give_back(({what,from})));
	return;
    }

    if (function_exists("create_food",what))
    {
	command("say Thank you! I am really starving.");
	command("eat "+what->query_names()[0]);
	ate_food = 1;
	/****************************************/
	/*   HERE I REWARD FOR GIVING FOOD      */
	/****************************************/
	if (!CHECK_QUEST(from, "prisoner2") &&
	  (ate_food + drank_drink == 2))
	{
	    REWARD_QUEST(from, "prisoner2");
	    from->catch_msg("You have nice feeling after helping him.\n");
	}
	return;
    }
    if (function_exists("create_drink",what))
    {
	command("say I don't remember when I had my last drink.");
	command("drink "+what->query_names()[0]);
	drank_drink = 1;
	/****************************************/
	/*   HERE I REWARD FOR GIVING DRINK     */
	/****************************************/
	if (!CHECK_QUEST(from, "prisoner2") &&
	  (ate_food + drank_drink == 2))
	{
	    REWARD_QUEST(from, "prisoner2");
	    from->catch_msg("You have nice feeling after helping him.\n");
	}
	return;
    }
    if ((function_exists("create_object",what) == "/std/weapon") &&
      (what->query_prisoner_sword()))
    {
	set_skill(SS_WEP_SWORD, 53);
	set_skill(SS_PARRY, 47);
	command("say Yes!!!  This is my sword!");
	command("wield "+OB_NAME(what));
	command("emote swings "+what_thing+" in his hand.");
	what->add_prop(OBJ_M_NO_DROP, 1);
	filip_has_sword = 1;
	/*********************************************/
	/*   HERE I REWARD FOR RETURNING ARMOUR      */
	/*********************************************/
	if (!CHECK_QUEST(from, "prisoner3") &&
	  (filip_has_sword + filip_has_armour == 2))
	{
	    REWARD_QUEST(from, "prisoner3");
	    from->catch_msg("You feel more experienced.\n");
	}
	return;
    }
    if ((function_exists("create_object",what) == "/std/armour") &&
      (what->query_prisoner_cloak()))
    {
	set_skill(SS_DEFENCE, 75);
	command("say Yes!!!  This is my cloak!");
	command("wear "+OB_NAME(what));
	what->add_prop(OBJ_M_NO_DROP, 1);
	filip_has_armour = 1;
	/************************************************/
	/*   OR HERE I REWARD FOR RETURNING ARMOUR      */
	/************************************************/
	if (!CHECK_QUEST(from, "prisoner3") &&
	  (filip_has_sword + filip_has_armour == 2))
	{
	    REWARD_QUEST(from, "prisoner3");
	    from->catch_msg("You feel more experienced.\n");
	}
	return;
    }
}

void
give_back(object *foo)
{
    command("say I only accept things from those I trust.");
    if (!command("give "+OB_NAME(foo[0])+" to "+OB_NAME(foo[1])))
	command("drop "+OB_NAME(foo[0]));
}

void
hook_pushed_wall()
{
    no_of_pushes += 1;
}

void
capture_prisoner() 
{
    command("shout Oh NO!!! Goblins! They are after me!!!");
    command("panic");
    tell_room(environment(), "Great bunch of goblins come running in.\n"+
      "The leader goblin says: Here is the prisoner! Get him!!!\n"+
      "Goblins jump on "+QTNAME(TO)+", knock him down "+
      "and carry him quickly away.\n", TO);
    remove_object();
}

void
enter_env(object dest, object old)
{
    int reward;
    string to_write;

    ::enter_env(dest,old);
    if (function_exists("end_of_prisoner_quest", dest))
    {
	/* quest finished */
	if (present(ob_leader, environment()))
	{
	    reward = PRISONER_FINAL_EXP;
	    if (no_of_pushes < 3) 
		reward -= 5000*(3-no_of_pushes);
	    set_alarm(1.0, 0.0, &command("say Thank you for saving me "+
		"from those horrible goblins."));
	    set_alarm(2.0, 0.0, &command("say Now I will run home as fast "+
		"as I can and I will never return here!"));
	    set_alarm(3.0, 0.0, &command("wave "+leader));
	    set_alarm(4.0, 0.0, &command( "emote runs away with a big "+
		"smile on his face."));
	    /********************************************/
	    /*   HERE I REWARD FOR FINISHING QUEST      */
	    /********************************************/
	    setuid(); seteuid(getuid());
	    if (VARIABLE_REWARD_QUEST(ob_leader, "prisoner4", reward))
	    {
		ob_leader->catch_msg("You feel more experienced.\n");
	    }
	}
	set_alarm(5.0,0.0,remove_object);
    }
    return;
}

