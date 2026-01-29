/*
 * A corpse buried in the forest.
 * -- Finwe, May 2001
 */

#pragma save_binary

inherit "std/container";

#include "/d/Shire/cypress/sys/defs.h"
#include "../local.h"
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

inherit "/lib/keep";

create_container()
{
    set_name("corpse");
    set_short("decomposing corpse");
    set_adj("rotting");
    set_long("This is a the decomposed body of what was once a great " +
        "warrior. It lies buried under leaves and branches. " +
        "Now it is nothing more than a decomposing skeleton. " +
        "The bones are broken and shattered from animals " +
        "gnawing on them. Wrapped around its bones are rusting " +
        "armour and in its bony grasp is a once great " +
        "weapon.\n");
    add_prop(CONT_I_IN,1);
    add_prop(CONT_I_WEIGHT,80000);
    add_prop(CONT_I_VOLUME,100000);
    add_prop(CONT_I_MAX_WEIGHT,80000);
    add_prop(CONT_I_MAX_VOLUME,100000);
    enable_reset(200);
    reset_container();
  
}


void
reset_container()
{
    object armour1, armour2, weapon1, weapon2;
    setuid();
    seteuid(getuid());

    if (!present("armour"))
    {
        clone_object(ARM_DIR + "ran_arm")->move(TO,1);
        clone_object(ARM_DIR + "ran_misc_arm")->move(TO,1);
    }

    if(!present("weapon"))
    {
        clone_object(WEP_DIR + "ran_wep")->move(TO,1);
        clone_object(WEP_DIR + "ran_wep")->move(TO,1);
    }

} 
