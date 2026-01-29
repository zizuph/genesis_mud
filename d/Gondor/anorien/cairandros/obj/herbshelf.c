/*
 * Shelves of herbs in Cair Andros
 * /d/Gondor/anorien/cairandros/obj/herbshelf
 *
 * Varian - Feb 2020
 *
 */

#pragma strict_types
#pragma save_binary 

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/met_defs.h"
#include "../../defs.h"

inherit "/std/container";
int pouches = 1;

public void
create_container()

{
    set_adj("wooden");
    add_adj("long");
    set_name("shelves");
    add_name("shelf");

    set_short("collection of wooden shelves");
  
    set_long("There are several long wooden shelves mounted on " +
        "the northern wall of this room. Each shelf is filled " +
        "with several ceramic jars and wooden boxes. A strong, " +
        "earthy aroma hangs in the air near the shelves.\n");

    add_item( ({"jar", "ceramic jar", "ceramic jars", "jars"}),
        "There are dozens of ceramic jars scattered across the " +
        "shelves here, each of them smelling strongly of " +
        "dried herbs.\n");

    add_prop(CONT_I_VOLUME, 81000);
    add_prop(CONT_I_WEIGHT, 4535);
    add_prop(OBJ_M_NO_GET, 1);

    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    reset_object();
}

public mixed
do_search(object pl, string arg)
{
    object pouch;

    if (member_array(arg,
        ({ "box", "boxes", "wooden box", "wooden boxes", "jar", 
           "jars", "ceramic jar", "ceramic jars", "shelf", 
           "shelves", "wooden shelf", "wooden shelves"}) ) == -1)
    {

        return "Your search reveals nothing special.\n";
    }

    if (pouches < 1)
        {
            write("");
            return 1;
        }

    seteuid(getuid(this_object()));
    pouch = clone_object("/d/Gondor/anorien/cairandros/obj/h_pouch");
    clone_object("/d/Gondor/common/herbs/attanar")->move(pouch, 1);
    clone_object("/d/Gondor/common/herbs/tuo")->move(pouch, 1);
    pouch->move(this_player());
    pouches = pouches -1;

    SAY(" searches through the shelves and finds something!");

    return "You rummage through the various boxes and jars " +
        "on these wooden shelves and find a pouch filled " +
        "with herbs!\n";

}