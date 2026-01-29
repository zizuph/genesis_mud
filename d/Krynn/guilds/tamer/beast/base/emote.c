/* ACTION_CONTACT - This action requires the actor to be physically
 * near the target.
 */
/* ACTION_PROXIMATE - */
/* ACTION_AURAL - This action can be perceived with the sense of hearing */
/* ACTION_VISUAL - This action can be perceived with the sense of vision */
/* ACTION_OLFACTORY - This action can be perceived with the sense of smell */
/* ACTION_LACTIVITY - This action requires a low level of activity.
 * These actions can typically be performed while the actor is restrained,
 * though not while completely unable to move.
 */
 
/* ACTION_MACTIVITY - This action requires a moderate level of activity.
 * These actions can typically be performed while under minor restraint,
 * though not while more heavily restrained.
 */
/* ACTION_HACTIVITY - This action requires a high level of activity.
 * These actions require a full range of activity or perhaps can be
 * performed under minimal restraint.
 */
/* ACTION_OFFENSIVE - This action is intentionally rude or offensive */
/* ACTION_INGRATIATORY - This action is intentionally ingratiatory,
 * flattering, pleasing.
 */
/* ACTION_INTIMATE - This action is considered intimate.  This includes
 * sexual actions.
 */
/* ACTION_THREATENING - This action is considered threatening.  It is
 * intended to cause fear in the target.
 */
/* ACTION_BLIND - This action is not displayed towards those that
 * cannot see the actor.
 */

inherit "/lib/commands";

#include <cmdparse.h>
#include <adverbs.h>
#include <macros.h>

#include "defs.h"

mapping gReactLimit = ([]);

public string *
get_genus_emote(int emotion)
{
    string  genus;
    mixed  *e_list;
    
    if (!strlen(genus = this_object()->query_genus()))
        return ({});
    
    e_list = GENUS->query_genus_emotion(genus, emotion); 
    
    if (!pointerp(e_list))
        return ({});
    
    return e_list;
}

string
process_adverb(string str, string adverb)
{
    string *list;
    
    if (!sizeof(list = explode(str, " adverb")))
        return str;
    
    return implode(list, adverb);
}

public status
temote(object target, int emotion, string adverb)
{
    string *how;
    object old_tp, *targets;
    
    targets = ({ target }) - ({ 0 });
    old_tp  = this_player();
    set_this_player(this_object());
    
    switch(emotion)
    {
        case E_ADMIRATION:
        case E_TRUST:
        case E_ACCEPTANCE:
            break;
        case E_TERROR:
        case E_FEAR:
        case E_APPRENHENSION:
            break;
        case E_AMAZEMENT:
        case E_SURPRISE:
        case E_DISTRACTION:
            break;
        case E_GRIEF:
        case E_SADNESS:
        case E_PENSIVENESS:
            break;
        case E_LOATHING:
        case E_DISGUST:
        case E_BOREDOM:
            break;
        case E_RAGE:
        case E_ANGER:
        case E_ANNOYANCE:
            break;
        case E_VIGILANCE:
        case E_ANTICIPATION:
        case E_INTEREST:
            break;
        case E_ECSTASY:
        case E_JOY:
        case E_SERENITY:
            break;
        case E_LOVE:
            break;
        case E_SUBMISSION:
            break;
        case E_AWE:
            break;
        case E_DISAPPROVAL:
            break;
        case E_REMORSE:
            break;
        case E_CONTEMPT:
            break;
        case E_AGGRESSIVENESS:
            break;
        case E_OPTIMISM:
            break;
        default:
        how = parse_adverb_with_space(adverb, "cautiously", 0);
        all2actbb(" acts" + how[1] + " towards", targets, 0, how[1], 
            ACTION_OTHER);
        targetbb(" acts" + how[1] + " towards you.", targets, how[1],
            ACTION_OTHER);
            break;
    }
    set_this_player(old_tp);
    return 1;
}

public void
trigger_other(object actor, int value, int target)
{
    string  adverb;
    int     emotion;
    
    switch(value)
    {
        case -6:
        case -5:
        case -4:
        case -3:
        case -2:
        case -1:
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
    }
    
    temote(actor, emotion, adverb);
}

public void
trigger_contact(object actor, int value, int target)
{
    string  adverb;
    int     emotion;
    
    switch(value)
    {
        case -6:
        case -5:
        case -4:
        case -3:
        case -2:
        case -1:
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
    }
    
    temote(actor, emotion, adverb);
}

public void
trigger_proximate(object actor, int value, int target)
{
    string  adverb;
    int     emotion;
    
    switch(value)
    {
        case -6:
        case -5:
        case -4:
        case -3:
        case -2:
        case -1:
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
    }
    
    temote(actor, emotion, adverb);
}

public void
trigger_aural(object actor, int value, int target)
{
    string  adverb;
    int     emotion;
    
    switch(value)
    {
        case -6:
        case -5:
        case -4:
        case -3:
        case -2:
        case -1:
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
    }
    
    temote(actor, emotion, adverb);
}

public void
trigger_visual(object actor, int value, int target)
{
    string  adverb;
    int     emotion;
    
    switch(value)
    {
        case -6:
        case -5:
        case -4:
        case -3:
        case -2:
        case -1:
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
    }
    
    temote(actor, emotion, adverb);
}

public void
trigger_olfactory(object actor, int value, int target)
{
    string  adverb;
    int     emotion;
    
    switch(value)
    {
        case -6:
        case -5:
        case -4:
        case -3:
        case -2:
        case -1:
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
    }
    
    temote(actor, emotion, adverb);
}

public void
trigger_ingratiatory(object actor, int value, int target)
{
    string  adverb;
    int     emotion;
    
    switch(value)
    {
        case -6:
        case -5:
        case -4:
        case -3:
        case -2:
        case -1:
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
    }
    
    temote(actor, emotion, adverb);
}

public void
trigger_intimate(object actor, int value, int target)
{
    string  adverb;
    int     emotion;
    
    switch(value)
    {
        case -6:
        case -5:
        case -4:
        case -3:
        case -2:
        case -1:
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
    }
    
    temote(actor, emotion, adverb);
}

public void
trigger_threatening(object actor, int value, int target)
{
    string  adverb;
    int     emotion;
    
    switch(value)
    {
        case -6:
        case -5:
        case -4:
        case -3:
        case -2:
        case -1:
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
    }
    
    temote(actor, emotion, adverb);
}

public void
trigger_offensive(object actor, int value, int target)
{
    string  adverb;
    int     emotion;
    
    switch(value)
    {
        case -6:
        case -5:
        case -4:
        case -3:
        case -2:
        case -1:
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
    }
    
    temote(actor, emotion, adverb);
}

public void
trigger_high_activity(object actor, int value, int target)
{
    string  adverb;
    int     emotion;
    
    switch(value)
    {
        case -6:
        case -5:
        case -4:
        case -3:
        case -2:
        case -1:
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
    }
    
    temote(actor, emotion, adverb);
}

public void
react_emote(object actor, int cmd, int value, int target)
{
    // Need something to prevent it from spamming.. fix later
    //if (random(gReactLimit[actor]))

    string tamer = this_object()->query_tamer_name();
    
    if (actor->query_real_name() == tamer)
        value++;
    
    switch(cmd)
    {
        case ACTION_OTHER:
        trigger_other(actor, value, target);
            break;
        case ACTION_CONTACT:
        trigger_contact(actor, value, target);
            break;
        case ACTION_PROXIMATE:
        trigger_proximate(actor, value, target);
            break;
        case ACTION_AURAL:
        trigger_aural(actor, value, target);
            break;
        case ACTION_VISUAL:
        trigger_visual(actor, value, target);
            break;
        case ACTION_OLFACTORY:
        trigger_olfactory(actor, value, target);
            break;
        case ACTION_INGRATIATORY:
        trigger_ingratiatory(actor, value, target);
            break;
        case ACTION_INTIMATE:
        trigger_intimate(actor, value, target);
            break;
        case ACTION_THREATENING:
        trigger_threatening(actor, value, target);
            break;
        case ACTION_OFFENSIVE:
        trigger_offensive(actor, value, target);
            break;
        case ACTION_HACTIVITY:
        trigger_high_activity(actor, value, target);
            break;
    }
}

public int
bitwise_and(int bit_one, int bit_two)
{
    return bit_one & bit_two;
}

public varargs int *
query_cmd_action(int cmd_attr = -1)
{
    int *actions = ({
        ACTION_CONTACT,     ACTION_PROXIMATE,   ACTION_AURAL,
        ACTION_VISUAL,      ACTION_OLFACTORY,   ACTION_INGRATIATORY, 
        ACTION_INTIMATE,    ACTION_THREATENING, ACTION_BLIND,
        ACTION_HACTIVITY,   ACTION_OFFENSIVE
    });
    
    if (cmd_attr > -1)
        actions = map(actions, &bitwise_and(cmd_attr, ));
    
    return actions - ({ 0 });
}

public int
query_emote_reaction(object actor, string tamer, int act)
{
    int     value;
    string *behavior;
    mapping pet_score = ([
        "fierce"    : -2,   "vicious"       : -2,
        "savage"    : -2,   "aggressive"    : -2,
        "guarded"   : -1,   "timid"         : -1,
        "docile"    :  0,   "meek"          :  0,
        "tranquil"  :  0,   "mannered"      :  0,
        "gracious"  :  1,   "gentle"        :  1,
        "calm"      :  1,
        "daring"    :  2,   "adventurous"   :  2,
        "energetic" :  2
    ]);
    mapping act_score = ([
        ACTION_CONTACT          :  0,
        ACTION_PROXIMATE        :  0,
        ACTION_AURAL            :  0,
        ACTION_VISUAL           :  0,
        ACTION_OLFACTORY        : -1,
        ACTION_INGRATIATORY     :  2,
        ACTION_INTIMATE         :  1,
        ACTION_THREATENING      : -4,
        ACTION_OFFENSIVE        : -3,
        ACTION_HACTIVITY        : -1,
    ]);
    
    // Sets the value of the action
    if (member_array(act, m_indexes(act_score)) > -1)
        value += act_score[act];
    
    // We dont want to proceed if the pet doesnt have a behavioral type
    if (!sizeof(behavior = filter(MANAGER->query_pet_adjs(tamer),
        &operator(>)(,-1) @ &member_array(,m_indexes(pet_score)))))
        return value;
    
    return value + pet_score[behavior[0]];
}

public void
emote_hook(string emote, object actor, string adverb, object *oblist, 
           int cmd_attr, int target)
{
    string  tamer;
    int    *react, *value;
    
    react = query_cmd_action(cmd_attr);
    
    if (!stringp(tamer = this_object()->query_tamer_name()))
        return;
    
    if (IN_ARRAY(ACTION_BLIND, react) && (!CAN_SEE(this_object(), actor) ||
        !CAN_SEE_IN_ROOM(this_object())))
        return;
    
    foreach(int act: react)
    {
        int tmp = 0;
        
        if (!(tmp = query_emote_reaction(actor, tamer, act)))
            continue;
        
        if (!sizeof(value) || abs(value[1]) < abs(tmp))
            value = ({ act, tmp });
    }
    
    if (!sizeof(value))
    {
        if (target)
            react_emote(actor, 0, 0, target);
        
        return;
    }
    
    react_emote(actor, value[0], value[1], target);
}


/*
 * Function name: block_action
 * Description:   Players can block certain actions on being performed on them.
 * Arguments:     string cmd    - the name of the executed command
 *                object target - the target in your inventory, if 0 it's you.
 *                object actor  - the command performer
 *                int cmd_type  - the command attributes (from cmdparse.h) 
 * Returns:       0 - command allowed
 *                1 - command blocked, no error message provided
 *                string - command blocked, use string as error message.
 */
public mixed
block_action(string cmd, object target, object actor, int cmd_type)
{
    /*
    if (cmd_type & ACTION_INTIMATE)
    {
        return 1;
    }*/
    
    return 0;
}