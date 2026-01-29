#include "local.h"
inherit ROOM_BASE;

public void
create_sea_room()
{
    set_special_short("the Mistlestraight channel between " +
        "the Elian Isles and the mainland of the Dairly Plains");

    ::create_sea_room();

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("the Mistlestraight channel");

    add_item(({"mistlestraight", "mistlestraits", "channel",
        "mistlestraight channel" }),
        "The Mistlestraights is the passage between the mainland " +
        "of the Dairly Plains to your west and the Elian Isles " +
        "to your east, allowing passage from the Blood Sea " +
        "of Istar to the Southern Courrain Ocean.\n"); 

    add_item(({"dairly plains", "plains", "west", "grasslands",
        "scrublands", "grasses", "copses", "woods"}),
        "To your west are the Dairly Plains, rolling grasslands " +
        "of verdant grasses broken by spare copses of woods and " +
        "scrublands.\n");

    add_item(({"elian isles", "isles", "east", "elian wilds",
        "island", "reef", "reefs" }),
        "To your east is the island of the Elian Wilds, " +
        "a thickly forested land rumoured to be the home of " +
        "a barbarian race of martial humans. This island is " +
        "surrounded by numerous reefs, and is impossible to " +
        "approach from the Mistlestraights.\n");

    add_item(({"water", "sea", "bloodsea", "blood sea"}), 
        "The water within the Blood Sea has "+
        "a strange and reddish colour. Rumour has it that the colour "+
        "is the result of the blood of many victims who lost their "+
        "lives during Krynn's most terrible hour, though it "+
        "could be the clay stirred up from the sea bottom by the "+
        "maelstrom.\n");

    add_std_exits();

    herbs = HERB_MASTER->query_herbs( ({ "nearshore", }) );
}

