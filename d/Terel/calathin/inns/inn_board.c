/*
 *   Company, Inn Board Room
 *  Updated by Shinto  031299
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <stdproperties.h>

void 
create_room() 
{
     object board;
     set_short("Company Board Room");
     set_long("Board room description\n");

    board=clone_object(COMPANY + "company_board.c");
    board->move(this_object());

    INSIDE;

    add_exit(COMPANY + "inn/inn_stair", "north", 0);
    add_exit(COMPANY + "inn/inn_meditate", "west", 0);
    add_exit(COMPANY + "inn/inn_herb","east",0);

}
