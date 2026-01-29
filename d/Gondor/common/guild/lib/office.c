/*
 *	/d/Gondor/common/guild/lib/office.c
 *
 *	Function for the offices of the ranger companies.
 *
 *	Copyright (c) 1997 by Christian Markus
 *
 *	Coded by Olorin, February 1997
 *	using older code by Olorin.
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/guild/lib/members.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/ranger_defs.h"

static int     Company_Number;

static void set_company_number(int i) { Company_Number = i; }
public int  query_company_number() { return Company_Number; }

static string 
exa_poster()
{
    write("On the poster you read:\n\n");
    write(TO->print_member_list(Company_Number));
    return "";
}

static string 
list_council()
{
    return COUNCIL->query_council();
}

static string 
exa_plaque()
{
    write("You read the bronze plaque:\n" +
          "The Council of Rangers now consists of:\n" + 
	  list_council() +
	  BSN("To give your ideas and reports to the Council, "+
	  "talk to the Council members personally, or mail any of them in "+
	  "the post-office here in the guildhouse."));

    if (COUNCIL->query_election(Company_Number))
	write("\n  The Council of the Rangers has called the Rangers of " + 
	      COMPANIES[Company_Number] +"\n" +
	      "  to vote for a new Captain of the Rangers of " + 
	      COMPANIES[Company_Number] +"!\n" +
	      "    The candidates are: " + 
	      COUNCIL->query_candidates(Company_Number)+".\n\n" +
	      "  The Rangers of " + COMPANIES[Company_Number] +
	      " can vote here with 'vote <name>'\n\n");
    return "";
}

public void
create_office()
{
}

nomask void
create_gondor()
{
    add_prop(ROOM_I_INSIDE,1);

    add_item("plaque", exa_plaque);
    add_cmd_item("plaque", "read", exa_plaque);
    add_item(({"rangers","members","poster"}), exa_poster);
    add_cmd_item(({"rangers","members","poster"}), "read", exa_poster);
    add_item("council", list_council);

    create_office();
}

public int 
get_new_key(string str)
{
    if (!strlen(str) || ((str != "council") && (str != "council key")) )
	return 0;
    if (!COUNCIL->is_officer(TP->query_real_name()) && !TP->query_wiz_level()) 
	return 0;
    if(present("_council_key",TP))
    {
	NF("You already have a council key!\n");
	return 0;
    }
    FIX_EUID;
    clone_object(RANGER_DIR + "obj/councilkey")->move(TP);
    write("You get a key to the council-room.\n");
    return 1;
}

public int 
do_vote(string vote)
{
    string result;

    NF("To vote for one of the candidates, type 'vote <name>'!\n");
    if (!strlen(vote))
        return 0;

    result = COUNCIL->ranger_vote(TP, vote);
    if (stringp(result))
    {
        write(result);
        say(QCTNAME(TP) + " votes in the election for the Capitancy of the Rangers of " +
            COMPANIES[Company_Number] + ".\n");
        return 1;
    }
    return 0;
}

public void 
enter_inv(object ob, object from)
{
    string *elected;

    ::enter_inv(ob, from);

    if (!objectp(ob) || !objectp(from))
        return;

    if (!interactive(ob))
        return;

    elected = COUNCIL->query_elected();
    if (!sizeof(elected))
        return;

    if (member_array(ob->query_name(),elected) == -1)
        return;

    COUNCIL->make_captain(ob);
}
    
public void 
init()
{
    ::init();

    add_action(get_new_key, "get_key");
    add_action(get_new_key, "get");

    if (COUNCIL->query_election(Company_Number))
	add_action(do_vote, "vote");
}
