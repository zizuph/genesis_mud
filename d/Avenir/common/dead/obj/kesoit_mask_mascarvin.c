
// file name:  /d/Avenir/common/dead/obj/kesoit_mask_mascarvin.c
// creator(s): Lilith, June 2021
// purpose:    Magical death mask of the Hegemons
// note:       The wearer of this mask is a master of life and death:
//             They resist death magic, scrys, and they don't need food
//             while wearing it.
//     Lilith Apr 2022: Seperated out the Mascarvin quest reward mask from
//             the regular one that is clone_unique to the sarcophagi
//             This version provides scry immunity, and is given as a reward
//             for the one-time Mascarvin quest.



#include "../dead.h"
inherit OBJ + "kesoit_mask.c";

void
create_object()
{
    ::create_object();

    set_short("kesoit death mask");
	set_long("This is the death mask of one of the Hegemons of "
      +"Sybarus. It is carved from a burl of precious kesoit "
      +"wood and polished to a silken sheen so that the deep "
      +"red-black color of the wood and the swirling red-gold "
      +"grain within it seem to pulse with life. "
      +"The wood itself has an unusual scent, woodsy and "
      +"sweet.\n"
      +"A trefoil shape has been burned into the "
      +"wood on the inside of the mask, alongside "
      +"an elvish script.\n");
	  
    // This one provides full scry immunity.
    set_scry_strength(100);    
	
	add_prop(MAGIC_AM_ID_INFO, ({
	"  The kesoit death mask glows with the power of magick\n", 10,
	"  bestowed by Mascarvin herself, the Sybarun Goddess\n", 15,
	"  of death and rebirth\n.", 20,
	"  Designed to sustain a Hegemon through his journey to rebirth\n", 25,
	"  the wearer is blessed with resistance to death magicks, and\n", 30,
	"  is resistant to the need for food.\n", 35,
	"  The one so blessed to wear it is entirely shielded from eyes "+
	"  prying from afar with magicks.\n", 40 }));

    add_prop(OBJ_S_WIZINFO,
      "This death mask was made for one of the Hegemons of Sybarus, "
      +"to sustain him in death and help hasten his rebirth.\n"
      +"It is found randomly in the sarcophagi in the catacombs.\n"
      +" Location: /d/Avenir/commmon/dead/catacombs/crypt_s*.c  \n"
      +" Cloned by: /d/Avenir/common/dead/obj/sarcophagus.c \n"
      +"It will resist death magic(20), grants immunity to scrying, "
	  +"and makes\n"
      +"it so the wearer does not grow hungrier, using a shadow:\n"
      +"/d/Avenir/common/dead/obj/death_mask_sh\n");

}
