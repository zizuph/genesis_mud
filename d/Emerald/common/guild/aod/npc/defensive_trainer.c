/*
 *  /d/Emerald/common/guild/aod/npc/defensive_trainer.c
 *
 *  This is the training npc for the Defensive Training Hall
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
    set_living_name("Brofus");
    set_name("brofus");
    add_name( ({ "trainer" }) );
    set_adj( ({ "suspicious", "jowel-faced" }) );

    set_title("of the Trueborn Tribe, Swishing Trainer "
            + "for the Army of Darkness");

    set_long("This ogre looks pretty proper! Huge sheets of flesh"
      + " hang as jowels from each side of his monstrous sagging"
      + " face. Foul layers of fat rest in deep folds all along"
      + " his body and suspicious little eyes peer above its flat nose."
      + " He is probably able to help you <learn> or <improve>"
      + " skills.\n");

    config_ogre(170);  /* A very powerful npc */
    set_ogre_weapon(AOD_WEP_DIR + "bucket");

    set_job_response("I's all about da tricky swishin'! Shaddap!");

    remove_prop(LIVE_I_NEVERKNOWN);

    setuid();
    seteuid(getuid());
} /* create_aod_ogre */

