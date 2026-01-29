/*
 * Magic Missile Descriptions
 *
 * This file is included in the Magic Missile Spell
 *
 * Created by Arman, October 2016
 */
 

public void
magic_missile_desc_cast(object caster, object target)
{
    string caster_message, target_message, watcher_message;
    
        caster_message = "You extend your hand with fingers fanning outwards, " +
            "your palm directed towards " + QTNAME(target) + ".\n";
        target_message = QCTNAME(caster) + " extends " + caster->query_possessive()
            + " hand, fingers fanning outwards and palm directed towards you.\n";
        watcher_message = QCTNAME(caster) + " extends " + caster->query_possessive()
            + " hand, fingers fanning outwards and palm directed towards "
            + QTNAME(target) + ".\n";
    
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, target, ({ caster, target }));    
}

public void
missile_desc_damage(object caster, object target, int phurt, string hitloc_desc)
{
    string target_message, watcher_message;
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "A bolt of magical energy flies past you, "
            + "crackling menacingly before dissipating harmlessly.\n";
        watcher_message = "A bolt of magical energy flies past " + 
            QTNAME(target) + ", crackling menacingly before " +
            "dissipating harmlessly.\n";
    }
    else
    {   
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "A bolt of magical energy hits your " + hitloc_desc 
                + ", inflicting a superficial wound.\n";
            watcher_message = "A bolt of magical energy hits " + QTNAME(target) +
                " in the " + hitloc_desc +  ", inflicting a superficial wound.\n";
            break;
            
        case 1..10:
            target_message = "A bolt of magical energy hits your " + hitloc_desc 
                + ", inflicting bruising wounds.\n";
            watcher_message = "A bolt of magical energy hits " + QTNAME(target) +
                " in the " + hitloc_desc +  ", inflicting bruising wounds.\n";
            break;
            
        case 11..30:
            target_message = "A bolt of magical energy slams in to you, "
                + "crushing your " + hitloc_desc + " painfully.\n";
            watcher_message = "A bolt of magical energy slams in to " + 
                QTNAME(target) + " crushing " +target->query_possessive()+
                " " + hitloc_desc + " painfully.\n";

            break;
            
        case 31..60:
            target_message = "Three bolts of magical energy violently smash " +
               "into your " +hitloc_desc+ " causing incredible damage.\n";
            watcher_message = "Three bolts of magical energy violently smash "+
                "into the " +hitloc_desc+ " of " +QTNAME(target)+ ", causing " +
                "incredible damage.\n";
            break;
            
        default:
            target_message = "Three bolts of magical energy explode in to you, " +
               " ripping through your " +hitloc_desc+ " and causing grievous " +
               "damage to you!\n";

            watcher_message = "Three bolts of magical energy explode in to "
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
magic_missile_desc_damage(object caster, object target, mixed * result)
{
    string caster_message, target_message, watcher_message;
    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    int phurt = result[0];
    string hitloc_desc = result[1];

    missile_desc_damage(caster, target, phurt, hitloc_desc);
  
}

