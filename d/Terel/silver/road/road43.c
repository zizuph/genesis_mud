/* File         : /d/Terel/silver/forest/road43.c
 * Creator      : Pasqua
 * Date         : March 2006         
 * Purpose      : road file for Silver Forest.
 * Related Files: /d/Terel/silver/include/road_base.c
 * Comments     : Basic Silver forest road room.
 * Modifications: 
 */


#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"

inherit INCLUDE + "road_base";

int move_log(string str);
void close_way();
void open_way();
int open;

public void
create_room()
 
 {
    ::create_room();

	set_short("a road in the northern silver forest");
	 add_my_desc("@@extra_short");
	add_exit(ROAD + "road44", "east", 0);
    add_exit(ROAD + "road42", "west", "@@log_here@@", 0, 1);

    add_item(({"log", "wooden log"}), ("The log is placed in the middle of the road, " +
        "its purpose seem to be to block people from passing by.\n"));

    reset_room();
}

string extra_short()
{
	if(!open)
		return "A wooden log is placed in the middle of the road.\n";
	return "";
}

int
log_here()
{
    if (open)
        return 0;
    write("The log is in the way to proceed in that direction.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(move_log, "move");
}

int
move_log(string str)
{
    if(str != "log")
    {   
        write("Move what? the wooden log?\n");
        return 0;
    }
    write("You grab the log and push it to the side.\n");
    say(QCTNAME(TP)+" gets a good grip of the log and pushes it to the side.\n");
    open_way();

    return 1;
}

void
open_way()
{
    if(!open)
    {
        tell_room(TO,
            "As the log is gone its now possible to proceed westward!\n");
        open = 1;

        setuid();
        seteuid(getuid());
        
        (ROAD + "road42")->open_way();
        set_alarm(15.0, 0.0, &close_way());
    }
}

void
close_way()
{
    if (open)
    {
        tell_room(TO,"The log rolls back to its old position.\n");
        open = 0;

        (ROAD + "road43")->close_way();
    }
}
