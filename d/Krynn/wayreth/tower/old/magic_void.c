#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/wayreth/guild/local.h"

inherit "std/room";


void
reset_room()
{
    return;
}


void
create_room()
{
    set_short("The magic void");
    set_long("A bright light blinds you. You are unable to "
      + "see anything.\n");
}

void
enter_inv(object ob, object from)
{
    string start_room;
    object to;

    ::enter_inv(ob, from);

    if (living(ob) && interactive(ob))
    {
	  if (IS_MEMBER(ob))
        {
            //call_other(ADMINDIR + "admin", "remove_wohs_member", ob, 3);
            start_room = ADMIN->query_starting_room(ob->query_real_name());
	      if (stringp(start_room))
            {
                start_room->load_me();
                to = find_object(start_room);
                if (objectp(to))
                {
                    ob->move(to);
                    return;
                }
            }

            start_room = DEFAULT_START_LOC;
            start_room->load_me();
            to = find_object(start_room);
            ob->move(to);

        }
    }
}
