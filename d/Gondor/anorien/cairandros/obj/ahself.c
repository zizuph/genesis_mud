/*
 * /d/Gondor/anorien/cairandros/obj/ashelf.c
 *
 * Varian - March, 2020
 *
 */

#pragma strict_types
#pragma save_binary

inherit "/std/container";

#include "../../defs.h"
#include <stdproperties.h>
#include <files.h>
#include "contobjs.c"

public void
create_container()

{
    set_adj("wide");
    add_adj("wooden");
    set_name("shelves");
    add_name( ({"bookshelves", "bookshelf", "shelf"}) );

    set_short("series of wide wooden shelves");
  
    set_long("There are several wide shelves here, each one " +
        "made from wood and filled with stacked papers. It " +
        "sort of looks as if these papers are old reports, " +
        "making this an archive of sorts for the fortress.\n");

    add_item( ({"paper", "papers", "archive", "report", "reports"}),
        "There are thousands of old reports here, all neatly " +
        "stacked in tall piles of paper on the wooden shelves. " +
        "Judging from the dates printed on the papers it appears " +
        "that there are several decades of reports here, " +
        "perhaps even longer!\n");

    add_prop(CONT_I_VOLUME, 810000);
    add_prop(CONT_I_WEIGHT, 45350);
    add_prop(CONT_I_MAX_VOLUME, 1200000);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(CONT_I_ATTACH, 1);
}
