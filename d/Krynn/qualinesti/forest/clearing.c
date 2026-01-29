
/* File name  : clearing.c
 * Description: A clearing in the Qualinesti forest.
 *
 * Blizzard, 14.03.2004 
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include "../local.h"

inherit  FORESTBASE;
#include "stream_drink.h"

object   animal, animal2, animal3;

void
reset_qualinesti_room()
{
    if ( !animal )
    {
        animal = clone_object(NPC + "dog");
        animal->move(TO, 1);
    }

    if ( !animal2 )
    {
        animal2 = clone_object(NPC + "dog");
        animal2->move(TO, 1);
    }

    if ( !animal3 )
    {
        animal3 = clone_object(NPC + "dog");
        animal3->move(TO, 1);
    }
}

public string
do_enter_stream(string where)
{
    if ( (TP->query_race() == "hobbit") || (TP->query_race() == "gnome") ||
         (TP->query_race() == "dwarf") )
    {
        write("You enter the stream and carefully but steadily " +
            "force your way through the low-growing bushes. They " +
            "scratch your face and arms.\n");
        TP->heal_hp(-50);
        
    }
    else
    {
        write("You enter the stream and almost crawling in the water " +
            "you force your way through the bushes. The low-growing " +
            "branches scratch your face and arms.\n");
        TP->heal_hp(-100);
    }

    if ( TP->query_hp() <= 0 )
    {
        say(QCTNAME(TP) + " enters the stream and attempts to force " +
            HIS(TP) + " way through the bushes, but the low-growing " +
            "branches badly scratch his body.\n");
        TP->do_die(TO);

        return "";
    }
        
    say(QCTNAME(TP) + " slowly enters the stream.\n");
    TP->move_living("through the bushes", FDIR + "forest7", 0, 0);

    return "";

}

public string
do_climb_tree(string where)
{
    if ( TP->query_skill(SS_CLIMB) < 10 )
    {
        write("It seems to be too difficult for you. You feel much better " +
            "standing firmly on the ground.\n");
        return "";
    }
    
    write("Using the strong branches as a grip, you climb up the small " +
        "apple tree.\n");
    TP->move_living("climbing up the small apple tree", FDIR + "apple_tree",
        0, 0);

    return "";
}  

void
create_forest()
{
    set_long_desc("You are standing at the bank of a shallow stream " +
        "that circles among trees. The forest creates a small clearing " +
        "as the area is not so thickly wooded here. You notice a lone " +
        "apple tree growing just next to the stream.");
    add_my_desc("\n");
    
    add_item(({ "stream", "water", "river" }), "The shallow, bubbling " +
        "stream that circles among trees from the north to the south. " +
        "It is quite shallow and even a crawling person would not be " +
        "covered by the water.\n");
    add_item(({ "bank", "river bank" }), "You are standing at the bank " +
        "of a shallow stream. Several small footprints are leading towards " +
        "the water.\n");
    add_item(({ "apple tree", "small tree", "lone tree" }), "A lone apple " +
        "tree with low hanging branches is standing here. You probably " +
        "could climb on it.\n");
    add_item(({ "trees", "area" }), "The trees are not growing so thickly " +
        "here and create a small clearing. There is a small, lone apple tree " +
        "growing just next to the stream. Its branches hang low above the " +
        "surface of the water.\n");
         
    OUTSIDE;
    add_prop(OBJ_I_CONTAIN_WATER, -1);

    add_cmd_item(({ "water", "stream", "river" }), "enter",  
        do_enter_stream);
    add_cmd_item(({ "stream", "water", "from stream" }), "drink", 
        drink_water);
    add_cmd_item(({ "small tree", "apple tree", "lone tree" }), "climb", 
        do_climb_tree);

    reset_qualinesti_room();

}

