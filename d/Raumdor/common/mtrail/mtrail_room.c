/* Mountain trail rooms, credit to Sarr */
#pragma strict_types
#include "defs.h"
inherit STD_ROOM;

mapping xGrid = ([
    "mtrail01": 23,
    "mtrail02": 24,
    "mtrail03": 25,
    "mtrail04": 26,
    "mtrail05": 27,
    "mtrail06": 28,
    "mtrail07": 29,
    "mtrail08": 30,
    "mtrail09": 31,
    "mtrail10": 32,
    "mtrail11": 33,
    "mtrail12": 34,
    "mtrail13": 35,
    "mtrail14": 36,
    "mtrail15": 37,
    "mtrail16": 38,
    "mtrail17": 39,
    "mtrail18": 40,
    "mtrail19": 41,
    "mtrail20": 42,
    "mtrail21": 29,
]);

mapping yGrid = ([
    "mtrail01": 7,
    "mtrail02": 8,
    "mtrail03": 9,
    "mtrail04": 10,
    "mtrail05": 11,
    "mtrail06": 12,
    "mtrail07": 13,
    "mtrail08": 13,
    "mtrail09": 12,
    "mtrail10": 11,
    "mtrail11": 11,
    "mtrail12": 11,
    "mtrail13": 10,
    "mtrail14": 9,
    "mtrail15": 8,
    "mtrail16": 7,
    "mtrail17": 7,
    "mtrail18": 7,
    "mtrail19": 6,
    "mtrail20": 5,
    "mtrail21": 14,
]);

string type;
string roadWest;
string roadEast;

void
create_room()
{
    ::create_room();
    set_short("On a mountain pass trail");
    if (type == "west")
    {
        set_long("You stand on a steep mountain trail travelling through a " +
                "mountain pass. All you can see around you are rocks and " +
                "the silence is eerie. The trail leads " + roadEast +
                " toward the top of the pass and " + roadWest + 
                " to a dreadful-looking forest valley.\n");
        add_item(({"forest","valley"}), "A sinister-looking " +
                "wildwood is spread thoroughly between mountain ranges. " +
                "The only breach of the dense canopy is a thin groove " +
                "leading to the trail you stand on.\n");
        add_item("canopy", "Impenetrable by sight, you can only imagine " +
                "what lies beneath.\n");
        add_item("groove", "It begins at the base of the trail you stand " +
                "and snakes off to the west.\n");
    } else {
        set_long("You are on a steep mountain trail. All around are rocks " +
            "and mountain cliffs. Far down the mountain you see the trail " +
            "dumps into a huge valley. You see plains, rocky hills, and " +
            "what appear to be cities. The path leads down to the " + roadEast +
            " and up to the " + roadWest + ".\n");
        add_item("cities","It's hard to see much from so far away.\n");
        add_item("plains","Huge flat plains dominate the landscape.\n");
        add_item("hills","You see many large rocky hills " +
            "around on the plains.\n");
    }
    add_item("trail","The trail is rocky, dusty and steep.\n");
    add_item("rocks","Hard, jagged rocks formed by the mountains.\n");
    add_item(({"mountains","mountain","cliffs","ranges"}),
            "They surround you, forming the pass.\n");
    add_item("pass", "It is created by two great mountain ranges extending " +
        "west and south. The cliffs on either side of you rise high into " + 
        "the sky.\n");
}

int
up()
{
    write("You travel further up through the mountain pass.\n");
    return 0;
}
int
down()
{
    write("You travel further down the mountain pass.\n");
    return 0;
}

mixed
query_waypoint_direction(string waypoint)
{
    if (waypoint == "forest")
        return roadWest;
    if (waypoint == "plains")
        return roadEast;
    return 0;
}

int *
query_coordinates()
{
    string room = extract(MASTER_OB(TO), strlen(MTRAIL_DIR));
    return ({xGrid[room], yGrid[room], 0});
}
