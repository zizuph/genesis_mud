// file name:   /d/Avenir/common/holm/t_camp/insignia.c
// creator(s):  
// thanks:      
//            
// last update: 
//             
// purpose:    A quest item that the noble_troloby want to possess 
// note:       
//            
// bug(s):
// ideas:     
        
#include "../holm.h"

inherit "/std/object";

void create_object()
{
    set_name("insignia");
    set_short("insignia");
    add_name("INSIGNIAQ_QUEST_ID");
    set_long("A small square shaped insignia it is illuminous and it looks " +
            "just like piece of the source. " +
            "The insignia is also unnusually " +
            "heavy for being so small.\n" );
    add_prop(OBJ_I_WEIGHT, 1000); 
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 500);
}

