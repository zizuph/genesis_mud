inherit "/std/workroom";

#include "/sys/macros.h";
#include "/d/Emerald/sys/macros.h"
#include "/sys/stdproperties.h"

create_workroom()
{
    set_short("A large marble chamber");
    set_long("The walls of this room appear to be huge slabs of black marble. "+
        "There are obsidian pyres lining each side of the room, burning with "+
        "pale, green unnatrual flames. There is a desk on the far side of the "+
        "room, with a large chair behind it. As you look around this vast nearly "+
        "empty chamber, you see the ceiling is made entirely of clear crystal. "+
        "Dark foreboding clouds roll by at unnaturally high speeds, spitting torrid "+
        "bolts of lighting which light up the black sky as they roll by. Behind the "+
        "desk, dominating the northern wall, is a huge black, silken banner with a "+
        "silver symbol of Val-Shoreil in it's center, the silver symbol is "+
        "giving off a soft glow that seems to contrast oddly with the pale green "+
        "light coming from the pyres. The dull roar of the pale flames burning "+
        "in their obsidian pyres, and the great claps of thunder in the sky are the "+
        "only sounds you hear echoing throughout this huge marble chamber.\n");
   add_item(({"desk","ebony desk"}),"A large desk made of ebony, it "+
        "has papers and maps all over it.\n");
   add_item("banner","A large black banner, the symbol of Val-Shoreil "+
       "glows softly, warming your eyes when you look at it.\n");

    add_exit("/d/Emerald/outpost1/gate02.c","down","@@check_exit");

    

}
int

check_exit()
{
    if(TP->query_wiz_level())
        return 0;
    write("You step twards the exit and slam into the chest of a armored skeletal " +
        "warrior who wasn't there a second ago. The warrior stares at you with " +
        "his firey eyes and speaks: \n " +
        "                 'You mortal, may not pass this way, only      \n" +
        "                those of devine power may enter these halls...' \n " +
        "\n " +
        "The skeletal guardian points his clawed finger at you  in warning and " +
        "slowly fades out of existance.\n");
        return 1;
}
