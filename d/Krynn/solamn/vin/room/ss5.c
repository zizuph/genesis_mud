/* Street south 5, by Teth
 * By Teth, Dec. 3 1996
 */


#include "../local.h"
inherit STREET;

public void
create_street()
{
    add_my_desc("A fortified building sits to the north. The " +
        "street continues both west and east.\n");
    AI(({"building","fortified building"}),"The building is " +
        "constructed of a dark mineral. A gold plaque is " +
        "affixed near the entrance.\n");
    AI(({"mineral","dark mineral"}),"It appears to be hematite, " +
        "most likely shipped from the mines near Pax Tharkas.\n");
    AI("entrance","A simple entrance, just walk right in.\n");
    AI(({"plaque","gold plaque"}),"The plaque reads:\n\n"+
        "Vingaard Keep Branch of the Palanthian Bank.\n\n");
    ACI(({"plaque","gold plaque"}),"read","The plaque reads:\n\n" +
        "Vingaard Keep branch of the Palanthian Bank.\n\n");

    AE(VROOM + "ss4", "west", 0);
    AE(VROOM + "bank", "north", 0);
    AE(VROOM + "ss6", "east", 0);
}
