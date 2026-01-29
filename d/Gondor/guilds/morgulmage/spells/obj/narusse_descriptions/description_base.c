inherit "/std/object";

#define _NO_PREP_TIME_ADJUSTMENT
#include "../../generic_functions.c";
#include <options.h>
#include <wa_types.h>
#include "descriptions_hit.h"

void display_wield_message(object wielder, object weapon)
{
    wielder->catch_msg("You raise your " + weapon->short() 
        + " high into the air.\n");
    can_see_caster(wielder)->catch_msg(QCTNAME(wielder) + " raises "
        + wielder->query_possessive() + " " + weapon->short()
        + " high into the air.\n");        
}

void display_wield_flame_message(object wielder, object weapon)
{
    object env = environment(wielder);
    tell_room(env, QCPNAME(wielder) + " " + weapon->short()
        + " is suddenly engulfed in scorching flames.\n", wielder);
    wielder->catch_tell("Your "+ weapon->short()
        + " is suddenly engulfed in scorching flames.\n", wielder);
}

void display_unwield_message(object wielder, object weapon)
{
    object env = environment(wielder);
    tell_room(env, "The searing-hot flames engulfing "
        + QPNAME(wielder) + " " + weapon->short() 
        + " quietly flicker out of existence.\n",
        wielder);
    wielder->catch_msg("The searing-hot flames engulfing "
        + "your " + weapon->short() + " quietly flicker out of "
        + "existence.\n");
}

void display_ignite_message(object wielder, object weapon)
{
    wielder->catch_msg("No ignite message defined, please leave a bug "
        + "report.\n");
}

void display_extinguish_message(object wielder, object weapon)
{
    object env = environment(wielder);
    tell_room(env, "As if snuffing a candle, " + QTNAME(wielder) 
        + " extinguishes the flickering flames on the " + weapon->short()
        + " with a fell breath.\n", wielder);
    
    wielder->catch_msg("As if snuffing a candle, you extinguishes the "
        + "flickering flames on the " + weapon->short() + " with a fell "
        + "breath.\n");
}

mixed get_flicker_messages() 
{
    return ({ 
        ({ "The searing-hot flames engulfing ", " flicker hungrily.\n" }),
        ({ "The flames dance menacingly across ", ".\n" }),
        ({ "The flames hiss softly as they burn on ", ".\n" }),
        ({ "The flames on ", " flare briefly.\n" }),
        ({ "The flames on ", " cast a dull radiance, lengthening "
              + "shadows rather than truly illuminating.\n" })
    });
}

int display_death_message(object wielder, object enemy, object weapon) 
{
    return 0;
}

int display_miss_message(object wielder, object enemy, object weapon)
{
    wielder->tell_watcher_miss("The air seems to become thick with "
        + "frustration as " + QTPNAME(wielder) + " attack with the "
        + weapon->short() + " whips through the air over " 
        + QTNAME(enemy) + ".\n", enemy, ({ wielder, enemy }));

    if (!wielder->query_option(OPT_GAG_MISSES)) {
        wielder->catch_msg("With a snarl of frustration, you watch "
            + "your " + weapon->short() + " soar effortlessly through "
            + "the air above " + QTNAME(enemy) + ".\n");
    }
    
    if (!enemy->query_option(OPT_GAG_MISSES)) {
        enemy->catch_msg("Impending doom engulfs your senses as the "
            + "errant swing of the " + weapon->short() + " from "
            + QTNAME(wielder) + " sails effortlessly over your head. "
            + "That was too close for comfort!\n");
    }
    
    return 1;
}

string convert_damage(int phurt) {
    switch(phurt) {
        case 0..5: return "slightly hurt";
        case 6..10: return "hurt";
        case 11..15: return "really hurt";
        default: return "extremely hurt";
    }
}

int filter_message(int phurt, int dt, mixed data) 
{
    return ((phurt >= data[1]) && (phurt <= data[2]) && (member_array(dt, data[3]) != -1));
}

int display_hit_message(object wielder, object enemy, object weapon,
    string location, int phurt, int dt) 
{
    mixed messages = filter(HIT_MESSAGES, &filter_message(phurt, dt));
    if (sizeof(messages) == 0) return 0;
    
    mixed selected_message = messages[random(sizeof(messages))];
    mixed message_function = selected_message[0];
    
    return message_function(wielder, enemy, weapon, location, convert_damage(phurt));
}  
