/*
 *  /d/Emerald/common/guild/aod/npc/offensive_trainer.c
 *
 *  This is the training npc for the Offensive Training Hall in
 *  the Army of Darkness guild.
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
    set_living_name("Baruk");
    set_name("baruk");
    add_name( ({ "trainer" }) );
    set_adj( ({ "broad-armed", "musclebound", }) );

    set_title("of the Trueborn Tribe, Master of Crushing for the"
            + " Army of Darkness");

    set_long("This ogre looks to be a real brute. His vast shoulders"
      + " and arms look capable of using a small tree as a weapon!"
      + " He is probably able to help you <learn> or <improve>"
      + " skills.\n");

    config_ogre(160);  /* A very powerful npc */

    set_job_response("I train to crush the Ogre way! SMASH! SMASH!");

    remove_prop(LIVE_I_NEVERKNOWN);

    setuid();
    seteuid(getuid());
} /* create_aod_ogre */
