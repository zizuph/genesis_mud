/*
 * File:     aliya.c
 * Created:  Cirion
 * Purpose:  librarian of the monks
 * Cloned:   /d/Earthsea/monk/room/library 
 * Modification Log:
 *
 */
#include "defs.h"
#include <money.h>
#include <ss_types.h>

inherit MONK_NPC + "npc";

void
create_monk ()
{
    set_name ("aliya");
    set_race_name ("elf");
    set_short ("stern graceful elf");
    set_long ("While her face and figure of her race betray none "
        + "of her years, her dark blue eyes show the ages which "
        + "she has seen. She is dressed in a soft, flowing robe, "
        + "and holds a long feathered pen in her hand.\n");

    init_monk ();
    set_gender(G_FEMALE);
    set_height_weight(5.6, 85);

    // give him some copper coins
    equip_monk (({ 19 + random (12) }));

    set_act_time(10);
    add_act(({ "emote reaches up and removes a book from the shelves.",
        "emote wipes the dust from the book.", "emote returns the book to "
        + "the shelves." }));
    add_act("peer stern " + VBFC_ME("vbfc_one_living"));
    add_act("smile warm " + VBFC_ME("vbfc_one_living"));
    add_act("sigh softly");
}


