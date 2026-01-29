inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "climb.h"

create_room()
{
    set_noshow_obvious(1);
    add_prop(ROOM_I_INSIDE, 0);
    set_short("You are climbing the rock");
    set_long("You are climbing the rock.\n");

    add_exit(ROOM_D, "_never_use_1", 1);
    add_exit(ROOM_U, "_never_use_2", 1);

}

void
enter_inv(object ob, object from)
{
  if(!living(ob))
  {
    tell_room(TO, "The "+ob->short()+" falls down.\n");
    tell_room(ROOM_D, "The "+ob->short()+" falls from the rock.\n");
    ob->move(ROOM_D);
    return;
  }
  if((from != find_object(ROOM_D)) && (from != find_object(ROOM_U)))
  {  /* Perhaps LD before?  */
    ob->catch_msg("You slide down the rock.\n");
    tell_room(ROOM_D, QCTNAME(ob)+" slides down the rock.\n");
    tell_room(TO, QCTNAME(ob)+" slides down the rock.\n", ob);
    ob->move_living("M", ROOM_D);
  }
}
