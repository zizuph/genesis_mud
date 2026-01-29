/*      Created by:     ???   
 *      Purpose:        
 *      Modified:       Toby, 971008 (fixed a typo and added 
 *				      SS_int and WIS instead of numbers)
 *
 *  This medallions drops of : /d/Raumdor/common/npc/penthalus.c
 */


inherit "/d/Raumdor/std/armour.c";
#include "/d/Raumdor/defs.h"

void
create_armour()
{
    ::create_armour();
    set_name("medallion");
    set_adj("blood-stone");
    set_short("blood-stone medallion");
    set_long("This is a strange medallion indeed. A single blood red "+
    "stone hangs from a silver chain. The stone feels incredibly light "+
    "and must be magical in some way.\n");

    set_at(A_NECK);
    set_ac(1);
    set_af(TO);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_MAGIC,({30,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This gives the power of great "+
    "intelligence and wisdom.\n",20}));
    add_prop(OBJ_S_WIZINFO,"This add 10 points of int to whoever wears "+
    "it. And adds 20 points of wis.\n");
    add_prop(OBJ_I_WEIGHT,300);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_VALUE,1000);
    add_prop(OBJ_M_NO_BUY,1);
}

int
wear(object ob)
{
    int stat,stat2;
    stat2 = E(ob)->query_stat_extra(SS_WIS);
    E(ob)->set_stat_extra(SS_WIS,stat2 + 20);
    stat = E(ob)->query_stat_extra(SS_INT);
    E(ob)->set_stat_extra(SS_INT,stat +10);
    write("The pendant feels hot, then cools down again. Odd.\n");
    return 0;
}

int
remove(object ob)
{
    int stat,stat2;
    set_this_player(query_worn());
    write("You feel a mental drain on you.\n");
    stat2 = TP->query_stat_extra(SS_WIS);
    TP->set_stat_extra(SS_WIS,stat2 - 20);
    stat = TP->query_stat_extra(SS_INT);
    TP->set_stat_extra(SS_INT,stat - 10);
    return 0;
}

