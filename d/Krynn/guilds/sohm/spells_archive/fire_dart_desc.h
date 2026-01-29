/*
 * Fire Dart Descriptions
 *
 * This file is included in the Fire Dart Spell
 *
 * Created by Arman, Feb 2016
 */
 

public void
fire_dart_desc_cast(object caster, object target)
{
    string caster_message, target_message, watcher_message;
    
        caster_message = "With a flick your wrist you make an arcane gesture " +
            "towards " + QTNAME(target) + ".\n";
        target_message = QCTNAME(caster) + " flicks " + caster->query_possessive()
            + " wrist, making an arcane gesture towards you.\n";
        watcher_message = QCTNAME(caster) + " flicks " + caster->query_possessive()
            + " wrist towards " + QTNAME(target) + ", making an arcane gesture towards " 
            + target->query_objective()+ ".\n";
    
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, target, ({ caster, target }));    
}

public void
dart_desc_damage(object caster, object target, int phurt, string hitloc_desc)
{
    string target_message, watcher_message;
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "A fiery dart flies past you, doing little more than "
            + "warming your face before dissipating harmlessly.\n";
        watcher_message = "A fiery dart flies past " + 
            QTNAME(target) + ", leaving a trail of faint smoke as it " +
            "dissipates harmlessly.\n";
    }
    else
    {   
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "A fiery dart hits your " + hitloc_desc 
                + ", scorching you superficially.\n";
            watcher_message = "A fiery dart hits " + QTNAME(target) +
                " in the " + hitloc_desc +  ", scorching " + 
                target->query_objective()+ " superficially.\n";
            break;
            
        case 1..10:
            target_message = "A fiery dart hits your " + hitloc_desc 
                + ", inflicting blistering wounds.\n";
            watcher_message = "A fiery dart hits " + QTNAME(target) +
                " in the " + hitloc_desc +  ", inflicting blistering wounds.\n";
            break;
            
        case 11..30:
            target_message = "A fiery dart explodes in to you, "
                + "burning your " + hitloc_desc + " painfully.\n";
            watcher_message = "A fiery dart explodes in to " + 
                QTNAME(target) + " burning " +target->query_possessive()+
                " " + hitloc_desc + " painfully.\n";

            break;
            
        case 31..60:
            target_message = "A fiery dart explodes into you, roasting your " 
                +hitloc_desc+ " and causing incredible damage.\n";
            watcher_message = "A fiery dart explodes into "+ QTNAME(target)+
                ", roasting " +target->query_possessive()+ " " +hitloc_desc+ 
                " and causing incredible damage.\n";
            break;
            
        default:
            target_message = "A seething bolt of fire explodes into you, " +
               " engulfing your " +hitloc_desc+ " and causing fatal " +
               "damage to you!\n";

            watcher_message = "A seething bolt of fire explodes into "
                + QTNAME(target) + ", engulfing " +target->query_possessive()+
                " " +hitloc_desc+ " and causing fatal damage.\n"; 
            break;            
        }
    }
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
}

public void
fire_dart_desc_damage(object caster, object target, mixed * result)
{
    string caster_message, target_message, watcher_message;
    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    int phurt = result[0];
    string hitloc_desc = result[1];

    dart_desc_damage(caster, target, phurt, hitloc_desc);
  
}

