/*
 * Bruise object
 *
 * Creator: Zizuph 10-2021
 *
 * When the bruising boots hit an enemy, they experience a temporary
 * loss in acrobat or parry skill (depending on hit location)
 * This will drop up to 30 points of skill at any time.
 *
 * The skill is returned over time.
 */


inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>

#define TO this_object()
#define ENV(obj)   environment(obj)

int potential_parry_loss = 0;
int potential_acrobat_loss = 0;
int parry_loss = 0;
int acrobat_loss = 0;

public void create_object()
{
    set_name("_bruised_boots_obj");
    
    set_no_show();
    set_no_show_composite(1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GET, 1);
}


public void update_effects()
{
    
    // First remove prior losses
    ENV(TO)->set_skill_extra(SS_PARRY,
        ENV(TO)->query_skill_extra(SS_PARRY) + parry_loss);
    
    ENV(TO)->set_skill_extra(SS_ACROBAT,
        ENV(TO)->query_skill_extra(SS_ACROBAT) + acrobat_loss);
        
    // Then, compute desired losses, parry preferred.
    parry_loss = min(potential_parry_loss, 30);
    parry_loss = min(parry_loss, ENV(TO)->query_skill(SS_PARRY));

    ENV(TO)->set_skill_extra(SS_PARRY,
        ENV(TO)->query_skill_extra(SS_PARRY) - parry_loss);
    
    acrobat_loss = min(potential_acrobat_loss, 30 - parry_loss);
    acrobat_loss = min(acrobat_loss, ENV(TO)->query_skill(SS_ACROBAT));

    ENV(TO)->set_skill_extra(SS_ACROBAT,
        ENV(TO)->query_skill_extra(SS_ACROBAT) - acrobat_loss);
    
}

public void arm_better()
{
    potential_parry_loss -=10;
    
    tell_object(environment(this_object()),
        potential_parry_loss ?
          "Your arm starts to feel a little better.\n" :
          "Your arm feels better.\n");

    update_effects();
    if (!potential_parry_loss && !potential_acrobat_loss)
    {
        remove_object();
    }
}

public void arm_hit()
{
    tell_object(environment(this_object()),
        potential_parry_loss ?
          "Your arm feels more sore after that hit.\n" :
          "Your arm feels sore after that hit.\n");

    potential_parry_loss += 10;
    update_effects();
    
    set_alarm(120.0, 0.0, arm_better);
    
}

public void leg_better()
{
    potential_acrobat_loss -=10;
    
    tell_object(environment(this_object()),
        potential_acrobat_loss ?
          "Your legs starts to feel a little better.\n" :
          "Your legs feel better.\n");

    update_effects();
    if (!potential_parry_loss && !potential_acrobat_loss)
    {
        remove_object();
    }
}

public void leg_hit()
{
    tell_object(environment(this_object()),
        potential_acrobat_loss ?
          "Your legs feel more sore after that hit.\n" :
          "Your legs feel sore after that hit.\n");

    potential_acrobat_loss += 10;
    update_effects();
    
    set_alarm(120.0, 0.0, leg_better);
}



