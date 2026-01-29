/* Void coded by Lord Rastlin */

#pragma save_binary

inherit "/std/room";
#include "/sys/stdproperties.h"
#include "/d/Krynn/common/defs.h"
#include <std.h>

create_room() {
   set_short("VOID");
   set_long("The void. And remember, magic is useless in the void.\n");
   add_prop(ROOM_I_NO_CLEANUP, 1);
}

public void
enter_inv(object ob, object from)
{
    object prop;

    if (interactive(ob))
        if (!(SECURITY->query_wiz_level(ob->query_real_name())))
	{
            if ((prop = ob->query_prop(LIVE_O_KRYNN_DRAGON)))
	    {
		write(BS("Hmmm.. Something strange has happened. You " +
			 "probably went link-dead when you where flying " +
			 "on one of the dragons in Krynn. You will be " +
			 "taken to the starting place for the dragon.", 70));
		ob->move_living("X", prop);
	    }
            else
	      write(BS("Ooppss... You are not supposed to be here, " +
		       "you better contact a wizard to help you out " +
		       "from here.", 70));
	}
    ::enter_inv(ob, from);
}
