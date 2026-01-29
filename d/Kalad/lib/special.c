/*
    /d/Kalad/lib/special.c
   
    A general file that has standard functions for npcs
    that have a special. Uses normal combat routines and hence
    takes into account:
        * weapon class hit/pen of the special,
        * parry/defence, blindfighting skill,
        * encumberance, stats difference,
        * armours of the enemy.

    Minimum number of things to setup your special:
        * Call set_default_special
        * mask special_did_hit
   
    Fysix@Genesis, Jan 1998
 */
#pragma save_binary
#pragma strict_types

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

#define DEBUG(x)  find_player("fysix")->catch_tell(x + "\n")

// Global variables with some default setup
static int  Special_chance    = 10,
            Special_dt        = W_BLUDGEON,
            Special_wchit     = 10,
            Special_wcpen     = 10,
            Special_hitloc_id = A_BODY;

// --- Set and query functions ----------------------------------------

/* Function name: set_special_chance
 * Description:   Set the chance of the special to succeed.
 * Arguments:     int 0-100
 */
public void
set_special_chance(int i)
{
    if (i >= 0 && i <= 100)
        Special_chance = i;
}

/* Function name: query_special_chance
 * Description:   What's the chance of the special to succeed.
 * Returns:       int 0-100
 */
public int
query_special_chance()
{
    return Special_chance;
}

/* Function name: set_special_dt
 * Description:   
 * Arguments:     
 */
public void
set_special_dt(int x)
{
    Special_dt = x & (W_BLUDGEON | W_IMPALE | W_SLASH);
}

/* Function name: query_special_dt
 * Description:   
 * Returns:       
 */
public int
query_special_dt()
{
    return Special_dt;
}

/* Function name: set_special_wchit
 * Description:   
 * Arguments:     
 */
public void
set_special_wchit(int x)
{
    Special_wchit = x;
}

/* Function name: query_special_wchit
 * Description:   
 * Returns:       
 */
public int
query_special_wchit()
{
    return Special_wchit;
}

/* Function name: set_special_wcpen
 * Description:   
 * Arguments:     
 */
public void
set_special_wcpen(int x)
{
    Special_wcpen = x;
}

/* Function name: query_special_wcpen
 * Description:   
 * Returns:       
 */
public int
query_special_wcpen()
{
    return Special_wcpen;
}

/* Function name: 
 * Description:   
 * Arguments:     
 */
public void
set_special_hitloc_id(int x)
{
    Special_hitloc_id = x;
}

/* Function name: query_special_hitloc_id
 * Description:   
 * Returns:       
 */
public int
query_special_hitloc_id()
{
    return Special_hitloc_id;
}

/* Function name: set_default_special
 * Description:   Use this to setup your special
 * Arguments:     int chance,
 *                int damage_type
 *                int weapon class hit
 *                int weapon class penetration
 *                int hitloc_id, give invalid hitloc_id like -1
 *                               for random hitloc
 */
public void
set_default_special(int chance, int dt, int wchit, int wcpen, int hitloc_id)
{
    set_special_chance(chance);
    set_special_dt(dt);
    set_special_wchit(wchit);
    set_special_wcpen(wcpen);
    set_special_hitloc_id(hitloc_id);
}

// --- Hooks ----------------------------------------------------------

/* Function name: special_death_hook
 * Description:   Redefine this hook if you want to give a message
 *                when an npc dies because of the special.
 * Arguments:     object enemy
 */
public void
special_death_hook(object enemy)
{
}

// --- Here all the action takes place --------------------------------

/* Function name: special_tohit_enemy
 * Description:   Decide if we hit the enemy, should depend on
 *                wchit and skill/stat differences me/victim.
 *                Calls cb_tohit in our combat object.
 * Arguments:     object enemy,
 *                int weapon class hit
 * Returns:       int 1 if we hit, otherwise a negative number
 *                indicating how much we fail.
 */
public int
special_tohit_enemy(object enemy, int wchit)
{
    // attack_id argument in /std/combat/cbase.c is not used
    return this_object()->query_combat_object()->cb_tohit(-1, wchit, enemy);
}

/* Function name: special_hit_enemy
 * Description:   Hit the enemy.
 * Arguments:     object enemy
 *                int weapon class penetration
 *                int damage type
 *                int hitloc_id
 * Returns:       mixed result of enemy->hit_me
 */
public mixed
special_hit_enemy(object enemy, int pen, int dt, int hitloc_id)
{
    // arguments: penetration, damage type,
    //    attacker, attack id (special attack), hitloc id
    return enemy->hit_me(pen, dt, this_object(), -1, hitloc_id);
}

/* Function name: special_did_hit
 * Description:   Give some cool messages for the special attack.
 *                Stripped version of did_hit.
 * Arguments:     object   enemy
 *                string   hitlocation description
 *                int      hitlocation id
 *                int      % hurt
 *                int      damage type
 *                int      damage
 */
public void
special_did_hit(object enemy, string hdesc, int hitloc_id, int phurt, 
    int damage_type, int damage)
{
}

/* Function name: execute_special_attack
 * Description:   Executes a special attack.
 * Arguments:     object enemy,
 *                int wchit, weapon class hit of the special
 *                int wcpen, weapon class penetration of the special
 *                int damage type,
 *                int hitloc_id of the enemy
 */
public void
execute_special_attack(object enemy, int wchit, int wcpen,
    int damage_type, int hitloc_id)
{
    int   hitsuc;
    mixed *hitresult;

    // See if we hit the enemy
    hitsuc = special_tohit_enemy(enemy, wchit);

    // Do some damage depending on hitsuc   
    hitresult = (mixed*) (hitsuc < 0 ?
        special_hit_enemy(enemy, hitsuc, 0,           hitloc_id) :
        special_hit_enemy(enemy, wcpen,  damage_type, hitloc_id));

//DEBUG("Hitsuc: " + hitsuc + "\t%hurt: " + hitresult[0] +
//   "\tdamage: " + hitresult[3]);
   
    // Give messages if not linkdead, ghost etc
    if (pointerp(hitresult) && hitresult[1])
        special_did_hit(enemy, hitresult[1], hitloc_id, hitresult[0], 
            damage_type, hitresult[3]);
}

/* Function name: do_special_attack
 * Description:   Fill your code for the special here.
 *                Called by special_attack depending on query_special_chance.
 *                The special attack is executed here.
 *                Doesn't have to take care of do_die in the enemy.
 * Arguments:     object enemy
 */
public void
do_special_attack(object enemy)
{
    int *dbits, dt;

    // Pick a random damage type
    dt = query_special_dt();
    dbits = ({dt & W_IMPALE, dt & W_SLASH, dt & W_BLUDGEON }) - ({0});
    dt = dbits[random(sizeof(dbits))];

    execute_special_attack(enemy, query_special_wchit(),
        query_special_wcpen(), dt,
        query_special_hitloc_id());
}

/* Function name: special_attack
 * Description:   Do a special attack in query_chance % of the
 *                combat rounds. Let's the enemy die if he has
 *                no hp left and calls death_hook.
 * Returns:       (int) 1 if special attack is executed
 *                      0 if normal combat should continue 
 */
public int
special_attack(object enemy)
{
    if (random(100) <= Special_chance)
    {
        do_special_attack(enemy);
      
        if (enemy->query_hp() <= 0)
        {
            special_death_hook(enemy);
            enemy->do_die(this_object());
        }
        return 1;
    }

    return 0;
}
