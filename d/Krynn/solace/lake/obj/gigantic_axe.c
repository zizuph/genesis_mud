/*
 * What         : A gigantic two-handed battleaxe
 * Used by      : Minotaur chieftain Kadez in the Toron minotaur village
 *                near Crystalmir Lake.
 *                /d/Krynn/solace/lake/npc
 * Description  : A quite good two-handed axe for minotaurs.
 * Made by      : Cherek, Feb 2007
 */

#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include "/d/Krynn/common/defs.h"

inherit "/std/weapon";

int HIT = 40;
int PEN = 40;

void
create_weapon()
{
    set_name("battleaxe");
    add_pname("battleaxes");
    add_name("axe");
    set_adj("gigantic");
    set_adj("two-handed");
    set_short("gigantic two-handed battleaxe");
    set_long("This must be the largest axe you have ever seen. The handle " +
             "is made from a thick piece of wood with a deep green cloth " +
             "wrapped around it. Only the blade itself measures over three " +
             "feet in length. It looks quite deadly in the right hands. \n");

    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_BOTH);
    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_AXE)
             +2000+random(1000)+random(1000));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3 + random(200));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
    
    set_wf(TO);

    seteuid(getuid(TO));
}

/*
 * Function name: wield
 * Description  : Checks if the wielder is a minotaur, other races are
 *                unable to wield a weapon made for minotaur hands.
 */

mixed
wield(object what)
{
    if(wielder->query_race_name() != "minotaur")
    {
        return "You have no idea how to wield this huge weapon.\n";
        
    }
    
    return 0;
}
