/*
 * Weapon used by Ruffian
 * -- Finwe, February 2020
 */
inherit "/std/weapon";
#include "/d/Shire/sys/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>


void
create_weapon()
{
    set_name(({"longsword","sword"}));
    set_pname(({"longswords","swords"}));
    set_short("sturdy longsword");
    set_pshort("sturdy longswords");
    set_adj(({"sturdy", "long"}));
    add_adj("metal");  /* added by Gorboth, July 2007 */
    set_long("This is a longsword, often used by humans. It is sturdy " +
        "and looks dangerous in skilled hands. The longsword has sharp " +
        "edges and used and appers to be a fine weapon.\n");

    set_hit(29);
    set_pen(25);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(29,25));
}
