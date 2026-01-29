/* -*- Mode: C -*-
 *
 * trade/houses/u-13.c
 *
 * Skippern 20(c)01
 *
 * The post office of Dol Amroth.
 */
#include "../../defs.h"

//inherit DOL_STD + "inside.c";

inherit "/d/Gondor/common/lib/post";

#include <macros.h>

/* Prototypes */

void
create_room()
{
    set_short("inside a post office");
    set_long("This is inside a post office. The walls are filled with " +
	     "small shelves and boxes with names on the. The shelves and " +
	     "boxes are sorted alfabetically. You even notices a box " +
	     "with your name on it. In the far part of the room three or " +
	     "four persons are busy sorting post, and along the northern " +
	     "wall some tables are put up so people can read and write " +
	     "mail. On a board right by the door a large poster hangs.\n");

    add_item( ({ "shelve", "shelves", "box", "boxes" }), "There are " +
	      "shelves and boxes along all walls. You can even see a " +
	      "box with a lable saying: "+this_player()->query_name()+".\n");
    add_item("board", &exa_poster());

    set_poster_name("large poster");

    clone_object(DOL_OBJ + "doors/u-13-door")->move(this_object());
    create_post();
}

void
init()
{
    ::init();
}

void
enter_inv(object ob, object from)
{
    object task;
    string *places, tmp;
    int i;

    ::enter_inv(ob, from);

    if (task = present("I_do_quest_token.c", ob))
    {
	if (task->query_task() == DOL_Q_M_EXPLORE_TOWN)
	{
  	    tmp = task->query_visit();
	    places = explode(tmp, "::");
	    for (i = 0; i < sizeof(places); i++)
	    {
		if (places[i] == "post") return;
	    }
	    places += ({ "post" });
	    tmp = implode(places, "::");
	    task->set_visit(tmp);
	    task->set_part(task->query_part()+1);
	}
    }
}
