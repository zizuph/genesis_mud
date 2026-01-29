/*
 *  /d/Emerald/common/guild/aod/npc/ogre_trainer.c
 *
 *  This is the training npc for the Ogre Training Hall in
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
    set_living_name("Ogg");
    set_name("ogg");
    add_name( ({ "trainer" }) );
    set_adj( ({ "big", "lumbering", }) );

    set_title("of the Trueborn Tribe, Basic Ogre Skillmaster for the"
      + " Army of Darkness");

    set_long("Though somewhat fatter than the typical ogre, this"
      + " creature stands a good thirteen feet high with arms"
      + " as thick as tree trunks. He is probably able to help"
      + " you <learn> or <improve> skills.\n");

    config_ogre(150);  /* A rather powerful npc */

    set_job_response("Me train face smashing skills! You learn!");

    remove_prop(LIVE_I_NEVERKNOWN);

    setuid();
    seteuid(getuid());
} /* create_aod_ogre */
