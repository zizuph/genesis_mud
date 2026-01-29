#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Large hall");
 set_long("You find yourself standing in the large hall. In the middle "+
   "of the room you see sofas and chairs for those who wishes to rest. "+
   "Walls are decorated with pictures , and floor with carpets. "+
   "Passage to east runs into broad corridor , while two corridors "+
   "start to north and northeast.\n");

 add_item(({"sofa","sofas","chair","chairs"}),"Sofas and chairs are "+
   "very comfortable, anyone who is weary and wishes to rest can "+
   "easily use them.\n");
 add_item(({"wall","walls"}),"Walls are richly decorated with all "+
   "kind of pictures.\n");
 add_item(({"picture","pictures"}),"The decorator had really good "+
   "taste , he has brought many pictures of several well known "+
   "painters of Earthsea.\n");
 add_item("floor","Floor is covered with carpets.\n");
 add_item(({"carpets","carpet"}),"Carpets are colourfull and look "+
   "very expensive.\n");

 add_exit(STRHOLD_LVL2+"cor15","east");
 add_exit(STRHOLD_LVL2+"cor16","north");
 add_exit(STRHOLD_LVL2+"cor26","northwest");
}

