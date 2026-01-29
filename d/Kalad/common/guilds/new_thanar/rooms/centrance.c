/* 
 * Entrance to the Thanarian Cathedral in Kabal
 * /d/Kalad/common/guilds/new_thanar/rooms/entrance
 */

#include "../local.h"

inherit THANAR_STD_ROOM; 

/*
 * Function name: create_std_thanar()
 * Description  : Constructor for the room, modify this to change room.
 */
void 
create_std_thanar()
{
    set_short("Entrance to the Cathedral");
    set_long("The entrance to the cathedral of Thanar. This "
        + "is where the Thanarian order are centred. As the state "
        + "religion of Kabal, they are granted many privileges and have "
        + "almost unending wealth. The opulence of the space makes such "
        + "wealth abundantly apparent. A Statue stands in the middle of "
        + "floor as a sign of greeting, or oppression, depending on who "
        + "gazes upon it.\n");
    
    //Add the items to the room
    add_item(({"statue"}),
      "The statue is made from obsidian and it is the figure "+
      "of a noble human carrying a scroll in his hand and a "+
      "snake in the other. At the foot of the statue is a golden "+
      "plaque, which you may read.\n");
      add_item(({"plaque","gold plaque", "golden plaque"}),
      "Welcome to the Temple of Thanar.\n\n"+
      "We are pleased that you have found your way here.\n"+
      "If you are human you may enter our grand temple\n"+
      "and learn more about the Great Thanar and our cause.\n\n"+
      "Chosen Minister of Thanar\n");
    add_cmd_item("plaque", "read","Welcome to the Temple of Thanar.\n\n"+
      "We are pleased that you have found your way here.\n"+
      "If you are human you may enter our grand temple\n"+
      "and learn more about the Great Thanar and our cause.\n\n"+
      "Chosen Minister of Thanar\n");
        
    add_exit(RDIR + "alcove_west","west");
    add_exit(RDIR + "inner_mid","north",0);
    add_exit(RDIR + "alcove_east","east");
    add_exit("/d/Kalad/common/central/promenade/s2", "south");
    
    //Sets the no exit message for unlisted directions.
    set_no_exit_msg(get_all_no_exits(({"w","n","e","s"})),
    "The rest of the Cathedral is still under construction.\n");
    
    add_exit(RDIR + "inner_right1","northeast");
    add_exit(RDIR + "inner_left1","northwest");

	  //Add the NPCs, Number of them.
    //add_npc(LIV +"cpriest", 2);
        
    reset_room();
}

