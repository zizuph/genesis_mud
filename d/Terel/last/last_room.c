/*
 *  /d/Terel/last/last_room.c
 *
 *  Master room for all rooms in Last
 *
 * Shinto March 98
 */

#pragma strict_types
#pragma binary_save

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <stdproperties.h>


// Global Variables
string Extraline;

// Prototypes
string create_long();
void   create_last_room();
void   add_road();
void   add_snow();
void   add_mountain();
void   add_sea();
void   add_town();

/*  Function name: create_long
 *  Description  : Makes the long description for a room.
 *  Returns      : A string - The long description.
 */

string
create_long()
{
    string long;
		long = "You are in the town of Last in the north of Terel. The final"+
          " established town before the great north. A great mountain "+
          "towers above to the northwest, open tundra to the northeast"+
          ", and the Sea of Terel to the east. The west becomes lush and"+
          " greener as you head towards Calathin.";

    if (stringp(Extraline))
        long = long+" "+Extraline;

    return long + "\n";
}


/*  Function name: create_last_room
 *  Description  : Sets up a last room.
 */

void
create_last_room()
{
    set_long(&create_long());

}

void
add_road()
{
    add_item(({"road","ground"}),"The road is narrow and not well-travelled."+
                   " The road and the ground are both covered with snow that "+
                   "slowly descends from above.\n");
}

void
add_snow()
{
    add_item(({"snow"}),"The falling snow blows down from Mount Siralan "+
                   "and blanketing the town pure white.\n");
}

void
add_mountain()
{
    add_item(({"mountain","siralan","Siralan","mount siralan",
                   "mount Siralan","Mount siralan","Mount Siralan"}),
                   "The mountain begins with a large base then rises up to"+
                   " a great peak. Winds blow violently around the mountain"+
              " blowing snow this way and that.\n");
}

void
add_sea()
{
    add_item(({"sea","sea of terel","Sea of Terel","sea of Terel","Sea of terel",
                   "water","bay"}),
                   "The Sea of Terel spreads out before you to the east. The"+
                   " water is dark and ominous, a deep purple nearly black. The"+
                   " water this far north is rather cold, but not deadly. Ships"+
                   " can be seen arriving and leaving the port, ships being the "+
                   "prefered means of travel to Last.\n");
}

void
add_town()
{
    add_item(({"Last","last","town"}),"The town is blanketed with snow "+
                   "falling from the north. Being so far to the north, the town"+
                   " is neither crowded nor very active. Fishing and hunting "+
                   "seem to be the main occuptions outside of necessities such "+
                   "as blacksmith, inns and pubs.\n");
}
