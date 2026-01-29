/* The room for rent above the boot maker shop in altaruk */

#include "../defs.h"
inherit "/d/Cirath/std/room.c";

void
create_room()
{
    set_short("a room above the bootmakers shop in Altaruk");
    set_long("The room looks surprisingly clean. A window gives you a" +
        " view of the street below. A bunk stands at the far end of the" +
        " room. On the wall a tapestry is hung. A chest for putting your" +
        " stuff in stands next to the bunk.\n");

    add_item(({"window","street"}), "You look out the window at the street"+
             " below. Clothier street you believe.\n");

    add_item("tapestry", "The tapestry depicts a scene of a young"+
             " beauty sleeping under some sort of fruit tree. There is" +
             " a sign in the corner. It means its safe to 'start here'.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit("rentstairs.c", "out", 0, 1);
}

init()
{
    ::init();
    add_action("start","start");
}

int
start(string s)
{
    object ob;
    if(!(ob=present("_altaruk_room_key_",this_player())))
    {
        write("How do you propose to do that without a room key?\n");
        return 1;
    }
    notify_fail("Start where?\n");
    if(s!="here") return 0;
    ob->remove_object();
    this_player()->set_temp_start_location(ALT_HOU + "rentroom");
    write("You lie down in the bunk thinking about your day and what" +
        " your doing in a town like this. As your mind settle you" +
        " finaly fall to sleep.\n");
    this_player()->remove_object();
    return 1;
}
