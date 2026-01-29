/* 
 *	/d/Gondor/morgul/npc/ithil_olog.c
 *
 *	Olorin, August 1994
 *	General revision: Olorin, February 1996
 */
#pragma strict_types

inherit "/d/Gondor/morgul/npc/ithil_soldier.c";

#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../defs.h"

#define WEP_ARRAY1 ({MORGUL_DIR + "obj/mattock", \
                     MORGUL_DIR + "obj/halberd", \
                     MORGUL_DIR + "obj/mornstar"})
#define WEP_ARRAY2 ({ })
#define ARM_ARRAY2 ({MORGUL_DIR + "obj/chainmail"})

public void
create_ithil_olog()
{
}

nomask void
create_ithil_soldier()
{
    int     rnd = random(40);

    set_short("large troll");
    set_pshort("large trolls");
    set_name("troll");
    set_pname("trolls");
    set_adj("large");
    set_race_name("troll");
    set_name("troll");
    add_name("olog");
    remove_name("orc");
    set_long(BSN(CAP(LANG_ADDART(implode(query_adjs()," "))) + 
	" troll, one of the olog-hai, the troll-race bred by the Dark " +
	"Lord in the mountains of Mordor. They are larger, fiercer, " +
	"and more cunning than other trolls, but like them hard as " +
	"stone."));

    set_base_stat(SS_STR, 200 + rnd);
    set_base_stat(SS_DEX, 150 + rnd / 2);
    set_base_stat(SS_CON, 250 + rnd * 2);
    set_base_stat(SS_INT,  55 + rnd / 2);
    set_base_stat(SS_WIS,  25 + rnd);
    set_base_stat(SS_DIS,  65 + rnd / 2);

    set_alignment(-250-rnd*10);
    set_skill(SS_WEP_SWORD,   75 + rnd);
    set_skill(SS_WEP_POLEARM, 75 + rnd);
    set_skill(SS_WEP_CLUB,    75 + rnd);
    set_skill(SS_WEP_AXE,     75 + rnd);
    set_skill(SS_WEP_KNIFE,   75 + rnd);
    set_skill(SS_PARRY,       75 + rnd);
    set_skill(SS_DEFENCE,     75 + rnd);
    add_prop(CONT_I_HEIGHT,  220 + rnd);
    add_prop(CONT_I_WEIGHT, 200000 + rnd * 2000);
    add_prop(CONT_I_VOLUME, 200000 + rnd * 2000);    
    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_restrain_path(CAMP_ROOM_DIR);

    create_ithil_olog();

    reset_monster();
}

static void
set_arm_arrays()
{
    ::set_arm_arrays();
    Wep1 = WEP_ARRAY1;
    Wep2 = WEP_ARRAY2;
    Arm2 = ARM_ARRAY2;

    set_all_hitloc_unarmed(30);
}

/*
 * Function name: init_attack
 * Description:   Called from init_living() i monster.c
 */
public void
init_attack()
{
    object  room, 
    *arr;
    int     i;

    if ((!monster_aggressive) || (TP->query_npc()))
    {
	::init_attack();
	return;
    }

    if ((monster_attack_chance == 0) || (random(100) < monster_attack_chance))
    {
	set_alarm(1.0, 0.0, &do_attack(TP));

	room = ENV(TO);
	arr = filter(all_inventory(room), &->id("_morgul_monster"));
	for (i = 0; i < sizeof(arr); i++)
	{
	    if(arr[i] != TO)
		arr[i]->order_attack_enemy(TO, TP);
	}
    }
    else
	::init_attack();
}

void
reset_monster()
{

    ::reset_monster();

    if ((ENV(TO) != TO->query_monster_home()) && 
      (TO->query_monster_home() != 0))
    {
	TO->move_living("to the camp",TO->query_monster_home());
    }
}
