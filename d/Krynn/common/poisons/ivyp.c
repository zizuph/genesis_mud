/* Poison ivy poison by Jeremiah and Teth, Feb.26,96
*/

inherit "/std/poison_effect";

#include "/d/Krynn/common/defs.h"
#include <poison_types.h>
#include <ss_types.h>

public void
create_poison_effect()
{
    set_name("_krynn_herb_ivy_poison");
    set_interval(5);
    set_time(2400);
    set_damage(({ POISON_FATIGUE, 5 }));
    set_strength(25);
    set_poison_type("ivy");
    set_silent(2);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);    
}

public void
make_scratch()
{
    string *scratch_loc = ({ "head", "behind", "back", "nose" });

    if (random(3))
    {
        E(TO)->command("$scratch " + scratch_loc[random(4)]);
    }
}


public void
start_poison()
{
    set_alarm(60.0, 30.0, make_scratch);
    ::start_poison();
}

