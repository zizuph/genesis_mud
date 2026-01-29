// file name:
// creator(s):    Lilith   03/26/03
// purpose:       Defenders of Sybarus
// note:          This file acts like multiple npcs.
// last update:   Copied and Modified for the Ziggurat.
//
// bug(s):
// to-do:
#pragma strict_types

#include "zigg.h"

inherit ZIG_NPC;

#include <const.h>
#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>


private static mixed *everyone = ({
  /*  race         adj         eyes           hair  */
  ({ "elf",	 "sturdy",   "dark-brown",  "dark-brown" }),
  ({ "elf",	 "muscular", "dark-grey",   "light-brown" }),
  ({ "elf",	 "serious",  "light-brown", "red-brown" }),
  ({ "elf",	 "athletic", "brown",       "blond" }),
  ({ "elf",	 "dutiful",  "black",       "white-blond" }),
  ({ "elf",	 "slender",  "blue",        "golden-blond" }),
  ({ "elf",	 "vigorous", "hazel",       "dark-blond" }),
  ({ "elf",	 "alert",    "grey",        "black" }),
  ({ "elf",	 "smiling",  "blue-green",  "brown" }),
  ({ "elf",	 "fit",      "green",       "grey" }),
  ({ "elf",	 "vigilant", "grey-green",  "blond" }),
  ({ "half-elf", "quirky",   "vivid blue",  "red" }),
  ({ "half-elf", "hearty",   "pale blue",   "chestnut" }),
  ({ "half-elf", "grinning", "brown",       "orange" }),
  ({ "half-elf", "frowning", "dark-blue",   "yellow" }),
  ({ "half-elf", "lithe",    "dark-green",  "short" }),
  ({ "half-elf", "stocky",   "pale-green",  "long" }),
  ({ "half-elf", "bashful",  "dark-brown",  "cropped" }),
});

private static string *adjs = ({
    "guarding", "defensive", "defending", "protective",
});

private string my_long(void);

private static string eyes, hair;
public string query_eyes(void)	{ return eyes; }
public string query_hair(void)	{ return hair; }

/*
 * set_morph sets the various attributes of the
 * npc, making it unique 10 different ways.
 */
public void
set_morph(int who)
{
    string *someone;

    if (who < 0 || who >= sizeof(everyone))
	who = random(sizeof(everyone));

    someone = everyone[who];
    set_race_name(someone[0]);
    set_adj(one_of_list(adjs));
    add_adj(someone[1]);

    eyes = someone[2];
    hair = someone[3];

    set_gender(G_MALE);
}

/* Create the npc */
static void
zig_npc(void)
{
    fixeuid();

    set_name(({"defender", "guard"}));
    set_title("Defender of Sybarus");
    set_alignment(0);

    set_morph(-1);
    set_long(my_long);

    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_UNARMED, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    /* Makes us hard to fight. */
    add_prop(LIVE_I_QUICKNESS, 150);
    /* We see nearly all. */
    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(LIVE_I_SEE_INVIS, 5);

    set_knight_prestige(-5);

    set_skill(SS_DEFENCE,   random(20) + 80);
    set_skill(SS_2H_COMBAT, random(20) + 90);
    set_skill(SS_WEP_SWORD, random(20) + 90);
    set_skill(SS_AWARENESS, random(40) + 60);
    set_skill(SS_WEP_KNIFE, random(20) + 80);
    set_skill(SS_BLIND_COMBAT, random(20) + 80);
    set_skill(SS_SNEAK, random(20) + 25);
    set_skill(SS_HIDE, random(20) + 25);

    set_all_attack_unarmed(10, 10);

    set_height_desc(
	one_of_list(({"tall", "very tall", "of normal length"})));
    set_width_desc(
	one_of_list(({"skinny", "lean", "of normal width"})));

    set_exp_factor(150);
    default_config_npc(200, 10);

    set_cact_time(7);
    add_cact("glare mercilessly enemy");
    add_cact("say Flee from me and I will not follow!");
    add_cact("say From whence thou came, so shall I return you.");

    set_dont_answer_unseen(1);
    set_default_answer("@@what_me@@", 1);
    add_ask(({"bath", "melchior's bath", "bathhouse"}),
      "say There is a bathhouse in the City. I won't be visiting "+
      "it again in this life.", 1);
    add_ask(({"sybarus","bazaar"}),
      "say Its the main island, over yonder.",1);
    add_ask("city", "say You won't get anything from me!", 1);
    add_ask(({"task", "job", "quest", "help"}), "eyebrow arch", 1);

    add_ask(({"infidel","infidels", "shame"}),
      "say Infidels are without rank, less than slaves. They have "+
      "acted against the Gods' Will, and rather than submit to "+
      "servitude or a dignified death, they have chosen to live "+
      "the rest of their lives in fear of death.", 1);
    add_ask(({"faithful","faithfuls","Faithful", "sybarite", "sybarites"}),
      "say Sybarites are the Faithful. Sybarites live to serve and "+
      "uphold the Pact, that the Source will always cast its illum"+
      "ination upon us.",1);
    add_ask(({"ziggurat","Ziggurat","pleasure palace"}),
      "say If you've coin and purity enough you may find all manners of "+
      "pleasure inside, though the more interesting levels are still "+
      "reserved for those possessing a sigil. Idrys be praised.",1);  
    add_ask(({"sigil","sigils"}),
      "say The symbol of your House. If you had one, you wouldn't need "+
      "to ask. I guess you won't be visiting the lower levels today.",1); 
    add_ask(({"lower levels"}),
      "say Most of the nobles spend their time in the depths of the "+
      "Pleasure Palace. That's where the best trained slaves are, delicious "+
      "food, music to make you weep, bards and acrobats and of course all "+
      "manner of hlaj and hlej. Even the Idrys are seen there at times.",1);    
    add_ask(({"hlaj", "hlej", "hlaj and hlej"}),
      "say Have you never worshipped Sisera?",1);   
    add_ask(({"Sisera"}), "say He is the god of carnal delight. You'd best "+
    	"be in good standing with him before you venture inside. I've "+
    	"heard some embarrassing stories.",1);     
    add_ask(({"stories", "embarrassing stories"}), "say Do I look like a "+
    	"gossip to you. Go on now. I have my Duty to attend.",1);      	                   
    add_ask(({"Idrys"}), "say The true gods whom we serve Faithfully.",1); 
    add_ask(({"Hizarbin"}), "say The god of the sea. All must be blessed "+
    	"and purified in his name before venturing within.",1);  
    add_ask(({"statue", "fountain"}), "say It is blessed by Hizarbin. "+
    	"The power of the Idrys is a mystery not meant for us to know.",1);     	  
    add_cmdsoul(COM + "obj/npc_soul");
    update_hooks();
}

private string
my_long(void)
{
    string poss = CAP(HIS(TO));

    return CAP(HE(TO)) +" is a Defender of Sybarus.\n"+
	poss +" hair is "+ query_hair() +".\n"+
	poss +" eyes are "+ query_eyes() +".\n";
}

/*
 * equip_me is called in the npc when it is cloned by the
 * placer module.
 */
public void
equip_me(void)
{
    clone_object(COM + "obj/knife")->move(TO);
    clone_object(BAZAAR + "Obj/wield/bsword")->move(TO);
    command("wield all");
}

public void
unseen_hook(void)
{
    if (random(2))
	command("emote looks suspiciously around.");
}

public string
what_me(void)
{
    if (random(3))
	return "";

#ifdef LOG_QUESTIONS
    logrotate(LOG_QUESTIONS, TP->query_cap_name() +" asked "+
       query_name() +" about: "+ query_question() +".\n");
#endif

    return "say to "+ OB_NAME(TP) +
	" Find someone else to answer your questions.";
}

public int
special_attack(object victim)
{
    if (!present(victim, ENV()) || victim->query_ghost())
    {
	victim->stop_fight(TO);
	TO->stop_fight(victim);
	return 1;
    }

    switch (random(5))
    {
    case 0: command("punch");
	return 1;
    case 1: command("pommel");
	return 0;
    case 2: command("skick");
	return 1;
    case 3: command("neck");
	return 0;
    case 4: command("heal");
	return 0;
    }
    return 0;
}

static void
check_meet(object who, string oname)
{
    if (IS_INFIDEL(who))
	command("shout Its an infidel!");
}

static void
return_intro(object who, string oname)
{
    command("nod "+ oname);
}
