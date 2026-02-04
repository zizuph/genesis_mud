/*
 *  Big Rock, Basement
 *  Coded by Shinto 101399
 *
 */

#include "/d/Terel/include/Terel.h"

inherit STDROOM;
#include <macros.h>
#include <ss_types.h>

#define HOLE CALATHIN_DIR + "pubs/big_hole"
int hole;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
/*
    "/d/Terel/calathin/pubs/big_hole"->spank_me();
*/
    set_short("Basement of the Big Rock Pub");
    set_long("The basement is dark and damp. Water drips from the "+
                   "walls in various places. A large number of barrels are "+
                   "stacked on some rocks to keep them dry. A single torch "+
                   "lights the room from the staircase.\n");

    add_item(({"wall","walls"}), "The walls are made of stone, "+
             "but water seems to be seeping through some of the cracks.\n");
    add_item(({"stair","stairs","stairway"}), "A stone stairway leading "+
             "back upstairs.\n");
    add_item(({"barrel","barrels"}), "There are five different barrels filled "+
             "with different drinks that are served in the pub. Large wooden "+
             "barrels that hold quite a bit of liquid.\n");
    add_item(({"rock","rocks","stone","stones"}), "The stones are used to "+
             "keep the barrels off the damp ground.\n");
    add_item("torch","The torch rests in a small notch on the wall.\n");
    add_item(({"first barrel","second barrel","third barrel", "fourth barrel",
        "fifth barrel" }), "A sturdy barrel filled with some brew of sorts.\n");
//
/*
    add_cmd_item("third barrel", "lift", "@@lift");
    add_cmd_item(({"barrel", "second barrel","fourth barrel", "fifth barrel"}), 
             "lift","@@lift_fail");
    add_cmd_item("barrel","replace","@@replace");
*/
    INSIDE;
    add_exit(CALATHIN_DIR +"pubs/big_pub", "up",0);
    hole = 0;
    reset_room ();
}


int
lift_fail()
{
    write("You try to lift the barrel but it won't move.\n");
    say(QCTNAME(TP) + " attempts to lift the barrel but it won't move.\n");
    return 1;
}

    
int
lift()
{
    if(hole)
    {
        write("The barrel has already been moved.\n");
        return 1;
    }

    //Small races can't lift the barrel
    if(TP->query_race_name() == "hobbit" || 
        TP->query_race_name() == "goblin" ||
        TP->query_race_name() == "gnome" ||
        TP->query_race_name() == "kender")
    {
        write("You try to lift the barrel but it won't move.\n");
        say(QCTNAME(TP) +" attempts to lift the barrel but it won't move.\n");
        return 1;
    }
    //a strength requirement to lift the barrel
    if(TP->query_stat(SS_STR) >= 100 + random(20))
    {
        write("You lift the barrel up and lean it against the wall.\n");
        say(QCTNAME(TP) +" lifts the barrel up and leans it against the wall.\n");
        tell_room(TO, "Beneath the barrel was a small hole.\n");
        hole = 1;
        TO->add_exit(CALATHIN_DIR + "pubs/big_hole", "down", "@@block");
        find_object(HOLE)->add_exit(CALATHIN_DIR + "pubs/big_base", "up", 0);
        set_alarm(15.0, -1.0, "reset_room");
        return 1;
    }

    write("You try to lift the barrel but it won't move.\n");
    say(QCTNAME(TP) +" attempts to lift the barrel but it won't move.\n");
    return 1;
}

int
replace()
{
    if(!hole)
    {
        write("The barrel is already in place.\n");
        return 1;
    }

    //Small races can't replace the barrel.
    if(TP->query_race_name() == "hobbit" || 
        TP->query_race_name() == "goblin" ||
        TP->query_race_name() == "gnome" ||
        TP->query_race_name() == "kender")
    {
        write("You can't manage to lower the barrel back into place.\n");
        say(QCTNAME(TP) + " can't manage to lower the barrel back into place.\n");
        return 1;
    }

    //a strength requirement to replace the barrel.
    if(TP->query_stat(SS_STR) >= 100 + random(20))
    {
        write("You slowly lower the barrel back into place on the stones.\n");
        say(QCTNAME(TP) + " slowly lowers the barrel back into place on the stones.\n");
        TO->remove_exit("down");
        hole = 0;
        find_object(HOLE)->remove_exit("up");
        return 1;
    }
    write("You can't manage to lower the barrel back into place.\n");
    say(QCTNAME(TP) + " can't manage to lower the barrel back into place.\n");
    return 1;
}

int
block()
{
    //Small races can fit down the hole.
    if(TP->query_race_name() == "hobbit" || 
        TP->query_race_name() == "goblin" ||
        TP->query_race_name() == "gnome" ||
        TP->query_race_name() == "kender")
    {
        write("Due to your dimunitive size you are able to slip down the hole.\n");
        say(QCTNAME(TP) + " slips easily through the small hole.\n");
        return 0;
    }
    //Big races cannot.
    write("You're just too big to fit down that small hole.\n");
    say(QCTNAME(TP) + " is too big to fit down that small hole.\n");
    return 1;
}

int
query_hole()
{
    return hole;
}

void
reset_room()
{
    if(hole = 1)
    {
        TO->remove_exit("down");
        find_object(HOLE)->remove_exit("up");
        hole = 0;
        tell_room(TO, "The barrel falls slamming back onto it's stand.\n");
        return;
    }
    return;
}
