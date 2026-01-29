
/*
 * Written by Quis for the Goblin Start Area 920516
 */

#pragma save_binary

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "../goblins.h"

#define START_CONNECT "/d/Genesis/start/human/wild2/top5"

static object guard1, guard2, guard3;

void reset_room();

void
create_room()
{
    ::create_room();

    change_prop(ROOM_I_INSIDE,0);
    change_prop(ROOM_I_LIGHT,1);

    add_prop(ROOM_I_NO_MAGIC_ATTACK,"@@block_attack");
    add_prop(ROOM_I_NO_ATTACK,"@@block_attack");
    add_prop(ROOM_I_NO_STEAL,"@@block_attack");

    set_short("Outside the goblin caverns");
//    set_long(break_string(
//        "This is the northern end of a box canyon. " +
///*
//        "You can climb off the beaten path to the east or west, " +
//*/
//        "or you can follow the broad trail leading south. " +
//        "You see a cavern entrance to the north. " +
//        "There is a badly painted sign here. " +
//        "You have an uneasy feeling that you are being watched. " +
//        "\n\n",70));

    set_long("This is the northern end of a box canyon. " +
        "You can follow the broad trail leading south. " +
        "You see a cavern entrance to the north. " +
        "There is a badly-painted sign here. " +
        "You have an uneasy feeling that you are being watched.\n");


    add_exit(GOBLIN_CAVERN_DIR + "entrance2","north",0,0);
    add_exit(START_CONNECT,"south",0,1);

    //      Understandable if you didn't have write access to the destination
    //      and didn't want to talk to someone who did...  
    /*START_CONNECT->add_my_desc("A narrow gorge leads north from here.\n");
    START_CONNECT->add_exit(GOBLIN_CAVERN_DIR + "entrance1", "north", 0, 1);
    START_CONNECT->change_prop(ROOM_I_NO_CLEANUP, 1);
    change_prop(ROOM_I_NO_CLEANUP, 1);*/

    add_item(({"sign"}),BSN("The sign is quite dilapidated.  There is a " +
        "message on it for all to read."));
    add_cmd_item(({"sign"}), "read", "@@read_sign");
    add_item(({"canyon"}),"You see nothing special\n");
    add_item(({"cavern","entrance"}),"The cavern looks very, very dark.\n");
    reset_room();
}

void
reset_room()
{
    if (!guard1 || !present(guard1, this_object())) {
        guard1 = clone_object(GOBLIN_NPC_DIR + "guard");
        guard1->move_living("south", this_object());
    }

    if (!guard2 || !present(guard2, this_object())) {
        guard2 = clone_object(GOBLIN_NPC_DIR + "guard");
        guard2->move_living("south", this_object());
    }

    if (!guard3 || !present(guard3, this_object())) {
        guard3 = clone_object(GOBLIN_NPC_DIR + "guard");
        guard3->move_living("south", this_object());
    }
}

int
read_sign()
{
    write("Bwhere de mity Goblin King! [sic]\n\n" /* +
        "If youse leave da canyon, " +
        "prob get lost! Lotsa junk south tho.\n"*/);
    return 1;
}

//int
string
block_attack()
{
  //write(BSN("You don't want to break the armed truce with these goblins."));
  return("You don't want to break the armed truce with these goblins.\n");
  //return 1;
}
