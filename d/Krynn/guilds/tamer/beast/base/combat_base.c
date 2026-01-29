#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

inherit "/d/Krynn/guilds/tamer/beast/base/mount_base";

#include "defs.h"

// Prototypes
public void     check_unconscious();
public int      do_skill_raise(int num, object player);
public mixed    query_obj_m_no_attack();

// Global Variables
static int  gLastSkill, gDecked,
            gCease, gDeathTimer;
mapping     gInjury;


public void
create_battle_beast()
{
}

public nomask void
create_mount()
{
    create_battle_beast();
    ::create_mount();
    add_prop(OBJ_M_NO_ATTACK, &query_obj_m_no_attack());
}
     
/* Function name: set_injury
 * Description:   Sets injuries sustained from death.
 */
public void
set_injury(int timeof, string injuries)
{
    if (!timeof)
        return;
    
    if (!mappingp(gInjury))
        gInjury = ([]);
    
    gInjury += ([ injuries : timeof ]);
}

/* Function name: query_injury
 * Description:   Returns which injuries the beast has sustained
 *                from death.
 */
public mapping
query_injury()
{
    return gInjury;
}

public void
update_injury()
{
    if (mappingp(MANAGER->query_pet_injuries(query_tamer())))
    {
        gInjury = ([]) + MANAGER->query_pet_injuries(query_tamer());
    }
}

public int
query_unconscious()
{
    if (gDecked)
        check_unconscious();
    
    return gDecked;
}

public void
cease_hostility(int set)
{
    object  enemy, tamer,
           *enemies;

    enemies = filter(all_inventory(environment()),
              &operator(==)(this_object()) @ &->query_attack());
    
    if (!objectp(tamer = query_tamer()))
        return;
    
    if (query_prop(LIVE_I_STUNNED))
    {
        tamer->catch_msg(QCTNAME(this_object()) + " is currently stunned.\n");
        return;
    }
    
    if (query_unconscious())
    {
        tamer->catch_msg(QCTNAME(this_object()) + " is unconscious and "
        + "therefore not hostile.\n");
        return;
    }
    
    if (!gCease && set && query_attack())
    {
        tell_room(environment(), QCTNAME(this_object()) + " calms down and "
        + "stops fighting.\n", enemies);
        enemies->catch_msg(QCTNAME(this_object()) + " appears to have calmed "
        + "down, maybe you could 'stop fighting' it.\n");
        stop_fight(enemies);
        gCease = 1;
        set_alarm(10.0, 0.0, &cease_hostility(0));
        return;
    }
    
    if (set)
        return;
    
    if (sizeof(enemies) && !query_attack())
    {
        if (enemy = tamer->query_attack())
            attack_object(enemy);
        else
            attack_object(enemies[0]);
        
        tell_room(environment(), QCTNAME(this_object()) + " is "
        + "once again hostile.\n");
    }
    
    gCease = 0;
}

public void
hook_stop_fighting_offer(object attacker)
{
    if (!IN_ARRAY(TCALM, MANAGER->query_achievements(query_tamer())))
        MANAGER->add_achievement(query_tamer(), TCALM);
    
    if (gCease)
    {
        attacker->catch_msg(QCTNAME(this_object()) + " withdraws, glaring "
        + "angrily at you, ceasing hostility.\n");
        tell_room(environment(), QCTNAME(this_object()) + " "
        + "withdraws, glaring at " + QTNAME(attacker) + ", ceasing hostility"
        + ".\n", attacker);
        attacker->stop_fight(this_object());
    }
    else if (!query_unconscious() && query_attack())
    {
        attacker->catch_msg(QCTNAME(this_object()) + " growls threateningly "
        + "at you.\n");
        tell_room(environment(), QCTNAME(this_object())
        + " growls threateningly at " + QTNAME(attacker) + ".\n", attacker);
    }
}

void
run_away()
{
}

public void
check_unconscious()
{
    object tamer = query_tamer();
    
    if (!objectp(tamer))
    {
        tell_room(environment(), QCTNAME(this_object()) + " "
        + "regains its consciousness and hastily makes a run for it, "
        + "disappearing into the distance.\n");
        remove_object();
    }
    
    if (environment() != environment(tamer))
    {
        tell_room(environment(), QCTNAME(this_object()) + " "
        + "regains its consciousness and hastily makes a run for it, "
        + "disappearing into the distance.\n");
        move_living("M",PET_HOUSE, 1);
        return;
    }
    
    if (gDecked && random(MANAGER->query_pet_age(tamer) - gDecked) > 50)
    {
        tell_room(environment(), QCTNAME(this_object()) + " regains "
        + query_possessive() + " consciousness.\n");
        gDecked = 0;
    }
    
    if (!m_sizeof(query_injury()))
        return remove_alarm(gDeathTimer);
    
    foreach(string injured, int timeof: gInjury)
    {
        if (MANAGER->query_pet_age(tamer) - timeof > INJURY_TIME)
        {
            tell_room(environment(), QCTNAME(this_object())
            + " has recovered from " + this_object()->query_possessive()
            + " injured " + injured + ".\n");
            MANAGER->remove_pet_injury(tamer, injured);
        }
    }
    
    gInjury = MANAGER->query_pet_injuries(tamer);
}

public void
do_die(object killer)
{
    int     avg;
    string *injuries, inj;
    object *enemies, tamer;
    
    if (query_hp() > 0 || query_unconscious())
        return;
    
    avg = query_average_stat();
    
    if (!objectp(tamer = query_tamer()))
        return ::do_die(killer);
    
    if (objectp(killer))
    {
        avg = ((avg * avg * avg) / 
              (killer->query_average_stat() ?
               killer->query_average_stat() : avg));
    
        if (avg > 1)
            MANAGER->add_satisfaction(tamer, -avg, this_object());
    }
    
    injuries = m_indexes(GENUS->query_hitlocs(query_genus()));
    injuries = filter(injuries, &operator(==)(,-1) @
               &member_array(, m_indexes(this_object()->query_injury())));
    
    gDecked  = MANAGER->query_pet_age(tamer);
    enemies  = filter(all_inventory(environment()),
               &operator(==)(this_object(),) @ &->query_attack());

    if (!gDeathTimer)
        gDeathTimer = set_alarm(1.0, 10.0, &check_unconscious());
    
    if (environment(tamer) != environment())
    {
        tell_room(environment(), QCTNAME(this_object()) + " makes "
        + "a run for it, disappearing into the distance.\n");
        move_living("M",PET_HOUSE, 1);
        return;
    }
    
    if (sizeof(enemies) > 0)
    {
        foreach(object enemy: enemies)
        {
            enemy->catch_msg("You turn to attack " + QTNAME(tamer) + "\n");
            enemy->attack_object(tamer);
            stop_fight(enemy);
        }
    }
    
    if (!sizeof(injuries))
    {
        tell_room(environment(), QCTNAME(this_object()) +  " has fallen "
        + "unconscious from the intensities of combat.\n");
        
        if (query_driver())
            do_dismount(query_driver());
        
        return;
    }
    
    inj  = one_of_list(injuries);
    
    tell_room(environment(), QCTNAME(this_object()) + " sustained a "
    + "lasting injury and has fallen unconscious due to the intensities of "
    + "combat.\n");
    
    if (query_driver())
        do_dismount(query_driver());
    
    set_injury(MANAGER->query_pet_age(tamer), inj);
    
    MANAGER->set_pet_injuries(tamer, gInjury);
    
    MANAGER->add_achievement(tamer, PET_INJURY);
    return;
}

public varargs mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc = -1)
{
    int     success,
            phurt,
            matur,
            skill;
    mixed  *hitres;
    object *tamer;
    
    hitres  = ::hit_me(wcpen, dt, attacker, attack_id);
    skill   = query_skill(SS_MOUNTED_COMBAT);
    matur   = (query_maturity() ? query_maturity() : 1);
    success = ((skill ? skill : 1) * ((skill ? skill : 3) / 3)) / matur;
    phurt   = hitres[0];

    if (sizeof(tamer = filter(all_inventory(environment()),
               &operator(==)(query_tamer_name()) @ &->query_real_name())) &&
              (tamer[0]->query_skill(SS_ANI_HANDL) >= 30))
        MANAGER->add_achievement(query_tamer(), TMANEUVER);
    
    if (objectp(query_driver()))
        if (phurt > 5 && (random(skill * query_maturity()) < phurt))
            query_driver()->has_fallen_off("combat", attacker);

    if (!random(success))
        do_skill_raise(SS_MOUNTED_COMBAT, this_object());
    
    skill   = query_skill(SS_DEFENCE);
    success = ((skill ? skill : 1) * ((skill ? skill : 3) / 3)) / matur;
    
    if (!random(success))
        do_skill_raise(SS_DEFENCE, this_object());
    
    return hitres;
}

public int
special_attack(object victim)
{
    if (!(SPECIALS + "pet_attack")->query_ability_active(this_object()))
        command("attack");
    
    return 1;
}


/*
 * Function name: stop_fight
 * Description  : Makes this living stop fighting others.
 * Arguments    : mixed elist - the enemy or enemies to stop fighting.
 */
public void
stop_fight(mixed elist)
{
    ::stop_fight(elist);
    
    if ((SPECIALS + "pet_attack")->query_ability_preparing(this_object()))
    {
        if (!pointerp(elist))
            elist = ({ elist });
        
        if (!sizeof(query_enemy(-1)) ||
            member_array(query_attack(), elist) > -1)
            (SPECIALS + "pet_attack")->stop_ability(this_object());
    }
}

public mixed
query_obj_m_no_attack()
{
    object player;
    
    if (!objectp(player = query_tamer()))
    {
        this_player()->catch_msg(QCTNAME(this_object()) + " runs away, your "
        + "attempts to catch up proves to be futile.\n");
        tell_room(environment(), QCTNAME(this_object()) + " runs away into the "
        + "distance.\n", ({ this_player() }));
        set_alarm(0.0, 0.0, &remove_object());
        return "";
    }
    
    if (player == this_player())
        return "You cannot attack your own pet.\n";
    
    if (IN_ARRAY(this_player(), player->query_team()))
        return "You cannot attack the pet of a team member.\n";
    
    if (environment(player) != environment(this_object()) &&
        query_unconscious())
    {
        tell_room(environment(), QCTNAME(this_object()) + " has recovered from "
        + query_possessive() + " unconscious state and escaped.\n");
        
        move_living("M",PET_HOUSE, 1);
        return "";
    }
    
    if (query_unconscious())
        return "The " + query_nonmet_name() + " is guarded by "
        + query_possessive() + " tamer, you are unable to approach.\n";
    
    return 0;
}

public int
has_fallen_off(string str, object cause)
{
    object rider = query_driver();
    
    if (!objectp(rider))
        return -3;
    
    switch(str)
    {
        case "riding":
        MANAGER->add_achievement(rider, HAS_FALLEN_RIDING);
        rider->catch_msg("You have trouble maintaining your balance and fall "
        + "to the ground.\n");
        tell_room(environment(), QCTNAME(rider) + " falls off from the back of "
        + QTNAME(this_object()) + ".\n", ({ rider }));
            break;
        
        case "combat":
        MANAGER->add_achievement(rider, HAS_FALLEN_COMBAT);
        rider->catch_msg("You fail to maintain your balance and are " +
        "violently thrown to the ground, landing on your back.\n");
        
        tell_room(environment(), QCTNAME(rider) + " is violently thrown from "
        + "the back off " + QTNAME(this_object()) + ", slamming "
        + rider->query_possessive() + " back hard onto the ground.\n",
        ({ rider }));
            break;
        
        default:
            return 0;
    }
    
    rider->remove_rider_shadow();
    remove_rider(rider);
    return -1;
}

/* Function name: set_family
 * Description:   Sets the family name of the beast.
 */
public void
set_last_skill(int skill)
{
    gLastSkill = skill;
}

/* Function name: query_family
 * Description:   Returns the family name of the beast.
 */
public int
query_last_skill()
{
    return gLastSkill;
}

public int
do_skill_raise(int num, object player)
{
    /* Lets allow the special to ignore cooldown */
    if ((time() - query_last_skill()) < SKILL_DELAY &&
        num != SS_MOUNTED_COMBAT)
        return 0;
    
    if (!query_genus() || !objectp(query_tamer()))
        return 0;
    
    int     cost,
            level = 0,
            skill;
    mapping list = ([]);
    mixed  *skillslist;

    if (!IN_ARRAY(num, m_indexes(SKILLS)))
        if (this_object() != player)
            return 0;
    
    if (!IN_ARRAY(num, m_indexes(GENUS->query_pet_skills(query_genus()))))
        if (player == this_object())
            return 0;

    if (player != this_object())
        skillslist = ({}) + SKILLS[num];
    else
        skillslist = ({}) + GENUS->query_pet_skills(query_genus())[num];
    
    level = player->query_base_skill(num);
    
    if (level + 1 > skillslist[2])
        return 0;
    
    cost =  ((((level + 1) * (level + 1) * (level + 1)) *
            skillslist[3]) / 100) - (((level * level * level) *
            skillslist[3]) / 100);
    
    if (cost < 1)
        cost = 1;
    
    if (!MANAGER->add_satisfaction(query_tamer(), -cost, 0))
        return 0;
    
    if (!player->set_skill(num, (level + 1)))
        return 0;

    if (player != this_object())
    {
        player->catch_msg("Your ability to " + skillslist[1] +
        " has improved slightly.\n");
        MANAGER->add_achievement(player, ADD_TAMER_SKILL);
    }
    else
    {
        query_tamer()->catch_msg(QCTNAME(this_object()) + " has improved "
        + this_object()->query_possessive() + " ability to " + skillslist[1]
        + ".\n");
        MANAGER->add_achievement(query_tamer(), ADD_PET_SKILL);
        
        foreach(int sk: this_object()->query_all_skill_types())
        {
            list += ([ sk : this_object()->query_base_skill(sk) ]);
        }
        MANAGER->set_skills(query_tamer(), list);
    }
    
    /* Lets allow the special to ignore cooldown */
    if (num != SS_MOUNTED_COMBAT)
        this_object()->set_last_skill(time());
    
    return 1;
}

/*
 * Function name:   query_skill
 * Description:     This has been masked to percentually increase
 *                  the pets skill to match the owner.
 * Arguments:       skill: The number of the skill to check
 * Returns:         The value of the skill
 */
public int
query_skill(int skill)
{
    mixed  *pet;
    int     tskill,
            pskill,
            test,
            result;
    
    result = ::query_base_skill(skill);
    
    if (!objectp(query_tamer()) || !query_genus())
        return result;
    
    tskill  = query_tamer()->query_base_skill(skill);
    pet     = ([]) + GENUS->query_pet_skills(query_genus());
    pskill  = ::query_base_skill(skill);
    
    if (!IN_ARRAY(skill, m_indexes(GENUS->query_pet_skills(query_genus()))))
        return 0;
    
    if (skill == SS_MOUNTED_COMBAT)
        return result;
    
    if (!random(SUCCESS(pskill, query_maturity())))
        do_skill_raise(skill, this_object());
    
    if (!(pskill = (pskill ? pskill : 1) * tskill))
        return result;
    
    if (pointerp(pet = pet[skill]))
        return pskill / pet[2];
    
    return result;
}

public int
query_stat(int stat)
{
    object player;
    
    if ((stat == SS_LAYMAN) && objectp(query_tamer()))
        return player->query_stat(stat);
    
    return ::query_stat(stat);
}

void
conf_hitlocs()
{
    mapping hitlocs;
    int    *hids, *list, prot, s;
    
    prot = (query_maturity() * 2) - 1;
    hids = ({ A_HEAD, A_BODY, A_R_ARM, A_L_ARM, A_LEGS });
    hitlocs = GENUS->query_hitlocs(query_genus());
    list    = m_indexes(hitlocs);
    
    for (s = 0; s < sizeof(list); s++)
    {
        set_hitloc_unarmed(hids[s], (prot * hitlocs[list[s]][0]) / 100,
                                            hitlocs[list[s]][1], list[s]);
    }
}

void
conf_stats(object player)
{
    int *list, stat, s;
    
    stat = player->query_average_stat() / (9-query_maturity());
    
    if (BETA_TEST)
        stat = player->query_average_stat();
    
    list = GENUS->query_stats(query_genus());
    
    for (s = 0; s < sizeof(list); s++)
    {
        list[s] = (stat * list[s]) / 100;
    }
    
    set_stats(list, 2);
}

/* Function name: configure_genus
 * Description:   Sets racial abilities and hitlocs.
 */
public void
configure_genus()
{
    object  player;
    string  tamer, genus;

    if (!strlen(tamer = query_tamer_name()))
        return;
    
    genus = query_genus();
    
    if (MANAGER->load_member(tamer))
    {
        player  = find_player(tamer);
        
        set_genus(MANAGER->query_pet_genus(tamer));
        set_race_name(MANAGER->query_pet_race(tamer));
        set_adj(MANAGER->query_pet_adjs(tamer));
        set_name(MANAGER->query_pet_name(tamer));
        add_name(GENUS->query_name(genus));
        set_fur(GENUS->query_fur(genus));
        
        set_mm_out(GENUS->query_mm_out(genus) + " elsewhere.");
        set_mm_in(GENUS->query_mm_in(genus) + " in.");
        set_m_out(GENUS->query_mm_out(genus));
        set_m_in(GENUS->query_mm_in(genus));
    
        MANAGER->set_current_pet(tamer, this_object());
        
        this_object()->update_injury();
        
        foreach(int sk, int val: MANAGER->get_skills(tamer))
        {
            this_object()->set_skill(sk, val);
            
            if (BETA_TEST)
                this_object()->set_skill(sk, 50);
        }
        
        conf_hitlocs();
        conf_stats(player);
    
        add_name(GENUS->query_family(genus));
    
        this_object()->set_vorare(GENUS->query_vorare(genus));
    
        this_object()->set_short(genus + " pet");
        this_object()->set_long("This is a " + genus + " pet.\n");
    
        this_object()->check_unconscious();
    }
    
    refresh_living();
    set_stuffed(this_object()->query_prop(LIVE_I_MAX_EAT));
}

/*
 * Function name:   heal_hp
 * Description:     Increase the number of hitpoints with a few.
 * Arguments:       (int) hp: The difference
 * Returns:         Nothing
 */
void
heal_hp(int hp)
{
    ::heal_hp(hp);
    
    call_hook(HOOK_TAMER_HEAL_HP, this_object());
} /* heal_hp */