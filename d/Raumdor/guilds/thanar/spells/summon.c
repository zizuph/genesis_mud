/**********************************************************************
 * - summon.c                                                       - *
 * - To summon a snake messenger                                    - *
 * - Created by Damaris@Genesis 4/2004                              - *
 **********************************************************************/

#pragma strict_types

#include "spells.h"
#include "../guild.h"
#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
inherit "/d/Genesis/newmagic/spell";
inherit SPELL_INHERIT;

public void
create_spell()
{
    object caster;
    set_spell_name("summon");
    set_spell_desc("Summon a messenger.");
    set_spell_target(spell_target_caster_environment);
    set_spell_time(8);
    set_spell_mana(35);
    set_spell_task(TASK_ROUTINE - (caster->query_stat(SS_RACE) / 2));
    set_spell_ingredients(0);
    set_spell_element(SS_ELEMENT_AIR, 20);
    set_spell_form(SS_FORM_CONJURATION, 20);

}
static object gMessenger;

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    if (resist[0])
    {
        caster->catch_tell("For some reason your messenger is "+
          "unable to return to you.\n");
        return;
    }

    caster->catch_tell("You stand quietly feeling the surging "+
      "power of Thanar course through you.\nYour summons are "+
      "heard as a small black snake arrives coiling itself "+
      "along your arm.\n");

    tell_room(targets[0],
      QCTNAME(caster) + " stands quietly concentrating.\n"+
      "You feel an eerie dark presence then notice a small "+
      "black snake out of nowhere.\n", ({caster}));

//    if (!objectp(gMessenger))
if(1)
    {
        FIXEUID;
        gMessenger =
          clone_object("/d/Raumdor/guilds/thanar/messenger/snake"); 

        gMessenger->move(caster,1);
    }
    else
    {
        gMessenger->fly_to_someone(caster);   
    }
}

