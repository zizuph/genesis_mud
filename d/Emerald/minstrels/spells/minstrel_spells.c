inherit "/std/object";
inherit "/d/Genesis/newmagic/spellcasting";

#include <macros.h>
#include <stdproperties.h>

public void
create_object()
{
    if (!IS_CLONE)
    {
        return;
    }
    
    set_name("_minstrel_spells");

    set_no_show();
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_M_NO_DROP, 1);

    add_spell("/d/Emerald/minstrels/spells/soothe");
}

public void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    add_spell_object(env);
}

public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    remove_spell_object(env);
}

nomask public int
start_spell_fail(string verb, string arg)
{
    object *tools, instrument;
    string cmd = query_verb();
    mixed m;
    int i;

    if ((cmd == "play") || (cmd == "perform"))
    {
        tools = this_player()->query_tool(-1);
	for (i = 0; i < sizeof(tools); i++)
	{
	    if (tools[i]->query_minstrel_instrument())
	    {
	        instrument = tools[i];
		break;
	    }
	}

	if (!instrument)
	{
            write("You cannot " + cmd +
                " if you are not holding an instrument.\n");
	    return 1;
	}
    }

    if (cmd != "play")
    {
        if (m = this_player()->query_prop(LIVE_M_MOUTH_BLOCKED))
	{
            write((stringp(m) ?
                m : "You cannot sing with your mouth blocked.\n"));
	    return 1;
	}
    }

    if (::start_spell_fail(verb, arg))
    {
        return 1;
    }

    if (instrument)
    {
        instrument->start_spell(this_object(), verb);
    }

    return 0;
}

public int
cast(string str)
{
    object ob;
    string spell, arg;

    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!sscanf(str, "%s %s", spell, arg))
    {
        spell = str;
    }

    if ((ob = this_player()->find_spell(spell)) && (ob == this_object()))
    {    
        this_player()->start_spell(spell, arg, ob);
        return 1;
    }

    dump_array(spell);
    dump_array(ob);
    write("Here\n");
    notify_fail(capitalize(query_verb()) + " what?\n");
    return 0;
}

public void
init()
{
    ::init();

    add_action(cast, "sing");
    add_action(cast, "play");
    add_action(cast, "perform");
}

