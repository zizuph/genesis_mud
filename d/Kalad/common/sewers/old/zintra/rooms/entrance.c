
inherit "/d/Kalad/common/sewer/sewer_std"
#include "/d/Kalad/defs.h"

create_room()
{
    ::create_room();
    add_short("Entrance to Zintra guild");
    add_long(BS("You are in a corridor running north and south. " +
        "The area reeks of excrement from nearby streams of sewage." +
        " A chill runs down your spine. You feel that you are not" +
        " safe here."));
    add_item(({"wall","walls","west wall"}), BS("It looks exactly" +
        " like the other rooms in this area of the sewer. It's made" +
        "of stone and is covered with patches of slippery scum."));
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
