
/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ew_cloak.c
 *
 * Mergula's cloak.
 *
 * Updated to reflect use of new standard armour in Terel.
 * Torm, Sept 98
 * 
 * Updated the desc to something a little more aesthetically
 * pleasing than "It's a black robe of finest quality."
 * Lilith, June 2005
 *
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

public void
create_terel_armour()
{
    set_name("cloak");
    set_short("gleaming black cloak");
    set_long("Threads of spun silver glitter within the heavy "+
        "black fabric of this cloak, which swings and sways "+
        "with every move. It is rather heavy due to the chain"+
        "mail carefully sewn between the inner and outer "+
        "linings. The intricate embroidery along the seams, "+
        "once again picked out with silver thread, would seem "+
        "to indicate that this cloak was made to honour the "+
        "greatness of a man, perhaps a great lord of war.\n");

    set_adj(({"black", "glittery", "glittering", "embroidered" ,
        "silvery", "silver-shot", "gleaming"}));
    add_item(({"embroidery", "silver embroidery", "intricate "+
        "embroidery"}), "The embroidery repeats an intricate "+
        "sword-and-shield pattern, picked out in thread "+
        "spun from silver.\n");
    set_default_armour(39, A_ROBE, 0, 0);
    set_am(({ -2, -2, 4}));
    set_keep(1);
   
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 600);
}
