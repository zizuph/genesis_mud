/* counmain.c: Council chamber. Serpine, 4-25-95.
   
   -Added tail functionality to check joins/quits
     Decius, 99/08/28
*/

#pragma save_binary

inherit "/d/Cirath/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"
#include <std.h>

#define PENDHOLD PSION_ROOM+"MAINHOLD"
#define PENDSAVE save_object(PENDHOLD)

#define MORE(x, y, z) CO("/std/board/board_more")->more(x, y, z)
#define LOG(a, b, c, d) write_file(MEM_FILE(a), ctime(time()) + "\n" + \
                        sprintf("%=-25s %=-50s\n\n", CAP(b) + \
                        " by " + CAP(c->query_real_name()), CAP(d)))
#define TPISCOUNCIL (QUERY_COUN_MEMB(lower_case(TP->query_name())) > -1)
#define LCQN(x)     lower_case(x->query_name())

int permit_entry, done_expel;
string pendingpunish, pendingvictim, pendingreason, *punishvoters;

void
reset_room()
{
    if (!present("board", TO))
                clone_object(PSION_ROOM+"counbord.c")->move(TO);
    bring_room_mob("cilops", PSION_NPC+"cylops.c", 1);
    if(done_expel > 0)
        done_expel = (done_expel - 1);   
}

int
query_prevent_snoop() { return 1; }

int
list_brutus_killers()
{
    string *pests, str;
    int i;
 
    setuid(); 
    seteuid(getuid());

    NF("You aren't a council member!\n");
    if (!TPISCOUNCIL && !IS_WIZ(TP) && !CIR_WIZ(TP)) return 0;
 
    NF("Divide by cucumber error, reinstall universe and reboot!\n");
    call_other(PSION_NPC + "brutus.c", "return_killers"); 
    pests = sort_array(map(call_other(PSION_NPC + "brutus.c", "return_killers"), capitalize));
 
    NF("Nobody has dared attack Brutus lately.\n");
    if (!sizeof(pests)) return 0;
    TP->catch_msg("\nThose foolish enough to attack Brutus include:\n"+
    "=== == =\n");
    str = "";
 
    for (i = 0; i < sizeof(pests); i++)
      str += explode(pests[i], ".")[0] + "\n";
 
    TP->catch_msg(sprintf("%-#60s\n", str));
    TP->catch_msg("=== == =\n\n");
    return 1;
}
 
int
forgive_brutus_killers(string str)
{
 
    NF("You aren't a council member!\n");
    if (!TPISCOUNCIL) return 0;
 
    TP->catch_msg((call_other(PSION_NPC+"brutus.c",
                   "remove_attacker", lower_case(str)))+"\n");
 
    return 1;
}

int
create_room()
{
    restore_object(PENDHOLD);
    done_expel = 0;
    if (!permit_entry) permit_entry = 0;
    if (!pendingpunish) pendingpunish = "";
    if (!pendingvictim) pendingvictim = "";
    if (!pendingreason) pendingreason = "";
    if (!punishvoters) punishvoters = ({});


    set_short("overseer sanctum");
    set_long("This stone chamber is cold and hard, like the ones who "
            +"use it: The Overseers of the Gladiators. "
            +"Shelves with records line one wall, while near "
            +"another is the nest of a gigantic insect, but otherwise "
            +"there is little adornment.\n");

    INSIDE

    add_exit(PSION_ROOM+"counentr.c", "south", 0, 1);

    add_item(({ "shelf", "shelves", "records", "record" }),
        "There are records on the comings and goings of the "+
        "Gladiators of Athas.\n");
    add_item("nest", "It is made of discarded refuse found in the "+
        "guild, including broken weapons, discarded betting chits, and "+
        "even the occasional skeleton.\n");
    add_item(({ "hexagon"}), "Its solidly built and rather ugly "+
        "but serves its purpose well.\n");
    add_item(({"scratch", "scratches"}), "They seem to spell out the "+
        "words 'help powers'. What could it mean?\n");

    LOAD_ERR(PSION_NPC + "brutus.c");
    reset_room();
}

int
query_can_enter_over(string who)
{
    if((present("cilops", TO)) && (!(QUERY_COUN_MEMB(who)>-1))
        && (!permit_entry)) return 0;
    return 1;
}

init()
{
    ::init();

    	add_action("appoint", "appoint");
    	add_action("bar", "bar");
    	add_action("list_brutus_killers", "brutkill");
    	add_action("forgive_brutus_killers", "brutforgive");
    	add_action("check", "check");
    	add_action("demote", "demote");
    	add_action("expel", "expel");
    	add_action("forgive", "forgive");
    	add_action("permit", "permit");
    	add_action("pet", "pet");
    	add_action("punish", "punish");
    	add_action("regret", "regret");
    	add_action("help", "help");
      	add_action("demote","gdemote");
}

int
appoint(string str)
{
    object who, amul;
    string *whowhat1=explode(str," ");
    int theslot1;

    NF("Usage:  appoint <playername> <Position>\n"+
       "        I.E. 'appoint rikus War'\n");
    if (sizeof(whowhat1)<2) return 0;

    NF ("Only the High Overseer may appoint Lesser Overseers.\n");
//    if (!(QUERY_COUN_MEMB(LCQN(TP)) == 0)) return 0;

    NF ("That is not a available position.\n");
    theslot1=member_array(whowhat1[1],PSION_COUN_SLOTS);
    if (theslot1<0) return 0;

    NF ("That position is taken already.\n");
    if (!((((call_other(MANAGER,"dump_overseer_array"))[theslot1+1])==0)))
        return 0;

    NF ("The person to be appointed must be present!\n");
    if (!(who=present(whowhat1[0], TO))) return 0;

    NF ("To late! They are an Overseer already!\n");
    if (QUERY_COUN_MEMB(LCQN(who)) > -1) return 0;

    NF ("IDIOT! Only Gladiators may be Overseers!\n");
    if (!IS_MEMBER(who)) return 0;

    ADD_COUNCIL(str);
    tell_room(TO, QCTNAME(who)+" is now a Lesser Overseer!\n");
    while (amul = present(AMUL_ID, who)) amul->remove_object();
    call_other(MANAGER, "give_amulet", who);
    
    return 1;    
}

int
bar(string str)
{
    NF ("You aren't an Overseer!\n");
    if (!TPISCOUNCIL) return 0;

    NF("Usage:  bar <playername>\n");
    if (!strlen(str)) return 0;

    NF("No such player.\n");
    if (!("secure/master"->exist_player(str = lower_case(str))))
        return 0;

    ADD_PUNISHMENT(BAR, str);
    write("Ok.\n");
    return 1;
}

int
check(string str)
{
    int *values, pun, i, flag;
    string path, *indices;
    mapping punishments;

    NF ("You aren't an Overseer!\n");
//    if (!TPISCOUNCIL) return 0;

    NF ("Check what?\n");
    if (!strlen(str)) return 0;

    punishments = call_other(MANAGER, "get_punishments");
    indices = m_indexes(punishments);
    values = m_values(punishments);

    seteuid(getuid());

    switch(str)
    {
        case "joins":      tail(JOIN_LOG); return 1;
        case "joins more": MORE(JOIN_LOG, 1, 0); return 1;  
        case "quits":      tail(QUIT_LOG); return 1;
        case "quits more": MORE(QUIT_LOG, 1, 0); return 1;
        case "bar":        pun = BAR;     break;
        case "expel":      pun = EXPEL;   break;
        default: 
            NF ("Check who?\n");
            if (file_size(path = MEM_FILE(str)) < 0) return 0;
            MORE(path, 1, 0);
            return 1;
    }

    for (i = 0, flag = 0; i < sizeof(values); i++)
    if (values[i] & pun)
    {
        write(CAP(indices[i]) + "\n");
        flag = 1;
    }

    NF ("Nobody punished in that way.\n");  
    if (!flag) return 0;
    return 1;
}

int
expel(string str)
{
    string who, why;
    object ob;

    NF ("You aren't an Counsel member!\n");
    if (!TPISCOUNCIL) return 0;

    NF("Usage:  expel <playername> <explanation>\n");
    if (sscanf(str, "%s %s", who, why) != 2) return 0;

    NF(CAP(who) + " not found among members.\n");
    if (file_size(MEM_FILE(who)) < 0) return 0;

    NF("You can't expel an Overseer!\n");
    if (QUERY_COUN_MEMB(lower_case(who)) > -1) return 0;

    NF("Somebody was just recently expelled, you will have to wait.\n");
    if (done_expel > 0) return 0;

    if ((pendingpunish == "expel") && (pendingvictim == who))
    {
        NF("You have already voted to do so.\n");
        if (member_array(LCQN(TP), punishvoters) > -1) return 0;

        punishvoters = punishvoters + ({LCQN(TP)});
        write("You vote for the expulsion of "+CAP(who)+".\n");
        say(QCTNAME(TP)+" votes for the expulsion of "+CAP(who)+".\n");

        PENDSAVE;

      if (sizeof(punishvoters) < 0) return 1;

        punishvoters = ({});
        pendingpunish = "";
        done_expel = 6;

        LOG(who, "expelled", TP, pendingreason);
        tell_room(E(TP), CAP(who)+" has been expelled.\n");

        if ((ob = find_player(who)) && IS_MEMBER(ob))
        {
            ob->catch_msg("You have been expelled from the Gladiators.\n");
        }
        ADD_PUNISHMENT(EXPEL, who);
        PENDSAVE;
    }

    NF ("Only the High Overseer may start expulsion proceedings.\n");
    if (!(QUERY_COUN_MEMB(LCQN(TP)) == 0)) return 0;

    punishvoters = ({LCQN(TP)});
    pendingreason = why;
    pendingvictim = who;
    pendingpunish = "expel";
 
    write("You begin expulsion proceedings against "+CAP(who)+".\n");
    say(QCTNAME(TP)+" begins expulsions proceedings against "
        + CAP(who) + ".\n");
    PENDSAVE;
    return 1;
}

int
demote(string str)
{
    string who;
    object ob;

/*
    NF ("You aren't an Overseer!\n");
    if (!TPISCOUNCIL) return 0;
*/

    NF("Usage:  demote <playername>\n");
    if (!strlen(str)) return 0;

    who = lower_case(str);

    NF("You can't demote a non-Overseer!\n");
    if (!(QUERY_COUN_MEMB(who) > -1)) return 0;

    if ((pendingpunish == "demote") && (pendingvictim == who))
    {
        NF("You have already voted to do so.\n");
        if (member_array(LCQN(TP), punishvoters) > -1) return 0;

        punishvoters = punishvoters + ({LCQN(TP)});
        write("You vote for the demotion of "+CAP(who)+".\n");
        say(QCTNAME(TP)+" votes for the demotion of "+CAP(who)+".\n");

        PENDSAVE;

    if ((sizeof(punishvoters) > 1)&&
           (!(member_array(pendingvictim, punishvoters) > -1)))
          return 1;

        punishvoters = ({});
        pendingpunish = "";

        LOG(who, "demoted", TP, "");
        tell_room(E(TP), CAP(who)+" has been demoted.\n");

        if (ob = find_player(who)) 
            ob->catch_msg("You have been removed as an Overseer!\n");
      REMOVE_COUN(who);
      PENDSAVE;
      return 1;
    }

    punishvoters = ({LCQN(TP)});
    pendingvictim = who;
    pendingpunish = "demote";
 
    write("You begin demotion proceedings against "+CAP(who)+".\n");
    say(QCTNAME(TP)+" begins demotion proceedings against "
        + CAP(who) + ".\n");
    PENDSAVE;
    return 1;
}

int
forgive(string str)
{
    int pun;
    string who, which;

    NF("Usage:  forgive <playername> <punishment>\n");
    if (sscanf(str, "%s %s", who, which) != 2) return 0;

    switch (which)
    {
        case "bar":     pun = BAR;     break;
        case "expel":   pun = EXPEL;   break;
        default: NF("No long term punishment to forgive.\n"); return 0;
    }

    NF(CAP(who) + " isn't under that punishment.\n");
    if (!REMOVE_PUNISHMENT(pun, who)) return 0;

    LOG(who, "forgiven", TP, "");
    write("Ok.\n");
    return 1;
}

int
permit()
{
    NF("You aren't a council member!\n");
//    if (!TPISCOUNCIL) return 0;
    if (permit_entry)
    {
        permit_entry = 0;
        write("You give the sign to the cilops to keep people out.\n");
        say(QCTNAME(TP)+" gives the sign to the cilops to keep "+
            "people out.\nThe cilops starts watching the entrance.\n");
        return 1;
    }
    permit_entry = 1;
    write("You give the sign to the cilops to let people in.\n");
    say(QCTNAME(TP)+" gives the sign to the cilops to let people in.\n"+
        "The cilops relaxes its guard.\n");
    return 1;
}

int
pet(string who)
{
    string *cilopstrs;
    cilopstrs = ({"cilops", "cylops", "gray cilops",
                  "large gray cilops", "large cilops"});

    if (!(member_array(who, cilopstrs) > -1)) return 0;

    NF("The cilops doesn't seem to be around.\n");
    if(!present("cilops", TO)) return 0;

    write("You pet the hard chitin of the cilops.\n");
    say(QCTNAME(TP)+" pets the hard chitin of the cilops.\n");
    tell_room(E(TP), "The cilops clicks its mandibles together happily.\n");
    return 1;
}

int
punish(string str)
{
    string who, why;

    NF("Usage:  punish <playername> <explanation>\n");
    if (sscanf(str, "%s %s", who, why) != 2) return 0;

    NF(CAP(who) + " not found among members.\n");
    if (file_size(MEM_FILE(who)) < 0) return 0;

    LOG(who, "punished", TP, why);
    write("Ok.\n");
    return 1;
}

int
regret()
{
    NF("You have not voted on the current issue.\n");
    if (!(member_array(LCQN(TP), punishvoters) > -1)) return 0;

    punishvoters = (punishvoters - ({LCQN(TP)}));
    write("OK.\n");
    PENDSAVE;
    return 1;
}

int
help(string str)
{
    if (!strlen(str)) return 0;
//    if (!TPISCOUNCIL) return 0;

    switch(str)
    {
        case "powers":
            write("\nYou may:  pet cilops\n" +
              "          appoint <playername>\n"+
              "          check joins <more>\n" +
              "          check quits <more>\n" +
              "          check <punishment>\n" +
              "          check <playername>\n" +
              "          bar <playername>\n" +
              "          brutkill\n" +
              "          brutforgive <playername>\n" +
              "          demote <Overseername>\n" +
              "          expel <playername> <explanation>\n"+
              "          punish <playername> <explanation>\n"+
              "          regret\n"+
              "          forgive <playername> <punishment>\n"+
              "          permit\n"+
              "          help <cmd>\n\n");
            return 1;
        case "appoint":
            write("\n = appoint <playername> <Position>\n"+
              " Allows the High Overseer to select new"+
              " Lesser Overseers.\n Position must be Arena, "+
              " War, Internal, Recruitment, or Assistant, "+
              "\n and must begin with a capital letter.\n\n");
              return 1;
        case "permit":
            write("\n = permit\n"+
              " Toggles the cilops between letting people in"+
              " and keeping them out.\n\n");
              return 1;
        case "regret":
            write("\n = regret\n"+
              " Allows you to withdraw your vote from a pending action\n"+
              " to demote or expel someone.\n\n");
              return 1;              
        case "brutkill":
            write("\n = brutkill\n"+
              " Produces a list of all those who have attacked Brutus,\n"+
              " The Guardian of the Gladiators.\n\n");
              return 1;
        case "brutforgive":
            write("\n = brutforgive <playername>\n"+
              " Allows removal of someone from the list of those who\n"+
              " have attacked Brutus. Do not take this ability lightly.\n\n");
            return 1;
        case "punish":
            write("\n = punish <playername> <explanation>\n"+
              " Allows you to record special punishments.\n"+
              " Requires vote of only 1 Overseer.\n"+
              " Explanation is a brief description of the punishment.\n\n");
            return 1;
        case "demote":
            write("\n = demote <playername>\n"+
              " Allows removal of someone from the Overseers.\n"+
              " Requires vote of 5 Overseers or 1 other than the target.\n"+
              " Overseername is the one to remove.\n"+
              " Demotion of the High Overseer disbands the council.\n\n");
            return 1;
        case "bar":
            write("\n = bar <playername>\n"+
              " Allows you to prevent a non-member from joining.\n"+
              " Or allows you to prevent a member from training\n"+
              "     or setting a custom charge string.\n"+
              " Requires vote of only 1 Overseer.\n"+
              " Playername is the person to be barred.\n\n");
            return 1;
        case "expel":
            write(" = expel <playername> <explanation>\n"+
              " Allows you to severely censure a member.\n"+
              " By revocation of chest privileges and \n"+
              " the ability to charge.\n"+
              " Requires High Overseer to initiate and\n"+
              "  four Lesser Overseers to ratify.\n"+
              " Playername is the name of the player to expel.\n"+
              " Explanation is a brief description of the reason.\n\n");
            return 1;
        case "forgive": 
            write(" = forgive <playername> <punishment>\n"+
              " Allows you to end of bars and unperformed expels.\n"+
              " Requires vote of only 1 Overseer.\n"+
              " Playername is the person to forgive.\n"+
              " Punishment is the punishment to remove.\n\n");
            return 1;
        default: return 0;
    }
}
