#include <filter_funs.h>
#include "climb.h"
#include "local.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    set_short("You are climbing the rock");
    set_long("You are climbing the big, dark, scary rock!\n");

}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

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

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    ROOM_D->set_climber_state(0);
    ROOM_U->set_climber_state(0);
}

