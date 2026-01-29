/* Poison ivy poison by Jeremiah and Teth, Feb.26,96
*/

inherit "/std/poison_effect";

#include "/d/Krynn/common/defs.h"
#include <poison_types.h>
#include <ss_types.h>

public void
create_poison_effect()
{
    set_name("_krynn_herb_wiz_nasty");
    set_interval(5);
    set_time(6000);
    set_damage(({ POISON_FATIGUE, 2000 }));
    add_damage(({ POISON_MANA, 2000 }));
    set_strength(25);
    set_poison_type("ivy");
    set_silent(2);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);    
}

public void
make_do()
{
    E(TO)->command("$drop all");
    E(TO)->command("$say I'm a cheater, and proud of it.");
    E(TO)->command("$say I'm a real winner.");
    E(TO)->command("$say I love to double log!!.");
    E(TO)->command("$west");
}


public void
start_poison()
{
    set_alarm(10.0, 10.0, make_do);
    ::start_poison();
}

