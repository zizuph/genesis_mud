/*
 * What         : A sturdy long-handled axe
 * Used by      : Minotaurs in the Hestos minotaur camp in southern Mithas.
 *                /d/Ansalon/goodlund/nethosak/forest/obj/weapon
 * Description  : A decent axe.
 * Made by      : Cherek, Feb 2007
 */

#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>"
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

inherit "/std/weapon";

int HIT = 25;
int PEN = 35;

void
create_weapon()
{
    set_name("axe");
    add_pname("axes");
    set_adj("sturdy");
    set_adj("long-handled");
    set_short("sturdy long-handled axe");
    set_long("A large axe that looks like it could be used both for " +
             "chopping wood and limbs.\n");

    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_BOTH);
    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_AXE)
             +2000+random(1000)+random(1000));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3 + random(200));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));

    seteuid(getuid(TO));
}
