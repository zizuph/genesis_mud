/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * f_cod.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDFOOD;

create_food()
{
    ::create_food();
    set_name("cod");
    set_pname("cod");
    set_short("boiled cod");
    set_pshort("some boiled cod");
    set_adj("boiled");
    set_long("A large portion of boiled cod! Your favourite!\n");
    set_amount(63);
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 60);
}
