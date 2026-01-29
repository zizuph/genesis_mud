/*
 * compartment.c
 *
 * This is simply a container that holds a few odds and ends. Some are
 * just 'red herrings' to quests, but the parchments and charcoal sticks
 * are necessary to complete the 'Sword in the Stone Quest'. Completion
 * of the 'Seer and the Lord Quest' is necessary to make this container
 * appear.
 *
 * Coded by Khail, Jan 4/97.
 */
#pragma strict_types

#include "defs.h"

inherit "/std/container";

/*
 * Function name: set_contents
 * Description  : Called when the compartment is cloned by the
 *                seer_tower, with 'who' pointing to the player
 *                that opened it. Unless the player has just
 *                completed teh Seer and the Lord Quest, the
 *                serpent ring should not be here, only the
 *                charcoal sticks and parchment.
 * Arguments    : who - Object pointer to the player who opened
 *                      the compartment.
 * Returns      : n/a
 */
public void
set_contents(object who)
{
    int i;

    seteuid(getuid());

    for (i = 0; i < 3; i++)
    {
        clone_object(OBJ + "parchment")->move(TO);
        clone_object(OBJ + "charcoal_stick")->move(TO);
    }

    if (who->query_prop(LIVE_I_DID_SEER_QUEST))
    {
        clone_object(ARM + "magic_ring")->move(TO);
        who->remove_prop(LIVE_I_DID_SEER_QUEST);
    }
}

/*
 * Function name: create_container
 * Description  : Turns this object into the compartment.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_container()
{
    set_name("compartment");
    set_adj("small");
    add_adj("hidden");
    set_long("This small compartment was hidden beneath a floorstone " +
        "which has been removed, for the time being. It's not very " +
        "large, but could safely hold a number of small items from " +
        "thieving hands.\n");


    add_prop(CONT_I_MAX_VOLUME, 4000);
    add_prop(CONT_I_MAX_WEIGHT, 50000);
    add_prop(CONT_I_HEIGHT, 10);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_VOLUME, 2000);
    add_prop(CONT_I_WEIGHT, 10);
    add_prop(OBJ_M_NO_GET, "The compartment is built right into the " +
        "floor, and is impossible to remove.\n");
    add_prop(OBJ_S_WIZINFO, "This object is revealed after a " +
        "player presses a certain stone in the wall of the " +
        "seer tower, /d/Calia/eldoral/ruins/seer_tower. The " +
        "exact stone is determined by NAME_TO_RANDOM, and " +
        "revealed to the player upon the completion of the " +
        "Seer and the Lord quest. Then and only then, the " +
        "serpent ring will be present. Any other time, it " +
        "will only be the parchments and the charcoal sticks " +
        "inside.\n");
}
