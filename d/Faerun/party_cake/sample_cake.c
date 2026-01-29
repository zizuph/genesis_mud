/*
 * Sample Party Cake
 * Finwe, January 2016
 */
inherit "/std/object";
inherit "/d/Faerun/party_cake/base_files/party_cake.c";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include "/d/Faerun/defs.h"

#define ADJ1            "tall"
#define ADJ2            "round"
#define SHORT_DESCR     "tall round cake"
#define LONG_DESCR      "This is a tall round cake. It is frosted white and decorated with pink donuts."


public void 
create_cake()
{
    set_name("cake");
//    add_name(CAKE_NAME);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(SHORT_DESCR);
    set_long(LONG_DESCR + " " + xtra_cake_desc + "\n");
}

void init()
{
    ::init();
    add_action("do_cut", "cut");
    add_action("do_catch_get", "get");
    add_action("do_catch_get", "take");

}