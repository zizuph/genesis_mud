/*
 * File:     guano.c
 * Created:  Cirion 1998.10.22
 * Purpose:  unarmed combar trainer of the monks
 * Cloned:   /d/Earthsea/monk/room/training_ua
 * Modification Log:
 *
 */
#include "defs.h"
#include <ss_types.h>

inherit MONK_NPC + "npc";

void
create_monk ()
{
    set_name ("guano");
    set_race_name ("goblin");
    set_adj (({ "surly", "ancient", "surly-looking" }));
    set_long ("Very short and lean, this elderly goblin's eyes show "
        + "that he has seen much of the world, and has enjoyed very "
        + "little of it. He stands in the center of the room with "
        + "a confidence and poise rare for his species.\n");

    init_monk ();
    set_gender(G_MALE);
    set_height_weight(4.5, 160);


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
    add_act("emote belches.");
    add_act("snarl");
    add_act("emote does a quick backroll in the floor, spins around, and "
        + "screams 'Kaiaiaiaiaiai', all for no apparant reason.");
    add_act("peer susp");
    add_act("emote grins unpleasantly.");
    add_act("say Havak aaaaa Kirishi!");
    add_act("scratch behind");
    add_act(({ "hiccup", "hiccup", "hiccup", "swear", "hiccup",
        "hiccup", "sigh" }));
    add_act("jump");
}


