/*
 * Kalaman Link from the Plains.
 *
 * 
 * 2008-03-26 
 * Lunatari added a sign of races not allowed.
 * Lunatari changed how the races are blocked using race_name.
 * 2008-03-31
 * Lunatari added ogres and hobgoblins to blocking.
 * Will however soon block it inside Kalaman (gate.c) using the
 * more appropriate method by letting a gatemaster block.
 */
#include "local.h"
inherit TDIR+"eplain_base";

public void
create_eplains_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("Before the city gates of Kalaman");
    set_long(
        "You can enter the city through the gates by going southeast. " +
        "Northwest, the road will take you towards the far away " +
        "city of Solanthus. North, you can see the Vingaard River, " +
        "while the massive city walls of Kalaman block your view to " +
        "the east. In the distance to the south, you can see mountains " +
        "rising up into the sky, while the west and southwest are " +
        "dominated by the green of bushes and the occasional tree " +
        "making up the Plains of Solamnia. To the southwest wagon " +
        "tracks leave the road and pass through a wooden palisade " +
        "that surrounds a wooden structure. A sign has been placed " +
        "here.\n");
    add_item(({"road", "stone road"}),
        "The road is a typical stone road, very dusty and dirty.\n");
    add_item(({"city", "gate", "gates", "wall", "city walls", "city gate",
        "city gates", "city wall", "walls", "kalaman"}),
            "The city of Kalaman can be entered by going southeast past " +
            "the city gates. The gates are the only way into the city, " +
            "since there are walls protecting the city everywhere else.\n");
    add_item(({"river", "vingaard river", "water"}),
        "You can see the water reflecting the light, and the river seems " +
        "to be several hundred metres across at this point.\n");
    add_item(({"mountains", "dargaard mountains"}),
        "The mountains to the south are known as the Dargaard Mountains, " +
        "stretching south from here all the way to Throtyl.\n");
    add_item(({"bushes", "tree", "trees", "plains", "plains of solamnia"}),
        "Bushes and trees block any good view you might otherwise have, " +
        "but you know these plains stretch out for many miles.\n");
    add_item(({"palisade","wooden palisade","structure","wooden structure"}),
        "A wooden palisade surrounds a wooden structure, that looks like it " +
        "is being used by caravans as a resting place for the merchants and " +
        "their guards before they enter Kalaman to trade.\n");

    add_item("sign", "The sign is a sturdy wooden creation and it has a " +
        "not attached to it, perhaps you should read it.\n");
    add_cmd_item("sign", "read", "The sign reads:\n\nOn command of Lord " +
        "Calof the ruler of the City of Kalaman, I here now declare that all " +
        "goblinkin, minotaurs and ogres are not to be allowed inside the " +
        "city walls, any of these filthy creatures should be very " +
        "aware that the city guards will not tolerate any of these foul " +
        "creatures to enter the city. To this the thieves of the kender " +
        "kind should also be added.\n\nCaptain Baxter of the City Guards.\n");
}

int
pass_gate()
{

        if(TP->query_race_name() == "goblin" || 
           TP->query_race_name() == "hobgoblin" ||
           TP->query_race_name() == "ogre" ||
           TP->query_race_name() == "minotaur")
        {
            write("The gates remain closed for you! A guard screams: " +
                "Your kind is not allowed into the city!\n");
            return 1;
        }

        if(TP->query_race_name() == "kender")
        {
            write("The gates remain closed for you. Obviously there has " +
                "been some misunderstanding... why wouldn't they let " +
                "kender into Kalaman?\n");
            return 1;
        }

    write("You pass through the city gates and enter Kalaman.\n");
    return 0;
}
