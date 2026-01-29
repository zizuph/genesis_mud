/*
 * /d/Kalad/common/wild/pass/underdark/u31.c
 * Purpose    : It has its reasons
 * Located    : Under Hespyre Mts.
 * Created By : Antharanos
 * Modified By: Nikklaus, Oct'97: adapted to dark_dom inherit
 */
/*
 * Undraeth repatriated wholly to Kalad.
 * Removed Avenir reference.
 * 	-Lucius, June 2017
 */
#pragma strict_types

#include "/d/Kalad/defs.h"
#include "dark_dom.h"

inherit DARK_DOM;

void
create_dark_dom()
{
    create_tunnel();
    set_long(long()+
      "Dark passages lead east and west.\n");
    add_exit(DARK(u30), "west");
    add_exit(CPASS(drow/d1), "east");
}
