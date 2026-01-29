/* /d/Raumdor/common/temple/lair_main.c 
*
*Lair of the Khiraa 
*
*
* Refurbishing the original khiraa lair
*
* Nerull 2020
*
*/
#pragma strict_types

#include "defs.h"
inherit TEMPLE_ROOM;

object knight;


string
query_k_mos()
{
    /*if(IS_DK(TP) || IS_LP(TP))
        return "but you are able to understand them. They read:\n"+
        "In that sea of darkness,\n"+
        "There shines but one light,\n"+
        "He is the Fallen One,\n"+
        "All hail to His might,\n"+
        "Lord of the Damned Grave,\n"+
        "Our souls we give Him,\n"+
        "That we live forever,\n"+
        "Our dark flame shant dim.\n";*/
    return "but you do not know what they say.\n";
}


string
query_k_ar()
{
    /*if(IS_LP(TP) || IS_DK(TP))
        return "You understand them to mean that to the east, is where"+
        " the Death Knights reside, while to the west, is where the "+
        "Lich Priesthood rests their damned souls.\n";*/
    return "The east one has a picture of a "+
    "grim skull with a sword going through it, while the west one has "+
    "an S symbol with a pole going through it.\n";
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
     
    write("A powerful field of magic blocks you from going in that direction.\n");
    
    
    return 1;
}


int
block2()
{
    if ((!present(knight, this_object())))
    {
        return 0;
    }
     
    write("The "+knight->short()+" blocks you from going in that direction!\n");
    
    
    return 1;
}


void
create_room()
{
    ::create_room();
	
	add_prop(ROOM_I_LIGHT,0);
	
    set_short("In a dark hall");
	
    set_long("\n   You have entered a strange and fascinating "+
    "room in this dark temple. The north wall is covered with "+
    "a huge mosaic in the shape of a skull. The ground here is "+
    "made of smooth black marble, while the walls and ceiling "+
    "are of black stone. The walls are all bare, except on the "+
    "north wall, which has many strange runes and symbols mixed "+
    "in with the mosaic. The air is very cold here, and smells "+
    "strong of death and decay.\n"+
    "   A black stone altar rests in the center of the north wall, "+
    "on which rests some kind of candle that burns a purple-black "+
    "flame. Also in the wall, you see a small doorway going north. "+ 
    "Archways to the west and east lead into other dark rooms. On "+
    "each archway you notice many strange runes. But noticably, "+
    "on the west archway, there is a picture of an S shaped "+
    "figure with a pole through it, and on the east archway, a "+
    "grim skull with a dagger through it.\n\n");

    add_item("mosaic","The mosaic is made of white and grey colors, "+
    "forming a very realistic picture of a grim skull. In each of "+
    "its eyes, a red dot is placed. Other strange symbols and runes "+
    "decorate it, @@query_k_mos@@");
	
    add_item("walls","The walls are made of cold black stone, and "+
    "are unadorned.\n");
	
    add_item("ceiling","The ceiling is not very high here, and it "+
    "is rather plain and unadorned.\n");
	
    add_item(({"archways","archway"}),"The archways are adorned with "+
    "many strange runes and symbols. @@query_k_ar@@");
	
    add_item("altar","The altar is made of black stone, and its "+
    "surface is polished to a gleaming shine. Skulls adorn its "+
    "sides, and on it rests a single candle of some sort that "+
    "burns an eerie purple-black flame.\n");
	
    add_item("floor","The floor is very clean and made of polished "+
    "black marble that reflects little light.\n");
		
	add_exit(TEMPLE_DIR + "lair7", "north", "@@block2@@");
	add_exit(TEMPLE_DIR + "lair11", "east", "@@block@@");
	add_exit(TEMPLE_DIR + "lair10", "west", "@@block@@");
	add_exit(TEMPLE_DIR + "lair5", "south", 0);	
	
	reset_room();
}


void
reset_room()
{
    if(!knight)
    {
        knight = clone_object("/d/Raumdor/common/npc/death_knight_temple");
        knight->move_living("M",TO);
        tell_room(TO, "A "+knight->short() + 
                " rushes in from the eastern archway!\n");
    }
}

