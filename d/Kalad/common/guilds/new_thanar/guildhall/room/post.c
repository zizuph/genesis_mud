/**********************************************************************
 * - post.c                                                         - *
 * - Postal service within the guild                                - *
 * - Created by Damaris@Genesis 3/2004                              - *
 * - New Standrad file for new area for guild. Typos fixed.         - *
 * - by Mirandus@Genesis 01/2018                                    - *
 **********************************************************************/

#pragma strict_types
#pragma save_binary
#include "../guild.h"

inherit THANAR_STD_ROOM; 
inherit "/d/Genesis/lib/post";

#include <macros.h> /* For the Q macros in messages.. */
#include <stdproperties.h> /* for room props */

/*
 * Function name: create_std_thanar()
 * Description  : Creates the room from standard room file
 */
public void
create_std_thanar()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 2);

    set_short("Postal office");
    set_long("This is a postal office. The atmosphere "+
      "here is very warm and inviting. Upon the walls there are highly "+
      "polished lanterns and paintings of distant lands. A large counter "+
      "rests in the corner with very pleasant looking postal worker "+
      "sorting mail. She is elven and quite busy with her tasks. It "+
      "would be wise to let her continue her work so please 'examine "+
      "mail reader' for further information.\n");
    add_item(({"room", "area"}), query_long);
    add_item(({"painting", "paintings"}),
      "You look closer at the posters that adorn the walls here.\n"+
      "They depict far off lands you have yet to see.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);  
    add_exit("start","west");
    add_exit("hall2", "south");
    set_no_exit_msg(get_all_no_exits(({"w","south"})),
    "There is a wall blocking your path.\n");
      

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
    write("\nThere is"+ new +" mail for you in the Thanarian post office.\n");
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
