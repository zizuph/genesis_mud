inherit "/d/Shire/std/room";
#include "/d/Shire/common/defs.h"

object ob;

void
create_shire_room()
{
    set_short("Inside an Orc Hut");
    set_long("This orc hut is like every other orc dwelling "+
      "you've seen or heard of- messy.  Remains of meals lie "+
      "partly uneaten in bowls that rest on the dirt floor. "+
      "Droppings of some kind stink up the only square "+
      "corner in this hut.  An open flap leads out of the hut.\n");
    add_item(({"remains","remain","bowls","bowl"}),
      "The remains are of some kind of animal. Hopefully it "+
      "won't happen to you, though.\n");
    add_item(({"dirt floor","floor","dirt"}),
      "Strewn about on the dirt floor are filthy bowls.\n");
    add_item(({"droppings","dropping","corner","square corner"}),
      "The droppings in the corner are too large to be from an "+
      "animal.\n");
    add_exit(EVENDIM_DIR + "ev17", "out", 0);
    add_prop(ROOM_I_INSIDE, 1);
    reset_shire_room();
}

void
reset_shire_room()
{
    if(!ob)
    {
	ob = clone_object(EVENDIM_DIR + "npc/letter_orc");
	ob->move(this_object());
    }
}
