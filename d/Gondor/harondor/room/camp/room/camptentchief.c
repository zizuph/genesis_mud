/* Name      : /d/Gondor/harondor/room/camp/room/camptentchief.c
 * Purpose   : The chief's pavilion inside the camp of Haradrim
 * Created by: Sir Toby, Gondor Domain, 2006-02-28
 * Modified  : Sir Toby, Gondor Domain, 2006-08-23
 *                       Added the chief cloning
 */

#pragma strict_types

#include "/d/Gondor/harondor/room/camp/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/harondor/room/camp/base_tent.c";


object	*Haradrim = allocate(2);
object	*Chief = allocate(1);

public void
create_gondor()
{
   setup_tent();

   add_my_desc("The ground is covered with straw mats.\n");

   add_prop(ROOM_I_INSIDE, 1);

   add_exit(HAR_RM_CAMP_DIR + "campchief", "out");
   reset_room();
}


public void
reset_room()
{
   ::reset_room();
   
   if(!find_living("coul-mahlu"))
   {
      clone_npcs(Chief, HAR_RM_NPC_DIR + "chief", -1.0);
      clone_npcs(Haradrim, HAR_RM_NPC_DIR + "haradrim", -1.0);
   }
   else
      clone_npcs(Haradrim, HAR_RM_NPC_DIR + "haradrim", -1.0);

}


