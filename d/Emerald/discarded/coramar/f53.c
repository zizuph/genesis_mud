/*
 * F53.c
 * Trail through the coramar forest.
 * Alaron - Feb 1998
 */

#include "/d/Emerald/defs.h"
#include "coramar.h"
#include "dirheader.h"
#include <stdproperties.h>

inherit BASEFOREST;

void
create_forest()
{
    set_long("   The cool, swift breeze blows east to west down the trail, rustling "+
	"the leaves of the high bushes and creating an eerie whistling noise as the "+
	"wind passes between the massive tree trunks. The heavy blanket of thick "+
	"gray mist casts the entire forest into an intimidating, dark gray gloom. The "+
	"path continues into the mist and shadows to the east and west.\n\n");

    add_fexit(CORAMAR+"f47", "east", 0);
    add_fexit(CORAMAR+"f52", "west", 0);
}
