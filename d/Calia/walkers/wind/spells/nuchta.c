
 /* 
  * Nuchta (Darkness) Spell for Windwalkers
  * by Jaacar
  * April 27th, 1998
  *
  */

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <tasks.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"
#include WIND_HEADER

public void nuchta(object caster, object *targets, int *resist,
    int result);
public int create_spell_nuchta(object caster, object *targets,
    string argument);

public int
create_spell_nuchta(object caster, object *targets, string argument)
{
    set_spell_time(2);
    set_spell_mana(40);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_AIR, 20);
    set_spell_form(SS_PRAYER, 20);
    set_spell_ingredients(({"black feather","drakeroot"}));
    set_spell_effect(nuchta);
    set_spell_object(NUCHTA_OB);
    return 0;
}

public void
nuchta(object caster, object *targets, int *resist, int result)
{
    object room;
    room = environment(caster);

    if (!room->query_prop(ROOM_I_INSIDE))
    {
        caster->catch_tell("You must be indoors to use the powers of "+
            "nuchta!\n");
        return;
    }

    caster->catch_tell("You correctly recite the mantras of nuchta and "+
        "the room goes dark.\n");
    tell_room(environment(caster),QCTNAME(caster)+" recites an ancient "+
        "mantra.  Everything goes dark.\n",({caster}));

    make_spell_effect_object(query_spell_object(), caster, caster, 
        resist, result)->move(environment(caster));
}
