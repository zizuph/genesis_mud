// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/s11.c
// creator(s):       unknown
// revisions:        Casca, 11/13/99
// purpose:          Connects to L2/add/t1.c
// note:             
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/dark/darkl2_base.c";

/* Include the local area defines, etc */
#include "/d/Avenir/common/dark/dark.h"  

/* Now create the room.  */
void
create_tunnel_room()
{
    set_short("Sharp turn");
    set_long("The natural passage turns sharply here, heading "+
        "north and northwest. Off to the east is tunnel carved into "+
        "natural wall. In the crook of the tunnel's bend sits a small "+
        "pool being fed by water dripping from a stalactite.\n");


    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_cmd_item(({"from pool","pool","water","the water"}),
        ({"drink","taste"}),
        "It is foul and brackish.\nYou feel slightly ill.\n");
    add_item(({"pool","water"}),"A shallow pool of dirty, brackish water.\n");
    add_item(({"stalactite"}),"A small stalactite hangs from the low "+
        "ceiling above the pool. The brackish nature of the water "+
        "has given it a dark and foul color.\n");
    add_tell("A drop of water falls from the stalactite and falls into the "+
        "pool below. The sound echos through the tunnel.\n");

    add_exit("s10","northwest");
    add_exit("add/t1","east"); 

  add_prop(OBJ_S_SEARCH_FUN, "search_me");

}
 
#include "/d/Avenir/union/lib/bits.h"
#define LIST ("/d/Avenir/union/list")

string search_me(object player, string str)
{
    if (player->query_prop("found_it_yet") ||
	player->test_bit("Avenir", GUILD_GROUP, QUEST_BIT) ||
	!LIST->query_accepted(player->query_real_name()))
    {
	return "";
    }

    if (!parse_command(str, ({}), "[in] [the] 'pool' / 'water'"))
	return "";
 
    player->add_prop("found_it_yet", 1);
    object ob = clone_object(UNION+"obj/quest/shard");
    ob->move(player, 1);

    return "You find "+LANG_ASHORT(ob)+" in the pool.\n";
}
