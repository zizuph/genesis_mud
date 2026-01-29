#pragma strict_types

inherit "/d/Gondor/common/room";
inherit "/d/Gondor/pelargir/city_items.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define MIN_STR		15
#define SEWER_ROOM	(PELAR_DIR + "sewers/grate")

void
create_room()
{
    set_short("on an east-west road");
    set_long(BSN("This is the middle of a long finger of land reaching "
      + "out into the immense river Anduin. At the end of the stretch to "
      + "the east the lighthouse stands proud, and to the west, the "
      + "peninsula connects to the mainland and the city of Pelargir. "
      + "On the road, there is a metal grating."));
    add_item(({"road", "ground", }), BSN(
        "The road is ending in front of the lighthouse at the end of "
      + "the peninsula not far east of here. In the opposite direction "
      + "it is leading back to the main street. A metal grating is "
      + "covering a hole that is probably leading down into the sewers."));
    add_item("lighthouse",BSN("The lighthouse of Pelargir "+
       "looms just to the east of here and seems quite imposing."));
    add_item(({"river", "river anduin","anduin river","anduin"}),BSN(
       "From this vantage you have a beautiful view of the river. "+
       "To the north the Anduin seems to march inexorably towards you "+
       "as it flows into and around the stretch of rock you stand upon. "+
       "To the south the rock provides a shelter of sorts from the river's "+
       "current, letting the ships dock peacefully at Pelargir."));
    add_item(({"hole", "opening", "grate", "grating", "metal grating", }),
        VBFC_ME("exa_grating"));
    add_towers();
    add_admiral("harbour");
    add_exit(PELAR_DIR + "street/nroad4","west",0);
    add_exit(PELAR_DIR + "street/nroad6","east",0);

    FIX_EUID
    SEWER_ROOM->load_me();
    SEWER_ROOM->reset_grating();
}

string
exa_grating()
{
    int     open;
    string  ld = "The opening is probably leading down into the sewers, "
               + "taking up the rain water to prevent a flooding of the "
               + "street.";

    open = SEWER_ROOM->query_open();

    if (open)
        ld += " The metal grating covering the hole is rusty and broken, "
            + "so it cannot stop anyone from entering the sewers anymore.";
    else
        ld += " An old rusty metal grating is covering the hole, preventing "
            + "people from falling down into the sewers.";
    
    return BSN(ld);
}

int
open_grate(string str)
{
    int     open;
    string  vb = query_verb();

    SEWER_ROOM->load_me();
    open = SEWER_ROOM->query_open();

    NFN(CAP(vb) + " what?");
    if (!strlen(str) || (str != "grate" && str != "grating" &&
        str != "metal grating"))
        return 0;

    if (open)
    {
        NFN("The grating is broken and does not block the entrance into the "
          + "sewers anymore.");
        return 0;
    }

    if (TP->query_stat(SS_STR) < MIN_STR)
    {
        write("You try to "+vb+" the rusty grating, but you are too weak.\n");
        say(QCTNAME(TP)+" tries to "+vb+" the rusty grating, but fails.\n");
        return 1;
    }
    write("You pull at the rusty grating, and without much effort you manage "
      + "to break it.\n"
      + "The way leading into the sewers is open now.\n");
    say(QCTNAME(TP)+" pulls at the rusty grating and breaks it.\n"
      + "The way leading into the sewers is open now.\n");

    add_exit(PELAR_DIR + "sewers/grate", "down", 0, 2);
    SEWER_ROOM->set_open();
    return 1;

}

void
init()
{
    ::init();

    add_action(open_grate, "break");
    add_action(open_grate, "open");
}

void
reset_room()
{
    SEWER_ROOM->reset_grating();
    remove_exit("down");
}

