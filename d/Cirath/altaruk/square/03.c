#include "../defs.h"
inherit ALT_STD + "room.c";
#include "/d/Cirath/common/teamer.h"

void
create_street()
{

     short_name("in the Merchant Plaza in Altaruk.");
    extra_line("This the central square of altaruk. Its" +
        " bustling with activity. Merchant stalls crowded" +
        " with traders and costumers haggling over trinkets" +
        " and other useless items sold here. There is a well" +
        " in middle of the square.");
    last_line("A gate to the guard barracks is north." +
        "All sorts of people are here, so watch you pockets.");
    
    add_item("well", "A well stands southwest of you.\n");
    
    add_exit("02", "west", 0,1,0);
    add_exit("05", "southwest", 0,1,0);
    add_exit("06", "south", 0,1,0);
    add_exit(ALT_HOU + "barracks2", "north", 0,1,0);
    
    reset_room();
}
void
reset_room()
{
    if (leader) return;
    bring_room_team(ALT_NPC+"alt_guard2",1,3,ALT_NPC+"alt_guard2",1);
}