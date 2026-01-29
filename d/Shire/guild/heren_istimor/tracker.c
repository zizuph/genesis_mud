#pragma strict_types
#pragma save_binary
#pragma no_clone
#pragma no_inherit

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/guild/heren_istimor/heren_istimor.h"
#include <std.h>

inherit "/std/object";

#define TITLE   0
#define RANKING 1

// Prototypes
void test_members();

private mapping Members = ([]);


void
create_object()
{
    set_name("tracker");
    FIXEUID
    Members = restore_map(MEMBER_SAVE);
    if (!mappingp(Members))
	Members = ([]);

    // Check if the current members are all valid at the 1st of the month
    if (atoi(ctime(time())[8..9]) == 1)
    {
	set_alarm(15.0,0.0,&test_members());
    }
}

void
update_member(object member)
{
    string index, guild_title;
    int guild_ranking;

    index = member->query_real_name();
    if (member->query_wiz_level())
    {
	guild_ranking = -1;
	guild_title = member->query_title();
    }
    else
    {
	guild_ranking = member->query_heren_istimor_level();
	guild_title = member->query_guild_title_occ();
    }


    if (!pointerp(Members[index]))
    {
	Members[index] = ({guild_title, guild_ranking});
    }
    else
    {
	if (Members[index][TITLE] != guild_title)
	{
	    Members[index][TITLE] = guild_title;
	}
	if (Members[index][RANKING] != guild_ranking)
	{
	    Members[index][RANKING] = guild_ranking;
	}
    }

    save_map(Members,MEMBER_SAVE);
}

void
remove_member(object player)
{
    string index;

    index = player->query_real_name();
    if (!pointerp(Members[index]))
    {
	return;
    }
    Members = m_delete(Members, index);
    save_map(Members, MEMBER_SAVE);
}

void
test_members()
{
    string *names = m_indexes(Members);
    int index = -1;
    int size = sizeof(names);

    while (++index < size)
    {
	if (!SECURITY->exist_player(names[index]))
	{
	    Members = m_delete(Members,names[index]);
	}
    }
    save_map(Members, MEMBER_SAVE);
}

int
sort_names(string a, string b)
{
    if (Members[a][RANKING] < Members[b][RANKING])
	return 1;
    if (Members[a][RANKING] > Members[b][RANKING])
	return -1;

    return (a < b ? -1 : 1);
}

string
query_members(int flag)
{

    string *names = m_indexes(Members);
    string to_write;
    int i, sz;

    names = sort_array(names, "sort_names", TO);
    sz = sizeof(names);
    to_write = "Current members of the "+HEREN_ISTIMOR_GUILD_NAME+" are:\n\n";

    for (i = 0; i < sz;i++)
    {
	if (flag == 1 || (Members[names[i]][RANKING] != -1 &&
	    extract(names[i], -2) != "jr"))
	    if (Members[names[i]][RANKING] == -1)
		to_write += CAP(names[i]) + " "+Members[names[i]][TITLE]+".\n";
	    else
		to_write += CAP(names[i]) +" the "+ Members[names[i]][TITLE] +".\n";
    }

    return to_write;
}

string *
query_indexes()
{
    return m_indexes(Members);
}
