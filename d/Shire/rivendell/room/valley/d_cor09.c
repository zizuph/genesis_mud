/*
 * Downstairs corridor
 * By Finwe, February 1998
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit HOUSE_IN_BASE;
 
void
create_house_room()
{
    set_short("A downstairs corridor");
    set_long("The corridor ends here. The atmosphere is serene " +
        "and quiet, reflecting the mood from the room south of " +
        "here. On the east wall, giant windows fill the " +
        "corridor with light. The north wall is decorated with " +
        "a large mural.\n");
 
    add_item(({"mural", "north wall"}),
        "On the wall, you see a mural of a great city built " +
        "upon a great hill. Fair houses surround the hill, and " +
        "in the midst of the houses stands a great tower.\n");
    add_item(({"pillars", "square pillars", "square wooden pillars"}),
        "The pillars are carved from thick trees. They are squared " +
        "and are set into the walls. The pillars are expertly " +
        "decorated with carved leaves.\n");
    add_item(({"houses", "fair houses"}),
        "The fair houses are painted on the hill, like white jewels glistening in the light. They surround the tower in a dizzying array of order and beauty.\n");
    add_item(({"city", "great city", "fair city"}),
        "@@city_descr@@\n");
    add_item(({"tuna", "hill", "grass covered hill"}),
        "@@descr_tuna@@\n");
    add_item(({"valinor", "blessed realm"}),
        "@@descr_blessed@@\n");
    add_item(({"tirion"}),
        "@@descr_tirion@@\n");
    add_item(({"pelori", "pelori mountains"}),
        "@@descr_pelori@@\n");
    add_item(({"mindon eldalieva", "tower of ingwe", "tower", 
            "lofty tower"}),
        "@@descr_mindon@@\n");
    add_item(({"galathilion", "white tree"}),
        "@@descr_galathilion@@\n");
    add_item(({"fountains", "beautiful fountains"}),
        "They are painted with detail in the mural. Glorious water sprays forth from the fountains and glisten in the light.\n");
    add_item(({"crystal staircases", "staircases"}),
        "The staircases are painted with detail. They appear to be made from crustal and surround the city and towers.\n");
    add_item(({"walls", "white walls"}),
        "The white walls sparkle in the light of the mural. They are tall and surround the city and make up the houses that are on the hill..\n");
 
    add_exit(VALLEY_DIR + "post", "south");
    add_exit(VALLEY_DIR + "d_cor08", "west");
}
// Descriptions of various items in the mural. 
// The descriptions vary based on the race of the player. Noldor,
// will naturally see all descriptions as the mural depicts their
// homeland. Regular elves won't as they haven't been there, though 
// some players may choose to differ. So sad, to bad. ;)

string city_descr()
{

    if(TP->query_guild_name_race() == NOLDOR_ELF)
         return "The fair city of Tirion rises from the hill, Tuna in the Blessed Realms. It sparkles in the light of Elbereth with a large tower rising from its midst with a large white tree at the base of the tower";
    else
        return "You see a breathtakingly beautiful city on top of a hill somewhere.";
}
 
string descr_tuna()
{

    if(TP->query_guild_name_race() == NOLDOR_ELF)
         return "It is a emerald green, grass covered hill in the Blessed Realm. Its western side was once blessed by the light of the Two Trees, but now that is no more, while the eastern side faces the Pelori. The fair city of Tirion crowns the hill, like a precious jewel of the Firstborn.";
    else 
        return "It is a grass covered hill. A fair city rises from the hill with a lofty tower rising from the midst of the city.";
}

string descr_tirion()
{
    if(TP->query_guild_name_race() == NOLDOR_ELF)
         return "The main city of Eldamar, it rises from the top of Tuna, and is glorious to behold. The crystal staircases, the white walls, the beautiful fountains, are all captured with exquisite detail. The great tower, Mindon Eldalieva, rises from the center of the city. At the base of the tower grows Galathilion.";
    else 
        return "The beautiful city is painted with great detail in the mural. It shines on the hill with a great tower rising from its center. A white tree grows at the base of the tower.";
}

string descr_blessed()
{

    if(TP->query_guild_name_race() == NOLDOR_ELF)
         return "The Blessed Realm, or Valinor, is depicted as full of light, beauty, and joy. In the center rises Tuna and crowned with Tirion. The beauty of the land is so overwhelming that it almost makes your heart ache to return to its fair shores and reside there again.";
    else 
        return "You fail to recall what that is.";
}


string descr_galathilion()
{

    if(TP->query_guild_name_race() == NOLDOR_ELF)
         return "The Galathilion is the white tree that grows at the base of the Tower of Ingwe. Made by Yavanna, the tree is breath-taking and perfect. The bark is silver and smooth with green and silver leaves but doesn't shine.";
    else 
        return "It is a beautiful white tree with green leaves growing at the base of the tower.";
}

string descr_mindon()
{

    if(TP->query_guild_name_race() == NOLDOR_ELF)
         return "The Tower of Ingwe, also known as Mindon Eldalieva, rises above Tirion. The tower is silver and very lofty. The top of the tower is crowned with a silver lamp that shines a perfect light into Eldamar. At the base of the tower is the White Tree, also known as Galathilion.";
    else 
        return "It is a beautiful white tower that rises above the city. A perfect white tree grows at the base of the tower.";
}

string descr_pelori()
{

    if(TP->query_guild_name_race() == NOLDOR_ELF)
         return "The Pelori are painted with exquiste detail. The mountain range runs along the eastern side of the mural.";
    else 
        return "You fail to recall what that is.";
}
