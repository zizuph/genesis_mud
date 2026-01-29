/*
 * Virtual Skill Provider
 *
 * There is a 7x7 combination of skills available for rangers.  Instead
 * of having 49 different trainers, this will create 49 objects that
 * will contain the skill maps.
 *
 * Author: Zizuph 2022-06-14
 *
*/

#include "./rangers.h"
#include "/d/Gondor/defs.h"
#include <macros.h>
#include <ss_types.h>

inherit "/std/room";

static mapping virtue_providers = ([]);

mapping allowed_skills = ([]);

public create_room()
{
    set_short("Virtue skill provider");
    set_long("This room dynamically calculates maximum skill levels " +
      "for the various virtue combinations.\n");
}

public object get_virtue_skills(int major_virtue, int minor_virtue)
{
    string key = "" + major_virtue + ":" + minor_virtue;
    object provider = virtue_providers[key];
    if (!provider)
    {
        provider = clone_object(MASTER);
        provider->configure_virtues(major_virtue, minor_virtue);
        virtue_providers[key] = provider;
    }
    return provider;
}

public mapping get_all_skills()
{
    return secure_var(allowed_skills);
}

public void inc_skill(int skill, int amount)
{
    int base = allowed_skills[skill];
    base += amount;
    base = min(100, base);
    allowed_skills[skill] = base;
}

public void set_skill(int skill, int amount)
{
    int base = allowed_skills[skill];
    base = max(base, amount);
    base = min(100, base);
    allowed_skills[skill] = base;
}

public void configure_virtues(int major_virtue, int minor_virtue)
{
    // First we start with the base
    set_skill(SS_WEP_SWORD, 50);
    set_skill(SS_WEP_MISSILE, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_DEFENCE, 50);

    set_skill(SS_SNEAK, 50);
    set_skill(SS_HIDE, 50);
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_FR_TRAP, 50);

    set_skill(SS_TRACKING, 60);
    set_skill(SS_LOC_SENSE, 60);
    set_skill(SS_HUNTING, 50);
    set_skill(SS_ANI_HANDL, 30);

    // Base values in AG
    set_skill(SS_ALCHEMY, 20);
    set_skill(SS_WEP_AXE, 30);
    set_skill(SS_WEP_POLEARM, 30);
    set_skill(SS_HERBALISM, 30);
    set_skill(SS_FORM_CONJURATION, 20);
    set_skill(SS_SPELLCRAFT, 20);
    set_skill(SS_ELEMENT_LIFE, 20);
    
    if (!major_virtue)
    {
        set_skill(SS_AMBUSH, 50);
        set_skill(SS_HEARING, 50);
        set_skill(SS_BRAWLING, 50);
    }
    else
    {
        set_skill(SS_AMBUSH, 100);
        set_skill(SS_HEARING, 100);
        set_skill(SS_BRAWLING, 100);
    }
    
    switch (major_virtue)
    {
        case RANGER_MAJOR_VIRTUE_ENEMY_OF_THE_EAST:
            inc_skill(SS_WEP_SWORD, 40);
            inc_skill(SS_PARRY, 30);
            inc_skill(SS_DEFENCE, 30);
            inc_skill(SS_SNEAK, 40);
            inc_skill(SS_HIDE, 40);
            inc_skill(SS_AWARENESS, 40);
            break;
        case RANGER_MAJOR_VIRTUE_HAND_OF_THE_KING:
            inc_skill(SS_ALCHEMY, 55);
            inc_skill(SS_HERBALISM, 20);
            inc_skill(SS_WEP_SWORD, 40);
            inc_skill(SS_PARRY, 25);
            inc_skill(SS_DEFENCE, 25);
            inc_skill(SS_SNEAK, 50);
            inc_skill(SS_HIDE, 50);
            break;
        case RANGER_MAJOR_VIRTUE_ENEMY_OF_THE_SHADOW:
            inc_skill(SS_WEP_SWORD, 40);
            inc_skill(SS_PARRY, 40);
            inc_skill(SS_DEFENCE, 25);
            inc_skill(SS_2H_COMBAT, 70);
            inc_skill(SS_SNEAK, 20);
            inc_skill(SS_HIDE, 20);
            inc_skill(SS_AWARENESS, 40);
          break;
        case RANGER_MAJOR_VIRTUE_SENTINEL_OF_IMLADRIS:
            inc_skill(SS_WEP_MISSILE, 50);
            inc_skill(SS_DEFENCE, 40);
            inc_skill(SS_SNEAK, 20);
            inc_skill(SS_HIDE, 20);
            inc_skill(SS_AWARENESS, 20);
            inc_skill(SS_HERBALISM, 20);
            inc_skill(SS_SPELLCRAFT, 30);
            inc_skill(SS_ELEMENT_LIFE, 20);
            inc_skill(SS_FORM_CONJURATION, 0);
            break;
        case RANGER_MAJOR_VIRTUE_DAUNTLESS_GUARDIAN:
            inc_skill(SS_WEP_SWORD, 50);
            inc_skill(SS_DEFENCE, 40);
            inc_skill(SS_PARRY, 40);
            inc_skill(SS_HIDE, 40);
            inc_skill(SS_SNEAK, 40);
            inc_skill(SS_AWARENESS, 40);
            break;
        case RANGER_MAJOR_VIRTUE_DEFENDER_OF_OSGILIATH:
            inc_skill(SS_WEP_POLEARM, 70);
            inc_skill(SS_DEFENCE, 40);
            inc_skill(SS_HIDE, 50);
            inc_skill(SS_SNEAK, 50);
            inc_skill(SS_AWARENESS, 50);
            inc_skill(SS_HERBALISM, 20);
            break;
        case RANGER_MAJOR_VIRTUE_OLD_HATRED:
            inc_skill(SS_WEP_AXE, 70);
            inc_skill(SS_DEFENCE, 35);
            inc_skill(SS_PARRY, 35);
            inc_skill(SS_2H_COMBAT, 70);
            inc_skill(SS_AWARENESS, 10);
            break;
    }
    
    switch (minor_virtue)
    {
        case RANGER_MINOR_VIRTUE_BLESSING_OF_THE_ELDAR:
            set_skill(SS_HERBALISM, 40);
            set_skill(SS_SPELLCRAFT, 50);
            set_skill(SS_ELEMENT_LIFE, 40);
            set_skill(SS_FORM_CONJURATION, 20);
            set_skill(SS_FORM_ABJURATION, 30);
            break;
        case RANGER_MINOR_VIRTUE_DEEP_SONGS:
            set_skill(SS_WEP_AXE, 90);
            set_skill(SS_PARRY, 75);
            break;
        case RANGER_MINOR_VIRTUE_WARDEN_OF_PELENNOR:
            set_skill(SS_WEP_POLEARM, 90);
            set_skill(SS_PARRY, 75);
            break;
        case RANGER_MINOR_VIRTUE_DEADLY_ARCHERS:
            set_skill(SS_WEP_MISSILE, 90);
            break;
        case RANGER_MINOR_VIRTUE_ART_OF_DISAPPEARING:
            set_skill(SS_SNEAK, 100);
            set_skill(SS_HIDE, 100);
            set_skill(SS_AWARENESS, 85);
            break;
        case RANGER_MINOR_VIRTUE_NOBLE_LINEAGE:
            set_skill(SS_WEP_SWORD, 85);
            set_skill(SS_PARRY, 80);
            break;
        case RANGER_MINOR_VIRTUE_FRIEND_OF_ROHAN:
            set_skill(SS_RIDING, 75);
            set_skill(SS_ANI_HANDL, 75);
            break;
        case RANGER_MINOR_VIRTUE_GIFTS_OF_ESTE:
            set_skill(SS_ALCHEMY, 60);
            set_skill(SS_HERBALISM, 70);
            break;
    }
}

public int get_train_max(int skill)
{
    return allowed_skills[skill];
}

public int sk_query_max(int skillnum, int silent)
{
    return allowed_skills[skillnum];
}

public int set_player_skills(object player)
{
    object provider = player->query_guild_trainer_occ();
    if (!provider)
        return 0;
    
    mapping all_skills = provider->get_all_skills();
    if (!m_sizeof(all_skills))
        return 0;
    
    player->catch_msg("Your ranger skills have been refreshed " +
        "back to the defaults.\n");
    
    foreach (int skill : m_indexes(all_skills))
    {
        player->set_skill(skill, all_skills[skill]);
    }
    player->set_skill(SS_BRAWLING, 100);
    player->set_skill(SS_AMBUSH, 100);
    player->set_skill(SS_HEARING, 100);
    return 1;
}

public void delayed_set_player_skills(string name)
{
    object player = find_player(name);
    if (!player)
    {
        set_alarm(60.0, 0.0, &delayed_set_player_skills(name));
        return 0;
    }
    set_player_skills(player);
}
