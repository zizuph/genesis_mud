#include "defs.h"
inherit STD_ROOM;

mapping xGrid = ([
    "test1": -10, 
    "test2": -9,
    "test3": -8,
    "test4": -10,
    "test5": -9,
    "test6": -8,
    "test7": -10,
    "test8": -9,
    "test9": -8,
]);

mapping yGrid = ([
    "test1": -10,
    "test2": -10,
    "test3": -10,
    "test4": -11,
    "test5": -11,
    "test6": -11,
    "test7": -12,
    "test8": -12,
    "test9": -12,
]);


void
create_room()
{
    ::create_room();
    set_short("A test room");
    set_long("You are in a test room with space for testing.\n");
}

int
query_test_room()
{
    return 1;
}

int *
query_coordinates()
{
    string room = extract(MASTER_OB(TO), strlen(TEST_DIR));
    return ({xGrid[room], yGrid[room], 0});
}
