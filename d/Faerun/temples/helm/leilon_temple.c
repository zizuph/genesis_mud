/*
 * Temple of Helm
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
inherit HELM_DIR + "info";

#define ROOM_DIR    "/d/Faerun/leilon/rooms/"

void
create_temple()
{
    ::create_temple();
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Inside the shrine of " + deity_name);
    set_long(query_short() + ". Smaller than a temple, it is clean and square shaped. A large altar sits in the center of the room and where followers may pray at. Next to the altar is an iron box. Behind the altar is a large, full set of armour. There is a sign on a wall.\n");

    add_item(({"altar"}),
        "It is a large stone block and set in the center of the shrine and dedicated to " + deity_name + ". A feeling emanates from it, urging you to worship or pray before it. The altar is clean and has an iron box is set next to it.\n");
    add_item(({"stone blocks", "blocks"}),
        "They made of granite and squared and make up the walls, floor, and ceiling. One large stone block sits in the center of the temple makes up the altar.\n");
    add_item(({"walls"}),
        "They are made of stone blocks and very clean. Hanging on the wall is a sign.\n");
    add_item(({"floor", "ground"}),
        "It is swept clean and made of stone blocks. Set in the center of the floor is an altar, and behind the altar is a full set of armour.\n");
    add_item(({"full set of armour"}),
        "It is set behind the altar and represents the god Helm. The armour is polished and gleams in the light.\n");
    add_item(({"ceiling"}),
        "It is clean and made of stone blocks.\n");
    
    add_exit(ROOM_DIR + "rd05", "west");
}


void
init()
{
    ::init();

    add_action("insert","insert");
    add_action("insert","drop");
    add_action("pray","pray");
    add_action("pray","worship");

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

int
pray()
{
    write("You kneel and say a prayer to " + deity_name + ". The altar suddenly feels warm. After a moment it cools, you stand up, and back away from it.\n"); 
    say(QCTNAME(TP) + " kneels and says a prayer at the altar. After a few moments, " + HE_SHE(TP) + " stands up and backs away from it.\n");
    return 1;
}
