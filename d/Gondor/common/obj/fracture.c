/* This code copied from the original coder, with permission.
 * Thanks to Sorgum of Terel.
 */

/*
 * fracture.c
 *
 * A broken arm.
 * This object simulates a broken arm by occupying a toolslot until it is
 * removed.
 */

inherit "/std/armour";

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define FRAC_SUBLOC "_frac_subloc"

static int msg_seen = 0;
void heal();
void fixed();
void add_fracture(object victim);

public string
query_recover() { return 0; }

query_auto_load()
{
    return MASTER + ":";
}

int wear()
{
    if (msg_seen == 0) {
	TP->catch_msg("Your arm is broken.\n");
	msg_seen = 1;
    }
    TP->add_subloc(FRAC_SUBLOC, TO);
    return 1;
}

show_subloc(string subloc, object carrier, object for_obj)
{
    string str;
    string *indexes;
    int i;

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if (subloc != FRAC_SUBLOC)
	return carrier->show_subloc(subloc, carrier, for_obj);

    if (for_obj == carrier)
	str = "You have a broken arm.\n";
    else
	str = capitalize(carrier->query_pronoun()) + " has a broken arm.\n";
    
    return str;
}

int remove()
{
    set_alarm(1.0, 0.0, &add_fracture(TP));
    return 1;
}

remove_broken()
{
    return;
}

varargs int
query_ac(int hid)
{
    return 0;
}

create_armour()
{
    set_name("fracture");
    set_short("fracture");

    set_no_show();
    
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    set_default_armour(1, A_SHIELD, 0, TO);
    set_likely_cond(0);
    set_likely_break(0);
    set_ac(0);
    msg_seen = 0;
    
}

enter_env(object dest, object old)
{
    if (living(dest))
    set_alarm(2.0, 0.0, &add_fracture(dest));

    ::enter_env(dest, old);
}

void
add_fracture(object victim)
{
    object armour;
    object weapon;

    if ((weapon = victim->query_weapon(W_LEFT))) {
	weapon->add_prop(OBJ_I_BROKEN, 1);
	weapon->move(environment(victim));
    }
    
    if ((armour = victim->query_armour(W_LEFT))) {
	if (MASTER_OB(armour) != MASTER_OB(TO)) {
	    armour->add_prop(OBJ_I_BROKEN, 1);
	    armour->move(environment(victim));
	}
    }
   
    if (query_worn() == 0)
	wear_me();
    set_alarm(itof(400 + random(400)), 0.0, heal);
    
}

void
heal()
{
    set_alarm(600.0, 0.0, fixed);
}

void
fixed()
{
    ENV(TO)->catch_msg("Your arm is healed.\n");
    remove_object();
}
