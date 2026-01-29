/* Road to Tantallon
 * By Teth, Jan 17 1996
 */

#include "local.h"
inherit ROADBASE;


public void
create_road()
{
    add_my_desc("The city walls of Tantallon loom before you, to the " +
      "northeast. Along the wall to the east, emerges a wide sewer " +
      "pipe, with sewage flowing down the hillside. The road leaves " +
      "southwest.\n");

    AI(({"platform","large platform"}),"It seems that the platform " +
      "is used for some sort of aerial transportation.\n");
    AI(({"city","city of tantallon","tantallon"}),"The city of Tantallon " +
      "rests behind the city walls.\n");
    AI(({"walls","city walls"}),"The city walls of Tantallon stand firm " +
      "and keep unwanted travellers out.\n");
    AI("east wall","From the east wall emerges a wide sewer pipe.\n");
    AI(({"pipe","sewer pipe","wide pipe","wide sewer pipe"}),"The pipe " +
      "obviously leads to the sewers beneath the city of Tantallon. " +
      "Raw sewage flows from the pipe, down the hillside.\n");
    AI(({"sewage","raw sewage"}),"The raw sewage is the waste and want-not " +
      "of the people of Tantallon. It reeks.\n");

    ACI(({"pipe","sewer pipe", "wide pipe", "wide sewer pipe"}),"enter",
      "@@go_sewer");

    AE(TROOM + "road15", "southwest", 0, 2);
    /*AE(TROOM + "street1", "northeast", "@@is_blocked", 1);*/
    AE("/d/Krynn/neraka/city24","northeast");
    /*When the new Tantallon is in place, remove this link to
     *the old version of Neraka
     * ~Aridor 09/97
     */
    reset_tant_room();
}

go_sewer()
{
    write("You hold your breath, slog through raw sewage, and enter the " +
      "sewer pipe.\n");
    set_dircmd("pipe");
    TP->move_living("into the pipe",TROOM + "sewer1", 0, 0);
    return "";
}


int
is_blocked()
{
    write("Unfortunately, the gates of Tantallon are closed to " +
      "visitors. Return within the month!\n");
    return 1;
}
