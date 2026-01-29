/*
 * What         : A light iron chainmail
 * Used by      : Minotaurs in the Hestos minotaur camp in southern Mithas.
 *                /d/Ansalon/goodlund/nethosak/forest/obj/armour
 * Description  : A pretty poor armour for minotaurs.
 * Made by      : Cherek, Feb 2007
 */

#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/armour";

int AC =  25;

void
create_armour()
{
    set_name("chainmail");
    set_ac(AC);
    set_at(A_BODY);
    set_adj("light");
    add_adj("iron");
    set_short("light iron chainmail");
    set_long("Considering the size of the chainmail it is surprisingly " +
             "light. The iron links seem weak and you do not think it " +
             "would protect you very well. Two crossed yellow swords " +
             "have been painted on the front, the emblem of the " +
             "Hestos minotaur tribe from Mithas. \n");

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_BODY)
             +3000+random(2000)+random(2000));
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
