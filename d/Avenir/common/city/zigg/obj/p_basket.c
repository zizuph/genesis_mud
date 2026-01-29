// -*-C++-*-
// file name:
// creator(s):
// last update:
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

inherit "/d/Genesis/std/pack";
inherit "/lib/keep";

#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include "zigg.h"

public void
fill_basket(void)
{
    object obj;

    obj = clone_object(ZIG_FOOD + "tomato_sw");
    obj->set_heap_size(8);
    obj->move(TO, 1);

    obj = clone_object(ZIG_FOOD + "borange");
    obj->set_heap_size(8);
    obj->move(TO, 1);

    obj = clone_object(ZIG_FOOD + "peach");
    obj->set_heap_size(4);
    obj->move(TO, 1);

    obj = clone_object(ZIG_FOOD + "peach");
    obj->set_heap_size(4);
    obj->move(TO, 1);

    obj = clone_object(ZIG_FOOD + "punch");
    obj->move(TO, 1);

    obj = clone_object(ZIG_OBJ + "p_blanket");
    obj->move(TO, 1);

}

public void
create_container(void)
{
    setuid();
    seteuid(getuid());

    set_name(({"basket", "picnic basket"}));
    set_adj(({"willow","dark", "brown", "black", "red", "sybarun", "ziggurat"}));
    set_short("willow picnic basket");
    set_long("This handsome dark brown, hand made willow basket serves a "+
	"party of 4. Its red and black gingham liner has a matching blanket. "+
	"It is accented with decorative straps, hinges and closure with "+
	"gold tone clasp. The double sided lid opens for easy access. One "+
	"side has a partition to securely hold a bottle and glass set. The "+
	"basket also has a sturdy stationary handle for carrying.\n");

    add_prop(CONT_I_MAX_WEIGHT, 5000);
    add_prop(CONT_I_MAX_VOLUME, 5000);
    add_prop(CONT_I_WEIGHT, 50);
    add_prop(CONT_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 1000);
    add_prop(CONT_I_REDUCE_WEIGHT, 500);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_CLOSED, 1);

    fill_basket();
}

public int
item_filter(object ob)
{
    return !(!ob->id("food") && !ob->id("drink") &&
	!ob->id("picnic blanket"));
}

