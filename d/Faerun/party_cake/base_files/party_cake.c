/*
 * Party cake. This is based on the old party cake from years ago.
 * The  cake can be cut and pieces thrown at others.
 * -- Finwe, Octover 2016
 */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include "/d/Faerun/defs.h"

#define CAKE_NAME   "_party_cake"

string xtra_cake_desc = "The cake hasn't been cut. You may <cut cake>.";
string cake_cutter = "";

public void create_cake()
{
}

public void create_object()
{
    set_name("cake");
    add_name(CAKE_NAME);
    set_adj("large");
    set_adj("round");
    set_adj("pumpkin");
    set_short("");
//    set_long("@@my_long_desc@@");

    add_prop(OBJ_I_WEIGHT, 10000000);
    add_prop(OBJ_I_VOLUME, 800000);

    create_cake();
}

void init()
{
    ::init();
    add_action("do_cut", "cut");
    add_action("do_catch_get", "get");
    add_action("do_catch_get", "take");

}