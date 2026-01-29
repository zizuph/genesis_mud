//
// crossbow.c
//
// An attempt to do a crossbow weapon. Currently, I will
// refrain from making this a room to room weapon, though
// I might do it in Moria, as Moria has been designed with
// positions.
//
// The idea is, that a crossbow can be used *before* you
// are engaged in melee combat. It will do much damage if
// you hit, but the reloading time of 20-30 seconds, will
// ensure balancing things.
// 
// Sir Rogon.

#include "defs.h"
#include "/d/Shire/moria/include/bows.h"

inherit "/std/weapon";
inherit "/d/Immortal/rogon/open/parse";

#include <language.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <tasks.h>

#define MISSILE_PENETRATION_FACTOR 5

/*
 * missile_type is the type of missile which fits in this weapon.
 * Can be: LIGHT_BOLT, HEAVY_BOLT or ARBALEST_BOLT.
 */
int missile_type; 

/* What missile is loaded? */
object loaded_missile;

/* Reloading time. */
int reloading_time;

/* The bow's penetration value. */
int bow_pen;

/* The bow's "to hit" value. */
int bow_hit;

/* Aiming at? */
object aim_at;

#define DEBUG(str) find_player("rogon")->catch_msg("#crossbow#" + str)

void set_missile_type(int type) {
    missile_type = type;
}

int query_missile_type() {
    return missile_type;
}

void set_bow_pen(int cl)
{
    bow_pen = cl;
}

int query_bow_pen()
{
    return bow_pen;
}

void set_bow_hit(int cl)
{
    bow_hit = cl;
}

int query_bow_hit()
{
    return bow_hit;
}

void set_reloading_time(int time) {
    reloading_time = time;
}

int query_reloading_time() {
    return reloading_time;
}

object query_loaded_missile() {
    return loaded_missile;
}

nomask void
create_weapon()
{
    set_name("crossbow");
    set_adj("heavy");
    set_long("You are looking at a beautifully adorned heavy crossbow.\n");

    set_missile_type(HEAVY_CROSSBOW_BOLT);
    set_bow_pen(100);
    set_bow_hit(100);
    set_reloading_time(20);

    this_object()->create_missile_weapon();

    set_wt(W_CLUB); /* Melee combat! A club. */
    set_hit(20);
    set_pen(14);
    set_hands(W_BOTH);
    set_likely_break(80);
}

varargs string
long(string what, object for_obj)
{
    string str = ::long(what, for_obj);

    if (stringp(what))
	return str;

    if (loaded_missile) {
	str += "The " + short(for_obj) + " is loaded and ready with " +
	       LANG_ASHORT(loaded_missile) + ". ";
    }
    str += 
	"This weapon is a \"club\", but this is simply because " +
	"you can use it as a club in melee combat. To shoot " +
	"with it, you will need the correct arrows/bolts.\n";
    return str;
}

init()
{
    ::init();
    add_action("do_reload", "reload");
    add_action("do_reload", "load");
/*    add_action("do_unstring", "unstring"); */
/*    add_action("do_string", "string"); */
/*    add_action("do_unload", "unload"); */
    add_action("do_aim", "aim");
    add_action("do_fire", "fire");
    add_action("do_fire", "shoot");
}

int
do_reload(string arg)
{
    object what, with, stop;
    int bt;
    
    if (!parse_command(arg, TP, "%o 'with' %o", what, with) &&
	!parse_command(arg, TP, "%o 'into' [the] %o", with, what))
	return notify_fail(CAP(query_verb()) + " <what> with <what>?\n");
    
    if (what != TO)
	return notify_fail(CAP(query_verb()) + " what?\n");

    if (!(bt = with->query_missile_type()))
	return notify_fail("That seems not to be a missile.\n");

    if (bt != missile_type) {
	write("Sorry, that missile is of wrong type.\n");
	return 1;
    }

    if (objectp(loaded_missile)) {
	write("But, you have already loaded " + LANG_ASHORT(loaded_missile) +
	      " on " + LANG_THESHORT(TO) + "!\n");
	return 1;
    }

    FIXEUID;

    if (!reloading_time)
	reloading_time = 20;

    stop = clone_object("/std/paralyze");
    stop -> set_stop_object(TO);
    stop -> set_stop_fun("stop_reloading");
    stop -> set_fail_message("You are busy loading " + LANG_ASHORT(with) +
			     " onto your " + short() + ".\n");
    stop -> set_remove_time(reloading_time);
    stop -> add_prop("_obj_o_loading", with);
    stop -> move(TP);

    write("You start loading " + LANG_ASHORT(with) + " onto your " + 
	  short() + ".\n");
    write("You can stop your reloading by typing 'stop reloading'.\n");
    return 1;
}

int
stop_reloading(mixed arg)
{
    if (stringp(arg) && (arg == "reloading" || arg == "loading")) {
	write("You stop reloading your " + short() + ".\n");
	return 1;
    } else if (objectp(arg)) {
	loaded_missile = previous_object()->query_prop("_obj_o_loading");
	loaded_missile->move(TO, 1);
	arg->catch_msg("You successfully managed to load the "+short()+ ".\n");
	return 1;
    } else {
	write("Stop what? Stop reloading?\n");
	return 1;
    }
}

mixed
parse_to_attack(string arg)
{
    string rest;
    string verb = CAP(query_verb());
    mixed what, objs;

    if (!query_wielded())
	return notify_fail("Perhaps wield it first?\n");

    if (!strlen(arg))
	rest = "";
    else if (parse_command(arg, TP, "%i %s", what, rest))
    {
	what = NORMAL_ACCESS(what, 0, 0);
	if (!sizeof(what))
	    return notify_fail(verb + " what??\n");
	if (sizeof(what) > 1)
	    return notify_fail(verb + " only one thing at a time.\n");
	if (what[0] != TO)
	    return notify_fail(verb + ".. Eh? What?\n");
    } else
	rest = arg;
    
    objs = parse_attack(rest, "[at]", 0);

    if (!sizeof(objs))
	return notify_fail(verb + " at whom?\n");
    if (sizeof(objs) > 1)
	return notify_fail(verb + " at one only...\n");

    return objs[0];
}

int
do_aim(string arg)
{
    object obj;

    if (!(obj = parse_to_attack(arg)))
	return 0;

    if (!loaded_missile)
	return notify_fail("Eh.. Perhaps load a missile in the " + short() +
			   " first?\n");

    TP->catch_msg("You aim your " + short() + " at " + QTNAME(obj) + ".\n");
    obj->catch_msg("Oops, " + QTNAME(TP) + " aims " + HIS_HER(TP) + 
		   " " + short() + " at you!\n");
    tell_room(ETP,
	      QCTNAME(TP) + " aims " + HIS_HER(TP) + " " + short() +
	      " at " + QTNAME(obj) + ".\n", ({ TP, obj }));

    aim_at = obj;

    return 1;
}

int
do_fire(string arg)
{
    object target;
    int tohit, pen;
    int succ;
    mixed res;
    string where, how, verb;
    int skill;
    int diff;

    target = parse_to_attack(arg);
    verb = query_verb();

    if (!target)
	target = aim_at;

    if (!target)
	return 0;

    if (!CAN_SEE(TP, target))
	return 0;

    if (!loaded_missile)
	return notify_fail("Eh.. Perhaps load a missile into the " + 
			   short() + " first?\n");
	
    // ---***--- Fun part starts, do we actually hit the target? ---***---
    
    /*
     * Hmm, let's see:
     * + For attacker : Dexterity, skills in missile, tohit large.
     * - For attacker : In melee combat (?)
     * + For defender : Not encumbred, high dexterity, cover.
     *
     */       

    skill = TP->query_skill(SS_WEP_MISSILE);
    tohit = (bow_hit + loaded_missile->query_missile_hit()) / 2;

    diff = TASK_DIFFICULT - tohit;
    diff -= target->query_encumbrance_weight();
    diff += TP->query_encumbrance_weight();

    diff += (TP->query_armour(TS_RARM) ? 50 : 0)
	  + (TP->query_armour(TS_LARM) ? 50 : 0);

    if (ETP->query_prop(ROOM_I_INSIDE)) 
	where = "wall";
    else
	where = "ground";

    if (TP->resolve_task(diff, ({ TS_DEX, SS_WEP_MISSILE }),
			 target, ({ TS_DEX, SS_ACROBAT })) < 0)
    {
	TP->catch_msg("You shoot at " + QTNAME(target) + ", but the " +
		      loaded_missile->short() + " misses completely!\n");
	target->catch_msg(QCTNAME(TP) + " shoots at you with his " +
			  HIS_HER(TP) + " " + QSHORT(TO) + ", but misses " +
			  "completely!\n");
	tell_room(ETP, QCTNAME(TP) + " shoots " + LANG_ASHORT(loaded_missile) +
		  " at " + QTNAME(target) + " with " + LANG_ASHORT(TO) +
		  ", but it misses completely!\n");

	loaded_missile->reduce_quality(random(50)+1); 

	if (loaded_missile->query_missile_quality() <= 0) {
	    tell_room(ETP, "The " + loaded_missile->short() + " schmacks " +
		      "into the " + where + " and breaks into pieces.\n");
	    loaded_missile->remove_object();
	}
	else {
	    loaded_missile->move(ETP);
	}
	loaded_missile = 0;
	return 1;
    }

    /*
     * Did actually hit!
     */
    
    pen = bow_pen + loaded_missile->query_pen();
    pen = MISSILE_PENETRATION_FACTOR * F_PENMOD(pen, skill);

    if (TP->query_wiz_level())
	write("WIZINFO: pen = " + pen + "\n");

    res = target->hit_me(pen, W_IMPALE, TP, -1);

    if (TP->query_wiz_level())
	write(sprintf("WIZINFO: proc hurt = %d%%, hitloc = %s, " +
		      "phit = %d%%, dam = %d.\n", 
		      res[0], res[1], res[2], res[3]));
    if (res[0] > 40)
	how = " extremely hard.";
    else if (res[0] > 25)
	how = " very hard.";
    else if (res[0] > 12)
	how = " hard.";
    else
	how = ".";

    TP->catch_msg("You " + verb + " the " + loaded_missile->short() + 
		  " at " + QTNAME(target) + 
		  " and hit " + HIS_HER(target) + " " + res[1] + how + "\n");
    target->catch_msg(QCTNAME(TP) + " " + verb + "s " + 
		      LANG_ASHORT(loaded_missile) + " at you and hits your " +
		      res[1] + " " + how + "\n");
    say(QCTNAME(TP) + " " + verb + "s " + LANG_ASHORT(loaded_missile) + 
	" at " + QTNAME(target) + " and hits " + HIS_HER(target) + " " + 
	res[1] + how + "\n", ({target,TP}));
    
    tell_room(ENV(TP), "The " + QSHORT(loaded_missile) + " lands in the " 
	      + where + ".\n");

    if (target->query_hp() <= 0) {
	target->do_die(TP);
    }

    loaded_missile->move(ETP);
    loaded_missile = 0;
    return 1;
}
