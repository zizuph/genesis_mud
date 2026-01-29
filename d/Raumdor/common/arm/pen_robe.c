/* September 4th 2013, After Discussion with AoB (Petros), I (Navarre) changed the resitance of this robe
 * to be 30-non-additive instead of 35 additive.
 * The npc is easy and was made repeatable (it was quest limited before).
 */
inherit "/std/armour";
#include "/d/Raumdor/defs.h"

void
create_armour()
{
    ::create_armour();
    set_name("black_death_robe");
	add_name("robe");
    set_adj("black");
    add_adj("death");
    set_short("black death robe");
    set_long("This robe is made of pure black material. It reflects "+
    "no light, and seems to absorb the light around it. It radiates "+
    "a cold, cruel feeling. You notice that it carries an almost "
    +"invisible mark resembling a decayed grinning skull resting "
    +"on a scythe.\n");
    set_at(A_ROBE);
    set_af(TO);
    set_ac(20);
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,500);
    add_prop(OBJ_M_NO_BUY,1);
    add_prop(MAGIC_AM_MAGIC,({50,"enchantment"}));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_ID_INFO,({"This robe once belonged to "+
    "the most vilest of the nesferatus, Shabakk. Thus, from "+
    "being worn so long, it has adopted the power to protect one "+
    "from death magic.\n",35}));
    add_prop(OBJ_S_WIZINFO,"This robe gives a player protection from "+
    "the magic in the element of Death: 30, non-additive.\n");
}

int
wear(object ob)
{
    E(ob)->catch_msg("A strange black aura surrounds you.\n");
    E(ob)->add_magic_effect(TO);
    return 0;
}

int
remove(object ob)
{
    set_this_player(query_worn());
    TP->catch_msg("The strange black aura disappears.\n");
    TP->remove_magic_effect(TO);
    return 0;
}

mixed*
query_magic_protection(string prop, object what)
{
    if (what == query_worn() && prop == MAGIC_I_RES_DEATH)
    {
        return ({30,0});
    }
    return ::query_magic_protection(prop,what);
}
