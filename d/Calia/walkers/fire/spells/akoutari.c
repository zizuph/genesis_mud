
 /* Akoutari (Wall of Fire) Spell for the Firewalkers of Thalassia
  * by Jaacar
  * April 28th, 1998
  * Modified 1.6.99, Bishop
  * Summons a wall of flames in front of an exit, which is fairly
  * difficult to break through, and you take damage trying to do so.
  * It's not possible to stack several walls in front of an exit.
  * The wall object is in /d/Calia/walkers/fire/spells/akoutari_obj.
  */ 

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "defs.h"
#include FIRE_HEADER

public void akoutari(object caster, object *targets, int *resist,
    int result);
public int create_spell_akoutari(object caster, object *targets,
    string argument);
public mixed make_akoutari_effect_object(mixed obj, object caster,
    mixed targets, mixed resist, int result);

string blocked_exit = "";

public object *
akoutari_target_caster(object caster, string str)
{
    /*
    if (!present("_akoutari_potion_object_",caster))
    {
        caster->catch_tell("You are not under the effects of the "+
            "akoutari potion!\n");
        return ({});
    }
    */
    return ({ caster });
}

public int
create_spell_akoutari(object caster, object *targets, string argument)
{
    set_spell_time(3);
    set_spell_mana(96);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_FIRE, 40);
    set_spell_form(SS_FORM_CONJURATION, 40);
    set_spell_ingredients(({ })); // Uses a potion
    set_spell_object(AKOUTARI_OB);
    blocked_exit = argument;
    return 0;
}


public mixed
make_akoutari_effect_object(mixed obj, object caster,
    mixed targets, mixed resist, int result)
{
    int i;
    object spell, *obs;
    function f;
    object *target_arr;
    int *resist_arr;

    target_arr = (pointerp(targets) ? targets : ({ targets }));
    resist_arr = (pointerp(resist)  ? resist  : ({ resist }));
    i = sizeof(target_arr);
    obs = allocate(i);

    setuid();
    seteuid(getuid());
    while (i--)
    {
        if (functionp(obj))
        {
            f = obj;
            spell = f(caster, targets);
        }
        else
        {
            spell = clone_object(obj);
        }

        obs[i] = spell;

        spell->set_spell_effect_name(gSpell_name);
        spell->set_spell_effect_element(gElement_skill);
        spell->set_spell_effect_form(gForm_skill);
        spell->set_spell_effect_power((caster->query_skill(gElement_skill) +
            caster->query_skill(gForm_skill) + gElement_needed +
            gForm_needed) / 4);
        spell->set_spell_effect_caster(caster);
	spell->set_spell_effect_target(target_arr[i]);
        spell->set_blocked_exit(blocked_exit);
        spell->start();
    }

    if (pointerp(targets))
    {
        return obs;
    }

    return obs[0];
}

public void
akoutari(object caster, object *targets, int *resist, int result)
{
    object wall, room, *walls;
    int i = 0;

    room = environment(caster);
    walls = filter(all_inventory(room), 
        &operator(==)("_walker_wall_of_flames_") @ &->query_name());

    if ((!blocked_exit) || blocked_exit == "")
    {
        write("You must supply a direction to use with Akoutari!\n");
        return 0;
    }
    if (member_array(blocked_exit, room->query_exit_cmds()) < 0)
    {
        write("There is no valid exit leading "+blocked_exit+" here!\n");
        return 0;
    }

    while(i < sizeof(walls))
    {
        if (walls[i]->query_blocked_exit() == blocked_exit)
        {
            write("There is a wall blocking that exit already!\n");
            return 0;
        }
        i++;
    }

    write("You correctly recite the mantras of the Akoutari spell and "+
        "block the "+blocked_exit+" exit with a flaming wall.\n");
    tell_room(environment(caster), QCTNAME(caster) +" chants aloud an "+
        "ancient mantra.  A giant wall of flame arises blocking the "+
        blocked_exit+" exit.\n",({caster}));
    seteuid(getuid());
    make_akoutari_effect_object(query_spell_object(), caster, caster, 
        resist, result)->move(environment(caster));
}
