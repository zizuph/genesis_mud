inherit "/d/Genesis/ship/deck";

#include <stdproperties.h>

#define SHIP "/d/Terel/mecien/valley/lake/"
#define BSN(xx)  break_string(xx+"\n", 70)

object pirate;

int
not_open()
{
    write("The hatch is closed and locked for the duration of the trip.\n");
    return 1;
}

void
reset_deck()
{
    int i, flagit;
    object room, *obs;

    if (!pirate)
    {
        pirate = clone_object("/d/Terel/dabaay/npc/dabaayhab");
        pirate->move(this_object());
        return;
    }
    flagit = 0;
    room = find_object("/d/Terel/ships/hold");

    if (present(pirate, room))
    {
        obs = all_inventory(room);
        for (i=0; i<sizeof(obs); i++)
        {
            if (living(obs[i]) && !(obs[i]->query_npc())) 
              flagit = 1;
        }
        if (!flagit)
        {
          pirate->move(this_object());
          pirate->add_prop(OBJ_I_HIDE, 100);
        }

    }
}   

void
create_deck()
{
    set_short("On Deck");
    set_long(BSN(
        "This is the deck of a small white ship, it is elegant, fashioned "
        +"of some rare silver and white wood. The masts rise high up into "
        +"sky, there they hold nobily aloft their sails." 

    ));
    add_item("masts", "They are tall and proud, silver-white.\n");
    add_item("sails", "Billowing in the wind, they shimmer in their silver hue.\n");
    add_exit(SHIP + "m_cab", "aft", 0);
    reset_room();
}
