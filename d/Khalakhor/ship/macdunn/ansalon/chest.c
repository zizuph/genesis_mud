/* File:          /d/Khalakhor/ship/macdunn/ansalon/chest.c
 * Creator:       Teth
 * Date:          April 16, 1997
 * Modifications: Teth - Feb 10 2002 - Added a gem to the chest.
 * Purpose:       This is the chest belonging to the dwarf captain
 *                on the ship. There is no key, so it is only 
 *                pickable via skill.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/ansalon/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:      A little something for thieves.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/receptacle";
#include <stdproperties.h>
#include "/d/Genesis/gems/gem.h"

object coins1, coins2, coins3, gem1;

public void
reset_receptacle()
{
    seteuid(getuid());

    if (!coins1 || !present(coins1))
    {
        coins1 = clone_object("/std/coins");
        coins1->set_coin_type("gold");
        coins1->set_heap_size(5 + (random(16)));
        coins1->move(this_object(), 1);
    }

    if (!coins2 || !present(coins2))
    {
        coins2 = clone_object("/std/coins");
        coins2->set_coin_type("silver");
        coins2->set_heap_size(25 + (random(76)));
        coins2->move(this_object(), 1);
    }

    if (!coins3 || !present(coins3))
    {
        coins3 = clone_object("/std/coins");
        coins3->set_coin_type("copper");
        coins3->set_heap_size(100 + (random(201)));
        coins3->move(this_object(), 1);
    }

    if (!gem1 || !present(gem1))
    {
        gem1 = RANDOM_GEM_BY_RARITY(GEM_RARE);
        gem1->move(this_object(), 1);
    }
    
    this_object()->add_prop(CONT_I_CLOSED, 1);
    this_object()->add_prop(CONT_I_LOCK, 1);
}

public void
create_receptacle()
{
    set_name("chest");
    add_name("receptacle");
    set_adj("compact");
    add_adj("steel");
    set_short("compact chest");
    set_pshort("compact chests");
    set_long("This compact chest is bolted to the floor. It is made " +
      "of steel, and apparently impossible to break open. A small " +
      "keyhole on the frame is immediately below the edge of the " +
      "lid.\n");
    add_item(({"bolts","floor bolts"}),"The bolts of the chest are " +
      "secured deeply into the wood of the floor, making it " +
      "impossible to get the chest.\n");
    add_item(({"hole","keyhole"}),"This appears to be the only way to " +
      "open the chest.\n");
    add_item("lock","The lock on the chest is a somewhat complicated " +
      "slip and tumble mechanishm.\n");
    add_item(({"slip mechanism","tumble mechanism","mechanism","slip " +
        "and tumble"}),"The mechanism might be pickable, if you " +
      "attempt to pick the lock on the chest.\n");
    add_item("frame","The frame of the chest is made of reinforced " +
      "steel.\n");
    add_item(({"steel","reinforced steel"}),"The steel does not look like it " +
      "will yield to mortal powers.\n");
    add_item("lid","The lid meets firmly against the top edge of the " +
      "frame, overlapping it on the sides.\n");
    add_item("sides","The sides of the chest are solid.\n");
    add_cmd_item("lid","pry","Although a good idea, prying the lid " +
      "of the chest does not get you anywhere, as it is unyielding.\n");
    add_cmd_item(({"chest","compact chest","steel chest"}),({"break","destroy",
        "smash"}),"You attempt to open the chest through brute strength, but it " +
      "does not open and give you any reward.\n");

    set_key("Dwarf_Chest_Key");
    set_pick(50);

    add_prop(CONT_I_WEIGHT, 3220);
    add_prop(CONT_I_MAX_WEIGHT, 12350);
    add_prop(CONT_I_VOLUME, 3100);
    add_prop(CONT_I_MAX_VOLUME, 12100);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_SELL, "If you managed to get this chest, please " +
      "report it as a bug.\n");
    add_prop(OBJ_M_NO_GET, "The chest is bolted to the floor, one bolt in each " +
      "corner. Straining as hard as you can, you find yourself unable " +
      "to get the chest.\n");
    add_prop(OBJ_I_VALUE, 240);

    enable_reset(30);
    reset_receptacle();
}
