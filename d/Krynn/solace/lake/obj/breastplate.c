/*
 * What         : A fur-covered leather breastplate
 * Used by      : Minotaurs in the Toron village near Crystalmir Lake.
 *                /d/Krynn/solace/lake/npc
 * Description  : Very simple and doesnt give much protection.
 * Made by      : Cherek, Feb 2007
 */ 

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

inherit "/std/armour";

int AC = 20;

void
create_armour()
{
    set_name("breastplate");
    set_ac(AC);
    set_at(A_BODY);
    set_adj("fur-covered");
    add_adj("leather");
    set_short("fur-covered leather breastplate");
    set_long("A hard leather armour that has been covered with a thick " +
             "animal fur. It serves as protection from the cold as well " +
             "as protection in battle. \n");

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_BODY)
             +2000+random(2000)+random(2000));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4 + random(500));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(AC));

    set_wf(TO);

    seteuid(getuid(TO));    
}
 
/*
 * Function name: wear
 * Description  : Checks if the wearer is a minotaur, other races are
 *                unable to wear an armour made for a minotaur body.
 */

mixed
wear(object what)
{
    if(wearer->query_race_name() != "minotaur")
    {
        return "This armour would not fit properly on you.\n";
    }
    
    return 0;
}
