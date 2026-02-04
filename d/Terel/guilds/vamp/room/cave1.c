/*
 * Cave entrance to vampire guild
 * Louie 2006
 *
 * Modified: Novo 2008
 */
#pragma strict_types
#include "defs.h"

inherit ROOM_DIR + "vamp_room";

#include <stdproperties.h>
#define CRYPT_ROOM (ROOM_DIR+"crypt")

//proto
int do_climb(string str);
void 
reset_room()
{
    if(!random(4))
        clone_object(NPC_DIR +"isabella")->move(TO);
}

void
create_vamp_room()
{
    set_short("cave");
    set_long("You are deep within a cave in the cliff rock.  "+
        "The air and stone around you hold the faintest "+
        "vibration, a melodic thrum that pulses, heart-like "+
        "around you.  "+        
        "To the west a tunnel declines towards the scent and "+
        "sound of water.  "+
        "Where the cave ends to the east the ceiling lowers, "+
        "and you can see large hole opening into unremitting "+
        "darkness.  "+
        "\n");

    add_item(({"hole","large hole","up","opening","darkness","ceiling"}),
        "The hole in the ceiling of the cave looks large enough "+
        "for a horse or an ogre to pass through.  "+
        "For some reason the darkness of the hole seems ominous.\n");

    add_item(({"east wall","wall","walls"}), 
        "The walls of the cave are all solid rock, although "+
        "at the top of the east wall is a large hole.\n");

    add_item(({"cave"}),
        "You are standing within a cave deep in the cliff rock.\n");
    
    add_item(({"cliff", "cliff face"}),
        "The rocks of the cliff are all around you.\n");
    
    add_item(({"tunnel"}),
        "The tunnel leads west towards the sound of water.\n");

    add_exit("cave_entrance.c","west");
    reset_room();
}

void
init() {
    ::init();
    add_action(do_climb, "enter");
    add_action(do_climb, "climb");
    add_action(do_climb, "pass");
    add_action(do_climb, "pull");
}

int do_climb(string str)
{
    if (!strlen(str))
    {
        notify_fail("Enter the hole?\n");
        return 0;
    }

    notify_fail("Are you trying to enter the hole?\n");
    if (!parse_command(str, ({ }),
        "[myself] [up] [in] / [into] [through] [the] "+
        "'hole' / 'opening' / 'darkness' / 'ceiling'"))
        return 0;    

    object tp = this_player();

    write("You pull yourself up through the hole.\n");
    tp->move_living("M",CRYPT_ROOM,1,0);
    
    return 1;
}


