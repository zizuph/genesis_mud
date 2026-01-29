/* Lady's Slipper by Teth, Feb.18,96 */
#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

void
create_herb()
{
    set_name("flower");
    set_adj(({"enchanting", "shoe-shaped"}));
    set_herb_name("lady's slipper");
    set_short("enchanting shoe-shaped flower");
    set_pshort("enchanting shoe-shaped flowers");
    set_pname(({"flowers", "herbs", }));
    set_ingest_verb("eat");
    set_unid_long(BSN("This is an enchanting shoe-shaped flower. It was " +
        "probably picked from a wide-leaved herb in a forest."));
    set_id_long(BSN("This is a flower of lady's slipper, an orchid found " +
        "in temperate forests. Lady's slipper (Cypripedium spp.) is an " + 
        "herb that grows to about 60 cm high. The flower is highly " +
        "specialized, forming a shoe that traps bees temporarily, forcing " +
        "the bee to transport the pollen. This particular flower is a " +
        "brilliant pink on white. Eating any part of most orchids is " +
        "said to cause mental pain or anguish."));
    set_effect(HERB_POISONING,"mana",20);
    set_herb_value(60);
    set_id_diff(23);
    set_find_diff(7);
    set_decay_time(2500);
}

init()
{
    ::init();
    ADA("smell");
}

int smell(string str)
{
    if ((str=="flower")||(str=="orchid"))
    {
        write("You inhale the cloying scent of the orchid, and it " +
        "tantalizes you. If only you were a honeybee!\n");
        say(QCTNAME(TP)+ " inhales deeply from a flower, and " +
        "then seems to be very satisfied and jealous of honeybees.\n");
    return 1;
    }
    NF("Smell what?\n");
    return 0;
}
string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
