/* 
* Room in the Lizard Caves
* /d/Kalad/common/wild/lizard_area/cave_start.c
*/
#include "../local.h"

inherit LIZARD_STD_ROOM;

int recently_searched;

/*
 * Function name: create_std_lizard()
 * Description  : Constructor for the room, modify this to change room.
 */
void
create_std_lizard()
{
    string long1, long2, long3;
    
    //Selects the random long description strings
    long1 = one_of_list(LONG1);
    long2 = one_of_list(LONG2);
    long3 = one_of_list(LONG3);

    add_prop(OBJ_S_SEARCH_FUN, "search_pile");
    
    set_short("Inside a Dark Cave");
    set_long(long1+long2+long3+" There appears to also be some "+
    "filth and refuse piled up in one corner.\n"); 

    add_item(({"floor"}),"The ground is barely visible due to the large "+
    "number of stalagmites intermixed with numerous bones and filth.\n");
    add_item(({"bones","bone","refuse","filth"}),"Gnawed and chewed "+
    "animal bones mixed with raw feces and other solid waste fills this"+
    "chamber. One large pile of filth in the corner is particularly "+
    "disgusting.\n");
    add_item(({"pile"}),"A massive pile of dung! Whew, boy does it stink!\n");
        
           
    add_exit(RDIR + "level6-2","north");
        
    //Sets the no exit message for unlisted directions
    set_no_exit_msg(get_all_no_exits(({"n"})),
    "The cave walls block your path.\n");

    //Adds the npc, the number of them and then arms them.
    add_npc(LIV +"shaman_lizard", 1, &->arm_me());
    
    reset_room();
}

void
reset_room()
{
    recently_searched = 0;
}
string
search_pile(object searcher, string place)
{
    if (!place || (place != "pile" && place != "the pile"))                    
        return "";
    if (recently_searched)
    {
       return "You find nothing in the disgusting pile, and just get yourself "
           + "dirty for your effort!\n";
    }
    recently_searched = 1;
    say(QCTNAME(TP) + " discovered something from the pile!\n");
    clone_object("/d/Kalad/common/wild/pass/npc/chest_mimic")->move_living("M",TO);
    return "You discover a golden chest within the pile!\n";
}