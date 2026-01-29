/*
 * Mounttrainer.c
 * A Warrior of supreme skill in the area of mounted combat
 * who has decided to leave the guilds of the puissant and 
 * skilled horseman to train adventurers in the high skill of
 * mounted combat.  He wanders through the realm of Rhovanion
 * Coded by Elanor of Rhovanion late of Gondor July 1994
 * Modified for the Riders of Rohan by Elessar, Aug 1994
 */
inherit "/std/monster";
inherit "/lib/skill_raise";

#include "/d/Gondor/defs.h"
#include "/d/Rhovanion/lib/binbit.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <tasks.h>
#include "/secure/std.h"
#define KILLER_LOG   "/d/Gondor/log/freawine_killer"

void init_skills();

#define KILLERS_TO_REMEMBER	20
#define	MULTIPLIER_FOR_KILLER	3

string *list_introduced = ({ });
string *list_of_killers = ({ });

void
init_killers()
{
    string text;

    seteuid(getuid());
    text = read_file(KILLER_LOG);
    if (text)
	list_of_killers = explode(text, "\n");
    list_of_killers -= ({});
}

int
player_is_killer(string name)
{
    return member_array(name, list_of_killers) >= 0;
}

void
add_killer(mixed killer)
{
    string text;

    if (objectp(killer))
	killer = killer->query_real_name();
    if (!killer)
	return;
    if (!SECURITY->exist_player(killer))
	return;
    list_of_killers -= ({ killer });
    list_of_killers += ({ killer });
    if (sizeof(list_of_killers) > KILLERS_TO_REMEMBER)
	list_of_killers = list_of_killers[sizeof(list_of_killers)-KILLERS_TO_REMEMBER .. sizeof(list_of_killers) - 1];
    text = implode(list_of_killers, "\n");
    seteuid(getuid());
    rm(KILLER_LOG);
    write_file(KILLER_LOG, text);
}

void create_monster()
{
    set_living_name("freawine");
    set_title("trainer");
    set_name("freawine");
    set_race_name("human");
    set_adj(({"fair","tall","old","wise","blond","bow legged"}));
    add_name("rohirrim");
    add_name("man");
    set_short("tall rohirrim riding a great grey horse");
    set_long("This aging rohirrim still retains flowing blond hair,\n"+
      "and a proud and fair face. Riding a great grey horse,\n"+
      "a mearas from Rohan, he is a skilled trainer of riding.\n");
    set_stats(({ 130+random(55), 160+random(35), 160+random(35), 
		  90+random(10),  95+random(10), 140+random(40) }));
    set_learn_pref(({1,1,1,0,0,0,}));
    set_hp(10000);
    set_mana(10000);
    set_fatigue(1000);
    set_alignment(900);
    set_skill(SS_WEP_SWORD,100);
    set_skill(SS_MOUNTED_COMBAT,90);
    set_skill(SS_WEP_POLEARM,100);
    set_skill(SS_WEP_KNIFE,70);
    set_skill(SS_PARRY,90);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_AWARENESS,100);
    set_skill(SS_RIDING,100);
   
    add_prop(CONT_I_HEIGHT,193);
    add_prop(CONT_I_WEIGHT,98000);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(LIVE_I_SEE_DARK,1);

    add_item("horse","@@exa_horse");
    set_chat_time(15);
    add_chat("What's the use of a horse if you cannot fight from it?");
    add_chat("I could show you a thing or two when it comes to horsemanship.");
    add_chat("Fighting on horseback is a mixture of many skills!");
    add_chat("Our Mearas are the best horses!");
    add_chat("I can help all in one of the skills of horsemanship.");
    set_cchat_time(2);
    add_cchat("For the Mark! Freawine for the Mark!");
    add_cchat("I will teach you not to attack me!");
    trig_new("%w 'introduces' %s","react_introduce");

    init_skills();
    init_killers();

    call_out("arm_me", 1);
}

string *
train_text(int skill)
{
    string what, does, *text;

    switch (skill) {
	case SS_RIDING:
	    what="ride on the back of a steed";
	    does=what;
	    break;
	default:
	    what="do nothing.  THIS IS A BUG";
	    does="meditate";
	    break;
    }
    text = ({ what, does });
    return text;
}

void
init_skills()
{
    create_skill_raise();

    sk_add_train(SS_RIDING,
		 train_text(SS_RIDING),
		 0,
		 0,
		 30);
}

void
sk_hook_raise_rank(int snum, int to_lev, int cost)
{
    string rank, long_str;

    rank = sk_rank(to_lev);

    this_player()->catch_msg("You improve your ability to " +
			     sk_tdesc[snum][0] + ".\n" +
			     "You achieve the rank of " +
			     rank + ".\n");
    long_str = " improves " + this_player()->query_possessive() +
	       " ability to " + sk_tdesc[snum][1] + " and receives "+
	       "the rank of " + rank + ".\n";
    say( ({ this_player()->query_Met_name() + long_str,
	    capitalize(this_player()->query_unmet_name()) + long_str }) );
}

int
sk_cost(int skill, int from, int to)
{
    int cost;

    cost = ::sk_cost(skill, from, to);
    if (player_is_killer(this_player()->query_real_name()))
	cost *= MULTIPLIER_FOR_KILLER;
    return cost;
}

int
sk_improve(string str)
{
    if (this_player()->query_race_name() == "goblin") {
	notify_fail("I don't train goblins or orcs!\n");
	return 0;
    }
    return ::sk_improve(str);
}

void
arm_me()
{
    object ob;

    seteuid(getuid());

    ob = clone_object("/d/Gondor/rohan/edoras/obj/rosword");
    ob->move(TO);
    command("wield all");

    ob = clone_object("/d/Gondor/rohan/edoras/obj/chainmail");
    ob->move(TO);

    ob = clone_object("/d/Gondor/rohan/edoras/obj/rohelm");
    ob->move(TO);

    ob = clone_object("/d/Gondor/rohan/edoras/obj/roshield");
    ob->move(TO);
    command("wear all");
}

int
second_life(mixed killer)
{
    add_killer(killer);
}


void
init_living()
{
    ::init_living();
    init_skill_raise();
}

string
exa_horse()
{
  return "The horse is a Meara, one of the great horses bred by the Rohirrim.\n"+
    "It looks powerful and strong, greater than any normal horse you\n"+
    "have seen before, and it carries its rider with ease.\n";
}

