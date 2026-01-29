/*
 *  Alasia, a member of the Cuallach Dreugan.
 *
 */

#include "local.h"
#include "/d/Khalakhor/sys/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <language.h>
#include <filter_funs.h>
#include <composite.h>
#include <stdproperties.h>
#include <const.h>
#include <formulas.h>

inherit "/d/Khalakhor/std/npc/elf";
inherit INFO;

// prototypes
void arm_me();

// Global Vars
static string eye_colour = "sparkling emerald-green";
static string hair_style = "long, french-braided golden-red";
static mapping remembered = ([]);
static int last_attack = time();
static int preparing = 0;

void
create_khalakhor_elf()
{
    int xtra = random(16) + 5;

    set_name("alasia");
    set_living_name("alasia");
    set_gender(G_FEMALE);
    set_adj(({"lean","graceful"}));
    set_size_descs("very tall", "lean");
    set_long("@@my_long@@");
    set_title("the Blademistress of the Cuallach Dreugan");
    set_alignment(850 + (xtra * 10));

    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_LOOKS, 1);

    set_stats(({130 + xtra,170 + (2 * xtra),145 + xtra,130,140,100}));

    set_skill(SS_WEP_SWORD, 90 + xtra);
    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_2H_COMBAT, 74 + xtra);
    set_skill(SS_PARRY, 84 + xtra);
    set_skill(SS_DEFENCE, 74 + xtra);
    set_skill(SS_BLIND_COMBAT, 65);

    set_skill(SS_APPR_MON, 75);
    set_skill(SS_AWARENESS, 90);

    set_skill(SS_LANGUAGE, 65);
    set_skill(SS_SPELLCRAFT, 50);

    // Emotes!!!

    set_act_time(6 + random(6));
    add_act("emote strokes a lock of her "+hair_style+" hair.");
    add_act("sigh concern");
    add_act("think");
    add_act("emote glances in your direction with her "+eye_colour+" eyes.");
    add_act("smile softly at _calchdun_mage");
    add_act("emote fidgets with the white rose placed within her "+
      hair_style +" hair.");
    add_act("grin wicked at @@someones_name@@");
    add_act("chuckle quiet");
    add_act("emote shuts her "+eye_colour+" eyes for a moment, lost "+
      "in some thought.");
    add_act("smile mischeivously at @@someones_name@@");

    set_chat_time(9 + random(6));
    add_chat("to @@someones_name@@ Where might you be from stranger?");
    add_chat("These reports of goblin movement worry me, I hope they "+
      "stay in the Waste.");
    add_chat("The weather has been strange here lately.  I wonder "+
      "what is causing it to behave so oddly.");
    add_chat("The History of Clach Dun is quite impressive, is it not?");
    add_chat("Another goblin was found inside the sewers again.  "+
      "I want to send a patrol down there to find out "+
      "how these wretched things are entering unnoticed.");

    set_cact_time(3 + random(6));
    add_cact("emote glares at you, her "+eye_colour+" ablaze with fire.");
    add_cact("shout Attackers in the Throne Room, Guards!");
    add_cact("growl menacingly at @@attackers_name@@");
    add_cact("slap @@attackers_name@@");
    add_cact("emote gets a grim look of determination on her face.");

    set_cchat_time(5 + random(6));
    add_cchat("to @@attackers_name@@ Fool!! now you feel the sting on my blades!");
    add_cchat("You all shall regret this day for attacking me!");
    add_cchat("Aye tis a good day for you to die.");
    add_cchat("to @@attackers_name@@ I shall enjoy seeing you "+
      "hang from the gallows.");
    set_default_answer("I'm sorry I can not help thee with that.");
    arm_me();
}

string
my_long()
{
    string str;
    object attacker;

    str = query_The_name(this_player());

    if (objectp(attacker = query_attack()))
    {
	if (attacker == TP)
	    str += " dodges and weaves out of your way.  A grim "+
	    "expression of determination is upon her gentle face "+
	    "as she attempts to press her attack against you.\n";
	else
	    str += " is busy dodging and weaving out of "+
	    LANG_POSS(attacker->query_the_name(TP))+" blows.  A grim "+
	    "expression of determination is upon her gentle face as she "+
	    "attempts to press her attack against the vile "+
	    attacker->query_race_name()+".\n";
    }
    else
    {
	switch(TP->query_race())
	{
	case "elf":
	case "human":
	    if (TP->query_gender() == G_MALE)
		str = LANG_POSS(str)+" blazing golden-red hair, contains a "+
		"single white rose, which highlights her beauty.  "+
		"A serious, stern expression suddenly crosses her face, "+
		"making you wonder what thorns lie hidden under this "+
		"remarkable rose.\n";
	    else
		str += " is a woman of noticable beauty and grace.  Within "+
		"her golden-red hair is a single white rose, its scent "+
		"permiates the air.  She carries the trappings of a "+
		"distinguished warrior and looks quite capabile of "+
		"fending of any who dare attack her.\n";
	    break;
	case "gnome":
	case "dwarf":
	case "hobbit":
	    str += " is a woman of considerable height, even for elven "+
	    "kind.  As you stare upwards at her, you notice a single "+
	    "white rose adorns her golden-red locks.  A cold, fearsome "+
	    "expression is engraved in her face, as she looks over some "+
	    "reports.\n";
	    break;
	default:
	    str += " smells icky, as the scent of that filthy white rose "+
	    "adorning her hair, wafts through the air.  Taller and not "+
	    "nearly as scrawny as most elves.  She looks she would "+
	    "put up a good fight, for an elf that is.\n";
	}
    }
    str += "She has "+eye_colour+" eyes.\n";
    str += "She has "+hair_style+" hair.\n";  

    return str;
}

string
attackers_name()
{
    return OB_NAME(query_attack());
}
string
someones_name()
{
    return OB_NAME(ONE_OF(FILTER_CAN_SEE(FILTER_PLAYERS(all_inventory(ENV(TO))), TO)));
}

void
arm_me()
{
    setuid(); seteuid(getuid());
    clone_object(ARM_DIR + "alasia_dblmail")->move(TO);
    clone_object(ARM_DIR + "alasia_greaves")->move(TO);
    clone_object(WEP_DIR + "swordbreaker")->move(TO);
    clone_object(WEP_DIR + "caircith")->move(TO);

    command("wield all");
    command("wear all");
}

int
find_weak_spot(object enemy)
{
    int ac, i, weak_ac, weak_spot;
    int *hlocs;

    i = 0;
    hlocs = enemy->query_combat_object()->query_hitloc_id();
    weak_spot = hlocs[i];
    weak_ac = enemy->query_armour(weak_spot)->query_ac();
    while(++i < sizeof(hlocs))
    {
	ac = enemy->query_armour(hlocs[i])->query_ac();
	if (ac < weak_ac)
	{
	    weak_ac = ac;
	    weak_spot = hlocs[i];
	}
	// if equal weak spots randomly pick either one.
	else if (ac == weak_ac && !random(2))
	    weak_spot = hlocs[i];
    }
    return weak_spot;
}

int
special_attack(object victim)
{
    object dagger, sword;
    int pen;
    mixed hitres;
    string adjective, how;

    if (time() < last_attack + 20)
	return 0;
    if (!preparing)
    {
	preparing = 1;
	return 0;
    }
    else
	preparing = 0;
    // Make sure we are wiedling everything
    command("wield all");
    dagger = query_weapon(W_LEFT);
    sword = query_weapon(W_RIGHT);
    if (!objectp(sword) || sword->query_wt() != W_SWORD ||
      !objectp(dagger) || dagger->query_wt() != W_KNIFE)
	return 0;
    last_attack = time();
    if (query_combat_object()->cb_tohit(-1, 100, victim) != 1)
	pen = -1;
    else
    {
	pen = (sword->query_pen() + query_stat(SS_STR)) / 2; 
	pen = F_PENMOD(pen, query_skill(SS_WEP_SWORD));
    }
    hitres = victim->hit_me(pen, W_SLASH, TO, -1, find_weak_spot(victim));
    if (victim->query_wiz_level())
	victim->catch_tell("Attack pen: "+pen+"\nAttack Damage: "+ hitres[3]+"\n");

    switch(hitres[4])
    {
    case A_LEGS:
	adjective = "crouches low and ";
	break;
    case A_HEAD:
	adjective = "aims high and ";
	break;
    case A_TORSO:
	adjective = "follows through and ";
	break;
    default:
	adjective = "";
    }
    switch(hitres[0])
    {
    case -1:
    case 0:
	how = "unharmed";
	break;
    case 1..10:
	how = "barely scratched";
	break;
    case 11..20:
	how = "scratched";
	break;       
    case 21..35:
	how = "slightly injured";
	break;       
    case 36..50:
	how = "injured";
	break;       
    case 51..70:
	how = "badly slashed";
	break;       
    case 71..90:
	how = "horribly slashed";
	break;       
    default:
	how = "utterly massacred";
	break;       
    }
    victim->catch_tell("Guarding with "+HIS_HER(TO)+" "+dagger->short()+
      " "+query_the_name(victim)+" "+adjective+ "slashes at your "+hitres[1]+
      " with "+HIS_HER(TO)+" "+sword->short()+", leaving you feeling "+ how +
      " from "+HIS_HER(TO)+" counter attack.\n");
    tell_watcher("Guarding with "+HIS_HER(TO)+" "+dagger->short()+" "+
      QTNAME(TO)+" "+adjective+ "slashes at "+QTNAME(victim) +" "+hitres[1]+
      " with "+HIS_HER(TO)+" "+sword->short()+", leaving "+QTNAME(victim)+
      " feeling "+how+" from "+LANG_POSS(QTNAME(TO))+" counter attack.\n"
      , victim);
    return 1;
}

void
add_introduced(string str)
{
    kb_add_introduced(str);
}

void
init_living()
{
    ::init_living();
    kb_init_living();
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    kb_enter_env(env,from);
}

int
hook_return_intro(string str)
{
    if (!remembered[str])
    {
	command("say Tis a pleasure to meet thee, "+capitalize(str)+
	  ", you are in the presence of "+query_name()+" "+query_title()+".");
	remembered[str] = "nice";
	present(str, environment())->add_introduced("alasia");
    }
    else if (remembered[str] == "bad")
    {
	command("scowl");
	command("say Begone "+capitalize(str)+", before I decide to remove you "+
	  "forceably from my presence.");
    }
    else
    {
	command("giggle");
	command("ruffle "+str);
	command("say I have not forgotten you, "+ capitalize(str)+
	  ", who could forget a face like that.");
    }
    return 1;
}

void
clachdun_history()
{
    my_communicate("Clach Dun History.");
}

void
clachdun_advisor()
{
    my_communicate("F'yar??");
    my_communicate("I am charged with his protection.");
    command("smile soft at f'yar");
    my_communicate("We have been bonded as the tradition of the "+
      "Cuallach Dreugan requires of us.");
}

void
clachdun_blademistress()
{
    command("chuckle");
    my_communicate("Well that is an easy question to answer.");
    my_communicate("The Blademistress of Clach Dun would be me.");
}
