
/* File name: precision.h
 *
 * Elven Archers special, increasing their accuracy but making them
 * shoot slower.
 *
 * The file is included in the guild soul.
 *
 * Blizzard
 */
 
public int             query_precision();

static private int     precision_alarm = 0;

public void
reset_precision(object archer)
{
    archer->catch_msg("You are ready to improve your accuracy again.\n");
    precision_alarm = 0;
}

public int
precision(string str)
{
    object precision_object, archer = TP;
    int    precision_skill;
    
    precision_skill = archer->query_skill(SS_IMPROVED_AIM);

 /* The command will work only if the player has gained this ability.
  * Otherwise there is no hint about it.
  */
    if ( !precision_skill )
    {
        notify_fail("What?\n");
        return 0;
    }

    if ( strlen(str) )
    {
        notify_fail("Just 'precision' would be enough.\n");
        return 0;
    }
    
    if ( !archer->query_attack() && !query_aiming() )
    {
        notify_fail("Calm down, you are not in combat with anyone.\n");
        return 0;
    }
    
    if ( query_precision() )
    {
        notify_fail("Patience, you are doing your best.\n");
        return 0;
    }
       
    if ( archer->query_prop(LIVE_I_STUNNED) )
    {
        notify_fail("You are too stunned, you can't focus your senses.\n");
        return 0;
    }
    
    precision_object = present("_archer_precision_object_", archer);
    
    if ( precision_object )
    {
        notify_fail("Patience, you are doing your best.\n");
        return 0;
    }
    
    setuid();
    seteuid(getuid());
    
    precision_object = clone_object(GUILD_OBJ + "precision_object");
    precision_object->move(archer, 1);
    
    precision_alarm = set_alarm(35.0, 0.0, &reset_precision(archer));
    
    return 1;
}

public int
query_precision()
{
    return !!precision_alarm;
}

