inherit "/std/room";
inherit "/d/Kalad/room_std";
inherit "/lib/pub";

#include <stdproperties.h>
#include "/d/Kalad/defs.h"
#include <macros.h>
#include <money.h>
void
create_room()
{
    ::create_room();
    set_short("You are sitting on a table in The Rickety Roaring Rumbling. "
             +"Restaurant. There is a menu standing on the table. "
             +"When you have made a choice you could order a menu");
    set_long("You are sitting on a table in The Rickety Roaring Rumbling. "
             +"Restaurant. There is a menu standing on the table. "
             +"When you have made a choice you could order a menu.\n");
    add_item("menu","It seems readable.\n");
    add_item("table","It's got a menu on it.\n");
    add_cmd_item("menu","read","@@read");
add_prop(ROOM_I_INSIDE,1);
}

void
init()
{
    ::init();
    add_action("stand_up","stand");
    add_action("order_menu","order");
}

int
read(string str)
{
      write("\n"+
           "+---------------------MENU---------------------------+\n"+
           "|                                                    |\n"+
           "| Menu 1: - Spaghetti with red wine                  |\n"+
           "|                                                    |\n"+
           "| Menu 2: - Lasagna with a bottle of beer            |\n"+
           "|                                                    |\n"+
           "| Menu 3: - A plate of baked potatoes with           |\n"+
           "|           sauerkraut, a bratwurst and              |\n"+
           "|           a pint of beer                           |\n"+
           "|                                                    |\n"+
           "| Menu 4: - Shaorma and french fries                 |\n"+
           "|                                                    |\n"+
           "| Menu 5: - A filled turkey and whiskey              |\n"+
           "|                                                    |\n"+
           "+----------------------------------------------------+\n");
     return 1;
}
 
int
stand_up(string str)
{
    write("You decide that you've eaten enough and stand up.\n");
     this_player()->move_living("M","/d/Kalad/common/trade/restaurant",1,0);
return 1;
}
