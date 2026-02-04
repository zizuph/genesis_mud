/*
 * Upstairs hallway in the vampire manor
 * Louie 2006
 */ 
#pragma strict_types
#include "defs.h"

inherit ROOM_DIR + "vamp_room";

#include <stdproperties.h>
#include <macros.h>

#define ENTRY_ROOM (ROOM_DIR+"entry")

//proto
int lit = 0;
string chandelier_desc();
int do_extinguish(string str);
int do_light(string str);

void
create_room()
{
    ::create_room();
    set_short("hallway");
    set_long("You stand in a hallway at the top of the stairs "+
        "above the entry hall of the manor.  "+
        "The edge of the hallway has a large banister with "+
        "elaborate carvings running along the edge of a balcony "+
        "overlooking the entry room below.  "+
        "Past the banister, hanging slightly above where you stand, "+
        "an enormous crystal chandelier hangs down.  "+
        "Against the north wall is a shelf containing tools "+
        "necessary to light and extinguish the dozens of candles "+
        "that make up the chandelier.  "+
        "\n");

    add_exit("entry.c", "down");
    add_exit("narrowhall.c", "north");
    add_exit("masterbedroom.c", "west");
    add_exit("childbedroom.c", "northwest");

    add_item(({"chandelier","enormous chandelier","crystal chandelier",
        "enormous crystal chandelier","candles","candle"}),
        "@@chandelier_desc@@");

    add_item(({"hall","large hall","entry hall","large entry hall",
        "down"}),
        "Below you is the large entry hall of the manor.\n");

    add_item(({"west","master bedroom"}),
        "To the west appears to be the master bedroom.\n");

    add_item(({"northwest","small room","small bedroom"}),
        "To the northwest appears to be a small bedroom.\n");

    add_item(({"north","hallway"}),
        "To the north is a long, narrow hallway.\n");

    add_item(({"balcony"}),
        "The balcony extends far enough that it would be possible "+
        "to reach the chandelier with the proper tools.\n");

    add_item(({"banister","large banister","wooden banister",
        "large wooden banister","stairs","stairway"}),
        "The wooden banister provides a handgrip along the stairs "+
        "and the balcony here.  It is covered "+
        "in elaborate carvings.\n");

    add_item(({"carvings","elaborate carvings","images"}),
        "The carvings along the banister appear to be images "+
        "of faces and people.  "+
        "Disturbingly, it appears that most of the carvings are "+
        "of people either sleeping or screaming.\n");

    add_item(({"tools","shelf","north wall"}),
        "The shelf along the north wall contains various tools "+
        "for lighting and extinguishing the chandelier.  "+
        "You see flint, tinder, as well as a long handled "+
        "punk on a stick.  "+
        "\n");

    add_item(({"flint"}),
        "The flint on the shelf is used to strike a spark.\n");
    
    add_item(({"tinder"}),
        "The tinder is used to catch the spark created by the flint.\n");

    add_item(({"punk","long punk","punk on a stick",
        "long punk on a stick","long handled punk",
        "long handled punk on a stick","long handled punk on stick"}),
        "The long handled punk has a slow-burning wick on one side, "+
        "and a bell-shaped brass ornament on the other.  "+
        "The wick is lit by the tender, and can be used to light the "+
        "chandelier.  "+
        "When turned over, the bell-shaped brass can be used to snuff "+
        "out the candles.  "+
        "\n");    
}

string
chandelier_desc()
{
    string s = "The crystal chandelier is suspended past the edge of the "+
        "balcony.  "+
        "It is simply enormous, holding dozens of candles. ";

    if (lit) {
        s += "The chandlier is currently lit, "+
            "flooding the area with light.  ";
    } else {
        s += "The chandelier is currently dark.  ";
    }

    return s+"\n";
}

void 
init()
{    
    ::init();
    add_action(do_light, "light");
    add_action(do_extinguish, "extinguish");
}

int do_extinguish(string str)
{
    if (!strlen(str))
    {
        notify_fail("Extinguish the chandelier?\n");
        return 0;
    }

    if (str != "chandelier"
        && str != "the chandelier")
    {
        notify_fail("Extinguish the chandelier?\n");
        return 0;
    }

    if (!lit)
    {
        notify_fail("The chandelier is not lit.\n");
        return 0;
    }

    object tp = this_player();

    write("You use the bell-shaped brass ornament of the long handled "+
        "punk to slowly snuff the flame from every candle "+
        "in the chandelier, leaving it dark.\n");
    say(QTNAME(tp)+" uses the bell-shaped brass ornament of the long "+
        "handled punk to slowly snuff the flame from every candle "+
        "in the chandelier, leaving it dark.\n");

    tell_room(ENTRY_ROOM, "The chandelier slowly goes out as its candles "+
        "are extinguished by someone on the balcony.\n");

    add_prop(ROOM_I_LIGHT,
        query_prop(ROOM_I_LIGHT) - 10);

    ENTRY_ROOM->add_prop(ROOM_I_LIGHT,
        ENTRY_ROOM->query_prop(ROOM_I_LIGHT) - 10);

    lit = 0;

    return 1;

}
int do_light(string str) 
{
    if (!strlen(str))
    {
        notify_fail("Light the chandelier?\n");
        return 0;
    }

    if (str != "chandelier"
        && str != "the chandelier")
    {
        notify_fail("Light the chandelier?\n");
        return 0;
    }
    
    if (lit)
    {
        notify_fail("The chandelier is already lit.\n");
        return 0;
    }

    object tp = this_player();

    write("You take the flint and create a tiny spark, catching "+
        "it with the tinder and igniting the end of the long handled "+
        "punk.  "+
        "Stretching over the balcony, you slowly light each candle "+
        "of the chandelier.\n");
    say(QTNAME(tp)+" takes the flint and creates a tiny spark, "+
        "catching it with the tinder and igniting the end of the long "+
        "handled punk.  "+
        "Stretching over the balcony, "+tp->query_pronoun()+" slowly "+
        "lights each candle of the chandelier.  \n");

    tell_room(ENTRY_ROOM, "The chandelier slowly begins to fill the "+
        "area with light as the candles are lit by someone "+
        "on the balcony.\n");

    add_prop(ROOM_I_LIGHT,
        query_prop(ROOM_I_LIGHT) + 10);

    ENTRY_ROOM->add_prop(ROOM_I_LIGHT,
        ENTRY_ROOM->query_prop(ROOM_I_LIGHT) + 10);

    lit = 1;

    return 1;
}

int query_lit()
{
    return lit;
}
