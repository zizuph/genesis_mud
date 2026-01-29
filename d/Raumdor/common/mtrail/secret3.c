#include "defs.h"
inherit SECRET_ROOM;
/* SARR */

string *trick_room();

void
create_room()
{
    string *trick_rooms = trick_room();
    ::create_room();
    set_long("This is a small cavern. A few torches hang on the wall, "+
    "lighting up the room. From here, you see a dark pool in the "+
    "center of the room, and, two passageways. One of the passages "+
    "leads northeast, while the other leads southeast. To the west, "+
    "you can go back the way you entered.\n");
    add_item(({"torch","torches"}),"They burn on the wall, and look like "+
    "they are taken care of, by who, you have know idea.\n");
    add_item("pool","@@pool");
    add_exit(MTRAIL_DIR + "secret2","west",0);
    add_exit(trick_rooms[0],"northeast","@@mess");
    add_exit(trick_rooms[1],"southeast","@@mess");
    set_alarm(0.1,0.0,"reset_room");
}

int
mess()
{
   write("The passage way bends to the east...\n");
   return 0;
}


string
*trick_room()
{
    if(random(2))
    {
        return ({MTRAIL_DIR + "death_room",MTRAIL_DIR + "true_room"});
    }
    return ({MTRAIL_DIR + "true_room",MTRAIL_DIR + "death_room"});
}

string
pool()
{
    return
    "As you gaze into the pool, a voice echos in your head..."+
    "Rooms of death and utter despair, the bones do show the nature of "+
    "the lair, seek ye the right one, and you will go true, choose the "+
    "false one, and its the end for you!\n";
}

