inherit "/d/Emerald/ctower/room/ctower_base";
 
#include "../../ctower.h"

void
ctower_reset()
{
    if (!present("ctower_cube"))
    {
        setuid();
        seteuid(getuid());
        clone_object(CTOWER_OBJ + "cube")->move(this_object(), 1);
    }
}

void
create_ctower_room()
{
    set_short("Crystal cavern");
   
    set_long("   This small crystaline platform is barely large " +
       "enough to maneuver on.  Looking down, you can " +
       "make out the jagged crystal formations that make up the " +
       "floor of the cavern thirty meters or more below you.  " +
       "To the south, a walkway extends over to a small ledge " +
       "jutting out from the wall of the cavern.\n");
   
    add_item(({ "ledge", "narrow ledge" }),
        "The narrow ledge extends out a short distance from the " +
        "cavern wall to the south.\n");

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
        "A small crystal platform that extends up from the floor, " +
        "thirty meters or more below.\n");

    add_item(({ "walkway", "narrow walkway" }),
        "A narrow walkway that extends out to a ledge on the cavern " +
        "wall to the south.\n");

    add_exit("cavern2", "south");

    ctower_reset();
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
