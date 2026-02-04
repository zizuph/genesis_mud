/* This comment tells emacs to use c++-mode  -*- C++ -*- */

#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;

#define ARM_DIR  ORC_CAVE_DIR + "armour/"
#define WEP_DIR  ORC_CAVE_DIR + "weapon/"
#define summoned "_i_called_hounds"
#define WOLF ORC_CAVE_DIR + "monster/wolf"

#include <ss_types.h>
#include <money.h>
int hounds;
/*
 * Function name: query_object_list
 * Description:   return list of equipment
 */
public string*
query_object_list()
{
    return ({
	WEP_DIR + "sword",
        ARM_DIR + "crown"	    
		});
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    set_name(({"orcchief","chief"}));
    set_adj(({"mean","old"}));
    set_race_name("orc");
    set_short("mean old orcchief");
    set_long("He is at least 100 years old.\n");
    set_stats(({125, 125, 125, 125, 125, 125}));
    
    set_skill(SS_WEP_SWORD, 95);
    set_skill(SS_PARRY, 85);
    set_skill(SS_DEFENCE, 85);
    set_alignment(-170 + -1 * random(200));
    SET_MAX_HP;
    add_prop(OBJ_I_WEIGHT, 150000);
    add_prop(OBJ_I_VOLUME, 150000);
    add_prop(CONT_I_MAX_WEIGHT, 250000);
    add_prop(CONT_I_MAX_VOLUME, 230000);
    add_prop(LIVE_I_SEE_DARK,2);
    set_all_hitloc_unarmed(query_average_stat() / 2);
    hounds = 0;
}




/*
 * Function name: equip_me
 * Description:   Give me some equipment.
 */
public void
equip_me()
{
    object money;
    
    ::equip_me();
    FIX_EUID;
    money = MONEY_MAKE_CC(400 + random(300));
    money->move(TO);
}

/*
 * Function name: equip_actions
 * Description:   Initial commands (e.g. wield sword)
 */
public void
equip_actions()
{
    TO->command("wield sword");
    TO->command("wear all");
}

public void
do_die(object killer)
{
     object ghost;
     object sword;

     if (query_hp() > 0)
	 return;
     
     if (interactive(killer)) {
	 tell_room(ETO, "An icy chill rushes through the room after " +
		   QTNAME(killer) + " delivers the death blow to the " +
		   "orcchief.\n", killer);
	 killer->catch_msg("An icy chill rushes through the room after " +
		   "you deliver the death blow to the " +
		   "orcchief.\n");

	 FIX_EUID;
	 ghost = clone_object(ORC_CAVE_DIR + "monster/chief_ghost");
	 if ((sword = present("sword", TO))) {
	     sword->move(ghost);
	     ghost->command("get all from corpse");
	     ghost->command("wield sword");
	 }
	 ghost->set_killer(killer);
	 ghost->move(ETO);
	 ghost->arise();
	 ghost->attack();
     }
     ::do_die(killer);
}
     
int
special_attack(object enemy)
{
    
    if(random(10) < 4) 
    {
        if(hounds == 1)
            return 1;
        TO->command("whistle loudly");
        FIX_EUID;
        clone_object(WOLF)->move_living("north", ETO, 0, 0);
        clone_object(WOLF)->move_living("north", ETO, 0, 0);
        hounds = 1;

	      return 1;
    }

    return 0;
}



