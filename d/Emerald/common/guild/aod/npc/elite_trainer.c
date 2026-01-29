/*
 *  /d/Emerald/common/guild/aod/npc/elite_trainer.c
 *
 *  This is the training npc for the Elite Training Hall
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
    set_living_name("Tukatog");
    set_name("tukatog");
    add_name( ({ "trainer" }) );
    set_adj( ({ "hulking", "green-skinned" }) );

    set_title("of the Trueborn Tribe, Smashing Stick Master Trainer"
            + " for the Army of Darkness");

    set_long("This ogre looks like a real smasher. Huge, hammer-like"
      + " fists are attached to its bulging arms. Its broad, flat"
      + " forehead crowns beady, hate-filled eyes."
      + " He is probably able to help you <learn> or <improve>"
      + " skills.\n");

    config_ogre(200);  /* A very powerful npc */

    set_job_response("Tukatog Smash! SMASH WITH TWO CLUBS! TEACH!");

    remove_prop(LIVE_I_NEVERKNOWN);

    setuid();
    seteuid(getuid());
} /* create_aod_ogre */
