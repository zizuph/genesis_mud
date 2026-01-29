/* Carridin, 30 July 97 - A cute little pine weasel with wicked teeth */

#include "/d/Ansalon/common/defs.h"

inherit "/std/creature";
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */

inherit "/std/act/domove"; /* Include this if you want the creature to move */
inherit "/std/act/action"; /* Include this if you want your creature to act */

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

#define WEASELSUBLOC    "_ansalon_weasel_subloc"
#define WEASELNAME      "_ansalon_weasel"

/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2
#define A_TAIL  3

#define H_HEAD 0
#define H_BODY 1

int false_drop;

create_creature()
{
    set_name("weasel"); 
	add_name("rodent");
	add_name(WEASELNAME);
    add_name("animal");
	
    set_race_name("weasel");
    set_short("little pine weasel");
    set_adj(({"little", "pine" }));
    set_long("You're staring down at a cute, furry little critter, " +
		"its soft fur brown of the colour.\n");

	set_gender(2);

	default_config_mobile(5);

    set_skill(SS_DEFENCE, 30);
	set_skill(SS_AWARENESS,40);
    set_skill(SS_SWIM, 80);

    set_attack_unarmed(A_BITE,  8, 15, W_IMPALE, 40, "jaws");
    set_attack_unarmed(A_LCLAW, 15, 10, W_SLASH,  30, "left paw");
    set_attack_unarmed(A_RCLAW, 15, 10, W_SLASH,  30, "right paw");
    set_attack_unarmed(A_TAIL, 5, 1, W_BLUDGEON, 5, "furry tail");
   
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 80, "body");

	add_prop(LIVE_I_NEVERKNOWN,1);
	change_prop(OBJ_M_NO_GET,"@@get_weasel");
	add_prop(CONT_I_WEIGHT, 1000);
    add_prop(CONT_I_HEIGHT, 10);
    add_prop(CONT_I_VOLUME, 1000);
	add_prop("_live_i_leaps_tall_buildings_in_a_single_bound",1);

	set_act_time(5);
	add_act("kill parrot");
	add_act("emote wiggles its furry little tail.");
	add_act("kill parrot");
}

mixed
get_weasel()
{
	if (present(WEASELNAME,TP))
    {
    	return "One oversized rodent is enough, don't you think?\n";
    }
    else
        return 0;
}

void
attack_object(object ob)
{
	::attack_object(ob);
	if (ob->id("parrot"))
		add_prop(LIVE_O_ENEMY_CLING,ob);
}

int
is_weasel(object ob)
{
    if (ob->id(WEASELNAME))
        return 1;
    else
        return 0;
}

void
enter_env(object env, object from)
{
	::enter_env(env, from);

    if(env->query_prop(LIVE_I_IS))
    {
        object *t;
        t = filter(deep_inventory(env), is_weasel) - ({ TO });
    
        if (sizeof(t))
        {
            env->catch_msg("Deciding that one oversized rodent is more " +
            "than enough, you put the " + short() + " back on the ground.\n");
            tell_room(E(env), QCTNAME(env) + " ponders the " + short() +
            " for a moment, then puts it down on the ground.\n", env);
            set_alarm(0.0,0.0,&move(E(env)));
            false_drop = 1;
        }
        else
        {
    	    env->catch_msg("You tuck the cute " + short() + " safely under " +
    	    "your arm.\n");
            env->add_subloc(WEASELSUBLOC,TO);
            set_alarm(1.0,0.0,&set_no_show_composite(1));
        }
    }
}

void
leave_env(object from, object to)
{
    ::leave_env(from,to);
    if(!false_drop && from->query_prop(LIVE_I_IS))
    {
	    from->remove_subloc(WEASELSUBLOC);
        set_no_show_composite(0);
    }

    false_drop = 0;
}

string
show_subloc(string subloc, object me, object for_obj)
{
    if (subloc != WEASELSUBLOC)
        return ::show_subloc(subloc, me, for_obj);
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "You have a weasel tucked under your arm.\n";

    if (for_obj == me)
        return "You have a " + short() + " tucked under your arm.\n";
    else
        return C(PRONOUN(me)) + " has a " + short() + " tucked under " +
            POSSESSIVE(me) + " arm.\n";
}
