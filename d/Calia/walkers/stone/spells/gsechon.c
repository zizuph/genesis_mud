
  /*
   * Gsechon (Name Forget) Spell for the Stonewalkers Guild
   * by Jaacar
   * November 7th, 1998
   */

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include "defs.h"
#include STONE_HEADER

public void gsechon(object caster, object *targets, int *resist, int result);
public int create_spell_gsechon(object caster, string argument, object *targets);

public void
create_spell_gsechon(object caster, string argument, object *targets)
{
    set_spell_time(1);
    set_spell_mana(24);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_EARTH,20);
    set_spell_form(SS_PRAYER,20);
    set_spell_ingredients(({"rock"}));
    set_spell_resist(spell_resist);
    set_spell_target_verify(spell_verify_present);
    set_spell_effect(gsechon);
    return 0;
}

public void
gsechon(object caster, object *targets, int *resist, int result)
{

    if (random(100) < resist[0])
    {
        caster->catch_tell("You successfully cast the Gsechon spell but "+
            "it seems to have no effect.\n");
        return;
    }

    targets[0]->catch_tell(caster->query_The_name(targets[0])+" mumbles some strange words "+
        "under "+C_HIS+" breath, then closes "+C_HIS+" eyes.  Your "+
        "head begins to pound with pain as the blood rushes against "+
        "your skull rapidly.  Grasping your head, you close your "+
        "eyes until the pain goes away.\n");
    caster->catch_tell("You chant the ancient mantras of Gsechon, and "+
        "close your eyes, concentrating on "+targets[0]->query_the_name(caster)+".  "+
        targets[0]->query_The_name(caster)+" grasps "+TS_HIS+" head and winces as if "+
        "in terrible pain.  "+targets[0]->query_The_name(caster)+" removes "+TS_HIS+
        " hands from "+TS_HIS+" head, and appears to be in much less "+
        "pain that "+TS_HE+" was a moment ago.\n");
    tell_room(environment(caster), QCTNAME(caster)+" mumbles some strange "+
        "words under "+C_HIS+" breath, then closes "+C_HIS+" eyes.  Suddenly, "+
        QNAME(targets[0])+" grasps "+TS_HIS+" head and appears to "+
        "be in a great amount of pain.  "+QCTNAME(targets[0])+
        " removes "+TS_HIS+" hands from "+TS_HIS+" head and appears "+
        "to be in much less pain than "+TS_HE+" was a moment ago.\n",
        ({ caster, targets[0]}));
    targets[0]->remove_remembered(caster->query_real_name());
}
