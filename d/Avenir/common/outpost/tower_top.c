// file name: d/Avenir/common/outpost/tower_top.c
// creator(s):  Kazz    March '95
// purpose:     the "attic" of the tower, an escape room
//              for the banker/manager.
// note:        
// revisions:   Lilith, Apr 2022: for fortress update 

#include <composite.h>
#include "/d/Avenir/common/outpost/outpost.h"
inherit OUTPOST+ "fort_base";

#define SEE_DOWN OUTPOST + "tower_office"


private int
do_view(string str)
{
    if (!str)
	return 0;

    object ob = find_object(SEE_DOWN);

    if (!objectp(ob))
    {
	write("There is nothing to be seen.\n");
	return 1;
    }

    object *live, *dead;

    write("Putting your eye to the opening in the floor, you see:\n\n");
    write(ob->long(0));

    dead = all_inventory(ob);
    live = filter(dead, living);
    dead = filter(dead - live, not @ &->query_no_show());

    if (sizeof(dead) && strlen(str = SILENT_COMPOSITE_DEAD(dead)))
	write(break_string((capitalize(str) + "."), 76) + "\n");

    if (sizeof(live) && strlen(str = SILENT_COMPOSITE_LIVE(live)))
	write(break_string((capitalize(str) + "."), 76) + "\n");

    write("\n");
    return 1;
}

void
create_fort_room()
{
    set_short("a tiny cramped space");
    add_prop(ROOM_S_DARK_LONG, "A small, dark space with barely "+
        "enough room for you to huddle in. You notice some "+
        "light emanating from a hole in the floor beneath you. "+
        "It seems like you might be able to see something through "+
        "it.\n"); 	
    set_long("This cramped space appears to be a hidden room. "+
        "If you manage not to move or breathe too loudly you "+
        "might evade detection. Light emanates through a hole "+
        "nearby. You should probably see through the opening "+
        "to make sure it is safe to leave.\n" );

    add_exit(OUTPOST + "tower_office","down",0);
    add_exit(OUTPOST + "tower_office","slide", 0, 0, 1);
	  
    //  It is really dark in here.
    add_prop(ROOM_I_LIGHT, -10);
	
    // These are in the fort_base.c
    add_fort_room();

} 


public void
init(void)
{
    ::init();
    // load add_actions()
    add_action("do_view", "see");
    add_action("do_view", "peep");
    add_action("do_view", "squint");
	
} 

