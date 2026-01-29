/*
 * Acid Arrow Descriptions
 *
 * This file is included in the Acid Arrow Spell
 *
 * Created by Arman, Feb 2016
 */
 

public void
acid_arrow_desc_cast(object caster, object target)
{
    string caster_message, target_message, watcher_message;
    
        caster_message = "You hurl your open hands towards "+ QTNAME(target) + 
            ".\n";
        target_message = QCTNAME(caster) + " hurls " + caster->query_possessive()
            + " open hands towards you.\n";
        watcher_message = QCTNAME(caster) + " hurls " + caster->query_possessive()
            + " open hands towards " + QTNAME(target) + ".\n";
    
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, target, ({ caster, target }));    
}

public void
arrow_desc_damage(object caster, object target, int phurt, string hitloc_desc)
{
    string target_message, watcher_message;
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "An arrow of acid hisses past you, "
            + "dissipating harmlessly.\n";
        watcher_message = "An arrow of acid hisses past " + 
            QTNAME(target) + " and dissipates harmlessly.\n";
    }
    else
    {   
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "An acid arrow hits your " + hitloc_desc 
                + ", mildly irritating it.\n";
            watcher_message = "An acid arrow hits " + QTNAME(target) +
                " in the " + hitloc_desc +  ", mildly irritating it.\n";
            break;
            
        case 1..10:
            target_message = "An acid arrow hits your " + hitloc_desc 
                + " causing a mild stinging sensation.\n";
            watcher_message = "An acid arrow hits " + QTNAME(target) +
                " in the " + hitloc_desc +  ", causing a mild " +
                "stinging sensation.\n";
            break;
            
        case 11..30:
            target_message = "An arrow of acid explodes in to you, "
                + "blistering your " + hitloc_desc + " painfully.\n";
            watcher_message = "An arrow of acid explodes in to " + 
                QTNAME(target) + ", blistering " +target->query_possessive()+
                " " + hitloc_desc + " painfully.\n";

            break;
            
        case 31..60:
            target_message = "A caustic acid arrow explodes into you, " +
                " causing painful burns and blackening your " 
                +hitloc_desc+ ".\n";
            watcher_message = "A caustic acid arrow explodes into "+ 
                QTNAME(target)+ ", causing painful burns and blackening " +
                target->query_possessive()+ " " +hitloc_desc+ ".\n";
            break;
            
        default:
            target_message = "A seething arrow of acid explodes in to you, " +
               " fatally burning away flesh and tissue from your " 
               +hitloc_desc+ " and dissolving your bones!\n";

            watcher_message = "A seething arrow of acid explodes in to "
                + QTNAME(target) + ", fatally burning away flesh and " +
                "tissue from " +target->query_possessive()+
                " " +hitloc_desc+ " and dissolving " 
                +target->query_possessive()+ " bones!\n"; 
            break;            
        }
    }
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
}

public void
acid_arrow_desc_damage(object caster, object target, mixed * result)
{
    string caster_message, target_message, watcher_message;
    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    int phurt = result[0];
    string hitloc_desc = result[1];

    arrow_desc_damage(caster, target, phurt, hitloc_desc);
  
}

