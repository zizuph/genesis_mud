/*
 * Recruithall of the Rangers of the Westlands
 * Here recruits can join the guild.
 *
 * By Lord Elessar Telcontar
 *
 * Revision history:
 * - many undocumented revisions ;-)
 * - typecasted all functions
 *   (except those functions where typecasting is impossible due to a gd bug)
 * Olorin, 05-jan-1994
 * - Added sponsor-system.
 * Elessar, Feb. 1995.
 * - Fixed the throw_out() mechanism, added shadow of set_alignment()
 * Olorin, 05-aug-97
 *
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/binbit.c";
inherit "/d/Gondor/common/guild/lib/members.c";
inherit "/d/Gondor/common/guild/gondor/no_theft";

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"

#include "/d/Gondor/common/guild/lib/ranger_defs.h"
#include "/d/Gondor/common/guild/lib/punish_defs.h"

#define GUILD_NAME	"Gondorian Rangers Guild"
#define GUILD_STYLE	"ranger"
#define GUILD_TYPE	"occupational"
#define MEMBERLIST	RANGER_DIR + "rangers"
#define MEMBER_LOG	LOG_DIR + "members"
#define MEMBER_FAIL_LOG "/d/Gondor/log/ranger_fail"
#define SHADOW		RANGER_DIR + "ranger_shadow"
#define COMPANY         ({"Ranger pupils","Gondor","Ithilien"})
#define TOKEN           ({RANGER_DIR+"rring",RANGER_DIR+"rring",\
                          RANGER_DIR+"ramulet"})   
#define TOKEN_NAME      ({"ring", "ring", "amulet"})
#define RING            RANGER_DIR + "rring"
#define SCROLL		RANGER_DIR + "obj/rscroll"
#define RANGER_S_SPONSOR   "_ranger_s_sponsor"
#define REDUCEFACTOR    2
#define JOIN_MIN_ALIGN	100
#define	MASTER_RANGER	(RANGER_DIR + "lib/master_ranger")

// Prototypes:
public int     join_rangers(string str);
public int     leave_rangers(string str);
public int     vouch_for_pupil(string str);
public int     give_token(object pl, int how);
public int     query_company(string name);
static int     remove_ring(object player, int pigeon);
static int     remove_shadow(object tp);
public int     test_access();
public mixed   check_join_guild(mixed player = this_player());
public string  exa_poster();
public void    reset_room();
public void    check_members();

// Global variables:
static object  Member_Book, 
Ranger;
mixed         *rangers;
mixed         *company_rangers = ({ ({}), ({}), ({}) });

public void 
create_gondor()
{
    set_short("the Recruitment Hall of the Rangers of Gondor");
    set_long(BS("You are in a white walled hall with burning torches lining "+
	"the walls. On the north wall, above a wooden altar, hangs "+
	"a large black banner, on the west wall, there is a poster. " +
	"Upon the altar lies a large, leatherbound book. Through a narrow " +
	"doorway in the west wall a small office is visible. " +
	"The main hall of the guildhouse is to the south.\n"));

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ATTACK,1);
    add_prop(ROOM_I_NO_CLEANUP,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK,1);
    add_prop(ROOM_M_NO_STEAL, no_theft);

    add_item("torches",BS("The torches are all burning brightly, and all are "+
	"fastened to the wall.\n"));
    add_item("altar",BS("It is a wooden altar, its sides covered with deer "+
	"hides. Carved into the wood in Elven letters you "+
	"read the word 'Orome'. Upon the altar, seemingly "+
	"held there by crawling plants, is a large "+
	"leatherbound book.\n"));
    add_item("banner",BS("Upon the black banner is embroidered with silver "+
	"threads a white tree surrounded by seven stars.\n"));
    add_item(({"walls","wall"}),BS("The walls are made of white polished stone "+
	"slabs, neatly fitted among each other. This is "+
	"excellent craftsmanship.\n"));
    add_item(({"poster","members","pupils"}), exa_poster);
    add_cmd_item(({"poster","members","pupils"}), "read", exa_poster);
    add_exit(RANGER_GON_DIR + "boardhall", "south", 0, 0);
    add_exit(RANGER_GON_DIR + "recruit_library", "west", test_access, 0);
    reset_room();

    restore_object(MEMBERLIST);
    set_alarm(1.0, 0.0, check_members);
}

public void 
reset_room()
{
    if (!objectp(Member_Book))
	(Member_Book = clone_object(RANGER_DIR + "obj/rangerbook"))->move(TO);

    Ranger = clone_npc(Ranger, RANGER_DIR + "npc/amaron");
}

public int
test_access()
{
    object pl = TP;

    if ((pl->query_ranger_mentor())
      || (pl->query_skill(SS_MASTER_TASK) == RECRUITER)
      || (pl->query_skill(SS_MASTER_TASK) == INSTRUCTOR)
      || (COUNCIL->is_officer(pl->query_real_name()))
      || (SECURITY->query_wiz_dom(pl->query_real_name()) == "Gondor"))
	return 0;
    if (objectp(Ranger) && present(Ranger, TO))
    {
	Ranger->command("say Halt! That is a private office!");
	write("The Master Ranger stops you from going there.\n");
    }
    else
    {
	write("You decide not to sneak into private rooms.\n");
    }
    return 1;
}

public int 
query_banned(string name)
{
    int     bb;
    object  who;

    name = lower_case(name);
    if (!objectp(who = find_player(name)))
	return 0;
    return (query_bin_bits(1, 18, 2, who) == 3);
}

public int 
check_keep_player(object pl)
{
    if (pl->query_wiz_level()) 
	return 1;
    if (query_banned(pl->query_real_name())) 
	return 0;
    if (pl->query_race_name() == "kender")
	return 0;
    return (pl->query_race() != "goblin");
}

public void 
init()
{
    ::init();

    add_action(join_rangers,    "sign");
    add_action(leave_rangers,   "erase");
    add_action(vouch_for_pupil, "vouch");
}

public void
test_restore_ranger(object pl)
{
    int    co, 
    rk;

    if (pl->query_wiz_level() || (QRACE(pl) == "goblin") ||
      (pl->query_alignment() < 0))
	return;

    rk = query_bin_bits(1, 18, 2, pl);
    if ((pl->query_guild_name_occ() != GUILD_NAME) &&
      ((rk == 0) || (rk == 3)))
	return;

    if ((pl->query_guild_name_occ() == GUILD_NAME) &&
      ((rk == 1) || (rk == 2)))
    {
	co = query_company(pl->query_real_name());
	if (co == -1)
	    return;
	if (co != query_bin_bits(1, 16, 2, pl))
	    set_bin_bits(1, 16, 2, pl, co);
	if (!present("ranger_guild_object", pl))
	    give_token(pl, 1);
	return;
    }
    else if (rk < 1)
    {
	co = query_bin_bits(1, 16, 2, pl);
	if (co == 0)
	    co = query_company(pl->query_real_name());
	if (co == -1)
	    return;
	if (co == 3)
	{
	    set_bin_bits(1, 16, 2, pl, 2);
	    co = 3;
	}
	else if (co != query_bin_bits(1, 16, 2, pl))
	    set_bin_bits(1, 16, 2, pl, co);
	if (COUNCIL->query_captain(pl->query_real_name()))
	    set_bin_bits(1, 18, 2, pl, 2);
	else
	    set_bin_bits(1, 18, 2, pl, 1);
	if (!present("ranger_guild_object", pl))
	    give_token(pl, 1);
    }
    return;
}

public void
report(string str)
{
    object *gm = ({ find_player("rohim") });

    gm -= ({ 0 });
    if (!sizeof(gm))
	return;
    gm->catch_tell(str);
}

public int 
query_ranger(string name)
{
    object who = find_player(LOW(name));

    if (!objectp(who))
    { 
	report("RANGER DEBUG: In query-func: Could not find_player "+name+"!\n"); 
	return 0;
    }
    return IS_RANGER(who);
}

public int 
give_ring(object tp, int how)
{
    object ring;
    if (!how)
    {
	tell_object(tp,"The master Ranger hands you a ring.\n");
	if (objectp(ring = present("ranger_ring", tp)))
	    ring->remove_object();
	ring = clone_object(RING);
	ring->move(tp, 1);
	return 1;
    }
    tp->catch_tell("A white pigeon comes flying, and lands on your shoulder.\n");
    if (objectp(ring = present("ranger_ring",tp)))
    {
	ring->remove_object();
	tp->catch_tell("The pigeon gives you a new ring and takes your old one in its beak.\n");
    }
    else 
	tp->catch_tell("The pigeon gives you a new ring.\n");
    ring = clone_object(RING);
    ring->move(tp, 1);
    tell_object(tp,"Then it flies off again, disappearing as a white speck in the horizon.\n");
    return 1;
}

/*
 * 6-jun-1993, Olorin
 * should replace give_ring in the future, assuming that
 * the how = 1 option of give_ring is obsolete since the
 * introduction of the newtoken command
 */
int
give_token(object pl, int how)
{
    object  token,
    mranger;
    int     company;

    if (!objectp(pl))
	return 0;
    company = query_bin_bits(1,16,2,pl);
    if (how) 
    {
	tell_object(pl,"A white pigeon comes flying, and lands on your shoulder.\n");
	tell_object(pl,"The pigeon drops a new " + 
	  LANG_ADDART(TOKEN_NAME[company]) + " in your hand.\n");
	if (objectp(token = present("ranger_guild_object",pl))) 
	{
	    token->remove_object();
	    tell_object(pl,"Then the pigeon flies off with the old Ranger-token.\n");
	}
	else 
	    tell_object(pl,"The pigeon flaps its wings, and flies away into the sky.\n");
    }
    else 
    {
	if (living(mranger = previous_object()) &&
	  function_exists("create_ranger", mranger) == MASTER_RANGER)
	{
	    pl->catch_msg(QCTNAME(mranger)+" gives you "+
	      LANG_ADDART(TOKEN_NAME[company]) + ".\n");
	    say(QCTNAME(mranger)+" gives "+
	      LANG_ADDART(TOKEN_NAME[company])+
	      " to "+QTNAME(pl)+".\n");
	}
	else
	{
	    tell_object(pl,"The master Ranger hands you "+
	      LANG_ADDART(TOKEN_NAME[company]) + ".\n");
	    say("The master Ranger gives "+
	      LANG_ADDART(TOKEN_NAME[company])+
	      " to "+QTNAME(pl)+".\n");
	}
	if (objectp(token = present("ranger_guild_object", pl)))
	    token->remove_object();
    }
    token = clone_object(TOKEN[company]);
    if (token->move(pl))
	token->move(pl, 1);
    return 1;
}


int 
race_accepted(string race)
{
    return ((race == "human") || (race == "elf") || (race == "dwarf")
      || (race =="gnome") || (race == "hobbit"));
}

public int 
vouch_for_pupil(string str)
{
    int     is_new,
    in_company;
    mixed   result;
    object  pupil;
    string  name,
    tp_name = TP->query_real_name();

//    NFN("Amaron says: You are not a Mentor of the Rangers.\n");
//    if (!IS_RANGER(TP) || !SPONSOR->query_can_sponsor(tp_name))

    NFN("Amaron says: You are not a full Ranger.\n");
    if (!IS_RANGER(TP) || TP->query_company() == "the Ranger pupils")
	return 0;
    NFN("Vouch for whom?");
    if (!strlen(str)) 
	return 0;
    if (sscanf(LOW(str), "for %s", name) != 1) 
	return 0;

    NFN("That person is not present.");
    if (!objectp(pupil = present(name, TO)))
	return 0;
    NFN("You can only vouch for someone who is with you.");
    if (!interactive(pupil)) 
	return 0;

    if (is_new = (pupil->query_guild_name_occ() != GUILD_NAME))
    {
	if (stringp(result = check_join_guild(pupil)))
	{
	    if (pupil->query_guild_style("thief"))
	    {
		log_file("members",  ctime(time())+
		  TP->query_name()+" tried to vouch for thief "+
		  pupil->query_name()+".\n");
		tell_room(TO, 
		  "Amaron says: What! You vouch for a thief!?!\n");
		no_theft(pupil);
	    }
	    else
	    {
		pupil->catch_tell(result);
	    }
	    NFN("Why vouch for someone who cannot join the Rangers?");
	    return 0;
	}
    }
    else if (in_company = query_bin_bits(RANGER_GROUP, RANGER_GUILD_BIT, 2, pupil))
    {
	NFN(CAP(name) + " is a member of the Rangers of " +
	  COMPANIES[in_company] + " and does not need a sponsor!");
	return 0;
    }
/*
    else if (SPONSOR->query_approved(name) < 3)
    {
	NFN(CAP(name) + " is not yet approved for membership.!");
	return 0;
    }
*/
    else if (stringp(result = SPONSOR->query_sponsor(name)))
    {
	NFN(CAP(name) + " is currently sponsored by " + result +
	  "and does not need a second sponsor!");
	return 0;
    }

    if (stringp(result = SPONSOR->add_pupil(tp_name, name, 1)))
    {
	NFN(result);
	return 0;
    }
    write("You kneel before Amaron, taking a solemn oath to be the faithful\n"+
      "instructor and mentor of " + CAP(name) + ", until an Officer\n"+
      "accepts " + OBJECTIVE(pupil) + " into a Company.\n");
    say(QCTNAME(TP) + " kneels before Amaron, and takes a solemn oath:\n"+
      "     I, " + CAP(tp_name) + ", hereby swear to be the instructor\n"+
      "     and guide of " + CAP(name) + ", until such a time when\n"+
      "     an Officer will accept "+OBJECTIVE(pupil)+" into a Company.\n"+
      "     I swear this Oath before the Valar, may I be punished utterly\n"+
      "     should I neglect my task!\n", TP);
    Ranger->command("say So be it! " + CAP(name) +
      " has been vouched for!");
    say(QCTNAME(TP)+" rises to "+POSSESSIVE(TP)+" feet again.\n",TP);
    if (is_new)
	pupil->add_prop(RANGER_S_SPONSOR, tp_name);
    return 1;
}

int 
add_shadow(object tp)
{
    object  shadow;
    int     result;

    if (!objectp(tp))
	return 0;
    shadow = clone_object(SHADOW);
    if ((result = shadow->shadow_me(tp, GUILD_TYPE, GUILD_STYLE,
	  GUILD_NAME)) != 1) 
    {
	write_file(RANGER_LOG, "RANGERS: "+tp->query_name()+
	  " could not be shadowed! Result: " + result + ". " +
	  ctime(time())+".\n");  
	SECURITY->do_debug("destroy", SHADOW);
	return 0;
    }
    return 1;
}

int 
give_scroll(object tp,int how)
{
    object scroll;
    int company;
    if (!how)
    {
	write("The master Ranger gives you a scroll.\n");
	scroll = clone_object(SCROLL);
	scroll->move(tp);
	return 1;
    }
    tell_object(tp,"A white pigeon lands on your shoulder, "+
      "dropping a scroll in your hand.\n");
    tell_object(tp,"Then it flies away into the horizon.\n");
    scroll = clone_object(SCROLL);
    scroll->move(tp);
    return 1;
}

/*
 * Add the name and the company of a ranger to the list.
 */
static void
add_to_list(string name, int company)
{
    if (company < 0 || company > 2)
	return;
    if (!sizeof(rangers))
	rangers = ({ });
    if (member_array(name, rangers) == -1)
	rangers += ({ LOW(name), company });
    if (member_array(name, company_rangers[company]) == -1)
	company_rangers[company] += ({ LOW(name) });
    save_object(MEMBERLIST);
}

/*
 * Make the new ranger join the guild
 */
varargs int 
add_ranger(string name, int how)
{
    int n;

    seteuid(getuid(TO));
    name = lower_case(name);
    if (!find_player(name)) 
	return -1;
    if (query_ranger(name)) 
	return -2;  
    set_bin_bits(1,18,2,find_player(name),1);
    if((n = query_bin_bits(1,16,2,find_player(name))) != 0)
    {
	write_file(RANGER_LOG," >>>> " + CAP(name) +
	  " joined the rangers. Company bits were set to " + n + ".\n");
	set_bin_bits(1,16,2,find_player(name),0);
    }
    if (add_shadow(find_player(name)) == 1 || (how >= 1))
    {     
	give_ring(find_player(name),how);
	give_scroll(find_player(name),how);
	find_player(name)->remove_skill(SS_MASTER_TASK);
	add_to_list(name, 0);
    }
    else
    {
	set_bin_bits(1,18,2,find_player(name),0);
	set_bin_bits(1,16,2,find_player(name),0);
	return 0;
    }
    return 1;
}

/*
 * Function name: check_join_guild
 * Description:   Call this function to determine if a player is
 *                permitted to join the Rangers.
 * Arguments:     the name of the player or the player object
 * Returns:       0 for success, fail message else.
 */
public mixed
check_join_guild(mixed player = this_player())
{
    string  race;

    if (stringp(player))
	player = find_player(LOW(player));
    if (!objectp(player))
	return "No such player found!\n";

    // Bug(?) in query_guild_not_allow_join_guild, so we do it the hard way:
    if (player->query_guild_not_allow_join_occ(player, GUILD_TYPE, GUILD_STYLE, GUILD_NAME) ||
      player->query_guild_not_allow_join_lay(player, GUILD_TYPE, GUILD_STYLE, GUILD_NAME) ||
      player->query_guild_not_allow_join_race(player, GUILD_TYPE, GUILD_STYLE, GUILD_NAME))
	return "Your other guilds do not permit you to join the " + GUILD_NAME + "!\n";
    if (player->query_guild_name_occ() == GUILD_NAME)
	return "But you are already a Ranger!\n";

    if (!race_accepted(player->query_race()))
	return CAP(LANG_PWORD(race)) + " may not become Rangers "+
	"of Gondor! Please leave before somebody catches you.\n";

    if (player->query_guild_name_race() == "Drow race guild")
	return "The evil Drow elves are not a trusted race.\n" +
	"You can not become a Ranger of Middle-earth!\n";

    if (player->query_race_name() == "kender")
	return "Kenders are not trustworthy enough to join!\n";
    /*
	if (player->query_race_name() == "gnome")
	    return "Gnomes are not fit for becoming Rangers of the Westlands.\n";

	if (player->query_race_name() == "hobbit")
	    return "Hobbits are not for becoming Rangers of the Westlands, I'm sorry.\n";
    */

    if (player->query_guild_style("magic"))
	return "But you are a magician! Mages "+
	"cannot join the Rangers of the Westlands!\n";

    if (player->query_guild_style("thief"))
	return "We do not allow thieves among "+
	"our numbers! You are not allowed to join!\n";

    if (player->query_guild_member(GUILD_TYPE))
	return "But you are already a member of an " +
	"occupational guild!\n";

    if (query_banned(player->query_name()))
	return "You have been banned from the "+
	"Rangers! You are not allowed to join!\n";

    if (player->query_alignment() < JOIN_MIN_ALIGN) 
	return CAP(player->query_align_text()) +
	" persons do not belong with the Rangers!\n" +
	"You must behave better, and stop being tempted " +
	"by evil ways!\n" +
	"If you don't, you need not return here!\n";

    return 0;
}

public int 
join_rangers(string str)
{
    int     result;
    mixed   fail_msg;
    object  shadow;
    string  sponsor;

    if (stringp(fail_msg = check_join_guild(TP)))
    {
	NF("The master Ranger says: " + fail_msg);
	return 0;
    }

    if (!strlen(sponsor = TP->query_prop(RANGER_S_SPONSOR)))
    {
	NFN("The master Ranger says: You will need a Ranger to vouch "+
	  "for you, and to be your instructor.\n" +
	  "Please come back when you have found one.");
	return 0;
    }

    if (!present(LOW(sponsor), TO))
    {
	NFN("The master Ranger says: But your guide must be present when "+
	  "you join!");
	return 0;
    }

    if (stringp(fail_msg = SPONSOR->add_pupil(sponsor,
	  TP->query_name(), 0)))
    {
	NF("The master Ranger says: " + fail_msg);
	return 0;
    }

    NFN("The master Ranger says: I'm sorry, but for some unknown "+
      "reason I am unable to help you join the Gondorian Rangers.");
    if ((result = add_ranger(TP->query_name())) != 1) 
    {
	write_file(RANGER_LOG,"RANGERS: "+TP->query_name()+
	  " failed to join. Result "+result+". "+ctime(time())+".\n");
	SPONSOR->remove_pupil(TP->query_name());
	return 0;
    }
    /*
     * clear previous guild stat, nobody can start as an experienced ranger 
     */
    TP->clear_guild_stat(SS_OCCUP);
    TP->setup_skill_decay();
    write("You kneel before the master Ranger, and he opens the book for\n"+
      "you to sign in and hands you a quill.\n");
    write("With a deft hand you sign your name in the large leatherbound "+
      "book.\n");
    write_file(STATUS_LOG, TP->query_name()
      +" joined the Rangers, vouched for by "+
      CAP(sponsor) + " " + ctime(time()) + ".\n");
    write(BS("The master Ranger says: Welcome! You are now a "+
	"pupil of the Rangers!\n"));
    write("He hands you a ring as a token of your membership.\n"+
      "You also receive a scroll with some information.\n");
    say(QCTNAME(TP) + " signs " + TP->query_possessive() +
      " name in the leatherbound book.\n"+
      "The master Ranger shakes "+TP->query_possessive()+
      " hand and says: Welcome! You are now a pupil of the Rangers.\n",TP);
    say(QCTNAME(TP)+" receives a ring and a scroll from the master Ranger.\n",
      TP);
    return 1;
}

public void
remove_from_list(string name)
{
    int i = -1,
    n;

    if ((n = member_array(name, rangers)) == -1)
    {
	i = -1;
	while (++i < 3)
	{
	    company_rangers[i] -= ({ name });
	}
	save_object(MEMBERLIST);
	return;
    }
    company_rangers[rangers[n+1]] -= ({ name });
    rangers = exclude_array(rangers, n, n+1);
    save_object(MEMBERLIST);
    return;
}

/*
 * Code to remove players from the guild:
 *
 * remove_ranger(string name, int how = 0, string reason = "")
 * Calls: remove_shadow, remove_ring
 *
 */

/*
 * All removal of a player from the guild has to go through this routine!
 *
 * 
 */
varargs int 
remove_ranger(string name, int how = 0, string reason = "")
{
    object pl,
    prev,
    key,
    spellbook;
    string prev_name;
    if ( !objectp(prev = previous_object()) )
    {
	write_file(STATUS_LOG,
	  "Failed to remove "+CAP(name)+": NULL previous object\n");
	return 0;
    }
    if ( prev != TO &&
      (prev_name = file_name(prev)) != COUNCIL &&
      prev_name != SOUL_FILE &&
      MASTER_OB(prev) != SHADOW )
    {
	write_file(STATUS_LOG,
	  "Failed to remove "+CAP(name)+": previous object '"+
	  prev_name+"' not recruithall, council, soul or shadow file\n");
	return 0;
    }
    name = lower_case(name);
    if (!objectp(pl = find_player(name)))
    {
	write_file(STATUS_LOG,
	  "Failed to remove "+CAP(name)+": cannot find player\n");
	return 0;
    }
    if (pl->query_master_ranger())
	COUNCIL->remove_master(CAP(pl->query_real_name()));
    // Remove the guild shadow:
    remove_shadow(pl);

    // Remove the guild soul:
    pl->remove_cmdsoul(SOUL_FILE);
    pl->update_hooks();

    // Remove guild skill, set up skill decay:
    pl->setup_skill_decay();

    pl->remove_skill(SS_HEARING);
    pl->remove_skill(SS_BRAWLING);
    pl->remove_skill(SS_REWARDED);
    pl->remove_skill(SS_PUNISHED);
    pl->remove_skill(SS_PUNISHMENT);
    pl->remove_skill(SS_RANGER_SPELL_LIST);
    pl->remove_skill(SS_RANGER_DISFAVOUR);

    if (pl->query_skill(SS_MASTER_TASK) > 0)
    {
	pl->remove_skill(SS_MASTER_TASK);
	COUNCIL->remove_master(pl->query_name());
    }

    // Reset guild stat:
    pl->clear_guild_stat(SS_OCCUP);

    // Reset start location:
    pl->set_default_start_location(pl->query_def_start());

    // Fix bits:
    set_bin_bits(1, 18, 2, pl, 0);
    set_bin_bits(1, 16, 2, pl, 0);

    // Fix officer status:
    if (COUNCIL->is_officer(name))
    {
	COUNCIL->remove_ranger(name);
	if (objectp(key = present("_Council_Key", pl)))
	    key->remove_object();
    }

    // Fix sponsor status:
    if (SPONSOR->query_sponsor(pl->query_name()))
	SPONSOR->remove_pupil(pl->query_name());
    if (SPONSOR->query_pupil(pl->query_name()))
	SPONSOR->remove_sponsor(pl->query_name());

    if (SPONSOR->query_can_sponsor(pl->query_name()))
	SPONSOR->remove_mentor(pl->query_name());
    // Update member list:
    remove_from_list(name);

    // Remove guild objects:
    remove_ring(pl, 1);

    if (objectp(spellbook = present("ranger_spell_book", pl)))
	spellbook->remove_object();

    // Log action:
    write_file(STATUS_LOG, CAP(name) + " is removed from the Ranger guild. " +
      "Reason = " + reason + " (" + ctime(time()) + ").\n");

    return 1;
}

/*
 * Function name: remove_shadow
 * Description:   remove the guild shadow
 * Argument:      tp - player object
 * Returns:       0/1
 */
static int 
remove_shadow(object tp)
{
    int result;

    if (!objectp(tp))
	return 0;

    if ((result = tp->remove_guild_occ()) != 1)
    {
	report("Failed to remove shadow from goblin " + 
	  tp->query_name()+"! Result: "+result+"\n");
	write_file(RANGER_LOG, "RANGERS: "+tp->query_name()+
	  " failed to leave! Result: "+result+". "+ctime(time())+".\n");
	return 0;
    }
    return 1;
}

/*
 * Function name: remove_ring
 * Description:   Remove the guild token.
 * Arguments:     player - player object
 *                pigeon - 0 if a master Ranger is present
 *                         1 if a pigeon takes the ring
 */
static int 
remove_ring(object player, int pigeon)
{
    object token;
    string tok_str;

    if (!objectp(player))
	return 0;
    if (!objectp(token = present("ranger_guild_object",player)))
	return 0;

    tok_str = token->short();

    if (!pigeon)
    {
	tell_object(player, "The master Ranger takes your "+tok_str+" and puts it away.\n" +
	  "The master Ranger says: You won't need this anymore.\n");
    }
    else
	tell_object(player,"A white pigeon comes flying, and takes your "
	  + tok_str+" in its beak.\n"+
	  "The white pigeon flies away with it.\n");
    token->remove_object();
    return 1;
}

/*
 * Function name: leave_rangers
 * Description:   a player wants to leave the guild
 * Argument:      str - command line argument
 * Returns:       1/0
 *
 */
public int
leave_rangers(string str)
{
    int     result;
    object  tp = TP;

    if (!strlen(str))
	str = "name";

    if ((str != "name") && (str != "my name"))
    {
	NFN("Erase what? Your name, perhaps?");
	return 0;
    }

    NFN("The master Ranger says: But you are not a Gondorian Ranger!");
    if ((tp->query_guild_name_occ() != GUILD_NAME) 
      && (!query_ranger(tp->query_name())))
	return 0;

    NFN("The master Ranger says: I'm sorry, but for some unknown "
      + "reason I am unable to help you leave the guild!");
    if ((result = remove_ranger(tp->query_name(), 0, "left")) != 1)
    {
	write_file(RANGER_LOG,"RANGERS: "+tp->query_name()+
	  " failed to leave. Result "+result+". "+ctime(time())+".\n");
	return 0;
    }

    write("You erase your name from the large, leatherbound book.\n");
    say(QCTNAME(tp)+" erases "+tp->query_possessive()+" name "+
      "from the large, leatherbound book.\n",tp);
    if (objectp(present(Ranger, TO)))
    {
	Ranger->command("say I'm sorry you didn't want to stay with "
	  + "us, "+tp->query_name()+".");
	Ranger->command("say We have enjoyed your company.");
    }
    write_file(STATUS_LOG, tp->query_name()+
      " left the Rangers. "+ctime(time())+".\n");

    return 1;
}

/*
 * Function name: ban_from_guild
 * Description:   remove someone forcibily from the guild and ban him or her
 * Arguments:     victim - player object
 *                reason - explanation for removal
 * Returns:       1/0
 */
static varargs int 
ban_from_guild(object victim, string reason = "banned")
{
    string  name = victim->query_name();

    report("Ban_from_guild called for "+name+"!\n");

    name = lower_case(name);

    if (!interactive(victim))
    { 
	report("In ban-func: Player not found!\n"); 
	return 0;
    }

    if (!query_ranger(name))
    {
	report("In ban-func: Not ranger!\n");
	return 0;
    }

    if (query_banned(name)) 
    {
	report("In ban-func: Already banned!\n");
	write_file(STATUS_LOG,
	  "ERROR: ban_from_guild: " + name +
	  " is still a ranger, but already banned on " +
	  ctime(time()) + ".\n");
	return 0;
    }

    remove_ranger(name, 1, reason);
    set_bin_bits( 1, 18, 2, victim, 3);
    return 1;
}  

int 
unban_from_guild(string name)
{
    int sb, n;
    name = lower_case(name);
    if (!find_player(name))
	return 0;
    if (!query_banned(name))
	return 0;
    set_bin_bits(1,18,2,find_player(name),0);
    return 1;
}

public varargs int 
throw_out(object player, string reason = "thrown out")
{
    if (!objectp(player))
    {
	report("No player-object sent to the Guild for throwing out!\n");
	return 0;
    }

    if (!query_ranger(player->query_real_name()))
    {
	report("Player to throw out is not a Ranger!\n");
	write_file(STATUS_LOG, "ERROR: " + player->query_name() + " NOT thrown out for " + reason + " on " + ctime(time()) + ".\n");
	return 0;
    }

    report("Throw out called successfully for "+player->query_name()+".\n");

    if (reason != "North closing")
    {
	ban_from_guild(player, reason);
	player->catch_tell("You are banned from the guild until " +
	  "the Council can judge your case!\n");
    }
    else
    {
	remove_ranger(LOW(player->query_real_name()), 1, reason);
    }
    return 1;
}

static void
company_log(string name, int bit)
{
    int     p;

    name = LOW(name);
    p = member_array(name, rangers);
    rangers[p + 1] = bit;

    if (member_array(name, company_rangers[bit]) == -1)
	company_rangers[bit] += ({ name });

    if (member_array(name, company_rangers[0]) > -1)
	company_rangers[0] -= ({ name });

    save_object(MEMBERLIST);
}

public string *
query_company_members(int company)
{
    if ((company > -1) && (company < 3))
	return ( ({ }) + company_rangers[company]);
    return 0;
}

public string 
exa_poster()
{
    write("On the poster you read:\n");
    return print_member_list();
}

public int 
query_company_number(string name)
{
    object ranger;
    string company;

    name = lower_case(name);
    if (!objectp((ranger = find_player(name))))
	return -1;
    company = ranger->query_company();
    if (company == "the Ranger pupils")
	company = "Ranger pupils";

    return (member_array(company, COMPANY));
}

public int
query_company(string name)
{
    int     ic;

    name = lower_case(name);
    if( (ic = member_array(name, rangers)) < 0 )
	return -1;

    if (member_array(name, company_rangers[rangers[ic+1]]) > -1 )
	return rangers[ic+1];

    return -2;
}

public void 
check_present_rangers()
{
    object *present_rangers = users();
    string  name, 
    company;
    int     i = -1, 
    n_co,
    n;

    present_rangers = filter(users(), 
      &operator(==)(GUILD_NAME) @ &->query_guild_name_occ());

    while (++i < sizeof(present_rangers))
    {
	name = present_rangers[i]->query_real_name();
	if (!present_rangers[i]->query_wiz_level() && extract(name, -2) != "jr")
	{
	    if ((n = member_array(name, rangers)) == -1)
	    {
		add_to_list(name, n_co = query_company_number(name));
		log_file("members", "check_present_rangers on " +
		  ctime(time()) + ": Added " + name +
		  " to list as member of company " + n_co + ".\n");

	    }
	    else
	    {
		if( (n_co = query_company_number(name)) != rangers[n+1])
		    if (n_co > -1)
		    {
			log_file("members", "check_present_rangers on " +
			  ctime(time()) + ": Changed company for " + 
			  name + " from " + rangers[n+1] + " to " +
			  n_co + ".\n");
			company_log(name, n_co);
		    }
	    }
	}
    }
    save_object(MEMBERLIST);
}

public void 
check_members()
{
    int     i;
    mixed  *old_rangers;
    string *new_pupil = ({}),
    *new_gondor = ({}),
    *new_ithilien = ({}),
    *old_company_pupil,
    *old_company_gondor,
    *old_company_ithilien,
    *add_pupil,
    *add_gondor,
    *add_ithilien,
    *sub_pupil,
    *sub_gondor,
    *sub_ithilien,
    *to_be_removed = ({}),
    log_msg = "";
    mixed  *old_company_rangers;

    old_rangers          = rangers;
    old_company_rangers  = company_rangers;
    old_company_pupil    = company_rangers[0];
    old_company_gondor   = company_rangers[1];
    old_company_ithilien = company_rangers[2];

    for (i = 0; i < sizeof(old_rangers); i+=2)
    {
	if (member_array(old_rangers[i], old_company_rangers[old_rangers[i+1]]) == -1)
	{
	    log_msg += "CHECK_MEMBERS BUG! i = " + i + ", company : " +
	    old_rangers[i+1] + ", ranger: " + old_rangers[i] +
	    " - not in company list!\n";
	    if (!stringp(old_rangers[i]))
	    {
		log_msg += "CHECK MEMBERS BUG! " + old_rangers[i] + 
		" no string! Remove entry!\n";
		remove_from_list(old_rangers[i]);
	    }
	    else if (!SECURITY->exit_player(old_rangers[i]))
	    {
		log_msg += "CHECK MEMBERS BUG! " +old_rangers[i] +
		" does not exist as player: remove entry!\n";
		remove_from_list(old_rangers[i]);
	    }
	    else
		log_msg += "CHECK MEMBERS BUG! " + old_rangers[i] + " exists as player!\n";
	}

	switch (old_rangers[i+1])
	{
	case 0:
	    new_pupil    += ({ old_rangers[i] });
	    break;
	case 1:
	    new_gondor   += ({ old_rangers[i] });
	    break;
	case 2:
	    new_ithilien += ({ old_rangers[i] });
	    break;
	default:
	    log_msg += "CHECK_MEMBERS BUG! i = " + i + ", company \n: " +
	    old_rangers[i+1] + ", ranger: " + old_rangers[i] + "\n" +
	    " - Illegal company number! Will remove name!\n";
	    remove_from_list(old_rangers[i]);
	    break;
	}
    }

    add_pupil    = new_pupil    - old_company_pupil;
    add_gondor   = new_gondor   - old_company_gondor;
    add_ithilien = new_ithilien - old_company_ithilien;

    if (sizeof(add_pupil))
    {
	log_msg += "Pupils in ranger list, but not in company list:\n" +
	implode(add_pupil,", ") + "\n";
	to_be_removed += add_pupil;
    }
    if (sizeof(add_gondor))
    {
	log_msg += "Gondor rangers in ranger list, but not in company list:\n" +
	implode(add_gondor,", ") + "\n";
	to_be_removed += add_gondor;
    }
    if (sizeof(add_ithilien))
    {
	log_msg += "Ithilien rangers in ranger list, but not in company list:\n" +
	implode(add_ithilien,", ") + "\n";
	to_be_removed += add_ithilien;
    }

    sub_pupil    = old_company_pupil    - new_pupil;
    sub_gondor   = old_company_gondor   - new_gondor;
    sub_ithilien = old_company_ithilien - new_ithilien;

    if (sizeof(sub_pupil))
    {
	log_msg += "Pupils in company list, but not in ranger list:\n" +
	implode(sub_pupil,", ") + "\n";
	to_be_removed += sub_pupil;
    }
    if (sizeof(sub_gondor))
    {
	log_msg += "Gondor rangers in company list, but not in ranger list:\n" +
	implode(sub_gondor,", ") + "\n";
	to_be_removed += sub_gondor;
    }
    if (sizeof(sub_ithilien))
    {
	log_msg += "Ithilien rangers in company list, but not in ranger list:\n" +
	implode(sub_ithilien,", ") + "\n";
	to_be_removed += sub_ithilien;
    }

    for (i = 0; i < sizeof(to_be_removed); i++)
    {
	remove_from_list(to_be_removed[i]);
	log_msg += CAP(to_be_removed[i]) + " removed from member list!\n";
    }
    if (strlen(log_msg))
	write_file(MEMBER_LOG,ctime(time()) + ":\n" + log_msg + "\n");
}
