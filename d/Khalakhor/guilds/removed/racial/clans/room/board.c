/* File         : /d/Khalakhor/guilds/racial/clans/room/board.c
 * Creator      : Tomas@Genesis
 * Copyright:   : Bryan D.
 * Date         : March, 13 2001         
 * Purpose      : Board room to the default Clans of Khalakhor Guildhome
 * Related Files: /
 * Comments     : This is the Board room to the default Clansmen guildhome.
 * Modifications: 
 */
#include "../guild.h"
#include <stdproperties.h>
inherit GUILD_ROOM;
#define BOARD_DIR "/d/Khalakhor/guilds/racial/clans/log/board_data"

public void
create_guild_room()
{
    object bb;
    set_short("" + GUILD_NAME + " board room");
    set_long("This is the " + GUILD_NAME + " board room. "+
      "A large cork bulletin board has been nailed securely " +
      "to the wall before you.\n");
      
     add_cmd_item(({"board"}),(({"get","take","burn","climb"})),
         "You fail to do so and should be ashamed for even trying.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    add_exit("hall", "north");
    add_exit("c_board", "up");


    setuid();
    seteuid(getuid());
    bb = clone_object("/std/board");
    bb->set_board_name(BOARD_DIR);
    bb->set_num_notes(30);
    bb->set_silent(0);
    bb->set_show_lvl(0);
    bb->move(this_object(), 1);
}

