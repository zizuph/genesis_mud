/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * f_soup.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDFOOD;

create_food()
{
    ::create_food();
    set_name("soup");
    set_short("bowl of lobster soup");
    set_pshort("bowls of lobster soup");
    set_adj("lobster");
    set_long("It's a bowl with lobster soup.\n");
    set_amount(30);
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 30);
}
