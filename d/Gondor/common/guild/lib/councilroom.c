/*
 *	/d/Gondor/common/guild/lib/councilroom.c
 *
 *	Copyright (c) 1993, 1997 by Christian Markus
 *
 *	The generic council room for the rangers.
 *
 *	Modification log:
 *	17-Feb-1997, Olorin:	Added mail reader.
 *
 *       4-Nov-2000, Gwyneth: Removed Elessar's hard-coded name.
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Genesis/lib/post.c";
inherit "/d/Gondor/common/lib/binbit.c";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include <macros.h>
#include <stdproperties.h>
#include <std.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"

#define COUNCIL       (RANGER_DIR + "council")
#define VOTES         (RANGER_HELP_DIR + "votes.txt")
#define IDEAS         (RANGER_HELP_DIR + "councilideas.txt")
#define PUNISH_HELP   (RANGER_HELP_DIR + "punishlist.txt")
#define COUNCILHELP   (RANGER_HELP_DIR + "councilhelp.txt")
#define RECRUITHALL   (RANGER_DIR + "recruithall")
#define PUNISH_LOG    (LOG_DIR + "rangerpunish")
#define STATUS_LOG    (LOG_DIR + "rangers")
#define KILLS         (LOG_DIR    + "rangerkills")
#define MORE_OBJ   "/std/board/board_more"
#define BOOK_DIR "/d/Gondor/common/guild/library/book/"
#define ELECTION_LOG (BOOK_DIR + "Elections")
#define COMPANY       ({"the Ranger pupils", "Gondor", "Ithilien"})
#define TMP_RANGER_CAPTAIN_RESIGN "_tmp_ranger_captain_resign"

#define NCAP    2
#define NLT     2
#define CSIZE   2

#define	SETTLE_NAME	"long settle"
#define	SETTLE_CAPACITY	12


//	Prototypes
        int     croom_read(string str);
        string  exa_poster();
	public void	leave_inv(object ob, object dest);
	public string	look_at(string arg);    /* VBFC for room and chairs */
	public int	plump(string arg);

//	Global variables
static object   board;
static int      company_number = 1;

int 
set_company_number(int i)
{
   if(i > 0 && i < sizeof(COMPANY))
      company_number = i;
   return i;
   return 0;
}

void 
create_councilroom()
{
   set_long("A council chamber.\n");
}

string
read_aliases()
{
    return "Here you may read and write your mail as in any post office.\n"+
	"Check the mailreader for instructions.\n" +
        "The following aliases can be used here:\n" +
        "\tguildmaster - the guildmaster of the Rangers guild,\n" +
        "\tcouncil     - the Council of Rangers,\n" +
        "\tgondorian   - the Officers of Gondor Company,\n" +
        "\tithilien    - the Officers of Ithilien Company,\n";
}

nomask void 
create_gondor()
{
   create_councilroom();
   
   set_short("The Council-chamber of the Rangers of " + COMPANY[company_number]);
   
   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_I_LIGHT,1);
   
   add_item( ({ "poster", "commands" }), exa_poster);

   add_item( ({ "plaque", "aliases", }), read_aliases);
   add_cmd_item( ({ "plaque", "aliases", }), "read", 
		read_aliases);

    add_chair(SETTLE_NAME,
	"[down] [in] / [on] [the] [long] 'settle'",
	SETTLE_CAPACITY, "on");

    add_item( ({ "long settle", "settle" }), &look_at(SETTLE_NAME));
    add_item( ({ "carving", "carvings", "carved back", "back", }),
	BSN("Delicate carvings of vines and flowers twine round "+
	    "the back of the settle."));
    add_item( ({ "vine", "flower", "vines", "flowers", }),
	BSN("The vines and flowers are carved in careful detail; "+
	    "they almost seem to grow from the wood."));
    add_item( ({ "blond oak", "oak", "wood" }),
	BSN("The settle is made from blond oak, carefully polished "+
	    "and beautifully carved."));
    add_item( ({ "colourful cushion", "cushion", "colourful cushions",
	"cushions", }),
	BSN("Cushions of all colours are heaped on the settle."));
    add_item( ({ "floor", "soft rushes", "rushes" }),
	BSN("Fresh rushes, soft and sweetly scented, cover the floor."));
    add_item( ({ "ceiling", "walls", "wall", }),
	BSN("The plaster walls and ceiling are quite clean."));
    add_item( ({ "plaster" }),
	BSN("The plaster is the colour of new cream."));

    add_cmd_item( ({ "colourful cushion", "cushion",
	"colourful cushions", "cushions", }),
	({ "get", "take", "pick", "steal" }),
	BSN("Please leave the cushions for others to enjoy."));
    add_cmd_item( ({ "soft rushes", "rushes" }),
	({ "smell", }),
	BSN("The rushes have the aroma of a hayfield on a sunny day."));

}

int help(string str)
{
   string *hstr;
   
   if(!str)
      return 0;
   hstr = explode(str," ");
   if(hstr[0] != "council")
      return 0;
   if(sizeof(hstr) > 2)
      return 0;
   if(sizeof(hstr) == 1)
      cat(COUNCILHELP);
   else if(hstr[1] == "votes")
      return 0;
   else if(file_size(RANGER_HELP_DIR + hstr[1] + ".txt") > 0)
      cat(RANGER_HELP_DIR + hstr[1] + ".txt");
   else
      return 0;
   return 1;
}

int
croom_read(string str)
{
   int     ivc;
   string  dummy;
   
   if (!str) 
   {
      notify_fail("Read what?\n");
      return 0;
   }
   if (str == "votes") 
   {
       write("Read calls for vote to see the list,\n" +
        "or read vote <n> to see how that vote is progressing.\n");
       return 1;
   }
   if (str == "status")
   {
        clone_object(MORE_OBJ)->more(STATUS_LOG, 2);
	return 1;
    }
    if (sscanf(str, "status %d", ivc) == 1)
    {
        if (ivc < 1)
            ivc = 1;
        clone_object(MORE_OBJ)->more(STATUS_LOG, ivc);
        return 1;
    }
   if (str == "punishlog")
   {
       clone_object(MORE_OBJ)->more(PUNISH_LOG, 2);
       return 1;
   }
   if (sscanf(str, "punishlog %d", ivc) == 1)
   {
       if (ivc < 1)
	   ivc = 1;
       clone_object(MORE_OBJ)->more(PUNISH_LOG, ivc);
       return 1;
   }
   if (str == "punishlist")
   {
       cat(PUNISH_HELP);
       return 1;
   }
   if (str == "kills") 
   {
       write("Sorry, this functionality has been removed.\n");
       return 1;
   }
   if (str == "poster") 
   {
       cat(RANGER_HELP_DIR + "councilposter.txt");
       return 1;
   }
   if(str == "calls for vote" || str == "call for vote" ||
      str == "calls for votes" || str == "call for votes" ||
      str == "call" || str == "calls")
   {
       write(COUNCIL->read_calls());
       return 1;
   }
   if(sscanf(str,"vote %d",ivc))
   {
       write(COUNCIL->read_vote(ivc));
       return 1;
   }
   if (sscanf(str, "impeac%s", dummy) == 1)
   {
       if (stringp(dummy = COUNCIL->query_impeachment()))
	   write(dummy);
       else
	   write("There is presently no call for an impeachment!\n");
       return 1;
   }
   if (str == "punishments pending" || str == "pending punishments")
   {
       write(COUNCIL->read_pendings());
       return 1;
   }
   return 0;
}

void 
remove_tmp_resign(object captain)
{
   captain->remove_prop(TMP_RANGER_CAPTAIN_RESIGN);
}

int 
do_resign(string str)
{
   int     ic = COUNCIL->is_council_member(TP->query_real_name());
   string *council = COUNCIL->query_council_members();
   
   if(!ic || ic > NCAP)
   {
      if (!ic)
      {
         if (!TP->query_prop(TMP_RANGER_CAPTAIN_RESIGN))
         {
            write("Do you really want to resign from your position as "
              + "Sergeant?\n" +
                "If so, then repeat the command!\n");
            TP->add_prop(TMP_RANGER_CAPTAIN_RESIGN, 1);
            set_alarm(10.0, 0.0, &remove_tmp_resign(TP));
            return 1;
         }
         say(QCTNAME(TP) + " resigns from the position of Sergeant!\n");
         write("You resign from your position as Sergeant!\n");
         write_file(RANGER_LOG, TP->query_name() + " resigned as Sergeant "
           + "of " + TP->query_company() + ". " + ctime(time()) + "\n");
         COUNCIL->remove_ranger(TP->query_real_name());
         TP->remove_prop(TMP_RANGER_CAPTAIN_RESIGN);
         return 1;
      }
      if (!stringp(council[ic-1]))
      {
         NF("You cannot resign while there is no Captain of your Company!\n"+
            "The Rangers of " + TP->query_company() + " must not be without "+
            "a leader!\n");
         return 0;
      }
      if (!TP->query_prop(TMP_RANGER_CAPTAIN_RESIGN))
      {
         write("Do you really want to resign from your position as "
           + "Lieutenant?\n" +
             "If so, then repeat the command!\n");
         TP->add_prop(TMP_RANGER_CAPTAIN_RESIGN, 1);
         set_alarm(10.0, 0.0, &remove_tmp_resign(TP));
         return 1;
      }
      say(QCTNAME(TP) + " resigns from the position of Lieutenant!\n");
      write("You resign fromyour position as Lieutenant!\n");
      write_file(RANGER_LOG, TP->query_name() + " resigned as Lieutenant "
        + "of " + TP->query_company() + ". " + ctime(time()) + "\n");
      COUNCIL->remove_ranger(TP->query_real_name());
      TP->remove_prop(TMP_RANGER_CAPTAIN_RESIGN);
      return 1;
   }
   
   NF("A Captain can only resign if there is a Lieutenant of the Company!\n"+
      "You cannot leave the Rangers of your company without a leader!\n");
   council = COUNCIL->query_council_members();
   if(!stringp(council[ic-1+NCAP]))
      return 0;
   
   str = lower_case(str);
   if(str != "as captain of the rangers")
      {
      NF("If you want to resign as a Captain of the Rangers, then type:\n"+
         "    'resign as captain of the rangers'\n"+
         "You will have to give the command a second time to confirm.\n");
      return 0;
   }
   if(!TP->query_prop(TMP_RANGER_CAPTAIN_RESIGN))
      {
      write("Do you really want to resign as Captain of the Rangers of "+COMPANY[ic]+"?\n"+
         "If so, then repeat the command!\n");
      TP->add_prop(TMP_RANGER_CAPTAIN_RESIGN,1);
      set_alarm(10.0, 0.0, &remove_tmp_resign(TP));
      return 1;
   }
   say(QCTNAME(TP) + " resigns as Captain of the Rangers of "+COMPANY[ic]+"!\n");
   write("You resign from your post as Captain of the Rangers of "+COMPANY[ic]+"!\n");
   write_file(RANGER_LOG,TP->query_name()+" resigned as Captain of the Rangers of "+COMPANY[ic]+
      ". "+ctime(time())+"\n");
   write_file(ELECTION_LOG,TP->query_name()+" resigned as Captain of the Rangers of "+COMPANY[ic]+
      ". "+ctime(time())+"\n");
   COUNCIL->remove_ranger(TP->query_real_name());
   set_bin_bits(1,18,2,TP,1);
   COUNCIL->call_election(ic);
   TP->remove_prop(TMP_RANGER_CAPTAIN_RESIGN);
   return 1;
}

int do_clear(string str)
{
   int i;
   
   if (!str) 
      {
      write("Clear what?\n");
      return 1;
   }
   if (str == "ideas" || str == "letters")
      {
      rm(IDEAS);
      write("The Rangers ideas are deleted.\n");
      return 1;
   }
   if (str == "votes") 
      {
      if (TP->query_wiz_level()) 
         rm(VOTES);
      else 
         write("Only the wizards may remove the votes.\n");
      return 1;
   }
   if(sscanf(str,"call for vote %d", i) == 1)
      {
      write("You clear the call for vote no "+i+".\n");
      SAY(" clears the call for vote no "+i+".");
      write(COUNCIL->read_vote(i));
      return COUNCIL->remove_call(i);
   }
   return 0;
}

int
do_pardon(string name)
{
    object player;
    string cap_name;
    
    if (!name)
    {
	write("syntax: pardon name\n" +
	    "Pardons a player that has been banned because of his deeds.\n");
	return 1;
    }
    name = LOW(name);
    cap_name = capitalize(name);
    player = find_player(name);

    if (!player)
    {
	write(cap_name + " must be in the realms to be given pardon.\n");
	return 1;
    }
    write((RANGER_LOG) + "\n");
    if ((RECRUITHALL)->unban_from_guild(name))
    {
	write("You pardon " + cap_name + ".\n");
	write_file(RANGER_LOG,"RANGER-COUNCIL: " + TP->query_cap_name() +
		   " pardoned " + cap_name + " for his deeds. "+ctime(time()) +
		   "\n");
	return 1;
    }
    else
    {
	write(cap_name + " is not banned.\n");
	return 1;
    }	    
}

    
int terminate_vote(string str)
{
   int i;
   
   NF("To end the voting on a topic, type: 'Terminate vote <number>'.\n");
   if(!stringp(str))
      return 0;
   
   if(sscanf(str, "vote %d", i) != 1)
      return 0;
   
   write("You end the voting for vote no "+i+".");
   SAY(" ends the voting for vote no "+i+".");
   write(COUNCIL->read_vote(i,1));
   return COUNCIL->remove_call(i);
}

int add_to_ithilien(string str)
{
   if(!TP->query_wiz_level())
      return 0;
   
   if (!str)
      {
      NF("Add who to the Council?\n");
      return 0;
   }
   if (COUNCIL->add_ithilien_captain(str))
      {
      write("You make "+CAP(str)+" Captain of the Rangers of Ithilien,\n"+
         "and member of the Council of Rangers.\n");
      return 1;
   }
   NF("There is already a captain of Ithilien.\n");
   return 0;
}

int add_to_gondor(string str)
{
   if(!TP->query_wiz_level())
      return 0;
   
   if (!str) 
      {
      NF("Add who to the Council?\n");
      return 0;
   }
   if (COUNCIL->add_gondor_captain(str))
      {
      write("You make "+CAP(str)+" Captain of the Rangers of Gondor,\n"+
         "and a member of the Council of Rangers.\n");
      return 1;
   }
   NF("There is already a captain of Gondor.\n");
   return 0;
}

int list_council()
{
   write("Currently in the Council of Rangers:\n"+COUNCIL->query_council()+"\n");
   return 1;
}

int remove_from_council(string str)
{
   if(!TP->query_wiz_level())
      return 0;
   
   if (!str)
      {
      NF("Remove whom from the Council?\n");
      return 0;
   }
   if (COUNCIL->remove_ranger(str)) 
      {
      write("You removed "+CAP(str)+" from the Council of Rangers.\n");
      return 1;
   }
   NF("That player is not in the Council of Rangers!\n");
   return 0;
}

int vote_for(string str)
{
   int     vn,
   ic;
   string  vote;
   
   NF("'vote <text>' or 'vote on <n> with <aye|yes|no|nay>'!\n");
   if (!str)
      return 0;
   
   if(sscanf(str, "on %d with %s", vn, vote) == 2)
      {
      write("You cast your vote on the call for vote no "+vn+".\n");
      SAY(" casts "+TP->query_possessive()+" vote on the call for vote no "+vn+".");
      switch(lower_case(vote))
      {
         case "aye":
         case "yes": ic = 1; break;
         case "no":
         case "nay": ic = -1; break;
         default: ic = 0;
      }
      NF("Vote on <n> with <aye|yes|no|nay>!\n");
      return COUNCIL->cast_vote(TP->query_real_name(),vn,ic);
   }
   return 0;
}

int call_council(string str)
{
   string *council,
   who;
    string   txt;
   object  cplayer;
   int     ic;
   
   NF("Call what?\n");
   if(!str || (lower_case(str) != "council") )
      return 0;
   
   council = COUNCIL->query_officers();
   
   who = TP->query_name();
   
   while(ic < sizeof(council))
   {
      if(stringp(council[ic]))
         {
         if(objectp(cplayer = find_player(lower_case(council[ic]))))
            {
            if(cplayer != TP)
               {
               cplayer->catch_msg(who + 
                  " calls for a meeting in the Council room " +
                  "of the guildhouse of the Rangers of " + 
                  COMPANY[company_number] + ".\n");
               write(CAP(council[ic]) + " has been notified.\n");
            }
         }
         else
            write(CAP(council[ic]) + " is nowhere to be found within the world.\n");
         }
      else
       {
          txt = "There is no ";
          if (ic < 2) txt +="Captain ";
          else if (ic < 4) txt += "Lieutenant ";
          else txt += "Sergeant ";
          txt += "of the Rangers of "+COMPANY[ic % 2]+".\n";
          write(txt);
       }
      ic++;
   }
   write_file(RANGER_LOG,"RANGER-COUNCIL: "+TP->query_cap_name()+" called for meeting. "+ctime(time())+"\n");
   return 1;
}

void test_allowed(object obj, object from)
{
    int     wizrank;
    string  name;

    if (!(wizrank = SECURITY->query_wiz_rank(name = obj->query_real_name())))
        if (COUNCIL->is_officer(name))
            return;
    if (wizrank >= WIZ_ARCH)
        return;
    if (SECURITY->query_wiz_dom(name) == "Gondor")
        return;
   tell_object(obj,"You are not allowed to enter this room!\n");
   obj->move(from);
   return;
}

void enter_inv(object obj, object from)
{
   ::enter_inv(obj,from);
   if (living(obj) && from) 
      test_allowed(obj,from);
}

string 
exa_poster()
{
   cat(RANGER_HELP_DIR + "councilposter.txt");
   return "";
}

int call_for_impeachment(string str)
{
   string  capname;

   NF(CAP(query_verb()) + " impeachment of <name>\n");
   if (!stringp(str))
      return 0;

   if (sscanf(str, "impeachment of %s", capname) != 1)
      return 0;

   capname = CAP(lower_case(capname));
   return COUNCIL->call_for_impeachment(TP, capname);
}

int do_impeach(string str)
{
    NF("Impeach <name>\n");
    if (!stringp(str))
        return 0;

    str = CAP(lower_case(str));
    return COUNCIL->do_impeach(TP, str);
}

int veto_impeach(string str)
{
    string  capname;

    NF("Veto the impeachment of <name>\n");
    if (!stringp(str))
        return 0;

    if (sscanf(str, "the impeachment of %s", capname) != 1)
        return 0;

    capname = CAP(lower_case(capname));
    return COUNCIL->veto_impeach(TP, capname);
}

int call_for_vote(string str)
{
   string *text,
   vstr;
   NF("Call for what?\n"+
     "Call for vote on <text> .. or\n"+
     "Call council\n");
   if (!str) return 0;
   
   text = explode(str," ");
   
   NF("Call for vote on <text>\n");
   if(lower_case(implode(text[0..1]," ")) != "for vote")
      return 0;
   
   vstr = implode(text[2..sizeof(text)-1]," ");
   
   write("You call for a vote: " + vstr + "\n");
   SAY(" calls for a vote: " + vstr);
   
   vstr = TP->query_name() + " called for a vote: " + vstr +
   " (" + ctime(time())[0..9]+")";
   
   seteuid(getuid());
   if(!COUNCIL->add_call(vstr))
      return 0;
   return 1;
}

int 
do_nominate(string name)
{
   string  result;
   
   NF("To nominate a ranger as a candidate for an election: 'nominate <name>'.\n");
   if(!name)
      return 0;
   
   if(sizeof(explode(name," ")) > 1)
      return 0;
   
   name = lower_case(name);
   result = COUNCIL->add_candidate(name);
   
   if(stringp(result))
      {
      write("You nominate " + result);
      say(QCTNAME(TP) + " nominates " + result);
      
      return 1;
   }
   return 0;
}

/*
 * Function name:	leave_inv
 * Description	:	mask parent to be sure that departing players
 *			are removed from chair/sofa occupants
 * Arguments	:	object ob -- the departing object
 *			object dest -- its destination
 *
 * If they leave via a normal exit, they've already been made to stand
 * by the exit efunc check_sitting().
 * However, if they leave by quitting, going netdead, teleporting, etc
 * and we don't call leave_inv_room_chairs(), then they'll still look
 * as if they're here.
 */
public void
leave_inv(object ob, object to)
{
    post_leave_inv(ob, to);

    ::leave_inv(ob, to);
    leave_inv_room_chairs(ob, to);
}

void 
init_council_room()
{
    post_init();

    add_action(croom_read,           "read");
    add_action(do_clear,             "clear");  
    add_action(list_council,         "council");
    add_action(call_council,         "call");
    add_action(call_for_vote,        "call");
    add_action(call_for_impeachment, "start");
    add_action(call_for_impeachment, "support");
    add_action(vote_for,             "vote");
    add_action(terminate_vote,       "terminate");  
    add_action(do_resign,            "resign");
    add_action(do_nominate,          "nominate");
    add_action(do_pardon,            "pardon");    
    add_action(do_impeach,           "impeach");
    add_action(veto_impeach,         "veto");
    add_action(help,                 "help");
    /* wizards only */
    add_action(add_to_ithilien,     "ithilien");
    add_action(add_to_gondor,       "gondor");
    add_action(remove_from_council, "dismiss");

    add_action(plump, "plump");
    add_action(plump, "fluff");
    init_room_chairs();	/* add chair verbs */
}

void
add_aliases(object rdr)
{
    string *wizards = ({});
    string *council;

    wizards = GONDOR_MASTER->query_domain_aliases(RANGER_S_GUILD_NAME);
    if (sizeof(wizards))
      rdr->set_alias("guildmaster", wizards);

    council = R_COUNCIL->query_officers();
    council -= ({ 0 });
    rdr->set_alias("council", council);

    council = ({ R_COUNCIL->query_gondor(), 
	         R_COUNCIL->query_gondor_deputy(),
		 R_COUNCIL->query_gondor_sergeant() });
    council -= ({ 0 });
    rdr->set_alias("gondorian", council);

    council = ({ R_COUNCIL->query_ithilien(), 
		 R_COUNCIL->query_ithilien_deputy(),
		 R_COUNCIL->query_ithilien_sergeant() });
    council -= ({ 0 });
    rdr->set_alias("ithilien", council);
}

 
 
/*
 * Function name: silent_room
 * Description  : Mask parent to allow all commands.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - player blocked/player not blocked.
 */
public int
silent_room(string str)
{
    return 0;
}






/*
 * Function name:	look_at
 * Description	:	VBFC to describe room/settle + occupants
 * Arguments	:	string arg -- what's being looked at
 *				      null str -> it's the room
 * Returns	:	string -- the description
 */
public string
look_at(string arg)
{
    if (arg == SETTLE_NAME)
    {
	return BSN(
	    "The settle has a handsomely carved back and colourful "
	  + "cushions. It is long enough to seat several people "
	  + "very comfortably.")
	  + sitting_on_chair(SETTLE_NAME, this_player(), 0);
    }
    return "";	/* "cannot happen" */
} /* look_at */


/*
 * Function name:	plump
 * Description	:	let 'em plump the cushions
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
plump(string arg)
{
    string	vb = QVB;
    if (strlen(arg) &&
	parse_command(LOW(arg), ({}),
	    "[up] [the] [settle] 'cushion' / 'cushions' "+
	    "[on] [the] [long] [settle]"))
    {
	WRITE("You "+vb+" the cushions on the settle.");
	SAY(" "+vb+"s the cushions on the settle.");
	return 1;
    }
    NF0(CAP(vb)+" what?\n");
} /* plump */

public int
query_prevent_snoop()
{
    FIX_EUID;
    if (SECURITY->query_wiz_dom(this_interactive()->query_real_name()) == "Gondor") 
    {
        return 0;
    }
    return ::query_prevent_snoop();
}

