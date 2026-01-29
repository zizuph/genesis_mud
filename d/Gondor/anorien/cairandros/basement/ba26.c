/*
 * Basement in Cair Andros
 * /d/Gondor/anorien/cairandros/basement/ba26.c
 *
 * Varian - March, 2020
 */

#pragma strict_types

#include "../../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit ANORIEN_STD_DIR + "bsmt_base";

/*
 * Function name:        create_bs_room()
 * Description  :        Creates a basement room in Cair Andros
 */

nomask void 
create_bs_room() 
{    
    set_items_barracks();

    set_short("Inside the lower barracks in Cair Andros");
    set_long("@@desc@@"); 

    add_item( ({"quarters", "barracks", "lower barracks", "here"}),
        "@@desc@@");
    add_item( ({"hall", "hallway"}),
        "This hallway leads through the lower levels of Cair Andros, " +
        "you can reach it by going through the opening in the north " +
        "wall.\n");
    add_item (({"west", "west wall", "western wall"}),
        "Much like the eastern wall, there are several beds lined " +
        "up against the stone blocks of the western wall. The beds " +
        "are really not much more than pallets, wooden boxes " +
        "filled with straw covered with a thick layer of linen.\n");
    add_item( ({"north", "northern wall", "north wall", "opening",
            "wide opening"}),
        "The northern wall has been left fairly plain, distinguished " +
        "only by single wide opening which leads into the hallway " +
        "beyond.\n");
    add_item( ({"south", "south wall", "southern wall"}),
        "Your eyes are immediately drawn to the ancient, ornate " +
        "sarcophagus which sits in front of the southern wall.\n");
    add_item (({"east", "east wall", "eastern wall"}),
        "Much like the western wall, there are several beds lined " +
        "up against the stone blocks of the eastern wall. The beds " +
        "are really not much more than pallets, wooden boxes " +
        "filled with straw covered with a thick layer of linen.\n");
    add_item( ({"bunk", "bunks", "bed", "beds", "pallet", "pallets"}),
        "The beds in here have been lined up against both the " +
        "east and west walls. The beds themselves are sturdy " +
        "wooden boxes which have been filled with straw and then " +
        "covered with a thick linen blanket. They don't look " +
        "overly comfortable, but they would certainly be preferable " +
        "to sleeping on the stone floor.\n");
    add_item( ({"ancient ornate sarcophagus", "ornate sarcophagus",
            "ancient sarcophagus", "sarcophagus", "stone sarcophagus"}),
        "This is an ancient sarcophagus ornately carved from a " +
        "smooth black stone. The top of the sarcophagus details " +
        "the body of a tall man, both hands laid upon his breast " +
        "as they clutch the hilt of a sword that points down " +
        "to his knees. Etched into the side of the sarcophagus " +
        "you read the following:\n\nHere lies Adrahil of Belfalas\n" +
        "Hero of Gondor, he gave his life to save the lives of " +
        "two score of his men and to ensure the Wainriders " +
        "could not cross the Anduin.\nJuly 28, T.A. 1944.\n");
    add_item( ({"bier", "stone bier", "simple stone bier",
            "simple bier"}),
        "This simple bier, constructed entirely out of the same " +
        "grey stone seen everywhere else in Cair Andros, supports " +
        "an ancient and ornate sarcophagus.\n");

    set_no_exit_msg( ({"northwest", "northeast", "southwest",
            "southeast", "east", "west", "south"}),
        "Those walls sure are solid! You will have to try moving in " +
        "a different direction.\n");

    add_npc(CA_NPC_DIR + "ca_officer");
    add_npc(CA_NPC_DIR + "ca_soldier", 1 + random(2));

    add_prop(ROOM_I_INSIDE,1);

    add_exit(CABASE_DIR + "wcor4", "north", 0, 0, 0);

    reset_room();
}

string
desc()
{
    write("Dozens of bunks lined up against the east and west walls " +
        "here mark this as sleeping quarters for some of the soldiers " +
        "who are serving here in the fortress at Cair Andros. A wide " +
        "space at the southern edge of the room has been cleared to " +
        "make room for an ancient and ornate sarcophagus sitting upon " +
        "a simple stone bier. The corridor you came in from is visible " +
        "through a wide opening in the north wall.\n");
}