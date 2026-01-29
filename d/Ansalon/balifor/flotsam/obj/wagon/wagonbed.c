#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include "caravan.h"

inherit AR_FILE

object gWagon;
mixed gCargo;

void
create_krynn_room()
{
    set_short("in a wagonbed");
    set_long("You are sitting in a large, covered " +
      "wagon. Rough grey canvas forms an arching roof over the " +
      "wagonbed. If the wagon is standing still you can go out. " +
      "@@cargo@@\n");

    add_item(({"canvas","grey canvas","rough canvas"}),
      "The rough, grey canvas forms an arching roof, covering " +
      "the cargo from weather and wind and prying eyes.\n");
    add_item(({"roof","arching roof"}),
      "The roof protects the cargo from weather and wind.\n");

    add_item(({"view","surroundings"}),
      "The canvas roof blocks the view of the outside.\n");

    add_exit("@@query_outside@@",
      "out","@@can_go_out@@",0);

    add_prop(ROOM_M_NO_ATTACK, "Inside the wagon you would be the last " +
      "to draw a weapon and first to die. You will have to wait untill " +
      "wagon arrives to its destination.\n");

    add_prop(ROOM_M_NO_MAGIC_ATTACK, "The place is so small that any " +
      "combat spell would for sure affect you as well. But when the " +
      "wagon reaches its destination ...\n");

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
    p->remove_prop(FLOTSAM_LIVE_O_WAGON_STEED);
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
	write("The wagon is moving, you cannot leave now.\n");
	return 1;
    }
    write("You jump out of the wagon.\n");
    if (steed = TP->query_prop(FLOTSAM_LIVE_O_WAGON_STEED))
    {
	set_alarm(0.5,0.0,&retrieve_horse(TP,steed));
    }
    return 0;
}

string
cargo()
{
    if (stringp(gCargo))
	return "The wagonbed is packed almost full with " + gCargo + ".";
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
	  "the driver makes you stop. Better leave them alone.\n");
    }
    gCargo = c;
}


