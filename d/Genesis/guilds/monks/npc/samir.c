/*
 * File:     samir.c
 * Created:  Cirion 1998.10.22
 * Purpose:  defence trainer of the monks
 * Cloned:   /d/Earthsea/monk/room/training_defence 
 * Modification Log:
 *
 */
#include "defs.h"
#include <ss_types.h>

inherit MONK_NPC + "npc";

void
create_monk ()
{
    set_name ("samir");
    set_race_name ("human");
    set_adj (({ "dark-skinned", "bald" }));
    set_long ("Deep, sky-blue eyes clash with the deep brown skin "
        + "of this tall and imposing human. He looks about him with "
        + "confidence and wisdom, his strength and speed apparant "
        + "beneath his flowing robe.\n");

    init_monk ();
    set_gender(G_MALE);
    set_height_weight(6.3, 146);


    // as a trainer, all skills are maxxed
    set_skill (SS_UNARM_COMBAT, 100);
    set_skill (SS_DEFENCE, 100);
    set_skill (MONK_SKILL_FOCUS, 100);
    set_skill (MONK_SKILL_STRIKE, 100);
    set_skill (MONK_SKILL_PLEXUS, 100);
    set_skill (SS_AWARENESS, 100);
    set_skill (SS_BLIND_COMBAT, 100);

    // give him some silver coins
    equip_monk (({ 0, 19 + random (90) }));

    set_act_time(10);
    add_act(({ "emote kneels upon the floor.", "emote whispers a brief prayer.",
        "emote rises and look around with renewed strength." }));
    add_act("smile conf " + VBFC_ME("vbfc_one_living"));
    add_act("emote executes a quick and expert defensive roll on the floor.");
    add_act("emote clenches his fists.");
}


