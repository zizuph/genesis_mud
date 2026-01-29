#pragma strict_types

#include "../../morgulmage.h"

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>
#include <ss_types.h>

inherit "/std/creature.c";

#define HOLDING_ROOM    (MORGUL_SPELL_OBJ_DIR + "crabandir_room")
#define MAX_FAILURES    12
#define MIN_ANI_HANDL   40
#define MIN_AWARE       40
#define MIN_SPELLCRAFT  20
#define MIN_WIS         60

object search_target;
object message_target;
object spell_object;
int target_located = 0;
int search_alarm;
int failures = 0;

private void watch_target();

public void
create_creature()
{
    set_name(({ "craban", "crow", "crows", "clutch", "bird", "beast" }));
    set_race_name( "crow" );
    set_adj(({ "encircling", "midnight", "black" }));
    set_short("encircling clutch of midnight black crows");
    set_pshort("encircling clutches of midnight black crows");

    set_alignment( -100 );

    set_stats( ({ 10, 60, 25, 40, 40, 10 }) );
    set_whimpy( 80 );

    add_prop(CONT_I_WEIGHT, 700);
    add_prop(CONT_I_VOLUME, 700);
    add_prop(CONT_I_MAX_WEIGHT, 800);
    add_prop(CONT_I_MAX_VOLUME, 800);

    add_prop(OBJ_M_NO_ATTACK, "The crows are flying out of reach. It is "
        + "impossible to attack them.\n");

    add_prop(LIVE_I_UNDEAD, 100);
    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    add_prop(MAGIC_I_RES_POISON, 70);
    add_prop(MAGIC_I_RES_MAGIC,  40);
    add_prop(MAGIC_I_RES_AIR,    70);

    add_prop(LIVE_I_NO_CORPSE,   1);
    add_prop(LIVE_I_UNDEAD,    100 );   
}


public varargs string
long(mixed for_obj)
{
    if (!for_obj) for_obj = this_player();

    string message = "Above you is an innumerable amount of squaking, "
        + "midnight black birds. There is a rythmic determination to the "
        + "way they move, akin to that of carrion birds on the battlefield, "
        + "waiting and watching.  It is impossible to discern exact "
        + "detail from the writhing mass of beaks and feathers, but a "
        + "sense of extreme unease begins to creep up your spine the "
        + "longer you gaze upon it.";

    int spellcraft = for_obj->query_skill(SS_SPELLCRAFT);
    int awareness = for_obj->query_skill(SS_AWARENESS);
    int animal_handl = for_obj->query_skill(SS_ANI_HANDL);
    int wisdom = for_obj->query_stat(SS_WIS);

    if ((spellcraft > (MIN_SPELLCRAFT / 2 + random(MIN_SPELLCRAFT))) 
        || (awareness > (MIN_AWARE/ 2 + random(MIN_AWARE))))
    {
        message += " The crows do not look like normal beasts. Your skilled "+
            "senses notice the power of Dark Sorcery emanating from the "+
            "bird.";
    }

    if ((animal_handl > (MIN_ANI_HANDL / 2 + random(MIN_ANI_HANDL))) &&
        (wisdom > (MIN_WIS / 2 + random(MIN_WIS))))
    {
        message += " The eyes of the crabain show more intelligence by far "
            + "than one could expect from crows. The crabain seems to watch ";

        if (search_target == for_obj)
        {
            message += "you";
        }
        else
        {
            message += search_target->query_the_name(for_obj);
        }
        message += " intently.";
    }

    return message + "\n";
}


public void
start_search(object target, object caster)
{
    search_target = target;
    message_target = caster;

    this_object()->move(HOLDING_ROOM);
    search_alarm = set_alarm(5.0, 5.0, watch_target);
}

public void
set_spell_object(object ob)
{
    spell_object = ob;
}

private void
end_spell()
{
    remove_alarm(search_alarm);
    spell_object->remove_craban();
}

private int
can_scry_target()
{
    object target_env = environment(search_target);
    if (target_env->query_prop(ROOM_I_INSIDE)) return 0;
    if (target_env->query_prop(ROOM_M_NO_SCRY)) return 0;
    if (target_env->query_prevent_snoop()) return 0;
    if (!interactive(search_target)) return 0;
    if (search_target->query_prop(LIVE_M_NO_SCRY)) return 0;
    if (search_target->query_invis()) return 0;
    return 1;
}

private void
watch_target()
{
    object target_env = environment(search_target);

    if (!objectp(search_target) || !objectp(target_env) 
        || (failures > MAX_FAILURES)) 
    {
        message_target->catch_msg("The crebain fail to locate their target "
            + "and return to the shadows.\n", this_object());
        end_spell();
    }

    if (MASTER_OB(environment(this_object())) == HOLDING_ROOM)
    {
        if (!target_located)
        {
            message_target->catch_msg("You begin to receive a vision from "
                + "the crebain as they fly slowly over the land of "
                + target_env->query_domain() + " looking for " 
                + search_target->query_name() + ".\n", this_object());
            target_located = 1;
        } 
        else if (can_scry_target())
        {
            failures = 0;

            message_target->catch_msg("The crabain spot " 
                + search_target->query_name() + " below and glide down "
                + "to investigate.\n", this_object());

            move_living( "M", target_env, 1, 0);
            tell_room(target_env, capitalize(LANG_ADDART(short()) )+
                " appears overhead and slowly flies about.\n",
                this_object());
        } else {
            failures++;
        }

        return;
    }

    if (environment(this_object()) != target_env)
    {
        if (can_scry_target())
        {
            message_target->catch_msg("The crabain attempt to follow "
                + search_target->query_name() + ".\n");

            tell_room(environment(this_object()), QCTNAME(this_object())
                + " flies away as if they are following someone.\n", 
                this_object());
            move_living( "M", target_env, 1, 0 );

            tell_room(target_env, capitalize(LANG_ADDART(short()))
                + " appears overhead and slowly flies about.\n",
                this_object());

            failures = 0;
        } else {
            message_target->catch_msg("The crebain have lost " 
                + search_target->query_name() + ". They slowly fly "
                + "over the land of " + target_env->query_domain()
                + " trying to locate " + search_target->query_objective()
                + " again.\n", this_object());

            tell_room(environment(this_object()), QCTNAME(this_object())
                + " flap their wings and fly up into the sky.\n",
                this_object());

            this_object()->move(HOLDING_ROOM);
            failures++;
        }

        return;
    }

}

void
enter_env(object to, object from)
{
    ::enter_env( to, from );

    if (!objectp(to) || !objectp(from))
    {
        return;
    }

    if (!objectp(message_target))
    {
        end_spell();
        return;
    }

    if (MASTER_OB(to) == HOLDING_ROOM)
    {
        return;
    }

    if (present(search_target, to))
    {
        string message = "Through the eyes of the crabain you see:\n"
            + to->long();

        object *inv = FILTER_CAN_SEE(all_inventory(to), message_target)
            - ({ this_object() });

        object *ld;
        if (sizeof(ld = FILTER_DEAD(inv)))
        {
            message += capitalize(FO_COMPOSITE_DEAD(ld, message_target)) 
                + ".\n";
        }

        if (sizeof(ld = FILTER_LIVE(inv)))
        {
            message += capitalize(FO_COMPOSITE_LIVE(ld, message_target))
                + ".\n";
        }
        
        message_target->catch_msg(message, this_object());
    }
}

void
catch_msg(mixed str, object from_player)
{
    ::catch_msg( str, from_player );

    if ((from_player == this_object()) || !objectp(message_target))
    {
        return;
    }

    message_target->catch_tell( "Through the eyes of the crabain you see:\n");
    message_target->catch_msg(str, from_player);
}

/*
 * This trigger hopefully won't fire too frequently.
 */
public void emote_hook( string emote, object actor, string adverb,
    object *oblist, int cmd_attr = 0, int target = 0 )
{
    message_target->catch_msg(QCTNAME(actor) + " does something but the "
        + "details escape the bird's attention.\n", this_object());
}

public int
query_see_special_msg()
{
    return 1;
}
