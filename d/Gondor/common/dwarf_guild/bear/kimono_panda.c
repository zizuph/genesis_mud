//INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <macros.h>

// OBJECT DEFINITION

void create_object ()
{
    set_name("kimono");
    add_name("print");
    set_short("comfortable silk kimono with panda bear print"); 
    set_adj(({"comfortable", "silk", "kimono", "with", "panda", "bear" }));

    set_long("The comfortable kimono is tailor-made for cute furry " +
        "bear-sized beings, and will not fit anyone else. It is made of " +
        "the softest silk, almost as soft as fur, and has " +
        "a warm light brown background with contrasting designs. You see " +
        "intricate scenes with panda bears eating bamboo and playing " +
        "in the forest, in black, white, shades of green, yellow and brown. " +
        " The matching sash belt " +
        "is made of a darker brown silk, with an elaborate silk brocade " +
        "embroided scene of two cute furry bears leaning comfortably " +
        "against the trunk of giant sequoia. A tiny tag is " +
        "sewn to the neck area of the comfortable kimono.\n");
    add_item( ( { "tag", "tiny tag" }), "The tag states in curly writing " +
        " 'Made by Tai-Lor', and 'From Stern'.\n");

    add_prop(OBJ_M_NO_SELL, "Gifts should never be sold.");
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_WEIGHT, 800);
}


int bear_query_bearable ()
{
    return (1);
}


string query_auto_load ()
{
  return (MASTER);
}


void init_arg (string sArgs)
{
}
