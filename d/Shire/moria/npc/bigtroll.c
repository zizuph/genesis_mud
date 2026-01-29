/*  -*- LPC -*-  */

/* 
 * This file has been changed to inherit the cavetroll. 
 * 
 * ---  NEVER COPY THINGS WHICH YOU CAN EASILY INERHIT! ---
 *
 * The results are that the size of this file became
 * very small. Check it out for yourself, and the 
 * gamedriver smiles happily at me.
 * Sir Rogon.
 *
 * Added UNIQUE_WEAPON code to limit number of JBS in the game
 *  to a total of 10.
 *  Jaypeg Apr 99
 *
 * Changed from Shire UNIQUE_WEAPON to AOB's CLONE_UNIQUE
 *  Jaypeg Apr 00
 */

inherit "/d/Shire/moria/npc/cavetroll";
inherit "/d/Shire/lib/kill_logger";
inherit "/lib/unique.c";

object ob;

#include "/d/Shire/common/defs.h"

create_troll_guard(int r)
{
    ::create_troll_guard(r);
    set_skill(SS_WEP_AXE, 100);
    make_gold(5);    
    set_kill_log_name("troll");
}

/* 
 * arm_me calls up cavetroll's arm_me(), but adds Dain's Axe.
 */
arm_me()
{
    ::arm_me();

    ob = clone_unique(MORIA_DIR + "wep/dainaxe", MAX_UNIQUE_ITEMS, MORIA_DIR + "wep/orcaxe");
    ob->move(TO);

    command("unwield scimitar");
    if (!command("wield axe in both hands"))
	command("wield axe");
}    

