// file name:		~Avenir/common/dark/l3/n8.c
// creator(s):
// revision history:
//			Added A piece of the source here for the impquest.
// 			       -Ilyian, May 13 1995
//			Jan 96: Made the source-containing-place to have
//				unique number to properly use the
//				souce-distributing daemon.
//					-=Denis
// note:		Contains piece of source - part of impquest to
//			players.
// bug(s);
// to-do:


# include "l3_defs.h"
# include "/d/Avenir/common/dark/dark.h"

inherit "/std/room";
inherit SOURCE_CHECKER;

void
create_room()
{
  set_short("dead end");
  
  set_long(
"This natural tunnel comes to an inexplicable dead end here. Your "+
"footing is unsteady on the uneven rock, and weird shadows play "+
"along the rocks. There is a small hole at the dead end through "+
"which an intensely strong and moist wind is blowing, making "+
"everything in the cavern wet and cold.\n");

    add_item(({"wall","walls"}),
"The walls of this tunnel are simply the natural rock formation. "+
"They glisten with moisture and create strange shadows all around.\n");

    add_item( ({"hole","gap"}),
             "@@exa_fun");

    add_item("wind",
"You will never know from where this mysterious wind blows. It is "+
"cold and wet.\n");

    add_exit("/d/Avenir/common/dark/l3/n7","southwest",0);

    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_I_INSIDE,1);
    can_contain_source=1;
}

string exa_fun()
{
    if(find_source(TP,3))
    return
"The hole is about a handwidth in diameter, and through it you can "+
"see nothing but darkness. A powerful wind is coming in through it, "+
"making everything in the area damp and cold. At the edge of the "+
"hole you find a small shard of crystal, which you take.\n";

    else
    return
"The hole is about a handwidth in diameter, and through it you can "+
"see nothing but darkness. A powerful wind is coming in through it, "+
"making everything in the area damp and cold.\n";
}
