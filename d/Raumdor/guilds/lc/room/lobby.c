/*********************************************************************
 * - lobby.c                                                       - *
 * - room in Ladies Club                                           - *
 * - Created by Damaris@Genesis 5/2003                             - *
 *********************************************************************/
#pragma no_clone
#pragma no_inherit
#pragma strict_types

#include "/d/Raumdor/defs.h"
#include "../guild.h"

inherit CLUB;

object table;

int
chk(string id, string fname)
{
    if (!objectp(present(id,table)))
    {
      (clone_object(GUILD_DIR+fname))->move(table);
       return 1;
    }
    return 0;
}
 
void
check_table()
{
    if ((chk("roses","roses"))<0)
      tell_room(TO,"A young female rushes in, places something on the "+
        "table and rushes back out.\n");
}
 
public void
reset_room()
{
    check_table();
}
public void
create_guild_room()
{
    set_short("A spacious lobby");
    set_long("\n   This is a spacious lobby in the Lady's Club. The room "+
      "is slightly oval shaped and it leads in several directions. "+
      "There is a large oval rug that has been placed on the tiled "+
      "floor in the center of the room. There is also a large oval "+
      "table placed in the center as well. There are large and small "+
      "paintings along the walls with golden lanterns firmly attached "+
      "next to them.\n");
    add_item(({"room", "lobby", "area"}), query_long);
    add_item(({"floor", "flooring", "ground"}),
      "The flooring is made from a cream tile with small intricately "+
      "stained red patterns. A large oval rug has been place upon it.\n");
    add_item(({"rug"}),
      "The rug has been died a soft ruby red colour and a oval table "+
      "is sitting on it.\n");
    add_item(({"candles", "scented candles", "candle", "scented candle"}),
      "There are scented candles resting on some small tables.\n");
    add_item(({"table", "tables", "small table", "small tables"}),
      "There are small tables scattered in various places against the "+
      "walls, but done in a very orderly fashion.\n");
    add_item(({"counter", "large counter"}),
      "There is a large counter situated close to the eastern wall and "+
      "there is a stairway leading downward behind it.\n");
    add_item(({"stairs", "starcase", "stairway"}),
      "There is a a highly polished stairway leading downward from just "+
      "behind the counter.\n");
    add_item(({"east"}),
      "There is a doorway in that direction that leads to the sitting room.\n");
    add_item(({"south"}),
      "There is a doorway in that direction that leads to the board area.\n");
    add_item(({"southeast"}),
      "There is a doorway in that direction that leads to the postal area.\n");
    add_item(({"down"}),
      "That direction leads back to the guest areas.\n");
    add_item(({"up"}),
      "That direction leads up to the private sleeping chambers.\n");
    add_item(({"west", "north","southwest","northwest", "northeast"}),
      "There is a wall in that direction.\n");
    add_item(({"painting", "paintings"}),
      "There are different sized paintings on the walls. Each are quite "+
      "elegant in nature, depicting various ladies in different "+
      "settings.\n");
    add_prop(ROOM_I_LIGHT, 2);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
    add_exit("board", "south");
    add_exit("sit", "east");
    add_exit("post", "southeast");
    add_exit("join", "down");
    table=clone_object(GUILD_DIR + "table");
    table->move(TO);
    reset_room();  
   
}
int
do_smell(string str)
{
    if(str == "")
    return 0;

    notify_fail("Smell what?\n");
    if(str != "flower" &&  str != "the flower" &&
       str != "flowers" && str != "the flowers" &&
       str != "rose" &&    str != "the rose" &&
       str != "roses" &&   str != "the roses")
    return 0;

    write("You lean over and smell the flowers and "+
      "inhale deeply. You close your eyes as you are briefly overcome "+
      "by the strong scent.\n");
    say(QCTNAME(TP)+" leans over and smells the flowers and inhales "+
      "deeply, closing "+HIS(TP)+" eyes briefly.\n");

    return 1;
}
void
init()
{
    ::init();

    add_action("do_smell", "smell");
    add_action("do_smell", "sniff");
}
