
/* Invisibility Object

   Conjured by the Photostepsanos spell of the Stonewalkers.

   Coded by Jaacar 

*/

#pragma strict_types

inherit "/d/Genesis/magic/spells/invisibility_obj";

#include <stdproperties.h>
#include <macros.h>

varargs public int dispel_spell_effect(object dispeller);

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->add_prop(LIVE_I_SEE_INVIS,
        (int)spell_target->query_prop(LIVE_I_SEE_INVIS) - 1);
    ::dispel_spell_effect(dispeller);
}