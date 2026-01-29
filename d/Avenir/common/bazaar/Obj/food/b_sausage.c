// path:         /d/Avenir/common/bazaar/obj/b_sausage.c
// creator(s):   Lilith Sep 1997
// last update:  
// desc:         Sausage from butcher shop
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
    set_short("spicy "+ query_race() +" sausage");    
    set_long("This is a spicy sausage made from "+ query_race() +
        " meat. It looks like it would be a tasty snack.\n");
    add_adj(query_race() +" sausage");
}

void
create_food()
{
    set_amount(100);
    set_name("sausage");
    set_short("spicy sausage");
    set_long("This is a spicy sausage made from mystery "+
        "meat. It looks like it would be a tasty snack.\n");
    add_name(({"link", "sausage link", "food"}));
    add_adj(({"butcher", "spicy", "thick"}));    
}

