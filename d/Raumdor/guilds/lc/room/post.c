/*********************************************************************
 * - post.c                                                        - *
 * - Postal area for Ladies Club.                                  - *
 * - Created by Damaris@Genesis 5/2003                             - *
 *********************************************************************/

#pragma strict_types
#pragma save_binary

#include <macros.h> /* For the Q macros in messages.. */
#include <stdproperties.h>  
#include "../guild.h"

inherit CLUB;
inherit "/d/Genesis/lib/post";

/*
 * Function name:   create_guild_room
 * Description:     define the basics of the room
 */
public void
create_guild_room()
{

    set_short("A postal area");
    set_long("This is a small postal area that the club owners "+
      "have added to make the members feel relaxed about sending "+
      "and receiving their correspondence. There are a few "+
      "parchments laid upon a small counter and postal workers "+
      "are busy sorting mail. A polite lady would 'examine "+
      "mail reader' rather than disturb the postal workers.\n");
    add_item(({"room", "area", "post office", "postal area"}), query_long);
    add_item(({"parchmant", "parchments"}),
      "There are few clean parchments laid upon upon a small "+
      "counter.\n");
    add_item(({"painting", "paintings"}),
      "The paintings that adorn the walls here are of far away lands.\n");
    add_item(({"wall", "walls"}),
      "The walls are a light wood and have a few lanterns "+
      "firmly attatched along with a few paintings.\n");
    add_item(({"postal worker", "postal workers", "worker", "workers"}),
      "The postal workers appear to be quite busy as they sort "+
      "the mail.\n");
    add_item(({"counter", "large counter"}),
      "A small counter rests in the corner with postal workers behind it.\n");
    add_item(({"north","south", "east", "northeast", "northwest", "southeast"}),
     "There is a wall in that direction.\n");
    add_item(({"west"}),
      "There is a doorway in that direction that leads to the board area.\n");
     add_item(({"southwest"}),
      "There is a doorway in that direction that leads back to the "+
      "lobby area.\n");
    add_item(({"up"}),
      "There is a ceiling in that direction.\n");
    add_exit("lobby", "northwest");
    add_exit("board","west");
   

}

/*
 * Function name:   leave_inv
 * Description:     remove mailreader from players exiting the room
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}

public void
mail_message(string new)
{
    write("\nThere is"+ new +" mail for you in the Ladies Club post office.\n");
}

/*
 * Function name:   init
 * Description:     add a mailreader to players who enter the room
 */
public void
init()
{
    ::init();
    post_init();

}
