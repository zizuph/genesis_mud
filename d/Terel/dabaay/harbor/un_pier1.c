/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * un_pier1.c
 *
 * Under south pier 1 
 *
 * Goldberry January, 2000
 * Modified 05102002  Goldberry
 *     Relocated Slugg and Chest
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
    return ({DAB_NPC + "slug"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Under a short pier");
    set_long(
        "You are on a muddy strip of sand under a short "+
        "pier. Above you, you can see the beams and planks "+
        "that make up the pier. A few steps to your south, "+
        "the bay-waters lap at the beach. There is a ladder "+
        "attached to one of the pier's pilings.\n");
    
    add_item("ladder",
        "A wooden ladder that leads back up to the pier.\n");
    
    add_item("planks",
        "Rough-sawn and weather-beaten, the planks appear "+
        "to be less sturdy when looking at them from below.\n");

    add_item(({"pier", "wooden pier"}), 
        "It's a well-built wooden pier. It will withstand the " +
        "worst of storms.\n");

    add_item(({"piers", "wooden piers"}), 
        "Wooden piers, sturdily built. Several of the piers " +
        "have boats docked at them.\n");
    
    add_item(({"bay"}),	
        "You can see some fishing boats that have anchored in the "+
        "midst of the bay. Out towards the east and past some other "+
        "piers, the bay opens into the sea. From this distance, you "+
        "can barely make out what appears to be a stone wall "+
        "stretching from the north shore into the bay.\n");

    add_item(({"wall","stone wall"}),
        "The wall is made up of large gray stones, piled up "+
        "in a line from the north point to the center of the bay's "+
        "entrance. You can see watercraft traversing the calm waters "+
        "created by this artificial cove. Every few moments a wave "+
        "crashes over the wall.\n");

    add_item(({"stones","stone","large gray stones","gray stones"}),
        "The wall is too far away to see much about the stones.\n");

    add_item(({"boat","boats","watercraft","vessels","ships"}),
        "There are some fishing boats anchored out in the bay. "+
        "There are also various vessels that appear to be docked "+
        "at several piers.\n");
    
    add_item(({"sea"}), "It looks cold and blue.\n");
    add_item(({"sand","mud","muddy strip"}),
        "White to tan-coloured sand, wet from the seawater.\n");

    add_cmd_item(({"in sand"}), "dig", "@@digging");


    add_exit(DAB_HARB + "spier_1", "up", 0);
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

    set_alarm(5.0, -1.0, "no_item");

    return 1;
}

void
no_item()
{
    write("You dig deep in the sand, but find nothing.\n");
    return;
}

