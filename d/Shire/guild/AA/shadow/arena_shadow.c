inherit "/std/shadow";

public status
inside_arena()
{
    return 1;
} /* inside_arena */

public status
enter_arena()
{
    return 1;
} /* inside_arena */

public status
leave_arena()
{
    return 1;
} /* inside_arena */

/*
 * Function name:   do_die
 * Description:     Called from enemy combat object when it thinks we died.
 * Arguments:       object killer: The enemy that caused our death.
 */
public void
do_die(object killer)
{
    object *enemies;
    
    if (shadow_who->query_hp() > 0)
        return;
        
    enemies = shadow_who->query_enemy(-1) & all_inventory(environment(shadow_who));
    foreach(object enemy: enemies)
    {
        enemy->stop_fight(shadow_who);
        shadow_who->stop_fight(enemy);
    }
    shadow_who->set_hp(1);
} /* do_die */

void
add_panic(int panic)
{
} /* add_panic */

void
run_away()
{
} /* run_away */
