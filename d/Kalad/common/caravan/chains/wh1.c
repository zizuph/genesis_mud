#include "../default.h"
inherit CVAN_ROOM;

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Bedchamber");
    set_long("You've entered an opulent bedchamber. A huge bed lies in "+
      "the center of the room, taking up nearly all the space here. The "+
      "walls here have been colored a gaudy pink and even the floor has "+
      "been similarly decorated, with a dark purple rug covering it. A large "+
      "dresser lies beside the bed.\n");

    add_item(({ "bed" }), "An incredibly soft-looking bed lined with silken "+
      "pillows and a satin cover.\n");

    add_item(({ "walls" }), "They've been covered up with plaster and "+
      "painted over with a bright pink color.\n");

    add_item(({ "floor" }), "The floor is made out of wooden planks and is "+
      "covered by a dark purple rug.\n");

    add_item(({ "wooden planks", "planks" }), "They look fairly sturdy, and "+
      "capable of holding our weight.\n");

    add_item(({ "dark purple rug", "purple rug", "dark rug", "rug" }), "A "+
      "crudely woven rug made out of some fibers that make you itch!\n");

    add_item(({ "large dresser", "dresser" }), "A large mahogany dresser used "+
      "by whoever lives here to store clothes in.\n");

    add_exit(CVAN + "chains/wh", "west");

    clone_object(NPC + "whlady")->move_living("M", TO);
}

void
do_snore()
{
    TP->command("$yawn");
    TP->command("$snore");
}

int
do_sleep(string str)
{
    if(!str || str != "bed")
    {
	notify_fail("You can't sleep '" + str + "'.\n");
	return 0;
    }
    write("You lie down on the bed and feel very relaxed.\n");
    say(QCTNAME(TP) + " lies down on the huge bed.\n");
    set_alarm(2.0, 0.0, do_snore);
    return 1;
}

void
do_things()
{
    TP->command("$drop all coins");
    TP->command("$moan");
    TP->command("$groan");
    TP->command("$wiggle seductively");
    TP->command("$love lady");
    TP->command("$smile contentedly");
}

int
do_please(string str)
{
    if(!str || str != "lady")
    {
	notify_fail("You can't please '" + str + "'.\n");
	return 0;
    }
    write("You take the lady into your arms and begin doing the wild thing.\n");
    say(QCTNAME(TP) + " does the wild thing with the lady!\n");
    set_alarm(2.0, 0.0, do_things);
    return 1;
}

void
init()
{
    ::init();
    add_action(do_sleep, "sleep");
    add_action(do_please, "please");
}
