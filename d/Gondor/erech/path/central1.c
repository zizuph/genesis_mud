/*
 * central1.c
 * By Skippern
 */
#pragma strict_types

#include "../erech.h"

inherit E_STD + "path.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include TERRAIN_TYPES

/* Prototypes */
public void      create_gondor();
public void      reset_room();
public string    try_search(object tp, string str);

/* Global variables */
object ob;
object *ghost;
string Searching;
int    nr;
int    key;

/*
 * Function name:    create_gondor()
 * Definition   :    Creates the room.
 */
public void
create_gondor()
{
  set_short("Inside a tunnel.");
  set_long("You are inside a tunnel. The air feels very dense here. You " +
	   "are in the heart of the White Mountains.\n");

  tunnel_items();

  add_prop(ROOM_I_LIGHT, -2);
  add_prop(ROOM_I_INSIDE, 1);
  add_prop(ROOM_S_DARK_LONG, DARK_ROOM_LONG);
  add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_TUNNEL);
  add_prop(OBJ_I_SEARCH_TIME, 15);
  add_prop(OBJ_S_SEARCH_FUN, "try_search");

  nr = 4;
  ghost = allocate(nr);
  reset_room();

  add_exit(E_PATH + "north3.c", "west", "@@pass", 2, 0);
  add_exit(E_PATH + "central2.c", "southeast", "@@pass", 2, 0);
}

public void
reset_room()
{
    reset_ghosts(ghost, nr);
    key = 1;
}

void
init()
{
    ::init();
}

public void
leave_inv(object ob, object dest)
{
    if (Searching == ob->query_name())
    {
      Searching = "";
    }
    ::leave_inv(ob, dest);
}

public string
try_search(object tp, string str)
{
    string tmpstr;
    /*
    if (parse_command(LOW(str), ({}), "'dust' / 'rumble' %s", tmpstr) &&
	(!strlen(tmpstr) || parse_command(tmpstr, ({}), "[for] [key]")))
	{ */
	if (this_player()->query_skill(SS_AWARENESS) > 15 && 
	    CAN_SEE_IN_ROOM(this_player()) && key != 0)
	{
	    say(QCTNAME(this_player()) + " finds something in the dust.\n");
	    ob = clone_object(E_OBJ + "pkey");
	    ob->move(this_player());
	    key = 0;
	    return "You find a key in the dust.\n";
	}
	//    }
    return "";
}

int query_key() { return key; }
