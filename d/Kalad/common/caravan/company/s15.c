#include "../default.h"
inherit CVAN_ROOM;

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

void
create_cvan_room()
{
    add_prop(ROOM_NO_TIME_DESC, 1);

    set_short("Courtyard");
    set_long("You've reached a relatively secluded spot in the courtyard.\n"+
      "All around you are red rose bushes, with their roses blooming "+
      "profusely in the air. The cobblestones are a bit more "+
      "worn here then in the central courtyard. A path to the south leads "+
      "out of this spot.\n");

    add_item(({ "bushes" }), "The flowering plants seem to be in full "+
      "bloom, a wonderful smell emanates from them.\n");

    add_item(({ "path" }), "A small path winding its way past the many rose "+
      "bushes. Its paved in light grey cobbles.\n");

    add_exit(CVAN + "company/s16", "south");
}

void
do_sneeze()
{
    TP->command("$sneeze");
}

int
do_smell(string str)
{
    if(!str || str != "roses")
    {
	notify_fail("You can't smell '" + str + "'.\n");
	return 0;
    }
    write("You inhale the sweet fragrance of some roses.\n");
    say(QCTNAME(TP) + " smells some roses.\n");
    set_alarm(2.0, 0.0, do_sneeze);
    return 1;
}

void
init()
{
    ::init();
    add_action(do_smell, "smell");
    add_action(do_smell, "sniff");
}
