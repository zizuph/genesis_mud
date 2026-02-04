/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * f_meal.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDFOOD;

create_food()
{
    ::create_food();
    set_name("meal");
    set_short("seadog's meal");
    set_adj("seadog's");
    set_long("A complete seadog's meal. It consists of cod, a red-beat " +
	     "salad, some shrimps, and finally, a cream layered cake. " +
	     "Yum-yum!\n");
    set_amount(100);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 100);
}
