/*
 * pScry
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/spells/std_pot_spell";

#include "/d/Ansalon/common/defs.h"
#include "../spells.h"
#include "../guild.h"
#include <macros.h>
#include <tasks.h> 
#include <filter_funs.h>
#include <stdproperties.h>
#include <composite.h>
 
static string *common_art = ({ "a", "an", "the" });
static string *common_prep = ({ "up", "on", "at", "in", "outside",
    "inside", "above", "below", "beside", "under" });

static mapping race_colour = ([
    "human"     : ({ "white", "silver", "black" }),
    "elf"       : ({ "golden", "yellow", "dark yellow" }),
    "dwarf"     : ({ "silver grey", "grey", "dark grey" }),
    "hobbit"    : ({ "light green", "green", "dark green" }),
    "gnome"     : ({ "light brown", "bronze", "deep bronze" }),
    "goblin"    : ({ "brown", "greenish brown", "brownish black" })
    ]);

static string *brute_colour = ({
    "", "streaked with red", "mottled with red",
    "with swirling clouds of red" });

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 13;
}


varargs string *
translate_auras(object *obj, object for_obj)
{
    int i;
    string *auras;

    if (!for_obj)
        for_obj = this_player();

    auras = ({ });

    for (i=0; i<sizeof(obj); i++)
    {
        object o;
        string *ca,c;

        o = obj[i];

        if (o->query_prop(LIVE_I_UNDEAD))
            continue;

        ca = race_colour[o->query_race()];
        if (!pointerp(ca))
            c = "indistinct";
        else if (o->query_alignment() > 250)
            c = ca[0];
        else if (o->query_alignment() < -250)
            c = ca[2];
        else
            c = ca[1];

        c += " aura";

        if (for_obj == o)
            c += " of yourself";
        else if (for_obj->query_met(o))
            c += " belonging to " + C(o->query_real_name());
            
        auras += ({ LANG_ADDART(c) });
    }
    return auras;
}

public void
concentrate_msg(object caster, object *targets, string arg)
{
    object old_tp = TP;

    set_this_player(caster);
    caster->catch_tell("You close your eyes and turn your sight inwards.\n");
    all_msgbb(QCTNAME(caster) + " closes " + HIS(caster) + " eyes, " +
        "concentrating on something.\n", caster);
    set_this_player(old_tp);
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    object tar = targets[0];
    object env;
    string s,short_desc;
    string *auras;
    int t;

    env = environment(tar);
    if (!env)
    {
        caster->catch_tell("You do not sense anything of " +
        tar->query_the_name(caster) + "'s surroundings.\n");
        return;
    }

    short_desc = env->short();
    s = "You let your mind travel towards " + tar->query_the_name(caster) +
    ". ";
    
    switch(env->query_prop(ROOM_I_TYPE))
    {
        case ROOM_IN_WATER:
            s += "You see the swirling blue clouds of open water " +
            "all around you. ";
            break;
        case ROOM_UNDER_WATER:
            /* cannot scry under water */
            caster->catch_tell("Somehow, you fail to locate " +
            capitalize(tar->query_real_name()) + ".\n");
            return;
        case ROOM_BEACH:
            s += "You see the swirling blue clouds of open water " +
            "nearby. ";
            break;
    }

    if (short_desc && short_desc != "")
    {
        string tmp;

        tmp = lower_case(explode(short_desc + " ", " ")[0]);
        if (member_array(tmp,common_prep) >= 0)
        {
            short_desc = tmp + extract(short_desc,strlen(tmp));
            s += "Drawing near, you get a strong impression of " +
            "being " + short_desc + ". ";
        }
        else if (member_array(tmp,common_art) >= 0)
        {
            short_desc = tmp + extract(short_desc,strlen(tmp));
            s += "Drawing near, you get a strong impression of " +
            short_desc + ". ";
        }
        else
        {
            s += "Drawing near, you get a strong impression of " +
            "the " + short_desc + ". ";
        }
    }

    auras = translate_auras(FILTER_LIVE(all_inventory(env)), caster);

    if (sizeof(auras))
    {
        s += "Nearby, you sense " + COMPOSITE_WORDS(auras) + ". ";
    }
    else
    {
        s += "You do not sense any auras nearby. ";
    }

    caster->catch_tell(s + "\n");

    /* Only send a message to the target if the caster is
       a non-wizard, to allow for testing
     */
    if (caster->query_wiz_level())
        return;

    tar->catch_msg("You briefly feel an alien presence " +
    "nearby, but the feeling passes.\n");
}

public object *
pscry_target(object caster, string str)
{
    object who;

    if (!stringp(str))
    {
        caster->catch_tell("Target the spell on whom?\n");
        return ({ });
    }
    
    who = find_living(str);
    
    if (!objectp(who))
    {
        caster->catch_tell("You do not sense anyone known as " +
            C(str) + " being present in the realms.\n");
        return ({ });
    }

    if (who->query_prop(LIVE_M_NO_SCRY))
    {
        if (stringp(who->query_prop(LIVE_M_NO_SCRY)))
            caster->catch_msg(who->query_prop(LIVE_M_NO_SCRY));
        else
            caster->catch_tell("You sense a wall of force " +
                "stopping your attempt to divine the whereabouts " +
                "of " + C(str) + ".\n");
         
         return ({ });
    }
    
    if (environment(who)->query_prop(ROOM_M_NO_SCRY))
    {
        if (stringp(environment(who)->query_prop(ROOM_M_NO_SCRY)))
            caster->catch_msg(environment(who)->query_prop(ROOM_M_NO_SCRY));
        else
            caster->catch_tell("You sense a wall of force stopping " +
                "your attempt to divine the whereabouts of " + C(str) + ".\n");
   
        return ({ });
    }
    
    if (!(wildmatch("*jr", caster->query_real_name())) &&
        (who->query_wiz_level()))
    {
        caster->catch_tell("You sense a wall of force stopping your " +
            "attempt to divine the location of the wizard " + C(str) +
            ".\n");
        return ({ });
    }
    
    if (caster->query_met(who))
    {
        set_spell_mana(107);
    }
    else
    {
        set_spell_mana(214);
    }
    
    return ({ who });
}

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       0/1 - spell configured/not configured (cannot be cast)
 */
public varargs int
config_spell(object caster, object *targets, string argument)
{
    set_spell_name("pscry");
    set_spell_desc("Divine the whereabouts of someone you know");

    set_spell_element(SS_ELEMENT_LIFE, 45);
    set_spell_form(SS_FORM_DIVINATION, 30);

    set_spell_time(10);
    set_spell_mana(107);

    set_spell_task(TASK_ROUTINE);

#ifndef NO_INGREDIENTS
    set_spell_ingredients(({"solinaith", "apple"}));
#endif

    set_spell_target(pscry_target);
    
    set_spell_vocal(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_visual(0);

    return 0;
}
