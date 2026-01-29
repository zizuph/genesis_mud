inherit "/std/weapon";
inherit "/lib/keep";

#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#include <stdproperties.h>
#include <wa_types.h>

#define HIT 37
#define PEN 40

#define HIT2 27
#define PEN2 35

/* This weapon is more effective against mounted opponents */
int enemy_mounted = 1; /* Initial state is fighting a mounted opponent */

void
create_weapon()
{
    set_name("pike");
    set_adj(({"long","steel-capped"}));
    set_short("long steel-capped pike");    
    set_long("The long pike is well-crafted and sturdy. The thick " +
    "wooden pole is capped with a steel tip. While a powerful " +
    "weapon in its own right, it is especially effective against " +
    "cavalry.\n");
    
    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_POLEARM);
    set_hands(W_BOTH);
    set_dt(W_IMPALE);
    
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 3000);
    
}

void
state_change(int hit, int pen)
{
    set_hit(hit);
    set_pen(pen);
    
    if (wielded && wielder)
        wielder->update_weapon(this_object());
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
                int phit, int dam)
{
    int r;
    
    r = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    
    if (objectp(enemy->query_prop(LIVE_O_STEED)))
    {
        /* Switch to high power */
        if (!enemy_mounted)
        {
            state_change(HIT, PEN);
            enemy_mounted = 1;
        }
        
    }
    else
    {
        /* Switch to low power */
        if (enemy_mounted)
        {
            state_change(HIT2, PEN2);
            enemy_mounted = 0;
        }
        
    }
    
    return r;
}
