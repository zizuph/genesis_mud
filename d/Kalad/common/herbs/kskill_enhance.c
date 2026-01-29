/*
 * /d/Gondor/common/herbs/skill_enhance.c
 *
 * Olorin, 1-nov-1993
 * Last mod: Olorin, 07-dec-1993
 *           added autoload feature and stat info following
 *           a suggestion by Rogon
 *           removed Gondor specific macros
 *           added logging
 *
 * changes still to be implemented:
 * - chance of failure
 *
 * checks:
 * - max skill enhance or decrease: MAX_STRENGTH = 50
 * - skills that cannot be enhanced or decreased: SS_WEP_xxxx, 
 *   SS_2H_COMBAT, SS_BLIND_COMBAT, SS_UNARM_COMBAT, SS_PARRY,
 *   SS_DEFENCE
 * - max level above which skills cannot be enhanced: 100
 * - min level below which skills cannot be decreased: 1
 * - skills can only be enhanced to twice the trained levels
 * - time of effect: strength*10 + base_skill * strength (randomized)
 * 
 * usage:
 * in create_herb(): set_effect(HERB_SPECIAL,"",0);
 * 
 * void special_effect()
 * {
 *     object  shadow;
 * 
 *     shadow = clone_object(HERB_DIR + "skill_enhance");
 *     shadow->set_enhance_effect(SS_SNEAK,"sneak",15);
 *     shadow->move(this_player(),1);
 * }
 * 
 * suggested price of the herb (if strength > 0):
 * 50 * strength + strength * strength (in cc)
 *
 * suggested id diff: > 2 * strength
 * 
 */
#pragma save_binary

inherit "/std/object";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define STRENGTH        10    /* default */
#define MAX_STRENGTH    50    /* maximum */

int     time,
        strength,
        skill,
        rem_alarm,
        enhance_flag = 0;
string  effect_msg;

/* prototypes */
nomask static void start_effect(object target);
nomask static void remove_effect();
/*
 * Function name: create_object
 * Description:
 *
 */
nomask void create_object()
{
  set_name("Skill_Enhance");
  add_prop(OBJ_I_VOLUME,0);
  add_prop(OBJ_I_WEIGHT,0);
  add_prop(OBJ_M_NO_DROP,1);
  add_prop(OBJ_M_NO_GIVE,1);
  add_prop(OBJ_M_NO_SELL,1);
  add_prop(OBJ_I_INVIS,1);
  set_no_show();
}

/*
 * Function name: void set_enhance_effect(int isk, string str, int istr)
 * Description:   set the variables for skill enhancement
 *
 * Arguments:     skill: the skill number (according to /sys/ss_types.h)
 *                str:   a string describing the skill to be enhanced
 *                i:     the strength of the effect, ie the number
 *                       of levels the skill is to be enhanced,
 *                       can also be negative.
 *                       -50 < i < 50 will be enforced.
 * Returns:       nothing
 */
nomask void set_enhance_effect(int isk, string str, int istr)
{
    skill = isk;
    strength = istr;
    effect_msg = str;

    if(istr == 0)
        strength = STRENGTH;
        
    else if(istr > MAX_STRENGTH)
        strength = MAX_STRENGTH;

    else if(istr < -MAX_STRENGTH)
        strength = -MAX_STRENGTH;

    switch(skill)
    {
        case 0..8:
        case 20..24:
            skill = -1;
            effect_msg = "";
            break;
    }
}

/*
 * Function name: void enter_env(object to, object from)
 * Description:   will start the skill enhancement
 * Arguments:     see /std/object.c
 * Returns:       nothing
 */
void enter_env(object to, object from)
{
    ::enter_env(to,from);

    if (!interactive(to)) 
    {
        remove_object();
        return;
    }
  
    if(enhance_flag)
        return;

    start_effect(to);
}

/*
 * Function name: nomask static void start_effect(object target)
 * Description:   will start the skill enhancement
 * Arguments:     none
 * Returns:       nothing
 */
nomask static void start_effect(object target)
{
    int     tp_bsk,
            tp_esk,
            tp_sk,
            max_time;

    if (!interactive(target) || target != environment(this_object())) 
    {
        remove_object();
        return;
    }
  
/* illegal skill */
    if(skill < 0)
    {
        remove_object();
        return;
    }

    tp_sk  = target->query_skill(skill);
    tp_esk = target->query_skill_extra(skill);
    tp_bsk = tp_sk - tp_esk;

/* you can only enhance an exisiting skill */
    if(tp_bsk <= 0)
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }
/* fix the duration of the enhancement */
    max_time = ABS(strength)*10 + tp_bsk * ABS(strength) * (50 + random(100)) / 100;
    if(time <= 0 || time > max_time)
        time = max_time;

/* you cannot decrease a skill to less than 1 */
    if(strength + tp_sk <= 1)
        strength = - tp_sk + 1;

/* you cannot enhance a skill to more than level 100 */
    if(strength + tp_sk > 100)
        strength = 100 - tp_sk;

/* enhance the skill */
    if(strength)
    {
        target->set_skill_extra(skill, tp_esk + strength);
        enhance_flag = 1;
        target->catch_msg("You feel your ability to "+effect_msg+
            (strength>0 ? " improve" : " deteriorate")+"!\n");
        seteuid(getuid());
    }

    rem_alarm = set_alarm(itof(time), 0.0, remove_effect);
}

/*
 * Function name: int query_time()
 * Description:   returns the time that the effect will still last
 * Arguments:     none
 * Returns:       time till the effect is removed
 */
int query_time()
{
    if (rem_alarm)
        return ftoi(get_alarm(rem_alarm)[2]);
    return 0;
}

static nomask void set_time(int i) { if(time > 0) time = i; }

/*
 * Function name: void remove_effect()
 * Description:   remove skill enhancement
 * Arguments:     none
 * Returns:       nothing
 */
void remove_effect()
{
    object  tp = environment(this_object());

    if(enhance_flag)
    {
        if(strength)
        {
            tp->set_skill_extra(skill,tp->query_skill_extra(skill) - strength);
            enhance_flag = 0;
            tp->catch_msg("You feel your ability to "+effect_msg+
                (strength<0 ? " improve" : " deteriorate")+"!\n");
        }
    }

    set_alarm(0.0, 0.0, remove_object);
}

/*
 * Function name: void leave_env(object from, object to)
 * Description:   remove effect
 * Arguments:     see /std/object.c
 * Returns:       nothing
 */
void leave_env(object from, object to)
{
    ::leave_env(from, to);
    remove_effect();
}

/*
 * Function name: query_auto_load
 * Description:   Used to reload the effect into the player if it hasn't
 *                expired when he quits.
 */
string query_auto_load()
{
    string str;

    str = MASTER + ":";
    str += "#d#" + ftoi(get_alarm(rem_alarm)[2]);
    str += "#s#" + skill;
    str += "#m#" + effect_msg;
    str += "#t#" + strength;
    str += "#";
    return str;
}

/*
 * Function name: init_arg
 * Description:   Parses the data from the saved object.
 */
void init_arg(string arg)
{
    string dummy;

    sscanf(arg, "%s#d#%d%s", dummy, time, dummy);
    sscanf(arg, "%s#s#%d%s", dummy, skill, dummy);
    sscanf(arg, "%s#m#%s#%s", dummy, effect_msg, dummy);
    sscanf(arg, "%s#t#%d%s", dummy, strength, dummy);
}

/*
 * Function name: stat_object
 * Description:   Called when wizard stats the object
 * Returns:       A string describing the object.
 */
string
stat_object()
{
    string str;

    str = ::stat_object();

    str += "Time left: " +ftoi(get_alarm(rem_alarm)[2])+ "\n";
    str += "Skill effected: " + effect_msg + " <" + skill + ">\n";
    str += "Strength:  " + strength + "\n";

    return str;
}

