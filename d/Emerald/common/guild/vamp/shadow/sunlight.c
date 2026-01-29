/* sunlight.c created by Shiva@Genesis.
 *
 * This file contains code related to the effects of light
 * on a vampire
 *
 * This is a subpart of the vampire guild shadow
 */

#include "../guild.h"
#include "../voptions.h"
#include "/d/Emerald/sys/domain.h"
#include <macros.h>
#include <stdproperties.h>

#define SW shadow_who

static mixed *rooms_entered;
static int    registered,
              rooms,
              total_light_levels,
              resistance = SUNLIGHT_DAMAGE(1);

/* 
 * Function name: sunlight_res
 * Description:   Get this vampire's resistance to sunlight damage
 * Returns:       The vampire's sunlight resistance.
 */
int
sunlight_res()
{
    return resistance + MIN(250, query_vamp_stat() * 3 / 2);
}

/*
 * Function name: add_sunlight_resistance
 * Description:   Give the vampire additional resistance to sunlight
 * Arguments:     int i - the amount of resistance
 */
void
add_sunlight_resistance(int i)
{
    resistance += i;
}

/*
 * Function name: query_sunlight_level
 * Description:   Give the amount of sunlight in a room
 * Arguments:     object where - The room to check.  If not specified,
 *                               the environment of this vampire is used.
 * Returns:       The sunlight in the given room.
 */
varargs int
query_sunlight_level(object where)
{
    int sun = 0;
    int base_light, light;

    if (!where)
    {
        where = environment(SW);
    }

    light = QP(where, OBJ_I_LIGHT);

    if (light < 1)
    {
        return 0;
    }

    base_light = QP(where, ROOM_I_LIGHT);
  
    if (member_array(ROOM_I_SUNLIGHT, where->query_props()) >= 0)
    {
        sun = QP(where, ROOM_I_SUNLIGHT);
    }
    else if (!QP(where, ROOM_I_INSIDE))
    {
        sun = base_light;
    }
  
    if (base_light > light)
    {
        if (base_light < 1)
        { 
            return 0;
        }

        sun = sun * 100 * light / base_light / 100;
    }

    return MAX(0, sun);
}

/*
 * Function name: query_sunlight_modifier
 * Description:   Returns a value to be applied as a penalty to 
 *                tasks performed by a vampire because of the 
 *                current light level in his/her environment.
 * Returns:       The modifier
 */
int
query_sunlight_modifier()
{
    int sunlight_minus;
  
    if (sunlight_minus = query_sunlight_level())
    {
        sunlight_minus = ++sunlight_minus * 4 + 20;
        sunlight_minus -= query_vamp_stat() / 5;
    
        /* regardless of his/her level, a vampire always has at least
         * a small penalty while in sunlight
         */
        sunlight_minus = MAX(10, sunlight_minus);
    }
  
    return sunlight_minus;
}

/* 
 * Function name: unregister
 * Description:   Cancel this vampire's registration with the sun object
 */
void
unregister()
{
    registered = 0;
  
    setuid();
    seteuid(getuid());
  
    SUN->unregister(SW);
  
    total_light_levels = 0;
    rooms = 0;
}

static varargs void
check_sunlight(object env, object from)
{
    int li = query_sunlight_level();
    int damage, i;
    object meld_cont;

    if (!env)
    {
        env = environment(SW);
    }

    if (!from)
    {
        from = SW->query_prop(LIVE_O_LAST_ROOM);
    }

    // Decide if we are going to be damaged from sunlight
    if (((env->query_domain() != DOMAIN_NAME) ||
        !SW->query_prop(VAMP_I_VS_POWER)) && 
        !QP(env, ROOM_I_INSIDE) &&
        ((damage = SUNLIGHT_DAMAGE(li) - sunlight_res()) > 0))
    {
        /* If the room is so bright that we would die w/in
         * 12 seconds then try to force an earthmeld
         */
        if (query_vamp_option(VOPT_AUTOMELD) &&
            from && (MASTER_OB(from) != MELD_CONT) &&
            (SW->query_hp() <= (SUNLIGHT_DAMAGE(li)) *
            (12 / ftoi(SUNLIGHT_DAMAGE_INTERVAL))) &&
            (meld_cont = clone_object(MELD_CONT)))
        {
            SW->catch_msg("\nThe sun's scorching rays consume your " +
                "senses with burning agony.\nInstinctively, you " +
                "attempt to seek refuge within the earth.\n\n");

            set_alarm(2.0, 0.0, &meld_cont->earthmeld(SW));
        }
    
        /* If we aren't already, register with the sunlight object,
         * which will repeatedly call sunlight_damage() in us
         */
        if (!registered)
        {
            setuid();
            seteuid(getuid());
      
            registered = 1;
            SUN->register(SW);
        }
    }
    else if (registered)
    {
        unregister();
    }
  
    if (registered)
    {
        /* Keep track of the cumulative light levels of the
         * lighted rooms through which we pass
         */
        total_light_levels += li;
    
        /* Keep track of the number of lighted rooms through which
         * we pass
         */
        rooms++;
    }
}

/*
 * Function name: enter_env
 * Description:   Called when this vampire enters a container, this
 *                function checks the sunlight value in the container,
 *                and takes the appropriate actions according to that
 *                value.
 * Arguments:     as enter_env() on /std/object.c
 */
#if 0
void
enter_env(object env, object from)
{
    SW->enter_env(env, from);

    if (interactive(SW) && !IS_WIZ(SW))
    {
    /* At this point, enter_inv() is called after enter_env() in the move()
     * routine.  This is troublesome since enter_inv() is resposible for
     * updating the new environment, meaning that light, volume, etc.
     * may not be correct at the point that enter_env() is called.  Until
     * this is changed, I'll have to use an alarm here *YUCK*
     */
#ifndef ENTER_ENV_AFTER_ENTER_INV
        set_alarm(0.0, 0.0, &check_sunlight(0, 0));
#else
        check_sunlight(env, from);
#endif
    }
}
#endif


/* 
 * Function name: sunlight_damage
 * Description:   This is called to apply damage to this vampire
 *                based upon the sunlight level in his/her environment.
 */
void
sunlight_damage()
{
    object who = SW;
    int dam;
    int li = query_sunlight_level();
    string str;
  
    /* We don't need to be taking damage if linkdead */
    if (who->query_linkdead())
    {
        unregister();
        return;
    }
  
   /* Figure damage based on the average levels of light
    * in the rooms through which we have passed.
    */
    dam = SUNLIGHT_DAMAGE(total_light_levels / rooms);
  
    total_light_levels = li;
    rooms = 1;
  
    dam -= sunlight_res();

    if (who->query_prop(OBJ_I_INVIS))
    {
        dam /= 2;
    }

    if ((dam -= sunlight_res()) > 0)
    {
        if (!random(10))
        {
            switch (dam / who->query_max_hp())
            {
                case 0..5:
                    str = "singes your exposed skin";
                    break;
                case 6..15:
                    str = "burns your skin, making every movement painful";
                    break;
                case 18..40:
                    str = "burns deep into your skin...every moment becoming " +
                        "more agonizing";
                    break;
                default:
                    str = "consumes your undead flesh, combusting your " +
                        "volatile blood and wrapping you in flames";
            }
      
            who->catch_msg("The sunlight " + str + ".\n");
        }
    
        who->heal_hp(-dam);
        who->add_fatigue(-1); 
        who->add_mana(-1);
    
        if (!random(3))
        {
            who->add_thirst(1);
        }

        if (SW->query_hp() <= 0)
        {
            if (environment(SW)->query_destroy_vampire(SW))
            {
                unregister();
                SW->vampire_death();
                return;
            }
            else if (dam > SUNLIGHT_DAMAGE(5))
            {
                unregister();
                SW->do_die(0);
                return;
            }
        }
    }
}
