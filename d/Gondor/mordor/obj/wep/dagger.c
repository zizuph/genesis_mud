/*
 * /d/Gondor/mordor/obj/wep/dagger.c
 *
 * A nice dagger that is poisonous. It can be found somewhere in Cirith Ungol.
 *
 * /Mercade, 26 September 1993
 *
 * Revision history:
 */

inherit "/std/weapon";

#include "/d/Gondor/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <poison_types.h>

int poison_is_used = 0; /* set if the poison was used */

void
create_weapon()
{
    set_name("dagger");
    add_name("_poisonous_dagger_at_cirith_ungol_");
    add_adj("short");
    add_adj("steel");
    add_adj("orkish");

    set_short("steel orkish dagger");
    set_long("@@long_description");

    set_hit(10);
    set_pen(10);

    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_S_WIZINFO,
        BSN("This dagger will be poisonous. It will poison the enemy " +
        "with a poison that will both inflict his hitpoints and his " +
        "constitution."));
}

/*
 * The long description of the dagger
 */
string
long_description()
{
    if (!poison_is_used)
    {
        return BSN("Looking at the dagger, you see a nick in the blade. " +
            "In the nick you see some liquid, probably a poison.");
    }

    return BSN("Looking at the dagger, you see a nick in the blade. In the " +
        "nick you see some liquid, maybe water, but probably blood."); 
}

/*
 * Poison your enemy with the blade.
 */
varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
    object poison;

    if((!poison_is_used) && (random(100) < 10))
    {
        poison = clone_object("/std/poison_effect");

        if(poison)
        {
            if(random(100) < 30)
            {
                poison_is_used = 1;
            }
            poison->move(enemy, 1);
            poison->set_time(1000);
            poison->set_interval(60);
            poison->set_strength(60);
            poison->set_damage( ({ POISON_HP, 80, POISON_STAT, SS_CON }) );
            poison->start_poison();
        }
        else 
            write(BSN("Even though you hit your opponent right, you didn't " +
                "manage to poison " + OBJECTIVE(enemy) + ".")); 
    }

    return 0;
}

/*
 * Tell the wizard who stats this dagger whether it is still has poison on it.
 */
stat_object()
{
    return (::stat_object +
        (poison_is_used ?
            "The poison is completely used.\n" :
            "The poison is not completely used yet.\n"));
}

/*
 * Recovery stuff
 */
string
query_recover()
{
    return MASTER + ":#poison#" + poison_is_used + "#" +
        query_wep_recover();
}

void
init_recover(string arg)
{
    string foobar;

    sscanf(arg, "%s#poison#%d#%s", foobar, poison_is_used, foobar);

    init_wep_recover(arg);
}
