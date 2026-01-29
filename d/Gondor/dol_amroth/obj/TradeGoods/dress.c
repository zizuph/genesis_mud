/* -*- Mode: C -*-
 *
 * dress.c
 *
 * A dress to be sold in Dol Amroth
 *
 * By Skippern 20(c)01
 */
inherit "/std/object";
inherit "/lib/wearable_item";

#include <const.h>
#include <stdproperties.h>
#include <wa_types.h>

/* Globale variables */
string color;

void set_color(string a) { color = a; }

string short() { return color + " dress"; }
string pshort() { return color + " dresses"; }
string long() { return "It is a "+color+" dress made of the most " +
		  "beautiful fabrics.\n"; }

void
create_object()
{
    set_name("dress");
    add_adj(color);
    set_short(&short());
    set_pshort(&pshort());
    set_long(&long());

    set_wf(this_object());

    set_slots(A_BODY|A_WAIST|A_LEGS|A_ARMS|A_SHOULDERS);
    set_layers(1);
    set_looseness(0);

    add_prop(OBJ_I_WEIGHT, 550);
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_VALUE,  350);
}

/*
 * Function name:    wear
 * Description  :    This function is called when somebody tries to wear
 *                   this dress.
 * Arguments    :    object ob - this object
 * Return       :    0 - Failure
 *                   1 - Success
 */
public mixed
wear(object ob)
{
    int g = this_player()->query_gender();
    string shmsg = short();

    if (g == G_FEMALE)
    {
        write("You wear the " + shmsg + ". It looks beautiful on you.\n");
	say(" wears the " + shmsg + ". It looks beautiful on her.\n");
	return 1;
    }
    return "Only females of the oposite sex may wear this dress.\n";
}

/*
 * We need to override leave_env() so that we can be sure to remove
 * the anklet if it gets moved from the wearer while it is still worn.
 */
public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    wearable_item_leave_env(env, to);
}

/*
 * We need to override appraise_object() so that we can be sure that the
 * player can appraise it properly.
 */
void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

