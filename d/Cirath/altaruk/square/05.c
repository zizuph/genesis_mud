#include "/d/Cirath/altaruk/defs.h"

inherit ALT_STD + "room.c";
inherit "/lib/pub";

#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
   bring_room_mob("wguard",ALT_NPC + "wguard",1,1);
}

void
create_street()
{

    short_name("in the Merchant Plaza in Altaruk.");
    extra_line("This the central square of altaruk. Its" +
        " bustling with activity. Merchant stalls crowded" +
        " with traders and costumers haggling over trinkets" +
        " and other useless items sold here. There is a well" +
        " in middle of the square.");
    last_line("All sorts of people are here, so watch you pockets." +
        " There is a sign next to the well.");
    
    add_item("well", "A well stands here. A merchant is" +
        " selling the water. Nothing good comes cheap in Altaruk." +
        " A big mul is selling water skins here." +
        " There is a sign next to the well.\n");
    add_item("sign", "The sign says:\n" +
        " Water skins - only one gold!\n");

    add_drink(({"water","waters", "water skin", "water skins"}),"skin","water",500,0,144,0,0,"A water skin bursting with water from the well in Altaruk.\n",0);

    add_cmd_item("sign","read",
     "The sign says:\n Water skins - only one gold!\n"); 

    add_exit("01", "northwest", 0,1,0);
    add_exit("02", "north", 0,1,0);
    add_exit("03", "northeast", 0,1,0);
    add_exit("04", "west", 0,1,0);
    add_exit("06", "east", 0,1,0);
    add_exit("07", "southwest", 0,1,0);
    add_exit("08", "south", 0,1,0);
    add_exit("09", "southeast", 0,1,0);
    
    reset_room();
}

void
init()
{
    ::init();
    init_pub();
    add_action ("well_drink", "drink");
}

private int
well_drink(string str)
{
    if(str == "from well")
    {
    write("As you step up to the well you find the" +
        " water level much to low to reach.\n");
        return 1;
    }
}
