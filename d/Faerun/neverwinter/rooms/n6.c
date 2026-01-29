/*  /d/Faerun/neverwinter/rooms/1o.c
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

inherit BASE_NEWERW_OUTDOOR;


void
create_neverw_outdoor()
{
    extraline = "The street has narrowed immensely compared to the main "
       +"street that you entered Neverwinter from. Compared to the main "
       +"street, this side street of Protector's Enclave is more noble "
       +"or extravagant. Banners of all colors and sizes hang from the "
       +"various buildings and shops that line the small street. Grand "
       +"Knights ride up and down the street in a ceremonial manner, "
       +"prompting wonder and awe from the citizens of Neverwinter.";
    
    set_short("Streets of Protector's Enclave");
    
    //If we want herbs here.
    //add_std_herbs("mere");
        
    add_item(({"knights"}),
       "The Knights are all wearing grand, shiny silver plate armor. "
       +"The Knights push pass Neverwinter's citizens, acting high and "
       +"mighty, and most believe that their demeanor is justified, for "
       +"they're the sole protectors of Neverwinter from the horrors "
       +"that await in the Neverdeath Crypts.\n");

    add_item(({"banners"}),
       "Gazing over the banners, you spot three distinct variations. "
       +"The first, colored red, depicts a man wielding a large blade, "
       +"standing atop "
       +"a mound of bodies, presumably undead from the crypts. The "
       +"second banner, colored black, depicts a lightning bolt, "
       +"striking what can be "
       +"considered as a lich. The third banner, colored blue, "
       +"depicts only one object, "
       +"a large hammer, standing up right.\n");
	   
    add_item(({"red banner"}),
       "The banner is intricately designed, and was clearly created with "
       +"care. Most knights that roam the streets possess the banner's "
       +"symbol somewhere upon their armor. The man depicted in the "
       +"banner has donned an immense set of pitch black armor, and "
       +"wields a massive blade, the same dark shade as the armor. "
       +"The man has stabbed his blade into a mound of mangled corpses. "
       +"The corpses are clearly of the lower class, shriveled from "
       +"malnutrition and wearing very tattered clothing.\n");
	   
    add_item(({"black banner"}),
       "The banner seems to have been designed in a hurry, as the "
       +"lightning bolt on each banner seems to have been stitched on "
       +"sloppily. The depiction of the lich; however, seems to have "
       +"been the most focused on feature of the banner. It has its arms "
       +"outstreched as if welcoming the devestating attack, absorbing "
       +"power from it. The knights seen wearing this banner seem to be "
	   +"outcast from the other knights, and instead of wearing the "
	   +"shining silver armor like the knights wearing the red banner, "
	   +"these knights are wearing dull and lackluster iron suits.\n");
	   
	add_item(({"blue banner"}),
       "The banner is the most simple of the three. The hammer is "
       +"engraved with elvish runes and wrapped in the finest silk. "
	   +"The knights that wear the hammer banner are all dressed in "
	   +"silver armor, with bright blue robes draped over their "
	   +"shoulders. These knights seem to be the most open to other "
	   +"races, as you see that even a goblin is adorned in the "
	   +"armor.\n");
	   
	add_item(({"street"}),
       "The street is worn down, and hasn't been freshly cobbled like "
       +"the main street of Protector's Enclave; however, work is "
       +"clearly being done on the road, as gardners and street workers "
       +"are hard at work, tending to the street, preparing it for even "
       +"more travel.");
	   
    add_item(({"gardeners"}),
       "The gardeners are all humans. They wear worn and tattered "
       +"clothing, much like the corpses depicted in one of the banners "
       +"Behind them, riding upon a black horse, is one of the knights "
       +"that wear the black banner. Every now and then, the knight hits "
       +"one of the gardeners, yelling that they are being too slow at "
       +"their job.\n");
	   
    add_item(({"workers"}),
       "The street workers, just like the gardeners are all humans. "
	   +"And just like the gardeners, the street workers wear rags for "
	   +"clothing. A knight stands behind them, a black shoulder cape "
	   +"concealing the knights armor. He has in his left hand a whip, "
	   +"in which the knight grips tightly.\n");

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "n5.c", "west");
	add_exit(ROOM_DIR + "nae3.c", "southeast");
	add_exit(ROOM_DIR + "n7.c", "northeast");
}


void
reset_faerun_room()
{
    set_searched(0);
}