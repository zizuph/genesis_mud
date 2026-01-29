/* longsword  */
/*  Tigerlily--Nov. 24, 2004--fixed bug in unwield/wield */
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>  
#include <macros.h>
#include <formulas.h>
#include "/d/Gondor/defs.h"

#define HIS TP->query_possessive()

void
create_weapon()
{
    set_name(({"longsword","sword","weapon"}));
    set_pname("swords");
    add_pname("longswords");
    set_short("camouflaged longsword");
    set_pshort("camouflaged longswords");
    set_long("This large sword resembles the weaponry of soldiers of "
        + "Gondor. It has been painted in such a way to make it less obvious "
        + "in a forest setting, hiding even its cutting edges.\n");
    set_adj(({"camouflaged", "steel", "large", "gondorian", }));

    set_pen(40);
    set_hit(40);

    set_keep(1);
    set_wt(W_SWORD);
    set_dt(W_SLASH|W_IMPALE);
    set_hands(W_RIGHT);
    set_likely_corr(0);
    set_likely_dull(0);
    set_likely_break(0);

    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(40, 40)+random(400)-200);
    add_prop(OBJ_I_WEIGHT,
     (F_WEIGHT_DEFAULT_WEAPON(40, W_SWORD) + random(500) + 500));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

    add_prop(GONDOR_M_RANGERS_NO_SELL,1);
    add_prop(GONDOR_M_TIRITH_NO_SELL,1);

    set_wf(TO);
}
