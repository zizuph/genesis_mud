/* towncastle/npc/guard.c is cloned by towncastle/battlement.c */
inherit "/std/monster";
 
#include "../default.h"
#include <ss_types.h>
#include "/d/Emerald/lib/prestige.h"
 
void
create_monster()
{
    set_name("guard");
    set_adj("big");
    add_adj("sturdy");
    set_race_name("human");
    set_short("sturdy guard");
    set_long("It is a rather large man. He looks like he "+
	     "is guarding this part of the castle in case it should be "+
             "attacked.\n");
 
    set_stats( ({ 50+random(100), 80 + random(50), 70 + random(50),
		  50+random(100), 50+random(100), 50+random(100) }) );
 
    set_skill(SS_WEP_SWORD, 75);
    set_skill(SS_PARRY, 55);
    set_skill(SS_DEFENCE, 35);
 
    set_all_hitloc_unarmed(query_stat(SS_CON) / 4);
 
    set_hp(query_max_hp());
 
    set_alignment(-random(150)-50);
 
    add_prop(CONT_I_WEIGHT, 89000);
    add_prop(CONT_I_MAX_WEIGHT, 180000);
    add_prop(CONT_I_VOLUME, 89000);
    add_prop(CONT_I_MAX_VOLUME, 100000);
    add_prop(LIVE_I_NEVERKNOWN, 1);
}
 
void
arm_me()
{
    if (random(5) < 3)
    clone_object(TOWNSHIP_DIR + "arm/plate")->move(this_object(),1);
    if (random(5) < 3)
    clone_object(TOWNSHIP_DIR + "arm/helmet")->move(this_object(),1);
    if (random(5) < 2)
    clone_object(TOWNSHIP_DIR + "arm/gauntlets")->move(this_object(),1);
    if (random(5) < 2)
    clone_object(TOWNSHIP_DIR + "arm/leggings")->move(this_object(),1);
    if (random(5) < 2)
    clone_object(TOWNSHIP_DIR + "arm/boots")->move(this_object(),1);
    clone_object(TOWNSHIP_DIR + "wep/sword")->move(this_object(),1);
    command("wear all");
    command("wield longsword");
}
