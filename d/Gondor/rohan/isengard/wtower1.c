/*                     7
 *     /d/Gondor/opus/rohan/isengard/watchtower1.c
 *
 *     Opus, June 1997
 *
 *     Copyright   1997 by Robert Miller
 *
 *     Modification log:
 */
#pragma strict_types

#include "defs.h"

inherit ISEN_ROOM;
		  
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

#define PATH_WAY   "/d/Gondor/rohan/isengard/isengate.c"
#define NPC_FILE   ISEN_DIR + "/npc/archer.c"

// Prototypes
string  pathdesc();
void    reset_room();

object *Npcs = allocate(2);


public void
create_isengard()
{
    set_short("watchtower of Isengard");
    set_long( BSN(
       "Located high above the gates below, this is one of the two watch "+
       "towers used to defend Isengard. There is an opening on the wall "+
       "just large enough for someone to be able to fire a weapon safely "+
       "onto the pathway below. A large banner hangs from one of the "+
       "walls. The only noticeable way out is back onto the lookout."));
    
    add_item( ({"path", "pathway", "gates", "opening", "gate",
		"outside"}), pathdesc);
    add_item( ({"wall", "walls"}), BSN(
       "The walls seem quite solid except for an opening and a doorway. "+
       "The doorway leads back to the lookout while the opening allows "+
       "guards the ability to see outside."));
    add_item( ({"floor", "ground"}), BSN(
       "There is a fine layer of dirt covering the floor. Wind "+ 
       "stirrs up the dirt a bit as it whips through the tower.")); 
    add_item( ({"banner", "large banner"}), BSN(
       "This banner is crafted from a fine cloth, and is simply decorated "+
       "with a large, white hand on a dark background."));
    add_cmd_item( ({"banner", "large banner"}), ({"tug", "pull", "grab",
		    "get", "take"}), BSN(
	"As you grab hold of the banner, you notice that it is firmly "+
        "attached to the wall. When you let go, ripples form and travel "+
        "upwards toward the top of the banner."));
    add_item( ({"tower", "watch tower", "towers", "watch towers"}), BSN(
        "This is of one of two watch towers that loom over the gates "+
        "and pathway below."));
    add_item( "dirt", BSN(
	"A fine layer of dirt, covering the floor of the tower, occasionally "+
	"gets stired up when wind whips through the tower."));
    add_item( "doorway", BSN(
	"The only opening large enough for a person to fit through leads "+
	"back out onto the lookout to the east.")); 
    add_item( ({"isengard", "fortress", "vast fortress"}), BSN(
        "The expanse of Isengard extends outward as a vast fortress "+
	"ringed by the steep cliffs of the ringwall."));
    add_item( ({"ringwall", "steep cliff", "steep cliffs", "cliffs",
		"cliff"}), BSN(
	"Almost a hundred feet high, the ringwall surrounds all of "+
	"Isengard providing additional protection from any hostile "+
	"creatures or enemies."));
    add_item( ({"ceiling", "roof"}), BSN(
        "High above, a roof has been constructed to provide "+ 
	"a shelter for the guards from the elements.")); 
    add_item( ({"cloth", "fine cloth"}), BSN(    
        "The fine cloth is very smooth to the touch. It "+
	"is very dark in color and has only a single descoration on it; "+
	"a large white hand."));
    add_item( ({"hand", "large hand", "white hand", "large white hand"}), BSN(
        "The white hand has been placed in the middle of the banner as "+
	"the sign of Saruman's army."));
    add_item( "lookout", BSN(
	"The lookout, seen to the east through the doorway, runs across "+
	"the top of the ringwall allowing guards to safely stand and keep "+
	"watch for any threats."));
    add_item( ({"rock", "black rock", "smooth rock", 
	"smooth black rock"}), BSN(
            "This strange black rock makes up the entire area. "+
	    "It has been carved and shaped to form this guard tower that "+
	    "rises high above the ringwall."));



    add_exit(ISEN_DIR + "lookout1.c", "east", 0);
    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}  /* create_isengard */


public void
reset_room()
{
     clone_npcs(Npcs, NPC_FILE, 3.0);
}  /* reset_room */
 
/*
 * Function name: pathdesc
 * Description:   returns a description of the room below (isengate.c)
 *                as well as any living thing that happen to be there.
 * Returns:       description of isengate.c and any living things that
 *                are also in the room at the time (NPCs or PCS).
 */

string
pathdesc()
{
    string pdesc;
    object *lnames;

    switch (tod())
    {
	case "night":
	    pdesc = "The darkness from night prevents a good "+
		"view of the pathway below. Through the calm night, "+
		"movement and occasional mumbling can be heard "+
		"and the glow from a hand-held lantern can be seen from "+
		"below.";
	    break;
	default:
	    pdesc = "Looking down, a clear view of the pathway "+
		"that leads up to the outer gates can be seen. ";
	    seteuid(getuid(TO));
	    (PATH_WAY)->load_me();
	    lnames = FILTER_LIVE(all_inventory(find_object(PATH_WAY)));
	    if (sizeof(lnames)>0)
            {
               pdesc += "Currently " +COMPOSITE_LIVE(lnames)+" are "+
               "on the pathway below.";
            }
	    else
            {
               pdesc += "Currently there is no one before the gates.";
            }
            break;
    }

    return BSN(pdesc);
}  /* pathdesc */


