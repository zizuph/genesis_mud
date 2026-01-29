/* qpath4.c.c
 * Somewhere in the Qualinesti forest.
 *
 * Blizzard, 01/2003 
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include "../local.h"

inherit   FORESTBASE;

#include "stream_drink.h"

#define  IN_STREAM    "_in_stream"

int      enter_stream(string arg);
int      exit_check();
int      check_stream();

object  dog1, dog2;

void
reset_qualinesti_room()
{
    if ( !dog1 )
    {
        dog1 = clone_object(NPC + "dog");
        dog1->move(TO, 1);
    }
    
    if ( !dog2 )
    {
        dog2 = clone_object(NPC + "dog");
        dog2->move(TO, 1);
    }
}

void
create_forest()
{
    set_long_desc("The path suddenly ends and the forest creates a small " +
        "clearing here. It does not look like someone created it, but you " +
        "wonder what the trail was made for. There is a stream southwest " +
        "of here. Maybe those elves use this place just as a source of " +
        "clear water.");
    add_my_desc("\n");
    
    add_item("stream",
        "The water is clear and cold. There are also some " +
        "footprints on the ground leading towards the stream.\n" ); 
    add_item("path",
        "The path ends here and it seems you may only go back from this " +
        "place.\n");
    add_item("clearing",
        "You find yourself standing in a small clearing. There is a stream " +
        "cutting the forest to the southwest.\n");
    add_item("water",
        "The water is clear and cold. You think you could drink some of it.\n");
    
    add_cmd_item(({ "stream", "from stream", "from small stream", "water"}),
        "drink", "@@drink_water");
        
    OUTSIDE;
    add_prop(OBJ_I_CONTAIN_WATER, -1);

    set_up_herbs( ({ GOHERB + "attanar", GOHERB + "suranie" }), 
        ({ "growth", "forest", "herb growth", }), 3);

    add_exit(FDIR + "qpath5.c", "southwest", "@@exit_check", 2);
    add_exit(FDIR + "qpath3.c", "east", "@@check_stream", 2);

    reset_qualinesti_room();
}

void
init()
{
    ::init();
    add_action(enter_stream, "enter");
}

int
enter_stream(string arg)
{
    if ( arg != "stream" && arg != "water" )
    {
        notify_fail("Enter what?\n");
        return 0;
    }
    
    if ( !TP->query_prop(IN_STREAM) )
    {
        write("You enter the stream and realize it is possible to use it " +
            "as a path leading towards southwest.\n");
        tell_room(TO, QCTNAME(TP) + " enters the stream.\n", TP);
        TP->add_prop(IN_STREAM, 1);
    
        return 1;
    }
    
    notify_fail("You are standing in the water already.\n");
    return 0;
        
}

int
exit_check()
{
    if ( !TP->query_prop(IN_STREAM) )
    {
        write("There is no path leading in that direction.\n");
        return 1;
    }
    
    return 0;
}

int check_stream()
{
    if ( TP->query_prop(IN_STREAM) )
    {
        write("You step out of the stream and follow the trail leading " +
            "east.\n");
        tell_room(TO, QCTNAME(TP) + " steps out of the stream and leaves " +
            "east.\n", TP);
        TP->remove_prop(IN_STREAM);
    }
    
    return 0;
}
        

        
