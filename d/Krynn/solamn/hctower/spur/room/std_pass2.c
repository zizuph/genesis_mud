// std pass2
// grace aug 1994

#include "/sys/stdproperties.h"
#include      "../local.h"

inherit SPURRM;


/*
 * This function defines the room.
 */
varargs void
make_the_room(string extra_long)
{
    if (!extra_long) { extra_long = "\n"; }

    set_name("passage");

    LONG("Torches placed in sconces at regular intervals down the "+
        "passage make it bright as day.  The stone floor is swept "+
        "and polished to a high sheen that reflects the light.  " +
         extra_long);

    AI(({"torches","torch"}), "The torches burn brightly.\n");
    AI("sconces", "Stone brackets made for holding torches.\n");
    AI(({"floor","stone floor"}),
        "It is so shiny you can see your reflection in it.\n");
    AI(({"reflection", "my reflection"}), "Yes, sure enough, that "+
        "is a distorted image of your face. At least, you hope it "+
        "is distorted. You've seen draconians prettier than that!\n");
    AI(({"walls", "wall", "passage", "passageway", "hall", "hallway"}),
        "The walls are made of smooth dark stone. The passageway is "+
        "wide enough for five men to walk abreast.\n");
 
    LIGHT;
}


