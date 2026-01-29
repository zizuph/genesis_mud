/*
 * File:     fylia.c
 * Created:  Cirion 1998.10.22
 * Purpose:  focus trainer of the monks
 * Cloned:   /d/Earthsea/monk/room/training_focus 
 * Modification Log:
 *
 */
#include "defs.h"
#include <ss_types.h>

inherit MONK_NPC + "npc";

void
create_monk ()
{
    set_name ("fylia");
    set_race_name ("elf");
    set_adj (({ "lithe", "red-haried" }));
    set_long ("Highlighting her deep red hair are streaks of white, "
        + "twisting and falling around her long neck in graceful "
        + "strands. Falling about her ageless body is a soft, low-cut "
        + "robe. Her smile is otherwordly, haunting.\n");

    init_monk ();
    set_gender(G_FEMALE);
    set_height_weight(6.1, 146);


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

/*
    set_act_time(10);
    add_act(({ "emote raises her hands upwards, palms outward.",
        "emote sings in a soft, strange voice.",
        "smile wear." }));
    add_act("stare wisely " + VBFC_ME("vbfc_one_living"));
*/
}


