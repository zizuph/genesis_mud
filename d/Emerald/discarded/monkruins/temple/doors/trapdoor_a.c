/* temple/doors/trapdoor_a.c is cloned by temple/hall.c */
inherit "/std/door";
 
#include "/d/Emerald/defs.h"
 
void
create_door()
{
    set_door_id("trapdoor");
    set_pass_command( ({ "d", "down" }) );
    set_door_name( ({ "altar" }) );
    set_open_desc("A finely ornamented altar, tipped to one side revealing an opening leading downwards.\n");
    set_closed_desc("A finely ornamented altar stands before you.\n");
    set_door_desc(break_string("It is a finely ornamented altar. " +
               "It appears like it to have had extensive use. "+
               "It looks very heavy and impossible to move.\n",76));
    set_open_command("push");
    set_close_command("pull");
    set_open_mess( ({ "tips the altar against the wall, revealing an opening.\n",
		      "The trapdoor opens.\n" }) );
    set_close_mess( ({ "pulls the altar back in position, covering the opening.\n",
		       "The trapdoor closes.\n" }) );
    set_other_room(TEMPLE_DIR + "tunnel1");
    set_open(0);
}
 
void
init()
{
    ::init();
    add_action("try_move", "move");
}
 
int
try_move(string arg)
{
    notify_fail("Move what?\n");
    if (arg != "altar")
	return 0;
    write("Do you want to push or pull on the altar?\n");
    return 1;
}
