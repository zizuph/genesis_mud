/*
 * Random jelly bean for Easter
 * -- Finwe, April 2007
 */

inherit "/std/food";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Shire/sys/defs.h"

#define COLOURS_AND_FLAVOURS \
    ([ "red"         : "strawberry", \
       "yellow"      : "lemon", \
       "green"       : "lime", \
       "brown"       : "chocolate", \
       "scarlett"    : "cherry", \
       "black"       : "licorace", \
       "ruby"        : "raspberry", \
       "dark-red"    : "tropical punch", \
       "cream"       : "coconut", \
       "crimson"     : "cinnamon", \
       "purple"      : "grape", \
       "white"       : "pineapple", \
       "pink"        : "pink lemonade", \
       "orange"      : "orange", \
       "blue"        : "blueberry", \
       "light-orange": "cantalope", \
       "lavendar"    : "plum" ])

/* Global variable containing the color of the jelly beans. */
string color;
string flavor;

void
set_color(string c)
{
    mapping colours_and_flavours = COLOURS_AND_FLAVOURS;
    
    if (!strlen(c))
    {
    	c = one_of_list(m_indices(colours_and_flavours));
    }
    if (adjectiv_id(color))
    {
    	remove_adj(color);
    }

    color = c;
    flavor = colours_and_flavours[color];
    set_adj(color);
    set_short(color + " jelly bean");
    set_pshort(color + " jelly beans");
    set_long("This is " + LANG_ASHORT(this_object()) + ". It is a sugar glazed " +
        "candy and in the shape of a bean. The candy has a hard shell " +
        "with a soft center. It has a " + flavor + " flavor.\n");
}

void
create_food()
{
    set_name("bean");
    add_name("jelly bean");
    set_pname("beans");
    set_adj("small");
    set_amount(2);
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
