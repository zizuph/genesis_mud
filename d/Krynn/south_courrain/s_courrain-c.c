#include "local.h"
inherit ROOM_BASE;

public void
create_sea_room()
{
    ::create_sea_room();

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("off the coastline of the Goodlund peninsula");

    add_item(({"coastline", "peninsula", "goodlund peninsula",
        "goodlund"}),
        "To your south you make out the coastline of Goodlund, " +
        "a land of lush forests and verdant fields of green " +
        "grass and plentiful wildlife, largely due to the short " +
        "winters and mild summers driven by the warm moist air " +
        "coming from the Blood Sea's maelstrom.\n");
    add_item(({"water", "sea", "blood sea", "bloodsea"}), 
        "The water within the Bloodsea has a strange and reddish " +
        "colour. Rumour has it that the colour is the result of " +
        "the blood of many victims who lost their lives during " +
        "Krynn's most terrible hour, though it "+
        "could be the clay stirred up from the sea bottom by the "+
        "maelstrom.\n");

    add_std_exits();

    herbs = HERB_MASTER->query_herbs( ({ "nearshore", }) );
}

