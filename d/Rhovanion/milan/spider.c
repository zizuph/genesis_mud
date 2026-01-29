/*
spiders are interesting creatures.  They can only bite.	 But if they
bite you you have a random chance of being stunned, and they will try to
web you up.
*/
#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/chat";
inherit "/std/act/attack";

#include "/d/Rhovanion/lib/kill_log.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include <composite.h>
#include "/d/Rhovanion/defs.h"

#define WEB	(OBJ_DIR+"web")
#define LEG	(OBJ_DIR+"spider_leg")

#define LEG_IS_LIVE "_leg_is_live"
#define A_BITE 0
#define H_HEAD 0
#define H_BODY 1

static int number_of_legs_missing = 0;
static string *list = ({ "Bite it!", "Sting it!", "Web it!",
			 "It looks plump and tasty!"});
static string *list1 = ({"I want to eat it now!", "I think it's dead now!",
			 "Shelob says you should hang them for days first.",
			 "It's still wriggling!  It's not dead yet!",
			 "I am hungry now!",
			 "Are you sure this web will hold it?",
			 "Why don't you sting it again?",
			 "Why do we always have to do what you say anyhow?"});
static string *list2 = ({"I want something to eat!", "Plump and tasty!",
			 "I am hungry now!"});

string
spider_chat()
{
    if (present("web", ENV(TO))) return ONE_OF_LIST(list1);
    return ONE_OF_LIST(list2);
}

string
spider_cchat() { return ONE_OF_LIST(list); }

/*** prototype ***/
private void sting_web(int arg);

public void
create_creature()
{
    int i;

    set_name("spider");
    set_pname("spiders");
    set_race_name("spider");
    set_short("black spider");
    set_pshort("black spiders");
    set_adj(({"black", "menacing" }));
    set_long("@@my_long@@");
    set_gender(G_NEUTER);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_stats(({ 55, 150, 80, 29, 31, 100}));

    set_attack_unarmed(A_BITE, 15, 20, W_IMPALE, 100, "jaws");

    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 20, 25, 30, 20 }), 72, "body");
    for (i=0; i<8; i++)
	set_hitloc_unarmed(2+i, ({ 30, 20, 20, 20 }), 1, "leg");
    add_leftover(LEG, "leg", 8, 0, 0, 0);

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_AWARENESS, 100);

    set_chat_time(2);  add_chat("@@spider_chat@@");
    set_cchat_time(2); add_cchat("@@spider_cchat@@");

    set_alarm(0.0, 0.0, &sting_web(0));
    set_aggressive(1);
}

private void
do_paralyse(object who, int time)
{
    object ob;

    seteuid(getuid());
    ob = clone_object("/std/paralyze");
    ob->set_name("_spider_paralyze_");
    ob->set_no_show(1);
    ob->set_remove_time(time);
    ob->set_stop_message("You shake your head as you regain your senses!\n");
    ob->set_fail_message("Spider poison paralyses you!\n");
    ob->set_stop_verb("depart"); /* No command to stop paralyze! */
    ob->set_stop_object(0);	 /* Use the messages set above */
    ob->move(who, 1);		 /* Now DO the paralyze */
    who->stop_fight(who->query_attack());
}

/* Function name: special_attack
 * Description:	  Poison and web him!
 * Argument:	  enemy - object we want to poison and web
 * Returns:	  1 - poisoned or webbed, 0 - make standard atack
 */
public int
special_attack(object enemy)
{
    object *weapons, room;
    mixed ob, *hitresult;

    if (number_of_legs_missing > 5) return 1; /* can't move anymore */
    room = ENV(TO);
    if (present("_spider_paralyze_", enemy))
    {
	if (random(4+number_of_legs_missing)) return 1; /* failed to web */
	seteuid(getuid());
	ob = clone_object(WEB);
	ob->move(room);
	enemy->catch_msg(QCTNAME(TO) + " spins a web around you!\n");
	tell_room(room, QCTNAME(TO) + " spins a web around " +
			QTNAME(enemy)+".\n", enemy);
	enemy->move(ob);
	ob->add_prop(CONT_I_CLOSED, 1);
	TO->stop_fight(enemy);
	return 1;
    }
    if (random(7 + number_of_legs_missing)) return 0;
    hitresult = enemy->hit_me(F_PENMOD(20+random(20), 40+random(40)),
			      W_IMPALE, TO, -1);
    enemy->catch_msg(QCTNAME(TO) + " stings you!\n");
    enemy->tell_watcher(QCTNAME(TO)+" stings "+QTNAME(enemy)+".\n", enemy);
    if (hitresult[0] < 1) return 1;
    enemy->catch_msg("You are stunned by " + QTNAME(TO) + "'s bite.\n");
    enemy->tell_watcher(QCTNAME(enemy) + " is stunned by " +
			QTNAME(TO) + "'s bite.\n", enemy);
    weapons = ({ });
    if (objectp(ob = enemy->query_weapon(W_RIGHT)) && !ob->move(room))
	weapons += ({ ob });
    if (objectp(ob = enemy->query_weapon(W_LEFT)) && !ob->move(room))
	weapons += ({ ob });
    if (objectp(ob = enemy->query_weapon(W_BOTH)) && !ob->move(room))
	weapons += ({ ob });
    if (sizeof(weapons))
    {
	enemy->catch_msg("You drop " + COMPOSITE_DEAD(weapons) + ".\n");
	tell_room(room, QCTNAME(enemy) + " drops " +
			COMPOSITE_DEAD(weapons) + ".\n", enemy);
    }
    do_paralyse(enemy, MAX(1, hitresult[2]));
    if (enemy->query_hp() <= 0) enemy->do_die(TO);
    return 1;
}

void
sting_web(int arg)
{
    int i;
    object ob, *in;
    mixed *hitresult;

    if (query_attack())
    {
	set_alarm(itof(random(20)+10), 0.0, &sting_web(0));
	return; /* fight first */
    }
    if ((number_of_legs_missing < 6) && (ob = present("web", ENV(TO))))
    {
	set_alarm(itof(random(20)+10), 0.0, &sting_web(0));
	if (sizeof(in = FILTER_LIVE(all_inventory(ob))))
	{
	    ob = in[0];
	    hitresult = ob->hit_me(F_PENMOD(40+random(20), 50+random(40)),
				   W_IMPALE, TO, -1);
	    ob->catch_msg("Something stings you!\n");
	    tell_room(ENV(), QCTNAME(TO)+" stings the web.\n");

	    if (!present("_spider_paralyze_", ob) && (hitresult[0] > 0))
	    {
		ob->catch_msg("You are stunned.\n");
		do_paralyse(ob, MAX(1, hitresult[2]/2));
	    }
	    if (ob->query_hp() <= 0)
	    {
		ob->do_die(TO);
		tell_room(ENV(), QCTNAME(TO)+
                                 " sucks something from the web.\n");
	    }
	    return;
	}
	tell_room(ENV(), QCTNAME(TO)+" unweaves the web.\n");
	ob->remove_object();
	return;
    }
    if (sizeof(FILTER_PLAYERS(all_inventory(ENV(TO)))))
    {
	set_alarm(itof(random(20)+10), 0.0, &sting_web(0));
	return;
    }
    if (arg == 10) remove_object();
    else set_alarm(itof(random(20)+10), 0.0, &sting_web(arg+1));
}

void
slow_init_attack(object tp)
{
    if (!tp || query_attack() || !present(tp, ENV(TO))) return;
    aggressive_attack(tp);
}

void
init_attack()
{
    if (TP->query_wiz_level() || (TP->query_race_name() == "spider") ||
	TP->query_invis() || (number_of_legs_missing > 5))
	return;
    write(QCTNAME(TO) + " is running to you on its " +
	  LANG_WNUM(8-number_of_legs_missing) + " legs.\n");
    set_alarm(itof(1 + (2 * number_of_legs_missing)), 0.0,
	      &slow_init_attack(TP));
}

void
my_remove_hitloc(int id, object att)
{
    string text = (TO->query_combat_object())->query_hitloc(id)[2];
    object leg;

    if (remove_hitloc(id))
    {
	number_of_legs_missing += 1;
	remove_hitloc(H_BODY);
	set_hitloc_unarmed(H_BODY, ({ 20, 25, 30, 20 }),
			   72 + number_of_legs_missing, "body");
	TO->set_stat_extra(SS_DEX,
	     -number_of_legs_missing * TO->query_stat(SS_DEX) / 10);
	TO->set_skill_extra(SS_DEFENCE,
	     -number_of_legs_missing * TO->query_skill(SS_DEFENCE) / 10);
	add_leftover(LEG, "leg", 8-number_of_legs_missing, 0, 0, 0);

	leg = clone_object(LEG);
	leg->add_prop(LEG_IS_LIVE, 1);
	leg->move(ENV(TO));

	att->catch_msg("You chopped off the " + text + " from " +
		       QTNAME(TO) + ".\n");
	tell_room(ENV(TO),QCTNAME(att) + " chopped off the " + text +
			  " from " + QTNAME(TO) + ".\n", att);
    }
    return;
}

void
cr_got_hit(int hid, int ph, object att, int aid, int dt, int dam)
{
    ::cr_got_hit(hid, ph, att, aid, dt, dam);
    if ((hid > 1) && dam) my_remove_hitloc(hid, att);
    return;
}

string
my_long()
{
    int i = 8 - number_of_legs_missing;
    switch(i)
    {
	case 8: return "It looks rather menacing!\n";
	case 0: return "It is lying on the ground unable to move " +
		       "without legs.\n";
	case 1: return "It is lying on the ground stretching his last " +
		       "leg occationaly.\n";
	case 2: return "It is lying on the ground trying to push itself " +
		       "away with its last two legs.\n";
	default: return "It looks menacing as it moves on its "+
			LANG_WNUM(i)+" legs towards you.\n";
    }
}
