/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * treas_key.c
 *
 * Sorgum 950719
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"

inherit "/std/key";
create_key()
{
    set_adj("large");
    add_adj("steel");
    set_long("It is a large key made from steel and gilded in a layer of gold.\n");
    set_key(TREASURE_KEY);
}
