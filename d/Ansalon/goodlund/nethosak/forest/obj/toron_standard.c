/*
 * What         : A deep green battle standard
 * Used by      : Handed out my minotaur Halamin in the Hestos minotaur camp
 *              : in southern Mithas.
 *                /d/Ansalon/goodlund/nethosak/forest/obj
 * Description  : One of two quest items the player has to find when solving 
 *              : the Toron_missing_standard quest.
 * Made by      : Cherek, Feb 2007
 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>

#include <stdproperties.h>"
#include <wa_types.h>
#include <formulas.h>

inherit "/std/weapon";

int HIT = 10;
int PEN = 40;

void
create_weapon()
{
        set_name("standard");
        add_name("_deep_green_battle_standard");
        set_pname("standards");
        set_adj( ({"deep", "green", "battle" }) );
        set_short("deep green battle standard");
        set_pshort("deep green battle standards");
        set_long("The standard is made of a deep green cloth with " +
                 "three embroidered golden axes. It is almost five " +
                 "feet tall and on the top of the wooden handle a " +
                 "steel tip has been fastened making it possible to " +
                 "use the standard as a weapon should the need " +
                 "arise. \n" );

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_POLEARM)
             +random(1000));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3 + random(200));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));

    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);

    seteuid(getuid(TO));
}
