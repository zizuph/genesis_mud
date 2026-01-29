/* A jetty onto the river Sha. ~mucalytic/hills/locations/jetty1 */

inherit "/std/room";

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

void create_room()
{
    set_short("A jetty on the south bank of the river Sha in the foothills");
    set_long("You find yourself on a wooden jetty situated on the south "+
        "bank of the river Sha, which flows gently westwards. Paths lead "+
        "both east and west into the hills directly to your south. You "+
        "notice a sign posted into the ground nearby.\n");

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT, 50 + random(50));

    add_exit(LOCATIONS + "path25", "west", "@@ch_dir1@@", 2);
    add_exit(LOCATIONS + "path29", "east", "@@ch_dir2@@", 3);

    add_item("ground", "You notice nothing of interest.\n");

    add_item("sign", "The sign is made from the same type of wood as the "+
        "jetty and has words written on it in red paint.\n");

    add_item(({"river", "river sha"}), "The river is a bluey-green colour "+
        "and is very wide from this to the north bank. It flows calmly "+
        "from the east, westwards.\n");

    add_item("hills", "The foot-hills to the south roll unremittantly and "+
        "ceaslessly, dominating their surrounding terrain and obscuring "+
        "almost everything but the sky from your view.\n");

    add_item("paths", "The paths are made of a scattering of gravelly rock "+
        "and weeds. It runs in a twisty confusing mode and seems to meander "+
        "in the furthest possible route to nowhere at all.\n");

    add_item(({"jetty", "wooden jetty"}), "The jetty is made from a dark, "+
        "solid-looking wooden and is about 10 metres long. It extrends "+
        "from the south bank nearby, out over the river to allow boats to "+
        "berth here.\n");
}

void init()
{
    ::init();

    add_action("do_read", "read");
}

void ch_dir1()
{
    write("The path slopes upwards and becomes more overgrown. You follow "+
        "it past some obstructing rocks and turn south.\n\n");
}

void ch_dir2()
{
    write("The path slopes upwards and becomes more overgrown. You follow "+
        "it round a small pool of water and turn south.\n\n");
}

int do_read(string what)
{
    if(!strlen(what))
        return 0;

    if(what == "sign")
    {
        write("The sign reads:\n\nThere will eventually be a ferry service "+
            "running from here to the north bank. This will be a long time "+
            "in coming though, since other areas of more import are still "+
            "under development.\n\nKind regards - Sir Mucalytic.\n");

        if(!TP->query_invis())
            say(QCTNAME(TP)+" reads the writing on the sign above the arch.\n");
        return 1;
    }
    else
        write("Read what? IE: 'read sign'.\n");
    return 1;
}
