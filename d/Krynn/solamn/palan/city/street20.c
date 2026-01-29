/* created by Aridor 06/21/93 */

#include "../local.h"

inherit STREET_BASE

string
wall()
{
    return "The wall to the north seems to surround an empty " +
           "parcel, it feels quite strange to leave one of " +
           "the best locations in town empty like that.\n";
}

string
query_to_jail()
{
  return "east";
}

void
create_palan_room()
{

    set_short("Paladine Street");
    set_long(BS("There are houses along this street just like "
        +    "any other street in the city, the street is "
        +    "bustling with activity. Only the alley to the "
        +    "south seems to cast dark shadows. It is completely "
        +    "deserted and you wonder if you dare go in there. "
        +    "Strangely though, to the north you see a wall but no "
        +    "building behind it.", SL));


    add_exit(ROOM + "street9","west",0,1);
    add_exit(ROOM + "plaza","east",0,1);
    add_exit(ROOM + "street19","south","@@dare",1);
    add_exit(ROOM + "street21","north",0,1);

    add_item("wall",wall);
}

int
dare()
{
    if (TP->query_base_stat(5) > 30)
        return 0;
    else
        write("You don't have the guts to go in there!\n");
        return 1;
}

