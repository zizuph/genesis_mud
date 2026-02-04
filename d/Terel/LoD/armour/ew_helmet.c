/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ew_helmet.c
 *
 * Mergula's helmet.
 *
 * Updated to reflect use of new standard armour in Terel.
 * Torm, Sept 98
 *
 * Removed magical properties, making this 'normal' armour.
 * Updated the description to be more interesting.
 * Lilith, June 2005
 *
 */

#include <wa_types.h>
#include <ss_types.h>
#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;
inherit "/lib/keep";

public void
create_terel_armour()
{
    set_name("helmet");
    set_short("plumed helmet of blackened steel");
    set_long("This helmet has been superbly crafted to "+
      "protect the head while leaving the face open so "+
      "as not to obstruct vision. Dark plumage rises "+
      "along the crest of the blackened steel, adding "+
      "intimidating height to the wearer.\n");
    set_adj("plumed");
    add_adj(({"blackened", "steel"}));
    add_item(({"crest", "plumage", "plume"}),
        "The crest of the helmet is decorated with "+
        "a long row of black horsetail that resembles "+
        "the plumage of an exotic bird.\n");

    set_default_armour(29, A_HEAD, 0, 0);
    set_am(({ 2, 2, -4}));
    set_keep(1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VALUE, 600);
}

