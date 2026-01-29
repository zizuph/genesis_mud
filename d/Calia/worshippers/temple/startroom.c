

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/worshippers/specials/worshipper.h"
#include "defs.h"

int
is_worship(object living)
{
    return living->query_guild_name_lay() == GUILD_NAME;
}


void
create_room()
{
    set_short("Elemental Worshippers of Calia startroom");
    set_long("This chamber is ornately decorated with many "+
        "tapestries, paintings and pictures on the walls, "+
        "and beautiful flowers and bushes planted around it. "+
        "There are many natural beds here made from wood, cloth, "+
        "and leaves. If you are a member "+
        "of this circle, you may <start here> if you wish. There "+
        "are three regular exits from this chamber, one west, one south, and "+
        "one east.\n");

    add_item(({"tapestry","tapestries"}),"There are several beautiful "+
        "tapestries hanging on the walls. They are made from the "+
        "finest cloths in the land. Each of the depicts a different "+
        "Elemental God or Goddess in a different location around "+
        "Calia.\n");
    add_item(({"painting","picture","pictures","paintings"}),"These paintings and pictures have been "+
        "painted by the finest artists in all of Calia, on the best "+
        "canvas in all of the lands. They show various members of "+
        "the circle consulting with each other, carving things into "+
        "their Elemental Tools, and many other scenes.\n");
    add_item(({"flower","flowers","bush","bushes","plant","plants"}),
        "The flowers, bushes and plants are very well tended to, "+
        "and add a peaceful nature to this room. Small traces of "+
        "sunlight filter in from the room onto them.\n");
    add_item(({"bed","beds","natural bed","natural beds"}),"The "+
        "beds look very comfortable for when you need to rest from "+
        "your travels within these realms. They are made from wood, "+
        "cloth and leaves, making them very soft.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_IS,1);

    add_prop(OBJ_S_WIZINFO,"This is the default start location for "+
        "the Elemental Worshippers of Calia guild.  If a member loses any of their "+
        "guild items, direct them to the library (west, northeast, north, west from "+
        "here), where they can learn how to get them back.\n");

    add_exit(WOR_TEMPLE+"post","west",0,1);
    add_exit(WOR_TEMPLE+"board","east",0,1);
    add_exit(WOR_TEMPLE+"medroom","south","@@check_banned",1);
}

int
check_banned()
{
    if (TP->query_skill(SS_PUNISHMENT) == 2)
    {
        write("A voice echoes through your mind: You have been banned from "+
            "training by the council. You may not enter the focus chamber.\n");
        return 1;
    }
    return 0;
}

int
start(string where)
{
    if (!is_worship(this_player()))
    {
        NF("You are not a member of this guild!\n");
            return 0;
    }
    if (where != "here")
    {
        NF("Start where?  Here?\n");
        return 0;
    }
    this_player()->set_default_start_location("/d/Calia/worshippers/temple/startroom");
    write("The Elementals welcome you. You shall start here now.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action("start","start");
}
