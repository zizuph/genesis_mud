#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/guild/gondor/no_theft";

#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/punish_defs.h"

#define DEBUG 0

public int     do_gather(string str);
public string  read_poster();
public string  exa_feathers();
public string  exa_floor();
public string  exa_pigeons();
public string  long_func();
public void    give_message(string msg, object tp, object ranger);
public void    reset_room();

private int    Called,
               Feathers = 20 + random(21);

void
create_gondor()
{
    set_short("the pigeon coop of the Gondorian Rangers");
    set_long(long_func);
    add_item("ladder", "It leads down through a hatch in the floor.\n");
    add_item("poster", read_poster());
    add_cmd_item("poster", "read", read_poster());
    add_item("pigeons", exa_pigeons);
    add_item( ({ "floor", "ground", }), exa_floor);
    add_item( ({ "feather", "feathers", }), exa_feathers);
    add_prop(ROOM_I_INSIDE,0);
    add_prop(ROOM_M_NO_STEAL, no_theft);
    add_exit(RANGER_GON_DIR + "uphall", "down", 0, 2);

    reset_room();
}

public string
read_poster()
{
    return "The poster reads:\n"+
        "If there are fresh pigeons here, you may send messages to all\n"+
        "Rangers, or Rangers of one company with the command\n"+
        "'call <all/company> with <message>'. It will only work as long\n"+
        "as there are fresh pigeons available.\n";
}

public string
exa_pigeons()
{
    if (Called > 20)
        return "There are only a few white carrier pigeons here, and "
          + "they look tired.\n";
    else 
        return "There are several white carrier pigeons here, "
          + "and they look rested.\n";
}

public string
long_func()
{ 
    string str =
        "The odour of birds is strong here, as this is the coop where "
      + "the Rangers carrier pigeons stay when not carrying messages. There "
      + "is some traffic of pigeons here, landing or taking off up through "
      + "the open ceiling. A poster is on the wall.";

    if (Called > 20)
        str += " Only a couple of tired pigeons are here now, resting "
            +  "before being summoned by a whistle again.";
    else
        str += " There are several fresh and rested carrier pigeons sitting "
            +  "here, ready to be sent with messages to the adventuring "
            +  "Rangers.";
    str += " A ladder leads down through a hatch in the floor.";
    return BSN(str);
}

int
try_get(string str)
{
    if (str == "pigeon" || str == "pigeons" || str == "carrier pigeon")
    {
        write("You can't take the pigeons here. You must summon your own "
          + "as all rangers do, or buy one in the post-offices.\n");
        return 1;
    }
    return 0;
}

int
rfilter(object pl, string comp)
{
    if (comp == "all")
        return ((pl->query_guild_name_occ() == "Gondorian Rangers Guild")
           && (pl != TP) && ((pl->query_real_name() == "elessar")
           || !pl->query_wiz_level()));
    else
        return ((pl->query_guild_name_occ() == "Gondorian Rangers Guild")
           && (pl->query_company() == comp) && (pl != TP) 
           && ((pl->query_real_name() == "elessar") 
           || !pl->query_wiz_level()));
}

public int
call_all(string str)
{
    float   delay;
    int     i,
            s;
    string  msg,
            who;
    object *rlist; 

    if (!IS_RANGER(TP) && !TP->query_wiz_level())
    {
        write("The pigeons do not seem to want to obey you.\n");
        return 1;
    }
    if (TP->query_skill(SS_PUNISHMENT) == NOACCESS) 
    {
        write("The pigeons won't obey you because of your disobedience "
          +   "to the Council of Rangers.\n");
        return 1;
    }
    if (!strlen(str))
    {
        write("You can 'call <all> with <msg>' or "
          +   "'call <company> with <msg>'.\n");
        return 1;
    }
    if (Called > 20) 
    {
        write("There are no fresh and rested pigeons here.\n"
            + "You will have to wait.\n");
        return 1;
    }
    sscanf(str, "%s with %s", who, msg);
  
    if (!strlen(who))
        who = "all";
    else 
    {
	who = LOW(who);
        if (who == "north" || who == "the north")
            who = "the North";
        else if (who == "gondor")
            who = "Gondor";
        else if (who == "ithilien")
            who = "Ithilien";
        else 
            who = "all";
    }
    if (!strlen(msg))
    {
        write("You must give a short message to send too!\n");
        return 1;
    }
    rlist = filter(users(), &rfilter(,who));
    if (!sizeof(rlist))
    {
        write("There are no Rangers logged on.\n");
        return 1;
    }
    Called +=  sizeof(rlist);
    
    for (i = 0, s = sizeof(rlist); i < s; i++)
    {
	delay = 20.0;
	if (ENV(rlist[i])->query_domain() != "Gondor")
	    delay = 40.0;
	set_alarm(delay + rnd() * delay, 0.0, &give_message(msg, TP, rlist[i]));
    }
    write(BSN("You write '"+msg+"' on "+sizeof(rlist)+" notes, and fasten "
      +	"each to the leg of a carrier pigeon, and send it off to "
      + "locate Rangers of " + who + " with your message."));
    say(QCTNAME(TP)+" writes "+sizeof(rlist)+" notes, and sends off a "
      + "pigeon with each, to locate Rangers somewhere in the world.\n", TP);
    return 1;
}

private void
mkmsg(string msg, object pl, object tp)
{
    object  note;
    seteuid(getuid(TO));
    note = clone_object(RANGER_DIR+"obj/message");
    note->set_message(msg+"\n");
    note->set_sender(tp->query_name());
    pl->catch_msg(BSN("A white carrier pigeon descends from the sky, lands "+
		    "on your shoulder and gives you a message."));
    note->move(pl, 1);
    pl->catch_msg(BS("The pigeon flaps its wings, and flies away into the sky.\n"));
    tell_room(TO, "A pigeon returns, having delivered the message to "
	      + pl->query_name()+".\n");
    return;
}

public void
give_message(string msg, object tp, object ranger)
{
    Called--;
    if (objectp(ranger))
    {
	if (!ENV(ranger)->query_prop(ROOM_I_INSIDE))
	    mkmsg(msg, ranger, tp);
	else 
	    tell_room(TO, "A pigeon returns, unable to find "
		      + ranger->query_name()+".\n");
    }
    else 
	tell_room(TO,"A pigeon returns, unable to find its target.\n");
    return;
}

int
query_no_called()
{
    return Called;
}

void
init()
{
    ::init();
    add_action(try_get,   "get");
    add_action(try_get,   "take");
    add_action(try_get,   "pick");
    add_action(call_all,  "call");
    add_action(do_gather, "gather");
    add_action(do_gather, "collect");
}

public void
reset_room()
{
    Called = 0;
    Feathers = 20 + random(21);
}

public string
exa_floor()
{
    string  desc = "The floor is made from wooden boards.";

    switch (Feathers)
    {
    default:
    case 20 .. 100:
	desc += " On them, many feathers are lying around, "
	    + "probably lost by the pigeons here.";
	break;
    case 4 .. 19:
	desc += " Some feathers are lying around on the "
	    + "ground.";
	break;
    case 2 .. 3:
	desc += " There are " + LANG_WNUM(Feathers)
	    + " lying on the ground.";
	break;
    case 1:
	desc += " There is one white feather lying on the ground.";
	break;
    case 0:
	desc += " Strangely, not a single feather is lying " 
	    + "around on the ground. Someone must have collected "
	    + "them all.";
	break;
    }

    return BSN(desc);
}

public string
exa_feathers()
{
    string  desc = " You could try to collect them.";

    switch (Feathers)
    {
    default:
    case 20 .. 100:
	desc = "Many feathers are lying around, "
	    + "probably lost by the pigeons here." + desc;
	break;
    case 4 .. 19:
	desc = "Some feathers are lying around on the "
	    + "ground." + desc;
	break;
    case 2 .. 3:
	desc = "There are " + LANG_WNUM(Feathers)
	    + " lying on the ground." + desc;
	break;
    case 1:
	desc = "There is one white feather lying on the ground. " +
	    "You could try to collect it.";
	break;
    case 0:
	desc = "Strangely, not a single feather is lying " 
	    + "around on the ground. Someone must have collected "
	    + "them all.";
	break;
    }

    return BSN(desc);
}

public int
do_gather(string str)
{
    int     n;
    object  feather;

    if (!strlen(str) || 
	((str != "feather") && (str != "feathers")))
    {
	NFN(CAP(query_verb()) + " what?");
	return 0;
    }

    if (!Feathers)
    {
	write("There are no feathers here!\n");
	return 1;
    }

    n = 2 + random(TP->query_skill(SS_HUNTING) / 5);
    if (n > Feathers)
	n = Feathers;

    feather = clone_object(OBJ_DIR + "feather");
    feather->set_heap_size(n);
    if (feather->move(TP))
    {
	write("You cannot carry the " + feather->short() +
	      ", so you drop them again!\n");
	feather->remove_object();
    }
    else
    {
	write("You pick up " + feather->short() +
	      " from the ground.\n");
	Feathers -= n;
    }

    return 1;
}
