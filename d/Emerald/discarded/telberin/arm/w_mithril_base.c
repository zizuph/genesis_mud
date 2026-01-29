/* w_mithril_base.c created by Shiva@Genesis
 * inherit file for curan's white-mithril armour
 */ 

inherit "/std/armour";
 
#include <stdproperties.h>
#include <wa_types.h>

#define DEBUG_ON
#undef DEBUG_ON
#define DEBUG_WHO find_player("shiva")
#include "/d/Emerald/sys/debug.h"

#define CURANS_ARMOURS(who) filter(who->query_armour(-1), \
                            &->query_curans_armour())
#define HOW_MANY_ARMOURS 3

#define IS_CURAN(ob) (ob->id("prince_curan"))

#define MIN_ACMOD -10
#define MAX_ACMOD (query_extra_power() ? 20 : 10)

static int extra_power;

int query_extra_power();

void create_mithril_armour() { }

nomask void
create_armour()
{
    set_likely_break(1);
    set_af(this_object());

    create_mithril_armour();
  
    set_adj("white");
    add_adj("mithril");
  
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 60, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({ })); 
    add_prop(OBJ_S_WIZINFO, "");
}

mixed
wear()
{
    object *armours = CURANS_ARMOURS(this_player()) | ({ this_object() });
  
    if (sizeof(armours) >= HOW_MANY_ARMOURS)
    {
        armours->power_up();
    }

    return 0;
}

mixed
remove()
{
    object *armours = CURANS_ARMOURS(this_player()) | ({ this_object() });
    armours->power_down();
    return 0;
}

int query_curans_armour() { return 1; }

void
improve_ac(int dt)
{
    int i;
    object who;
    int *acmod;

    if (dt == MAGIC_DT)
    {
        return;
    }

    who = query_worn();
    acmod = query_am(0);

    for (i = 0; i < 3; i++)
    {
        if ((1 << i) == dt)
	{
            if (acmod[i] > MAX_ACMOD)
	    {
                acmod[i]--;
	    }
            else if (acmod[i] < MAX_ACMOD)
	    {
                acmod[i] += 2;
	    }
	}
        else
	{
            if (acmod[i] > MIN_ACMOD)
	    {
                acmod[i] -= (IS_CURAN(who) ? random(2) : 1);
	    }
	}

        /* modified ac should never exceed 60 */
        acmod[i] = min(60 - query_ac(), acmod[i]);
    }

    set_am(acmod);
    who->update_armour(this_object());
}

varargs int
got_hit(int hid, int ph, object att, int dt, int dam)
{
    if (ph < 0)
    {
        return ::got_hit(hid, ph, att, dt, dam);
    }

    if (random(500) < (dam + 30))
    {
        improve_ac((dt & W_SLASH) || (dt & W_BLUDGEON) || (dt & W_IMPALE));
    }

    return ::got_hit(hid, ph, att, dt, dam);
}

void
power_up()
{
    if (extra_power)
    {
        return;
    }

    extra_power = 1;
    set_likely_break(0);
}

void
power_down()
{
    if (!extra_power)
    {
        return;
    }

    extra_power = 0;
    set_likely_break(1);
}

int
query_extra_power()
{
    return extra_power;
}

/* Unfortunately, there are armour breaking routines that don't check
 * likely_break == 0, so I have this.
 */
varargs void
remove_broken(int silent)
{
    if (query_likely_break())
    {
	::remove_broken(silent);
    }
}
