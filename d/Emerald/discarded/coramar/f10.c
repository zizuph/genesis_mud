/*
 * F10.c
 * Wide path through the Coramar forest.
 * - Alaron Feb 1998
 */

#include "/d/Emerald/defs.h"
#include "dirheader.h"
#include "coramar.h"
#include <stdproperties.h>

inherit BASEFOREST;

void
create_forest()
{ 
    set_long("   The trail through the forest is wide here, but the mass of "+
	"hanging, tangled vines makes maneuvering through it very tedious and "+
	"sometimes painful. Some of the larger vines have thorns on them "+
	"for protection. A cool, gentle breeze blows east-west down the path, "+
	"softly bending the waist-high bushes and shrubs and creating an eerie "+
	"whistling noise. All around you are the dark, mist-shrouded shadows of "+
	"enormous tree trunks. The wide trail continues east and west from here.\n\n");


    add_fexit(CORAMAR+"f7", "west", 0);
    add_fexit(CORAMAR+"f50", "east", 0);
}