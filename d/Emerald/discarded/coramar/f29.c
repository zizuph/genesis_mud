/*
 * F29.c 
 * Grave of the First
 * Forest of Coramar
 * Alaron March 1998
 */

#include "/d/Emerald/defs.h"
#include "dirheader.h"
#include "coramar.h"

inherit BASEGRAVE;

void
create_graveyard()
{
    set_long("   You are standing in what appears to be a graveyard of some kind. The "+
	"small clearing in the middle of the dense, mist-covered forest seems to be "+
	"unaffected by the mist. The dense, gray cloud hovers and swirls at the edge "+
	"of the iron fence but seems unable to move beyond. The black iron fence is "+
	"short and more decorative than functional. It serves more as a boundary line "+
	"indicating the edge of the graveyard. The clearing made of perfect, straight "+
	"lines and well-tended grass continues to the east and west. Just east of here "+
	"there is a small break in the iron fence, leading off into the forest.\n\n");    

    add_fexit(CORAMAR+"f30", "east", 0);
    add_fexit(CORAMAR+"f28", "west", 0);
}