// path:         /d/Avenir/common/bazaar/obj/b_steak.c
// creator(s):   Lilith Sep 1997
// last update:  
// desc:         Steak from butcher shop
// note:         
// bug(s):
// to-do:       

inherit "/std/food";
#include "/sys/stdproperties.h"
#include <macros.h>

string race;
void set_race(string str) {     race = str;     }
string query_race()       {     return race;    }

void
add_race()
{
    set_long("A thick and juicy steak made from "+
        query_race() +" meat. It looks like it would be quite "+
        "filling.\n");
    set_short("thick "+ query_race() +" steak");
}
void
create_food()
{
    set_amount(250);
    set_name("steak");
    set_long("A thick and juicy steak made from mystery "+
        "meat. It looks like it would be quite "+
        "filling.\n");
    set_short("thick steak");
    add_name(({"thick steak", "tender steak", query_race() +" steak", 
        "food", "meat" }));
    add_adj(({"butcher", "tasty", "thick", "tender"}));   
}

