/* Name      : /d/Gondor/harondor/room/camp/room/campE02.c
 * Purpose   : The northern campentrance to the camp of Haradrims
 * Created by: Sir Toby, Gondor Domain, 2006-02-28
 * Modified  : 
 */

#pragma strict_types

#include "/d/Gondor/harondor/room/camp/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/harondor/room/camp/base_camp.c";

public string enter_pavilion();

object	*Haradrim = allocate(4);
object  *Leader = allocate(2);

public void
create_camp()
{
   FIXEUID;
   set_areatype(0);
   set_areadesc("arid land");
   set_area("southern");
   set_areaname("Gondor");
   set_land("Harondor");
   set_extraline("Across the dry and barren land dried grasses grow " +
       "in scattered patches. Sand has blown up over them, creating " +
       "mounds in different sizes. South of here tents are raised in " +
       "neat lines, a few bigger then most. There is a small pavilion " +
       "errected just off the path offering some shadow from the " +
       "blazing sun. The path leads northwest away from the pavilion " +
       "and south closer to the tents.");

   add_harad_camp_tells();
   add_desert();
   add_small_pavilion();
   add_ephel_duath("north"); /* where they are in relation to the camp */

   add_exit(HAR_RM_CAMP_DIR + "camp03", "south", check_allow, 2);
   add_exit(HAR_RM_CAMP_DIR + "camp02", "southwest", check_allow, 2);
   add_exit(HAR_RM_CAMP_DIR + "camp04", "southeast", check_allow, 2);
   add_exit(HAR_RM_CAMP_DIR + "trail15", "northwest");
    

   add_cmd_item( ({ "pavilion"}), "enter", enter_pavilion);

   reset_room();
}

public void
reset_room()
{
   ::reset_room();
   make_haradrim(Leader, 1);
   set_alarm(0.5, 0.0, &make_haradrim(Haradrim, 0));
}

public void
init()
{
    ::init();
 
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

public string
enter_pavilion()
{
   if (!check_allow())
   {
       ENV(TP)->set_dircmd("pavilion");
       write("You step into the small pavilion.\n");
       TP->move_living("into the small pavilion", HAR_RM_CAMP_DIR + "spavilion02.c");
   }
   return "";
}

