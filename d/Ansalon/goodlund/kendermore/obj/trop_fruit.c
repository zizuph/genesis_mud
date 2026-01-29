/* Tropical fruit for Kendermore, Gwyneth, June 1999 */

inherit "/std/food";
#include <stdproperties.h>

string *fruits = ({"mango", "papaya", "guava"});

void
create_food()
{
    string *fname;
    set_name(fruits[random(3)]);
    add_name("fruit");
    set_adj("ripe");
    fname = query_name(1);
    set_short("piece of ripe " + fname[0]);
    set_pshort("pieces of ripe " + fname[0]);
    set_long("This piece of " + fname[0] + " looks delicious. \n");
    set_amount(40);
}

