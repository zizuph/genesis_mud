#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

inherit STREET_DESC;
inherit KENDERMORE_OUT;

object ken_herbalist;

void
reset_kendermore_room()
{
    if (!ken_herbalist)
    {
        ken_herbalist = clone_object(KNPC + "herbalist.c");
        ken_herbalist->move(TO);
    }
}

void
create_kendermore_room()
{
    set_short("Outside a large house");
    set_long("@@long_descr");
    add_item("houses", "Even the houses here have a carefree feeling. One " + 
        "house doesn't seem to fit in like the others, though.\n");
    add_item("house", "Unlike the other houses, this house has a distinct " + 
        "unkenderlike look to it. A complicated gizmo sits on the metal " + 
        "shingled roof. Another gizmo is attached next to the front door.\n");
    add_item("gizmo", "The roof gizmo or the door gizmo?\n");
    add_item("roof gizmo", "It looks very complicated, but you guess that " + 
        "it might be a weathervane.\n");
    add_item("door gizmo", "There are gears, bells, whistles and a small " + 
        "button on it. It looks very complicated.\n");
    add_item("door", "It's very tightly locked.\n");
    add_item(({"roof", "shingles", "metal shingles"}), "You aren't certain " + 
        "why this house has metal shingles, especially since they don't " + 
        "add any aesthetic appeal.\n");
    add_item(({"gears", "bells", "whistles", "button", "small button"}),
        "This looks very much like a gnomish doorbell. Perhaps you could " + 
        "push the button and find out.\n");
    add_item(({"kendermore", "city"}), "The city of Kendermore spreads " +
        "out around you in a complicated twisting of streets. It is the " +
        "home of many kender when they aren't adventuring and exploring.\n");
    add_item(({"street", "road"}), "The road is made of cobblestones. " +
        "It winds " + 
        "beyond your view.\n");
    add_item(({"sign", "signs"}), "Best to ask directions instead.\n");

    add_cmd_item("house", "enter", "@@enter_house");
    add_cmd_item(({"button", "small button"}), ({"push", "press"}),
        "@@push_button");

    add_exit(KROOM + "street39", "north", 0);
    add_exit(KROOM + "g_house", "east", "@@no_pass");
    add_exit(KROOM + "street37", "southwest", 0);

    set_tell_time(100);
    add_tell("A kender bumps into you, apologizes and continues on " + 
        "his way.\n");
    add_tell("Bright laughter rings out from nearby.\n");
    add_tell("A kender arrives, excitedly picks up a piece of shiny " + 
        "metal from the ground, and happily skips away.\n");
    add_tell("A small mouse scurries across your path.\n");
    add_tell("A loud crashing sound reaches your ears.\n");
    add_tell("A small bug skitters under a bush.\n");

    reset_kendermore_room();
    return;
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
    return (tod_descr() + season_descr() + "Houses stand on both sides " + 
        "of you. One particular house stands out to your east. " +
        street_descr() + " It appears to be a gnome's house. The road " + 
        "continues on its winding way to the north and southwest. Numerous " + 
        "signs point in all directions, but they tend to contradict each " + 
        "other and point in directions where there are no exits.\n");
}

string
enter_house()
{
    write("You can't seem to find any way in. Perhaps the door needs " + 
        "to be opened from the inside.\n");
    return "";
}

string
push_button()
{
    write("You push the small button which turns a gear, which flips " +
        "a switch which...well, it's getting a bit confusing now. The " + 
        "bells and whistles finally ring with deafening clarity. A gnome " + 
        "opens the door and ushers you in.\n");
    say(QCTNAME(TP) + " pushes a small button on the door gizmo. It sets " + 
        "off a fairly confusing process. The bells and whistles finally " + 
        "ring with deafening clarity. A gnome appears in the doorway, and " + 
        "ushers " + QTNAME(TP) + " in.\n");
    tell_room(KROOM + "g_house", "You hear a loud whistling sound. The " + 
        "gnome opens the door and " + QTNAME(TP) + " walks in.\n");
    TP->move_living("M", KROOM + "g_house", 1, 0);
    return "";
}

int
no_pass()
{
    write("The door is closed and locked tightly.\n");
    return 1;
}



        
