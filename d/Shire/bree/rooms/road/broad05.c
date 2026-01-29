/*
 * Road in Bree
 * By Finwe, June  2001
 *
 * Gates fixed 2010/07/25 Lavellan
 *
 * 2011/07/21 Lavellan - Changed to use stdgateroom, commented out redundant
 *                       stuff here
 */
 
#include "/d/Shire/sys/defs.h" 
#include "defs.h"

//inherit ROAD_BASE;
inherit "/d/Shire/bree/stdgateroom.c";

object human;
//int gatestate;  /* 0 = closed, 1 = open */

//string other_room, direction;

string
gate_desc()
{
//    if (gatestate) return "The gate is open. ";
//    else return "The gate is closed to keep villains out. ";
    string str;
    if (gatestate) str = "The gates are open. ";
    else str = "The gates are closed to keep villains out. ";
    return "Houses crowd both sides of the Great East Road. A " +
        "large gate is to the east, which allows travellers to enter " +
        "and leave Bree. " + str + "A large building stands to the north "+
        "and a square building sits to the south. The road runs northwest " +
        "and east towards the South Gate. A large, " +
        "dusty stone has been raised here, in honor of the great " +
        "wizards who formed the lands. \n";
}

void
//create_road_room()
create_gateroom()
{
    string str;
    
    set_areadesc("large busy road");
    set_area("inside the");
    set_areaname("South Gate");
    set_land("Bree");

/*    add_bree_desc("Houses crowd both sides of the Great East Road. A " +
        "large gate is to the east, which allows travellers to enter " +
        "and leave Bree. @@gate_desc@@A large building stands to the north "+
        "and a square building sits to the south. The road runs northwest " +
        "and east towards the South Gate. A large, " +
        "dusty stone has been raised here, in honor of the great " +
        "wizards who formed the lands. \n");*/
//    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    set_vbfc_extra(gate_desc);

    set_add_houses();
    set_add_ger();

//    add_item(({"gate", "gates"}), "@@my_gates");   
    add_item(({"gate", "gates", "south gate", "south gates"}), "@@my_gates");
    add_item(({"large building"}),
        "The large building sits north of the road. It appears to " +
        "be a busy place as the road to it is well used. A square " +
        "sign is attached to the front the of the building.\n");
    add_item(({"square building"}),
        "The square building sits off away from the road south of " +
        "here. It is one story and looks quiet. A round sign hangs " +
        "above the door.\n");
    add_item("square sign", "It is square, securely attached to the " +
        "front of the large building, and above the door.\n");
    add_item("round  sign", "It is round and hangs above the door " +
        "of the square building.\n");
    add_item(({"signs", "sign"}),
        "There are two signs above the buildings, a square sign and " +
        "a round sign.\n");

    add_cmd_item("square sign", "read", "@@read_square_sign@@");
    add_cmd_item("round sign", "read", "@@read_round_sign@@");

    reset_shire_room();

// Gotta love the old artifacts. ;)
    clone_object("/d/Genesis/obj/wizquest/mage_stone")->move(this_object());
    
//    other_room = ROAD_DIR + "sgate";
    set_other_room(ROAD_DIR + "sgate");
//    direction = "east";
    set_direction("east");

//    add_exit(ROAD_DIR + "sgate", "east");
    add_exit(TOWN_DIR + "hhouse1", "west");
    add_exit(ROAD_DIR + "broad04", "northwest");
    add_exit(TOWN_DIR + "shop", "north");
    add_exit(TOWN_DIR + "gem_shop", "south");

//  gatestate = 1;
    
}

/*init()
{
    ::init();
    add_action("knock", "knock");
    check_gates();
}*/

void
reset_shire_room()
{
    setuid();
    seteuid(getuid());

    if(!objectp(human))
    {
        human = clone_object(NPC_DIR + "human");
        human->move(TO);
        human->set_restrain_path("/d/Shire/bree");
        human->set_random_move(2);

    }
}

/*knock(string str) 
{
    if (str != "gates" && str != "gate" && str != "on the gates" &&
        str != "on the gate" && str != "on gates" && str != "on gate") return 0;
    check_gates();
    if (gatestate)
    {
        write("You knock in the air wildly, just to discover that " +
            "the gate is open.\n");
        return 1;
    }
    pass_msg();
    set_dircmd(str);
    this_player()->move_living(direction, other_room);
    return 1;
}

pass_msg() 
{
    write("You knock loudly on the gates to wake up the hobbit guard.\n");
    write("The gates open and a sleepy guard lets you pass.\n");
    say(QCTNAME(TP) + " knocks loudly on the gates.\n");
    say("The gates open and a sleepy guard lets " +
        HIM_HER(TP) + " pass.\n");
}

my_gates()
{
    string str;

    check_gates();
    str = "The gates of Bree are made of wood and seem strong. ";
    if (gatestate) str += "They are currently open, to let good folk in. ";
    else str += "They are currently closed, to keep ruffians out. ";
    str += "There is a sign. It says:\n"+
        "The Gates Open At 8 In The Morning And "+
         "Close At 10 In The Evening.";
    return break_string(str + "\n", 70) + "It's now " +
        CLOCK->query_time_of_day() + ".\n";
}

block() 
{
    check_gates();
    if (gatestate) write("You pass the gates.\n");
    else 
    {
        if (this_player()->query_wiz_level())
        {
            pass_msg();
            return 0;
        }
        write("You try desperately to get past the gates, but fail.\n");
        write("Maybe you should knock on the gates to wake up the guard...\n");
    }
    return !gatestate;
}

wizinfo() 
{
    string str;
    check_gates();
    str = gatestate ? "Open" : "Closed";
    return "Current game time:  " + CLOCK->query_time() + "\n"+
           "Gates open at:      08:00\n"+
           "Gates close at:     22:00\n"+
           "Current gate state: " + str + ".\n";
}

check_gates() 
{
    int hour;

    hour = CLOCK->query_hour();
    if (hour < 8 || hour >= 22) gatestate = 0;
    else gatestate = 1;
}

query_state() 
{ 
    return gatestate; 
}

set_other_room(string str)
{ 
    other_room = str; 
}

query_other_room()
{ 
    return other_room; 
}

set_direction(string str)
{ 
    direction = str; 
}

query_direction() 
{ 
    return direction; 
}*/
