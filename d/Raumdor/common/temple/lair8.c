/* /d/Raumdor/common/temple/lair1.c 
*
*Lair of the Khiraa 
*
*
* Refurbishing the original khiraa lair2
*
* Nerull 2020
*
*/
#pragma strict_types

#include "defs.h"
inherit TEMPLE_ROOM;


string
query_k_rune()
{
    //if(IS_LP(TP) || IS_DK(TP))
      //  return "They are praises to the Nameless one. All hail "+
        //"unto Him. Khiraa.\n";
    return "You do not know what they mean, but "+
    "they look very ancient.\n";
}


int
block()
{
    /*mapping temp = restore_map(KHIRAA_DIR(log/friend_list));
    if(IS_DK(TP) || IS_LP(TP))
        return 0;
        
    if(member_array(TP->query_real_name(),m_indexes(temp)) != -1)
        return 0;
        
    if ((!present(guard1, this_object())) && (!present(guard2, this_object())) && (!present(lich, this_object())))
    {
        return 0;
    }*/
     
    write("A powerful magical field blocks you from going in that direction.\n");
    
    
    return 1;
}


void
create_room()
{
    ::create_room();
	
	add_prop(ROOM_I_LIGHT,0);
	
    set_short("In a dark hall");
    
    set_long("\n   You are walking along a short, cold hallway. The "+
    "walls and ceiling are made of smooth black stone, while the "+
    "floor is formed of polished black marble. Small red runes "+
    "decorate the sides of the walls.\n"+
    "   You can smell death and decay in the air. Looking to the "+
    "north, you can see a purple glowing coming from the room there. "+
    "To the east, only darkness can be seen.\n\n");

    add_item(({"runes","symbols"}),"@@query_k_rune@@");
	
    add_item("ceiling","The ceiling is made of solid black stone.\n");
	
    add_item("walls","The walls are made of dark black stone, with "+
    "a few runes inscribed on them.\n");
	
    add_item("floor","The floor is of solid polished black marble.\n");
		
    add_exit(TEMPLE_DIR + "temple_portal", "north", "@@block@@");
	add_exit(TEMPLE_DIR + "temple_join", "east", 0);
	add_exit(TEMPLE_DIR + "lair7", "south", 0);
}

