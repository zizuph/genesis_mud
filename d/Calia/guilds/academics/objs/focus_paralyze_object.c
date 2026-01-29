/*
 * Focus Paralyze Object
 * 
 * An Academic focuses themselves elementally in preparation to
 * use cheiropoto, their elemental at-will spell.
 * During the focus, they cannot do anything.
 *
 * Created by Petros, December 2009
 */

#include <stdproperties.h>
#include <std.h>
#include <macros.h>
#include <files.h>

#include "defs.h"

inherit "/std/paralyze";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define ACADEMIC_FOCUS_SUBLOC   "_academic_focus_subloc"

// Variables
private static string * base_allow_verbs = ({
    "look",
    "l",
    "last",
    "mwho",
    "team",
    "who",
});

public string * focus_messages = ({
    "You close your eyes and breathe slowly, harnessing your mind "
        + "to focus yourself elementally.",
    "You sink into a deep trance, feeling a serene calm.",
    "You follow carefully the steps you have learned and begin to feel "
        + "yourself melding with the energies surrounding you.",
    "Feeling yourself taking control of them with your mind, you open "
        + "your eyes.",
    });
    
public void
create_paralyze()
{
    set_name("_academic_focus_paralyze_object");
    add_name( ({ "academic_focus_paralyze_object" }) );
    set_short("hidden focus paralyze object");
    set_long("This is the hidden focus paralyze object that is on a "
        + "student who is focusing to become elementally focused.\n");
    set_fail_message("You are currently focusing yourself. If you wish "
        + "to stop, you can <stop afocus>.\n");
    
    // Set up the abort stuff
    set_stop_verb("stop"); 
    set_stop_fun("stop_afocus"); 
    set_stop_object(this_object());      
}

public string *
query_allowed_verbs()
{
    string * allow_verbs = ({ });

    allow_verbs += base_allow_verbs;
    allow_verbs += m_indices("/cmd/live/info"->query_cmdlist());
    allow_verbs += m_indices("/cmd/live/state"->query_cmdlist());
    
    return allow_verbs;
}

int
stop(string str)
{       
    // We want to allow some basic commands
    if (IN_ARRAY(query_verb(), query_allowed_verbs()))
    {
        return 0;
    }
    
    return ::stop(str);
}

public int
stop_afocus(string str)
{
    if (!strlen(str) || str != "afocus")
    {
        // returning 1 ensures the paralyze stays.
        return 1;
    }
    
    object player = this_player();
    // Return 0 to remove the paralyze object
    write("You relax yourself and stop focusing. You don't feel "
        + "ready to channel the elemental energies.\n");
    tell_room(environment(player), QCTNAME(player) + " opens "
        + player->query_possessive() + " eyes and seems to be alert "
        + "again.\n", ({ player }));
    return 0;
}

public void
display_focus_message()
{
    object player = environment(this_object());
    if (!IS_PLAYER_OBJECT(player))
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }
    
    string message = focus_messages[0];
    focus_messages = focus_messages[1..];
    write("\n" + message + "\n\n");
    if (sizeof(focus_messages))
    {
        // Set up random intervals between 2 and 5 seconds
        float delay = itof(3 + random(5));
        set_alarm(delay, 0.0, &display_focus_message());
    }
    else
    {
        setuid();
        seteuid(getuid());
        set_alarm(0.0, 0.0, remove_object);
        object focus_obj = clone_object(ACADEMIC_FOCUS_OBJECT);
        focus_obj->set_spell_effect_caster(player);
        focus_obj->set_spell_effect_target(player);
        focus_obj->move(player, 1);
        focus_obj->setup_spell_effect();
        player->catch_tell("You find yourself fully elementally focused. You "
            + "can now channel the elemental energies with ease.\n");            
        tell_room(environment(player), QCTNAME(player) + " opens "
            + player->query_possessive() + " eyes and seems to be alert "
            + "again.\n", ({ player }));
    }
}

/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    
    if (!IS_PLAYER_OBJECT(dest))
    {
        return;
    }

    dest->add_subloc(ACADEMIC_FOCUS_SUBLOC, this_object());
    set_alarm(0.0, 0.0, &display_focus_message());
}

/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
        
    if (!IS_PLAYER_OBJECT(ob))
    {
        return;
    }

    ob->remove_subloc(ACADEMIC_FOCUS_SUBLOC);            
}
 

/*
 * Function:    show_subloc
 * Description: The sublocation description is shown when you examine
 *              someone or examine yourself. For the wounding shadow,
 *              it should display the wounds that the person has.
 * Arguments:   subloc  - name of the sublocation to return string for
 *              on      - where the object is on
 *              for_obj - which object to display message to
 * Returns:     nothing
 */
public string
show_subloc(string subloc, object on, object for_obj)
{
    string data, desc;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
        return on->show_subloc(subloc, on, for_obj);
    }
    
    if (subloc != ACADEMIC_FOCUS_SUBLOC)
    {
        return on->show_subloc(subloc, on, for_obj);
    }
    
    if (for_obj == on)
    {
        return "You are in the process of focusing yourself elementally.\n";
    }
    return (capitalize(on->query_pronoun())) + " is concentrating "
        + "on something.\n";
}
