/*
 * Pscourge Descriptions
 *
 * This file is included in the Pscourge Spell
 *
 * Created by Arman, April 2016
 */

public void
pscourge_desc_cast(object caster, object target)
{
    object *clubs = FILTER_CLUBS(caster);
    string weaps = COMPOSITE_WORDS(clubs->short());
    
    caster->catch_msg("You swing your " + weaps + " in a mighty arc "+
	"towards "+ QTNAME(target) +", calling on the Queen of Darkness "+
	"to strike "+ HIM(target) +" down.\n");

    caster->tell_watcher(QCTNAME(caster) + " swings " + HIS(caster) +" "+
	weaps + " in a mighty arc towards " + QTNAME(target) +
	", calling on the Queen of Darkness to strike " +
	HIM(target) + " down.\n", target, ({ caster, target }));

    target->catch_msg(QCTNAME(caster) + " swings " + HIS(caster) +" "+
	weaps + " in a mighty arc towards you, calling on " +
	"the Queen of Darkness to strike you down.\n");
}

public void
scourge_desc_damage(object caster, object target, int phurt, string hitloc_desc)
{
    string target_message, watcher_message;

    if (phurt < 0)
    {
        // Missed! give the miss messages.
        target_message = "You are not affected by the unholy strike.\n";
        watcher_message = QCTNAME(target) + " is not affected by "+
	    "the unholy strike.\n";
    }
    else
    {   
        switch (phurt) // percentage hurt
        {
        case 0:
            target_message = "You are mildly irritated by the unholy "+
		"strike to your " + hitloc_desc + ".\n";
            watcher_message = QCTNAME(target) +" is mildly irritated "+
		"by the unholy strike to " + HIS(target) +" "+ hitloc_desc +".\n";
            break;
            
        case 1..10:
            target_message = "You are discomforted by the unholy strike "+
		"to your " + hitloc_desc + ".\n";
            watcher_message = QCTNAME(target) +" is discomforted by the "+
		"unholy strike to "+ HIS(target) +" "+ hitloc_desc +".\n";
            break;
            
        case 11..30:
            target_message = "You are lashed painfully by the unholy "+
		"strike to your " + hitloc_desc + ".\n";
            watcher_message = QCTNAME(target) +" is lashed painfully by the "+
		"unholy strike to " + HIS(target) +" "+ hitloc_desc +".\n";

            break;
            
        case 31..60:
            target_message = "You are agonizingly scourged by the unholy "+
		"strike to your "+ hitloc_desc +".\n";
            watcher_message = QCTNAME(target) +" is agonizingly scourged by "+
		"the unholy strike to "+ HIS(target) +" "+ hitloc_desc +".\n";
            break;
            
        default:
            target_message = "The unholy attention of the Queen of Darkness "+
		"scourges your "+ hitloc_desc +" mercilessly, causing "+
		"devastating injuries.\n";
            watcher_message = "The unholy attention of the Queen of Darkness "+
		"scourges "+ QTPNAME(target) +" "+ hitloc_desc +
		" mercilessly, causing devastating injuries.\n";
            break;            
        }
    }
        
    caster->catch_msg(watcher_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));
    target->catch_msg(target_message);
}

public void
pscourge_desc_damage(object caster, object target, mixed * result)
{
    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    int phurt = result[0];
    string hitloc_desc = result[1];

    scourge_desc_damage(caster, target, phurt, hitloc_desc);
}

