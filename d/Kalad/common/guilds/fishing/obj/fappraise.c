 /*****************************************************************************
*  Includes
 *****************************************************************************/
#include "/d/Kalad/common/guilds/fishing/defs.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"

 /*****************************************************************************
*  Inherits
 *****************************************************************************/
inherit "/std/object";

 /*****************************************************************************
*  Pragma
 *****************************************************************************/
#pragma strict_types

/*
 * Function name: appraise_object
 * Description:   A mask for changing volume to length
 *                
 * Arguments:     num - use this number instead of skill if given.
 */
public void
appraise_object(int num)
{
    write(this_object()->long() + "\n");
    write("You " + APPRAISE_VERB + " that the weight is " +
        appraise_weight(num) + " and you " + APPRAISE_VERB +
        " its length is about " + appraise_length(num) +
        ". You estimate its worth to " + appraise_value(num) + "." +
        appraise_light(num));
    if (this_object()->check_recoverable() != 1)
    {
        write(" " + capitalize(LANG_THESHORT(this_object())) +
            " does not seem to be able to last a while.");
    }
    if (this_object()->query_keepable())
    {
        write(this_object()->appraise_keep(num));
    }
    write("\n");
    
    if (this_object()->query_item_expiration())
        write(appraise_item_expiration() + "\n");
}

/*
 * Function name: appraise_length
 * Description:   A mask to change volume to length
 *                
 * Arguments:     num - use this number instead of skill if given.
 */
public string
appraise_length(int num)
{
    int value, skill;

    skill = (num ? num : this_player()->query_skill(SS_APPR_OBJ));
    skill = random((1000 / (skill + 1)), atoi(OB_NUM(this_object())));
    /* One routine for both objects and containers. Intentionally consider the
     * full volume of the container including its contents. But for livings,
     * only the volume of the living. */
    if (living(this_object()))
        value = query_prop(CONT_I_VOLUME);
    else
        value = query_prop(OBJ_I_VOLUME);
    value = cut_sig_fig(value + (skill % 2 ? -skill % 70 : skill) * value / 100);

    /* Display whole meters, fractions of meters or centimeters. */
    if ((value > 10000) || (!(value % 100)))
        return (value / 1000) + " meters";
    else if (value > 100)
        return sprintf("%3.1f", itof(value) / 100.0) + " meters";
    else
        return value + " centimeters";
}