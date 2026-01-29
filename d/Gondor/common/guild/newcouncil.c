
#include <composite.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/binbit.h"
#include "/d/Gondor/common/guild/lib/ranger_defs.h"
#include "/d/Gondor/common/guild/lib/punish_defs.h"
/* Defines for handling council-membership */
#define NCAP    3
#define NLT     3
#define CSIZE   6

/* Other defines */
#define COMPANY ({"the Ranger pupils", "Gondor", "the North", "Ithilien" })
#define WEEK    604800
#define BOOK_DIR "/d/Gondor/common/guild/library/book/"
#define VOTE_LOG (BOOK_DIR + "Votes")
#define ELECTION_LOG (BOOK_DIR + "Elections")

string  i_ranger,n_ranger,g_ranger;
string  g_deputy,n_deputy,i_deputy;
string  g_srgt, n_srgt, i_srgt;
string *council = ({0,0,0,0,0,0});

string *to_vote;
mixed  *votes_cast;
mixed  *election;                 /*  int      company number: 1-Gondor, 2-North, 3-Ithilien
                                   * *string   candidates, first name is deputy
                                   * *mixed    name of ranger, number of candidate array
                                   *  int      time when vote was called or last candidate nominated
                                   */
string *elected_captain;
string *impeached_captain = ({});
string *Masters = ({ });

mapping punishments = ([ ]);

static int  inited;
/* prototypes */
int execute_punishment(string who);
void check_ranger_loc_ok(object pl, int ptype);

void
init_council_object()
{
    if (!inited)
    {
        seteuid(getuid());
        restore_object(COUNCIL);
        inited = 1;
    }
}

string 
query_council()
{
  string cstr;
  init_council_object();
  if (g_ranger) 
    cstr =  " - Captain of the Rangers of Gondor:       "+g_ranger+"\n";
  else 
    cstr =  " - There is no Captain of the Rangers of Gondor.\n";
  if(g_deputy)
    cstr += " - Lieutenant of the Rangers of Gondor:    "+g_deputy+"\n";
  else 
    cstr += " - There is no Lieutenant of the Rangers of Gondor.\n";
  if (g_srgt)
    cstr += " - Sergeant of the Rangers of Gondor:      "+g_srgt+"\n";
  else
    cstr += " - There is no Sergeant of the Rangers of Gondor.\n";
  if (n_ranger) 
    cstr += " - Captain of the Rangers of the North:    "+n_ranger+"\n";
  else 
    cstr += " - There is no Captain of the Rangers of the North.\n";
  if (n_deputy) 
    cstr += " - Lieutenant of the Rangers of the North: "+n_deputy+"\n";
  else 
    cstr += " - There is no Lieutenant of the Rangers of the North.\n";
  if (n_srgt)
    cstr += " - Sergeant of the Rangers of the North:   "+n_srgt+"\n";
  else
    cstr += " - There is no Sergeant of the Rangers of the North.\n";
  if (i_ranger) 
    cstr += " - Captain of the Rangers of Ithilien:     " +i_ranger+"\n";
  else 
    cstr += " - There is no Captain of the Rangers of Ithilien.\n";
  if (i_deputy) 
    cstr += " - Lieutenant of the Rangers of Ithilien:  " +i_deputy+"\n";
  else 
    cstr += " - There is no Lieutenant of the Rangers of Ithilien.\n";
  if (i_srgt)
    cstr += " - Sergeant of the Rangers of Ithilien:    " +i_srgt+"\n";
  else
    cstr += " - There is no Sergeant of the Rangers of Ithilien.\n";
  return cstr;
}

int add_ithilien_captain(string str)
{
  if (!str) return 0;
  str = capitalize(lower_case(str));
  init_council_object();
  if (i_ranger) return 0;
  i_ranger = str;
  council[I_CPT-1] = str;
  save_object(COUNCIL);
  return 1;
}

int add_ithilien_deputy(string str)
{
  if (!str) return 0;
  str = capitalize(lower_case(str));
  init_council_object();
  i_deputy = str;
  if (i_srgt == str) i_srgt = 0;
  council[I_LT-1] = str;
  save_object(COUNCIL);
  return 1;
}

int add_ithilien_sergeant(string str)
{
  if (!str) return 0;
  str = capitalize(lower_case(str));
  init_council_object();
  i_srgt = str;
  if (i_deputy == str) i_deputy = 0;
  save_object(COUNCIL);
  return 1;
}

int add_north_captain(string str)
{
  if (!str) return 0;
  str = capitalize(lower_case(str));
  init_council_object();
  if (n_ranger) return 0;
  n_ranger = str;
  council[N_CPT-1] = str;
  save_object(COUNCIL);
  return 1;
}

int add_north_deputy(string str)
{
  if (!str) return 0;
  str = capitalize(lower_case(str));
  init_council_object();
  n_deputy = str;
  if (n_srgt == str) n_srgt = 0;
  council[N_LT-1] = str;
  save_object(COUNCIL);
  return 1;
}

int add_north_sergeant(string str)
{
  if (!str) return 0;
  str = capitalize(lower_case(str));
  init_council_object();
  n_srgt = str;
  if (n_deputy == str) n_deputy = 0;
  save_object(COUNCIL);
  return 1;
}

int add_gondor_captain(string str)
{
  if (!str) return 0;
  str = capitalize(lower_case(str));
  init_council_object();
  if (g_ranger) return 0;
  g_ranger = str;
  council[G_CPT-1] = str;
  save_object(COUNCIL);
  return 1;
}

int add_gondor_deputy(string str)
{
  if (!str) return 0;
  str = capitalize(lower_case(str));
  init_council_object();
  g_deputy = str;
  if (g_srgt == str) g_srgt = 0;
  council[G_LT-1] = str;
  save_object(COUNCIL);
  return 1;
}

int add_gondor_sergeant(string str)
{
  if (!str) return 0;
  str = capitalize(lower_case(str));
  init_council_object();
  g_srgt = str;
  if (g_deputy == str) g_deputy = 0;
  save_object(COUNCIL);
  return 1;
}

int remove_ranger(string str)
{
  if (!str) return 0;
  str = capitalize(lower_case(str));
  init_council_object();

  if(str == g_ranger)
  {
    g_ranger = 0;
    council[G_CPT-1] = 0;
  }
  else if(str == n_ranger)
  {
    n_ranger = 0;
    council[N_CPT-1] = 0;
  }
  else if(str == i_ranger)
  {
    i_ranger = 0;
    council[I_CPT-1] = 0;
  }
  else if(str == g_deputy)
  {
    g_deputy = 0;
    council[G_LT-1] = 0;
  }
  else if(str == n_deputy)
  {
    n_deputy = 0;
    council[N_LT-1] = 0;
  }
  else if(str == i_deputy)
  {
    i_deputy = 0;
    council[I_LT-1] = 0;
  }
  else if(str == n_srgt)
    n_srgt = 0;
  else if(str == g_srgt)
    g_srgt = 0;
  else if(str == i_srgt)
    i_srgt = 0;
  else
    return 0;

  save_object(COUNCIL);
  return 1;
}

query_gondor()
{
  init_council_object();
  if (g_ranger) return g_ranger;
  return 0;
}

query_gondor_deputy()
{
  init_council_object();
  if (g_deputy) return g_deputy;
  return 0;
}

query_gondor_sergeant()
{
  init_council_object();
  if (g_srgt) return g_srgt;
  return 0;
}

query_ithilien()
{
  init_council_object();
  if (i_ranger) return i_ranger;
  return 0;
}

query_ithilien_deputy()
{
  init_council_object();
  if (i_deputy) return i_deputy;
  return 0;
}

query_ithilien_sergeant()
{
  init_council_object();
  if (i_srgt) return i_srgt;
  return 0;
}

query_north()
{
  init_council_object();
  if (n_ranger) return n_ranger;
  return 0;
}

query_north_deputy()
{
  init_council_object();
  if (n_deputy) return n_deputy;
  return 0;
}

query_north_sergeant()
{
  init_council_object();
  if (n_srgt) return n_srgt;
  return 0;
}

int is_council_member(string str)
{
  if (!str) return 0;
  str = capitalize(lower_case(str));
  init_council_object();

  return (member_array(str,council)+1);
}

int query_captain(string str)
{
    int    rank;

    if (!stringp(str))
        return 0;

    rank = is_council_member(str);

    if (rank == 0 || rank > NCAP)
        return 0;

    return 1;
}

int query_lieutenant(string str)
{
  int rank;

  if (!stringp(str))
    return 0;

  rank = is_council_member(str);
  if (rank > NCAP && rank <= CSIZE)
    return 1;
  return 0;
}

int query_sergeant(string str)
{
  if (!stringp(str))
    return 0;

  str = capitalize(lower_case(str));

  if (str == g_srgt) return 1;
  else if (str == n_srgt) return 2;
  else if (str == i_srgt) return 3;

  return 0;
}

string *query_council_members()
{
    init_council_object();
    return council;
}

string *query_officers()
{
    init_council_object();
    return council + ({ g_srgt, n_srgt, i_srgt });
}

int is_officer(string str)
{
  if (!stringp(str))
    return 0;
  str = capitalize(lower_case(str));
  if (member_array(str, query_officers()) >= 0)
    return 1;
  return 0;
}

int
add_master(string rname)
{
  init_council_object();
    if (!stringp(rname) || !strlen(rname))
        return 0;
    if (member_array(rname, Masters) >= 0) return -1;
    if (!sizeof(Masters))
        Masters = ({ rname });
    else
        Masters += ({ rname });
    save_object(COUNCIL);
    return 1;
}

string
query_masters()
{
    init_council_object();
    if (!sizeof(Masters))
        return "None";
    if (sizeof(Masters) == 1)
        return Masters[0];
    else return COMPOSITE_WORDS(Masters);
}

int
query_is_master(string rname)
{
    rname = CAP(LOW(rname));
    return (member_array(rname, Masters) >= 0);
}

int
remove_master(string rname)
{
    int  n;
    init_council_object();
    if (!stringp(rname) || !strlen(rname))
        return 0;
    if (member_array(rname, Masters) < 0)
        return -1;
    n = member_array(rname, Masters);
    Masters = exclude_array(Masters, n, n);
    save_object(COUNCIL);
    return 1;
}

int
add_punishment(string who, int punishtype, object cm, string why)
{
  init_council_object();
  who = lower_case(who);
  if (punishments[who])
    punishments = m_delete(punishments,who);
  if (!m_sizeof(punishments)) punishments = ([ who : punishtype ]);
  else
  punishments += ([ who : punishtype ]);
  save_object(COUNCIL);
  write_file(PUNISH_LOG, CAP(who) + " logged to be " +
    ((punishtype == REWARD || punishtype == COMMEND) ? "rewarded " :
    "punished ") + "with " +
        PTYPE[punishtype]+", by "+cm->query_name()+".\n" + 
        "  Reason was: "+why+".\n");
  return 1;
}

int
query_pending_punishment(string who)
{
  int i;
  init_council_object();
  return punishments[who];
}

mixed
query_pending_list()
{
    string *names;
    init_council_object();
    if (!m_sizeof(punishments))
        return 0;
    names = m_indexes(punishments);
    if (sizeof(names))
        return names;
    return 0;
}

string
read_pendings()
{
    int pt, i;
    string *names, txt;
    names = query_pending_list();
    if (!sizeof(names))
        return "No punishments or rewards are pending.\n";

    if (sizeof(names) == 1)
    {
        return CAP(names[0]) + " is awaiting this " +
        ((punishments[names[0]] == REWARD || punishments[names[0]] == COMMEND) ?
         "reward" : "punishment") +
          ": " + PTYPE[punishments[names[0]]] + ".\n";
    }
    txt = "Pending Punishments and Rewards: \n";
    while (i < sizeof(names))
    {
        pt = punishments[names[i]];
        txt += sprintf("  %-42s %30s",
          CAP(names[i]) + " is awaiting this " +
          ((pt == REWARD || pt == COMMEND) ? "reward" : "punishment") + ": ",
          CAP(PTYPE[pt]) + ".") + "\n";
        i++;
    }
    return txt;
}

int
pigeon_message(string txt, string from, object to)
{
  object note,fromob;
  seteuid(getuid());
  note = clone_object(RANGER_DIR+"obj/message");
  note->set_message(txt);
  note->set_sender(from);
  fromob = find_player(lower_case(from));
  if (objectp(fromob) && (ENV(fromob) == ENV(to)))
  {
      to->catch_msg(QCTNAME(fromob)+" points at you!\n",fromob);
    to->catch_msg(QCTNAME(fromob)+" hands you a message explaining "+
	fromob->query_possessive()+" decision.\n");
    fromob->catch_msg("You hand "+QTNAME(to)+" the judgement on a piece of paper.\n");
  }
  else
  {
    /* don't mention sky etc .. might be indoors */
    to->catch_msg("A white carrier pigeon lands on your shoulder.\n"+
      "You retrieve a message from a holster bound to its foot.\n"+
      "The pigeon flaps its wings and flies away again.\n");
  }
  note->move(to,1);
  return 1;
}

int
clear_pending_punishment(string who)
{
  init_council_object();
  if (punishments[who])
    punishments = m_delete(punishments,who);
  save_object(COUNCIL);
  return 1;
}

int
remove_punishment(string who, object cm, string why)
{
  int ptype;
  object pl,note,cmob;
  string notetxt,notefrom, by;
  init_council_object();
  who = lower_case(who);
  if (punishments[who])
    punishments = m_delete(punishments,who);
  save_object(COUNCIL);
  NF(capitalize(who)+" is not playing right now.\n");
  if (!(pl = find_player(who))) return 0;
  ptype = pl->query_skill(SS_PUNISHMENT);
  pl->set_skill(SS_PUNISHMENT,NO_PUNISH);
  notetxt = "Hail Gondor!\nYou have now been cleared for the punishment of\n"+
    PTYPE[ptype]+".\n\nThe Council of Rangers.\n";
  if (cm) notefrom = cm->query_name();
  else notefrom = "The Council of Rangers";
  pigeon_message(notetxt,notefrom,pl);
  write_file(PUNISH_LOG,CAP(who)+" cleared for punishment of "+PTYPE[ptype]+
	     ", by "+notefrom+".\n");
  if (strlen(why)>5) write_file(PUNISH_LOG,"  Reason was: "+why+".\n");
  return 1;
}

int
execute_block(string who, int ptype, object cm, string why)
{
  object crim,note;
  string notetxt,notefrom;
  int oldp;
  if (find_player("elessar"))
  find_player("elessar")->catch_msg("DEBUG: execute_block func: who = "+
    who+", ptype = "+ptype+".\n");
  if (!(crim = find_player(who)))
    return 0;
  oldp = crim->query_skill(SS_PUNISHMENT);
  crim->set_skill(SS_PUNISHMENT,ptype);
  notetxt = crim->query_name()+"!\nYou have been punished with "+
    PTYPE[ptype]+",\nfor your misdoings.\n\nThe Council of Rangers.\n";
  if (!cm) notefrom ="The Council of Rangers";
  else notefrom = cm->query_name();
  pigeon_message(notetxt,notefrom,crim);
  write_file(PUNISH_LOG,CAP(who)+" punished with "+PTYPE[ptype]+
	     ", by "+notefrom+".\n");
  if (strlen(why)>5) write_file(PUNISH_LOG,"  Reason was: "+why+".\n");
  clear_pending_punishment(who);
  if (ptype == NOACCESS)
  {
    if ( !crim->set_default_start_location(RANGER_GON_DIR+"startchamber") )
    {
	crim->set_default_start_location(crim->query_def_start());
    }
    check_ranger_loc_ok(crim, NOACCESS);
  }
  return 1;
}

int
do_degrade(string who, object cm, string why)
{
  object crim;
  int oldp;
  string notetxt,notefrom;
  if (!(crim = find_player(who)))
    return 0;
  oldp = crim->query_skill(SS_PUNISHED);
  crim->set_skill(SS_PUNISHED,oldp+RANKSTEP);
  notetxt = crim->query_name()+
    "!\nYou have been degraded a rank for your misbehaviour!\n"+
      "\nThe Council of Rangers.\n";
  if (!cm) notefrom = "The Council of Rangers";
  else notefrom = cm->query_name();
  pigeon_message(notetxt,notefrom,crim);
  write_file(PUNISH_LOG,CAP(who)+" degraded in rank, by "+notefrom+".\n");
  if (strlen(why)>5) write_file(PUNISH_LOG,"  Reason was: "+why+".\n");
  clear_pending_punishment(who);
  return 1;
}

int do_reward(string who, object cm, string why)
{
  object crim;
  int oldp;
  string notetxt,notefrom;
  if (!(crim = find_player(who)))
    return 0;
  oldp = crim->query_skill(SS_REWARDED);
  crim->set_skill(SS_REWARDED,oldp+RANKSTEP);
  notetxt = crim->query_name()+
    "!\nYou have been rewarded with a rank for your exemplary behaviour!\n"+
      "\nThe Council of Rangers.\n";
  if (!cm) notefrom = "The Council of Rangers";
  else notefrom = cm->query_name();
  pigeon_message(notetxt,notefrom,crim);
  write_file(PUNISH_LOG,CAP(who)+" rewarded with a rank, by "+notefrom+".\n");
  if (strlen(why)>5) write_file(PUNISH_LOG,"  Reason was: "+why+".\n");
  clear_pending_punishment(who);
  return 1;
}

int
do_commend(string who, object cm, string why)
{
  object crim;
  int oldp;
  string notetxt,notefrom;
  if (!(crim = find_player(who)))
    return 0;
  oldp = crim->query_skill(SS_REWARDED);
  crim->set_skill(SS_REWARDED,oldp + 1);
  notetxt = crim->query_name()+
    "!\nYou have been given a commendation for your exemplary behaviour!\n"+
      "\nThe Council of Rangers.\n";
  if (!cm) notefrom = "The Council of Rangers";
  else notefrom = cm->query_name();
  pigeon_message(notetxt,notefrom,crim);
  write_file(PUNISH_LOG,CAP(who)+" given a commendation, by "+notefrom+".\n");
  if (strlen(why)>5) write_file(PUNISH_LOG,"  Reason was: "+why+".\n");
  clear_pending_punishment(who);
  return 1;
}

int pupilize_ranger(string who, object cm, string why)
{
  object crim;
  int i,lowered;
  string notetxt,notefrom;
  if (!(crim = find_player(who)))
    return 0;
  set_bin_bits(1,16,2,crim,0);
  while (i < sizeof(SKILLS))
  {
    if (crim->query_skill(SKILLS[i])>PUPIL_SKILLS[i])
    {
      crim->set_skill(SKILLS[i],PUPIL_SKILLS[i]);
      lowered = 1;
      }
    i++;
    }
  RANGER_GUILD->give_token(crim,1);
  notetxt = crim->query_name()+
    "!\nYou have been degraded to Ranger pupil for your misbehaviour!\n";
    if (lowered) notetxt = notetxt + "In the process you have become less skilled.\n";
    notetxt = notetxt +      "\nThe Council of Rangers.\n";
  if (!cm) notefrom = "The Council of Rangers";
  else notefrom = cm->query_name();
  pigeon_message(notetxt,notefrom,crim);
  write_file(PUNISH_LOG,CAP(who)+" degraded to Ranger pupil, by "+notefrom+".\n");
  if (strlen(why)>5) write_file(PUNISH_LOG,"  Reason was: "+why+".\n");
  clear_pending_punishment(who);
  return 1;
}

int expel_ranger(string who, object cm, string why)
{
  object crim;
  string notetxt,notefrom;
  if (!(crim = find_player(who)))
    return 0;
  if (!RANGER_GUILD->remove_ranger(who,1,"expelled"))
  {
    write_file(PUNISH_LOG,"Failed to expel "+CAP(who)+" from the Rangers. "+
      "The punishment remains pending.\n");
    return 0;
  }
  notetxt = crim->query_name()+
    "!\nYou have been expelled from the Rangers for your crimes!\n"+
    "If you want to rejoin the guild, you may do so, but you start\n"+
    "at the lowest rank again, as a Ranger pupil.\n\n"+
    "The Council of Rangers.\n";
  if (!cm) notefrom = "The Council of Rangers";
  else notefrom = cm->query_name();
  pigeon_message(notetxt,notefrom,crim);
  write_file(PUNISH_LOG,CAP(who)+" was expelled from the Rangers, by "+notefrom+".\n");
  if (strlen(why)>5) write_file(PUNISH_LOG,"  Reason given: "+why+".\n");
  clear_pending_punishment(who);
  crim->set_default_start_location(crim->query_def_start());
  check_ranger_loc_ok(crim, EXPULSION);
  return 1;
}

int ban_ranger(string who, object cm, string why)
{
  object crim;
  string notetxt,notefrom;
  if (!(crim = find_player(who)))
    return 0;
  if (!cm)
    notefrom = "The Council of Rangers";
  else
    notefrom = CAP(cm->query_real_name());
  if (IS_RANGER(crim))
  {
    RANGER_GUILD->remove_ranger(who,1);
    set_bin_bits(1,18,2,crim,3);
    notetxt = crim->query_name()+
    "!\nYou have been expelled and banned from the Rangers for your crimes!\n"+
    "You are not welcome to rejoin the Rangers again.\n\n"+
    "The Council of Rangers.\n";
    write_file(PUNISH_LOG, CAP(who) + " was expelled and banned "
      + "from the Rangers, by " + notefrom + ".\n");
  }
  else
  {
    set_bin_bits(1, 18, 2, crim, 3);
    notetxt = crim->query_name() + "!\n"
      + "You have been banned from joining the Rangers.\n"
      + "\nThe Council of Rangers.\n";
    write_file(PUNISH_LOG, CAP(who) + " was banned from the "
      + "Rangers, by " + notefrom + ".\n");
  }
  pigeon_message(notetxt,notefrom,crim);
  if (strlen(why)>5) write_file(PUNISH_LOG,"  Reason given: "+why+".\n");
  clear_pending_punishment(who);
  return 1;
}

int
unban_player(string who, object cm, string why)
{
    object pl;
    string notetxt, notefrom;
    if (!(pl = find_player(who)))
        return 0;
    if (!cm)
        notefrom = "The Council of Rangers";
    else
        notefrom = CAP(cm->query_real_name());
    set_bin_bits(1, 18, 2, pl, 0);
    notetxt = CAP(who) + "!\n"
      + "You have been found worthy to be\n"
      + "freed of the ban from the Rangers.\n"
      + "You are now eligible to apply and join the Rangers,\n"
      + "if someone will vouch for you.\n\n"
      + "The Council of Rangers.\n";
    pigeon_message(notetxt, notefrom, pl);
    write_file(PUNISH_LOG, CAP(who) + " is no longer banned from the Rangers, "
      + "sanctioned by " + notefrom + ".\n");
    return 1;
}


int
execute_punishment(string who)
{
  int pold,ptype;
  object pl;
  if (find_player("elessar"))
  find_player("elessar")->catch_msg("DEBUG: execute_punishment: who = "+who+". ptype "+punishments[who]+".\n");
  init_council_object();
  who = lower_case(who);
  ptype = punishments[who];
  if (!(pl = find_player(who))) {
    write_file(PUNISH_LOG,CAP(who)+" not found when executing punishment.\n");
    return 0;
    }
  pold = pl->query_skill(SS_PUNISHMENT);
  if (ptype == pold) {
    write_file(PUNISH_LOG,CAP(who)+" already punished type "+ptype+
          ". No change.\n");
      return 0;
  }
  switch(ptype)
    {
    case REM_PUNISH:
      remove_punishment(who,0,"none");
      break;
    case NOTRAIN:
    case NOTRADE:
    case NOACCESS:
    case NOSKILLS:
    case NOSPELLS:
    case NOABILITIES:
      execute_block(who,ptype,0,"none");
      break;
    case DEGRADE:
      do_degrade(who,0,"none");
      break;
    case REWARD:
      do_reward(who,0,"none");
      break;
    case COMMEND:
      do_commend(who, 0, "none");
      break;
    case PUPILIZE:
      pupilize_ranger(who,0,"none");
      break;
    case EXPULSION:
      expel_ranger(who,0,"none");
      break;
    case BAN:
      ban_ranger(who,0,"none");
      break;
    case OUTLAW:
      break;
    default:
      write_file(PUNISH_LOG,CAP(who)+" failed to be punished, in execute_punishment func. ptype = "+ptype+".\n");
      break;
    }
}

int add_call(string str)
{
    if(!str)
        return 0;

    init_council_object();

    if(!sizeof(to_vote))
        to_vote = ({});

    to_vote += ({str});

    if(!sizeof(votes_cast))
        votes_cast = ({ ({0,0,0,0,0,0}) });
    else
        votes_cast += ({ ({0,0,0,0,0,0}) });

    save_object(COUNCIL);
    return 1;
}

string read_calls()
{
    int i, s;
    string vtxt, nstr;

    init_council_object();

    if(!(s = sizeof(to_vote)))
        return "There are currently no questions to be decided.\n";

    vtxt = "Your vote is required on these items:\n\n";
    while(i < s)
    {
        nstr  = ">"+(i<10?" ":"")+i+"< ";
        vtxt += break_string(to_vote[i]+"\n",65,nstr);
        i++;
    }
    return vtxt + "\n";
}

int remove_call(int i)
{
    init_council_object();

    notify_fail("No such call for vote!\n");
    if( sizeof(to_vote) <= i )
        return 0;

    to_vote = exclude_array(to_vote,i,i);
    votes_cast = exclude_array(votes_cast,i,i);
    save_object(COUNCIL);
    return 1;
}

int cast_vote(string name, int v, int i)
{
    int     ic;

    if(!stringp(name))
        return 0;

    if(!(ic = is_council_member(name)))
        return 0;

    init_council_object();

    if(v >= sizeof(votes_cast))
        return 0;

    if(i != 1 && i != -1)
        return 0;

    votes_cast[v][ic-1] = i;
    save_object(COUNCIL);
    return 1;
}

varargs string read_vote(int icfv, int ilog = 0)
{
    int     ic, aye, nay;
    string  vstr,
            lstr,
            rstr;

    init_council_object();

    if(icfv < 0 || icfv >= sizeof(to_vote) )
        return "\nThere is no such call for votes!\n\n";

    vstr = "\n" + to_vote[icfv] + "\n\n";
    if(ilog) 
        lstr = to_vote[icfv] + "\n";

    ic = 1;
    while(ic <= CSIZE)
    {
        vstr += "The " + (ic <= NCAP? "Captain " : "Lieutenant ") +
            "of the Rangers of " + COMPANY[ic <= NCAP? ic : ic - NCAP];

        if(ilog)
            if(stringp(council[ic-1]))
                lstr += council[ic-1] + ": ";
            else
                lstr += (ic <= NCAP? "Captain" : "Lieutenant") + " of " + COMPANY[ic <= NCAP? ic : ic - NCAP] + ": ";

        switch(votes_cast[icfv][ic-1])
        {
            case  0: 
                vstr += " did not vote yet.";
                if(ilog)
                    lstr += " - ";
                break;
            case  1: 
                vstr += " voted 'Aye'!";
                if(ilog)
                    lstr += "Aye";
                aye++;
                if(ic <= NCAP && stringp(council[ic-1+NCAP]))
                    aye++;
                break;
            case -1: 
                vstr += " voted 'Nay'!";
                if(ilog)
                    lstr += "Nay";
                nay++;
                if(ic <= NCAP && stringp(council[ic-1+NCAP]))
                    nay++;
                break;
        }
        vstr += "\n";
        if(ilog)
            if(ic < CSIZE)
                lstr += "; ";
            else
                lstr += ".";
        ic++;
    }

    rstr = "'Ayes': " + LANG_WNUM(aye)+ (aye?"":"ne") + " - 'Nays': " + LANG_WNUM(nay)+(nay?"":"ne") + ". ";
    if(aye == nay && (aye || nay))
        rstr += "The vote is tied!\n";
    else if(aye > nay)
        rstr += "The 'Ayes' have it!\n";
    else if(aye < nay)
        rstr += "The 'Nays' have it!\n";

    vstr += "\n> " + rstr;
    if(ilog)
    {
        lstr += "\nVoting terminated by " + TP->query_name() + " at " + ctime(time())[0..9] + ": " + rstr;
        write_file(VOTE_LOG,lstr + "\n");
    }

    return vstr + "\n";
}

int check_votes(string name)
{
    int     ic,
            icfv,
            ncfv,
            iflg;

    if( !(ic = is_council_member(name)))
        return 0;

    init_council_object();

    if(!(ncfv = sizeof(to_vote)))
        return 0;

    ic--; iflg = 0;
    while(icfv < ncfv)
    {
        if(!votes_cast[icfv][ic])
            iflg++;
        icfv++;
    }
    return iflg;
}

varargs int call_election(int icompany, string candidate = 0)
{
    string  cname;

    /* company does not exist */
    if(icompany >= sizeof(COMPANY) || icompany <= 0)
        return -1;

    init_council_object();

    /* there is a captain of that company */
    if(stringp(cname = council[icompany-1]))
        if( SECURITY->exist_player(cname) )
            return -2;
        else
            remove_ranger(cname);

    if(sizeof(election) < 3)
        election = ({});

    if (!stringp(candidate))
        candidate = council[icompany-1+NCAP];
    election += ({ icompany, ({candidate, 0, }), GUILD->query_company_members(icompany), time(), });

    save_object(COUNCIL);

    return 1;
}

string add_candidate(string name)
{
    int     icc,
            ivote,
            i,
            vsum;

    name = lower_case(name);
    icc  = GUILD->query_company(name);

    if(icc <= 0)
    {
        NF(CAP(name) + " is not a member of a Ranger company!\n");
        return 0;
    }

    init_council_object();

    if(stringp(council[icc-1]))
    {
        NF("There is a Captain of the Rangers of " + COMPANY[icc] + "!\n");
        return 0;
    }

    if((ivote = member_array(icc,election)) == -1)
    {
        call_election(icc);
        NF("You have called for an election for the Captaincy of the Rangers of "+COMPANY[icc]+
            "!\nYou can now repeat the nomination of an additional candidate!\n");
        return 0;
    }

    name = CAP(name);
    if(member_array(name,election[ivote+1]) > -1)
    {
        NF(name + " has already been nominated as candidate!\n");
        return 0;
    }

    vsum = 0;
    i = 1;
    while(i < sizeof(election[ivote + 1]))
    {
        vsum += election[ivote + 1][i];
        i += 2;
    }
 
    if(vsum)
    {
        NF("You cannot nominate a new candidate because some rangers already voted in this election!\n");
        return 0;
    }

    election[ivote + 1] += ({ CAP(name), 0, });
    election[ivote + 3]  = time();
    save_object(COUNCIL);
    write_file(ELECTION_LOG, TP->query_name() + " nominated " + CAP(name) +
        " as candidate for the Captaincy of the Rangers of "+COMPANY[icc]+"!\n");
    return name+" as candidate for the Captaincy of the Rangers of "+COMPANY[icc]+"!\n";
}

void make_captain(object ob)
{
    string  name     = ob->query_real_name(),
            cname;
    int     ic,
            id,
            ie;

    ic = GUILD->query_company_number(name);

    if(ic <= 0 || ic >= sizeof(COMPANY))
        return;

    init_council_object();

    if(stringp(council[ic -1]))
        return;

    id = 0;
    cname = CAP(name);
    switch(ic)
    {
        case 1:
            g_ranger = cname; 
            if(g_deputy == cname)
            {
                g_deputy = 0;
                id = 1;
            }
            else if(g_srgt == cname)
		g_srgt = 0;
            break;
        case 2:
            n_ranger = cname; 
            if(n_deputy == cname)
            {
                n_deputy = 0;
                id = 1;
            }
            else if(n_srgt == cname)
		n_srgt = 0;
            break;
        case 3:
            i_ranger = cname; 
            if(i_deputy == cname)
            {
                i_deputy = 0;
                id = 1;
            }
            else if(i_srgt == cname)
		i_srgt = 0;
            break;
    }
    if(id)
        council[ic-1+3] = 0;

    if((ie = member_array(cname,elected_captain)) > -1)
        elected_captain = exclude_array(elected_captain,ie,ie);
    council[ic-1] = cname;
    save_object(COUNCIL);

    set_bin_bits(1,18,2,ob,2);
    ob->catch_msg("\nYou have been elected to Captain of the Rangers of "+COMPANY[ic]+"!\n\n");
    write_file(RANGER_LOG,"ELECTION: "+cname+" was promoted to Captain of the Rangers of "+
        COMPANY[ic]+". "+ctime(time())+"\n");
    write_file(ELECTION_LOG,cname+" was promoted to Captain of the Rangers of "+
        COMPANY[ic]+". "+ctime(time())+"\n");

}

void evaluate_votes(int i)
{
    int    icand,
           max_votes,
           ix;
    string elected,
           result;
    object ncap;

    while(icand < sizeof(election[i + 1]))
    {
        if(election[i+1][icand+1] > max_votes)
        {
            max_votes = election[i+1][icand+1];
            elected = election[i+1][icand];
        }
        icand+=2;
    }
    if(!sizeof(elected_captain))
        elected_captain = ({});
    if(!stringp(elected))
        return;
    elected_captain += ({ elected });

    result = "";
    while(ix < sizeof(election[i+1]))
    {
        result += election[i+1][ix] + ": "+election[i+1][ix+1]+", ";
        ix+=2;
    }
    write_file(RANGER_LOG,"ELECTION: Captain of "+COMPANY[election[i]]+": "+result+ctime(time())+"\n");
    write_file(ELECTION_LOG, "ELECTION: Captain of "+COMPANY[election[i]]+": "+result+ctime(time())+"\n");

    election = exclude_array(election,i,i+3);
    save_object(COUNCIL);

    if(ncap = find_player(lower_case(elected)))
        make_captain(ncap);
}

int end_of_election(int i) 
{ 
    if((time() - election[i+3]) < WEEK && sizeof(election[i+2]) > 0)
        return 0;

    evaluate_votes(i);
    return 1;
}

string ranger_vote(object ranger, string vote)
{
    string  name     = ranger->query_real_name();
    int     icp,
            ivote,
            ivoter,
            icand;

    icp = GUILD->query_company(name);
    if(icp <= 0 || icp >= sizeof(COMPANY))
    {
        NF("You cannot vote here, you are not a member of a Ranger company!\n");
        return 0;
    }

    init_council_object();

    if((ivote = member_array(icp,election)) == -1)
    {
        NF("As a Ranger of "+COMPANY[icp]+", you are not called to vote!\n");
        return 0;
    }

    if(sizeof(election[ivote+1]) < 4)
    {
        NF("The council has not decided on a second candidate for the elections yet!\n");
        return 0;
    }

    if((ivoter = member_array(name,election[ivote+2])) == -1)
    {
        NF("You have already cast your vote!\n");
        return 0;
    }

    vote = CAP(lower_case(vote));
    if((icand = member_array(vote,election[ivote+1])) == -1)
    {
        NF("Please vote for one of the candidates!\n");
        return 0;
    }

    if(end_of_election(ivote))
    {
        NF("You cannot vote anymore, the election is over!\n");
        return 0;
    }

    election[ivote+2] = exclude_array(election[ivote+2],ivoter,ivoter);
    election[ivote+1][icand+1]++;
    save_object(COUNCIL);
    return "You vote for "+CAP(vote)+" for Captain of the Rangers of "+COMPANY[icp]+"!\n";
}

varargs int query_election(int icp, string name)
{
    int     ivote;

    init_council_object();

    if( (ivote = member_array(icp,election)) == -1 )
        return 0;

    if(sizeof(election[ivote+1]) < 4)
        return 0;

    if(end_of_election(ivote))
        return 0;

    if(stringp(name))
    {
        name = lower_case(name);
        if(member_array(name,election[ivote+2]) == -1)
            return 0;
    }

    return 1;
}

int filter_string(mixed s) { return stringp(s); }

string query_candidates(int icp)
{
    int     ivote;
    string *cands;

    init_council_object();

    if( (ivote = member_array(icp,election)) == -1 )
        return 0;

    if(sizeof(election[ivote+1]) < 4)
        return 0;

    if(end_of_election(ivote))
        return 0;

    cands = filter(election[ivote+1],"filter_string",TO);
    return implode(cands,", ");
}
    
string *query_elected()
{
    return elected_captain;
}

int call_for_impeachment(object caller, string victim)
{
    int     rank = is_council_member(victim),
            si;
    string  who = caller->query_name(),
            msg;

    NF("Only council members may call for the impeachment of a Captain of the Rangers!\n");
    if (!is_council_member(who))
        return 0;

    NF("You can only impeach a Captain of the Rangers!\n");
    if (rank == 0 || rank > NCAP)
        return 0;

    init_council_object();

    /* are there three Captains in office? */
    NF("You can only call for an impeachment if there are three Captains in office!\n");
    if (!stringp(council[0]) || !stringp(council[1]) || !stringp(council[2]))
        return 0;

    /* is there already a call for impeachment? */
    if (sizeof(impeached_captain))
    {
        /* Is it against the same person? */
        if (impeached_captain[0] != victim)
        {
            /* Is the old victim still a captain? */
            rank = is_council_member(impeached_captain[0]);
            if (rank == 0 || rank > NCAP)
                impeached_captain = ({victim, who, });
            else
            {
                NF("There is already a call for the impeachment of " + impeached_captain[0] + "!\n");
                return 0;
            }
        }
        else
        {
            /* did I do this already once before? */
            NF("You already called for the impeachment of " + victim + ".\n");
            if (member_array(who, impeached_captain) > 0)
                return 0;
            impeached_captain += ({who, });
        }
    }
    else
        impeached_captain = ({victim, who, });

    save_object(COUNCIL);

    msg = " for the impeachment of " + victim + ".\n";
    si = sizeof(impeached_captain);
    write("You " + (si == 2 ? "have called" : "support the call") + msg);
    say(QCTNAME(caller) + (si == 2 ? " has called" : " supports the call") + msg);

    if (si > 2)
        tell_room(environment(caller), implode(impeached_captain[1..si-2], ", ") + " and " +
            impeached_captain[si - 1] + " are calling for the impeachment of " + victim + ".\n");

    return 1;
}

int do_impeach(object caller, string victim)
{
    int     rank = is_council_member(victim),
            si;
    string  who = caller->query_name(),
            msg;
    object  cap;

    NF("Only council members may impeach a Captain of the Rangers!\n");
    if (!is_council_member(who))
        return 0;

    NF("You can only impeach a Captain of the Rangers!\n");
    if (rank == 0 || rank > NCAP)
        return 0;

    init_council_object();

    /* is there already a call for impeachment? */
    NF("You should first 'start impeachment of <name>' and then try to get support for the move!\n");
    if (!(si = sizeof(impeached_captain)))
        return 0;

    /* Is it against the same person? */
    NF("There is already a call for the impeachment of " + impeached_captain[0] + "!\n");
    if (impeached_captain[0] != victim)
        return 0;

    if (si < 4)
    {
        if (si == 2)
            NF(BSN("Presently, only " + impeached_captain[1] +
                " is calling for the impeachment of " + victim +
                ". You will need at least two more council members " +
                "supporting the move before you can " +
                "impeach " + victim + "."));
        else
            NF(BSN("Presently, only " + impeached_captain[1] + " and " +
                impeached_captain[2] + " are calling for the impeachment of " +
                victim + ". You will need at least one more council " +
                "member supporting the move before you can impeach " +
                victim + "."));
        return 0;
    }

    // demote the Captain
    msg = victim + ", Captain of the Rangers of "+COMPANY[rank]+"!\n";
    say(QCTNAME(caller) + " impeaches " + msg);
    write("You impeach " + msg);
    msg = caller->query_name()+" impeaches " + msg +
        "The move was supported by " + implode(impeached_captain[1..si-2], ", ") +
        " and " + impeached_captain[si-1] + ". "+ctime(time())+"\n";
    write_file(RANGER_LOG,msg);
    write_file(ELECTION_LOG,msg);
    impeached_captain = ({});
    save_object(COUNCIL);

    remove_ranger(victim);
    remove_ranger(council[rank+NCAP-1]);
    remove_ranger(query_officers()[rank+CSIZE-1]);

    if (objectp(cap = find_player(lower_case(victim))))
        set_bin_bits(1,18,2,cap,1);
    call_election(rank, 0);

    return 1;
}

string *query_impeached_captain()
{
    return impeached_captain;
}

string query_impeachment()
{
    int     si;
    string  msg;

    init_council_object();

    if ((si = sizeof(impeached_captain)) < 2)
    {
        impeached_captain = ({});
        save_object(COUNCIL);
        return 0;
    }

    if (!query_captain(impeached_captain[0]))
    {
        impeached_captain = ({});
        save_object(COUNCIL);
        return 0;
    }

    if (si == 2)
        msg = impeached_captain[1] + " is";
    else if (si == 3)
        msg = impeached_captain[1] + " and " + impeached_captain[2] + " are";
    else
        msg = implode(impeached_captain[1..si-2], ", ") + " and " + impeached_captain[si-1] + " are";

    msg += " calling for the impeachment of " + impeached_captain[0] + "\n";

    return "\n" + BSN(msg);
}

int veto_impeach(object caller, string victim)
{
    int     rank,
            si;
    string  who = caller->query_name(),
            msg;

    NF("Only a Captain may veto an impeachment!\n");
    if (!query_captain(who))
        return 0;

    init_council_object();

    if ((si = sizeof(impeached_captain)) < 2)
    {
        NF("There is no call for an impeachment!\n");
        impeached_captain = ({});
        save_object(COUNCIL);
        return 0;
    }

    if (!query_captain(impeached_captain[0]))
    {
        NF(BSN("The call for the impeachment of " + impeached_captain[0] +
            " has been cancelled since " + impeached_captain[0] +
            " is not a Captain of the Rangers anymore!"));
        impeached_captain = ({});
        save_object(COUNCIL);
        return 0;
    }

    NF("There is no call for the impeachment of " + victim + "!\n");
    if (impeached_captain[0] != victim)
        return 0;

    NF("You cannot veto your own impeachment!\n");
    if (impeached_captain[0] == who)
        return 0;

    impeached_captain = ({});
    save_object(COUNCIL);
    write("You veto the impeachment of " + victim + ".\n");
    say(QCTNAME(caller) + " vetoes the impeachment of " + victim + ".\n");

    return 1;
}

/*
 * Function name:	check_ranger_loc_ok
 * Description	:	pl's access to ranger guildhouses has just been 
 *			limited or removed. be sure s/he is still allowed
 *			to be where s/he is.  if not, provide an escort out.
 * Arguments	:	object pl -- the punished player
 *			int ptype -- NOACCESS or EXPULSION
 */
public void
check_ranger_loc_ok(object pl, int ptype)
{
    string	guildhall,
		room,
		dest;
    object	env;

    if ( !objectp(pl) ||
	 !objectp(env = ENV(pl)) ||
    	 sscanf(file_name(env), (RANGER_DIR+"%s/%s"), guildhall, room) != 2 )
    {
	return;
    }
    if ( guildhall == "ithilien" )
    {
	if ( ptype == EXPULSION )
	{
	   dest = (ITH_DIR+"nforest/fpath/bushes5");
	}
	else if ( room != "entrance" )
	{
	    dest = "/entrance";
	}
    }
    else if ( guildhall == "north" )
    {
	if ( ptype == EXPULSION )
	{
	    dest = (FORNOST_DIR+"hideout_entr");
	}
	else if ( room != "stairs" )
	{
	    dest = "/stairs";
	}
    }
    else if ( guildhall == "gondor" )
    {
	if ( ptype == EXPULSION )
	{
	    dest = (DRUEDAIN_DIR+"rangerpath3");
	}
	else
	{
	    switch ( room )
	    {
	    case "armroom":		dest = "/startchamber";	break;
	    case "office":		dest = "/uphall";	break;
	    case "ranger_library":	dest = "/upcorr1";	break;
	    case "gondor_council":	dest = "/uphall";	break;
	    case "lib_office":	dest = "/upcorr1";	break;
	    }
	}
    }
    if ( !strlen(dest) )
    {
	return;
    }
    if ( ptype == NOACCESS )
    {
	dest = RANGER_DIR+guildhall+dest;
    }
    tell_object(pl, "Two sturdy rangers arrive and escort you from "+
	      "the room in grim silence.\n");
    tell_room(env, "Two sturdy rangers arrive and escort "+
	QTNAME(pl)+" from the room in grim silence.\n", pl);
    pl->move_living("M", dest);

    /* do not say "into the room" -- may be outdoors */
    tell_room(ENV(pl),
	"Two sturdy rangers escort "+QTNAME(pl)+" in, "+
	"then silently depart.\n", pl);
}
