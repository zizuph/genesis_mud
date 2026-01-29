#include <formulas.h>
#include <ss_types.h>
#include "../defs.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"

static float
    Resource_fail = 0.0;    /*  The % to reduce when the ability fails */

static int
    Resource_needed = 0;    /*  The amount needed to perform the ability */

static mixed
    Resource_factor = 1.0;  /*  The factor for more expensive spells */

public void
hook_no_resource_fail(string resource_desc)
{
    write("You don't have enough " + resource_desc + ".\n");
}

public float
query_ability_resource_factor()
{
    if (functionp(Resource_factor))
    {
        function f = Resource_factor;
        return f();
    }
    
    return Resource_factor;
}

public void
set_ability_resource_factor(float factor)
{
    Resource_factor = factor;
}

public float
query_ability_resource_fail()
{
    return Resource_fail;
}

public void
set_ability_resource_fail(float fail)
{
    Resource_fail = fail;
}

public int
query_ability_resource_needed()
{
    return Resource_needed;
}

public void
set_ability_resource_needed(int needed)
{
    Resource_needed = needed;
}

public int get_maintained_combat_aid(object living)
{
    int total;
  
    string lay_style = living->query_guild_style_lay();
    string occ_style = living->query_guild_style_occ();
    
    if (living->query_npc())
    {
        return 200;
    }
  
    if (lay_style == "magic" || lay_style == "cleric")
    {
        total += 40;
    }
    else
    {
        total += 20;
    }
  
    if (occ_style == "magic")
    {
        total += 190;
    }
    else if (occ_style == "cleric")
    {
        total += 160;
    }
    else if (occ_style == "ranger")
    {
        total += 80;
    }
    else
    {
        total += 20;
    }
    return total;
}

public int get_dynamic_mana_cost(object living, mixed stats,
                                 int combat_aid, int task,
                                 int time)
{
    int modifier = combat_aid;
    if (!combat_aid)
    {
        modifier = task / 10;
    }
    if (!time)
    {
        // No time set, use one round of combat by default.
        time = 5;
    }
    
    if (intp(stats))
    {
        stats = ({ stats });
    }
    
    int drm = living->find_drm(stats) / 2;
    // Spell cost is a fraction of the total maintained combat aid
    // for the player, modified by the maintenance/spellcasting
    // time relative to the mana healing interval.
    int result = 
    F_DYNAMIC_SPELL_COST(drm) * modifier * 
        time / F_INTERVAL_BETWEEN_MANA_HEALING
        / get_maintained_combat_aid(living);

    result = max(1, result);
    send_debug_message("dynamic_mana_cost", 
       sprintf("%s %s drm %d modifier %d time %d result %d",
       living->query_real_name(), 
       this_object()->short(),
       drm, modifier, time, result));
    return result;    
}                                     

static int
query_ability_resource_cost(object actor, string resource_name)
{
    int resource = 0;
    mixed stats = this_object()->query_ability_stats();
    int time = this_object()->query_ability_time();
    int combat_aid = this_object()->query_ability_combat_aid();
    int task = this_object()->get_spell_task();
    switch(resource_name)
    {
        case "mana":/*
            int skill = 200 - actor->query_skill(SS_SPELLCRAFT);
            int stat = actor->query_stat(SS_WIS);
            if (this_object()->query_ability_combat_aid())
            {
                // Use 250 caid as the basis of mana
                resource = F_MANA_HEAL_FORMULA(skill, 0, stat)
                    * this_object()->query_ability_combat_aid() * time 
                    / 250 / F_INTERVAL_BETWEEN_MANA_HEALING;
            } else // Double mana regen for the duration of casts without caid
                resource = 2 * F_MANA_HEAL_FORMULA(skill, 0, stat)
                    * max(1, this_object()->query_ability_time())
                    / F_INTERVAL_BETWEEN_MANA_HEALING;
            */
            //resource = 15; //query_ability_resource_needed(); // Testing
            resource = get_dynamic_mana_cost(actor, stats,
              combat_aid, task, time);
            break;
        case "health":
            resource = 15;
            break;
    }
    
    // Scale based on resource factor.
    return ftoi(itof(resource) * query_ability_resource_factor());
}

public int
mana(object actor, mixed *targets, string arg, mixed *items, int pretest)
{
    int needed, reduce, total;

    total = query_ability_resource_cost(actor, "mana");
    if (pretest)
    {
        reduce = max(1, ftoi(itof(total) * (1.0 - Resource_fail)));
        needed = reduce;
    }
    else
    {
        reduce = ftoi(itof(total) * Resource_fail);
        needed = total;
    }

    if (actor->query_mana() < needed)
    {
        hook_no_resource_fail("mana");
        return 0;
    }
    
    actor->add_mana(-reduce);
    return 1;
}

public int
health(object actor, mixed *targets, string arg, mixed *items, int pretest)
{
    int needed, reduce, total;

    total = query_ability_resource_cost(actor, "health");
    if (pretest)
    {
        reduce = max(1, ftoi(itof(total) * (1.0 - Resource_fail)));
        needed = reduce;
    }
    else
    {
        reduce = ftoi(itof(total) * Resource_fail);
        needed = total;
    }
    
    actor->heal_hp(-reduce);

    if (actor->query_hp() <= 0)
    {
        hook_no_resource_fail("health");
        actor->do_die(actor);
        return 0;
    }

    return 1;
}