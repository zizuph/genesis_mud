/*
 * Helper object for spider web so that it will be possible to "fight"
 * it also when you are inside it.
 */

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

/*
 * Function name: create_object
 * Description:   Initialize things we need, like name of the web
 */
void
create_object()
{
    set_name(({ "web", "_inside_web_" }));
    set_adj("sticky");
    set_long("@@web_desc@@");
    set_no_show_composite(1);
    add_prop(OBJ_M_NO_GET, 1);
}

/*
 * Forward most stuff to the 'real' web.
 */
string web_desc() { return environment()->web_desc(); }
mixed query_weapon() { return environment()->query_weapon(); }
string query_the_name() { return environment()->query_the_name(); }
string query_objective() { return environment()->query_objective(); }
string query_possessive() { return environment()->query_possessive(); }
string query_pronoun() { return environment()->query_pronoun(); }
mixed *hit_me(int wcpen, int dt, object attacker, int aid)
{
    return environment()->hit_me(wcpen, dt, attacker, aid);
}
int query_hp() { return environment()->query_hp(); }
int query_max_hp() { return environment()->query_max_hp(); }
void do_die(object killer) { environment()->do_die(killer); }
int query_ghost() { return environment()->query_ghost(); }

/*
 * Function name: init
 * Description:   Add commands specific to the web inside
 */
void
init()
{
    ::init();
    add_action("do_cut", "cut");
}

/*
 * Function name: do_cut
 * Description:   Start cutting up the web.  Called when the player says
 *                'cut'.
 * Arguments:     arg - the rest of the command given
 * Returns:       0 - the command was not executed
 *                1 - the command was executed
 */
int
do_cut(string arg)
{
    notify_fail("Cut what?\n");
    if (!id(arg))
	return 0;
    if (environment(this_player()) != environment())
	return 0;
    write("You attack the web.\n");
    say(QCTNAME(this_player()) + " attacks the web.\n");
    this_player()->attack_object(this_object());
    return 1;
}
