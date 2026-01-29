// file name:        /d/Avenir/common/dead/mascarvin/dying.c
// creator(s):       Lilith, Aug 2021
// revision history: 
// purpose:         This is where the alternate death sequence occurs
//                  Nearly identical to resting.c, this room is where
//                  players who have the death shadow from Mascarvin are
//                  moved to. 
// note:           
// bug(s):           
// to-do:  

    // TODO: SHADOW OR CURSE THAT BRINGS PLAYER TO MASCARVIN AT DEATH.
	// offer undead period?
	// SHE PASSES THEM ON TO LARS TO FINISH DEATH SEQUENCE.


inherit "/std/room";
#include "defs.h"

void 
reset_room()
{
     /* Don't reset while there are players here */
    if (sizeof(filter(all_inventory(TO), interactive)))
      return;
    if (!objectp(mascarvin))
	{	
		mascarvin = clone_object(MASCARVIN);
		mascarvin->move_living("M", TO);
    }
}

string
wiz_long()
{
	if (!TP->query_wiz_level())
		return "";
	return "(If a player is here DO NOT TRANS THEM OUT. "
		+"Do <stat here> to read WIZ_INFO.)\n";
}

void
create_room()
{
    set_short("Resting place, the Bosom of Mascarvin");
    set_long("Warmth pervades this amorphous space. Close and red-dark, "
		+"it pulses and thrums with numinous energy. "
		+"The air is heavy with an earthy, feminine scent that calls "
		+"up visceral pre-memories of maternal nurturing. The milky mist "
		+"above swirls and flows into the shape of a grinning skull "
		+"that seems to be looking down upon you. "
		+"Anguished cries and contented murmurs echo in a faint "
		+"chorus, whilst a roiling mass presses upon your conscious"
    	+"ness - the psychic remnants of those recently dead and "
    	+"those long forgotten. You have a sense of the multitudes "
	    +"that once lived in the penumbra of the Source, dedicated to "
	    +"the Gods, and gathered to the bosom of Mascarvin for "
	    +"nurturing, awaiting the possibility of rebirth.\n"
		+"@@wiz_long");
	
    add_item(({"ceiling","mist", "skull", "grinning skull"}),
		 "The mist, you now surmise, is the stuff of souls. "
		 +"It swirls overhead in the form of a skull "
		 +"grinning down at you. It glows just enough to "
		 +"illuminate this place.\n");
		 
	add_prop(ROOM_M_NO_TELEPORT, 
	    "An angry goddess-figure wreathed in red-gold flames "
        +"appears to prevent you from doing that.\n");
	add_prop(ROOM_M_NO_MAGIC, anti_magic(TP));
	add_prop(ROOM_M_NO_SCRY, "A dark room.\n");

    add_prop(OBJ_S_WIZINFO, "This room is part of an alternate "
	    +"death sequence. Player will be passed along to LARS "
		+"momentarily.\n");	
    IN_IN;
    reset_room();
}
