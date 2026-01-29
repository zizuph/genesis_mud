/* Name      : /d/Gondor/harondor/room/camp/room/spavilion02.c
 * Purpose   : The guards pavilion inside the camp of Haradrim
 * Created by: Sir Toby, Gondor Domain, 2006-02-28
 * Modified  : 
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
   setup_pavilion();

   add_prop(ROOM_I_INSIDE, 1);

   add_exit(HAR_RM_CAMP_DIR + "campE02", "out");
   reset_room();
}


public void
reset_room()
{
   ::reset_room();
   clone_npcs(Haradrim, HAR_RM_NPC_DIR + "guard", -1.0);
}


