/*
 * Random marshmallow peeps for Easter
 * -- Finwe, April 2007
 */

inherit "/std/food";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Shire/sys/defs.h"

#define COLOURS_AND_SHAPES \
    ([ "green"      : "rooster", \
       "brown"      : "cow", \
       "yellow"     : "baby chick", \
       "pink"       : "bunny", \
       "orange"     : "duck", \
       "lavendar"   : "pony" ])

/* Global variable containing the color of the jelly beans. */
string color;
string shape;

void
set_color(string c)
{
    mapping colours_and_shapes = COLOURS_AND_SHAPES;
    
    if (!strlen(c))
    {
    	c = one_of_list(m_indices(colours_and_shapes));
    }
    if (adjectiv_id(color))
    {
    	remove_adj(color);
    }

    color = c;
    shape = colours_and_shapes[color];
    set_adj(color);
    set_short(color + " peep");
    set_pshort(color + " peeps");
    set_long("This is " + LANG_ASHORT(this_object()) + ". It is is made from marshmallow and shaped like a " + shape + ". The peep is dusted with colored sugar and looks very tasty.\n");
}

void
create_food()
{
    set_name("peep");
    set_pname("peeps");
    set_adj("small");
    set_amount(5);
    set_color("");
}

string
query_recover()
{
    return MASTER + ":" + color;
}

void
init_recover(string arg)
{
    set_color(arg);
}
