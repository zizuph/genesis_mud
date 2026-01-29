/*  A log book that records the actions taken by members 
    of the Calian Council. 

    coder(s):   Maniac, Glykron
    history:    
                 5. 2.2001           security updated         Maniac 
                30. 6.94             Modified                 Glykron 
                10. 5.94             Created                  Maniac 

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

#include <stdproperties.h>
#include "defs.h"
#pragma save_binary

inherit CRPALACE_OBJECTS + "log_book";

#define BOOK_MAX_SIZE 4600000

void
read_it(string str)
{
    ::read_it("mread");
}

void
create_log_book()
{
    seteuid(getuid()); 
    set_name("book"); 
    set_adj("red"); 
    set_short("red book sitting on the table"); 
    set_long("A book with a red cover. " + 
        "The title of the book is: \"Calian Council Log\".\n"); 
    set_file(LOG("council")); 
    set_max_size(BOOK_MAX_SIZE); 
    add_prop(OBJ_I_WEIGHT, 1000); 
    add_prop(OBJ_I_VOLUME, 1000); 
    add_prop(OBJ_M_NO_GET, 
	"The council log book is fixed here by the magic of Caliana.\n"); 
}

/*
void
update_log_book(string new_line)
{
    ::update_log_book(new_line);
}
*/ 
