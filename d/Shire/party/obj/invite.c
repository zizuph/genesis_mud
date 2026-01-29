inherit "/std/object";

#include "../defs.h"
#include <language.h>

string hosts = PARTY_MASTER->query_hosts();
string reason = PARTY_MASTER->query_reason();
string for_whom = PARTY_MASTER->query_party_for();

//  Prototypes
string my_long();

void
create_object()
{
    set_name("invitation");
    add_name("_shire_party_invite_");
    set_short("eloquent party invitation");
    set_long("@@my_long@@");

    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_M_NO_STEAL,1);
    add_prop(OBJ_M_NO_DROP,1);
    add_prop(OBJ_M_NO_GIVE,1);

// 30 min
    set_alarm(1800.0,0.0,remove_object);
}

string
my_long()
{
    return "The invitation is written in a flowing script "+
    "that reads:\n\n" +
    "Your presence is requested at " + hosts + "'s party in " +
    "order to celebrate " + (stringp(for_whom) ? for_whom + "'s " : "") +
    reason + ".\n" + 
    "If you ready to join the celebration, then it's <party time>!\n\n" + 
    "You will have 30 minutes. After that, the invitation will be recalled.\n\n" +
    "If you decide to join the party, there are a few things to keep in mind:\n" +
    "  > At the celebration, do <help party> to see what commands are\n" +
    "    available to you.\n" +
    "  > Horses, ponies, steeds, etc. are not allowed. You will\n" +
    "    need to return or stable the animals before joining.\n" +
    "  > Bad behaviour is not tolerated. You will be removed from the\n" +
    "    party.\n" +
    "  > When you are done and want to leave the party, you may <return>.\n" +
    "  > You can host a party anytime, too. Visit the hobbit in the quiet\n" +
    "    alcove, in the back of the Adventuresome Hobbit Guild, in\n" + 
    "    Michel Delving. They are always happy to help you set up a party.\n"; 

/*
There are some teleportation runes with the words 'party time'" +
    "cover the bottom of " + LANG_THESHORT(TO) + ".\n" + */
    ;
}

void
enter_env(object env, object from)
{
    ::enter_env(env,from);
    if (!interactive(env))
	return;
    env->catch_tell("A hobbit comes running up to you and says:  I have "+
      "an invitation to " + LANG_POSS(hosts) + " party for you, to celebrate "+
      (stringp(for_whom) ? LANG_POSS(for_whom) + " " : "") + reason + ".\n"+
      "The hobbit then hands you "+LANG_ASHORT(TO)+" and runs "+
      "off to deliver the rest of his invitations to the rest of the "+
      "party-goers.\n");
}

void
init()
{
    ::init();
    add_action("party","party");
    add_action("read","read");
}

int
party(string str)
{
    if (str != "time" && str != "down")
    {
	notify_fail("Party what?  What's that phrase?  Party down?  "+
	  "No no it's Party time!\n");
	return 0;
    }
        if (str == "down")
    {
	notify_fail("But your not at the party yet!!  Try 'party time' "+
	  "to get there.\n");
	return 0;
    }
    if (TP->query_attack())
    {
	notify_fail("You are to busy fighting to go to the party.\n");
	return 0;
    }
    write("Time to get down and party!\n");
    TP->move_living("off to a party",PARTY_START);
    set_alarm(0.0,0.0,remove_object);
    return 1;
}

int
read(string str)
{
    if (str == "invitation")
    {
	write(my_long());
	return 1;
    }
    NF(CAP(query_verb()) + " what?\n");
    return 0;
}
