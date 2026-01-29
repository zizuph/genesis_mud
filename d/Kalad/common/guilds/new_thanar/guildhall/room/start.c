/**********************************************************************
 * - start.c                                                        - *
 * - Start location for Thanar                                      - *
 * - Created by Damaris@Genesis 3/2004                              - *
 * - New Standrad file for new area for guild. Typos fixed.         - *
 * - by Mirandus@Genesis 01/2018                                    - *
 **********************************************************************/

#pragma strict_types

#include "../guild.h"
#include <stdproperties.h>

inherit THANAR_STD_ROOM;


/*
 * Function name: create_std_thanar()
 * Description  : Creates the room from standard room file
 */
void
create_std_thanar()
{

    set_short("Temple inner sanctum");
    set_long("You are standing in the inner sanctum of Thanar's "+
      "temple. This room is small but has a warm inviting atmosphere "+
      "with tapestries and paintings covering the walls. You may "+
      "<start here> and make this your new home.\n");
    
    add_item(({"tapestry", "tapestries"}),
      "The tapestries are woven with human flair and style. The silken "+
      "threads are colourful and produce a most spectacular vision before "+
      "you.\n");
    add_item(({"thread", "threads"}),
      "The threads used in the tapestries are vibrant and have been woven "+
      "by skilled human hands.\n");
    add_item(({"painting", "paintings"}),
      "A skilled human artist beautifully crafts the paintings. The "+
      "depictions of them are of the same theme, which is of human gardens "+
      "and forest areas.\n");
    add_item(({"inner sanctum", "room", "sanctum"}),
      "This is a small room but has a warm inviting atmosphere "+
      "with tapestries and paintings covering the walls.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 

    add_exit("board", "north");
    add_exit("library", "west");
    add_exit("train", "northwest");
    add_exit("post", "east");
    set_no_exit_msg(get_all_no_exits(({"nw","n","w","e"})),
    "There is a wall blocking your path.\n");
      
}

/*
 * Function name: start()
 * Description  : Lets guildmembers set this as default start.
 */
int
start(string str)
{
    if (str != "here") 
    {
    notify_fail("Start here?\n");
    return 0;
    }

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
    write("You are not a member of "+ GUILD_NAME + "!\n");
    return 1;
    }

    if (this_player()->set_default_start_location(STARTLOC))
    {
    write("Ok.\n");
    }
    else
    {
    write("Sorry, some problem prevents you from starting here.\n");
    }

    return 1;
}

/*
 * Function name: init()
 * Description  : initializes the commands.
 */
void
init()
{
    ::init();

    add_action(start, "start");
}
