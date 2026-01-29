/*
 * Temple of Lathander
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
inherit LATH_DIR + "info";

#define ROOM_DIR    "/d/Faerun/leilon/rooms/"

void
create_room()
{
    ::create_room();
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Inside the temple of " + deity_name);
    set_long("This is the inside of the temple of " + deity_name + ". It is made from pink marble which has been polished and sparkles in the " + LIGHT_DESC + ". The ceiling rises high overhead. Large windows are set in regular intervals in the walls. A large altar sits at one end of the room. Next to the altar is an iron box. There is a sign on a wall to read.\n");

    add_item(({"altar"}),
        "It is a large stone block and set in the center of the temple. It is made from white marble and glows in the " + LIGHT_DESC + ". An iron box is set next to the altar.\n");
    add_item(({"pink marble"}),
        "It is shades of pink with veins of off white running through the stone. It has been polished and gleams in the " + LIGHT_DESC + ".\n");
    add_item(({"walls"}),
        "They are made of blocks of pink marble. The walls are polished smooth and rise above you. Set in the walls are large windows.\n");
    add_item(({"ceiling"}),
        "The ceiling arches overhead and is crowned with a large dome. Windows are set in the dome at regular intervals. illuminating the temple below.\n");
    add_item(({"windows"}),
        "They are set in the walls and in the dome panels above. The are long and rectangular shaped and topped with half circle windows.\n");
    add_item(({"white marble"}),
        "The marble is white with black and grey veins. The marble is polished smooth and gleams in the light. It is used in the altar and the floor.\n");
    add_item(({"floor"}),
        "It is clean and made of white marble blocks. The blocks of stone are polished and laid into the ground in a diagonal herringbone pattern.\n");
    add_item(({"dome"}),
        "The dome crowns the ceiling. It is made of pink marble blocks and set with windows in its panels.\n");
    
    
    add_exit(ROOM_DIR + "rd07", "northeast");
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
  
    if(TP->query_alignment() < AL_NEUT_GOOD)
    {
        write("The path you wander is not tolerated by this deity.\n" +
            "You cannot join.\n");
        say(QCTNAME(TP)+" donates a coin to the temple.\n");        
        return 1;
    }

    say(QCTNAME(TP)+" joins the the " + cult_type + " of " + deity_name + ".\n");
    write("You receive a " + adj1 + " " + adj2 + " " + emblem_name + ".\n");

    token = clone_object(TEMPLE_DIR + emblem_file);
    token->move(TP);

// dont log wizards joining
    if (this_player()->query_wiz_level()) return 1;

    LOG_FILE("temples", "joined " + deity_name);


    return 1;
}
