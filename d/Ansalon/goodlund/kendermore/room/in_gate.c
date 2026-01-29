#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

inherit STREET_DESC;
inherit KENDERMORE_OUT;

void
reset_kendermore_room()
{
    return;
}

void
create_kendermore_room()
{
    set_short("Just inside Kendermore");
    set_long("@@long_descr");
    add_item(({"street", "road", "stone road"}), "It starts here, and " + 
        "heads east, winding beyond your view.\n"); 
    add_item(({"city", "kendermore"}), "The city of Kendermore spreads out " + 
        "to the east in a complicated twisting of streets.\n");
    add_item(({"gap", "large gap"}), "You could enter the gap to leave the " + 
        "city.\n");
    add_item(({"sign", "signs"}), "Best to ask directions instead.\n");
    add_item(({"wall", "walls"}), "The tops of the walls contain " + 
        "holes where construction was paused. It doesn't look like " + 
        "anyone is planning on finishing it, though. Where the gates to " + 
        "the city should be, lies a large gap. It looks like the only " + 
        "obvious way in our out of the city on the west side.\n");
    add_item(({"tent", "blue tent", "bright blue tent", "bright tent"}),
        "The bright blue tent has been set up here by the gate to attract " + 
        "the attention of travellers. The flap has tied been thrown open. " + 
        "A sign hangs on the front of the tent.\n");
    add_item("flap", "It has been thrown open.\n");
    add_item("sign", "\nIt reads: Danalin's hoopak store, now open!\n\n");
    add_exit(KROOM + "street06", "east", 0);
    add_exit(KROOM + "hoopak_store", "tent", 0);
    add_cmd_item("gap", "enter", "@@enter_gap");
    add_cmd_item("sign", "read", "\nThe sign reads: Danalin's " + 
        "hoopak store, now open!\n\n");

    set_tell_time(100);
    add_tell("You hear shouts and yells as a bunch of merchants try to " + 
        "fit their wagon through the gap.\n");
    add_tell("A cat bounds across your path.\n");
    add_tell("A high voice rings a biting taunt.\nA kender runs by " + 
        "followed closely by a flushed looking dwarf.\n");
    add_tell("A stone falls down from above, followed by a loud 'Oops!'\n");
    add_tell("A small bug skitters under a bush.\n");
 

    reset_kendermore_room();
    set_alarm(1.0,0.0,"call_dummy");
    return;
}

void
call_dummy()
{
    "/d/Ansalon/guild/society/room/kender_room"->dummy_function();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}
 
string
long_descr()
{
    return (tod_descr() + season_descr() + "You stand just inside the " + 
        "city of Kendermore. A tall stone wall towers to your " +
        "west. " + street_descr() + " A bright blue tent has been set up " + 
        "here, right inside the gate. A road starts here and heads east, " + 
        "winding beyond your view. Numerous signs point in all directions, " + 
        "but they tend to contradict each other and point in directions " + 
        "where there are no exits.\n");
}

string
enter_gap()
{
    write("You walk through the gap in the wall, exiting Kendermore.\n");
    say(QCTNAME(TP) + " walks through the gap in the wall, exiting " + 
        "Kendermore.\n");
    tell_room(KROOM + "out_gate", QCTNAME(TP) + " arrives from the gap " + 
        "in the wall.\n");
    TP->move_living("M", KROOM + "out_gate", 1, 0);
    return "";
}

