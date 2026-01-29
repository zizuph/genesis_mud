/*
 * Shaman goblin
 * Boreaulam, Jan 2014
 */
#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>

#include "defs.h"

int align;
string get_color();
void set_align(int arg_align);

/*
 * Function name:        create_monster
 * Description  :        constructor for the object
 */
void
create_monster()
{
    set_adj("cunning");
    set_short("cunning goblin shaman");
    set_race_name("goblin");
	set_name("shaman");
	add_name("_l2_shaman");
	align = 0;

	set_long("@@get_long_desc");

	set_base_stat(SS_STR, 150 + random(10));
	set_base_stat(SS_DEX, 120 + random(10));
	set_base_stat(SS_CON, 150 + random(10));
	set_base_stat(SS_INT, 90 + random(10));
	set_base_stat(SS_WIS, 120 + random(10));
	set_base_stat(SS_DIS, 90 + random(10));

    set_skill(SS_WEP_POLEARM, 85 + random(10));
    set_skill(SS_PARRY, 65 + random(10));
    set_skill(SS_DEFENCE, 65 + random(10));
    set_skill(SS_UNARM_COMBAT, 90 + random(10));
    set_skill(SS_BLIND_COMBAT, 60 + random(10));
    set_skill(SS_AWARENESS, 90 + random(10));
    set_skill(SS_SPELLCRAFT, 100);

    add_chat("Goblins will rule the world!");
    add_chat("My magic is strong! It will help us dominate all of the " +
        "lesser races!");

    add_act("emote thinks hard about using his magic.");
    add_act("emote sniffs loudly.");

    add_cact("say You cannot kill me!");
    add_cact("emote watches you intently, learning your habits in battle.");
    set_chat_time(40);
    set_act_time(40);
    set_cchat_time(20);
    set_cact_time(20);
    set_default_answer(QCTNAME(TP)+" says: I'm not sure "+
        "what you are asking.\n");

    add_prop(OBJ_I_RES_MAGIC, 20);
	
} /* create_monster */

/*
 * Function name:        get_long_desc
 * Description  :        long description depends on alignment
 */
string
get_long_desc()
{
    return "This goblin is skillful with magic and might be " +
             "dangerous opponent. The shaman is surrounded by " + get_color() + " aura." +
             "\n";
 } /* get_long_desc */

/*
 * Function name:        get_color
 * Description  :        returns color of aura depends alignment
 */
string 
get_color()
{
	string color = "undefined";
	switch(align)
	{
		case -1: 
			color = "black";
			break;
		case 0: 
			color = "grey";
			break;
		default: 
			color = "white";
	}
	return color;
 } /* get_color */

/*
 * Function name:        arm_me
 * Description  :        equip goblin
 */
void
arm_me(int arg)
{
    clone_object(EQUIP_DIR + "l2_shaman_helm")->move(TO);
    clone_object(EQUIP_DIR + "l2_shaman_shirt")->move(TO);
    clone_object(EQUIP_DIR + "l2_shaman_bracers")->move(TO);
    clone_object(EQUIP_DIR + "l2_shaman_greaves")->move(TO);
    clone_object(EQUIP_DIR + "l2_shaman_staff")->move(TO);
    clone_object(OBJS_DIR + "l2_shaman_evade")->move(TO);

	align = arg;
	
    command("wield all");
    command("wear all");
} /* arm_me */


/*
 * Function name:        special_attack
 * Description  :        fireball special
 */
int
special_attack(object enemy)
{
    mixed *hitresult;
    string result;

	if(random(3))
	{
		return 0;
	}
	int penet = 550 + random(300);
	penet -= penet * enemy->query_magic_res(MAGIC_I_RES_FIRE) / 100;
	hitresult = enemy->hit_me(penet, MAGIC_DT, TO, -1);
    switch (hitresult[0])
    {
        case 0:
            result = "misses";
            break;
        case 1..10:
            result = "it barely singes you";
            break;
        case 11..20:
            result = "it hits you squarely, burning painfully";
            break;
        default:
            result = "it burns you severely";
            break;
    }

    enemy->catch_tell(query_The_name(enemy) + " throws a small fireball at you and " +
                      result + ".\n");
    tell_watcher(QCTNAME(TO) + " throws small fireball at " +
                 QTNAME(enemy) + ".\n", enemy);

    if (enemy->query_hp() <= 0)
    {
		enemy->do_die(this_object());
    }

    return 1;
} /* special_attack */

/*
 * Function name:        set_align
 * Description  :        setter for alignment
 */
void 
set_align(int arg_align)
{
	align = arg_align;
	set_alignment(align * 300);
 } /* set_align */

/*
 * Function name:        hit_me
 * Description  :        deflecting blows of players of the same alignment
 */
varargs public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc = -1)
{
	if(((attacker->query_alignment() > 400) && (align > 0))
	 || ((attacker->query_alignment() <= 400) 
      && (attacker->query_alignment() >= -400) && (align == 0))
	 || ((attacker->query_alignment() < -400) && (align < 0)))
	{
		attacker->catch_tell(TO->query_The_name(attacker) + "'s aura shines " 
		+ get_color() + ", absolutely deflecting your blow.\n");
		return ::hit_me(-1, dt, attacker, attack_id, target_hitloc);
	} else {
		attacker->catch_tell("Your blow passes through " 
		+ TO->query_the_name(attacker) + "'s aura.\n");
		return ::hit_me(wcpen, dt, attacker, attack_id, target_hitloc);
	}
 } /* hit_me */
