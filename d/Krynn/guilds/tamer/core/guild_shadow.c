#pragma strict_types

inherit "/std/guild/guild_lay_sh";

#include "../defs.h"
#include "/d/Genesis/steed/new/steed.h"

#include "../safe_load.c"

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <state_desc.h>

/* Global Variables */
static mapping  gPetSkills = ([]);
/* Prototypes */
void remove_lay_member();

/* 
 * Function name: query_guild_tax_lay
 * Description:   Give the amount of tax the guild charges
 * Returns:       int - The tax amount
 */
int
query_guild_tax_lay() 
{ 
    return GUILD_TAX; 
}

/*
 * Function name: query_guild_style_lay
 * Description:   return the guild style for this guild
 * Returns:       string - the style
 */
string
query_guild_style_lay()
{
    return GUILD_STYLE;
}

/*
 * Function name: query_guild_name_lay
 * Description:   return the guild's name
 * Returns:       string - the guild name
 */
string
query_guild_name_lay()
{
    return GUILD_NAME;
}

/* 
 * Function name: query_guild_not_allow_join_lay
 * Description:   Check if we allow the player to join another guild.
 * Arguments:     player - the player
 *                type, style, name - the type, style and name of the
 *                      intended guild.
 * Returns:       1 if we do not allow, else 0
 */
int
query_guild_not_allow_join_lay(object player, string type, string style,
  string name)
{
    /* This checks to make sure that the new guild is not layman */
    if (::query_guild_not_allow_join_lay(player, type, style, name))
        return 1;

    return 0;
}

/* Function name: query_guild_level_lay
 * Description:   What is the member's level within the guild?
 * Returns:       int - the level
 */
int
query_guild_level_lay()
{
    return min(MAX_GUILD_LEVEL, shadow_who->query_stat(SS_LAYMAN) / 20);
}

/*
 * Function name: query_guild_title_lay
 * Description:   Return the member's guild title
 * Returns:       string - the title
 */
string 
query_guild_title_lay()
{
    string title = "", genus;
    int gender, skill, val;
    
    if (query_guild_level_lay() < 6)
        return TITLES[query_guild_level_lay()];
    
    MANAGER->add_achievement(shadow_who, GENUS_TITLES);
    
    if ((gender = shadow_who->query_gender()) > 1)
        gender = 0;
    
    if ((skill = MANAGER->query_title(shadow_who, "high")) > 0)
    {
        val   = min((sizeof(TITLE_LEVELS) - 1),
                query_shadow_who()->query_stat(SS_LAYMAN) /
                (sizeof(TITLE_LEVELS) * 5));
        title = TITLE_LEVELS[val];
        title += HIGH_TITLES[skill][gender];
    }
    else if (skill != -1)
    {
        title = TITLES[6];
    }
    
    if (!strlen(genus = MANAGER->query_pet_genus(shadow_who)))
        return title;
    
    if (MANAGER->query_title(shadow_who, genus))
    {
        if (strlen(title))
            title += ", ";
        
        title += GENUS->query_genus_title(genus)[gender];
    }
    
    return title;
}

/* 
 * Function name: query_guild_skill_name
 * Description:   Give a names for the guild's special skills
 * Arguments:     type - the number of the skill
 * Returns:       0 if no skill of mine, else the string.
 */
mixed
query_guild_skill_name(int type)
{
    return 0;
}

/*
 * Function name: query_guild_trainer_lay
 * Description:   Returns the skill trainers for the guild
 * Returns:       string * - an array of paths to the guild's
 *                trainers.
 */
mixed
query_guild_trainer_lay()
{
    return ({ PET_HOUSE });
}

/*
 * Function name: init_guild_member
 * Description:   Add necessary guild items to the player and
 *                do any other kind of initialization necessary.
 */
void
init_guild_member()
{
    object who = query_shadow_who();

    /* clone the guild emblem and move it to the player */

    setuid();
    seteuid(getuid());

    safely_load_master_file(MANAGER);
    safely_load_master_file(GENUS);
    safely_load_master_file(PET_HOUSE);
    
    /* add the guild's soul to the player */
    who->add_cmdsoul(GUILD_SOUL);
    who->update_hooks();
}

/*
 * Function name: init_lay_shadow()
 * Description:   This function is called from autoload_shadow and may
 *                be used to initialize the shadow when it's loaded.
 * Arguments:     The argument string sent to autoload_shadow.
 */
void init_lay_shadow(string arg)
{
    /* 
     * Delayed due to login
     */
    set_alarm(1.0, 0.0, init_guild_member);
}

/* 
 * Function name: add_lay_shadow
 * Description:   Shadow an object with this shadow
 * Arguments:     object who - the object to shadow
 * Returns:       as shadow_me in /std/guild/guild_base.c
 */
int add_lay_shadow(object who)
{
    return shadow_me(who, "layman", GUILD_STYLE, GUILD_NAME);
}

/*
 * Function name: remove_lay_member
 * Description:   remove this member from the guild
 */
void
remove_lay_member()
{
    object emblem, who = query_shadow_who();

    /* Clear the player's guild stat */
    who->clear_guild_stat(SS_LAYMAN);

    /* Remove the guild soul */
    who->remove_cmdsoul(GUILD_SOUL);
    who->update_hooks();

    /* Remove the guild shadow.  This also resets tax to 0. */
    remove_guild_lay();
}

public status
remove_pet_skill_effects(object pet)
{
    foreach(int skill, int value: gPetSkills)
    {
        if (!gPetSkills[skill])
            continue;
        
        shadow_who->set_skill_extra(skill, 
            shadow_who->query_skill_extra(skill) - value);
        gPetSkills[skill] = 0;
    }
    
    return 1;
}

public status
add_pet_skill_effect(object pet)
{
    mapping skill_list;
    
    if (!objectp(pet) || !present(pet, environment(shadow_who)))
        return 0;
    
    if (!m_sizeof(skill_list = GENUS->query_special_skills(pet->query_genus())))
        return 1;
    
    foreach(int skill, int value: skill_list)
    {
        if (gPetSkills[skill])
            continue;
        
        shadow_who->set_skill_extra(skill, 
            shadow_who->query_skill_extra(skill) + value);
        gPetSkills[skill] = value;
    }
    
    return 1;
}

public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int     skill,
            matur,
            result,
            success;
    mixed   mount;
    string *locs, com;
    
    mount   = MANAGER->query_current_pet(shadow_who);
    skill   = shadow_who->query_base_skill(SS_RIDING);
    matur   = mount->query_maturity();
    
    if (!objectp(mount) || environment(mount) != environment(shadow_who))
        return shadow_who->move_living(how, to_dest, dont_follow, no_glance);
        
    if (mount == shadow_who->query_prop(LIVE_O_STEED) && !result)
    {
        if (skill < 45 && !random(skill * matur))
        {
            mount->has_fallen_off("riding", shadow_who);
            return 7;
        }
        
        if (!random(SUCCESS(skill, matur)))
            mount->do_skill_raise(SS_RIDING, shadow_who);
        
        if (shadow_who->query_prop(LIVE_I_SNEAK) && 
            !CAN_SNEAK[mount->query_genus()])
        {
            shadow_who->catch_msg("It is too difficult to sneak " +
            "while mounted on the " + mount->short() + ".\n");
            shadow_who->reveal_me();
        }
    }
    
    result = shadow_who->move_living(how, to_dest, dont_follow, no_glance);
    locs   = GENUS->query_location(to_dest);
    
    if (shadow_who->query_prop(LIVE_O_STEED) != mount)
    {
        if (!(success = mount->follow_leader(how)))
            success = mount->follow_leader(to_dest);
    }
    
    if (!add_pet_skill_effect(mount))
        remove_pet_skill_effects(mount);
    
    if (objectp(to_dest) &&
        STEED_STS_SUCCESS(mount->check_mounted_destination(to_dest)))
        mount->unlead_and_mount_pet(shadow_who, result);
        
    if (present(mount, environment(shadow_who)))
    {
        if (!sizeof(locs))
            return result;
        
        foreach(string loc: locs)
        {
            if (IN_ARRAY(loc, ({"carnivore", "herbivore", "omnivore"})))
                MANAGER->add_achievement(shadow_who, FOOD_INN);
            
            if (IN_ARRAY(loc, ({"metal", "leather"})))
                MANAGER->add_achievement(shadow_who, FIND_PET_ARMOUR);
        }
    }
    
    return result;
}

/*
 * Function name:   query_skill
 * Description:     This has been masked to increase skills in
 *                  the player when mounted.
 * Arguments:       skill: The number of the skill to check
 * Returns:         The value of the skill
 */
public int
query_skill(int skill)
{
    int     result, matur;
    mixed  *pet;
    object  mount;
    mapping sk_list;
    
    result  = shadow_who->query_skill(skill);
    
    if (query_verb() == "skills")
        return result;
    
    if (shadow_who->query_base_skill(skill) > 60)
    {
        switch(skill)
        {
            case SS_ANI_HANDL:
            MANAGER->add_achievement(shadow_who, TITLE_ANI_HANDL);
                break;
            case SS_HUNTING:
            MANAGER->add_achievement(shadow_who, TITLE_HUNTING);
                break;
            case SS_TRACKING:
            MANAGER->add_achievement(shadow_who, TITLE_TRACKING);
                break;
            case SS_LOC_SENSE:
            MANAGER->add_achievement(shadow_who, TITLE_LOC_SENSE);
                break;
            case SS_SNEAK:
            MANAGER->add_achievement(shadow_who, TITLE_SNEAK);
                break;
        }
    }
    
    if (!objectp(mount = shadow_who->query_prop(LIVE_O_STEED)) ||
        member_array(skill, ({ SS_RIDING, SS_ANI_HANDL })) < 0 ||
        !(matur = mount->query_maturity()))
        return result;
    
    if (!random(SUCCESS(mount->query_skill(skill), matur)))
        mount->do_skill_raise(skill, shadow_who);
    
    return result;
}
        
public varargs mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc = -1)
{
    object  mount;
    int     phurt;
    mixed  *hitres;

    hitres  = shadow_who->hit_me(wcpen, dt, attacker, attack_id);
    phurt   = hitres[0];

    if (objectp(mount = MANAGER->query_current_pet(shadow_who)))
    {
        if (present(mount, environment(shadow_who)))
        {
            MANAGER->add_achievement(shadow_who, TKILL);
            MANAGER->add_achievement(shadow_who, TASSIST);
        }
    }
    
    if (!(mount = shadow_who->query_prop(LIVE_O_STEED)))
        return hitres;
    
    if (phurt > 5 && (random(shadow_who->query_skill(SS_RIDING) *
        mount->query_maturity()) < phurt))
        mount->has_fallen_off("combat", attacker);

    return hitres;
}


/*
 * Function name: linkdeath_hook
 * Description  : This routine is called when the player linkdies. Do not mask
 *                it unless you really need to.
 * Arguments    : int linkdeath - 1/0 - if true, the player linkdied, else
 *                    he revives from linkdeath.
 */
public void
linkdeath_hook(int linkdeath)
{
    object pet;
    
    if (linkdeath && objectp(pet = MANAGER->query_current_pet(shadow_who)))
        pet->move_living("X", PET_HOUSE, 0, 0);
    
    shadow_who->linkdeath_hook(linkdeath);
} /* linkdeath_hook */


/*
 * Function name: remove_object
 * Description:   Destruct this object, but check for possessed first
 */
public void
remove_object()
{
    object pet;
    
    if (objectp(pet = MANAGER->query_current_pet(shadow_who)))
        pet->move_living("X", PET_HOUSE, 0, 0);
    
    shadow_who->remove_object();
} /* remove_object */
