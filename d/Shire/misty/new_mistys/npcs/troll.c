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

#include "/d/Shire/sys/defs.h"
#include "defs.h"

#define ADJDESC ({ "ugly", "shaggy", "hideous", "muscular", "grey",\
      "terrible", "unkempt", "dangerous"})

#define LONGDESC ({\
    "looks fierce and very powerful. It eyes you up, looking for a weakness in your armours.\n",\
    "looks ugly and unintelligent. Its eyes are terrible and fierce looking.\n",\
    "appears powerful, with large arms that could probably squeeze you to death.\n",\
    "growls dangerously at you, and prepares to battle you to the death!\n",\
    "has sharp claws that could slash you into ribbons.\n",\
    "has dark, thick skin covered with scales.\n",\
    "towers over you, growling with entrails hanging from its teeth.\n",\
    "snarls at you, challenging you to a fight to the death.\n" })


create_troll_guard(int r)
{
    ::create_troll_guard(r);
    set_adj(ADJDESC[r]);
    set_name(({"troll","mountain","mountain troll"}));
    add_name("_misty_troll");
    set_pname("guards");
    set_short(ADJDESC[r] + " mountain troll");
    set_pshort("mountain trolls");
    set_race_name("troll");
    set_long("This troll is one of the many creatures that inhabits the " +
        "mountains. It is tall and strong, and able to destroy almost " +
        "anything it meets. It looks like other trolls but has a shaggy " +
        "fur that protects it from the elements. The troll " + LONGDESC[r] );

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

//    ob = clone_unique(MORIA_DIR + "wep/dainaxe", MAX_UNIQUE_ITEMS, MORIA_DIR + "wep/orcaxe");
//    ob->move(TO);

    command("unwield scimitar");
    if (!command("wield axe in both hands"))
	command("wield axe");
}    

