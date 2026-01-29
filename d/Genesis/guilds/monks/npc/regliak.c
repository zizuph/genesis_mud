/*
 * File:     regliak.c
 * Created:  Cirion 1998.10.22
 * Purpose:  caretaker of the monestary
 * Cloned:   /d/Earthsea/monk/room/hall_lower_north 
 * Modification Log:
 *
 */
#include "defs.h"
#include <ss_types.h>

inherit MONK_NPC + "npc";

void
create_monk ()
{
    set_name ("regliak");
    set_race_name ("dwarf");
    set_adj (({ "ancient", "blind" }));
    set_long ("His eyes white and sightless, this ancient "
        + "dwarf stands with the the dignity of one who "
        + "has lead a long and difficult life.\n");

    init_monk ();
    set_gender(G_MALE);
    set_height_weight(3.3, 65);

    // give him some copper coins
    equip_monk (({ 19 + random (90) }));

    // this is a forced act, since he performs various
    // clean up duties in the monestary.
    set_act_time(10);
    add_act(({ VBFC_ME("verify_home"),
        "s", "s", "emote trims some of the branches of "
            + "the tree.", "emote picks up the trimmed branches "
            + "and piles them neatly near the doorway to the monestary.",
        "n", "w", "emote peers sightlessly around.",
        "w", "emote polishes the base of the great statue.",
        "emote dusts the altar with great respect.",
        "e", "e", "e", "greet maiko", "emote cleans the table with great care.",
        "emote cleans the window above the fireplace", "w", "n",
        "emote polishes the jade pillars.", "w", "emote dusts off the desk.",
        "e"
        }), 1);
}

string
verify_home()
{
    // make sure we start where we should be starting
    if(environment(TO) != find_object(MONK_ROOM + "hall_lower_north"))
        move_living("away", MONK_ROOM + "hall_lower_north");

    return "stretch";
}

