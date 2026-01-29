
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("Radagast's home");
    set_long("This is Radagast's home in Rhosgobel.  It "+
	"is small but cozy, made from stones with a thatched "+
	"roof.  A few odds and ends, the wizard's work, stand "+
	"around, though you had best not touch them.  "+
	"It appears Radagast is still out travelling through "+
	"Middle Earth; perhaps if you return at a later date, "+
	"he will have returned home by then.\n");

    add_item(({"odds", "ends", "odds and ends", "articles", "work"}), 
	"There are a few strange items here, but you had best "+
	"leave them alone, as they appear to be part of "+
	"Radagast's work.\n");

    AE(RHOS+"road2", "south");
    
}
