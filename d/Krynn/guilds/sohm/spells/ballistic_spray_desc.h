/*
 * Ballistic Spray Descriptions
 *
 * This file is included in the Ballistic Spray Spell
 *
 * Created by Arman, Dec 2016
 */
 

public void
ballistic_spray_desc_cast(object caster, object target)
{
    string caster_message, target_message, watcher_message;
    
    caster_message = "You thrust a closed fist towards " + QTNAME(target) + 
        ", opening your hand as your arm reaches full extension.\n";
    target_message = QCTNAME(caster) + " thrusts a closed fist towards you, " 
        + "opening " +HIS(caster)+ " hand as " +HIS(caster)+ " arm " +
        "reaches full extension.\n";
    watcher_message = QCTNAME(caster) + " thrusts a closed fist towards "
         + QTNAME(target) + ", opening " +HIS(caster)+ " hand as " +HIS(caster)+
         " arm reaches full extension.\n";
    
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, target, ({ caster, target }));    
}

public void
ballistic_spray_damage(object caster, object target, int phurt, string hitloc_desc)
{
    string target_message, watcher_message;
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "Summoned projectiles fly past you harmlessly.\n";
        watcher_message = "Summoned projectiles fly past " + 
            QTNAME(target) + " harmlessly.\n";
    }
    else
    {   
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "A summoned projectile hits your " + hitloc_desc 
                + ", inflicting a superficial wound.\n";
            watcher_message = "A summoned projectile hits " + QTNAME(target) +
                " in the " + hitloc_desc +  ", inflicting a superficial wound.\n";
            break;
            
        case 1..10:
            target_message = "Charged projectiles hit your " + hitloc_desc 
                + ", inflicting bruising wounds.\n";
            watcher_message = "Charged projectiles hit " + QTNAME(target) +
                " in the " + hitloc_desc +  ", inflicting bruising wounds.\n";
            break;
            
        case 11..30:
            target_message = "Charged projectiles slam in to you, "
                + "crushing your " + hitloc_desc + " painfully.\n";
            watcher_message = "Charged projectiles slam in to " + 
                QTNAME(target) + ", crushing " +target->query_possessive()+
                " " + hitloc_desc + " painfully.\n";

            break;
            
        case 31..60:
            target_message = "Many summoned projectiles violently smash " +
               "into your " +hitloc_desc+ " causing incredible damage.\n";
            watcher_message = "Many summoned projectiles violently smash "+
                "into the " +hitloc_desc+ " of " +QTNAME(target)+ ", causing " +
                "incredible damage.\n";
            break;
            
        default:
            target_message = "Many summoned projectiles explode in to you, " +
               "ripping through your " +hitloc_desc+ " and causing grievous " +
               "damage!\n";

            watcher_message = "Many summoned projectiles explode in to "
                + QTNAME(target) + ", devastating " +target->query_possessive()+
                " " +hitloc_desc+ " and causing grievous damage.\n"; 
            break;            
        }
    }
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
}

public void
ballistic_spray_desc_damage(object caster, object target, mixed * result)
{
    string caster_message, target_message, watcher_message;
    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    int phurt = result[0];
    string hitloc_desc = result[1];

    ballistic_spray_damage(caster, target, phurt, hitloc_desc);
  
}

