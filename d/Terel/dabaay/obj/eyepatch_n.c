/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * eyepatch_n.c
 *
 * Dabaayhab's eyepatch.
 * Non-magical version
 *
 * Goldberry February 2000
 */

#include <wa_types.h>
#include "/d/Terel/include/Terel.h"

inherit "/d/Terel/std/wearable_item";

void
create_terel_wearable_item()
{
    set_name("eyepatch");
    set_adj("black");
    add_adj("leather");
    set_pname("eyepatches");
    set_short("black leather eyepatch");
    set_pshort("black leather eyepatches");

    set_terel_wearable_item_size(ANY_SIZE);
    set_slots(A_EYES);
    set_looseness(0);
    set_layers(1);

    set_long(
        "A triangle of black leather with a leather thong attached "+
        "to it. It appears to be an eyepatch.\n");


    add_prop(OBJ_I_WEIGHT, 30);
    add_prop(OBJ_I_VOLUME, 60);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VALUE, 600);
}

public mixed
wear_terel_item(object obj)
{
  if(!(TP->query_npc()))
   {
    TP->add_prop("Hand_patch",1);
   }

    return 0;
}

int
remove_terel_item(object item)
{
  if(!(TP->query_npc()))
   {
    TP->remove_prop("Hand_patch");
   }

    return 0;
}

