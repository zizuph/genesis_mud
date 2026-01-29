/*
This is a workroom for the grave yard.  ***Please add anything to it
that might be of help (other exits, tools, idea board, etc.).  :)
				Dorak Da Dwarf Wiz :-)
*/

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
inherit  R_FILE
#include <stdproperties.h>
#include <std.h>

void
create_krynn_room()
{
    set_short("The workroom of Solace's Graveyard");
    set_long("\n"+
	     "This is a small cozy workroom in which Krynn wizards can work \n"+
	     "on the grave yard, out of reach of the cold damp of the graves.\n"+
	     "There is a grand window in the east wall that look out over the\n"+
	     "graveyard. On the north wall is a huge map, under which is an old\n"+
	     "pine desk with a matching comfortable chair pulled up to it. On the\n"+
	     "west wall runs a book and scroll case. On the north wall is an old\n"+
	     "fireplace with an ornate mantal. Pulled up in front of the\n"+
	     "fireplace is an armchair big enough in which to take a snooze.\n"+
	     "Right of the pine desk is a brightly glowing white forcefield.\n"+
	     "A big beautiful spiral staircase vanished into the room above.\n" +
	     "North you can reach the Krynn workroom and south is the Ansalon\n" +
	     "workroom.\n");
    
    add_exit("/d/Krynn/workroom","north","@@north_msg");
    add_exit("/d/Genesis/wiz/admin","up");
    add_exit("/d/Ansalon/workroom","south");
    clone_object("/d/Krynn/aridor/private/do_board/board")->move(TO);
}

int
north_msg()
{
    write("You step into a bright but NOT blinding white light.  No \n"+
	  "sooner have you been enveloped, then are you free of its\n"+
          "soothing radiance, stepping out into another workroom.\n");
    return 0;
}

public void 
enter_inv(object ob, object from)
{    
    ::enter_inv(ob, from);
    if (!ob->query_prop(LIVE_I_IS))
      return;
    if (((SECURITY)->query_wiz_dom(ob->query_real_name())) != "Krynn" &&
	(((SECURITY)->query_wiz_dom(ob->query_real_name())) != "Ansalon") &&
	((SECURITY)->query_wiz_rank(ob->query_real_name())) < WIZ_ARCH)
      {
	  write("*Error in loading object\n");
	  write_file("/d/Krynn/solace/graves/wiz/tried", extract(ctime(time()), 4, 15)
		     + " " + capitalize(ob->query_real_name()) + "\n");
	  ob->move_living("X","/d/Krynn/solace/village/innlanding");
      }
}
