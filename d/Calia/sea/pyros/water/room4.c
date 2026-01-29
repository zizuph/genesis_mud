
 /* Jaacar 21 MARCH 98 */

inherit "/d/Calia/std/water_room";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

void
create_water_room()
{
    set_short("Droproom/Mirror Room");
    set_long("This is the drop room for the Wavewalkers.\n");
    add_swim_exit(CAVE+"water/start","south");
}

int
enter(string str)
{
    if (!str || str != "mirror")
    {
        NF("Enter what?  The mirror perhaps?\n");
        return 0;
    }

    write("You boldly swim towards the surface of the "+
        "mirror.  As you come in contact with it you find "+
        "that you seem to slip right through it into the "+
        "reflection you see in it.\n");
    tell_room(environment(TP),QCTNAME(TP)+" boldly swims "+
        "towards the surface of the mirror.  As "+
        TP->query_pronoun()+" comes into contact with it "+
        TP->query_pronoun()+" seems to be sucked into it.\n",({TP}));
    TP->move_living("M",WATER_OBELISK);
    tell_room(environment(TP),"The obelisk suddenly begins "+
        "to vibrate rapidly, causing a humming sound to "+
        "ring throughout the area.  Water begins to form "+
        "inside of the impression, apparently coming from "+
        "within the obelisk itself.  Within seconds there "+
        "is a steady flow of water falling down the side of "+
        "the obelisk forming a pool on the ground.  The "+
        "water stops and all of the water makes its way down "+
        "to the pool on the ground.  The pool begins to "+
        "glow so brightly that you must divert your eyes for "+
        "fear of being blinded.  When you look back the pool "+
        "has formed a mirror-like object, from which you "+
        "see "+QTNAME(TP)+" stepping out of.  The mirror-like "+
        "object melts into a pool of water which is quickly "+
        "absorbed by the ground around the obelisk.\n",({TP}));
    return 1;
}

void
init()
{
    ::init();
    add_action("enter","enter");
}
