/* Name      : /d/Gondor/harondor/room/camp/room/camptent06.c
 * Purpose   : A tent inside the camp of Haradrim
 * Created by: Sir Toby, Gondor Domain, 2005-11-20
 * Modified  : Sir Toby, Gondor Domain, 2006-01-07
 *             Sir Toby, Gondor Domain, 2006-02-28
 *                       Added more add_item and fixed NPC cloning
 *                       Added base_tent.c and all description
 *                       for the tent is found there for simplicity
 *                       in changes.
 */

#pragma strict_types

#include "/d/Gondor/harondor/room/camp/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/harondor/room/camp/base_tent.c";


object	*Haradrim = allocate(4);

public void
create_gondor()
{
    FIXEUID;

    setup_tent();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(HAR_RM_CAMP_DIR + "camp06", "out");
    reset_room();
}


public void
reset_room()
{
    ::reset_room();
    clone_npcs(Haradrim, HAR_RM_NPC_DIR + "haradrim", -1.0);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        start_room_tells();
    }
}

