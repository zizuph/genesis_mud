#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#pragma save_binary

inherit "/std/room.c";

string gateway_source;

void
set_gateway(string str)
{
    gateway_source = str;
}

void
create_room()
{
    set_short("Within a swirling mass of mist");
    set_long("\n"+
        "   You find yourself floating in a mass of swirling black "+
        "and grey clouds. The mist is endless in all ways, and you "+
        "wonder how it is you keep from falling. Occasional flashes "+
        "of multi-colored lightning illuminate your surroundings, and "+
        "you vaguely see what appear to be twisted black structures "+
        "on a bleak landscape.\n"+
        "   Next to you floats two portals, one green, and one "+
        "black.\n\n");
    add_item("portal","Which portal do you want to examine?\n");
    add_item("portals","There are two, one green one and one black one.\n");
    add_item("black portal","Gazing into this portal, you see a lone "+
    "grim skull floating in its center.\n");
    add_item("green portal","Gazing into this portal, you see a red "+
    "square spinning slowly.\n");
    INSIDE;
}

int
do_enter(string str)
{
    NF("Enter what?\n");
    if(str == "black portal")
    {
        write("You float into the black portal.\n");
        say(QCTNAME(TP)+" floats into the black portal.\n");
        TP->move_living("M",KHIRAA_DIR(temple/rooms/t7));
        say(QCTNAME(TP)+" emerges from the mystical black portal.\n");
        return 1;
    }
    if(str == "green portal")
    {
        write("You float into the green portal.\n");
        say(QCTNAME(TP)+" floats into the green portal.\n");
        TP->move_living("M",gateway_source);
        say(QCTNAME(TP)+" emerges from the red portal.\n");
        return 1;
    }
    return 0;
}

void
init()
{
    ::init();
    add_action(do_enter,"enter");
}

void
shut_portal()
{
    int i;
    object *obs,groom;
    tell_room(TO,"Suddenly, the portals begins to shut, and you "+
    "quicky jump into the black portal before it closes.\n");
    obs = FILTER_LIVE(all_inventory(TO));
    for(i=0;i<sizeof(obs);i++)
    {
        obs[i]->move_living("M",KHIRAA_DIR(temple/rooms/t7));
        tell_room(E(obs[i]),QCTNAME(obs[i])+" emerges from the "+
        "mystical black portal.\n",obs[i]);
    }
    groom = find_object(KHIRAA_DIR(temple/rooms/t7));
    present("_gateway_",groom)->shut_portal();
}

