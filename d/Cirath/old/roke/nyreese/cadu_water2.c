/*
 * cadu_water2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/stdwater";

#include "bridgedefs.h"
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>

void
create_waterroom()
{
    set_name("water");

    set_short("Water");
    set_long("You are swimming in the water below a cliff. There are some " +
             "stones here, allowing you to climb up.\n");

    add_exit("cadu_s6", "up");

    set_f_to_be_tired(55);
    set_f_to_drown(6);

    add_item("stones", 
             "They are rather large, and make it possible to climb up.\n");

}

void
drown(object ob)
{
    tell_room(TO, QCTNAME(ob) + " drowns.\n", ob);
    ob->catch_msg("You are so tired that you don't manage to hold your head " +
                  "above the surface anymore. A huge wave drags you down, " + 
                  "and in a desperate try to stay alive, you take a deep " +
                  "breath, but around you is only water...\n");

    ob->set_hp(0);
    ob->do_die(this_object());
}

void
obj_is_tired(object obj)
{
    if (!obj->query_prop(IS_NOTIFIED))
    {
        obj->catch_msg("You are getting very tired from swimming so long.\n" +
                       "You realize that you must get up soon, or else the " +
                       "huge waves will drag you under the surface, and " + 
                       "cause your death.\n");
        obj->add_prop(IS_NOTIFIED,1);
    }
}

void
remove(object ob)
{
    tell_room(TO, "The " + ob->query_name() + 
              " sinks to the bottom of the sea.\n");
    ob->remove_object(); 
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(living(ob))
        return;

    set_alarm(1.0, 0.0, &remove(ob));
}
