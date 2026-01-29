/* Admin room in the Knights of Solamnia
 * /d/Krynn/solamn/guild/admin.c
 *
 * coded a long time ago by Nick and Percy (1992)
 * complete revision 1994 by Aridor
 * added the actions and awards 03/95 by Aridor
 * speed improvements by reducing calls to save_object 07/95, Aridor
 *
 *
 * This file controls the vital parts of the Knight guild.
 *  - conclave
 *  - rewards and punishments
 *  - squire/sponsor relations
 *  - assistants to the conclave
 *  - complete knights' data!
 */

#pragma strict_types
#pragma no_inherit
#pragma no_clone
#pragma save_binary

#include "/d/Krynn/common/defs.h"

inherit R_FILE

#include <std.h>
#include "guild.h"
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <config.h>

#define SPONSOR_TREE     "/d/Krynn/solamn/guild/sponsor_tree"
#define BACKUP_SAVE_FILE "/d/Krynn/solamn/guild/log/backup_admin"
#define MAX_ACTIONS     6
#define AWARD_PRETTY_STRING ({"the Twirled Braid","the Golden Ribband",\
			      "the emblem of the Honorary Rose",\
			      "the emblem of the Ceremonial Sword",\
			      "the emblem of the Ornamented Crown"})
/* Knight symbol award descriptions suggested by Danov. */


/*
 * Prototypes
 */
private void load_board();
public nomask int remove_knight_sponsorlist(string who);
public nomask int remove_squire_sponsorlist(string who);
public nomask varargs void leave(object ob, int force);
public nomask int is_assistant(string str);
private void add_award(object who, string what);

mapping allknights;
string *squirelist,
       *knightlist,
       crown, sword, rose,             /* current conclave */
       crownhigh, swordhigh, rosehigh, /* conclave runnerups */
       oldcrown, oldsword, oldrose;    /* previous conclave members */
int crownpres, swordpres, rosepres;    /* prestige of the runnerups */
mixed *actionlist = ({ });            /* put all actions for a knight into one big list */
/* the actionlist looks like this: ({ ({ <targetname>, <initiatorname>, <reason>, <type> [, <multiplier>] }),
 *                                    ({ ... }) ... })
 * additional arguments may be appended at the end of 
 */
mixed *assistants = ({({}),({}),({}),({}),({}),({}),({})});
                                       /* assistants to the conclave */
mixed *awards = ({});
static string temp_knight_slvl_down_to = 0;

void
create_krynn_room()
{
    set_short("Admin room");
    set_long("You are in the administration room of the Solamnian Knights.\n\n"
	     + "Grace recently found the room and took it over. It has been " 
	     + "thoroughly redecorated to suit her tastes and position as one "
	     + "of the Guildmasters of the Knights of Solamnia.\n"
	     + "The board here is for wizard discussions about the guild.\n"
	     + "There is a sign describing some of the administrative commands "
	     + "possible in this room.\n");
    
    
    add_exit(ENTRANCE, "entrance");
    add_exit("/d/Krynn/workroom", "krynn");
    
    seteuid(getuid(TO));
    restore_object(ADMIN_FILE);
    
    load_board();
    set_alarm(3.0,0.0,"remove_expired_knight_squire_relations");
    OUTSIDE;
    add_prop(ROOM_I_NO_CLEANUP, 1);

    (SPONSOR_TREE)->load_me();
}

void
init()
{
    ADA("read");
    ADA("relation");
    ADA("actions");
    ADA("list");
    ADD("list_awards","awards");
    ::init();
}

public int
list_awards(string str)
{
    dump_array(awards);
    return 1;
}

public int
list(string str)
{
    string str1;
    int *check;
    string *names;
    int i = -1,size;
    NF("List what?\n");
    if (!str)
      return 0;
    if (sscanf(str,"%srose%s",str1,str1) == 2)
      check = ({5});
    else if (sscanf(str,"%ssword%s",str1,str1) == 2)
      check = ({4});
    else if (sscanf(str,"%scrown%s",str1,str1) == 2)
      check = ({3});
    else if (sscanf(str,"%socc%ssquire%s",str1,str1,str1) == 3)
      check = ({2});
    else if (sscanf(str,"%slay%ssquire%s",str1,str1,str1) == 3)
      check = ({12});
    else if (sscanf(str,"%ssquire%s",str1,str1) == 2)
      check = ({2,12});
    else if (sscanf(str,"%socc%sblack%s",str1,str1,str1) == 3)
      check = ({1});
    else if (sscanf(str,"%slay%sblack%s",str1,str1,str1) == 3)
      check = ({11});
    else if (sscanf(str,"%sblack%s",str1,str1) == 2)
      check = ({1,11});
    else if (sscanf(str,"%socc%s",str1,str1) == 2)
      check = ({1,2,3,4,5});
    else if (sscanf(str,"%slay%s",str1,str1) == 2)
      check = ({11,12});
    else if (sscanf(str,"%sall%s",str1,str1) == 2)
      check = ({1,2,3,4,5,11,12});
    else
      return 0;
    names = m_indexes(allknights);
    size = sizeof(names);
    while(++i < size)
      if (member_array(allknights[names[i]], check) >= 0)
	write(C(names[i]) + " ");
    write("\n");
    return 1;
}

public int
actions(string str)
{
    write("Pending actions:\n\n");
    dump_array(actionlist);
    return 1;
}

private void
load_board()
{
    object bb;
    
    bb = clone_object("/std/board");
    bb->set_board_name("/d/Krynn/solace/guild/log/admin_data");
    bb->set_num_notes(20);
    bb->set_silent(0);
    bb->set_show_lvl(0);
    bb->set_remove_lvl(15);
    bb->set_remove_str("Sorry, only a wizard may remove the notes.\n");  
    bb->set_err_log("/d/Krynn/solace/guild/log/board_error");
    bb->move(this_object());
}


private void
remove_expired_knight_squire_relations()
{
    int i = -1, size;
    string *mylist = knightlist + ({ });

    seteuid(getuid());

    size = sizeof(mylist);

    while (++i < size)
      if (!(SECURITY)->exist_player(L(mylist[i])))
	remove_knight_sponsorlist(mylist[i]);

    size = sizeof(mylist = squirelist + ({ }));

    i = -1;
    while (++i < size)
      if (!(SECURITY)->exist_player(L(mylist[i])))
	remove_squire_sponsorlist(mylist[i]);

    i = -1;
    size = m_sizeof(allknights);
    mylist = m_indexes(allknights);
    while(++i < size)
      if (!(SECURITY)->exist_player(L(mylist[i])))
	TO->remove_knight(mylist[i]);
}


static int
read(string str)
{
    NF("Read what?\n");
    if(str != "sign")
      return 0;
    write("The ban and pres command previously available in this room have " +
	  "been disallowed. You can type 'relation squire' and 'relation " +
	  "knight' here to get a list of all sponsors and their respective " +
	  "squires. One version sorts according to squire names, the other " +
	  "with respect to sponsor names. The 'actions' command gives a list " +
	  "of all pending actions (reward,degrade,etc.) and 'list <type>'" +
	  "displays a list of all knights that belong to <type>. Possible " +
	  "is: all, layman, occupational, crown, sword, rose, squires, black, and " +
	  "a combination of these (eg. 'lay squires', 'occ black'). NOTE: This " +
	  "list may not be accurate as of now, but it'll become better and better " +
	  "with time :)\n");
    return 1;
}    


private int
lex_less_than_1(string *str1, string *str2)
{
    if (str1[0] > str2[0])
      return 1;
    if (str1[0] == str2[0])
      return 0;
    return -1;
}

private int
lex_less_than_2(string *str1, string *str2)
{
    if (str1[1] > str2[1])
      return 1;
    if (str1[1] == str2[1])
      return 0;
    return -1;
}

static int
relation(string str)
{
    int i,odd,k,half;
    mixed *kn = ({ });
    for(i=0;i<sizeof(knightlist);i++)
      kn += ({ ({ knightlist[i], squirelist[i] }) });
    if (str == "squire" || str == "s")
      kn = sort_array(kn,"lex_less_than_2");
    else
      kn = sort_array(kn,"lex_less_than_1");
    write("\nSPONSOR      SQUIRE      | SPONSOR      SQUIRE\n");
    write("----------------------------------------------------\n");
    half = sizeof(kn) / 2;
    odd  = sizeof(kn) % 2;
    for(i=0;i<half;i++)
      {
	  k = (odd ? i + half + 1 : i + half);
	  write(sprintf("%-11s  %-11s | %-11s  %-11s\n", kn[i][0],
			kn[i][1], kn[k][0], kn[k][1]));
      }
    if (odd)
      write(sprintf("%-11s  %-11s |\n", kn[half][0], kn[half][1]));
    return 1;
}

/*****************************************************************************
 * Keep track of who is a knight and what order s/he is in.
 */

public varargs int
add_knight(string knight, int level, int lay=0)
{
    int lev = 10 * lay + level;

    if (!allknights)
      allknights = ([]);

    allknights += ([ knight:lev ]);

    save_object(ADMIN_FILE);
    /*save_object(BACKUP_SAVE_FILE);*/
    return 1;
}

/* Returns the knight level of a knight:
 *    0 NOT a knight!       1 black knight
 *    2 squire              3 crown
 *    4 sword               5 rose
 *    11 black knight (layman)
 *    12 squire (layman)
 */
public int
query_knight_status(string knight)
{
    if (!allknights)
      allknights = ([]);

    return allknights[knight];
}

public int
remove_knight(string knight)
{
    if (!allknights)
      allknights = ([]);

    allknights = m_delete(allknights, knight);
    remove_knight_sponsorlist(knight);
    remove_squire_sponsorlist(knight);

    save_object(ADMIN_FILE);
    /*save_object(BACKUP_SAVE_FILE);*/
    return 1;
}

/*****************************************************************************
 * Handle the sponsor-squire relationships here. Add relationships, remove 'em
 * tests, all that follows below.
 */

/* Returns the knight attached to a squire or none if there isn't one
 */
public string
get_knight_squire_s(string squire)
{
    string name;
    int pos;
    
    name = C(L(squire));
    
    pos = member_array(name, squirelist);
    if (pos >= 0)
      return knightlist[pos];
    
    return "none";
}

public string
get_knight_squire(object squire)
{
    return get_knight_squire_s((string)squire->query_name());
}

/* Returns the squires attached to a knight or none
 */
public string *
get_squire_knight_s(string knight)
{
    string name, *banishlist2;
    int *pos,numberret, flag, loopvar, flag2;
    
    if (!pos)
      pos = ({ });
    flag = 0;
    name = C(L(knight));
    for (flag = 0; flag < sizeof(knightlist); flag++)
      {
	  if (knightlist[flag] == name)
	    {
		flag2 = 1;
		numberret = flag;
		pos += ({ numberret });
	    }
      }
    if (!flag2)
      return ({ "none" });
    if (!banishlist2);
    banishlist2 = ({ });
    if (!sizeof(pos))
      {
	  banishlist2 += ({ squirelist[numberret] });	
	  return banishlist2;
      }
    for (loopvar = 0; loopvar < sizeof(pos); loopvar++)
      {
	  numberret = pos[loopvar];
	  banishlist2 += ({ squirelist[numberret] });
      }
    return banishlist2;
    
}

public string *
get_squire_knight(object knight)
{
    return get_squire_knight_s((string)knight->query_name());
}

/* Adds a knight to the knightlist
 */
static void
add_knightlist(string squire, string knight)
{
    if (!knightlist)
      knightlist = ({ });
    knightlist += ({ knight });
    save_object(ADMIN_FILE);
    /*save_object(BACKUP_SAVE_FILE);*/
    write_file(SPONSOREDPATH, BS(ctime(time()) + ", " + capitalize(knight) +
				 " sponsored " +
				 capitalize(squire), 75));
}

/* Adds a squire to the squirelist
 */
static void
add_squirelist(string squire, string knight)
{
    if (!squirelist)
      squirelist = ({ });
    squirelist += ({ squire });
    save_object(ADMIN_FILE);
    /*save_object(BACKUP_SAVE_FILE);*/
    
}

static void
update_sponsor_tree(string knight, string squire)
{
    (SPONSOR_TREE)->add_new_relation(L(knight),L(squire),0);
}

/* Add a knight and squire to the lists
 */
public void
add_relation(string knight, string squire)
{
    add_knightlist(C(L(squire)), C(L(knight)));
    add_squirelist(C(L(squire)), C(L(knight)));
    set_alarm(2.0,0.0,"update_sponsor_tree",knight,squire);
}


/* Removes a squire and his knight from the lists
 */
public nomask int
remove_squire_sponsorlist(string who)
{
    string mess, knight;
    object sq, kn;
    int pos;
    string squire = C(L(who));
    
    if (!(member_array(squire, squirelist) >= 0))
      return 0;
    pos = member_array(squire, squirelist);
    knight = knightlist[pos];
    knightlist[pos] = "KNIGHTWIPERK1";
    squirelist -= ({ squirelist[pos] });
    knightlist -= ({ knightlist[pos] });
    write_file(SPONSOREDPATH, BS(ctime(time()) + ", " + capitalize(knight) +
				 " stopped sponsoring " +
				 capitalize(squire), 75));
    
    save_object(ADMIN_FILE);
    /*save_object(BACKUP_SAVE_FILE);*/

    if (sq = find_player(lower_case(squire)))
      {
	  mess = "You are no longer being sponsored by " + knight + ".\n";
	  sq->catch_msg(mess);
      }
    if (kn = find_player(lower_case(knight)))
      {
	  mess = "You are no longer sponsoring " + squire + ".\n";
	  kn->catch_msg(mess);
      }
    return 1;
}

/* Removes a knight and squires from the lists
 */
public nomask int
remove_knight_sponsorlist(string who)
{
    string mess, squire;
    object sq, kn;
    int pos, flag;
    string knight = C(L(who));
    
    if (!(member_array(knight, knightlist) >= 0))
      return 0;
    flag = 1;
    while (flag)
      {
	  pos = member_array(knight, knightlist);
	  squire = squirelist[pos];
	  squirelist[pos] = "SQUIREWIPERK1";
	  knightlist[pos] = "KNIGHTWIPERK1";
	  squirelist -= ({ squirelist[pos] });
	  knightlist -= ({ knightlist[pos] });
	  
	  write_file(SPONSOREDPATH, BS(ctime(time()) + ", " + capitalize(knight) +
				       " stopped sponsoring " +
				       capitalize(squire), 75));
	  
	  save_object(ADMIN_FILE);
	  /*save_object(BACKUP_SAVE_FILE);*/
	  
	  if (sq = find_player(lower_case(squire)))
	    {
		mess = "You are no longer being sponsored by " + knight + ".\n";
		sq->catch_msg(mess);
	    }
	  if (kn = find_player(lower_case(knight)))
	    {
		mess = "You are no longer sponsoring " + squire + ".\n";
		kn->catch_msg(mess);
	    }
	  if (!(member_array(knight, knightlist) >= 0))
	    flag = 0;
      }
    return 1;
}

/* Function returns 1 if player is found in the knightlist
 */
public int
check_knightlist(string player)
{
    int i, limit;
    limit = 0;
    for (i = 0; i < sizeof(knightlist); i++)
      {
	  if (knightlist[i] == player)
	    limit += 1;
      }
    return limit;
    
    return 0;
}

/* Function returns 1 if player is found in the squirelist
 */
public int
check_squirelist(string player)
{
    if (member_array(player, squirelist) >= 0)
      return 1;
    return 0;
}


/****************************************************************************
 * Service function for the conclave handling, set/clear the current conclave
 * and store the runner-up for conclave position (as far as prestige goes).
 * Query functions for all conclave information are provided, too.
 */
public string
crown_highest()
{
    return crownhigh;
}

public string
sword_highest()
{
    return swordhigh;
}

public string
rose_highest()
{
    return rosehigh;
}

public int
query_crown_high()
{
    return crownpres;
}

public int
query_sword_high()
{
    return swordpres;
}

public int
query_rose_high()
{
    return rosepres;	
    
}

public void
set_crown_high(int high, string player)
{
    if (extract(player,-2) == "jr")
      return;
    crownpres = high;
    crownhigh = player;
    save_object(ADMIN_FILE);
    save_object(BACKUP_SAVE_FILE);
}

public void
set_sword_high(int high, string player)
{
    if (extract(player,-2) == "jr")
      return;
    swordpres = high;
    swordhigh = player;
    save_object(ADMIN_FILE); 
    save_object(BACKUP_SAVE_FILE);
}

public void
set_rose_high(int high, string player)
{
    if (extract(player,-2) == "jr")
      return;
    rosepres = high;
    rosehigh = player;
    save_object(ADMIN_FILE);
    save_object(BACKUP_SAVE_FILE);
}

/* Returns the player who is the conclave member of 'order'
 */
public nomask string
query_conclave(mixed order)
{   
    if (stringp(order))
      {
	  if (order == "crown")
	    return crown;
	  if (order == "sword")
	    return sword;
	  if (order == "rose")
	    return rose;
      }
    else if (intp(order))
      {
	  if (order == 3)
	    return crown;
	  if (order == 4)
	    return sword;
	  if (order == 5)
	    return rose;
      }
    return "none";      
}

/* Returns if player is a member of the conclave and for which order.
 */
public nomask int
is_conclave(string who)
{   
    if (crown && C(who) == C(crown))
      return 3;
    if (sword && C(who) == C(sword))
      return 4;
    if (rose && C(who) == C(rose))
      return 5;
    return 0;
}

/* adds a player to the conclave of 'order'
 */
public void
add_conclave(string player, string order)
{
    if (!crown)
      crown = "";
    if (!sword)
      sword = "";
    if (!rose)
      rose = "";
    if (order == "crown" && oldcrown != player)
      crown = player;
    if (order == "sword" && oldsword != player)
      sword = player;
    if (order == "rose" && oldrose != player)
      rose = player;
    save_object(ADMIN_FILE);
    save_object(BACKUP_SAVE_FILE);
}

/* removes a conclave member of 'order'
 */
public void
remove_conclave(string order)
{
    if (!crown)
      crown = "";
    if (!sword)
      sword = "";
    if (!rose)
      rose = "";
    if (order == "crown")
      {
	  oldcrown = crown;
	  crown = "";
      }
    if (order == "sword")
      {
	  oldsword = "sword";
	  sword = "";
      }
    if (order == "rose")
      {
	  oldrose = "rose";
	  rose = "";
      }
    save_object(ADMIN_FILE);
    save_object(BACKUP_SAVE_FILE);
}

/****************************************************************************
 * Service functions for the perform_* functions. write something in a log.
 * see if the person is allowed to do something.
 */
private int
log_action(string path, string message)
{
    string mes = message;
    if (temp_knight_slvl_down_to)
      mes += " down to " + temp_knight_slvl_down_to;

    if (path)
      write_file(KNIGHT_LOG + path, ctime(time())[4..15] + " " + mes + ".\n");
    write_file(KNIGHT_ALL_LOG, ctime(time())[4..15] + " " + mes + ".\n");
    return 1;
}

public nomask int
check_can_perform_command(object who)
{
    if (who->query_knight_sublevel() == 11 ||
	is_assistant(who->query_real_name()) ||
	member_array(who->query_name(), GUILDMASTERS) > -1)
      return 1;
    return 0;
}

/****************************************************************************
 * Execute the different actions here. The syntax for each of these
 * functions is 'perform_*(object who, string initiator, string reason)'.
 * where the * marks the <type> of the action to be taken.
 * Note: although these functions are declared public due to the dirty call
 *       via call_other, they can only be called from inside this object.
 */
public nomask int
perform_banishment(object who, string initiator, string reason, mixed additional)
{
    if (previous_object() != TO &&
	MASTER_OB(previous_object()) != (MEDALPATH))
      return 0;
    if (who->query_knight_level() > L_BROSE)
      return 0;
    who->set_bit(GUILD_GROUP, BANISH_BIT);
    if (stringp(additional) && additional == "soft")
      leave(who,2);
    else
      leave(who,1);
    who->catch_msg("You have been banished from the knighthood by " +
		   C(initiator) + ", because " + reason + ".\n");
    return 1;
}

public nomask int
perform_pardon(object who, string initiator, string reason, mixed additional)
{
    /* Cannot pardon knights! */
    return 0;
}

public nomask int
perform_degradation(object who, string initiator, string reason, mixed additional)
{
    mixed lvl;
    int i, times = (intp(additional) ? additional : 1);
    int slvl, bound_value;
    string dname = who->query_name();
    if (previous_object() != TO)
      return 0;
    NF(C(dname) + " is not a knight.\n");
    if (!MEMBER(who) && !LAYMAN(who))
      return 0;
    NF(C(dname) + " is a conclave member!\n");
    if (who->query_knight_sublevel() == 11)
      return 0;
    if (times < 1 || times > MAX_ACTIONS)
      times = 1;
    for(i=0;i<times;i++)
      {
	  lvl = who->query_knight_level();
	  slvl = who->query_knight_sublevel();
	  if (lvl == L_BROSE)
	    return perform_banishment(who, initiator, reason, additional);
	  else if (slvl == 1)
	    {
#if NEW_KNIGHTS
		who->set_knight_level(lvl - 1);
#else
		if (lvl == L_SQUIRE)
		  who->set_knight_level(L_BROSE);
		else
		  who->set_knight_level(L_SQUIRE);
#endif
		break; /* No more reductions when the knight level has changed! */
	    }
	  else
	    {
		bound_value = K_LEVEL_ARRAY[slvl - 2] + 4;
		who->set_skill(SS_PRESTIGE_ST, bound_value);
		who->change_prestige(-1,0);
	    }
      }

    if (who->query_knight_level() == L_BROSE)
      lvl = "black knight";
    else if (who->query_knight_level() == L_SQUIRE)
      lvl = "squire";
    else if (who->query_knight_level() == L_CROWN)
      lvl = "crown knight";
    else if (who->query_knight_level() == L_SWORD)
      lvl = "sword knight";
    else if (who->query_knight_level() == L_ROSE)
      lvl = "rose knight";
    
    slvl = who->query_knight_sublevel();
    temp_knight_slvl_down_to = "" + lvl +
      (lvl != "black knight" ? " level " + slvl : "");
    who->catch_msg("You have been degraded down to " + temp_knight_slvl_down_to +
		   " by " + C(initiator) + ", because " + reason + ".\n");
    return 1;
}

public nomask int
perform_upgrade(object who, string initiator, string reason, mixed additional)
{ 
    int times = (intp(additional) ? additional : 1);
    if (previous_object() != TO)
      return 0;
    if (times < 1 || times > MAX_ACTIONS)
      times = 1;
    who->change_prestige(15000 * times);
    who->catch_msg("You have been rewarded by " + C(initiator) + " with prestige, " +
		   "because " + reason + ".\n");
    return 1;
}

public nomask int
perform_disgrace(object who, string initiator, string reason, mixed additional)
{
    if (previous_object() != TO &&
	MASTER_OB(previous_object()) != (MEDALPATH))
      return 0;
    who->set_skill(SS_DISGRACED, REALAGE(who) + SECONDS_IN_2_DAYS);
    who->catch_msg("You have disgraced the knighthood because " +
		   reason + ". You are now not allowed to train, use the " +
		   "armoury and lead teams for two days of your playing time. " +
		   "This punishment was laid upon you by " + C(initiator) + ".\n");
    return 1;
}

public nomask int
perform_forgive(object who, string initiator, string reason, mixed additional)
{
    int sk = who->query_skill(SS_DISGRACED);
    if (previous_object() != TO)
      return 0;
    if (!sk)
      return 0;
    
    who->remove_skill(SS_DISGRACED);
    if (sk < REALAGE(who))
      return 0;
    who->catch_msg("You have been forgiven your disgrace of the " +
		   "knighthood by " + C(initiator) + ". You are now " +
		   "allowed to train, lead teams and access the armoury " +
		   "again.\n");
    return 1;
}

public nomask int
perform_award(object who, string initiator, string reason, mixed withwhat)
{
    if (previous_object() != TO)
      return 0;
    add_award(who, withwhat);
    who->catch_msg(BS("You have been awarded by " + C(initiator) +
		   " with " + withwhat + " because " + reason + ".\n", 70));
    return 1;
}


/********************************************************
 * Actions that work on Non-Knights
 *******************************************************/
public nomask int
perform_non_knight_pardon(object who, string initiator, string reason, mixed additional)
{
    if (previous_object() != TO)
      return 0;
    
    who->clear_bit(GUILD_GROUP,BANISH_BIT);
    who->catch_msg("You have been pardoned from the banishment of the Solamnian " +
		   "Knighthood because " + reason + ".\n");
    return 1;
}

/* non Knights can be awarded, too, if they're logged in */
public nomask int
perform_non_knight_award(object who, string initiator, string reason, mixed withwhat)
{
    object award_obj;

    if (previous_object() != TO)
      return 0;

    add_award(who, withwhat);
    award_obj = P(NON_KN_AWD_ID,who);
    if (!award_obj)
      clone_object(NON_KN_AWD_OB)->move(who,1);
    who->catch_msg(BS("You have been awarded by " + C(initiator) +
		   " with " + withwhat + " because " + reason + ".\n", 70));
    return 1;
}


/****************************************************************************
 * Here follows the code to maintain the actionlist that will ensure that
 * punishments and rewards work, too, while the target is not logged in.
 */
private int
perform_action_now(string initiator, object who, string reason,
		   string type, mixed additional)
{
    int ret_val;
    string add_string = "";

    if (MEMBER(who) || LAYMAN(who))
      ret_val = call_other(TO,"perform_" + type, who, initiator, reason,
			   additional);
    else
      ret_val = call_other(TO,"perform_non_knight_" + type, who, initiator,
			   reason, additional);
    if (intp(additional))
      if (additional)
	add_string = "" + additional + " times";
    if (stringp(additional))
      add_string = additional;

    if (ret_val)
      log_action(type, C(type) + " (" + add_string + ") for " + who->query_name() +
		 " by " + C(initiator) + " because " + reason);
    else
      log_action(type, "Failed! " + C(type) + " (" + add_string + ") for " +
		 who->query_name() + " by " + C(initiator) + " because " +
		 reason);

    return ret_val;
}

int
ari_dirty_hack(string who, string initiator, string reason, string type,
	       string additional)
{
  actionlist += ({ ({ who, initiator, reason, type,
			  additional }) });
}

private int
mark_action_to_perform_later(object initiator, string who, string reason,
			     string type, mixed additional)
{
    string add_string = "";
    if (intp(additional))
      if (additional)
	add_string = "" + additional + " times";
    if (stringp(additional))
      add_string = additional;
    log_action(type, C(who) + " put in " + type + " list by " +
	       initiator->query_name() + " (" + add_string + ") because " +
	       reason);
    actionlist += ({ ({ who, initiator->query_real_name(), reason, type,
			  additional }) });
    save_object(ADMIN_FILE);
    save_object(BACKUP_SAVE_FILE);
    return 2;
}

private varargs int
perform_action(object initiator, string who, string reason,
	       string type, mixed additional=0)
{
   object target = find_player(who);
   int ret_val;
   
   if (target)
     ret_val = perform_action_now(initiator->query_name(), target,
				  reason, type, additional);
   else if (TO->query_knight_status(who)) /*only knights can be put in list*/
     ret_val = mark_action_to_perform_later(initiator, who, reason, type,
					    additional);
   else
     ret_val = 0;
   return ret_val;
}

public int
action_entry(int id)
{
    /* loop through actionlist and remove action number id
     * if id is <=0, display all actions pending
     * if any action was done, return 1 else return 0 
     */
    int i;
    mixed temp = 0;
    int donesomething = 0;
    mixed *loop_arr = actionlist + ({ });
    if (SECURITY->query_wiz_rank(TP->query_real_name()) < WIZ_LORD)
      {
	  write("You are not allowed to perform this command.\n");
	  return 0;
      }
    for(i=0;i<sizeof(loop_arr);i++)
      {
	  if (sizeof(loop_arr[i]) > 4)
	    temp = loop_arr[i][4];
	  if (id <= 0)
	    write("#" + (i+1) + "    " + C(loop_arr[i][3]) + " for " + loop_arr[i][0] +
		  " because " + loop_arr[i][2] + " by " + loop_arr[i][1] +
		  " (add: " + temp + ").\n");
	  else if ((i+1) == id)
	    {
		write("REMOVING: " + C(loop_arr[i][3]) + " for " + loop_arr[i][0] +
		  " because " + loop_arr[i][2] + " by " + loop_arr[i][1] +
		  " (add: " + temp + ").\n");
		actionlist -= ({ loop_arr[i] });
	    }
	  donesomething = 1;
      }
    save_object(ADMIN_FILE);
    save_object(BACKUP_SAVE_FILE);
    return donesomething;
}
/****************************************************************************
 * Loop through actionlist and perform all actions for 'who'
 * if any action was done, return 1 else return 0. This function is called upon
 * login from each knight's medal.
 */
public nomask int
check_action_pending(object who)
{
    /* loop through actionlist and perform all actions for 'who' */
    /* if any action was done, return 1 else return 0 */
    int i;
    mixed temp = 0;
    int donesomething = 0;
    string targetname = who->query_real_name();
    mixed *loop_arr = actionlist + ({ });
    for(i=0;i<sizeof(loop_arr);i++)
      {
	  if (loop_arr[i][0] == targetname)
	    {
		temp_knight_slvl_down_to = 0;
		if (sizeof(loop_arr[i]) > 4)
		  temp = loop_arr[i][4];
		perform_action_now(loop_arr[i][1], who, loop_arr[i][2],
				   loop_arr[i][3], temp);
		actionlist -= ({ loop_arr[i] });
		donesomething = 1;
	    }
      }
    save_object(ADMIN_FILE);
    save_object(BACKUP_SAVE_FILE);
    return donesomething;
}

/*******************************************************************************
 * The do_* functions are called either from the conclave command object or from
 * other places where the commands can be issued. These functions must call
 * perform_action. When perform_action returns 0, the action failed completely.
 * returning 1 means the action was executed immediately and 2 means it was put
 * in the actionlist. Putting something in the actionlist can of course never
 * ensure that the action will be executed, eg. if the target is a non-knight!
 */
public nomask int
do_banish(string str)
{
    string who, add = 0;
    string reason;
    int ret_val;
    int can_do = check_can_perform_command(TP);

    NF("What?\n");
    if (!can_do)
      return 0;

    NF("Ban <how> who because of what?\n<How> is optional and can be set to 'soft' (ie. no XP loss).");
    if (sscanf(str,"%s because %s", who, reason) != 2)
      return 0;
    sscanf(who,"%s %s", add, who);
    NF("Failed to banish " + who + ".\n");
    ret_val = perform_action(TP, who, reason, "banishment", add);
    if (ret_val == 1)
      write("You have banished " + C(who) + " from the Solamnian Knighthood.\n");
    else if (ret_val == 2)
      write("You have put " + C(who) + " in the banish list of the Solamnian Knighthood.\n");
    return ret_val;
}

public nomask int
do_pardon(string str)
{
    string who;
    string reason;
    int ret_val;
    int can_do = check_can_perform_command(TP);

    NF("What?\n");
    if (!can_do)
      return 0;
    
    NF("Pardon who because of what?\n");
    if (sscanf(str,"%s because %s", who, reason) != 2)
      return 2;

    NF("Failed to pardon " + who + ".\n");
    ret_val = perform_action(TP, who, reason, "pardon");
    if (ret_val == 1)
      write("You have pardoned " + C(who) + " from the banishment of the Solamnian Knighthood.\n");
    else
      ret_val = 0;
    return ret_val;
}

public nomask int
do_degrade(string str)
{
    string who, rest;
    string reason;
    int ret_val, times = 1;
    string down_to;
    int can_do = check_can_perform_command(TP);

    NF("What?\n");
    if (!can_do)
      return 0;

    NF("Degrade [how often] who because of what? (Note: [how often] may only be " +
       "of the interval [1.." + MAX_ACTIONS + "].\n");
    if (sscanf(str,"%d %s",times,rest) != 2)
      rest = str;
    if (times < 1 || times > MAX_ACTIONS)
      return 0;
    
    if (sscanf(rest,"%s because %s", who, reason) != 2)
      return 0;
    NF("Failed to degrade " + who + ".\n");
    ret_val = perform_action(TP, who, reason, "degradation", times);
    if (ret_val == 1)
      write("You have degraded " + C(who) + " down to " + temp_knight_slvl_down_to + ".\n");
    else if (ret_val == 2)
      write("You have put " + C(who) + " in the degradation list of the " +
	    "Solamnian Knighthood " + times + " times.\n");
    temp_knight_slvl_down_to = 0;
    return ret_val;
}

public nomask int
do_rewarding(string str)
{
    string who, rest;
    string reason;
    int ret_val, times = 1;
    int can_do = check_can_perform_command(TP);

    NF("What?\n");
    if (!can_do)
      return 0;

    NF("Upgrade [how often] who because of what? (Note: [how often] may only " +
       "be of the interval [1.." + MAX_ACTIONS + "].\n");
    if (sscanf(str,"%d %s",times,rest) != 2)
      rest = str;
    if (times < 1 || times > MAX_ACTIONS)
      return 0;
    
    if (sscanf(rest,"%s because %s", who, reason) != 2)
      return 0;
    NF("Failed to reward " + who + ".\n");
    ret_val = perform_action(TP, who, reason, "upgrade", times);
    if (ret_val == 1)
      write("You have rewarded " + C(who) + " with prestige " + times +
	    " times.\n");
    else if (ret_val == 2)
      write("You have put " + C(who) + " in the rewarding list of the " +
	    "Solamnian Knighthood " + times + " times.\n");
    return ret_val;
}

public nomask int
do_disgrace(string str)
{
    string who;
    string reason;
    int ret_val;
    int can_do = check_can_perform_command(TP);

    NF("What?\n");
    if (!can_do)
      return 0;

    NF("Disgrace who because of what?\n");
    if (sscanf(str,"%s because %s", who, reason) != 2)
      return 0;
    NF("Failed to disgrace " + C(who) + ".\n");
    ret_val = perform_action(TP, who, reason, "disgrace");
    if (ret_val == 1)
      write("You have punished " + C(who) + " with no training, no " +
	    "teamleading and no armoury access for 2 days (age).\n");
    else if (ret_val == 2)
      write("You have put " + C(who) + " in the disgrace list of the " +
	    "Solamnian Knighthood.\n");
    return ret_val;
}

public nomask int
do_forgive(string str)
{
    string who;
    string reason;
    int ret_val;
    int can_do = check_can_perform_command(TP);

    NF("What?\n");
    if (!can_do)
      return 0;

    who = L(str);
    NF("Failed to forgive " + C(who) + ".\n");
    ret_val = perform_action(TP, who, reason, "forgive");
    if (ret_val == 1)
      write("You have forgiven " + C(who) + " a prior disgrace.\n");
    else if (ret_val == 2)
      write("You have put " + C(who) + " in the forgive list of the " +
	    "Solamnian Knighthood.\n");
    return ret_val;
}

public nomask int
do_award(string str)
{
    string who;
    string withwhat, reason;
    int ret_val;
    int can_do = check_can_perform_command(TP);
    int lvl = TP->query_knight_level();

    NF("What?\n");
    if (!can_do)
      return 0;

    NF("Award who with what because what?\n");

    if (sscanf(str, "%s with %s because %s", who, withwhat, reason) != 3)
      return 0;
/*    if (sscanf(str,"%s with %s", who, withwhat) != 2)
      return 0;
*/
    if (TP == find_player(who))
      return NF("You can't award yourself.\n");

    NF("Award " + C(who) + " with what?\n");
    if (withwhat != "braid" && withwhat != "ribband" &&
	(withwhat != "rose" || lvl != 5) &&
	(withwhat != "sword" || lvl != 4) &&
	(withwhat != "crown" || lvl != 3))
      return 0;

    NF("Failed to award " + C(who) + ".\n");
    ret_val = perform_action(TP, who, reason, "award", withwhat);
    if (ret_val == 1)
      write("You have awarded " + C(who) + " with " + withwhat + ".\n");
    else if (ret_val == 2)
      write("You have put " + C(who) + " in the award list of the " +
	    "Solamnian Knighthood.\n");
    return ret_val;
}


/****************************************************************************
 * Function name: killed_logging
 * Description:   Log the killing of another player
 * Arguments:  killer - The killer
 *   killed - Who was killed
 */
public nomask void
killed_logging(object killer, object killed)
{
    seteuid(getuid(TO));
    write_file(KILL_LOG, capitalize(killer->query_real_name()) + 
	       " killed " + capitalize(killed->query_real_name()) + "(" +
	       killed->query_race() + ") on " +
	       extract(ctime(time()), 4, 15) + ".\n");
}

/****************************************************************************
 * Function name: leave
 * Description:   Someone wants to leave the guild
 * Arguments:     ob - The object who wants to leave
 *                force: 0: skill reduction left to skill decay if possible
 *                          & exp loss.
 *                       1: force immediate skill reduction
 *                       2: soft banishment (ie. no exp loss)
 *                       3: 1+2
 */
public nomask varargs void
leave(object ob, int force)
{
    int i, num;
    object sp;
    string squire, knight;
    mixed order;

    seteuid(getuid(TO));

    if (ob && ob->query_wiz_level())
      tell_object(ob, "I'm not sure this will work for a wizard but we " +
		  "might try.\n");

    write_file(LEAVEPATH, ctime(time()) + ", " + ob->query_name() +
	       " left. (");

    (SPONSOR_TREE)->left_guild(ob->query_real_name());

    if (MEMBER(ob))
      {
	  if (ob->query_knight_level() > 3)
	    {
	      ob->remove_guild_lay();
	      ob->set_guild_pref(SS_LAYMAN, 0);
	      ob->clear_guild_stat(SS_LAYMAN);
	    }
	  ob->remove_guild_occ();
	  ob->set_guild_pref(SS_OCCUP, 0);
	  ob->clear_guild_stat(SS_OCCUP);

	  /*if conclave member, remove that */
	  order = is_conclave(ob->query_real_name());
	  if (order)
	    {
		if (order == 3)
		  order = "crown";
		else if (order == 4) 
		  order = "sword";
		else 
		  order = "rose";
		remove_conclave(order);
	    }
      }
    if (LAYMAN(ob))
      {
	  ob->remove_guild_lay();
	  ob->set_guild_pref(SS_LAYMAN, 0);
	  ob->clear_guild_stat(SS_LAYMAN);
      }
    
    ob->clear_bit(GUILD_GROUP, MEMBER_BIT);
    ob->clear_bit(GUILD_GROUP, LAYMAN_BIT);
/*
    if (!(force & 2))
      ob->add_exp(-(ob->query_exp_combat()) / 6, 1);   
*/

      for (i = 0; i < sizeof(SKILLS); i++)
      {
#ifdef NO_SKILL_DECAY
	num = ob->query_skill(SKILLS[i]);
	
	if (SKILLS[i] <= 60000)
	{
	  write_file(LEAVEPATH, "," + num); /* record skills before reduction */
	  num -= (2 * num / 5 + random(num / 3));
	  num = num < 0 ? 0 : num;
	  ob->set_skill(SKILLS[i], num);
	}
#endif	
	if (SKILLS[i] > 60000)
	  ob->remove_skill(SKILLS[i]);
      }
    write_file(LEAVEPATH, ")\n");

    if (sp = P(SPELL_OB_NAME, ob))
      sp->remove_object();
    if (sp = P("pal_med", ob))
      sp->remove_object();
    ob->remove_cmdsoul(KNIGHT_SOUL);
    ob->update_hooks();

    TO->remove_knight(ob->query_real_name());

    if (ob->query_wiz_level())
      return;
    
    if (ob->query_default_start_location() == START_ROOM)
      ob->set_default_start_location(ob->query_def_start());
    
    ob->command("save");
}

/*
 * Function name: attacked_in_guild
 * Description:   Someone attacked a mobile in the guild, banishment!
 * Arguments:     attacked - Who was attacked
 *                attacker - The offender
 */
public nomask void
attacked_in_guild(object attacked, object attacker)
{
    tell_room(E(attacked), QCTNAME(attacked) + " shouts for help and three " +
	      "big Knights arrive.\n" +
	      "The biggest knight bellows: Hold it right there!\n", ({ attacker }));
    attacker->catch_msg(QCTNAME(attacked) + " shouts for help and three " +
			"big Knights arrive.\n" +
			"The biggest knight bellows: Hold it right there!\n");
    tell_room(ENTRANCE, "You see three big Knights arrive carrying " +
	      QTNAME(attacker) + " between them.\n");
    attacker->move(ENTRANCE);
    attacker->stop_fight(attacked);
    attacked->stop_fight(attacker);
    tell_room(E(attacked), "You see the Knights carry " + QTNAME(attacker) + 
	      " away.\n");
    tell_room(ENTRANCE, "The biggest knight shouts: Don't ever show " +
	      "your ugly face here again!\n");
    /*banish_now(attacker, "attacking " + attacked->short() +
	       " in the guild");*/
}

/****************************************************************************
 * Function name: goblin_leave
 * Description:   A goblin turned evil, kick him out of the guild
 * Arguments:     player - The guild member
 */
public nomask void
goblin_leave(object player)
{
    int i, num;
    
    seteuid(getuid(TO));
    
    if (player->query_wiz_level())
      return;

    tell_object(player, "You have proven that you don't suite as a Solamnian" +
		" Knight and are hence banished from our guild!.\n");
    leave(player,1);
    write_file(LEAVEPATH, "     (was a goblin)\n");
}

/*****************************************************************************
 * make the last logs of conclave actions available to all who need to be able
 * to read this
 */
public int
log_available_for_all_conclaves()
{
    if (check_can_perform_command(TP))
      {
	  if (!read_file(KNIGHT_ALL_LOG,1,1))
	    write("The Private Book of the Conclave is empty.\n");
	  else
	    tail(KNIGHT_ALL_LOG);
	  return 1;	
      }
    write("You are not allowed to read this book.\n");
    return 1;
}

/*****************************************************************************
 * Below follow the functions add, remove and query for the assistant to the
 * conclave. There can be a max of 2 assistants per knight order and these
 * assistants have the same commands available as the conclave! Is this too
 * much power?????????
 *
 *
 * Add an assistant to the conclave to be able to initiate new members
 * of the order.
 * return: 1 if successfully added, 0 if not.
 */
int
add_assistant(object initiator, object who)
{
    int i = is_assistant(who->query_real_name());
    /* check_initiator */
    if (initiator->query_knight_sublevel() != 11 &&
	member_array(initiator->query_name(), GUILDMASTERS) == -1)
      return 0;

    if (!assistants)
      assistants = ({({}),({}),({}),({}),({}),({}),({})});
    if (!i && (who->query_knight_level() == initiator->query_knight_level()) &&
	who->query_knight_sublevel() == 10)
      {
	  i = initiator->query_knight_level();
	  if (sizeof(assistants[i]) > 1)
	    return 0;
	  assistants[i] += ({ who->query_real_name() });
	  return 1;
      }
    return 0;
}

/* Remove an assistant to the conclave.
 * return: order of the assistant if successfully removed, 0 if not.
 */
public int
remove_assistant(object initiator, string who)
{
    int i = is_assistant(L(who));
    /* check_initiator */
    if (initiator->query_knight_sublevel() != 11 &&
	is_assistant(initiator->query_real_name()) &&
	member_array(initiator->query_name(), GUILDMASTERS) == -1)
      return 0;

    if (!assistants)
      assistants = ({({}),({}),({}),({}),({}),({}),({})});
    if (i)
      assistants[i] -= ({ L(who) });
    return i;
}
public void
reset_assis()
{
    assistants=0;
}

/* Return the list of assistants of a certain order
 */
public string *
query_assistants(int order)
{
    if (!assistants)
      assistants = ({({}),({}),({}),({}),({}),({}),({})});
    return assistants[order];
}

/* returns the number of the order 'str' is assistant to or 0 */
public nomask int
is_assistant(string str)
{
    int i;
    if (!assistants)
      assistants = ({({}),({}),({}),({}),({}),({}),({})});
    for(i=0;i<sizeof(assistants);i++)
      if (member_array(L(str),assistants[i]) >= 0)
	return i;
    return 0;
}

/******************************************************************************
 * Maintains the awards that knights have. the knight subloc checks this and
 * add the correct string in necessary.
 *
 *
 *  TETH suggested that also non-knights should be awarded. Awarding will
 *       only be possible when the person to award IS logged on!!
 *****************************************************************************/
/* The Award itself is a binary encoded number with the following
 * meaning:
 *  1: braid
 *  2: ribband
 *  4: rose
 *  8: sword
 * 16: crown
 * 
 */
private void
add_award(object who, string what)
{
    int age = REALAGE(who);
    if (!awards)
      awards = ({});
    awards += ({ ({ who->query_real_name(), what, age }) });
    save_object(ADMIN_FILE);
    save_object(BACKUP_SAVE_FILE);
}

public int
which_award(string withwhat)
{
    if (withwhat == "braid")
      return 1;
    else if (withwhat == "ribband")
      return 2;
    else if (withwhat == "rose")
      return 4;
    else if (withwhat == "sword")
      return 8;
    else if (withwhat == "crown")
      return 16;
}

public int
query_my_awards(object who)
{
    int i, age;
    string who_name;
    mixed *oldawards = ({ });
    int awds = 0;

    if (!objectp(who))
      return 0;

    age = REALAGE(who);
    who_name = who->query_real_name();
    if (!awards)
      return awds;

    for(i=0;i<sizeof(awards);i++)
      {
	  if (who_name != awards[i][0])
	    continue;

	  if (awards[i][2] + SECONDS_IN_2_DAYS < age)
	    oldawards += ({ awards[i] });
	  else
	    awds |= which_award(awards[i][1]);
      }
    awards -= oldawards;
    /* save_object(ADMIN_FILE);
     * save_object(BACKUP_SAVE_FILE);
     * this is not necessary. just takes a lot of cpu time..
     */
    return awds;
}

public string
query_award_nice(object who)
{
    string *arr;
    int i,j, my_awards;
    string str = "";

    my_awards = query_my_awards(who);

    arr = ({ });
    for(i=0;i<sizeof(AWARD_PRETTY_STRING);i++)
      if (my_awards & (1 << i))
	arr += ({ AWARD_PRETTY_STRING[i] });

    j = sizeof(arr);
    if (j > 2)
      for(i=2;i<j;i++)
	str += arr[i-2] + ", ";
    if (j > 1)
      str += arr[j-2] + " and ";
    if (j > 0)
      str += arr[j-1];

    return str;
}

