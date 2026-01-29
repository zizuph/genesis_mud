/* -*- Mode: C -*-
 *
 * obj/wep/mage-pole.c
 *
 * Skippern 20(c)02
 *
 * This is the main weapon of the magician in Dol Amroth. It is a unique,
 * and when it is not cloned, the mage-dagger from the same directory 
 * as this will be cloned. This quarterstaff is a good weapon with extra
 * damage and special abilities.
 */
inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../../defs.h"

#define HIT          50
#define PEN          25
#define ROOT_MANA    20

/* Global variables */
          int        Charge, Light;


void
create_weapon()
{
    set_name("staff");
    set_adj("ash");
    add_name("quarterstaff");
    set_pname( ({ "staves", "quarterstaves" }) );
    set_short("ash quarterstaff");
    set_pshort("ash quarterstaves");
    set_long("This is a long ash quarterstaff with a small amethyst " +
	     "in the top. It looks dangerous.\n");

    set_may_not_recover();

    set_hit(HIT);
    set_pen(PEN);

    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON);

    set_hands(W_BOTH);

    add_prop(MAGIC_AM_MAGIC, ({ 15, "enchantment" }));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) + random(250) + 1000 );
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_POLEARM) +
	     random(50) - 25 );
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
    add_prop(OBJ_M_NO_BUY, "A voice tells you: Don't sell my staff. Return " +
             "it to me instead.\n");
    add_prop(OBJ_M_NO_SELL, "A voice tells you: Don't sell my staff. " +
             "Return it to me instead.\n");
    add_prop(OBJ_S_WIZINFO, "This is a magical quarterstaff to be found on the " +
	     "mage in Dol Amroth. The quarterstaff give the wielder darkvision, can be " +
		 "used as a <light> source, and can entangle victims with <cast root>. " +
		 "It holds a limited amount of charges.\n");
    add_prop(MAGIC_AM_ID_INFO, ({ "This quarterstaff have some special abilities. " +
				      "It can help you in the dark.\n", 25,
				  "This quarterstaff have some special abilities. " +
				      "It allows you to see better in darkness and " +
					  "give light.\n", 50,
				  "This quarterstaff have some special abilities. " +
				      "It allows you to see better in darkness and " +
					  "give light. It holds a limited amount of " +
					  "charges, and cannot be recharged.\n", 
				      70 }) );
    set_wf(this_object());

    Charge = 1 + random(9);
}

int
light_fun(string str)
{
    notify_fail("Light what?\n");

    if (!strlen(str))
	return 0;

    if (Light == 1)
    {
        notify_fail("Your quarterstaff is already shining.\n");
        return 0;
    }

    if (!objectp(query_wielded()))
    {
	notify_fail("You cannot light your staff without wielding it.\n");
	return 0;
    }

    if (Light == 0 && (str == "staff" || str == "quarterstaff"))
    {
	write("Your quarterstaff lights up with a sudden flash.\n");
	say(QCTPNAME(this_player()) + " quarterstaff lights up with " +
	    "a sudden flash.\n");
	add_prop(OBJ_I_LIGHT, 1);
	Light = 1;
	return 1;
    }

    return 0;
}

int
exting(string str)
{
    notify_fail("Dim what?\n");

    if (!strlen(str))
        return 0;

    if (Light == 0)
    {
        notify_fail("Your quarterstaff isn't shining.\n");
        return 0;
    }

    if (!objectp(query_wielded()))
    {
        notify_fail("You cannot dim your staff without wielding it.\n");
        return 0;
    }

    if (Light == 1 && (str == "staff" || str == "quarterstaff"))
    {
        write("The light from your quarterstaff dims.\n");
        say("The light from "+QTPNAME(this_player())+" quarterstaff dims.\n");
        remove_prop(OBJ_I_LIGHT);
        Light = 0;
        return 1;
    }

    return 0;

}

void
start_root(object room)
{
    object o;
    o = clone_object(DOL_OBJ + "root_obj.c");
    o->set_room(room);
    o->move(room);
    o->grow();
}

int
do_root(string arg)
{
    object tp = this_player();
    object room = environment(tp);
    int spell_c = tp->query_skill(SS_SPELLCRAFT);
    int earth_e = tp->query_skill(SS_ELEMENT_EARTH);
    int int_stat = tp->query_stat(SS_INT);
    int curr_mana = tp->query_mana();

    if (!strlen(arg))
	return 0;

    if (arg == "root")
    {
	if (!spell_c||!earth_e)
	{
	    notify_fail("You are not skilled enough to try that.\n");
	    return 0;
	}
	if (!query_wielded())
	{
	    notify_fail("You must wield the staff in order to do that.\n");
	    return 0;
	}
	if (curr_mana < ROOT_MANA)
	{
	    notify_fail("You have drained yourself for mana.\n");
	    return 0;
	}
	if (!Charge)
	{
	    write("You hammer your "+short()+" into the ground for no " +
		  "reason.\n");
	    say(QCTNAME(tp)+" hammers "+tp->query_possessive()+" into the " +
		"ground.\n");
	    return 1;
	}
	Charge--;
	tp->add_mana(-ROOT_MANA);

	if (!room->query_prop(ROOM_I_INSIDE) && 
	    ( ((int_stat - random(10)) > 50) && 
	      ((spell_c - random(10)) > 30 ) && 
	      ((earth_e - random(10)) > 30 ) ))
	{
	    set_alarm(2.0, 0.0, &start_root(room));
	}

	write("You hammer your "+short()+" into the ground.\n");
	say(QCTNAME(tp)+" hammers "+tp->query_possessive()+" "+short()+
	    " into the ground.\n");
	return 1;
    }
    notify_fail("Cast what?\n");
    return 0;
}

void
init()
{
    ::init();
    add_action(light_fun, "light");
    add_action(exting, "dim");
    add_action(do_root, "cast");
}

mixed
wield(object ob)
{
    this_player()->add_prop(LIVE_I_SEE_DARK, query_prop(LIVE_I_SEE_DARK) + 1);

    write("You wield your "+short()+" in both hands.\n");
    say(QCTNAME(this_player()) + " wields " + 
	this_player()->query_possessive() + " " + short() + ".\n");

    return 1;
}

mixed
unwield(object ob)
{
    object tp = this_object()->query_wielded();

    if (!living(tp))
	return 0;

    if (Light == 1)
    {
	write("The light from your quarterstaff dims.\n");
	say("The light from "+QTPNAME(this_player())+" dims.\n");
	Light = 0;
    }

    if (this_player()->query_prop(LIVE_I_SEE_DARK) > 1)
	this_player()->add_prop(LIVE_I_SEE_DARK,query_prop(LIVE_I_SEE_DARK)-1);
    else this_player()->remove_prop(LIVE_I_SEE_DARK);

    write("You stop wielding your "+short()+".\n");
    say(QCTNAME(this_player()) + " stop wielding " + 
	this_player()->query_possessive() + " " + short() + ".\n");

    return 1;
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    if (dt != W_BLUDGEON)
	return 0;

    if (phit > 25 && dam > 25)
	dam = dam + (dam / 25);

    return 0;
}

