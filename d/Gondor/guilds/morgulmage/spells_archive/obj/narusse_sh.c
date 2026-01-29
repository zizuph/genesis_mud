/*
 * Spell effect for the morgul mage narusse spell. 
 *
 * Created by Eowul, Oktober 2009
 */
 
#include "../../morgulmage.h"

#include <stdproperties.h>
#include <macros.h>

inherit "/std/shadow";

#define _NO_PREP_TIME_ADJUSTMENT
#include "../generic_functions.c"

public varargs string flaming_short();
private void display_flicker_message();

object  weapon_owner;
mixed   original_short;
int     flicker_alarm;
object  description;

public varargs int
setup_shadow(mixed to_shadow, object description_ob)
{
    int result = shadow_me(to_shadow);
    if (!result) return result;
    
    description = description_ob;
    
    weapon_owner = environment(to_shadow);
    if (!living(weapon_owner)) 
    {
        remove_shadow();
        return 0;
    }
        
    original_short = shadow_who->query_short();
    shadow_who->set_short(flaming_short);
    
    flicker_alarm = set_alarm(20.0 + (rnd() * 20.0), 0.0, display_flicker_message);
}

void remove_narusse_enhancement()
{
    remove_alarm(flicker_alarm);
    
    shadow_who->set_short(original_short);    
    remove_shadow();
}

string long(string str, object for_obj)
{
    return (shadow_who->long(str, for_obj) 
        + "It is engulfed in searing-hot flames.\n");
}

public varargs string flaming_short()
{
    string text;
    if (functionp(original_short)) 
    {
        text = shadow_who->check_call(original_short);
    }
    else 
    {
        text = original_short;
    }
    
    return "flaming " + text;
}


int is_narusse_enhanced()
{
    return 1;
}

void display_flicker_message()
{
    mixed messages = description->get_flicker_messages();

    int selected_message = random(sizeof(messages));
    object wielder = environment(shadow_who);
    wielder->catch_msg(messages[selected_message][0] + "your "
        + shadow_who->short() + messages[selected_message][1]);
    can_see_caster(wielder)->catch_msg(messages[selected_message][0]
        + QTPNAME(wielder) + " " + shadow_who->short()
        + messages[selected_message][1]);
    
    flicker_alarm = set_alarm(30.0 + (rnd() * 60.0), 0.0, display_flicker_message);
}

int did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    object wielder = shadow_who->query_wielded();

    int original_didhit = shadow_who->did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    if (original_didhit == 1) return original_didhit;
    
    if (enemy->query_hp() <= 0) {
        if(!enemy->query_npc() || (random(10) == 0)) {
            return description->display_death_message(wielder, enemy, 
                shadow_who);
        }
    }
    
    if ((random(enemy->query_npc() ? 20 : 10) != 0)) return 0;
        
    if (phurt == -2) {
        // Parry
        return 0;
    } else if (phurt == -1) {
        // Evade
        return description->display_miss_message(wielder, enemy, shadow_who);
    } else if (phurt == 0) {
        // Miss
        return description->display_miss_message(wielder, enemy, shadow_who);
    }

    return description->display_hit_message(wielder, enemy, shadow_who, hdesc,
        phurt, dt);
}
