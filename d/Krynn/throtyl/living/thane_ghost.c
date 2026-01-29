/*
 * A mad ghost of a hill dwarf thane.
 * Incorporates specials used by the Doomseeker branch
 * of the Neidar.
 *                                  
 * Arman, July 2020                                           
 */
  
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/guild/neidar/guild.h"

inherit M_FILE
inherit "/lib/unique";

#define DOOMSHADOW "/d/Ansalon/guild/neidar/shadows/occ_shadow"
#define MACE       "/d/Krynn/throtyl/weapon/thane_mace"
#define DEF_MACE   "/d/Krynn/common/warfare/weapons/std_warfare_hammer"
#define STICK      "/d/Krynn/throtyl/obj/petrified_stick"

void get_me_soul();

int soul_id;

void
clone_guild_items()
{
    object doom_regen = clone_object(DOOM_REGEN_OBJ);
    doom_regen->move(TO, 1);
    doom_regen->start();

    TO->add_cmdsoul(DOOMSEEKER_SOUL);
}

void
create_krynn_monster()
{
    set_name("ghost"); 
    set_name("thane");    
    set_race_name("dwarf");
    set_adj("dwarven");
    add_adj("mad");
    set_short("mad ghost of a dwarven thane");
    set_long("This is the ghost of a dwarven thane, one of the " +
        "kings of the hill dwarves from times just after the " +
        "Cataclysm. Driven mad enough by some great tragedy " +
        "to take the Doomseeker Oath, it seems not even death " +
        "has allowed him final release.\n");

    add_prop(CONT_I_HEIGHT, 110);
    add_prop(CONT_I_WEIGHT, 900);
    add_prop(CONT_I_VOLUME, 200);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_UNDEAD, 100);
    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(LIVE_I_NO_DRAGONFEAR, 1);

    // immunities and vulnerabilities to certain magic types
    add_prop(OBJ_I_RES_COLD, 65);
    add_prop(OBJ_I_RES_POISON, 65);
    add_prop(OBJ_I_RES_DEATH, 25);
    add_prop(OBJ_I_RES_ILLUSION, 25);
    add_prop(OBJ_I_RES_LIFE, -95);

    set_stats(({300,200,300,250,250,300}));
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 60);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_AWARENESS, 60);
    set_skill(BATTLERAGING_SKILL, 100);
    set_skill(SS_GUILD_SPECIAL_SKILL, 100);

    set_alignment(0);
    set_knight_prestige(0);
    set_all_hitloc_unarmed(35);

    set_exp_factor(225);  // Ignores most physical attacks, high magic resists. 
                          // Powerful offensive, regen, and defensive specials.

    soul_id = set_alarm(0.5, 0.0, &get_me_soul());
}

void
get_me_soul()
{
    add_cmdsoul(DOOMSEEKER_SOUL);
    update_hooks();
    remove_alarm(soul_id);

    object doom_regen = clone_object(DOOM_REGEN_OBJ);
    doom_regen->move(TO, 1);
    doom_regen->start();
}

void
arm_me()
{
    object wep, stick;

    seteuid(getuid(TO));
    wep = clone_unique(MACE, 8, DEF_MACE);
    stick = clone_object(STICK);

    if(wep->query_krynn_warfare_weapon())
    {
        wep->set_weapon_level(5, W_BOTH, "neidar");
        wep->update_warfare_weapon();
    } 

    MONEY_MAKE_HERE_GC(random(80));
    MONEY_MAKE_HERE_PC(random(10));

    wep->move(TO, 1);
    command("wield all");
    stick->move(TO, 1);
}


/*
 * Function name:   query_not_attack_me
 * Description:     The intended victim may force a fail when attacked.
 *                  If fail, the cause must produce explanatory text himself.
 * Arguments:       who: The attacker
 *                  aid: The attack id
 * Returns:         True if the attacker fails hitting us, false otherwise.
 */
public int
query_not_attack_me(object who, int aid)
{
    object attack_ob;
    mixed attack;
    string attack_desc;
    
    attack_ob = who->query_combat_object();
    attack = attack_ob->query_attack(aid);

    // ATTACK WAS MAGICAL.   
    if (attack == 0)
        return  ::query_not_attack_me(who, aid);

    attack_desc = attack_ob->cb_attack_desc(aid);

    // 33% of all physical attacks will pass through.
    if (!random(3))
        return  ::query_not_attack_me(who, aid);

    object *weapon;
    string weapon_string;

    weapon = who->query_weapon(-1);

    if ((!sizeof(weapon)))
    {
        weapon_string = "hand";
    }
    else
    {
        weapon_string = weapon[0]->short();
    }
	
    who->catch_msg("Your " +weapon_string+ " passes right through the "+
        "ghost, causing no damage at all!\n");
    TO->tell_watcher(QCTPNAME(who) + " " +weapon_string+ " passes right "+
        "through the ghost, causing no damage at all!\n", who);
    return 1;
}

/*
 * Function name: special_attack
 * Description:   Called from the external combat object's heart_beat
 *                routine. By redefining this, monsters can easily attack
 *                with spells or take special actions when engaged
 *                in combat.
 * Arguments:     victim (the one we are fighting right now)
 * Returns:       0 - if we want the round to continue
 *                1 - if we are done with this round
 * Note:          By always returning 1 the mobile is unable
 *                to do an ordinary attack.
 */
int
special_attack(object enemy)
{
    command("battlerage");

    mixed weapons = query_weapon(-1);

    if(!sizeof(weapons)) /* no weapon wielded */
        return 0;

    int weapon_type = weapons[0]->query_dt();

    switch(weapon_type)
    {
        case W_BLUDGEON:
            command("crush");
            break;
        default:
            command("chop");
            break;
    }

    return 1;
}

public void
do_die(object killer)
{
    tell_room(E(TO), "With a wail the mad ghost of a dwarven thane is " +
        "banished, leaving behind little more than his weapon, some " +
        "burial coins and a petrified stick from an ancient oak.\n");

    ::do_die(killer);
}

