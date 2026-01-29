/*  

  /std/room.c ver 1.1

   ----------------------------------------------------------------------

   Defined functions and variables:


   set_container(object)             Sets the container for which this
                                     room represents the inside.

   ----------------------------------------------------------------------

  Typical usage:

      inherit "/std/room";

      create_room()
      {
	  set_short("A little room.");
	  set_long("This is a small but very nice room.\n");
	  add_exit("/room/church" , "north", 0);
	  add_exit("/room/post" , "post", "@@exitfun");
      }

      exitfun(to_dest)
      {
          return -1*(random(10)<3); /* 30% chance not to move
      }

*/
#pragma save_binary

inherit "/d/Krynn/dumrik/container";
#include <stdproperties.h>
#include <std.h>
#include <macros.h>
#include <ss_types.h>

#include "/std/room/exits.c"
#include "/std/room/description.c"
#include "/std/room/link.c"
#include "/std/room/map.c"
#include "/std/room/move.c"

static object   room_link_cont;	/* Linked container */
static object   *accept_here;    /* All objects created here on roomcreation */
static string   domain;
/*
 * Default constructor
 */
public void
create_room()
{
    add_prop(ROOM_I_INSIDE, 0);  /* Default is heaven above */
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);  /* Default is a room */
}

/*
 * Create the room
 */
nomask void
create_container()
{
    string str, wiz, name;

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_IS, 1);	/* This is a room */
    add_prop(ROOM_I_HIDE, 10);
    
    room_link_cont = 0;

    str = file_name(this_object());
    if (str[1] == 'd')
	sscanf(str,"/d/%s/%s/%s", domain, wiz, name);
    else
	domain = "backbone";

    seteuid(creator(this_object()));
    if (function_exists("reset_room", this_object()))
	enable_reset();
    create_room();
    accept_here = all_inventory(this_object());
    if (!sizeof(accept_here))
	accept_here = ({});
}

/*
 * An object that wont hinder a clean_up
 */
public object
clone_here(string file)
{
    object ob;
    
    ob = clone_object(file);
    accept_here += ({ ob });
    return ob;
}

public object *
query_cloned_here() { return accept_here; }

nomask void
reset_container()
{
    this_object()->reset_room();
    if (!sizeof(accept_here))
	accept_here = ({});
    accept_here = accept_here - ({ 0 });
}

#if 0
void
reset_room()
{
}
#endif

/*
 * Function name: light
 * Description:   Returns the light status in this room
 *                This function is called from query_prop() only.
 * Returns:	  Light value
 */
nomask int
light()
{
    int li;
    
    li = query_prop(ROOM_I_LIGHT);
    if (objectp(room_link_cont))
    {
	if ((environment(room_link_cont)) &&
	    (room_link_cont->query_prop(CONT_I_TRANSP) ||
	     room_link_cont->query_prop(CONT_I_ATTACH) ||
	    !room_link_cont->query_prop(CONT_I_CLOSED)))
	{
	    li += (environment(room_link_cont))->query_prop(OBJ_I_LIGHT);
	}
    }
    return query_internal_light() + li;
}

/*
 * Function name: set_container
 * Description:   Sets the container for which the room represents the inside
 * Arguments:	  ob: The container object
*/
public void
set_container(object ob)
{
    room_link_cont = ob;
}

public
set_room(ob) {}  /* This is invalid for rooms */


/* 
 * Function name: update_internal
 * Description:   Updates the light, weight and volume of things inside
 *                also updates a possible connected container.
 * Arguments:     l: Light diff.
 *		  w: Weight diff. (Ignored)
 *		  v: Volume diff. (Ignored)
 */
public void
update_internal(int l, int w, int v)
{
    ::update_internal(l, w, v);

    if (room_link_cont)
	room_link_cont->update_internal(l, w, v);
}


/*
 * Function name:
 * Description:     Obvious (Will be documented later, use man -s)
 */
public object
this_room() { return this_object(); }

/*
 * Function name: clean_up
 * Description:   This function destruct the room if there is nothing in it.
 *                If you have special variables stored in a room you should
 *		  define your own clean_up(). Also if you on startup of the
 *		  room clone some objects and put inside it, please define
 *		  your own clean_up() to destruct the room. This saves a
 *		  lot of memory in the game.
 */
public int
clean_up()
{ 
    if (MASTER == "/std/room")			/* Don't destroy /std/room */
	return 0; /* Don't call me again */

    if (!query_prop(ROOM_I_NO_CLEANUP) && 
	(sizeof(all_inventory(this_object()) - accept_here) == 0))
	remove_object();
    return 1; /* Check me next time too */
}

/*
 * Function name: room_add_object
 * Description:   Clone and move an object into the room
 * Arguments:	  file - What file it is we want to clone
 *		  num  - How many clones we want to have, if not set 1 clone
 *		  mess - Message to be written when cloned
 */
varargs void
room_add_object(string file, int num, string mess)
{
    int i;
    object ob;

    if (num < 1)
	num = 1;

    seteuid(getuid());
    for (i = 0; i < num; i++)
    {
	ob = clone_object(file);
	if (stringp(mess))
	{
	    tell_room(this_object(), mess);
	    ob->move(this_object(), 1);
 	}
	else if (living(ob))
	    ob->move_living("xx", this_object());
	else
	    ob->move(this_object(), 1);
    }
}

/*
 * Function name: stat_object
 * Description:   Called when someone tries to stat the room
 * Returns:	  A string to write
 */
string
stat_object()
{
    string str;
    int type;

    str = ::stat_object();

    if (query_prop(ROOM_I_INSIDE))
	str += "inside\t";
    else
	str += "outside\t";

    type = query_prop(ROOM_I_TYPE);
    str += " ";
    switch (type)
    {
    case 0: str += "normal"; break;
    case 1: str += "in water"; break;
    case 2: str += "under water"; break;
    case 3: str += "in air"; break;
    case 4: str += "beach"; break;
    default: str += "unknown type"; break;
    }
    str += "\t";

    return str + "\n";
}

nomask string
query_domain()
{
    return domain;
}

#if 0 
       /* This a little trick to fool the documentation maker.
	  Don't use '*/' after 'Description:' in the example.

/*
 * Typical usage of /std/room.c
 *
 * Description:   

      inherit "/std/room";

      create_room()
      {
	  set_short("A little room.");
	  set_long("This is a little but very nice room.\n");
	  add_exit("/room/church" , "north", 0);
	  add_exit("/room/post" , "post", "@@exitfun");
      }

      exitfun(to_dest)
      {
          return -1*(random(10)<3);    /* 30% chance not to move
      }
 */
public
USAGE()
{}

#endif
