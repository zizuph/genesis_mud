/*
 *   /d/Gondor/ithilien/poros/obj/report.c
 *
 *   This is the quest item the corsair captain gives you to take to Yrchor
 *   in Minas Morgul. It is the coded results of an interogation.
 *
 *   Talisan,  February 1996
 */

#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_object()
{
    set_name("report");
    add_name(({"paper", "sheet"}));
    add_name("corsair_quest_report");
    set_short("sheet of paper");
    set_pshort("sheets of paper");
    set_adj(({"sheet of", "grey", "folded", "corsair"}));
    set_long("This is a folded sheet of grey paper. Written on the "
      + "paper are symbols of mysterious origin, perhaps some form of "
      + "code... Regardless, the script is completely unintelligible "
      + "and impossible to read. At the bottom of the page is the "
      + "circled image of a great winged drake.\n");

    add_prop("corsair_quest_report", 1);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 20);

    add_cmd_item(({"report", "the report", "paper", "the paper", 
        "sheet", "the sheet"}), "read", "@@read_report@@");
}

public string
read_report()
{
    write("You find it impossible to make any sense from the "
      + "strange symbols on the paper. You have no idea what it "
      + "means, if anything at all.\n");
}
