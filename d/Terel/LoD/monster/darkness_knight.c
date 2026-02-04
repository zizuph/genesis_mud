/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * darkness_knight.c
 *
 * a knight of the legion 920916 redhawk
 * Modified by Sorgum 941029
 * 
 *  Modified by Shanoga 2019.04.30
 *      - Removed set_random_move so they stop moving
 *          (were stacking in HUGE groups and killing players too often)
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "monster/legion_knight";

#include <ss_types.h>
#include <money.h>

/*
 * Function name: query_object_list
 * Description:   return list of equipment to wear
 */
public string*
query_object_list()
{
    return ({LOD_DIR + "armour/dark_chainmail",
             LOD_DIR + "armour/dark_helmet",
	     LOD_DIR + "armour/dark_shield",
	     LOD_DIR + "weapon/dark_sword"});
}

/*
 * Function name: query_chats
 * Description:   return list of chats for this monster.
 */
public string *
query_chats()
{
    string *chats =
	({
"I kill you on sight next time I see you.",
"The legion of darkness will rule the world.",
"Evil will rule in the world.",
"You are lucky. I will kill you quickly and painlessly."
});
    return chats;
}

/*
 * Function name: query_spell_level
 * Description:   spell level is used in spell_attack()
 * Returns:       this knights spell level.
 */
public int
query_spell_level()
{
    return 2;
}

/*
 * Function name: create_terel_monster
 * Description:   Create the monster. (standard)
 */
public void
create_terel_monster()
{
    set_name ("knight");
    add_name("darkness_knight");
    set_pshort("dark knights");
    set_short("dark knight");
    set_long("A human knight that is a member of the powerful and evil " +
	     "legion of darkness, the legion which is known to take no " +
	     "prisoners.\n");
    set_adj("evil");
    set_race_name("human");
    set_gender(MALE);
    set_alignment(-300);
    //set_random_move(30);

    set_stats(({85, 80, 75, 90, 90, 90}));
    SET_MAX_HP;
    
    set_skill(SS_DEFENCE,      55 + random(11));
    set_skill(SS_UNARM_COMBAT, 30 + random(11));
    set_skill(SS_PARRY,        55 + random(11));
    set_skill(SS_WEP_SWORD,    85 + random(5));
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_AWARENESS,    60);
    AGGRESSIVE;

}

/*
 * Function name: equip_me
 * Description:   Give me some equipment.
 */
public void
equip_me()
{
    ::equip_me();
    FIX_EUID;
    MONEY_MAKE_GC(random(5))->move(TO);
}
