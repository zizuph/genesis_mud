/*
 * F5.c
 * Forest Room, Coramar
 * - Alaron Feb 1998
 */

#include "coramar.h"
#include "dirheader.h"
#include "/d/Emerald/defs.h"
#include <stdproperties.h>

inherit BASEFOREST;

void
create_forest()
{
    set_long("   The wide path wanders lazily through the misty forest, disappearing "+
	"behind slowly shifting clouds of gray, then suddenly reappearing again before "+
	"a towering tree trunk the width of ten men. The path's main course seems to "+
	"run northeast-southwest, however there is a narrow footpath leading off of "+
	"the path into the dark mist to the east. A cool, gentle breeze drifts slowly "+
	"across the path. Oddly enough, the mist seems to flow in a direction opposite "+
	"the wind.\n\n");

    add_fexit(CORAMAR+"f7", "northeast", 0);
    add_fexit(CORAMAR+"f8", "east", 0);
    add_fexit(CORAMAR+"f3", "southwest", 0);   
}