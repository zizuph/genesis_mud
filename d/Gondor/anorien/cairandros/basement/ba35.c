/*
 * Basement in Cair Andros
 * /d/Gondor/anorien/cairandros/basement/ba35.c
 *
 * Varian - March, 2020
 */

#pragma strict_types

#include "../../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>

inherit ANORIEN_STD_DIR + "bsmt_base";

/* 
 * Tasks tend to range from simple (200) to impossible (1400)
 * A combination of ATTRIBUTE_1 + ATTRIBUTE_2 + Dexterity = 100
 * would succeed on a simple task 100% of the time but would
 * fail on an impossible task 100% of the time. But it would
 * succeed about 2% of the time on a formidable (1100) task
 * range.
 *
 * Because player stats vary so widely on Genesis, we don't
 * want a stat to unbalance it too much. We are going to only
 * use XDEX% of the player dexterity and then use the two skills
 * defined in ATTRIBUTE_1 and ATTRIBUTE_2
 *
 * Given current stats in Genesis, the original % of XDEX will
 * be 5%. That might change if there is a stat nerf in the
 * future.
 *
 * Varian - March, 2020
 */

#define ATTRIBUTE_1 52 /* acrobat skill, aka, SS_ACROBAT */
#define ATTRIBUTE_2 108 /* hunting skill, aka, SS_HUNTING */
#define XDEX 5 /* Only 5% of dexterity counts towards the task! */
#define TASK_BULLSEYE 1000 
#define TASK_BLUE 900
#define TASK_ORANGE 800
#define TASK_GREEN 700
#define TASK_RED 600
#define TASK_YELLOW 500
#define TASK_PURPLE 400
#define TASK_BLACK 300

int do_dart(string str);
int do_grab(string str);
int do_throw(string str);

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
        "you can reach it by going through the opening in the south " +
        "wall.\n");
    add_item( ({"east", "east wall", "eastern wall"}),
        "Much like the western wall, there are several beds lined " +
        "up against the stone blocks of the eastern wall. The beds " +
        "are really not much more than pallets, wooden boxes " +
        "filled with straw covered with a thick layer of linen.\n");
    add_item( ({"south", "southern wall", "south wall", "opening",
            "wide opening"}),
        "The southern wall has been left fairly plain, distinguished " +
        "only by single wide opening which leads into the hallway " +
        "beyond.\n");
    add_item( ({"north", "north wall", "northern wall"}),
        "A circular wooden board has been painted with different " +
        "coloured rings and hung upon the northern wall here.\n");
    add_item( ({"west", "west wall", "western wall"}),
        "Much like the eastern wall, there are several beds lined " +
        "up against the stone blocks of the western wall. The beds " +
        "are really not much more than pallets, wooden boxes " +
        "filled with straw covered with a thick layer of linen.\n");
    add_item( ({"bunk", "bunks", "bed", "beds", "pallet", "pallets"}),
        "The beds in here have been lined up against both the " +
        "east and west walls. The beds themselves are sturdy " +
        "wooden boxes which have been filled with straw and then " +
        "covered with a thick linen blanket. They don't look " +
        "overly comfortable, but they would certainly be preferable " +
        "to sleeping on the stone floor.\n");
    add_item( ({"board", "circular board", "circular wooden board",
            "wooden board", "dart board", "dartboard"}),
        "This wooden board has been cut into a circular shape and " +
        "has many different rings raditing out from the center, " +
        "each painted a unique colour. There are several darts " +
        "stuck into the board, and it appears that some of the " +
        "soldiers engage in dart-throwing during their downtime.\n");
    add_item( ({"ring", "rings", "painted ring", "painted rings",
            "bullseye", "target"}),
        "The board has been painted in eight different colours. " +
        "There is a white circle in the middle and seven different " +
        "rings, each grown progressively larger.\nFrom smallest to " +
        "largest, the rings are blue, orange, green, red, yellow, " +
        "purple and the last ring at the edge of the board " +
        "is black.\n");
    add_item( ({"dart", "darts"}),
        "There are several darts here, you could grab one and " +
        "throw it at the board if you wanted.\n");

    set_no_exit_msg( ({"northwest", "northeast", "southwest",
            "southeast", "east", "north", "west"}),
        "Those walls sure are solid! You will have to try moving in " +
        "a different direction.\n");

    add_npc(CA_NPC_DIR + "ca_officer");
    add_npc(CA_NPC_DIR + "ca_soldier", 1 + random(2));

    add_prop(ROOM_I_INSIDE,1);

    add_exit(CABASE_DIR + "ecor4", "south", 0, 0, 0);

    reset_room();
}

string
desc()
{
    write("You are in the barracks which sprawl across the lower " +
        "levels of Cair Andros. These particular quarters boast " +
        "rows of simple pallets lined up along the eastern and " +
        "western walls, providing adequate bunks for the soldiers " +
        "to sleep in when they take their rest. The northern " +
        "wall has a circular piece of wood painted in many " +
        "different colours, and the corridor you came in from " +
        "is visible through the wide opening in the southern wall.\n");
}

public int
do_dart(string str)
{
    if(!strlen(str))
    {
        notify_fail("What are you trying to do?\n");
        return 0;
    }

    if((str != "the dart") && (str != "a dart") && (str != "dart"))
    {
        notify_fail("Grabba???\n");
        return 0;
    }

    if (this_player()->resolve_task(TASK_BULLSEYE, 
        ({SKILL_WEIGHT, XDEX, TS_DEX, SKILL_END,
            ATTRIBUTE_1, ATTRIBUTE_2})) > 0)
    {
        set_alarm(2.0, 0.0, &write("You hit the white circle in " +
            "the middle of the board! Bullseye!\n"));
        set_alarm(2.0, 0.0, &SAYBB(" throws a dart and hits the " +
            "white circle in the middle of the board! Bullseye!"));
        return 1;
    }

    if (this_player()->resolve_task(TASK_BLUE, 
        ({SKILL_WEIGHT, XDEX, TS_DEX, SKILL_END,
            ATTRIBUTE_1, ATTRIBUTE_2})) > 0)
    {
        set_alarm(2.0, 0.0, &write("You hit the tiny blue ring " +
            "beside the bullseye!\n"));
        set_alarm(2.0, 0.0, &SAYBB(" throws a dart and hits the tiny " +
            "blue ring beside the bullseye!"));
        return 1;
    }

    if (this_player()->resolve_task(TASK_ORANGE, 
        ({SKILL_WEIGHT, XDEX, TS_DEX, SKILL_END,
            ATTRIBUTE_1, ATTRIBUTE_2})) > 0)
    {
        set_alarm(2.0, 0.0, &write("You hit the small orange ring " +
            "near the middle!\n"));
        set_alarm(2.0, 0.0, &SAYBB(" throws a dart and hits the " +
            "small orange ring near the middle!"));
        return 1;
    }

    if (this_player()->resolve_task(TASK_GREEN, 
        ({SKILL_WEIGHT, XDEX, TS_DEX, SKILL_END,
            ATTRIBUTE_1, ATTRIBUTE_2})) > 0)
    {
        set_alarm(2.0, 0.0, &write("You hit the green ring " +
            "somewhat close to the middle!\n"));
        set_alarm(2.0, 0.0, &SAYBB(" throws a dart and hits the " +
            "green ring somewhat close to the middle!"));
        return 1;
    }

    if (this_player()->resolve_task(TASK_RED, 
        ({SKILL_WEIGHT, XDEX, TS_DEX, SKILL_END,
            ATTRIBUTE_1, ATTRIBUTE_2})) > 0)
    {
        set_alarm(2.0, 0.0, &write("You hit the large red ring " +
            "halfway to the middle!\n"));
        set_alarm(2.0, 0.0, &SAYBB(" throws a dart and hits the " +
            "large red ring halfway to the middle!"));
        return 1;
    }

    if (this_player()->resolve_task(TASK_YELLOW, 
        ({SKILL_WEIGHT, XDEX, TS_DEX, SKILL_END,
            ATTRIBUTE_1, ATTRIBUTE_2})) > 0)
    {
        set_alarm(2.0, 0.0, &write("You throw the dart and " +
            "hit the large yellow ring approaching the edge " +
            "of the board.\n"));
        set_alarm(2.0, 0.0, &SAYBB(" throws a dart and hits the " +
            "large yellow ring approaching the edge of the " +
            "board."));
        return 1;
    }

    if (this_player()->resolve_task(TASK_PURPLE, 
        ({SKILL_WEIGHT, XDEX, TS_DEX, SKILL_END,
            ATTRIBUTE_1, ATTRIBUTE_2})) > 0)
    {
        set_alarm(2.0, 0.0, &write("You hit the wide purple ring " +
            "near the edge of the board!\n"));
        set_alarm(2.0, 0.0, &SAYBB(" throws a dart and hits the " +
            "wide purple ring near the edge of the board!"));
        return 1;
    }

    if (this_player()->resolve_task(TASK_BLACK, 
        ({SKILL_WEIGHT, XDEX, TS_DEX, SKILL_END,
            ATTRIBUTE_1, ATTRIBUTE_2})) > 0)
    {
        set_alarm(2.0, 0.0, &write("You throw the dart and " +
            "hit the black ring on the edge of the board.\n"));
        set_alarm(2.0, 0.0, &SAYBB(" throws a dart and hits the " +
            "black ring on the edge of the board."));
        return 1;
    }

    set_alarm(2.0, 0.0, &write("You try your best to hit " +
        "the board with your dart, but unfortunately it hits " +
        "the stone wall and falls to the floor.\n"));
    set_alarm(2.0, 0.0, &SAYBB(" throws a dart at the board, " +
        "but misses!"));
        return 1;
}

public int
do_grab(string str)

{
    if(!strlen(str))
    {
        notify_fail("What did you want to grab?\n");
        return 0;
    }

    if((str != "dart") && (str != "a dart") &&
        (str != "darts") && (str != "the dart") && 
        (str != "the darts"))
    {
        notify_fail("Grab what? A dart?\n");
        return 0;
    }

    write("You grab a dart and aim carefully at the board.\n");
    SAYBB(" grabs a dart and aims it at the board.");
    this_player()->command("grabba dart");    

    return 1;
}

public int
do_throw(string str)

{
    if(!strlen(str))
    {
        notify_fail("What did you want to throw?\n");
        return 0;
    }

    if((str != "dart") && (str != "a dart") &&
        (str != "darts") && (str != "the dart") && 
        (str != "the darts"))
    {
        notify_fail("Throw what? A dart?\n");
        return 0;
    }

    write("You have to grab a dart first in order to throw it!\n");

    return 1;
}

public void
init()
{   
    ::init();
    add_action(do_dart, "grabba");
    add_action(do_throw, "throw");
    add_action(do_grab, "grab");
}