/*
 * /std/spell.c
 *

The standard spell implements a single spell.  It has support
built in for parsing out the targets of the spell and will automatically
apply the effects of the spell (see /std/spell_effect.c) to each
recipient of the spell.  The spell will handle the requirements for
casting the spell, including:

    o spell material components
    o checking spell requirements for casting
    o implementing casting time
    o deducting mana from the caster
    o notifying NPC's that a spell is being cast so they can attack as required.

public functions
----------------
create_spell
cast_spell

properties used
---------------
SPELL_AI_FORM
({skill, skill level})  -- the skill to use in casting the spell and the
minimum value in the skill to cast it.

SPELL_AI_ELEMENT
({skill, skill level})  -- the magic element skill to use in casting the
spell, and the minimum level to cast at all.

*SPELL_AM_MATERIALS
({({name, class, environment_ok, pct_consumed, 
    write_msg, say_msg, extra_difficulty}), ...})

This should come last for components of that class.
One component called 'name' of each 'class' must be present 
for the spell to be cast.  A component is present if it is in the
player's deep_inventory or in the room's inventory (if 'environment_ok'
is set.)  A component will be consumed (and destroyed) if
random(100) < 'pct_consumed'.  'write_msg' and 'say_msg' are printed 
in this case.  If this component is used for the spell,
'extra_difficulty' will be added to the chance to cast the spell.

The materials are specified as strings, and any object matching the
description will be removed. (The first one encountered in the player)

A class of 0 implies that the item is unique and must be present.
A 0 in 'name' implies that no component is needed of that class to cast
the spell.

SPELL_I_CASTING_TIME
The casting time in seconds 

SPELL_I_DIFFICULTY
The difficulty of the task to cast the spell.  One of:
TS_SIMPLE, TS_ROUTINE, TS_DIFFICULT, TS_FORMIDABLE, TS_IMPOSSIBLE

SPELL_I_MANA
Amount of mana to remove for successfully casting the spell.  If the
spell is spoiled, half this amount will be used.

*SPELL_O_EFFECT
Object which will handle the effects of the spell.  By default set to
be this_object().  If a magical object is created, it should inherit
/lib/spell_effect.c.  Examples might be a flaming sword, created from
/std/weapon, inheriting /lib/spell_effect in addition.

*/

inherit "/std/object";

#include <ss_types.h>
#include <comb_mag.h>
#include "spells.h"

int extra_difficulty;  /* Difficulty added when requirements not met */

void
add_difficulty(int diff)
{
    extra_difficulty += diff;
}

public void
create_spell()
{

}

nomask void
create_object()
{
    change_prop(SPELL_O_EFFECT, this_object());
    create_spell();
}

int
valid_skills()
{
    mixed *skills;

    skills = query_prop(SPELL_AI_FORM);
    if (this_player()->query_skill(skills[0]) < skills[1])
        extra_difficulty += 300;

    skills = query_prop(SPELL_AI_ELEMENT);
    if (this_player()->query_skill(skills[0]) < skills[1])
        extra_difficulty += 300;

    return 1;
}

object 
test_material(mixed *material)
{
    if(material[2])
        return (present(material[0], ({environment(this_player())})
            + deep_inventory(this_player()) ) );
    else
        return (present(material[0], deep_inventory(this_player())) );
}

int 
valid_materials()
{
    mixed *materials;
    int i, j;
    object found;
    string *class_used;
    string *class_not_used;

    materials = query_prop(SPELL_AM_MATERIALS);

    for (i = 0; i < sizeof(materials); i++)
    {
        if (member_array(materials[i][1], class_used) >= 0)
            break;

        found = test_material(materials[i]);
        if (!found) 
            class_not_used += materials[i][1];
        else
        {
            class_used += materials[i][1];
            class_not_used -= materials[i][1];
            if (random(100) < materials[i][3])
            {
                write (materials[i][4]);
                say (materials[i][5]);
                if (!found->query_prop(HEAP_I_IS))
                    found->remove_object();
                else
                {
                    /* Handle heaps somehow. */
                }
                extra_difficulty += materials[i][6];
            }
            
        }
    }

    return !sizeof(class_not_used);
}

public int
cast_spell(string str)
{
    object caster;
    object room;

    caster = this_player();

    room = environment(caster);
    if(RNMAGIC(room))
        return 0;

    if(!valid_skills()) return 0;
    if(!valid_materials()) return 0;

    if (caster->query_mana() < query_prop(SPELL_I_MANA))
        return 0;

    caster->add_mana(-query_prop(SPELL_I_MANA)/2);

    call_out("do_spell", query_prop(SPELL_I_CASTING_TIME));
    caster->set_prop(LIVE_O_SPELL_ATTACK, this_object());
    /* Freeze caster until spell is complete. */
    /* Ensure no fighting until spell is complete. */
  
    return 1;
}

public void
do_spell()
{
    int res;
    object caster;
    caster = this_player();
    /* Consume materials */

    res = caster->resolve_task(
        query_prop(SPELL_I_DIFFICULTY) + extra_difficulty, 
        ({query_prop(SS_SPELLCRAFT), 
          query_prop(SPELL_AI_FORM)[0],
          query_prop(SPELL_AI_ELEMENT)[0]
        }));

    if (res < 0) return;

    caster->add_mana(-query_prop(SPELL_I_MANA)/2);

    /* Create the specified spell_effect(s) and move it to the appropriate
    object */

}

void
notify_change_prop(string prop, mixed val, mixed old)
{
    switch(prop)
    {
        case SPELL_AI_FORM:
/*
            if (sizeof(val) != 2||!intp(val[0])||!intp(val[1]))
                change_prop(SPELL_AI_FORM, old);
*/
        break;

        case SPELL_AI_ELEMENT:
        break;

        case SPELL_AM_MATERIALS:
        break;

        case SPELL_I_CASTING_TIME:
        break;

        case SPELL_I_DIFFICULTY:
        break;

        case SPELL_I_MANA:
        break;

        case SPELL_O_EFFECT:
        break;
    }
}
