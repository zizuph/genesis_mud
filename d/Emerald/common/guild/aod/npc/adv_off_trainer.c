/*
 *  /d/Emerald/common/guild/aod/npc/adv_off_trainer.c
 *
 *  This is the training npc for the Advanced Offensive Training Hall
 *  in the Army of Darkness guild.
 *
 *  Created June 2006, by Cooper Sherry (Gorboth)
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
    set_living_name("Gruntok");
    set_name("gruntok");
    add_name( ({ "trainer" }) );
    set_adj( ({ "fearsome", "yellow-tusked" }) );

    set_title("of the Trueborn Tribe, Smashing Stick Trainer for the"
            + " Army of Darkness");

    set_long("This creature looks dangerous even by Ogre standards."
      + " Huge muscles ripple along his arms and legs, and his"
      + " huge cracked lips sag to make way for two splintered"
      + " yellow tusks which protrude from his lower jaw."
      + " He is probably able to help you <learn> or <improve>"
      + " skills.\n");

    config_ogre(170);  /* A very powerful npc */

    set_job_response("Me teach face smashing with club!");

    remove_prop(LIVE_I_NEVERKNOWN);

    setuid();
    seteuid(getuid());
} /* create_aod_ogre */
