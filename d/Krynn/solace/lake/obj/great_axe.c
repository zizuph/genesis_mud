/*
 * What         : A great two-handed battleaxe
 * Used by      : Minotaurs in the Toron village near Crystalmir Lake.
 *                /d/Krynn/solace/lake/npc
 * Description  : A decent axe for minotaurs.
 * Made by      : Cherek, Feb 2007
 */

#include <stdproperties.h>"
#include <wa_types.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"

inherit "/std/weapon";

int HIT = 25;
int PEN = 35;

void
create_weapon()
{
    set_name("axe");
    add_pname("axes");
    set_adj("great");
    set_adj("two-handed");
    set_short("great two-handed axe");
    set_long("This is one of the largest axes you have ever seen. " +
             "It has a crude design, consisting of only a long " +
             "wooden handle and a jagged steel blade. \n");

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
