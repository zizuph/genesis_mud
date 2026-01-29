/* features.c
   Tintin 920106 */

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "login.h"

/*
 * Function name: create_room()
 * Description  : Create the room.
 * In this function, we declare everything that should be fixed
 * when the room is started, and not changed in resets.
 */

create_room()
{
    object ob;

    set_short("feature room");
    set_long("You are in a small room. In the middle of the room\n" +
	     "there is black ebony table. On the table there is a book.\n" +
	     "There is also a portal leading out of here, over it is\n" +
	     "a collection of symbols that look like creatures performing\n" +
	     "a variety of activities.\n");
    
    add_item( ({"book", "black book" }),
	     "On the cover you see the text: " +
	     "   'Book of features'\n");
    add_item( ({"table", "ebony table" }),
	     "A heavy and solid black ebony table.");
}

/*
 * Function name: init
 * Description  : Add commands etc.
 */
public void
init()
{
    object ob;
    add_action("all_cmd", "", 1);
    if (this_player()->query_ghost() & GP_FEATURES)
    {
	ob = clone_object(PATH + "set_attrib");
	ob->move(this_player(), 1);
    }
}

/*
 * Function name: long
 * Description  : Modify the behaviour of long
 */
public varargs mixed
long(string arg)
{
    mixed str, *a;
    
    str = ::long(arg);

    if (arg)
	return str;
    
    a = this_player()->query_adj(1);
    if (sizeof(a) < 2 || a[0] == "" || a[1] == "")
    	str += "\nYou are still rather featureless. Reading the book might help.\n";
    else
	str += "\nYou suspect that you can do nothing more here.\n" +
	    "Maybe you should leave through the portal.\n";

    return str;
}

/*
 * Function name: enter_cmd
 * Description  : Catch all player commands. Take care of the legal ones
 *                and throw all the others away
 */
public void 
enter_cmd(string str)
{
    object player, ob;
    string tmp, *a;
    
    if (!str || !strlen(str))
    {
	write("Enter what?\n");
	return;
    }
    player = this_player();
    if (str == "portal")
    {
	ob = present("selector", this_player());
	if (ob && ob->no_leave())
	    write("An invisible force prevents you from leaving.\n");
	else if (!player->query_ghost())
	    player->move_living("through the portal.",
				player->query_def_start());
	else
	{
	    if (ob = present("selector", player))
		ob->remove_object();
	    write("As you enter the portal, there is a flash of light and\n" +
		  "you suddenly find yourself in a very different place.\n\n");
	    player->set_ghost(player->query_ghost() - GP_FEATURES);
	    if (!(player->query_ghost() & GP_SKILLS))
	    {
		say(QCTNAME(player) + " leaves through the portal.\n");
		player->set_ghost(0);
		player->ghost_ready();
	    }
	    else
		player->move_living("through the portal.", PATH + "skills");
	}
	return;
    }
    write("You find no " + str + " to enter.\n");

    return;
}

/*
 * Function name: all_cmd
 * Description  : Catch all player commands. Take care of the legal ones
 *                and throw all the others away
 */
public int
all_cmd(string str)
{
    switch(query_verb())
    {
    case "arrive":
    case "glance":
    case "depart":
    case "say":
    case "quit":
    case "Goto":
    case "goto":
    case "look":
    case "exa":
    case "examine":
    case "home":
    case "save":
    case "typo":
    case "bug":
	return 0;
	break;
    case "read":
	if (str == "book")
	{
	    notify_fail("You can't, you do not belong here!\n");
	    return 0;
	}
	break;
    case "enter":
	enter_cmd(str);
	return 1;
	break;
    case "help":
	write("You are supposed to select your two main personal features. Do:\n");
	write("     'read book'\n");
	write("This will give you further instructions.\n");
	write("When you are done, you can do 'enter portal'\n");
	return 1;
    case "leave":
    case "exit":
	enter_cmd(str ? str : "portal");
	return 1;
    default:
	if (this_player()->query_wiz_level() > 40)
	    return 0;
	write("That is not possible here.\n");
	return 1;
    }
}
