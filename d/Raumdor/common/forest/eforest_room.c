#include "defs.h"
inherit FOREST_ROOM;

mapping xGrid = ([
    "eforest29": 15,
    "eforest20": 15,
    "eforest12": 15,
    "eforest04": 15,
    "eforest30": 16,
    "eforest21": 16,
    "eforest13": 16,
    "eforest05": 16,
    "eforest31": 17,
    "eforest22": 17,
    "eforest14": 17,
    "eforest06": 17,
    "eforest32": 18,
    "eforest23": 18,
    "eforest15": 18,
    "eforest07": 18,
    "eforest01": 18,
    "eforest33": 19,
    "eforest24": 19,
    "eforest16": 19,
    "eforest08": 19,
    "eforest02": 19,
    "eforest43": 20,
    "eforest34": 20,
    "eforest25": 20,
    "eforest17": 20,
    "eforest09": 20,
    "eforest03": 20,
    "eforest52": 21,
    "eforest47": 21,
    "eforest44": 21,
    "eforest35": 21,
    "eforest26": 21,
    "eforest18": 21,
    "eforest10": 21,
    "eforest51": 22,
    "eforest48": 22,
    "eforest45": 22,
    "eforest36": 22,
    "eforest27": 22,
    "eforest19": 22,
    "eforest11": 22,
    "eforest49": 23,
    "eforest46": 23,
    "eforest37": 23,
    "eforest28": 23,
]);
mapping yGrid = ([
    "eforest29": 2,
    "eforest20": 1,
    "eforest12": 0,
    "eforest04": -1,
    "eforest30": 2,
    "eforest21": 1,
    "eforest13": 0,
    "eforest05": -1,
    "eforest31": 2,
    "eforest22": 1,
    "eforest14": 0,
    "eforest06": -1,
    "eforest32": 2,
    "eforest23": 1,
    "eforest15": 0,
    "eforest07": -1,
    "eforest01": -2,
    "eforest33": 2,
    "eforest24": 1,
    "eforest16": 0,
    "eforest08": -1,
    "eforest02": -2,
    "eforest43": 3,
    "eforest34": 2,
    "eforest25": 1,
    "eforest17": 0,
    "eforest09": -1,
    "eforest03": -2,
    "eforest52": 6,
    "eforest47": 4,
    "eforest44": 3,
    "eforest36": 2,
    "eforest26": 1,
    "eforest18": 0,
    "eforest10": -1,
    "eforest51": 5,
    "eforest48": 4,
    "eforest45": 3,
    "eforest35": 2,
    "eforest27": 1,
    "eforest19": 0,
    "eforest11": -1,
    "eforest49": 4,
    "eforest46": 3,
    "eforest37": 2,
    "eforest28": 1,
]);

void
create_room()
{
    forest_features = " Old trees loom despairingly over you, their " +
        "gnarled branches scratching at your face." + forest_features;
    ::create_room();
}

int *
query_coordinates()
{
    string room = extract(MASTER_OB(TO), strlen(FOREST_DIR));
    return ({xGrid[room], yGrid[room], 0});
}
