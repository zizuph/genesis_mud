/*
 * questparcel.c
 *
 * Used in nyreese/sandcastle.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "std/container";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>

int full;

string
query_recover()
{
    return MASTER + ":" + full;
}

void
init_recover(string s)
{
    if (s != "1")
        return;

    seteuid(getuid(TO));

    full = 1;

    clone_object(ROKEDIR + "obj/water")->move(TO);
}

void
create_container()
{
    set_name("bottle");
    add_name("he-he-spirit-quest-parcel");
    set_adj("small");
    set_long("It looks if it has lain in the sand for a very long time. " +
             "There is a small image of a volcano drawn on the inside " +
             "of the blue and green glass.\n");

    add_prop(CONT_I_WEIGHT, 100);  /* weight 100 g */
    add_prop(CONT_I_MAX_WEIGHT, 1100);  /* can hold 1 kg */
    add_prop(CONT_I_VOLUME, 100);  /* it's volume is 0.1 l */
    add_prop(CONT_I_MAX_VOLUME, 1100);  /* holds 1 litre */
    add_prop(OBJ_I_VALUE, 15);
    full = 0;
}

void
init()
{
    ::init();
    add_action("fill_it", "fill");
    add_action("drink", "drink");
}

int
fill_it(string s)
{
    object *a;
    string ss, sk;

    NF("Fill what with what?\n");

    if (!parse_command(s, TP, "%s 'with' 'water' %s", ss, sk))
        return 0;

    a = CMDPARSE_ONE_ITEM(ss, "check_bottle", "check_bottle");

    if (sizeof(a) > 0)
    {
        a[0]->fill("bottle");
        return 1;
    }
    return 0;
}

int
check_bottle(object ob)
{
    if (function_exists("fill", ob) && ob->query_name() == "bottle" &&
        present(ob, TP))
        return 1;
    return 0;
}

int
drink(string s)
{
    object o;
    mixed m;

    o = present("water", TO);

    NF("Drink what?\n");

    if (!o)
        return 0;
    if (s != "water")
        return 0;

    m = o->command_drink();
    if (stringp(m))
    {
        TP->catch_msg(m);
        return 1;
    }

    TP->catch_msg("You drink the water in the bottle.\n");
    full = 0;
    o->remove_object();

    return 1;
}

int
fill(string s)
{
    mixed temp;

    seteuid(getuid(TO));

    NF("Fill what?\n");
    if (s != "bottle" && s != "bottle with water" && s != "water")
        return 0;

    temp = environment(TP)->query_prop(ROOM_I_TYPE);

    if (!(temp == ROOM_BEACH) && !(temp == ROOM_IN_WATER))
    {
        TP->catch_msg("You suddenly realize that this room has no water.\n");
        return 1;
    }
    
    seteuid(getuid());

    NF("It is already full!\n");
    if (!full)
    {
        TP->catch_msg("You fill the bottle with water.\n");
        clone_object(ROKEDIR + "obj/water")->move(TO);
        full = 1;
        return 1;
    }
    return 0;
}
