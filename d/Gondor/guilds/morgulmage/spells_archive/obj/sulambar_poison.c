/*
 * /d/Gondor/guilds/morgulmage/spells/obj/sulambar_poison.c
 * Powerful stat reducing poison
 * Olorin, 26-jul-1994
 *
 * Modification log:
 * add_tmp_stat() sets up an alarm. The limit of alarms per object
 * introduced by the gd is 16. I therefore had to increase
 * the strength of the poison while increasing the interval time.
 * Olorin, 18-dec-1996
 *
 * Recoded to not use add_tmp_stat(), as the amount of set_alarm()'s
 * used can cause major bugs.  Practically completely rewritten,
 * with appreciated help from Shiva.  Change in the effects are slight,
 * if any.  Victim of 100 stats is completely newbified in about
 * 4.5 minutes.  Of course, if they continue to stand in the
 * cloud they will take on more poisons like always, and
 * will newbify in less time.  Fixes bug that allowed player
 * to log out and regain their stats.
 * Poison used to start cutting down stats very quickly (stat/4)
 * and then slow down as the player lost stats.  Poison now takes
 * off a set amount, so will seem to players to take longer to
 * take full effect.  Stats are also restored instantly
 * when poison wears off, rather than when the add_tmp_stat
 * expires (30 seconds after the original poison did).
 * So, in effect, the spell is weaker, but mortals shouldn't 
 * notice much.
 * Morbeche, Feb 08 2000
 *
 * Poison counters are traced separately for STR, CON and DEX
 * Chmee, 10.06.2002
 *
 * Changed fatigue drain to stuffed drain per Goldberry's orders.
 * Also added a very small amount of mana drain.
 * Gwyneth, 11/16/02
 *
 * Modified to avoid adding endless poison alarms.
 * Chmee, 24.09.2003
 *
 * Fixed bug that let players exploit the poison to get
 * huge stat bonuses.
 * Cotillion, 03-10-2005
 *
 * Moved to the new guild directory
 * Eowul, 03-14-2010
 */
 
inherit "/std/poison_effect";

#include <poison_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

#include "../../morgulmage.h"

inherit "/d/Genesis/specials/resist";

#define STAT_DROP 15

#define pc_STR 0
#define pc_CON 1
#define pc_DEX 2

/* Damage this victim has received. */
public int *poison_count = ({ 0, 0, 0 });
/* The old 'Dose' variable is sizeof(_time_stamps) + 1 by definition. */
float *_time_stamps = ({});

int increase_dose( int vpd_time, int vpd_str );
void special_damage_loop( int damage );

void
create_poison_effect()
{
    set_name(MORGUL_ID_SULAMBAR_POISON);
    set_interval( 45 );
    set_poison_type( "Morgul_Sulambar_Poison" );
    set_damage( ({ POISON_FATIGUE,  50, POISON_USER_DEF, 1 }) );
    set_silent( 2 );
}

/*
 * The poison recover string.
 */
public string query_poison_recover()
{
    return implode(map(_time_stamps, ftoa), ",") + "&pc&" +
        poison_count[pc_STR] + " " + poison_count[pc_CON] + " " +
        poison_count[pc_DEX];
}

public void init_poison_recover( string arg  = "")
{
    string str;
    float dtemp;
    string *words;
    
    if (sscanf( arg, "%s&pc&%d %d %d", arg, poison_count[pc_STR],
        poison_count[pc_CON], poison_count[pc_DEX] ) == 4)
    {
        words = explode(arg, ",");
        foreach(string word: words)
        {
            sscanf( word, "%f", dtemp);
            _time_stamps += ({ dtemp });
        }
    }
}

public varargs void
start_poison(object poisoner)
{
    ::start_poison(poisoner);

    if (recovery)
    {
        poisonee->set_stat_extra( SS_STR, poisonee->query_stat_extra( SS_STR )-
            poison_count[pc_STR]* STAT_DROP );
        poisonee->set_stat_extra( SS_CON, poisonee->query_stat_extra( SS_CON )-
            poison_count[pc_CON]* STAT_DROP );
        poisonee->set_stat_extra( SS_DEX, poisonee->query_stat_extra( SS_DEX )-
            poison_count[pc_DEX]* STAT_DROP );
    }
}

void special_damage( int damage )
{
    int index;

    for (index = 0; index < sizeof(_time_stamps); index++)
    {
        special_damage_loop( damage );
    }
}

void special_damage_loop( int damage )
{
 int i, j=0, res, fat;

     res = spell_resist_poison( this_object(), poisonee, SS_ELEMENT_AIR,
        TASK_DIFFICULT );
    if (random( 100 ) < res)
    {
        return;
    }

   if (poisonee->query_stat( SS_STR ) < 19)
    {
        j++;
    }
    else
    {
        poisonee->set_stat_extra( SS_STR, (poisonee->query_stat_extra(
            SS_STR )- STAT_DROP ));
        poison_count[pc_STR]++;
    }
    if (poisonee->query_stat( SS_CON ) < 19)
    {
        j++;
    }
    else
    {
        poisonee->set_stat_extra( SS_CON, (poisonee->query_stat_extra(
            SS_CON )- STAT_DROP ));
        poison_count[pc_CON]++;
    }    
    if (poisonee->query_stat( SS_DEX ) < 19)
    {
        j++;
    }
    else
    {
        poisonee->set_stat_extra( SS_DEX, (poisonee->query_stat_extra(
            SS_DEX )- STAT_DROP ));
        poison_count[pc_DEX]++;
    }

    for (i=0;i<j;i++)
    {
        fat = random( 1000 );
        fat += 70;
        fat = (poisonee->query_stuffed() < fat ? 
               poisonee->query_stuffed() : fat);
        fat *= -1;
        poisonee->eat_food( fat );
        poisonee->add_mana( -( random(50) ) );
        return;
    }
}

int increase_dose( int vpd_time, int vpd_str )
{
    int count = sizeof(_time_stamps);
    float delta = itof( vpd_time )- get_alarm( a_time )[2];

    if ( delta >= 1.0 )
    {
        /* strength is a global variable declared in poison_effect and set
         * by set_strength() */
        if (vpd_str != strength)
        {
            set_strength( (strength * count + vpd_str) / (count + 1) );
        }
        _time_stamps += ({ delta });
    }
    return sizeof(_time_stamps);
}

/*
 * Function name: timeout
 * Description  : This is called when the poison duration has expired.
 *                It simply removes itself.
 */
public void timeout()
{
    if (sizeof( _time_stamps ))
    {
        p_time = _time_stamps[0];
        _time_stamps = _time_stamps[1..];
        a_time = set_alarm( p_time, 0.0, timeout );
        if (silent < 2)
        {
            tell_object( poisonee, "You feel somewhat better.\n");
        }
        return;
    }

    if (silent < 2)
    {
        tell_object(poisonee, "You feel much better.\n");
    }

    remove_alarm(a_dam);
    remove_object();
}

/*
 * Note, that the victim doesn't regain the health instantly. This is
 * a planned effect, not a bug.
 */
public void remove_object()
{
    poisonee->set_stat_extra( SS_STR, poisonee->query_stat_extra( SS_STR )+
        poison_count[pc_STR]* STAT_DROP );
    poisonee->set_stat_extra( SS_CON, poisonee->query_stat_extra( SS_CON )+
        poison_count[pc_CON]* STAT_DROP );
    poisonee->set_stat_extra( SS_DEX, poisonee->query_stat_extra( SS_DEX )+
        poison_count[pc_DEX]* STAT_DROP );

    ::remove_object();
}

public string stat_object()
{
    return "SULAMBAR_POISON has taken off "+
        (poison_count[pc_STR]* STAT_DROP ) + " points from str, " +
        (poison_count[pc_CON]* STAT_DROP ) + " from con and " +
        (poison_count[pc_DEX]* STAT_DROP ) + " from dex.\n" +
        "Current dose: "+ sizeof(_time_stamps) + "\n";

    ::stat_object();
}
