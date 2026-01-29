/*
 * Prismatic Spray Descriptions
 *
 * This file is included in the Prismatic Spray Spell
 *
 * Created by Arman, Feb 2016
 */
 

public void
prismatic_spray_desc_cast(object caster, object target)
{
    string caster_message, target_message, watcher_message;
    
        caster_message = "You point a crooked finger towards " + QTNAME(target) + ".\n";
        target_message = QCTNAME(caster) + " points a crooked finger towards you.\n";
        watcher_message = QCTNAME(caster) + " points a crooked finger towards " + QTNAME(target) + 
            ".\n";
    
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, target, ({ caster, target }));    
}

public void
spray_desc_damage(object caster, object target, int phurt, string hitloc_desc)
{
    string target_message, watcher_message;
    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "A beam of multicoloured light sprays harmlessly past you.\n";
        watcher_message = "A beam of multicoloured light sprays harmlessly past " + 
            QTNAME(target) + ".\n";
    }
    else
    {   
        switch (phurt) // percentage hurt
        {
        case 0..10:
            target_message = "A beam of multicoloured light deflects off your " + 
               hitloc_desc+ ", causing tingling pain.\n";
            watcher_message = "A beam of multicoloured light deflects off " + 
                QTPNAME(target) + " " + hitloc_desc +  ", causing " + 
                target->query_objective()+ " tingling pain.\n";
            break;
            
        case 11..30:
            target_message = "A beam of multicoloured light hits your " + hitloc_desc 
                + ", causing numbing pain.\n";
            watcher_message = "A beam of multicoloured light hits " + QTNAME(target) +
                " in the " + hitloc_desc +  ", causing numbing pain.\n";
            break;
            
        case 31..60:
            target_message = "A prismatic beam of light smashes in to you, "
                + "radiating pain through your " + hitloc_desc + ".\n";
            watcher_message = "A prismatic beam of light smashes in to " + 
                QTNAME(target) + " radiating pain through " +target->query_possessive()+
                " " + hitloc_desc + ".\n";

            break;
            
        case 61..80:
            target_message = "A prismatic beam of light explodes in to you in a " +
                "kaleidoscope of colours, causing excrutiating pain throughout " +
                "your body.\n"; 
            watcher_message = "A prismatic beam of light explodes in to "+ QTNAME(target)+
                " in a kaleidoscope of colours, causing excrutiating pain throughout " 
                +target->query_possessive()+ " body.\n";
            break;
            
        default:
            target_message = "A prismatic beam of light explodes in to you, " +
               " fatally overloading your senses with radiating pain!\n";

            watcher_message = "A prismatic beam of light explodes in to "
                + QTNAME(target) + ", fatally overloading " +target->query_possessive()+
                " senses with radiating pain!\n"; 
            break;            
        }
    }
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
}

public void
prismatic_spray_desc_damage(object caster, object target, mixed * result)
{
    string caster_message, target_message, watcher_message;
    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    int phurt = result[0];
    string hitloc_desc = result[1];

    spray_desc_damage(caster, target, phurt, hitloc_desc);
  
}

