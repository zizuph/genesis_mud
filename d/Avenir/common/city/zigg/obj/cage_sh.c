/*
 * - cage_sh.c
 *
 * Shadow for the cage.
 */
#pragma strict_types

inherit "/std/shadow";

#include <zigg.h>
#include <macros.h>
#include <living_desc.h>
#include <stdproperties.h>

private static int temp, pushing;
private static object cage;

public varargs int
shadow_me(mixed to_shadow)
{
    if (::shadow_me(to_shadow))
    {
	shadow_who->set_no_show_composite(1);
	return 1;
    }

    return 0;
}

/* Try to cleanly handle shadow removal. */
public void
remove_shadow(void)
{
    shadow_who->set_no_show_composite(0);
    ::remove_shadow();
}

public void
remove_cage_shadow(void)	{ remove_shadow(); }

public void
set_cage_object(object ob)	{ cage = ob; }

public object
query_cage_object(void)		{ return cage; }

public void
cage_being_pushed(void)		{ pushing = 1; }

/*
 * Block moving while caged.
 */
public varargs int
move_living(string how, mixed dest, int no_follow, int no_glance)
{
    if (temp)
    {
	pushing = temp = 0;
	return shadow_who->move_living(how, dest, no_follow, no_glance);
    }

    if (!pushing)
    {
	shadow_who->catch_tell("The "+ cage->real_short() + " is ample, "+
	    "but the bars get in the way of that much movement.\n");
	tell_room(ENV(shadow_who), QCTNAME(shadow_who) +" moves around "+
	    "inside "+ HIS(shadow_who) +" "+ cage->real_short() +", as if "+
	    "looking for a way out.\n", ({ shadow_who }), shadow_who);

	return 7;
    }

    pushing = 0;
    return shadow_who->move_living("M", dest, 1, no_glance);
}

/* Specialized version of describe_contents() */
private string
describe_outside(void)
{
    object *obs, *lv, *dd, com;
    string item, res = ENV(shadow_who)->show_sublocs(shadow_who);
    object comp = find_object("/sys/global/composite");

    obs = all_inventory(ENV(shadow_who)) - ({ shadow_who, cage });

    lv = filter(obs, living);
    dd = obs - lv;

    if (stringp(item = comp->desc_dead(dd, 1)))
        res += capitalize(item) + ".\n";

    if (stringp(item = comp->desc_live(lv, 1)))
        res += capitalize(item) + ".\n";

    return res + "\n";
}

/*
 * Modified for the caged view of the world.
 */
public varargs int
do_glance(int brief)
{
    string desc;
    object env = environment(shadow_who);

    /* It is dark. */
    if (!CAN_SEE_IN_ROOM(shadow_who))
    {
	desc = env->query_prop(ROOM_S_DARK_LONG);

	if (!strlen(desc))
	    shadow_who->catch_tell(LD_DARK_LONG);
	else
	    shadow_who->catch_tell(desc);

	return 1;
    }

    if (brief)
    {
	desc = "Outside the cage, you see: "+ CAP(env->short()) + ".\n";
	desc += ENV(shadow_who)->exits_description();
	desc += describe_outside();
    }
    else
    {
	string str = ENV(shadow_who)->long(0, shadow_who);

	desc = "You are inside "+ LANG_ADDART(cage->real_short()) +
	    ", however, through the curved and gilded bars you see:\n";

	str = implode(explode(str, "\n")[..-2], " ");
	desc += break_string("\n" + str, 75, " } ") + "\n";
	str = "\n" + ENV(shadow_who)->exits_description();
	desc += break_string(str, 75, " } ");
	str = describe_outside();
	desc += break_string(str, 75, " } ");
    }

    /* Print out the view so far. */
    shadow_who->catch_tell(desc);

    /* Give a nice description of the combat that is going on. */
    shadow_who->describe_combat(filter(all_inventory(env), living));

    return 1;
}

public void
remove_object(void)
{
    temp = 1;
    cage->reset_cage();
    set_alarm(0.0, 0.0, &remove_cage_shadow());
    return shadow_who->remove_object();
}

/*
 * Masked function to capture linkdeath events.
 * See: sman /std/player_sec linkdeath_hook
 */
public void
linkdeath_hook(int link)
{
    if (!link)
	return shadow_who->linkdeath_hook(link);

    temp = 1;
    cage->reset_cage();
    set_alarm(0.0, 0.0, &remove_cage_shadow());
    shadow_who->linkdeath_hook(link);
}
