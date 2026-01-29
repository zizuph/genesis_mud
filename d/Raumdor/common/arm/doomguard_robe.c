/* 
 * This item is a mirror image of the black death robe.
 *
 * It is rewarded by sacrificing a black death robe on
 * the Khiraa altar
 *
 * Nerull 2020.
 
 */
inherit "/std/armour";
#include "/d/Raumdor/defs.h"

void
create_armour()
{
    ::create_armour();
    set_name("dim_purple_robe");
	add_name("robe");
    set_adj("purple");
    add_adj("dim");
    set_short("dim purple robe");
    set_long("This robe is made of some unknown purple fabric and "
	+"radiates a dim purple glow. You believe this object originates "
	+"from some otherwordly unholy ritual.\n");
    set_at(A_ROBE);
    set_af(TO);
    set_ac(20);
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,500);
    add_prop(OBJ_M_NO_BUY,1);
    add_prop(MAGIC_AM_MAGIC,({50,"enchantment"}));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
	
    add_prop(MAGIC_AM_ID_INFO,({"This robe is created from a source "
    +"in the netherworld. One may think it was a different robe, but "
    +"somehow altered by magical means. It will protect the wearer from "
    +"life magic.\n",35}));
	
    add_prop(OBJ_S_WIZINFO,"This robe gives a player protection from "+
    "the magic in the element of Life: 30, non-additive.\n");
}

int
wear(object ob)
{
    E(ob)->catch_msg("A strange purple aura surrounds you.\n");
    E(ob)->add_magic_effect(TO);
    return 0;
}

int
remove(object ob)
{
    set_this_player(query_worn());
    TP->catch_msg("The strange purple aura disappears.\n");
    TP->remove_magic_effect(TO);
    return 0;
}

mixed*
query_magic_protection(string prop, object what)
{
    if (what == query_worn() && prop == MAGIC_I_RES_LIFE)
    {
        return ({30,0});
    }
	
    return ::query_magic_protection(prop,what);
}
