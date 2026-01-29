/*
 * /doc/examples/mobiles/equipped_npc.c
 * 
 * This simple monster demonstrates how to add equipment to your
 * npcs.  In this case, we add a weapon and a piece of armour.
 */

inherit "/std/monster";

#define WEP "/doc/examples/weapons/knife"
#define ARM "/doc/examples/armours/helmet"

void
create_monster()
{
    set_name("ugluk");
    set_race_name("troll"); 
    set_adj("nasty");
    set_long("It is a very ugly and nasty lookin' troll.\n");

    set_stats(({ 20, 5, 20, 3, 3, 3 }));

    /* The helper function equip will clone and wear/wield the items */
    equip(({ WEP, ARM })); 
}

