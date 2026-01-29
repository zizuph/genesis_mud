/*
 * - makeover_shadow.c
 *
 * Shadow for modifying looks.
 *
 * * Lucius May 2009: Updated to use a domain skill to track expire time.
 * 		Other method was too unreliable.
 */
#pragma no_inherit
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>

inherit "/std/shadow";

#define STATE  ("/cmd/live/state")
#define SUBLOC_MISCEXTRADESC "_subloc_misc_extra"

// 1 Day in seconds.
#define DAY	86400
#define LASTS	(time() + (DAY * (3 + random(5))))

private static int expire;
private static string unique = "";

/*
 * Set our unique look.
 */
public int
set_unique_look(string str)
{
    return strlen(unique = str);
}

/*
 * Query our unique look.
 */
public string
query_unique_look(void)
{
    return unique;
}

#if 1
public void
remove_shadow(void)
{
    setuid();
    seteuid(getuid());

    write_file("/d/Avenir/log/zigg/makeover",
	ctime(time()) +": EXPIRES "+ ctime(expire) +
	": "+ calling_object()->query_name() +"\n"+
	">> "+ calling_function() +"() - "+
	    file_name(calling_object()) +"\n");

    ::remove_shadow();
}
#endif

/*
 * Remove this shadow.
 */
public void
remove_unique_looks(int flag)
{
    if (flag)
    {
	shadow_who->catch_tell("Your makeover is beyond recovery "+
	    "and your true looks show through.\n");
    }

    shadow_who->remove_autoshadow(this_object());
    remove_shadow();
}

/*
 * Finalize shadow placement.
 */
private void
finish_shadow(void)
{
    shadow_who->add_autoshadow(
	MASTER +":"+ unique +","+ LASTS);
}

/*
 * Recover our shadow.
 */
public void
autoload_shadow(string str)
{
    ::autoload_shadow(str);

    /* Corruption? */
    if (sscanf(str, "%s,%d", unique, expire) !=2)
	set_alarm(1.0, 0.0, &remove_unique_looks(1));
    /* Makeover is expired. */
    else if (expire <= time())
	set_alarm(1.0, 0.0, &remove_unique_looks(1));
}

/*
 * Add our custom subloc.
 */
public varargs int
shadow_me(mixed to_shadow)
{
    int res = ::shadow_me(to_shadow);
    if (res)  finish_shadow();
    return res;
}

/*
 * Description: Shows how we look.
 */
private nomask string
show_subloc_looks(object for_obj, object state)
{
    if (shadow_who->query_prop(NPC_I_NO_LOOKS))
        return "";

    if (!strlen(unique))
	return state->show_subloc_looks(shadow_who, for_obj);

    return (for_obj == shadow_who ? "You look " :
	capitalize(shadow_who->query_pronoun()) +" looks ") +
	unique +".\n";
}

/*
 * Description: Shows the specific sublocation description for a living
 * Notes:       Taken straight from /cmd/live/state.c
 */
private nomask string 
show_subloc_state(object for_obj)
{
    object state = find_object(STATE);
    string res, cap_pronoun, cap_pronoun_verb, tmp;

    if (shadow_who->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == shadow_who)
    {
        res = "You are";
        cap_pronoun_verb = res;
        cap_pronoun = "You are ";
    }
    else
    {
        res = capitalize(shadow_who->query_pronoun()) + " is";
        cap_pronoun_verb = res;
        cap_pronoun = capitalize(shadow_who->query_pronoun()) +
	    " seems to be ";
    }
    
    if (strlen(tmp = state->show_subloc_size(shadow_who, for_obj)))
        res += tmp;
    else
        res = "";

    /* This is our customized bit. */
    res += show_subloc_looks(for_obj, state);
    
    if (shadow_who->query_attack())
    {
        res += cap_pronoun_verb +
	    state->show_subloc_fights(shadow_who, for_obj);
    }

    res += cap_pronoun +
	state->show_subloc_health(shadow_who, for_obj) + ".\n";

    return res;
}

/*
 * Description: Intercepts the "_subloc_misc_extra" subloc query.
 */
public varargs mixed
show_cont_subloc(string sloc, object for_obj)
{
    if (sloc == SUBLOC_MISCEXTRADESC)
	return show_subloc_state(for_obj);

    return shadow_who->show_cont_subloc(sloc, for_obj);
}
