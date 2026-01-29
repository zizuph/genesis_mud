/*
 * /d/Gondor/ithilien/forest/olicamp.c
 *
 * Coded by Elessar.
 *
 * Modification log:
 * 30-Dec-1997, Gnadnar: general revision
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

#include "/d/Gondor/defs.h"

object	Oli, Haradrim;
static object  dung;

public int	do_smell(string arg);

public void
create_gondor()
{
    set_short("A large clearing in the Ithilien forest");
    set_long(
	"The trail from the west ends here in a large clearing. "+
	"In the center of the clearing you see a pile of vegetables "+
	"and a large tub of liquid. "+
	"Strange prints are visible in the trampled, muddy ground.\n");
    add_item( ({ "pile", "pile of vegetables", "vegetables", 
		"vegetable matter", "cabbages", "turnips", "carrots",
		"plants", "vegetable pile"}),  
	"The pile contains cabbages, turnips, carrots and other "+
	"vegetable matter that you cannot identify.\n");
    add_item( ({ "tub", "liquid" }), 
	"The wooden tub contains a murky, unappetizing liquid.\n");
    add_item( ({ "ground", "mud" }), 
	"The muddy ground is heavily trampled.  Some of the mud appears "+
	"to be animal waste.\n");
    add_item( ({ "animal waste", "waste", "excrement" }), 
	"Large quantities of animal waste are trampled into the mud.\n");
    add_item( ({ "trail", "woods", "trees", "clearing", "forest" }), 
	"Forest surrounds the clearing. The only exit is the "+
	"trail leading west.\n");
    add_item( ({ "tracks", "prints" }), 
	"The huge, round prints are deep enough to suggest a "+
	"considerable weight.\n");

    add_cmd_item( ({ "liquid from tub", "from tub", "from wooden tub" }),
	({ "drink" }),
	"The liquid is much too nasty to drink.\n");

    add_exit(ITH_DIR+"forest/olipath1","west",0);

    dung = clone_object("/d/Gondor/common/obj/olidung.c");
    dung->move(TO);

    reset_room();
}

public void
reset_room()
{
    Oli = clone_npc(Oli, (NPC_DIR + "oliphaunt"));
    Haradrim = clone_npc(Haradrim, (NPC_DIR + "haradrim"));
}


public void
init()
{
    ::init();
    add_action(do_smell, "smell");
    add_action(do_smell, "sniff");
}

/*
 * Function name:	do_smell
 * Description:		handle attempts to smell/sniff
 * Arguments:		string arg -- whatever the player typed
 * Returns:		1 if we understand arg, 0 if not
 */
public int
do_smell(string arg)
{
    if ( !arg || arg == "mud" || arg == "waste" || arg == "animal waste" ||
    arg == "excrement" )
    {
	write("The smell of animal waste permeates the clearing.\n");
	return 1;
    }
    return 0;
}
