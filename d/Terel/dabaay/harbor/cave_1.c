/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * cave_1.c
 *
 * Slugg's new home
 *
 * Goldberry May, 2002
 */

#include "/d/Terel/include/Terel.h"
#define DAB_HARB DABAAY_DIR + "harbor/"
#define DAB_NPC DABAAY_DIR + "npc/"
#define CHEST DABAAY_DIR + "obj/jchest"
#define FLOG DABAAY_DIR + "log/found_jchest"

inherit DAB_HARB + "port_room";

object item;
int dug;

public string*
query_object_list()
{
    return ({DAB_NPC + "slugg"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("In a sandy cave");
    set_long(
        "You are in a dimly-lit, but warm cave. The walls and "+
        "ceiling appear to be granite, while the floor is a mess "+
        "of damp sand. One small section of the ceiling has a "+
        "trapdoor set into it. A ladder climbs the wall underneath "+
        "the door.\n");
    
    add_item("ladder",
        "A wooden ladder that leads back up to the trapdoor.\n");
    
    add_item(({"door","trapdoor"}),
        "A door made from sturdy wooden planks is set into the ceiling. "+
        "This must be where you fell through.\n");

    add_item(({"sand","mud","damp sand"}),
        "White to tan-coloured sand, that is quite wet.\n");

    add_cmd_item(({"in sand"}), "dig", "@@digging");


    add_exit(DAB_HARB + "un_bwalk1", "up", 0);
    dug = 1;
    reset_room();
}

void
reset_room()
{    
   ::reset_room();
   dug = 1;
}


int
query_dug()
{
    return dug;

}

int digging()
{
    write("You start digging in the sand.\n");

    if(dug == 1 && !present(item,TO))
    {
        set_alarm(5.0, -1.0, "get_item");
        return 1;
    }
    set_alarm(5.0, -1.0, "no_item");

    return 1;
}

void
get_item()
{
   if(present(TP,TO))
    { 
    item = clone_object(CHEST);
    item->move(ENV(TP));
    dug = 0;
    write("Diggin deep in the sand, you find a heavy chest!\n");
    write_file(FLOG, TP->query_name()+" " + ctime(time()) + "\n");
    }
    return;
}

void
no_item()
{
    write("You dig deep in the sand, but find nothing.\n");
    return;
}

