
/*
 * The Rune Room.
 * 
 * Entrance to the Spellweavers Guild.
 * Players must have completed the quest properly. 
 * A proper player will have the following props in them (defined in
 * /d/Rhovanion/common/rhun/sw/s_s/sw_ent_quest.h):
 * TALKED_TO_WIFE
 * I_DID_NOT_KILL_WIFE
 * I_DID_NOT_KILL_WOODCUTTER
 * I_DID_NOT_KILL_SHADOW_GUY
 * I_DID_NOT_KILL_HAG
 * I_DID_NOT_KILL_GUILD_GUARD
 * 
 * They must rub the ointment on their hands,  which adds the
 * temporary property:
 * OINTMENT_ON_MY_HANDS
 * 
 * Then "trace rune" in this room.
 */
 
inherit "/d/Rhovanion/lib/room";
 
#include "/d/Rhovanion/farlong.h"
#include "/d/Rhovanion/common/rhun/sw/s_s/sw_ent_quest.h"
#include <macros.h>
#include <stdproperties.h>
 
init()
{
    ::init();
    add_action("trace_the_damn_rune", "trace");
}

create_room()
{
   set_short("Rune room");
   set_long("You have entered a round-shaped room.  The light "+
	"here is dim, and shadows lurk in the corners.  The entire "+
	"chamber seems to have been shaped by some magical power "+
	"in a long-forgotten time.  On the north wall is a large "+
	"rune, strangely shaped and carved into the wall's face.  You "+
	"may leave back to the south.\n");
	
    IN;
    
    add_item(({"wall", "walls"}), "The walls are jagged and tilting, "+
	"definitely not formed by organized craftsmen.  On the north "+
	"wall is carved a large and mysterion rune.\n");
    add_item("rune", "The rune is carved directly into the rock "+
	"face of the wall.  It is quite large, and consists of "+
	"a semicircle, concave down, with a smaller circle in the "+
	"center.  Strangely angled lines shoot off from the "+
	"semicircle's upper edge.  There is some sort of power in "+
	"the rune, wonder just who created it.  You feel a strange "+
	"urge to reach out and trace your finger along the rune's "+
	"surface as you stare at it.\n");

   AE(RHUN+"castle/guardroom", "south");
}
 
int
trace_the_damn_rune(string str)
{
    NF("Trace what?\n");
    if(!strlen(str))
	return 0;
    if(str!="rune")
	return 0;

    if((TP->query_bit("Rhovanion", 0, 10))&&
	(!(TP->query_bit("Rhovanion", 0, 11))))
	{
	    write("You trace your finger along the rune, and fell "+
		"yourself moved.\n");
	    say(QCTNAME(TP)+" suddenly disappears.\n");
	    TP->move_living("M", SWG+"arrive");
	    return 1;
	}
	

    NF("You have been banned from entering this place by its "+
	"Guildmasters.\n");
    if(TP->query_bit("Rhovanion", 0, 11))
	return 0;

    NF("You feel that you have not properly completed the requirements "+
	"to this place.  The rune does not respond to your touch.\n");
    if(!((TP->query_prop(TALKED_TO_WIFE))&&
	(TP->query_prop(I_DID_NOT_KILL_WIFE))&&
	(TP->query_prop(I_DID_NOT_KILL_WOODCUTTER))&&
	(TP->query_prop(I_DID_NOT_KILL_SHADOW_GUY))&&
	(TP->query_prop(I_DID_NOT_KILL_HAG))&&
	(TP->query_prop(I_DID_NOT_KILL_GUILD_GUARD))))
	return 0;

    NF("The rune does not respond to your touch.  Perhaps there is "+
	"something more you need.\n");
    if(!(TP->query_prop(OINTMENT_ON_MY_HANDS)))
	return 0;
	
	
    write("You feel a strange magic power go through you, and "+
	"you realize that you now can enter here whenever you "+
	"choose.\n");
	
    /* Set bit so you can always enter from now on */
    TP->set_bit(0, 10);
    
    write("You feel yourself moved.\n");
    say(QCTNAME(TP)+" suddenly disappears.\n");
    TP->move_living("M", SWG+"arrive");
    return 1;
}
