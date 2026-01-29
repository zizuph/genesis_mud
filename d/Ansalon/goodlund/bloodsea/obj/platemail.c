/*
 * What         : A rusty iron chainmail.
 * Used by      : Minotaur captain Corth, sailing the Bloodsea
 *                /d/Ansalon/goodlund/bloodsea/obj
 * Description  : A decent body armour for minotaurs. 
 * Made by      : Cherek, Feb 2007
 */ 

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include <macros.h>

inherit "/std/armour";

int AC =  28 + random(4) + random(4);

void
create_armour()
{
    set_name("platemail");
    set_ac(AC);
    set_at(A_BODY);
    set_adj("rusty");
    add_adj("iron");
    set_short("rusty iron platemail");
    set_long("This is a simple body armour made of two large steel " +
             "plates covering the chest and the back of the wearer. " +
             "On the front plate a red shield has been painted, " +
             "the emblem of the Orilg tribe minotaurs from Kothas. " +
             "You spot a few rust marks on it. \n");

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_BODY)
             +4000+random(2000)+random(2000));
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
