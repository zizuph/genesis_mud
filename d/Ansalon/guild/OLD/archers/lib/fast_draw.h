
/* File name: fast_draw
 *
 * Elven Archers special. It increases their speed, but lowers the
 * accuracy.
 *
 * The file is included in the guild soul.
 *
 * Blizzard
 */
 
public int             query_fast_draw();

static private int     fast_draw_alarm = 0;

public void
reset_fast_draw(object archer)
{
    archer->catch_msg("You are able to accelerate your shooting again.\n");
    fast_draw_alarm = 0;
}

public int
fast_draw(string str)
{
    object fast_draw_object, archer = TP;
    int    fast_draw_skill;
    
    fast_draw_skill = archer->query_skill(SS_FAST_DRAW);

 /* The command will work only if the player has gained this ability.
  * Otherwise there is no hint about it.
  */
    if ( !fast_draw_skill )
    {
        notify_fail("What?\n");
        return 0;
    }

    if ( str != "draw" )
    {
        notify_fail("Fast what? Fast draw?\n");
        return 0;
    }
    
    if ( !archer->query_attack() && !query_aiming() )
    {
        notify_fail("You are not in combat with anyone, so there is no " +
            "point to waste your energy.\n");
        return 0;
    }
    
    if ( query_fast_draw() )
    {
        notify_fail("Patience, you are doing your best.\n");
        return 0;
    }
       
    if ( archer->query_prop(LIVE_I_ATTACK_DELAY) || 
        archer->query_prop(LIVE_I_STUNNED) )
    {
        notify_fail("You are too stunned to draw your bow.\n");
        return 0;
    }
    
    if ( archer->query_fatigue() < (archer->query_stat(SS_CON) / 7) )
    {
        notify_fail("You are too weary to do that.\n");
        return 0;
    }
     
    fast_draw_object = present("_archer_fast_draw_object_", archer);
    
    if ( fast_draw_object )
    {
        notify_fail("Patience, you are doing your best.\n");
        return 0;
    }
    
    setuid();
    seteuid(getuid());
    
    fast_draw_object = clone_object(GUILD_OBJ + "fast_draw_object");
    fast_draw_object->move(archer, 1);
    
    fast_draw_alarm = set_alarm(40.0, 0.0, &reset_fast_draw(archer));
    
    return 1;
}

public int
query_fast_draw()
{
    return !!fast_draw_alarm;
}

  