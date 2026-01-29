inherit "/std/object";
#include "/d/Shire/guild/claws/claw_defs.h"
#include <stdproperties.h>
#define THRONE_SAVE       ("/d/Shire/guild/claws/obj/throne_save")

static int     inited;
public mapping  members = ([ ]);
object crown;

void
init_throne()
{
    if (inited)
        return;

    restore_object(THRONE_SAVE);

    if (member_array(CAPTAIN, m_values(members)) == -1)
    {
        crown = clone_object("/d/Shire/guild/claws/obj/crown");
        crown->move(ONE_OF_LIST(RANDOM_ROOMS));
        return;
    }
    inited = 1;
}

void
create_object()
{
	set_name("throne");
	set_short("throne");
	set_long("The throne of the ruling Captain!\n"+
		"This is where the Captain of the Black Claws makes all \n"+
		"his vital decitions. It os covered with blood!\n");

	add_prop(OBJ_M_NO_GET, 1);
	add_prop(OBJ_M_NO_GIVE, 1);
   setuid();
   seteuid(getuid());
   set_alarm(0.0, 0.0, init_throne);

   
}

int
add_member(string name, int rank)
{
    if (!strlen(name))
        return 0;
    if (rank < 1)
        return 0;

    if (members[name] > 0)
        return -1;

    members[name] = rank;
    save_object(THRONE_SAVE);
    return 1;
}

int
remove_member(string name)
{
    if (!strlen(name))
        return -1;

    if (member_array(name, m_indexes(members)) < 0)
        return 0;

    members = m_delete(members, name);
    save_object(THRONE_SAVE);
    return 1;
}

int
query_rank(string name)
{
    if (!strlen(name))
        return -1;

    return members[name];
}

int
make_captain(string name)
{
    if (!strlen(name))
        return -1;

    if (member_array(CAPTAIN, m_values(members)) > -1)
        return 0;

    members[name] = CAPTAIN;
    find_player(name)->set_claw_rank(CAPTAIN);
    save_object(THRONE_SAVE);
    return 1;
}

int
query_captain(mixed name)
{
    int     n;
    if (!stringp(name))
    {
        n = member_array(CAPTAIN, m_values(members));
        if (n >= 0)
            return m_indexes(members)[n];
        else
            return -1;
    }
    else if (stringp(name))
    {
        if (member_array(name, m_indexes(members)) == -1)
            return -1;
        else if (members[name] != CAPTAIN)
            return 0;
        else
            return 1;
    }
}

int
change_rank(string name, int rank)
{
    if (!strlen(name))
        return -1;

    if (member_array(name, m_indexes(members)) == -1)
        return -2;

    members[name] = rank;
    save_object(THRONE_SAVE);
    return 1;
}
 
