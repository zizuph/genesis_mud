inherit "/d/Emerald/ctower/room/ctower_base";
 
#include "../../ctower.h"
 
int block();

void
create_ctower_room()
{
    set_short("Crystal cavern");
   
    set_long("   The crystaline passage ends in a narrow ledge " +
       "which overlooks a large cavern.  Looking down, you can " +
       "make out the jagged crystal formations that make up the " +
       "floor of the cavern thirty meters or more below you.  " +
       "Far off to the north, a small crystal platform extends " +
       "up from the floor to your level.\n");
   
    add_item(({ "passage", "crystaline passage" }),
        "The short passage leads back into a study.\n");

    add_item(({ "ledge", "narrow ledge" }),
        "The narrow ledge is barely large enough for one person to " +
        "stand on.  Looking over the edge, you can see the crystaline " +
        "floor far below.\n");

    add_item(({ "floor", "crystaline floor" }),
        "Millions of crystal formations make up the floor of the " +
        "cavern.  There doesn't seem to be any safe way to climb " +
        "down to the floor, and jumping off the ledge would surely " +
        "be deadly.\n");

    add_item(({ "cavern", "large cavern", "wall", "walls", "ceiling" }),
        "A truly huge cavern opens up before you.  Composed entirely " +
        "of crystal, the walls, ceiling, and floor reflect the light " +
        "in a brilliant array of colours.\n");

    add_item(({ "platform", "small platform", "crystal platform",
        "small crystal platform" }),
        "Far off to the north, a small crystal platform extends up " +
        "from the floor to your level.  From here, it looks large " +
        "enough for perhaps a single person to move about on.  There " +
        "doesn't seem to be any way to climb to it, though.\n");

    add_exit("study3", "south", block);
}

void
close_fireplace()
{
    (CTOWER_ROOM_ENTRY + "study3")->close_fireplace();
}

int block()
{
    set_alarm(0.0, 0.0, close_fireplace);
    return 0;
}

int
jump(string str)
{
    string *arr = ({ "off of", "off", "down from" });

    if (!strlen(str) ||
        ((str != "down") &&
        !parse_command(str, ({}), "%p [the] 'ledge' / 'edge'", arr) &&
        !parse_command(str, ({}), "'down' 'to' [the] [crystal] 'floor'")))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    write("You jump off of the ledge, but instead of plummeting to " +
        "your death, you land on an elevated walkway which extends " +
        "to the platform to the north.  Strange...you are sure this " +
        "walkway wasn't here before.\n");
    say(QCTNAME(this_player()) + " jumps off the edge of the ledge!\n");

    this_player()->move_living("M", CTOWER_ROOM_ENTRY + "cavern2", 1);

    return 1;
}

void
init()
{
    ::init();

    add_action(jump, "jump");
    add_action(jump, "leap");
    add_action(jump, "dive");
}
