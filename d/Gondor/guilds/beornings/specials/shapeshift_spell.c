#pragma strict_types

#include "../defs.h"

inherit "/d/Genesis/specials/std/spells/shapeshift";

public void
config_shapeshift_spell()
{
    ::config_shapeshift_spell();

    set_shape_mapping(([
            "bear": "/d/Genesis/race/shapeshift/beorning_bear"
        ]));    
}