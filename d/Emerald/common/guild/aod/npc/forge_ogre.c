/*
 *  /d/Emerald/common/guild/aod/npc/forge_ogre.c
 *
 *  This ogre is responsible for melting down weapons and armours that
 *  players bring to the forge for the Army of Darkness guild.
 *
 *  Created July 2006, by Cooper Sherry (Gorboth)
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
    set_living_name("Smorny");
    set_name("smorny");
    add_name( ({ "blacksmith", "smith" }) );
    set_adj( ({ "fat", "pointy-chinned" }) );

    set_title("of the Trueborn Tribe,"
      + " Blacksmith for the Army of Darkness");

    set_long("This ogre, frankly, looks completely insane. Despite his"
      + " squat and massively fat body, he moves with a twitchy speed"
      + " that makes you rather uneasy. His chin is long and pointed, and"
      + " he has a somewhat maniacal grin. He is the blacksmith for"
      + " the Army of Darkness. You might be able to <buy> weapons"
      + " or armours from him.\n");

    config_ogre(150);  /* A fairly powerful npc */

    set_job_response("Eeeee ... ? I's meltin' da stuff! I's some kinda"
      + " smith ... eh ... ya.");

    set_ogre_weapon(AOD_WEP_DIR + "shovel");

    remove_prop(LIVE_I_NEVERKNOWN);

    add_act("emote scoops up a load of scrap metal from one of the"
      + " many piles and pitches it into the melting pot.");
    add_act("emote plops the end of his shovel into the melting pot and"
      + " slowly stirs the molten fluid.");
    add_act("emote trips over one of the piles of metal and curses"
      + " loudly!");
    add_act("emote takes a heated piece of metal to the anvil and"
      + " pounds on it with a large hammer.");
    add_act("emote bellows: Me getting smarter every day! Learn better"
      + " hammer tricks!");
    add_act("emote bends some heated metal over his knee, and looks at"
      + " it with a satisfied smile.");
    add_act("emote beats on a heated slab of metal with his bare fists,"
      + " sparks flying everywhere as he does so.");

    setuid();
    seteuid(getuid());
} /* create_aod_ogre */