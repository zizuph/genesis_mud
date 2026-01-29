inherit "/std/creature";
inherit "/std/combat/unarmed";

#include "../guild.h"

#include <macros.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <ss_types.h>

static object back;
static int leave_alarm;

void
check_back()
{
    if (!back)
    {
    	setuid();
    	seteuid(getuid());
    	back = clone_object(KOT_EAGLE_DIR + "eagle_back");
        back->set_eagle(this_object());
    }
}

void
create_creature()
{
    set_race_name("eagle");
    set_name("eagle");
    set_adj("giant");
    set_long("A truly enormous eagle looms above you.  You notice a " +
        "large leather saddle, large enough for two, on its back.\n");

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_M_NO_ATTACK, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_stats(({ 200, 200, 200, 250, 250, 250 }));
 
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENSE, 100);
    set_skill(SS_AWARENESS, 100);

    check_back();

    setuid();
    seteuid(getuid());
    EAGLE_MANAGER->register_eagle(this_object());
}

public int
mount(string str)
{
    mixed *oblist;

    if (!strlen(str) ||
        !parse_command(str, all_inventory(environment(this_player())),
        "[the] %i", oblist) || !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail(capitalize(query_verb()) + " what?  Be more specific.\n");
        return 0;
    }

    if (!oblist[0]->kot_eagle_mount())
    {
        notify_fail("You can't seem to mount that.\n");
        return 0;
    }

    return 1;
}

public void
leave_area()
{
    move_living("into the sky", TEMP_EAGLE_ROOM, 1, 1);
    remove_object();
}

public void
start_leave()
{
    if (!leave_alarm)
    {
        leave_alarm = set_alarm(20.0, 0.0, leave_area);
    }
}

public void
stop_leave()
{
    if (leave_alarm)
    {
        remove_alarm(leave_alarm);
        leave_alarm = 0;
    }
}

public int
kot_eagle_mount()
{
    object leader;

    if (present(this_player(), this_object()))
    {
        write("You are already mounted on the eagle, though.\n");
        return 0;
    }

    if (!this_player()->query_kot_member() && 
        !this_player()->query_wiz_level() &&
        (!(leader = this_player()->query_leader()) ||
        !(leader->query_kot_member() || leader->query_wiz_level()) ||
        !present(leader, back)))
    {
        write("You try to mount the eagle, but it throws you off!\n");
        return 1;
    }

    check_back();

    say(({ METNAME + " mounts the giant eagle.\n",
           NONMETNAME + " mounts the giant eagle.\n",
           "" }));
    write("You mount the giant eagle.\n");
    this_player()->move_living("M", back, 1);
    say(({ METNAME + " mounts the giant eagle.\n",
           NONMETNAME + " mounts the giant eagle.\n",
           "" }));

    return 1;
}
    
void
init_living()
{
    ::init_living();
    add_action(mount, "mount");
}

public void
remove_object()
{
    back->remove_object();
    return 0;
}

public int
query_eagle_free()
{
    return back->query_eagle_free();
}

public int
query_eagle_occupied()
{
    return back->query_eagle_occupied();
}

public void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    if (file_name(env) != TEMP_EAGLE_ROOM)
    {
        start_leave();
    }
}

public int
query_kot_eagle()
{
    return 1;
}
