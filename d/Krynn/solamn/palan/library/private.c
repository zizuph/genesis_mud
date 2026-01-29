/* created by Aridor, 06/06/94 */

inherit "/std/room";

#include "local.h"
#include <macros.h>

object asti;

void
reset_room()
{
    if (asti)
      return;
    asti = clone_object(LIBRARY + "astinus");
    asti->move_living("xxx",TO);
}


void
create_room()
{
    set_short("Private chamber of Astinus");
    set_long("You are in Astinus' private study. Here he writes down " +
	     "the history of Krynn as it happens. The room is extremely " +
	     "spartan, you can only see a chair and a desk here.\n");
    
    add_prop(ROOM_I_LIGHT, 10);
    INSIDE;
    add_prop(ROOM_M_NO_ATTACK, 1);
    add_prop(ROOM_M_NO_MAGIC_ATTACK, 1);
    add_prop(OBJ_S_WIZINFO,"Wizards can add books here by simply putting " +
	     "the file into .../library/personal/<title>\n");

    add_exit(LIBRARY + "public","north","@@without_book_only");

    add_item(({"chair"}),"An ordinary chair.\n");
    add_item(({"desk"}),"An ordinary desk. The only special thing you " +
	     "notice is a crystal sphere set on a stand on the desk.\n");
    add_item(({"sphere","ball","crystal sphere"}),
	     "It looks like it's made from glass. You cannot detect " +
	     "anything special about it.\n");

    set_alarm(1.0,0.0,"reset_room");
}

int
without_book_only()
{
    object ob = present(PALANTHAS_BOOK, TO);
    if (present(PALANTHAS_BOOK,TP))
      {
	  write("Don't forget to return the book first.\n");
	  return 1;
      }
    if (ob)
      ob->remove_object();
    (LIBRARY + "public")->back_from_audition(TP);
    return 0;
}

void
set_person_on_audition(object who)
{
    asti->give_out_book(who);
}

void
is_coming_on_audition(object who)
{
    set_alarm(10.0,0.0,"set_person_on_audition", who);
}
