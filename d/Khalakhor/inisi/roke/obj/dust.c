/*
 * dust.c
 *
 * Used in npc/grugg.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* partly borrowed from the wizdust. (except for the abilities)
   /Gres.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>

string
query_recover()
{
    string name;
    int i;
    sscanf(file_name(this_object()), "%s#%d", name, i);
    return name;
}

void
create_object()
{
    set_name("dust");
    set_name("pile");
    set_name("dust of cold feet");
    set_long("This pile of dust comes from an evil grugg.\n");
    set_short("pile of dust");

/*    add_prop(MAGIC_AV_CURSED, ({"@@curse"}));*/
    add_prop(MAGIC_AM_ID_INFO, ({"@@wrong", 10, "@@right", 50}));
    add_prop(MAGIC_AM_MAGIC, ({100, "enchantment"}));
    add_prop(MAGIC_I_RES_IDENTIFY, 50);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 50);
}

string
right()
{
    return "This is dust of cold feet.  Rubbing it on your feet " +
        "will make it possible to walk on lava.\n";
}

string
wrong()
{
    return "You feel that this dust has something to do with temparature.\n";
}

int
rub_dust(string str)
{
    notify_fail("Rub what?\n");
    if (!str)
        return 0;

    if (parse_command(str, this_object(),
                      " 'me' / 'myself' / 'feet' 'with' 'dust' "))
    {
        write("You rub the dust onto your feet. " +
              "They freeze to ice.\n");
        say(QCTNAME(this_player()) + " rubs some dust onto " +
            this_player()->query_possessive() + " feet.\n");

        TP->add_prop(COLDFEET, 2);
        remove_object();
        return 1;
    }
    return 0;
}

void
init()
{
    ::init();
    add_action(rub_dust, "rub");
}
