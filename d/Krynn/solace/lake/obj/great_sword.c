/*
 * What         : A great two-handed sword
 * Used by      : Minotaurs in the Toron village near Crystalmir Lake.
 *                /d/Krynn/solace/lake/npc
 * Description  : A decent sword for minotaurs.
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
    set_name("sword");
    add_pname("swords");
    set_adj("great");
    set_adj("two-handed");
    set_short("great two-handed sword");
    set_long("This is one of the largest swords you have ever seen. " +
             "It has a crude design, a wooden handle wrapped in simple " +
             "cloth attached to a jagged steel blade. \n");

    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_BOTH);
    set_wf(TO);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_SWORD)
             +2000+random(1000)+random(1000));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3 + random(200));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));

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
