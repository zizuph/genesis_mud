/*
 * /d/Kalad/common/wild/pass/underdark/u32.c
 * Purpose    : A space between walls, the floor, and the ceiling
 * Located    : Dark Domain, not far from Undraeth
 * Created By : Antharanos
 * Modified By: Nikklaus, Oct'97: adapted to dark_dom inherit
 */

# pragma strict_types
# include "dark_dom.h"

inherit DARK_DOM;

void
create_dark_dom()
{
    set_short("Entrance to Sulphur Cave");
    set_long("You are within the confines of the Dark Dominion, "+
      "in the lightless land below the world of men. "+
      "You are standing within a long, narrow cavern. The sides "+
      "of the cavern are strangely smooth, not a rough spot visible. The odd "+
      "smell of sulphur hangs in the air. Similarly, the floor and ceiling "+
      "are clear of obstacles, having no stalagmites or stalactites. Dark "+
      "passages continue to the north and south.\n");
    add_item(({"cavern"}),"The enclosed space surrounding you.\n");
    add_item(({"sides","side","walls","wall"}),"It does not seem to be "+
      "artificially created, yet somehow the walls are as smooth as silk.\n");
    add_item(({"floor","ceiling"}),"It has also been worn smooth, by some "+
      "strange and unseen force.\n");
    add_item(({"passages","passage"}),"Exits that lead out of this cavern.\n");
    add_exit(DARK(u28), "north");
    add_exit(DARK(u38), "south");
}

void
init()
{
    ::init();
    write("The smell of sulphur assaults your nostrils.\n");
}
