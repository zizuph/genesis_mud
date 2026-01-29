/*  /d/Faerun/neverwinter/rooms/inel.c
*
*   By Thessius, 2020
* 
*/

#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "defs.h"

inherit BASE_NEWERW_INDOOR;


void
create_neverw_room()
{
    set_long("Imelrain's Magical Cloths.\n"
       +"This open section of the alley is cluttered with various "
       +"stands and racks, holding a multitude of colorful cloths. "
       +"Set within the eastern wall is a small shop window, a bell is "
       +"placed upon the window, with a small sign below it. Only one or "
       +"two citizens are present in the hidden shop at a given time. "
	   +"Draped above the shop window is a red banner. "
       +"The shopkeeper has conjured a magical night sky that lights "
       +"the shop itself.\n");
    
    set_short("Imelrain's Magical Cloths");
    
    //If we want herbs here.
    //add_std_herbs("mere");
        

    add_item(({"red banner", "banner"}),
       "The banner is intricately designed, and was clearly created with "
       +"care. Most knights that roam the streets possess the banner's "
       +"symbol somewhere upon their armor. The man depicted in the "
       +"banner has donned an immense set of pitch black armor, and "
       +"wields a massive blade, the same dark shade as the armor. "
       +"The man has stabbed his blade into a mound of mangled corpses. "
       +"The corpses are clearly of the lower class, shriveled from "
       +"malnutrition and wearing very tattered clothing.\n");
	   
    add_item(({"window"}),
       "The window leads to a brightly lit room. A door sits on the far "
       +"wall, latched shut. The room contained a few shelfs, with even "
       +"more colorful cloths, just like the ones outside. A small "
       +"wooden stool on the other side of the window, behind a just as "
       +"small wooden desk.\n");
	   
    add_item(({"stool"}),
       "The stool is balanced on three legs, with one of them severely "
	   +"damaged. On the damaged leg is a faint inscription.\n");
	   
    add_item(({"inscription"}),
       "The inscription reads: 'Wooden Stool, courtesy of Undelon's "
       +"Woodworking!'\n");
	   
	add_item(({"bell"}),
       "The bell is actually a prop and serves no use. Pressing your "
       +"hand on the bell emits no sound. Instead, the shopkeeper gives "
       +"you the worst looks you've ever gotten.\n");
	   
    add_item(({"cloths"}),
       "The cloths here range in every color; however, the shop seems "
       +"to have an abundance of purple and orange cloths, selling them "
       +"at a reduced price.\n");
	   
	add_item(({"sign"}),
       "The sign is worn beyond recognition, and has a few knives "
	   +"thrust into the old rotted wood.\n");
	   
	add_item(({"knives"}),
       "The curved steel knives are planted firmly in the sign, and do "
       +"not budge, no matter how strong you pull on them.\n");
	   
    add_item(({"racks", "stands"}),
       "The stands and racks have small hooks outstretched from a "
       +"mahogany base. "
       +"Draped over the hooks are cloths that one may only find in "
       +"Neverwinter.\n");
	   
    add_item(({"citizens"}),
       "Those who browse the shop are usually cloaked, hiding their "
       +"appearance. They trace their fingers upon the various fabrics, "
       +"nodding or making a sound of confirmation as they make their "
       +"way from item to item.\n");
	   
    add_item(({"sky"}),
       "The artificial ceiling is constantly moving, with it's conjured "
	   +"stars blinking in and out of existance.\n");

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "nae1.c", "west");
}


void
reset_faerun_room()
{
    set_searched(0);
}