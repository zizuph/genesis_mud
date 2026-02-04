/*
 *
 *  Extended version of spell class
 *
 *  This variant of spell allows one to add a blood cost, as well as a
 *  minimum guild stat for effect.
 *
 *  It also overrides the standard messages with more vampire-specific
 *  ones
 *
 *  Created May 2008, by Novo
 */

#include "../guild.h"
#include <math.h>
#include <macros.h>

int BloodCost;

int Min_guild_stat;

public void set_min_guild_stat(int stat)
{
    Min_guild_stat=stat;
}

public int query_min_guild_stat()
{
    return Min_guild_stat;
}

public void set_blood_cost(int cost)
{
   BloodCost=cost;

}

public int query_blood_cost()
{
    return BloodCost;
}

public void
list_spells()
{
    int min_stat=Min_guild_stat + 20 - 
       NAME_TO_RANDOM(TP->query_real_name(),
        NAME_TO_RANDOM(query_ability_name(),0,1000),40);
    if (TP->query_vamp_stat()>min_stat)
    {
        ::list_spells();
    }
}

public varargs int
config_blood_spell(object caster, object *targets, string argument)
{
    set_min_guild_stat(100);
    set_ability_vocal(0);
    set_ability_visual(0);
    set_blood_cost(1000);
    set_spell_fail("You fail to reach your desired state of being.\n");
}


public varargs int
reduce_mana(object caster, int amnt, int test)
{
    //NPC vampires don't get charged
    if (caster->query_npc())
    {
        return 1;
    }
    
    if (caster->query_mana() < amnt)
    {
        write("You don't have enough mana to use this gift.\n");
        return 0;
    }
    if (caster->query_blood() < BloodCost*amnt/get_spell_mana())
    {
        write("You need more blood to use this gift.\n");
        return 0;
    }

    if (!test)
    {
        caster->add_mana(-amnt);
        caster->add_blood(-BloodCost*amnt/get_spell_mana());
    }

    return 1;
}

/*
 * Function name: hook_no_mana_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have enough mana.
 * Returns:       The message to print.
 */
public void
hook_no_mana_fail(object ability)
{
}


static int
query_casting_success(object caster)
{
    //NPCs always pass
    if (caster->query_npc())
    {
        return 100;
    }

    int result=::query_casting_success(caster);
    
    int stat=caster->query_vamp_stat();
    
    int min_stat=Min_guild_stat + 20 - 
       NAME_TO_RANDOM(caster->query_real_name(),
        NAME_TO_RANDOM(query_ability_name(),0,1000),40);
    
    if (stat<=min_stat)
    {
        result=max(0,
          result + (stat-min_stat)*get_spell_task()/100);
    }
    else
    {
        if (result)
        {
            result+=(stat-min_stat)*100/get_spell_task();
        }
    }
    write_file(LOG_DIR+"spells",ctime(time())+" " +
        capitalize(caster->query_real_name())+" cast "+
        query_ability_name()+", result: "+result+"\n");
    return result;
    
}

public void
concentrate_msg(object caster, mixed * targets, string arg)
{
    caster->catch_tell("You focus your energies inward.\n");
    WATCHERS(caster)->catch_msg(QCTNAME(caster) + " narrows "+
        POSS(caster)+" eyes.\n");
}

public void
hook_changed_env()
{
    write("Your movement has disturbed your focus.\n");
}

