/*
 *  /d/Emerald/common/guild/aod/npc/shopkeeper.c
 *
 *  This is the shopkeeper for the Army of Darkness general store.
 *
 *  Created December 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit AOD_NPC_DIR + "aod_ogre";

#include <stdproperties.h>

/* prototypes */
public void        create_aod_ogre();


/*
 * Function name:        create_aod_ogre
 * Description  :        dummy routine for inheriting files
 */
public void
create_aod_ogre()
{
    set_living_name("Waggabor");
    set_name("waggabor");
    add_name( ({ "shopkeeper", "_aod_shopkeeper" }) );
    set_adj( ({ "huge", "sleepy-eyed" }) );

    set_title("the Wide, Shopkeeper for the Army of Darkness");

    set_long("This very stout ogre peers at you through heavy and"
      + " wrinkled eyelids. His movements are slow and ponderous,"
      + " and he is constantly making a low, gurgling noise in"
      + " his throat. When in his shop, he's the keeper of things."
      + " You could probably try to <buy> or <sell> things when"
      + " he's around.\n");

    add_act("emote stomps slowly over to a pile of loot and spits"
      + " on it.");
    add_act("emote booms: SHOP SMART, SHOP S-MART!");
    add_act("emote ducks his head through the hole in the wall"
      + " and peers around. Looking confused, he stomps back"
      + " over to the counter.");
    add_act("emote lifts up the counter and looks underneath it."
      + " Not finding anything, he drops it with a room-shaking"
      + " thud.");
    add_act("emote booms: BUY AND SELL! YOU HERE FOR WHAT?");
    add_act("emote booms: ME HERE TO SELL! YOU HERE TO BUY?");
    add_act("emote rubs his thick eyelids with a hammy fist.");

    config_ogre(200);  /* A real bruiser */

    set_job_response("SELL SELL SELL!");

    remove_prop(LIVE_I_NEVERKNOWN);

    setuid();
    seteuid(getuid());
} /* create_aod_ogre */