/*
 * Lord Board for the Mercenaries of Sparkle
 *
 * Lunatari
 */
inherit "/d/Sparkle/guilds/mercs/obj/custom_std_board";

#include "../merc.h"

public int query_custom_board() { return 1; }

public string *query_all_wizard_names()
{
    string *wiznames = ({ });
    string wizname;
    mixed *head = query_headers(); 
    int num_notes = query_num_messages();
    int i = 0;

    for (i = 0; i < num_notes; i++)
    {
        wizname = lower_case(implode(explode(
	head[i][0][46..56], " "), ""));

        if (SECURITY->query_wiz_level(wizname))
	    wiznames += ({ capitalize(wizname) });
    }

    return wiznames;
}
        
public string *query_allowed_names(string name)
{
    string *names = ({ });
    string lord;

    name = capitalize(name);

    if (MCREST->query_lord_status(name) >= MERC_STATUS_LORD &&
        MCREST->query_members_lord(name) == name)
    {
	names = MCREST->query_followers(name);
	names += ({ name });
    }
    else
    {
	lord = MCREST->query_members_lord(name);
	names = MCREST->query_followers(lord);
        names += ({ lord });
    }

    if (member_array(name, names) == -1)
	names += ({ name });

    names += query_all_wizard_names();

    if (!sizeof(names))
	return ({ name });

    return names;
}

public void
create_board()
{
    seteuid(getuid(this_object()));
    set_long("Mercenaries Lords may share information with their "+
	"followers here.\n");
    set_board_name(MLORD_BOARD);
    set_num_notes(98);
    set_silent(1);
    set_show_lvl(1);
    set_no_report(0);
    set_keep_discarded(0);
}

int block_writer()
{
    string name = TP->query_name();

    if (MCREST->query_lord_status(name) >= MERC_STATUS_LORD ||
	MCREST->query_lord_status(MCREST->query_members_lord(name)) >=
	MERC_STATUS_LORD || TP->query_wiz_level())
	return 0;

    return 1;
}	

int block_reader(int note)
{
    string *names = ({ });
    string lord;

    if (TP->query_wiz_level())
	return 0;

    if (SECURITY->query_wiz_level(query_author(note)))
	return 0;

    if (MCREST->query_lord_status(TP->query_name()) >= MERC_STATUS_LORD &&
        MCREST->query_members_lord(TP->query_name()) == TP->query_name())
    {
	names = MCREST->query_followers(TP->query_name());
	names += ({ TP->query_name() });
    }
    else
    {
	lord = MCREST->query_members_lord(TP->query_name());
	names = MCREST->query_followers(lord);
        names += ({ lord });
    }

    if (!sizeof(names))
	return 1;

    if (member_array(capitalize(query_author(note)), names) == -1)
	return 1;

    return 0;
}
