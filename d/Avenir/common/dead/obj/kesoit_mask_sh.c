// file name: /d/Avenir/common/dead/obj/death_mask_sh.c
// creator(s): Lilith & Zizuph July 2021
// purpose:    Shadows the person wearing the magical death mask
//             /d/Avenir/common/dead/obj/kesoit_mask
//             Keeps player stuffed level from dropping
//             they don't get hungry until they take
//             take it off and then they feel the full
//             impact of not eating. 
//        It defers the effects of not eating.
//
// Update 11/2021 Zizuph: Move anti-scry into shadow, instead
//    of setting the prop in the mask itself.
//       Lilith Apr 2022: caching scry attempt results for 
//         5 mins at a time.
// note:
// bug(s):
// to-do:

inherit "/std/shadow";
#include <stdproperties.h>

int original_stuffed_level;

int scry_resist;
object effect_mask;

int query_stuffed() 
{
    int current_stuffed = shadow_who->query_stuffed();

    if (calling_function(0) == "eat_food")
	return current_stuffed;

    return min(shadow_who->query_prop(LIVE_I_MAX_EAT),
      max(original_stuffed_level, current_stuffed));
}

public mixed
query_prop(string prop)
{
    mixed result = shadow_who->query_prop(prop);
    if (prop != LIVE_I_NO_SCRY)
    {
        return result;
    }

    if (!result)
    {
        if (effect_mask && effect_mask->get_scry_random_value() >= scry_resist)
        {
            return "Death masks that one from your prying eyes.\n";
        }
        return result;
    }
    else
    {
        return result;
    }
}


void 
setup_death_mask_shadow(object player, int resist, object mask) 
{
    original_stuffed_level = player->query_stuffed();
    scry_resist = resist;
    effect_mask = mask;
    shadow_me(player);
}

void 
remove_death_mask_shadow() 
{
    remove_shadow();
}
