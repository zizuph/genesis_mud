/*
 * Ashlar, 6 Sep 97
 *
 * A gem that allows a priest to capture the soul of a dying enemy
 * and store it to use in spells as a mana-reducing component.
 *
 * Updated 13 May 98 - The new holdable item thingy fits this like
 *                     the proverbial glove, so lets make it a such.
 *
 * Obsolete with the transition to the new_pot code.
 * Code added to remove these objects on cloning.
 * New soul_gem in ~guild/new_pot/obj/soul_gem.c
 *
 * Arman 2017
 */

inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include "../guild.h"

#define ONE_CHARGE 60

string *adj = ({ "glimmering", "glittering", "shining", "glowing" });
string colour;
int charge, maxcharge;

void
set_up_gem()
{
    int i;
    remove_adj(adj);
    if (charge == 0)
    {
        add_adj("dull");

        set_short("dull " + (stringp(colour) ? colour + " " : "") +
        "soul gem");
        return;
    }
    if (maxcharge < 0)
        maxcharge = 0;
    i = (sizeof(adj) * charge) / (maxcharge + 1);
    if (i > 3)
        i = 3;
    add_adj(adj[i]);
    set_short(adj[i] + " " + (stringp(colour) ? colour + " " : "") +
    "soul gem");
}

string
query_colour()
{
    return colour;
}

void
set_colour(string c)
{
    if (stringp(colour))
        remove_adj(colour);
    colour = c;
    add_adj(colour);
    set_up_gem();
}

void
create_object()
{
    set_name("gem");
    add_name("soulgem");
    add_name("_ansalon_soul_gem");
    set_adj("soul");

    set_long("It is a small gem, finely cut. The inside is strangely " +
    "opaque. You recognize this as a soul gem, used to trap the souls " +
    "of unsuspecting victims.\n");

    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "This is a soul gem, used in some dark arts to capture the " +
        "souls of enemies.\n", 10,
        "In order to use this properly, the gem must be held in either " +
        "hand when killing the target.\n", 20 }));

    add_prop(OBJ_S_WIZINFO,
        "This object is used by the Priests of Takhisis to capture " +
        "souls of enemies and use them in their magic.\n");

    charge = 0;
    maxcharge = ONE_CHARGE * 5 + random(ONE_CHARGE);

    set_slots(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VOLUME, 60);
    add_prop(OBJ_I_VALUE, 1500);

    set_colour("silver");
    set_up_gem();

    set_keep(1);
}


void
remove_soul_gem(object env)
{
    env->catch_tell("You feel the power of the Dark Queen draw the souls " +
          "from your " +TO->short()+ "! It crumbles to dust in your hands. " +
          "Like storm clouds on the horizon, you feel the approach of " +
          "something darkly portentous.\n");
    TO->remove_object();
}

void
enter_env(object env, object from)
{

    set_alarm(3.0,0.0, &remove_soul_gem(env));
        
    ::enter_env(env, from);
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    /* This needs to be called from leave_env() so that items are
     * released when they are dropped.
     */
    holdable_item_leave_env(env, to);
}

int
query_charge()
{
    return charge;
}

int
query_max_charge()
{
    return maxcharge;
}

void
add_charge(int c)
{
    charge += c;
    if (charge > maxcharge)
        charge = maxcharge;
    if (charge < 0)
        charge = 0;

    if ((c < 0) && (charge < ONE_CHARGE))
    {
        maxcharge -= 5;

        /*
        if (maxcharge < ONE_CHARGE)
            remove_broken();
        */
    }
        
    set_up_gem();
}

int
trap_soul(object victim)
{
    if (victim->query_prop(LIVE_I_UNDEAD))
        return 0;
        
    add_charge(victim->query_average_stat());
    return 1;
}

string
query_recover()
{
    return MASTER + ":" + colour + "&&" +
    charge + "," + maxcharge;
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");

    colour = a[0];
    add_adj(colour);
    sscanf(a[1],"%d,%d",charge,maxcharge);
    set_up_gem();
}

/*
 * Function name: appraise_object
 * Description:   This is called when someone appraises this item.
 *                We want to mask it to add a message telling the
 *                appraiser that the item can be held.
 */
public void
appraise_object(int num)
{
    ::appraise_object(num);
    write(holdable_item_usage_desc());
}
