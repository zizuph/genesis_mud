#include "../wizday.h"
#include "spells.h"
#include <stdproperties.h>

inherit "/std/object";
inherit "/d/Genesis/newmagic/spellcasting";

void
create_object()
{
    set_name("spell_obj");
    set_short("spell object");
    set_long("You'll never see this!\n");
    set_no_show();

    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_VALUE);

    add_spell(WIZDAY_SPELL_DIR + "antimagic");
    add_spell(WIZDAY_SPELL_DIR + "blur");
    add_spell(WIZDAY_SPELL_DIR + "curse");
    add_spell(WIZDAY_SPELL_DIR + "flamewave");
    add_spell(WIZDAY_SPELL_DIR + "icebolt");
    add_spell(WIZDAY_SPELL_DIR + "shapeshift");
    add_spell(WIZDAY_SPELL_DIR + "jolt");
    add_spell(WIZDAY_SPELL_DIR + "tell");
}

void
enter_env(object env, object from)
{
    if (env->query_wiz_level || env->query_xx_player())
	add_spell_object(env);
    ::enter_env(env, from);
}

void
leave_env(object from, object to) 
{
    remove_spell_object(from);
    ::leave_env(from, to);
}

// Remove this when mudlib is fixed.
public int
start_spell_fail(string verb, string arg)
{
    object spell;

    gArg = arg;
    gCaster = this_player();
    gTargets = ({});

    if (!(spell = get_spell_object(verb)))
    {
	return 1;
    }

    /* I hate to have to do this here and again when the target is
     * acquired.  The problem is that I need to get information from
     * the spell to do the targeting, so I need to do setup for that.
     * I also want to allow the spell to be configured depending on
     * the targets, so I need to do setup for that as well.  The
     * alternative to repeating setup is to have a separate config
     * hook that only gets called after targets are found.  For now
     * I'm leaning toward repeating setup.
     */
    if (spell->do_spell_setup(0))
    {
	return 1;
    }

    if (spell->query_spell_pretarget())
    {
	gTargets = spell->target_spell(gCaster, arg);

	if (!sizeof(gTargets))
	{
	    return 1;
	}
    }

    if (spell->do_spell_setup(gCaster, gTargets, arg))
    {
	return 1;
    }

    return spell->concentrate_spell(gCaster, gTargets, arg);
}
