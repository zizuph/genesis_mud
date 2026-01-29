#include "defs.h"

object door;
object alchemist;

object
query_alchemist()
{
    return alchemist;
}

void
set_alchemist(object who)
{
    alchemist = who;
}

CONSTRUCT_ROOM {
    set_short("The dwarven alchemist's home");
    set_long(
	"You have arrived in what must be the dwarven alchemist's home.\n"+
	"The only things of interest here is his bed and a clean desk" +
        "@@desc_alchemist@@, otherwise the room seems spartanly clean.\n");

    add_item("bed", "It is as spartan as any bed you can imagine.\n");
    add_item("desk", "This seems to be the dwarven alchemist's desk.\n");
    add_neg("'lie' [down] [in] [the] 'bed'",
	    "You wouldn't do that.\n");
    add_neg("'sleep' / 'rest' [in] [the] [bed]",
	    "Nah, it wouldn't be safe, and the Dwarven Alchemist would " +
	    "probably not like that.\n");

    door = clone_object(MORIA_OBJ + "closet_door");
    door->init_south();
    door->move(TO);    
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (!living(ob))
	return;
    if (ob->id("_dwarven_alchemist_"))
	return;
   
    if (!alchemist)
	alchemist = present("_dwarven_alchemist_", TO);

    if (!alchemist || !living(alchemist))
	return;

    alchemist->recieve_at_home(ob);
    return;
}

string
desc_alchemist()
{
    if (living(alchemist))
	return ", where he sits solemnly waiting for you";
    else
	return "";
}


