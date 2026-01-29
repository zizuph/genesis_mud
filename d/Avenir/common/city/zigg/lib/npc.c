/*
 *  file name:   npc.c
 *  creator:     Lucius
 *  purpose:	Standard inherit for ziggurat npc's
 *  note(s):
 *  bug(s):
 *  to-do:
 */
#pragma no_clone
#pragma strict_types

inherit "/std/monster";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/inherit/sigil";
inherit "/d/Avenir/inherit/hair_eyes";
inherit "/d/Avenir/inherit/logrotate";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "../zigg.h"

public static string skintone;
public static int check_alarm, prestige;

#define TYR_COLOR  "/d/Cirath/tyr/paint/colourob"

public void
zig_npc(void)
{
}

/* Over-ride this to fine-tune clothing choices. */
static void
add_clothing(void)
{
    object cm = CM->get_this_object();

    cm->set_cset("random");

    if (query_gender() == G_FEMALE)
	cm->make_girl(TO, -1);
    else
	cm->make_boy(TO, -1);

    command("wear garments");
}

static void
skin_tone(string str)
{
    object ob = present("_colour_ob_");

    if (!strlen(str))
    {
	if (objectp(ob))
	    ob->remove_object();

	return;
    }

    skintone = str;

    if (!objectp(ob))
    {
	ob = clone_object(TYR_COLOR);
	ob->move(this_object());
    }

    ob->set_colour_desc(skintone);
}

static nomask void
create_monster(void)
{
    MAKE_SYBARITE;

    add_name("sybarite");

    set_random_size_descs();
    skin_tone("pale, translucent white");

    zig_npc();

    add_clothing();
}

/*
 * Proud to be sybarite.
 */
public string 
query_exp_title(void)
{
    return "sybarite "+ ::query_exp_title();
}

/*
 * A standard sybarite accent.
 */
public string 
race_sound(void)
{
    if (query_gender())
	return "speaks with a lilting accent";
    else
	return "mellifluously intones";
}

/* Modified from original, more useful. */
public varargs void
default_config_npc(int lvl, int ran = 0)
{
    for (int i = 0; i < SS_NO_EXP_STATS; i++)
	set_base_stat(i, (lvl ? lvl : 5), ran);

    stats_to_acc_exp();
    refresh_living();
}

public void
do_die(object killer)
{
    if (query_hp() > 0)
	return 0;

    if (!killer)
	killer = previous_object();

    /* Mark the murderers */
    WRATHOBJ->load_me();
    WRATHOBJ->mark_enemy(killer);

    ::do_die(killer);
}

public void
attacked_by(object ob)
{
    ::attacked_by(ob);

    /* Give our team a chance to help. */
    foreach(object who : query_team_others())
	who->notify_ob_attacked_me(this_object(), ob);
}

static void
help_friend(object who, object foe)
{
    /* Ignore if attacking or foe isn't nearby. */
    if (query_attack() || !present(foe, environment()))
	return;

    say(QCTNAME(this_object()) + " assists " +
	QTNAME(who) +" and attacks "+ QTNAME(foe) +".\n",
	({ this_object(), who, foe }) );

    tell_object(foe, query_The_name(foe) +" attacks you!\n");

    attack_object(foe);
    add_prop(LIVE_O_LAST_KILL, foe);
}   

public void
notify_ob_attacked_me(object me, object foe)
{
    float ran;

    /* Ignore if attacking or friend isn't nearby. */
    if (query_attack() || !present(me, environment()))
	return;

    ran = itof(1 + random(3));
    set_alarm(ran, 0.0, &help_friend(me, foe));
}

private static mapping race_conv = ([
    "half-elf"   : "elf",
    "shadow-elf" : "elf",
    "shadow elf" : "elf",
]);

/*
 * Try to fool things into thinking we are a different race
 * so that we get height/width descs.
 */
public string
query_race(void)
{
    string race = ::query_race();

    if (race_conv[race])
	return race_conv[race];
    else
	return race;
}

public string
query_long(void)
{
    string res;

    if (!notmet_me(TP))
    {
	res = TO->query_name() + " is " +
	    LANG_ADDART(TO->query_nonmet_name()) +
	    ", presenting " + TO->query_objective() + "self as:\n" +
	    TO->query_presentation() + ".\n";
    }
    else if (!(TO->short(TP)))
    {
	return "";
    }
    else
    {
	res = CAP(TO->query_pronoun()) + " is " +
	    LANG_ADDART(TO->short(TP)) +".\n";
    }

    if (obj_long)
	res += check_call(obj_long);

    return res;
}

static void
check_meet(object who, string oname)	{  }

private nomask void
init_meet(object who)
{
    check_alarm = 0;

    if (objectp(who) && present(who, environment()))
	check_meet(who, OB_NAME(who));
}

public void
init_living(void)
{
    ::init_living();

    if (!check_alarm &&
	query_interactive(TP) && CAN_SEE(TO, TP))
    {
	float delay = 1.5 + itof(random(2));
	check_alarm = set_alarm(delay, 0.0, &init_meet(TP));
    }
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if (subloc == hair_subloc())
	return gelan_hair();

    if (subloc == eyes_subloc())
	return gelan_eyes();

    return ::show_subloc(subloc, on, for_obj);
}

/* Add the dancer commands. */
static void
add_dancer(void)
{
    add_cmdsoul(COM + "clubs/dance/dancer_soul");
    update_hooks();
}

/* Add the mummer commands. */
static void
add_mummer(void)
{
    add_cmdsoul(COM + "clubs/mummer/mummer_soul");
    update_hooks();
}

/*
 * Function name: set_knight_prestige
 * Description:   Set the prestige changing value in the mobile
 * Arguments:     pres - the prestige, if > 0 it will add to the acc, if < 0
 *                       it will add to the stat.
 */
public void
set_knight_prestige(int pres)	{ prestige = pres; }

/*
 * Function name: query_knight_prestige
 * Description:   Return the prestige this monster will affect a knight.
 * Returns:       The prestige.
 */
public int
query_knight_prestige(void)	{ return prestige; }
