
 /* Agios (Fly) spell for the Windwalkers of Thalassia
  * by Jaacar 
  */

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";
inherit "/d/Calia/std/contents_desc";

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "defs.h"
#include WIND_HEADER

#define SHRINE_ENTRANCE "/d/Calia/worshippers/shrine/entrance"
#define TEMPLE "/d/Calia/worshippers/temple/s_chamber"
#define START_LOC "/d/Calia/mountain/cloud/startroom"

public void agios(object caster, object *targets, int *resist,
    int result);
public int create_spell_agios(object caster, object *targets,
    string argument);
string location;

public void
agios(object caster, object *targets, int *resist, int result)
{
 
    if (environment(caster)->query_prop(ROOM_I_INSIDE))
    {
        caster->catch_tell("You can only use the powers of Agios "+
            "outside!\n");
        return;
    }

    if (location == "shrine")
    {
        caster->catch_tell("After successfully reciting the ancient mantras "+
            "of Agios, you feel a tingling sensation come over your entire "+
            "body.  Your feet begin to lift off of the ground and you begin "+
            "to soar into the sky above you.\n");
    
        tell_room(environment(caster),QCTNAME(caster)+" places "+
            C_HIS+" fingers upon "+C_HIS+" forehead briefly.\nSuddenly "+
            C_HIS+" entire body begins to leave the ground and "+C_HE+
            " soars into the sky above you, disappearing from sight.\n",
            ({caster}));

        caster->catch_tell("You fly high into the sky and dance in and out "+
            "of the clouds.  In front of you there is a shimmering cloud "+
            "remarkably in the shape of a doorway.  You decide to fly "+
            "through it and find yourself standing at the entranceway "+
            "to the Elemental Shrine.  You feel certain that if you just "+
            "step back through the archway that you will end up back where "+
            "you started from.\n");
        caster->move_living("M",SHRINE_ENTRANCE);
    }
    if (location == "temple")
    {
        caster->catch_tell("After successfully reciting the ancient mantras "+
            "of Agios, you feel a tingling sensation come over your entire "+
            "body.  Your feet begin to lift off of the ground and you begin "+
            "to soar into the sky above you.\n");
    
        tell_room(environment(caster),QCTNAME(caster)+" places "+
            C_HIS+" fingers upon "+C_HIS+" forehead briefly.\nSuddenly "+
            C_HIS+" entire body begins to leave the ground and "+C_HE+
            " soars into the sky above you, disappearing from sight.\n",
            ({caster}));

        caster->catch_tell("You fly high into the sky and dance in and out "+
            "of the clouds.  Below you there is a small temple nestled inside "+
            "a grove of vines. You decide to fly through an archway that you "+
            "see and find yourself standing at the silver altar in the "+
            "Worshipper temple.\n");
        caster->move_living("M",TEMPLE);
    }
    else
    {
        caster->catch_tell("After successfully reciting the ancient mantras "+
            "of Agios, you feel a tingling sensation come over your entire "+
            "body.  Your feet begin to lift off of the ground and you begin "+
            "to soar into the sky above you.\n");
    
        tell_room(environment(caster),QCTNAME(caster)+" places "+
            C_HIS+" fingers upon "+C_HIS+" forehead briefly.\nSuddenly "+
            C_HIS+" entire body begins to leave the ground and "+C_HE+
            " soars into the sky above you, disappearing from sight.\n",
            ({caster}));

        caster->catch_tell("You fly high into the sky and dance in and out "+
            "of the clouds.  In front of you see the cloud where you begin "+
            "each days journey from and come to a perfect landing upon it.\n");
        caster->move_living("M",START_LOC);
    }
}

public int
create_spell_agios(object caster, object *targets, string argument)
{
    set_spell_time(4);
    set_spell_mana(50);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR, 50);
    set_spell_form(SS_PRAYER, 50);
    set_spell_ingredients(({"eel grass","feather"})); 
    set_spell_effect(agios);
    set_spell_stationary(1);
    location = argument;
    return 0;
}
