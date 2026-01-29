/* created by Aridor 05/19/94 */

#include "../local.h"

inherit LIGHTDARKROOM;

void
create_ld_room()
{
    set_short("In a hallway");
    set_long("@@my_long");
    
    add_exit(THEIWAR + "r11", "southeast");
    add_exit(THEIWAR + "r14", "northwest");
    
}


string
my_long()
{
    return "A passageway leading northwest and southeast. " +
      "This place is quite wide and you notice that it leads downwards " +
      "in the southeastern direction and upwards towards the northwest. " +
      "You can see a lot of debris and dust " +
      "on the floor.\n";
}

