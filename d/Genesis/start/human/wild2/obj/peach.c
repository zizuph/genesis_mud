/*
 * /d/Genesis/start/human/wild2/obj/apple.c
 *
 * Varian - March 2016
 *
 * Based on code borrowed from Mirandus via Mercade
 */

inherit "/std/food";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <money.h>
#include <stdproperties.h>

#define COLOUR ({"pink", "orange"})
#define ADJ ({"soft", "juicy", "ripe", "fuzzy"})

/*
 * Function name: create_object()
 * Description  : Constructor, redefine this to configure your flower
 */

void
create_food() 
{
    string colour = one_of_list(COLOUR);
    string adj = one_of_list(ADJ);
    
    set_name(({"peach"}));
    add_name(({"fruit"}));
    set_pname(({"peaches"}));
    add_pname(({"fruits"}));
    set_adj(colour);
    add_adj(adj);

    set_short(adj + " " + colour + " peach");
    set_long("This "+colour+" peach looks "+adj+" and very good to eat!\n");

    set_amount(50);

    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 0);   
}