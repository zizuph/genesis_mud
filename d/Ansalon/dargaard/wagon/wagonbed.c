#include "/d/Ansalon/common/defs.h"
#include "caravan.h"
#include <macros.h>

inherit AR_FILE

object gWagon;
mixed gCargo;

void
create_krynn_room()
{
    set_short("in a black chariot");
    set_long("As you look around you see an old rusted seat with cobwebs "+
             "all over it, the padding has worn away and left just bars to "+
             "sit on. The walls seem to scream out in your mind, they "+
             "seem to be begging for something. As you look out the "+
             "window, everything looks darker then usual. The road "+ 
             "seems almost to be burning with fire, as if you were in hell. "+
             "If the chariot is standing still you can go out.\n");

    add_item(({"view","surroundings"}),
      "You see the Dargaard Mountains outside of the window, the small "+
      "path that the chariot follows seems to burn with an intense fire.\n");

    add_prop(ROOM_I_NO_ATTACK, "There isn't enough room to start a fight in here!\n");

    add_exit("@@query_outside@@",
      "out","@@can_go_out@@",0);
}

public void
set_wagon(object wagon)
{ gWagon = wagon; }

public object
query_wagon()
{ return gWagon; }

string
query_outside()
{ return file_name(E(gWagon)); }

void
retrieve_horse(object p, object steed)
{
    p->remove_prop(DARGAARD_LIVE_O_WAGON_STEED);
    if (objectp(p) && objectp(steed))
    {
	steed->move_living("M",E(p));
	p->catch_msg("You fetch your " + steed->short() + " from the " +
	  "string of remounts.\n");
	tell_room(E(p), QCTNAME(p) + " fetches " + HIS(p) + " " +
	  steed->short() + " from the string of remounts.\n", p);
    }
}   

int
can_go_out()
{
    object steed;
    if (gWagon->query_moving())
    {
	write("The chariot is moving, you cannot leave now.\n");
	return 1;
    }
    write("You jump out of the chariot.\n");
    if (steed = TP->query_prop(DARGAARD_LIVE_O_WAGON_STEED))
    {
	set_alarm(0.5,0.0,&retrieve_horse(TP,steed));
    }
    return 0;
}

string
cargo()
{
    if (stringp(gCargo))
	return "";
    else
	return "";
}

void
set_cargo(mixed c)
{
    if (stringp(gCargo))
    {
	remove_item(gCargo);
    }
    if (stringp(c))
    {
	add_item(c,"You start examining the " + c + ", but a sharp word from " +
	  "the charioteer makes you stop. Better leave them alone.\n");
    }
    gCargo = c;
}


