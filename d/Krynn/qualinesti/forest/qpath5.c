/* qpath5.c
 * Somewhere in the Qualinesti forest.
 *
 * Blizzard, 01/2003 
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include "../local.h"

inherit  FORESTBASE;

#include "stream_drink.h"

#define  IN_STREAM  "_in_stream"
int      enter_stream(string arg);
int      exit_check();
int      check_stream();

object   animal;

void
reset_qualinesti_room()
{
    if ( !animal )
    {
        animal = clone_object(NPC + "stag");
        animal->add_act("emote lowers his head and drinks some water from " +
            "the stream."); 
        animal->move(TO, 1);
    }
}

void
create_forest()
{
    set_long_desc("Standing in a shallow stream you feel the cold water " +
        "refreshing your feet. The trees to the west are not growing so " +
        "densely and you can see a bit further from here. Again, you " +
        "notice a path leading in that direction."); 
    add_my_desc("\n");
    
    add_item("stream",
        "The water in the stream flows gently, here and there producing " +
        "some bubbles. To the northeast it would be possible to use it " +
        "as a path, but in the other direction it dissapears under a thick " +
        "mass of bushes and branches.\n");
    add_item("path",
        "After leaving the stream you once again notice a path leading " +
        "westwards through the forest.\n");
    add_item("water",
        "The clear and refreshingly cold water flows gently through the " +
        "forest.\n");
    
    add_cmd_item(({"stream", "water", "from stream", "cold water"}),
        "drink", "@@drink_water");
        
    OUTSIDE;
    add_prop(OBJ_I_CONTAIN_WATER, -1);

    set_up_herbs( ({ GOHERB + "attanar", GOHERB + "suranie" }), 
        ({ "growth", "forest", "herb growth", }), 3);
    
    add_exit(FDIR + "qpath4.c", "northeast", "@@exit_check", 2);
    add_exit(FDIR + "qpath6.c", "west", "@@check_stream", 2);

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
        write("You enter the stream.\n");
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
        write("You will have to use the stream as a path.\n");
        return 1;
    }
        
    return 0;
}

int check_stream()
{
    if ( TP->query_prop(IN_STREAM) )
    {
        write("You step out of the stream and leave west.\n");
        tell_room(TO, QCTNAME(TP) + " steps out of the stream and leaves " +
            "west.\n", TP);
        TP->remove_prop(IN_STREAM);
    }
    
    return 0;
}

        

        