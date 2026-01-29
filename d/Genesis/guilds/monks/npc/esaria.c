/*
 * File:     esaria.c
 * Created:  Cirion 1998.10.22
 * Purpose:  misc. trainer of the monks
 * Cloned:   /d/Earthsea/monk/room/training_other 
 * Modification Log:
 *
 */
#include "defs.h"
#include <ss_types.h>

inherit MONK_NPC + "npc";

void
create_monk ()
{
    set_name ("esaria");
    set_race_name ("gnome");
    set_adj (({ "short", "childlike" }));
    set_long ("Sweet and smiling, this gnome looks around her "
        + "with curious and child-like eyes. Her soft robe reaches "
        + "to the ground, so that is drags lightly along as "
        + "she moves.\n");

    init_monk ();
    set_gender(G_FEMALE);
    set_height_weight(3.1, 176);


    // as a trainer, all skills are maxxed
    set_skill (SS_UNARM_COMBAT, 100);
    set_skill (SS_DEFENCE, 100);
    set_skill (MONK_SKILL_FOCUS, 100);
    set_skill (MONK_SKILL_STRIKE, 100);
    set_skill (MONK_SKILL_PLEXUS, 100);
    set_skill (SS_AWARENESS, 100);
    set_skill (SS_BLIND_COMBAT, 100);

    // give her some silver coins
    equip_monk (({ 0, 19 + random (90) }));

    set_act_time(10);
    add_act("emote shuffles about.");
    add_act("twinkle " + VBFC_ME("vbfc_one_living"));
    add_act("wink know " + VBFC_ME("vbfc_one_living"));
    add_act("grin soft " + VBFC_ME("vbfc_one_living"));
}


