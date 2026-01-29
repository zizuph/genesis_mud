
inherit "/d/Kalad/common/sewer/sewer_std"
#include "/d/Kalad/defs.h"

create_room()
{
    ::create_room();
    add_short("Inside Zintra guild rotating room");
    add_long(BS("You are in a corridor running east from here. " +
        "The north and south walls are made of black stone that" +
        " seems to absorb sound, creating an eerie silence. " +
        "The east wall is conspicuously different. " + 
        "Your sensitive nose detects the aroma of sewage."));
    add_item("east wall", BS("It looks like" +
        " a wall that might be found in a sewer. It's made" +
        "of ordinary stone and is covered with patches of " +
        "slippery scum."));
    add_item(({"wall","walls"}), BS("The north and south walls" +
        " are crafted from a dull black stone that is unlike " +
        "any you have ever seen. The east wall looks like a " +
        "wall that might be found in a sewer. It's made of" +
        "ordinary stone and is covered with patches of " +
        "slippery scum."));
}

init()
{
    add_action("tap","tap wall");
    add_action("tap","tap west wall");
    add_action("tap","knock on wall");
}

tap()
{
    int i;

    TP->catch_msg("You tap the wall with your knuckles.");
    tell_room(E(TP), TP->query_name() + " taps the west wall with " +
        TP->query_pronoun() + " knuckles.\n", TP);
    for (i=0; i<300; i++) {};
    rotate_room(E(TP));
}

rotate_room(object environ)
{
    int i;
    object *inventory;

    ZINTRA(rooms/entranceb.c)->rotate_room() /* rotate the other room */
    tell_room(environ), "You hear the muffled sounds of" +
        " ancient machinery.\n");
    for (i=0; i<300; i++) {};
    tell_room(E(TP), BS("The heavy stone floor" +
        " rotates smoothly beneath your feet."));
    /*This is where the objects should be moved to the other room*/
    inventory = deep_inventory(TO);
    for (i=0; i < sizeof(inventory); i++)
    {
        inventory[i]->move(ZINTRA(rooms/entranceb.c), 1);
    }
}
