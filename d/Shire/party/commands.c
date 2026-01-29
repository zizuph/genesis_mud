//   These are commands which can be performed in any room of the party area
//   All code for the emote function was taken from Mrpr's Actors Club
//   with his permission.

#include "defs.h"
#include <options.h>

// Prototypes
static nomask int do_emote(string arg);
static nomask int do_help(string str);
static nomask int do_return(string str);
static nomask int do_invite(string str);
static nomask int do_boot(string str);
static nomask int do_end(string str);
static nomask mixed mk_item(object ob);
static nomask void tell_them(object ob, mixed arg);
static nomask string cat_string(mixed org, string what, object pl, int up);

void
boot_log(string text)
{
    setuid(); seteuid(getuid());
    write_file(PARTY_LOG+"boot",ctime(time()) + " " + text);
}

void
init_party_commands()
{
    add_action(do_emote, ":");
    add_action(do_emote, "emote");
    add_action (do_help,"help");
    add_action(do_invite,"invite");
    add_action(do_return,"return");
    if (PARTY_MASTER->query_is_host(TP->query_real_name()) ||
      PARTY_MASTER->query_is_guest_of_honour(TP->query_real_name()) ||
      TP->query_wiz_level())
    {
	add_action(do_boot,"boot");
	add_action(do_end,"end");
    }
}

static nomask int
do_emote(string arg)  
{
    object      pl, *pls;
    string      *args, *nms, oarg;
    int         i, sz, up;
    mapping     emap;

    pls = FILTER_LIVE(all_inventory(environment(TP))) - ({ TP });
    emap = mkmapping(pls, map(pls, mk_item));

    if (!stringp(arg))
	return notify_fail("Usage: @ <emote string>, emote string can "+
	  "contain names of present people enclosed in '|' characters, which "+
	  "then will be identified by their met/nonmet names to observers. e.g. "+
	  "'@ grins mischievously at |igneous|'\n");

    oarg = arg;
    args = explode(arg, "|");

    emap = map(emap, &cat_string(, args[0], 0, 0));
    if ((sz = sizeof(args)) > 1)
    {
	for (i = 1 ; i < sz ; i ++)
	{
	    nms = explode(args[i], " ");
	    up = nms[0] == lower_case(nms[0]) ? 0 : 1;
	    nms[0] = lower_case(nms[0]);
	    if (objectp((pl = present(nms[0], environment(TP)))))
	    {
		emap = map(emap, &cat_string(, "", pl, up));
		if (sizeof(nms) > 1)
		{
		    arg = implode(nms[1..], " ");
		    emap = map(emap, &cat_string(, arg, 0, up));
		}
	    }
	    else if (i % 2)
		return notify_fail("You can`t see " + nms[0] + " here.\n");
	    else
		emap = map(emap, &cat_string(, args[i], 0, up));

	}
    }

    map(emap, &tell_them(TP, ));

    pls = filter(m_indices(emap), query_interactive);

    setuid(); seteuid(getuid());
    write_file(PARTY_LOG + "emote", ctime(time()) + " "+
      TP->query_cap_name() +" emotes:  "+oarg+"\n");
    if (TP->query_option(OPT_ECHO))
	write("You emote: |" + capitalize(TP->query_real_name()) + "| " +
	  oarg + "\n");
    else 
	write("Ok.\n");
    return 1;       
}

static nomask mixed
mk_item(object ob)
{
    return ({ ob, "" });
}

static nomask string
cat_string(mixed org, string what, object pl, int up)
{
    if (objectp(pl))
	org[1] += (pl == org[0] ? (up == 1 ? "You" : "you") : (up == 1 ?
	    QCTNAME(pl) : QTNAME(pl)));
    else
	org[1] += what;
    return org;
}

static nomask void
tell_them(object ob, mixed arg)
{
    arg[0]->catch_msg(QCTNAME(ob) + " " + arg[1] + "\n");
}

static nomask int
do_help(string str)
{
    setuid(); seteuid(getuid());
    if (str == "party")
    {
	if (PARTY_MASTER->query_is_host(TP->query_real_name()) ||
	  PARTY_MASTER->query_is_guest_of_honour(TP->query_real_name()) ||
	  TP->query_wiz_level())
	{
	    HELP(advancedhelp);
	    return 1;
	}
	HELP(generalhelp);
	return 1;
    }
    if (str == "room")
    {
	switch(file_name(ENV(TP)))
	{
	case PARTY_DIR+"podium":
	    HELP(podiumhelp);
	    break;
	case PARTY_DIR + "costume_shop":
	    HELP(costumehelp);
	    break;
	default:
	    write("There is no help available for this room.\n");
	    break;
	}
	return 1;
    }
    return 0;
}

static nomask int
do_invite(string str)
{
    object player;

    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " who?\n");
        return 0;
    }
    
    str = lower_case(str);
    if (present(str,ENV(TP)))
	return 0;
    player = find_player(str);
    if (player)
    {
	if (!present("_shire_party_invite_",player))
	{
	    if (player->query_prop(LIVE_O_ROOM_BEFORE_PARTY))
	    {
		write("But "+CAP(str)+" is already at the party!\n");
		return 1;
	    }
	    setuid(); seteuid(getuid());
	    clone_object(INVITATION)->move(player,1);
	    write("You have just invited "+CAP(str)+" to the party.\n");
	    return 1;
	}
	else
	{
	    write(CAP(str)+" has already been invited to this party!\n");
	    return 1;
	}
    }
    write(CAP(str)+" was not found.\n");
    return 1;
}

static nomask int
do_return(string str)
{
    write("You bid everyone a fond farewell as you depart from the party.\n");
    say(QCTNAME(TP)+" bids you a fond farewell as "+HE_SHE(TP)+" departs "+
      "from the party.\n");
    if (!TP->query_prop(LIVE_O_ROOM_BEFORE_PARTY))
	TP->move_living("X",TP->query_default_start_location());
    else
    {
	TP->move_living("X",TP->query_prop(LIVE_O_ROOM_BEFORE_PARTY));
	TP->remove_prop(LIVE_O_ROOM_BEFORE_PARTY);
    }
    return 1;
}

static nomask int
do_boot(string str)
{
    object booted;
    if (interactive(booted = present(str,ENV(TP))) && booted != TP)
    {
	if (booted->query_wiz_level())
	{
	    write("You can't give wizards the boot.\n");
	    return 1;
	}
	TP->catch_msg("You give "+QTNAME(booted)+" the boot from the party.\n");
	say(QCTNAME(TP)+" points at "+QTNAME(booted)+" and a group of hobbits "+
	  "grab "+HIM_HER(booted)+" and promptly oust "+HIM_HER(booted)+
	  " from the party.\n",({TP,booted}));
	booted->catch_msg(QCTNAME(TP)+" has kicked you out from the party.\n");
	booted->add_prop(PARTY_BANISHED_PROP,1);
	if (!booted->query_prop(LIVE_O_ROOM_BEFORE_PARTY))
	    booted->move_living("M",booted->query_default_start_location());
	else
	{
	    booted->move_living("M",booted->query_prop(LIVE_O_ROOM_BEFORE_PARTY));
	    booted->remove_prop(LIVE_O_ROOM_BEFORE_PARTY);
	}
	boot_log(CAP(TP->query_real_name())+" gave "+CAP(booted->query_real_name())+
	  " the boot from the party.\n");
	return 1;
    }
    notify_fail("You find no "+str+" to give the boot to.\n");
    return 0;
}

static nomask int
do_end(string str)
{
    if (str != "party")
    {
	notify_fail("End what the party?\n");
	return 0;
    }
    write("With much regret you end the party.\n");
    say(QCTNAME(TP)+" decides to end the party.\n");
    PARTY_MASTER->end_party();
    return 1;
}
