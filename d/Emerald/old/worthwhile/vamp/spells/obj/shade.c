inherit "/d/Emerald/std/emerald_monster";

#include <stdproperties.h>
#include <filter_funs.h>
#include <const.h>
#include <cmdparse.h>
#include <macros.h>
#include <composite.h>

public object owner;
public object *refuse_these = ({});

public void
set_owner(object o)
{
    owner = o;
}

public void
create_emerald_monster()
{
    set_name("shade");
    set_race_name("shade");
    set_gender(G_NEUTER);
    set_stats(({ 1, 80, 1, 80, 30, 30 }));

    add_prop(LIVE_I_NO_GENDER_DESC, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(LIVE_I_SEE_INVIS, 100);
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
}

// Remove the shade, dropping any items it's holding
public void
poof()
{
    object *dropped, *who = FILTER_IS_SEEN(this_object(),
        FILTER_CAN_SEE_IN_ROOM(all_inventory(environment())));

    dropped = filter(all_inventory(), not @ &->move(environment(), 1));
    
    if (sizeof(who))
    {
        if (sizeof(dropped))
        {
            // Wish there were some other way to initialize QCOMPDEAD
            FO_COMPOSITE_DEAD(dropped, who[0]);
            who->catch_msg("The shade fades away, leaving behind " + QCOMPDEAD +
                ".\n");
        }
        else
        {
            who->catch_tell("The shade fades away.\n");
        }
    }

    remove_object();
}

// Remove the shade if it's attacked
public void
attack_object(object ob)
{
    ::attack_object(ob);
    set_alarm(0.2, 0.0, poof);
}

// Remove the shade if it's attacked
public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    set_alarm(0.2, 0.0, poof);
}

public string
get_theshort(object ob)
{
    if (ob->query_prop(HEAP_I_IS))
    {
        if (ob->heap_size() == 1)
        {
            return "the " + ob->singular_short();
        }

        return "the " + ob->plural_short();
    }

    return "the " + ob->short();
}

public void
refuse()
{
    string desc, *descs;

    if (!sizeof(refuse_these -= ({ 0 })))
    {
        return;
    }

    // All this trouble to get the descriptions right
    descs = map(refuse_these, get_theshort);
    if (sizeof(descs) > 1)
    {
        descs[sizeof(descs) - 1] = "or " + descs[sizeof(descs) - 1];
        desc = implode(descs, ", ");
    }
    else
    {
        desc = descs[0];
    }

    write("The shade did not accept " + desc + ".\n");

    refuse_these = ({});
}

// Only accept items from the owner
public int
prevent_enter(object ob)
{
    if (this_player() && (this_player() != owner))
    {
        // We do a little delay in case multiple items are given at once
        set_alarm(0.0, 0.0, refuse);
        refuse_these += ({ ob });
        return 1;
    }

    return 0;
}

public void
deliver(object dest, object target)
{
    if (dest != environment())
    {
        move(environment(dest), 1);

        if (target)
        {
            tell_room(environment(), QCNAME(this_object()) +
                " materializes before " + QTNAME(target) + ".\n", ({ target }));
            target->catch_tell(query_Art_name(target) +
                " materializes before you.\n");
	}
        else
	{
            tell_room(environment(), QCNAME(this_object()) +
                " materializes.\n");
	}
    }

    if (target)
    {
        command("$give items to " + OB_NAME(target));
    }

    set_alarm(0.5, 0.0, poof);
}

public void
deliver_fail()
{
    if (owner)
    {
        command("$give items to " + OB_NAME(owner));
    }

    set_alarm(0.5, 0.0, poof);
}

public int
command_me(string str)
{
    string cmd, name, start;
    mixed *oblist;
    object *obs, target, dest;

    if (!strlen(str))
    {
        return 0;
    }

    obs = all_inventory(environment());
    if ((!parse_command(str, obs, "[the] %l %s", oblist, cmd) &&
         !parse_command(str, obs, "[the] %l", oblist)) ||
         !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
    {
        return 0;
    }

    if ((sizeof(oblist) != 1) || (oblist[0] != this_object()))
    {
        return 0;
    }

    if (!strlen(cmd))
    {
        notify_fail("Command the shade to do what?\n");
        return 0;
    }

    if (sscanf(cmd, "go to %s", name) == 1)
    {
        if (!(target = find_player(lower_case(name))))
        {
            if (name == "home")
            {
                start = this_player()->query_default_start_location() ||
                        this_player()->query_def_start();
                if (LOAD_ERR(start))
		{
                    dest = 0;
		}

                dest = find_object(start);
            }
            else
            {
                dest = 0;
            }
        }
        else
        {
            if (!this_player()->query_met(target))
            {
                target = dest = 0;
            }
            else
            {
                dest = environment(target);
            }
        }

        if (dest)
        {
            deliver(dest, target);
        }
        else
        {
            deliver_fail();
        }

        return 1;
    }

    write("Command the shade to do what?\n");
    return 1;
}

public void
init_living()
{
    ::init_living();
    add_action(command_me, "command");
}
