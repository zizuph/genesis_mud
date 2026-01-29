inherit "/d/Khalakhor/std/weapon";

#include "local.h"
#include <wa_types.h>
#include <language.h>
#include <stdproperties.h>
#include <formulas.h>

void
create_khalakhor_weapon()
{
    set_name("swordbreaker");
    set_adj(({"long", "jagged"}));
    add_name(({"dagger", "knife", "sword breaker"}));
    set_short("long jagged swordbreaker");
    set_long("This "+short()+" is a long knife with many jagged "+
      "blades which can be used to snare bladed weapons.  "+
      "This sword breaker is a powerful defensive weapon in the hands "+
      "of a skilled knife user, capable of breaking any blade with a "+
      "quick parry.\n");

    set_wf(this_object());
    set_wt(W_KNIFE);
    set_hit(19);
    set_pen(14);
    set_hands(W_LEFT);
    set_dt(W_IMPALE);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(query_pen(), W_KNIFE) * 2);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 10);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(query_hit(), query_pen()) + 50);
}

public mixed
wield(object wep)
{
    setuid(); seteuid(getuid());
    clone_object(SWBREAKER_SHADOW)->add_sword_breaker_shadow(environment(), wep);
    return 0;
}

public mixed
unwield(object wep)
{
    query_wielded()->remove_sword_breaker_shadow();
    return 0;
}
