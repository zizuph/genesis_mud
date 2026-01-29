/* 	A poster that reports the most recent entrants to the Calian
        guild and those who have given help with the entrance quest

    coder(s):   Maniac
    history:
                13.4.94              Created                  Maniac

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

#include <stdproperties.h>
#include "defs.h"
#pragma save_binary

inherit GLYKRON_OBJECTS + "log_book";

#define POSTER_MAX_SIZE 1000

void
read_it(string str)
{
    ::read_it("mread");
}

void
create_poster()
{
    set_name("poster");
    set_short("poster pinned to the wall");
    set_long("A large poster with a bold header at the top.\n" +
        "The header says \"Record of recent recruitment to the guild\".\n");
    set_file(LOG("calian_recruitment"));
    set_max_size(POSTER_MAX_SIZE);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_M_NO_GET,
        "The poster cannot be taken, as it is pinned securely to the wall.\n");
}

void
create_log_book()
{
    create_poster();
}

int
update_poster(string str)
{
    ::update_log_book(str);
}