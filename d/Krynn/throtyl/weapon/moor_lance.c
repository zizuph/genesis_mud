
inherit "/std/weapon";
inherit "/lib/keep";

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

#define HIT 40
#define PEN 30
 
#define MOUNTED_HIT 40
#define MOUNTED_PEN 50

int mounted = 0;

void
create_weapon()
{
    set_name("lance");
    add_adj("black");
    add_adj("tipped");
    add_adj("black-tipped");
    add_adj("deadly");
    set_short("deadly black-tipped lance");
    set_long("This lance is essentially a long spear with a nasty looking " +
        "black-tipped head that is covered with bright runes. This weapon seems " +
        "particularly deadly when mounted, being light and quick to " +
        "maneuver into position.\n");

    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_POLEARM);
    set_hands(W_BOTH);
    set_dt(W_IMPALE);

    set_wf(TO);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This weapon is magically enchanted.\n", 5,
	"This horseman's lance has had enchantments placed upon it " +
        "to make it deadlier when the wielder is mounted.\n",55}));
    add_prop(MAGIC_AM_MAGIC,({80,"enchantment"}));
    add_prop(OBJ_I_VOLUME, 3500);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35,45) + 500 + random(500)); 
    add_prop(OBJ_S_WIZINFO, "This lance that has a chance to be " +
        "wielded by the mounted Riders in the Moor, " +
        "/d/Krynn/throtyl/living/moors_rider.c\nWhen wielded by " +
        "someone mounted the weapon's penetration increases.\n");
}

void
state_change(int hit, int pen)
{
    set_hit(hit);
    set_pen(pen);
 
    if (wielded && wielder)
        wielder->update_weapon(this_object());
}

mixed
wield(object what)
{
    if(wielder->is_rider_shadow())
    {
        wielder->catch_tell("The runes of your " + short() + " glow " +
            "with a dark emerald light!\n");
        tell_room(E(wielder), "The runes on the " + short() + " wielded by " +
            QTNAME(wielder) + " starts glowing with a dark emerald light.\n",
            wielder);
        state_change(MOUNTED_HIT, MOUNTED_PEN);
        mounted = 1;
    }
    else
    {
        state_change(HIT, PEN);
        mounted = 0;
    }

    return 0;
}

mixed
unwield(object what)
{
    state_change(HIT, PEN);
    mounted = 0;

    return 0;
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
                int phit, int dam)
{
    int r = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
 
    if (!mounted && wielder->is_rider_shadow())
    {
        wielder->catch_tell("The runes of your " + short() + " glow " +
            "with a dark emerald light!\n");
        tell_room(E(wielder), "The runes on the " + short() + " wielded by " +
            QTNAME(wielder) + " starts glowing with a dark emerald light.\n",
            wielder);
        state_change(MOUNTED_HIT, MOUNTED_PEN);
        mounted = 1;
 
    }
    else if(mounted && !(wielder->is_rider_shadow()))
    {
        state_change(HIT, PEN);
        mounted = 0;
    }

    return r;
}

