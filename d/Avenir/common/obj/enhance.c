/*
 * Object that allows you to set extra skills in a player
 * for a short while.
 *
 * Just clone the object and call in it:
 * skill_enhance(who, skillnum, enhancement, 
 *               duration, enter_msg, leave_msg, 
 *               max_skill_enhance = 85)
 * 
 * Example usage:
 *    clone_object("skill_extra")->skill_ehance(this_player(),
 *             SS_DEFENCE, 5, 160, "You feel better able to defend yourself.\n",
 *             "You feel less able to defend yourself.\n", 50);
 *
 *     Cirion, July 4th, 1997
 */
#pragma strict_types

inherit "/std/object";
#include "/d/Avenir/common/common.h"

static int     enhanced_skill, skill_enhanced_amount, prop_enhanced_amount, skill_enhance_enabled, prop_enhance_enabled;
static string  skill_time_out_msg, prop_time_out_msg, sk_desc, enhanced_prop;

nomask void
create_object()
{
    set_name("skill_enchance");
    set_short("skill enhancement");

    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    add_prop(OBJ_M_NO_DROP, "Drop what?\n");

    set_no_show();

}

varargs int
skill_enhance(object who, int skillnum, int enhancement, 
              int duration, string enter_msg = "", string leave_msg = "", 
              int max_skill_enhance = 85)
{
    int extra_skill, diff;
    mixed info;

    info = SS_SKILL_DESC[skillnum];
    if(sizeof(info))
        sk_desc = info[0];
    else
        sk_desc = "something";

    if(!objectp(who) || !living(who))
        return 0;

    if(max_skill_enhance > 100)
        max_skill_enhance = 100;

    /* Get the value of any other extra skill effects the player
     * might be under the effect of.
     */
    extra_skill = who->query_skill_extra(skillnum);

    /* Now add our enhancement to the old extra skill value. The
     * result will be the new value we set the extra skill to.
     */
    extra_skill += enhancement;    

    
    /* no change will be made to the skill, so
     * no enhancement will be made.
     */
    if(!extra_skill)
    {
        set_alarm(0.0, 0.0, remove_object);
        return 0;
    }

    skill_time_out_msg = leave_msg;
    enhanced_skill = skillnum;
    skill_enhanced_amount = enhancement;

    set_short(sk_desc + " skill enhancement [" + skill_enhanced_amount + "]");

    if(environment(this_object()) != who)
    {
        if(move(who)) // yikes! move error!
        {
            set_alarm(0.0, 0.0, remove_object);
            return 0;
        }
    }

    skill_enhance_enabled = 1;
    who->set_skill_extra(skillnum, extra_skill);

    if(!strlen(enter_msg))
        enter_msg = "You feel your " + sk_desc + " skill "
            + (enhancement > 0 ? "improve" : "degrade") + ".\n";

    if(strlen(enter_msg))
        who->catch_msg(enter_msg);

    set_alarm(itof(duration), 0.0, remove_object);

    return 1;
}


varargs int
prop_enhance(object who, string prop, int enhancement, 
              int duration, string enter_msg, string leave_msg, 
              int max_prop_enhance = 85)
{
    int extra_prop, diff, oldprop;
    mixed info;

    if(!objectp(who) || !living(who))
        return 0;

    /* We can only adjust props that are set to ints! */
    if(!intp(who->query_prop(prop)))
        return 0;

    oldprop = who->query_prop(prop);

    extra_prop = oldprop + enhancement;

    prop_time_out_msg = leave_msg;
    enhanced_prop = prop;
    prop_enhanced_amount = enhancement;

    set_short(prop + " enhancement [" + prop_enhanced_amount + "]");

    if(environment(this_object()) != who)
    {
        if(move(who)) // yikes! move error!
        {
            set_alarm(0.0, 0.0, remove_object);
            return 0;
        }
    }

    prop_enhance_enabled = 1;
    who->add_prop(prop, extra_prop);

    if(strlen(enter_msg))
        who->catch_msg(enter_msg);

    set_alarm(itof(duration), 0.0, remove_object);

    return 1;
}

void
leave_env(object to, object from)
{
    int       newskill;
    object    who;

    ::leave_env(to, from);

    who = environment(this_object());

    if(objectp(who) && living(who))
    {
        if(prop_enhance_enabled)
        {
            who->add_prop(enhanced_prop, who->query_prop(enhanced_prop) - prop_enhanced_amount);

            if(stringp(prop_time_out_msg) && strlen(prop_time_out_msg))
                who->catch_msg(prop_time_out_msg);
        }

        if(skill_enhance_enabled)
        {
            newskill = who->query_skill_extra(enhanced_skill) - skill_enhanced_amount;

            who->set_skill_extra(enhanced_skill, newskill);
 
            if(!strlen(skill_time_out_msg))
                skill_time_out_msg = "You your " + sk_desc + " skill "
                + (skill_enhanced_amount < 0 ? "improves" : "degrades") + " again.\n";

            if(stringp(skill_time_out_msg) && strlen(skill_time_out_msg))
                who->catch_msg(skill_time_out_msg);
        }
    }

}
