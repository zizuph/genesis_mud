/* Solace coded by Lord Rastlin */

#include "/d/Krynn/common/defs.h"
#include RND_MEET
#include "local.h"
#include <macros.h>
#include "/sys/stdproperties.h"
#include <filter_funs.h>

inherit  SOLINROOM;

object specs;
string room;

void
create_solace_room()
{
    set_short("The Quest master's house");
    set_long("This is the Quest master's house. It is a nice little house " +
	     "with a desk and a chair. There is also a soft rug on the " +
	     "floor. On one wall you can see a sign.\n");

    add_item("chair", "It is a ordinary wooden chair.\n");
    add_item("desk", "The desk is filled with strange objects.\n");
    add_item("rug", 
	     "It's thick and very soft. It would be a nice bed if needed.\n");
    add_item("sign",
	     "There are some letters on the sign, why not read it?\n");

    add_cmd_item("sign", "read", "@@read");
    
    add_exit(TDIR + "bridge_walk03", "south");
    
    add_prop(ROOM_I_NO_CLEANUP, 1);
    
    set_alarm(1.0, 0.0, "reset_solace_room");
}

public void
set_up_questmaster()
{
    if (P("quest_master", TO))
        return;
    
    clone_object(NPC + "quest_master")->move(TO);
    tell_room(TO, "There is a small puff of smoke as the master arrives.\n");
}

public void
set_up_glasses()
{
    int hide = 0;

    /* move the glasses every reset if they haven't been found,
       in case they ended up in a non accessible room or something */

    if (!specs)
        specs = clone_object(OBJ + "glasses");
    else 
        if (E(specs) != find_object(room) ||
	    sizeof(FILTER_PLAYERS(all_inventory(find_object(room)))))
            return;

    room = GET_RANDOM_ROOM("/d/Krynn/solamn/thief/");
    room->load_me(); /*This line isn't necessary is it? -Macker
		       Prolly not, but just to make sure. :) ~Aridor */
    if (!random(3))
    {
        hide = random(25) + 1;
        specs->add_prop(OBJ_I_HIDE, hide);
    }
    specs->move(room, 1);

    find_player("aridor")->catch_msg("Glasses moved to: " + room + "(" +
				     hide + ").\n");
}

void
reset_solace_room()
{
    set_up_questmaster();
    set_up_glasses();
}

public int
read()
{
    write("These are the instructions on how to communicate with the Quest " +
	  "master:\n");

    cat(LOG + "qm_help.txt");

    say(QCTNAME(TP) + " reads the sign.\n");
    return 1;
}







