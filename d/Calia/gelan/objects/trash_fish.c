

/*      This is an object in a Gelan trash heap

    coder(s):  Maniac 
    history:
                12/4/98    rabbit -> gopheroo                Maniac
                19.9.94    Created                           Maniac

    quests:     This object is a red
                herring, a useless item that's found in with the 
                potentially useful items for the gopheroo catching
                quest in Gelan 

    special:    none

    to do:      none
    bug:        none known
*/

inherit "/std/food";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "object.h"


void
special_effect(int num)
{
    write("Yeuch! That's revolting!\n");
}



void
create_food()
{
    set_name("fish");
    add_name("herring");
    set_adj(({"old", "smelly", "rotting", "red" }) );
    set_short("smelly rotting fish");
    set_pshort("smelly rotting fish"); 
    set_long("This fish was slung out several days ago. It " +
             "is rotting and it stinks!\n");
    add_prop(OBJ_I_VALUE, 0);
    set_amount(5);
}


