/*
 * Ashlar, 10 Jul 98
 *
 * The ritual which is initiated by the spell on the scroll.
 *
 */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <tasks.h>
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include "../guild.h"
#include "/d/Ansalon/common/defs.h"

object tar;
int round;

void start();

/* all_msg: puts a message to everyone in the environment of the caster */
public varargs void
all_msg(string str, object caster, mixed exclude, int only_vision)
{
    object *who;
    
    who = FILTER_PLAYERS(all_inventory(environment(caster)) - ({ caster }));

    if (pointerp(exclude))
        who -= exclude;
    else if (objectp(exclude))
        who -= ({ exclude });
        
    if (only_vision)
        who = FILTER_CAN_SEE_IN_ROOM(FILTER_IS_SEEN(caster,who));

    who->catch_msg(str);
}

public varargs void
all_msgbb(string str, object caster, mixed exclude)
{
    all_msg(str,caster,exclude,1);
}

public void
tell_outside(string str)
{
    (NERAKA_ADMIN)->tell_neraka("", str, 1, ({ environment(tar) }));
}

public void
tell_inside(string str)
{
    (NERAKA_ADMIN)->tell_neraka("", str, 2);
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    if (env && living(env))
    {
        tar = env;
        start();
    }
}

void
create_object()
{
    set_name("priest_ritual");

    add_prop(OBJ_S_WIZINFO,
        "This is an object that plays out a ritual for the " +
        "Priests of Takhisis. It should selfdestruct after " +
        "finishing.\n");

    set_no_show();
}

void
ritual()
{
    /* Check that we remain in the same place */
    object env = environment(tar);

    if (!env || !env->query_prop(NERAKA_I_IS_TEMPLE_ROOF))
    {
        tar->catch_tell("You left before the ritual was finished, " +
        "and the working is aborted!\n");
        remove_object();
        return;
    }
    
    switch(round++)
    {
        case 0:
            tell_room(env,
                "A strong gust of wind buffets you.\n");
            break;

        case 1:
            tell_room(env,
                "The wind picks up in speed, and you notice storm " +
                "clouds beginning to gather above the temple.\n");

            tell_outside("Dark storm clouds rush in to gather above " +
            "the temple.\n");
            break;

        case 3:
            tar->catch_tell("The wind is so strong you fall to your " +
            "knees to hold your balance.\n");

            all_msg("The wind is so strong you grab hold of the railing " +
            "less you will be blown off the roof.\n", tar);
            break;

        case 6:
            tell_room(env,
                "Lightning strikes from the clouds, crashing down on the " +
                "roof with a deafening noise!\n");

            tell_outside("Lightning strikes down on the roof of the " +
                "temple with loud crashes!\n");
            tell_inside("You hear the sound of thunder, close by.\n");
            break;

        case 8:
            tar->catch_tell("In the middle of the storm, you see before " +
            "you a vision of the Queen of Darkness.\n");

            all_msg("The fierce storm rages on.\n", tar);

            tell_outside("A fierce storm rages above the temple.\n");
            break;

        case 9:
            tar->catch_tell("The shimmering vision points at you, and " +
            "she speaks directly into your mind. Her strong, commanding " +
            "voice says: YOU HAVE SERVED ME WELL, CLERIC...\n");
            break;

        case 11:
            tar->catch_tell("The voice continues: YOU ARE WORTHY OF " +
            "CALLING YOURSELF PRIEST!\n");
            break;

        case 12:
            tar->catch_tell("Prompted by the vision, you extend your " +
            "right arm.\n");

            all_msgbb(QCTNAME(tar) + " extends " + HIS(tar) + " right " +
            "arm.\n", tar);
            break;

        case 14:
            tar->catch_tell("The voice speaks in your mind: " +
            "HEREBY IS YOUR BOND TO THE PRIESTHOOD RENEWED!\n");
            break;

        case 15:
            tar->catch_tell("A bolt of lightning strikes the tattoo " +
            "on your right wrist, transforming it. The noise is " +
            "so loud as to be painful, but you feel no pain from the " +
            "lightning.\n");

            all_msgbb("A bolt of lightning strikes " + QTNAME(tar) +
            "'s right wrist!\n", tar);

            tell_outside("Another bolt of lightning strikes the roof " +
            "of the temple.\n");

            tell_inside("Thunder rumbles nearby.\n");
            break;

        case 17:
            tar->catch_tell("The vision shimmers and disappears.\n");
            break;

        case 18:
            tell_room(env,
                "The wind stops blowing so suddenly you almost " +
                "fall down.\n");
            break;

        case 19:
            tell_room(env,
                "The storm clouds dissolve as quickly as they appeared.\n");

            tell_outside("The storm raging above the temple seems to have " +
            "ended and the clouds dissolve rapidly.\n");
            break;
            
        case 20:
            tar->catch_tell("The ritual is over and you stand up proudly, " +
            "knowing you are now a Priest of Takhisis!\n");

            // This will be able to be adjusted upwards once the player prays.
            tar->set_skill(PS_GUILD_LEVEL, 50);
            GUILD_ADMIN->clear_promotions(tar->query_real_name());
            GUILD_ADMIN->set_guild_level(tar->query_real_name(), 50);
            tar->remove_prop(TMP_POT_DEDICATION_SCROLL);

            remove_object();
            break;

    }
}

void
start()
{
    round = 0;
    set_alarm(5.0,5.0,ritual);
}
