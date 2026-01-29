/*
 * Temple of Myrkul
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit "/std/room";
inherit "/d/Faerun/std/cmd_parse";
inherit BASE_TEMPLE;
inherit CYRIC_DIR + "info";

#define MERE_DIR    "/d/Faerun/mere/rooms/"

void
create_room()
{
    ::create_room();
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Inside the temple of " + deity_name);
    set_long("This is the inside of the temple of " + deity_name + ". It is round and wide. A large altar sits in the center of the room. Next to the altar is an iron box. Wood remnants lay scattered around the floor, which used to be the ceiling. There is a sign on a wall to read.\n");

    add_item(({"altar"}),
        "It is a large stone block and set in the center of the temple. Dried blood stains the surface and sides of the altar. An iron box is set next to the altar.\n");
    add_item(({"stone blocks", "blocks"}),
        "They are pitted with age and cracked. The blocks are made of granite, rounded, and make up the walls. One large stone block makes up the altar.\n");
    add_item(({"walls"}),
        "They are made of stone blocks. The walls are rounded and pitted with age.\n");
    add_item(({"ceiling"}),
        "The ceiling is made of wood, but rotted with age. The ceiling has collapsed, leaving a large hole. Wood remnants lay scattered around the floor.\n");
    add_item(({"wood", "wood remnants"}),
        "The wood remnants lay scattered around the floor. They were once the ceiling, but have rotted away and fallen to the ground.\n");
    
    add_exit(MERE_DIR + "me26", "out");
}


void
init()
{
    ::init();

    add_action("insert","insert");
    add_action("insert","drop");
}
int
insert(string s)
{
    object token;

    FIXEUID;

    NF("Insert what into what?\n");
    if (!s) return 0;
    
    if(!parse_command(s,TO,"[platinum] 'coin' 'in' / 'into' [the] [iron] 'box'"))
        return 0;

    if(present(TOKEN_NAME,TP))
    {
       if(present(god_token, TP))
        {
            write("You are already worshipping this deity.\n");
            return 1;
        }
        else 
        {
            write("You can only worship one deity.\n");
            return 1;
        }
    }

    NF("You don't have any platinum coins.\n");
    

    if("/sys/global/money"->move_coins("platinum",1,TP,0))
        return 0;
  
    if(TP->query_alignment() > AL_EVIL)
    {
        write("The path you wander is not tolerated by this deity.\n" +
            "You cannot join.\n");
        say(QCTNAME(TP)+" donates a coin to the temple.\n");        
        return 1;
    }

    say(QCTNAME(TP)+" joins the the " + cult_type + " of " + deity_name + ".\n");
    write("You receive a " + adj1 + " " + adj2 + " " + emblem_name + ".\n");

    LOG_FILE("temples", "joined " + deity_name);

    token = clone_object(TEMPLE_DIR + emblem_file);
    token->move(TP);

    return 1;
}
