/*
 * F40.c
 * This is the location of the fourth and final rune stone, this one is slightly 
 * harder to get, since the stone is hidden in a fox hole.
 * Alaron - Feb 1998
 */

#include "/d/Emerald/defs.h"
#include "coramar.h"
#include "dirheader.h"
#include <stdproperties.h>

inherit BASEFOREST;

object runestone;
int rune_in_hole;

int do_dig(string str);

void
create_forest()
{
    set_long("   The path rounds a gradual curve here, leading northeast toward "+
	"a more narrow foot path and west toward an enormous wall of vegetation. A "+
	"cool, damp breeze blows across the trail, gently ruffling the leaves and "+
	"shaking the vines which hang down from seemingly endless branches high above. "+
	"Nestled strategically under the canopy effect of a small bush, you can see "+
	"a small animal hole.\n\n");

    add_item( ({"wall", "wall of vegetation"}),
	"It seems to go up forever until the mist obscures your view of it. The thing "+
	"is enormous, and it is made entirely of leaves, vines and other plants. The "+
	"sight is breathtaking, as well as deathly frightening.\n");

    add_item( ({"hole", "foxhole", "small hole", "animal hole"}),
	"The small animal hole has the appearance of a well-used fox hole. There are "+
	"fresh paw prints in and around the hole. "+
	VBFC_ME("hole_description")+"\n");
 
    reset_euid();
    runestone=clone_object(CORAMAR_OBJ+"rstone4");
    rune_in_hole = 1;
 

    add_fexit(CORAMAR+"f39", "northeast", 0);
    add_fexit(CORAMAR+"f41", "west", 0);
}

string
hole_description()
{
   if (rune_in_hole) {
	return "Peering further into the hole, you can see the faint outline of something "+
	"small, round and stone. It is too small to pull out with your hands. It might "+
	"be easier if the hole was dug out more.\n";
    }
   else {
        return "The hole looks as though it has been thoroughly dug out. You wonder "+
	   "what could have been in there worth digging for?\n";
}

}
void
init()
{
    ::init();
    add_action(do_dig, "dig");
}


int
do_dig(string str)
{
    if ( (str == "out hole") || (str == "hole") || (str=="out stone") ||
	(str == "stone") || (str == "for stone") || (str == "out") )
    {
        if (!rune_in_hole)
	 {
             notify_fail("The hole has already been dug out.\n");
             return 0;
	 }
        write("You dig furiously with your hands and you free a small stone from "+
	      "the depths of the animal hole.\n");
        say(QCTNAME(TP)+" digs furiously with "+TP->query_possessive()+" hands and "+
		"manages to free a small stone from the depths of an aminal hole.\n");
        runestone->move(this_object(), 1);
	rune_in_hole = 0;
        return 1;
    }
    else {
       notify_fail("Dig what?\n");
       return 0;
    }

}
   
