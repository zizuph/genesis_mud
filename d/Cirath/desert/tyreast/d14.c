inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"

string my_long();

void
create_room()
 {
  set_short("Desert East of Tyr");
  set_long(my_long()+".\n");
    add_exit(DESERT + "d15","east");
    add_exit(DESERT + "r1","south");
    add_exit(DESERT + "r2","southeast");
add_item("dust","The ever present dust of "
        +"Athas is everywhere.  When it is not being kicked up "
    +"by your footsteps, it is blowing around on the dry "
        +"winds that swirl constantly.\n");
add_item("sand","Sand is everywhere here, from the salt flats "
        +"to towering sand dunes.  It is almost as prevalent as "
        +"as the dust that seems to end up in or on everything.  "
        +"Sometimes the sand is coarse and rough, sometimes it is "
        +"so fine it is like silk.  Whatever form its in, its "
        +"always here.\n");
add_item(({"salt","crystals","salt crystals","crystal"}),
        "The remnants of some long forgotten body of water, these "
        +"salt crystals now form are mingled with regular sand "
        +"in many of the salt flats that are present in Athas.  "
        +"The salt reflects the sun more brightly than regular "
        +"sand does, hence the glare her is very bad.\n");
add_item(({"mountains","ringing mountains"}),"Standing tall and "
        +"imperious to your north, the Ringing Mountains stand "
        +"as the northern guardians of Tyr.  Iron is mined from "
        +"them by the order of Kalak, sorcerer king of Tyr.  "
        +"There are also tales of roving monster hordes that hide "
        +"in the mountains, using ancient fortresses and caverns.\n");
add_item(({"dune","dunes"}),"Sand dunes ripple through the desert "
        +"outward from Tyr, as if Tyr were a stone dropped in a "
        +"pond.  Sometimes, high, sometimes low, the dunes are "
        +"fairly constant in appearnce, and only vary in size "
        +"and shape.\n");


}

string
my_long()
{
string *long;
long = ({"You are in the desert east of the great city of Tyr.  "
	+"Dry, cracked earth releases small puffs of dust with "
	+"each step you take.  To the north, you can see the "
	+"Ringing Mountains, which lie to the north of Tyr",
	"You plod slowly through the burning desert east of Tyr.  "
	+"Dry ground and low, coarse sand dunes surround you, "
	+"while to the north, you can see the Ringing Mountains "
	+"in the distance, providing a northern barrier which "
	+"protects Tyr","You have entered a salt flat now, and "
	+"all around you the sun reflects off of the crystalline "
	+"salt on the ground, causing a painful glare to sting "
	+"eyes","Low dunes stretch across your field of view "
	+"here.  The thick, grainy sand flows almost like water as "
	+"you walk through it.  To the north, the light of Athas's "
	+"twin suns reflects off the Ringing Mountain, seemingly "
	+"beckoning to you"});
	
	return long[random(sizeof(long))];
}

