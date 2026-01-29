/* A dwarf-slaying and human-slaying mace
 *
 * Based on /d/Gondor/morgul/obj/wraith_mace.c by Olorin
 * 
 * Arman, 25 July 2020
 *
 * Damage modifier reduced from x1.5 - x2.0 to
 *                              x1.3 - x1.6
 * Arman, 3 Feb 2022.
 *
 */
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <options.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>
#include <wa_types.h>
#include "/d/Krynn/common/defs.h"

void
create_weapon()
{
   set_name("warhammer");
   set_adj(({"long", "adamantine"}));
   set_short("long adamantine warhammer");
   set_pshort("long adamantine warhammers");
   set_long("This is a long two-handed war mace of dwarven " +
       "craftsmanship. Made from the rare blue metal known as " +
       "star-metal or adamantine, it looks to be a powerful " +
       "weapon. Runes have been carved along the length of the " +
       "haft.\n");

   set_default_weapon(50, 50, W_CLUB, W_BLUDGEON, W_BOTH, 0);

   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(50, 50) + random(1000) - 500);
   add_prop(OBJ_I_WEIGHT,
	  (F_WEIGHT_DEFAULT_WEAPON(50, W_CLUB) + random(2000) + 500));
   add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(MAGIC_AM_MAGIC,({ 40, "enchantment" }));
   add_prop(OBJ_S_WIZINFO,
       "This mace is a powerful magical weapon wielded by a ghost dwarven thane "
       + "in the Throtyl region /d/Krynn/throtyl/living/thane_ghost.c "
       + "The mace is WC 50, but does between 1.5x and 2x damage on dwarves "
       + "and on humans.\n");

    add_prop(MAGIC_AM_ID_INFO,
      ({"The adamantine mace is magical.\n",10,
           "Enchanted by dwarven Runecarvers during the great dwarven " +
           "Kinslayer Wars following the Cataclysm, this powerful warhammer " +
           "does extra damage against dwarves and humans. The powerful " +
           "enchantments prevent the mace from dulling.\n",60}));

    add_cmd_item(({"runes","haft"}),"read","@@read_inscription");

    set_wf(TO);
}

varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    if (enemy->query_race_name() != "dwarf" && enemy->query_race_name() != "human")
        return 0;

    if (phurt < 0)
    {
        query_wielded()->catch_msg("You swing the " +short()+ 
            " with all your might through open air.\n");
        enemy->catch_msg("You deftly duck as " + QTNAME(query_wielded()) 
            + " swings " + query_wielded()->query_possessive() 
            + " " +short()+ " at you.\n");
        wielder->tell_watcher(QCTNAME(wielder)+" swings the " +short()+ " with all "
            + HIS(wielder) + " might through open air.\n", enemy);
    }
    else if (phurt == 0)
    {
        query_wielded()->catch_msg("Your " +short()+ " just barely misses "
            + QTNAME(enemy)+"!\n");
        enemy->catch_msg("The " +short()+ " of "+QTNAME(query_wielded())
            + " just barely misses your head!\n");
        wielder->tell_watcher(QCTNAME(wielder)+" just barely misses " 
            + QTNAME(enemy) + " with "+HIS(wielder)+" " +short()+ ".\n", enemy);
    }
    else
    {
        wielder->tell_watcher(QCTPNAME(wielder)+" " +short()+ " falls on "
            + QTNAME(enemy)+" with a bone breaking sound!\n", enemy);
        query_wielded()->catch_msg("The " +short()+ " falls down on the puny "        
            + enemy->query_race_name()+" with a mighty crush!\n");
        enemy->catch_msg("The " +short()+ " falls upon you with a mighty crush!\n");

//        enemy->heal_hp(-(random(dam/2) + dam/2));
        enemy->heal_hp(-(random(dam/3) + dam/3));
    }

    return 1;
}

/*
 * Function name: set_dull
 * Description:   Use this to increases the dull status on weapons. 
 * Arguments:     cond - The new condition we want (can only be raised)
 * Returns:       1 if new condition accepted
 *
 */
int
set_dull(int du)
{
    return 0;
}

string
read_inscription()
{
    if(TP->query_race_name() == "dwarf" || TP->query_skill(SS_LANGUAGE) > 40)
        return "Dwarven runes carved along the haft of the warhammer " +
            "translate to read 'Kinslayer, scourge of the Mountain " +
            "Dwarves and their Plainsman allies'.\n";

    return "You are unfamiliar with the dwarven language and are unable " +
        "to translate what the runes say.\n";

}