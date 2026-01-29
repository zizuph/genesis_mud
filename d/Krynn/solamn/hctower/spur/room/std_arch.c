// std_arch
// grace aug 1994

// each room should have individual SHORT desc
// each room should have an indivudual AI for the passage beyond
// the slits, perhaps filter living in the rooms beyond...

#include "/sys/stdproperties.h"
#include "../local.h"

inherit SPURRM;

// This function defines the room.
varargs void
make_the_room(string extra_long)
{
    if (!extra_long) { extra_long = "\n"; }

    set_name("archers' station");
    // SHORT("");
    LONG("You stand in a room deep inside the Knight's Spur.  "+
       "Despite the high ceilings, the unrelieved stone seems "+
       "to weigh upon you.  Torches placed in sconces at "+
       "regular intervals along the walls provide excellent "+
       "illumination. The stone floor is swept and polished "+
       "to a high sheen that reflects the light." +
         extra_long);

    AI(({"torches","torch"}), "The torches burn brightly.\n");
    AI("sconces", "Stone brackets made for holding torches.\n");
    AI(({"floor","stone floor"}),
        "It is so shiny you can see your reflection in it.\n");
    AI(({"reflection", "my reflection"}), "Yes, sure enough, that "+
        "is a distorted image of your face. At least, you hope it "+
        "is distorted. You've seen draconians prettier than that!\n");
    AI(({"walls", "wall", "stone", "stones"}),
        "The walls are made of blocks of smooth dark stone.\n");
    AI(({"roof", "ceiling", "ceilings"}),
        "The ceiling arches high above your head.\n");
    AI(({"opening", "openings", "narrow openings", "slit", "slits"}),
        "Openings in the stone about the width of your hand and " +
        "the length of your forearm. There is ample space " +
        "between each slit for two men to stand against the wall.\n");
    ACI(({"opening", "openings", "narrow openings", "slit", "slits"}),
        ({"open", "enter", "feel", "peer into", "look through"}), 
        "The slits are too small to do anything but look through " +
        "and thrust spears or shoot arrows from them. Peering into "+
        "one of the openings you can see a passageway beyond.\n");

    LIGHT;
}


