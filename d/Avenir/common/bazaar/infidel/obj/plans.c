inherit "/std/object";
#include "../infidel.h"

void
create_object()
{
    set_name("papers");
    add_name(({PLAN_ID, "plans","plan","bundle","sheaf","paper"}));
    set_short("large bundle of papers");
    set_adj(({"large","heavy","thick"}));
    set_long("It is a large sheaf of papers, maps, and charts. Much "
      + "of the paper seems yellowed or burnt, as if it were "
      + "carried over a long journey. The writing on the "
      + "paper appears to have been written in a coded shorthand.\n");

    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_M_NO_BUY, "The papers are not for sale.\n");
}
