/*  An activities poster for Gelan.

    coder(s):   Maniac
    history:
            23.12.94           created                      Maniac
            23.3.95            modified                     Maniac

    purpose:    to show people what special activities
                are available in Gelan

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

inherit "/std/scroll";
#include <stdproperties.h>
#include "object.h"

void
read_it(string str)
{
    ::read_it("mread");
}

void
create_scroll()
{
    set_name("poster");
    set_adj("bright");
    set_short("bright poster pinned to the wall next to the board");
    set_long("This poster is large, with bright bold letters at " +
             "the top proclaiming it to be the 'Public Announcements " +
             "of Gelan'.\n"); 
    set_file(GELAN_TEXTS + "special_activities");
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_M_NO_GET,
        "The bright poster is pinned securely to the wall.\n");
}
