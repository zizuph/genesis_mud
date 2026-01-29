/* 
*   Half-Giants village in the pass overhauled.
*   /d/Kalad/common/wild/pass/giantpass/
*
*  Standard room for giants camp in NW KALAD
*  Purpose    : Valley setting
*  Located    : Hespyre Mountains
*  Created By : 
*  Modified By: Meton 2020
*   other rooms doesnt work with /std/room.
*/ 

inherit "/d/Kalad/room_std";
//inherit  "/std/room";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/filter_funs.h"
#include "../local.h"

int summoning_done;
/* by Antharanos */
public void
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
    set_short("a set_short is needed here");
    set_long("A set_long is needed here.\n");
}
