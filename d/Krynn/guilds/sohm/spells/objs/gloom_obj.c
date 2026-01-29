#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <const.h>
#include "../defs.h"
#include "/d/Krynn/common/defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "spell_obj_base";
inherit "/d/Genesis/specials/resist";

mixed dark_msg, dark_long; 
string p_name;

void goto_player();

string 
no_get()
{
    say( QCTNAME( this_player() )+ " tries to grab the fog but it slips " +
         "through their fingers.\n" );
    return "You try to grab the fog but it slips through your fingers.\n";
}

void
dark_room_description()
{
    object target = environment(this_object());

    if(!target->query_prop(ROOM_S_DARK_LONG))
    {
       dark_long = 0;
    }
    else
    {            
       dark_long = target->query_prop(ROOM_S_DARK_LONG);
       target->remove_prop(ROOM_S_DARK_LONG);
    }

    if(!target->query_prop(ROOM_S_DARK_MSG))
    {
       dark_msg = 0;
    }
    else
    {
       dark_msg = target->query_prop(ROOM_S_DARK_MSG);
       target->remove_prop(ROOM_S_DARK_MSG);
    }

    target->add_prop(ROOM_S_DARK_MSG,
       "Shadows surrounding you obscure your vision, making it too dark to");
    target->add_prop(ROOM_S_DARK_LONG,
       "Dark shadows rise around you like a fog, obscuring " +
       "your vision and blocking your line of sight.\n");

}

void
remove_dark_room_description()
{
    environment(this_object())->remove_prop(ROOM_S_DARK_MSG);
    environment(this_object())->remove_prop(ROOM_S_DARK_LONG);

    if(dark_msg)    
       environment(this_object())->add_prop(ROOM_S_DARK_MSG, dark_msg);
    if(dark_long)
       environment(this_object())->add_prop(ROOM_S_DARK_LONG, dark_long);
}

public int
setup_spell_effect()
{
    int result = ::setup_spell_effect();
    set_name("shadows");
    add_name(({ "fog", "clouds","cloud","shadow","_SoHM_gloom_object" }));
    add_adj(({ "dark", "fog", "of" }));
    set_short("fog of dark shadows");
    set_pshort("whispy clouds of dark shadows");
    set_long("Whisps of dark shadows rise around you like a fog, obscuring " +
             "your vision and blocking your line of sight. Dark whispers, " +
             "barely perceptible, echo from within the gloom of the fog.\n");
    set_spell_effect_desc("gloom");
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 1000000);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_GET, no_get);
    add_prop(OBJ_I_LIGHT, DARKNESS_PASSIVE);
    unset_no_show();
    unset_no_show_composite();
    return result;    
}
    



/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();
    object caster = query_effect_caster();

    caster->catch_msg("The shadows rise around you, creating a fog that is " +
       "dark and impenetrable.\n");        
    tell_room(target, "The shadows rise around you, creating a fog that is " +
       "dark and impenetrable.\n", ({ caster }));

    // Provides two levels of darkness
    // this_object()->add_prop(OBJ_I_LIGHT, DARKNESS_PASSIVE);

    if(!target->query_prop(ROOM_S_DARK_LONG))
    {
       dark_long = 0;
    }
    else
    {            
       dark_long = target->query_prop(ROOM_S_DARK_LONG);
       target->remove_prop(ROOM_S_DARK_LONG);
    }

    if(!target->query_prop(ROOM_S_DARK_MSG))
    {
       dark_msg = 0;
    }
    else
    {
       dark_msg = target->query_prop(ROOM_S_DARK_MSG);
       target->remove_prop(ROOM_S_DARK_MSG);
    }

    target->add_prop(ROOM_S_DARK_MSG,
       "Shadows surrounding you obscure your vision, making it too dark to");
    target->add_prop(ROOM_S_DARK_LONG,
       "Dark shadows rise around you like a fog, obscuring " +
       "your vision and blocking your line of sight.\n");

    set_alarm(0.0, 1.0, &goto_player());

}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object target = query_effect_target();
    tell_room(environment(this_object()), "The fog begins to lighten, and the " +
              "shadows suddenly disperse.\n");

    remove_dark_room_description();
}
/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */

public void
hook_spell_effect_warn_fading()
{
    object caster = query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You sense the gloom spell is about to "
            + "disperse.\n");
    }
}
/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained()
{

    object caster = query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "the gloom spell.\n");
    }    
}

/*
 * Function name: goto_player()
 * Description  : We want the gloom to follow the player if they are maintaining
 *                a wind gust and moving really fast.
 */
void
goto_player()
{
    object caster = query_effect_caster();

    // caster not maintaining wind gust, gloom is stationary
    if (!caster->query_prop("_sohm_wind_gust_active"))
    {
        return;
    }

    // if the caster has gone LD, remove gloom
    if (caster->query_prop("_player_s_ld_in_room"))
    {
        remove_spell_object();
        return;
    } 

    // player is no longer in game
    if (!objectp(caster))
    {
        remove_spell_object();
        return;
    }

    // if caster has moved
    if(environment(caster) != environment(TO)) 
    {
        tell_room(environment(this_object()), "A strange wind gusts around you, " +
              "dispersing the shadowy fog.\n", ({ caster }));
        remove_dark_room_description();
        this_object()->move(environment(caster));
        tell_room(environment(this_object()), "An eerie wind suddenly rises, " +
            "blowing in a dark and impenetrable fog.\n", ({  }));
        dark_room_description();
    }
}

void init()
{
    ::init();
    // set_alarm(0.0, 1.0, &goto_player());
}
