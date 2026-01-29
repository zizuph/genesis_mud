/* The roads of Raumdor, credit to Sarr */
#pragma strict_types
#include "defs.h"
inherit STD_ROOM;

mapping xGrid = ([
    "road01": 43,
    "road02": 44,
    "road03": 45,
    "road04": 46,
    "road05": 47,
    "road06": 48,
    "road07": 49,
    "road08": 50,
    "road09": 51,
    "road10": 52,
    "road11": 53,
    "road12": 54,
    "road13": 55,
    "road14": 56,
    "road15": 57,
    "road16": 58,
    "road17": 59,
]);

mapping yGrid = ([
    "road01": 4,
    "road02": 3,
    "road03": 2,
    "road04": 1,
    "road05": 0,
    "road06": -1,
    "road07": -2,
    "road08": -3,
    "road09": -4,
    "road10": -3,
    "road11": -2,
    "road12": -1,
    "road13": 0,
    "road14": 1,
    "road15": 2,
    "road16": 2,
    "road17": 2,
]);

string roadWest;
string roadEast;
string proximity = "distant";
string longDesc;
string longPrefix = "You are on an old worn road that runs through " +
    "sweeping plains.";
string longSuffix = "\n";
void
create_room()
{
    ::create_room();
    set_short("On a road through desolate plains");
    longDesc = longPrefix + " Rock hills dart out of the otherwise flat "
        + "landscape. The air is cold and stale and you can almost feel "+
        "the bleakness that envelopes this place. The road is dirt in "+
        "some places and made of cobblestone in other places. ";
    if (proximity == "distant")
    {
        longDesc += "It runs to the " + roadEast + 
            " deeper into the plains, while " + roadWest +
            " it heads toward a mountain pass.";
        add_item("plains", "They stretch all around you, save to the " +
                roadWest + ", where it meets two mountain ranges. " +
                "You can see cities to the south and east of you.\n");

        add_item(({"city","cities"}), "Two cities lie in the " +
                "distance, one to the south and one to the east.\n");
    }
    else if (proximity == "fork")
    {
        longDesc += "It runs to northwest into the mountains and splits " +
            "to the northeast and southeast towards two cities.";
        add_item("plains", "They stretch all around you, save to the " +
            "northwest, where they run into the mountains. You can see two " +
            "cities, one on the road to the northeast, the other to the " +
            "southeast and blocked by barricades.\n");
        add_item(({"city","cities"}), "You can see two cities, both " +
                "obscured by very large walls. One looks accessible by " +
                "road to the northeast. The other is to the southeast, " +
                "blocked by a series of barricades.\n");
        add_item(({"barricade", "barricades"}), "Wooden barricades stand " +
                "between the hills on the traversable parts of the plains, " +
                "blocking passage southeast.\n");
        add_item(({"wall", "walls"}), "The two stone walls are quite high, " +
                "effective defenses against armed attack. Each has gates " +
                "on the side facing you.\n");
        add_item(({"gate","gates"}), "You cannot see much from here.\n");
    }
    else if (proximity = "drakmere")
    {
        longDesc += "It runs to the " + roadWest + " into the plains and " +
            roadEast + " toward a city.";
        add_item("cities", "The nearest city lies to the northeast, with a " +
                "gate on this side of its large stone walls. Another walled " +
                "city lies in the distance to the southeast.\n");
        add_item(({"city", "nearest city"}), "It is obscured by walls, but " +
                "it appears to be quite large.\n");
        add_item("distant city", "It looks large and walled, but otherwise " +
                "you cannot see much from here.\n");
        add_item(({"wall", "walls"}), "They are quite high and constructed " +
                "with sturdy-looking stone. Gates are visible on this side.\n");        add_item(({"gate","gates"}), "The gates are large and dark.\n");
    }
    
    set_long(longDesc + longSuffix);

    add_item("landscape", "Vast and flat plains, spiked with hills of rock.\n");
    add_item("cobblestone", "They look well-used.\n");
    add_item("road", "It is old and worn, made of dirt and stone.\n");
    add_item("hills","The hills roll on for as far as the eye can see.\n");
    add_item(({"mountain","mountains","ranges"}), "They stretch to the " +
            "south and west. A pass lies to the northwest, where they " +
            "converge.\n");
    add_item("pass", "It lies to the northwest, between " +
            "two mountain ranges.\n");


}

mixed
query_waypoint_direction(string waypoint)
{
    if (waypoint == "mountains")
        return roadWest;
    if (waypoint == "drakmere")
        return roadEast;
    return 0;
}

int *
query_coordinates()
{
    string room = extract(MASTER_OB(TO), strlen(ROAD_DIR));
    return ({xGrid[room], yGrid[room], 0}); 
}
