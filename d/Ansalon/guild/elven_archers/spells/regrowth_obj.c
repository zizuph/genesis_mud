inherit "/d/Genesis/newmagic/spell_effect_object";

#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Ansalon/guild/elven_archers/guild.h"

#define REGROWTH_SPELL_PROP   "_ansalon_regrowth_spell_prop"

varargs public int dispel_spell_effect(object dispeller);

object location;

public int
start()
{
    location = environment(spell_target);
    
    set_spell_effect_desc("regrowth");
    location->set_searched(0);
    location->add_prop(REGROWTH_SPELL_PROP, 1);

    set_alarm(1200.0, 0.0, dispel_spell_effect);

    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{

    location->remove_prop(REGROWTH_SPELL_PROP);
    remove_spell_effect_object();

    return 1;
}
