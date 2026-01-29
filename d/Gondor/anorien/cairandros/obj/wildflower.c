/*
 * /d/Gondor/anorien/cairandros/obj/wildflower.c
 *
 * Varian - March 2016
 *
 * Based on code borrowed from Mirandus via Mercade
 */

inherit "/std/object";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <money.h>
#include <stdproperties.h>

#define COLOUR ({"blue", "orange", "pink", "purple", "red", "white", "yellow"})
#define FLOWER ({"bellflower", "aster", "lady's slipper", "orchid",\
    "snapdragon", "rose", "cornflower", "poppy", "tulip", "daffodil", "daisy",\
    "hydrangea", "lily", "iris", "geranium", "magnolia", "hibiscus",\
    "petunia", "hyacinth", "pansy", "crocus", "anemone", "carnation", "peony"})
#define SHADE ({"light", "deep", "dark", "bright"})

string smell_flower(string str);

/*
 * Function name: create_object()
 * Description  : Constructor, redefine this to configure your flower
 */

void
create_object() 
{
    string colour = one_of_list(COLOUR);
    string flower = one_of_list(FLOWER);
    string shade = one_of_list(SHADE);
    
    set_name(({"flower",flower}));
    set_adj(colour);
    add_adj(shade);

    set_short(shade + " " + colour + " " + flower);
    set_long("This appears to be "+LANG_ASHORT(this_object())+". Blessed " +
	"with a fresh fragrance, and given the vivid "+shade+" "+colour+" " +
    "colour of the petals, you would expect that this particular "+flower+" " +
    "has been picked quite recently. The flower probably does not have any " +
    "value, save perhaps as a gift to a friend.\n");

    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_VALUE, 0);   
}

int
smell_flower(string str)
{
    
    notify_fail("Smell what?\n");
    if (str != "flower" && str != "the flower" && str != "wildflower" 
        && str != "the wildflower")
    return 0;
    
    else
    say(QCTNAME(this_player()) +
        " raises their arm to smell a "+LANG_ASHORT(this_object())+".\n");
    write("Raising the "+LANG_ASHORT(this_object())+" up to your face, you " +
        "sniff the flower to inhale its calming fresh fragrance. A scent " +
        "which seems to reach deep into your soul.\n");
    return 1;

}

public void
init()
{
    ::init();
    add_action(smell_flower, "smell");
    add_action(smell_flower, "sniff");
}
