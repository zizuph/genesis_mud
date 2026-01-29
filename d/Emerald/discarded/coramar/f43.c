/*
 * F43.c
 * Another path section in the coramar forest.
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
    set_long("   The sound of the cool breeze drifting across the path, shaking "+
	"the bushes and leaves is almost drowned out by the sound of water gently "+
	"running down a brook to the south. It sounds extremely close, but you can't "+
	"seem to separate the foliage on the south side of the path enough to see "+
	"anything. A thick blanket of mist hovers over the entire forest, distorting "+
	"trees, vines and grass into nothing more than bleak, gray shadows.\n\n");


    add_fexit(CORAMAR+"f42", "east", 0);
    add_fexit(CORAMAR+"f45", "west", 0);
}