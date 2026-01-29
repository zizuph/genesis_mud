inherit "/d/Emerald/ctower/room/ctower_base";

#include "../../ctower.h"
 
void
create_ctower_room()
{
    set_short("Crystal cavern");
   
    set_long("   A narrow walkway links a ledge at the cavern's " +
       "edge to a crystal platform to the north.  Looking down, " +
       "you can make out the jagged crystal formations that make " +
       "up the floor of the cavern thirty meters or more below you.\n");
   
    add_item(({ "ledge", "narrow ledge" }),
        "The narrow ledge extends out a short distance from the " +
        "cavern wall to the south.\n");

    add_item(({ "passage" }),
        "A narrow passge can be seen leading out of the cavern to " +
        "the south.\n");

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
        "At the northern end of the walkway, a small crystal platform " +
        "extends up " +
        "from the floor to your level.  From here, it looks large " +
        "enough for perhaps a single person to move about on.\n");

    add_item(({ "walkway", "narrow walkway" }),
        "The narrow walkway links a ledge at the cavern's " +
       "edge to a crystal platform to the north.\n");

    add_exit("cavern1", "south");
    add_exit("cavern3", "north");
}

int
jump(string str)
{
    string *arr = ({ "off of", "off", "down from" });

    if (!strlen(str) ||
        ((str != "down") &&
        !parse_command(str, ({}), "%p [the] 'walkway'", arr) &&
        !parse_command(str, ({}), "'down' 'to' [the] [crystal] 'floor'")))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    write("You jump off of the ledge, plummeting to your death.\n");
    say(QCTNAME(this_player()) + " jumps off the edge of the ledge!\n");

    this_player()->move_living("M", CTOWER_ROOM_ENTRY + "cavern_floor", 1, 1);
    
    this_player()->heal_hp(this_player()->query_hp());
    this_player()->do_die(this_object());

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
