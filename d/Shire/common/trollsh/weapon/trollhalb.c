/*
 * halberd wielded by trolls in trollshaws
 * -- Finwe, November 2001
 */

inherit "/std/weapon";

#include <wa_types.h>
#include <language.h>
#include <stdproperties.h>
#include <formulas.h>

#define WEP_TYPE    W_POLEARM
#define HIT         35
#define PEN         35
#define HANDS       W_BOTH
#define DAMAGE      W_SLASH | W_IMPALE | W_BLUDGEON

void
create_weapon()
{
    set_name("halberd");
    add_name("polearm");
    set_adj(({"heavily","damaged"}));
    set_short("heavily damaged halberd");
    set_long("This "+short()+" is a very unwieldly weapon, " +
        "requiring both hands to use properly. The shaft is broken " +
        "in half, yet still works very well as a dangerous weapon. " +
        "The blade at the top of the halberd is curved and crowned " +
        "with a sharp spear point making the weapon dangerous.\n");

    set_default_weapon(HIT,PEN,WEP_TYPE,DAMAGE, HANDS, 0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(40, W_POLEARM) + random(350));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30, 30) * (110 + random(21)) / 100);

}
