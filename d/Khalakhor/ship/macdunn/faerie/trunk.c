/* File:          /d/Khalakhor/ship/macdunn/faerie/trunk.c
 * Creator:       Teth
 * Date:          November 16, 1997
 * Modifications:
 * Purpose:       This is the trunk belonging to the captain
 *                on the ship. There is no key, so it is only 
 *                pickable via skill.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/faerie/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:      A little something for thieves.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/receptacle";
#include <stdproperties.h>
#include "local.h";

object coins1, coins2, coins3, treasure1;

public void
reset_receptacle()
{
    seteuid(getuid());

    if (!coins1 || !present(coins1))
    {
        coins1 = clone_object("/std/coins");
        coins1->set_coin_type("platinum");
        coins1->set_heap_size(1 + (random(5)));
        coins1->move(this_object(), 1);
    }

    if (!coins2 || !present(coins2))
    {
        coins2 = clone_object("/std/coins");
        coins2->set_coin_type("silver");
        coins2->set_heap_size(12 + (random(10)));
        coins2->move(this_object(), 1);
    }

    if (!coins3 || !present(coins3))
    {
        coins3 = clone_object("/std/coins");
        coins3->set_coin_type("copper");
        coins3->set_heap_size(400 + (random(401)));
        coins3->move(this_object(), 1);
    }

    if(!treasure1 || !present(treasure1))
    {
        treasure1 = clone_object(THIS_DIR + "treasure");
        treasure1->move(this_object(), 1);
    }

    this_object()->add_prop(CONT_I_CLOSED, 1);
    this_object()->add_prop(CONT_I_LOCK, 1);
}

public void
create_receptacle()
{
    set_name("trunk");
    add_name("receptacle");
    set_adj("heavy");
    add_adj("metal");
    set_short("heavy trunk");
    set_pshort("heavy trunks");
    set_long("This heavy trunk is bolted to the floor. It is made " +
      "of metal, and apparently impossible to break open. A small " +
      "keyhole on the frame is immediately below the edge of the " +
      "lid.\n");
    add_item(({"bolts","floor bolts"}),"The bolts of the chest are " +
      "secured deeply into the wood of the floor, making it " +
      "impossible to get the trunk.\n");
    add_item(({"hole","keyhole"}),"This appears to be the only way to " +
      "open the trunk.\n");
    add_item("lock","The lock on the trunk is a very complicated " +
      "slip and tumble mechanishm.\n");
    add_item(({"slip mechanism","tumble mechanism","mechanism","slip " +
        "and tumble"}),"The mechanism might release, if you " +
        "attempt to pick the lock on the trunk.\n");
    add_item("frame","The frame of the trunk is made of reinforced " +
      "steel.\n");
    add_item(({"steel","reinforced steel"}),"The steel does not look " +
      "like it will yield to mortal powers.\n");
    add_item("lid","The lid meets firmly against the top edge of the " +
      "frame, overlapping it on the sides.\n");
    add_item("sides","The sides of the chest are solid.\n");
    add_cmd_item("lid","pry","Although a good idea, prying the lid " +
      "of the chest does not get you anywhere, as it is unyielding.\n");
    add_cmd_item(({"trunk","heavy trunk","metal trunk"}),({"break","destroy",
        "smash"}),"You attempt to open the trunk through brute strength, " +
        "but it does not open and give you any reward.\n");

    set_key("Treas_Chest_Key");
    set_pick(80);

    add_prop(CONT_I_WEIGHT, 13220);
    add_prop(CONT_I_MAX_WEIGHT, 22350);
    add_prop(CONT_I_VOLUME, 12100);
    add_prop(CONT_I_MAX_VOLUME, 22100);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_SELL, "If you managed to get this trunk, please " +
      "report it as a bug.\n");
    add_prop(OBJ_M_NO_GET, "The trunk is bolted to the floor, one bolt " +
      "in each corner. Straining as hard as you can, you find yourself " +
      "unable to get the chest.\n");
    add_prop(OBJ_I_VALUE, 2400);

    enable_reset(30);
    reset_receptacle();
}
