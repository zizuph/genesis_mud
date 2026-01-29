/*
 * /secure/master.c
 *
 * This is the LPmud master object, used from version 3.0.
 * It is the second object loaded after void.c.
 * Everything written with 'write()' at startup will be printed on
 * stdout.
 * 1. create() will be called first.
 * 2. flag() will be called once for every argument to the flag -f
 * 	supplied to 'parse'.
 * 3. start_boot() will be called.
 * 4. preload_boot() will be called for each file to preload.
 * 5. final_boot() will be called.
 * 6. The game will enter multiuser mode, and enable log in.
 */

#pragma no_clone
#pragma no_inherit
#pragma resident

#include "/secure/std.h"
#include "/sys/stdproperties.h"
#include "/sys/living_desc.h"
#include "/sys/macros.h"
#include "/sys/filepath.h"
#include "/sys/udp.h"
#include "/sys/log.h"

#define SAVEFILE	"/syslog/KEEPERSAVE"	/* File to save object in */
#define QUEUE		"/secure/queue"
#define LOGIN_OBJECT	"/secure/login"
#define FINGER_PLAYER	"/secure/finger_player"

#include "/secure/master/flags.c"
#include "/secure/master/siteban.c"
#include "/secure/master/fob.c"
#include "/secure/master/faircombat.c"
#include "/secure/master/spells.c"
#include "/secure/master/language.c"
#include "/secure/master/notify.c"

/*
 * Prototypes
 */
static object find_admin();
static object find_someone(string wiz);
varargs object finger_player(string pl_name, string file);
static int check_snoop_validity(object snooper, object snoopee, int sanction);
varargs mixed do_debug(string icmd, mixed a1, mixed a2, mixed a3);
public void check_memory(int dodecay);
string creator_object(object obj);
static int special_sanct(string *dirs, string eff_user, string dom, string access);

/*
 * The global variables that are saved in the SAVEFILE.
 */
object  login_ob;
int     game_started;
string  *def_locations;
string  *temp_locations;
mapping known_muds;
mapping notrans_map;


/*
 * The global variables that are not saved.
 */
static int     mem_fail_flag;
static int     memory_limit;
static int     memory_check_alarm = 0;
static mapping command_substitute;
static string  udp_manager;
static object simul_efun_ob;

#define MEMORY_CHECK_TIME 900.0 /* 15 minutes */

void
create() 
{
    command_substitute = ([
			   "n":"north",
			   "s":"south",
			   "w":"west",
			   "e":"east",
			   "u":"up",
			   "d":"down",
			   "sw":"southwest",
			   "se":"southeast",
			   "nw":"northwest",
			   "ne":"northeast",
			   "l":"look",
			   "i":"inventory"
			  ]);
    mem_fail_flag = 0;
#ifdef LARGE_MEMORY_LIMIT
    memory_limit = LARGE_MEMORY_LIMIT;
#else
    memory_limit = 28000000;
#endif
    set_auth(this_object(), "root:root");

    /* We regularly check for armageddon. */
    memory_check_alarm =
	set_alarm(MEMORY_CHECK_TIME , 0.0, "check_memory", 1);
}

string 
short() 
{
    return "the hole in the donut";
}

/*
 * Function name: save_master
 * Description  : This function saves the master object to a file.
 */
static void
save_master()
{
    set_auth(this_object(), "root:root");
    save_object(SAVEFILE); 
}

/*
 * Function name: authorization
 * Description  : This filter checks which whether which players have the
 *                necessary authorization.
 * Arguments    : object pobj    - the object to check.
 *                int    mintype - the the minimum rank necessary.
 * Returns      : int 1/0 - true if the player has the authorization.
 */
static varargs int 
authorization(object pobj, int mintype)
{
    if (!pobj)
	return 0;

    if (!mintype)
	mintype = WIZ_ARCH;

    if ((geteuid(pobj) == ROOT_UID) ||
	(query_wiz_rank(geteuid(pobj)) >= mintype))
    {
	return 1;
    }

    return 0;
   
}
/*********************************************************************
 *
 * GD - INTERFACE LFUNS
 *
 * The below lfuns are called from the Gamedriver for various reasons.
 */

/*
 * Called on startup of game if '-f' is given on the commandline.
 *
 * To test a new function xx in object yy, do
 * parse "-fcall yy xx arg" "-fshutdown"
 */
void 
flag(string str) 
{
    string file, arg;

    if (game_started)
	return;

    if (sscanf(str, "for %d", arg) == 1) 
    {
	return;
    }

    if (str == "shutdown") 
    {
	do_debug("shutdown");
	return;
    }

    if (sscanf(str, "echo %s", arg) == 1) 
    {
	write(arg + "\n");
	return;
    }
    
    if (sscanf(str, "call %s %s", file, arg) == 2) 
    {
	arg = (string)call_other(file, arg);
	write("Got " + arg + " back.\n");
	return;
    }
    write("master: Unknown flag " + str + "\n");
}

/*
 * Function name:   get_mud_name
 * Description:     Gives the name of the mud. The name will be #defined in
 *		    all files compiled in the mud. It can not contain spaces.
 * Returns:         Name of the mud.
 *		    We always return a string but we must declare it mixed
 *		    otherwise the type checker gets allergic reactions.
 */
mixed
get_mud_name() 
{
#ifdef MUD_NAME    
    mixed n;

    n = MUD_NAME;
    if (mappingp(n))
    {
	if (stringp(n[debug("mud_port")]))
	    return n[debug("mud_port")];
	else
	    return n[0];
    }
    else if (stringp(MUD_NAME))
	return MUD_NAME;
#endif
    return "LPmud(" + do_debug("version") + ":" + MUDLIB_VERSION + ")";
}

/*
 * Function name:   get_root_uid
 * Description:     Gives the uid of the root user
 * Returns:         Name of the 'root' user
 */
string
get_root_uid() 
{
    return ROOT_UID;
}

/*
 * Function name:   get_bb_uid
 * Description:     Gives the uid of the backbone
 * Returns:         Name of the 'backbone' user
 */
string
get_bb_uid()
{
    return BACKBONE_UID;
}

object
get_vbfc_object()
{
    return "/secure/vbfc_object"->ob_pointer();
}

/*
 * This function is called every time a player connects.
 * input_to() can't be called from here.
 */
object
connect() 
{
    /* write("secure/master: Connect to /secure/login.c..."); */
    set_auth(this_object(), "#:root");
    login_ob = clone_object(LOGIN_OBJECT);
    write("\n");
    return login_ob;
}

mixed
valid_set_auth(object setter, object getting_set, mixed value)
{
    string *oldauth, *newauth;
    string auth = query_auth(getting_set);

    if (!stringp(value) || (setter != this_object() &&
			    setter != simul_efun_ob))
	return auth;
    oldauth = (stringp(auth) ?
	     explode(auth, ":") :
             ({ "0", "0"}));
    newauth = explode(value, ":");
    if (sizeof(newauth) != 2)
	return auth;
    if (newauth[0] != "#")
    {
	oldauth[0] = newauth[0];
    }
    if (newauth[1] != "#")
    {
	oldauth[1] = newauth[1];
    }
    return implode(oldauth,":");
}

/*
 * Function name:   valid_seteuid
 * Description:     Checks if a certain user has the right to set a certain
 *                  objects effective 'userid'. All objects has two 'uid'
 *                  - Owner userid: Wizard who caused the creation.
 *                  - Effective userid: Wizard responsible for the objects
 *                    actions.
 *                  When an object creates a new object, the new objects
 *                  'Owner userid' is set to creating objects 'Effective
 *                  userid'.
 *                  
 * Arguments:       ob:   Object to set 'effective' user id in.
 *                  str:  The effuserid to be set.
 * Returns:         True if set is allowed.
 * Note:	    Setting of effuserid to userid is allowed in the GD as
 *		    well as setting effuserid to 0.
 */
int
valid_seteuid(object ob, string str) 
{
    /*
     * Root can be anyone it pleases.
     */
    if (getuid(ob) == ROOT_UID)
	return 1;

    /*
     * We can be ourselves, why we have to check this... well...
     */
    if (getuid(ob) == str)
	return 1;

    /*
     * When arches and keepers are in a domain, the lord can't change
     * euid in his objects to the arch.
     */
    if (query_wiz_rank(str) > WIZ_ARCH)
	return 0;

    /*
     * A lord can be anyone of his subject wizards.
     */
    if (getuid(ob) == query_domain_lord(str) 
	|| getuid(ob) == query_domain_lord(query_wiz_dom(str)))
	return 1;

    return 0;
}

/*
 * This is the function called from the game driver when it wants to know
 * if it has permission to write in file 'file_name' with effective user
 * 'eff_user'. The return value is simply true or false.
 *
 */

/*
 * Function name:   valid_write
 * Description:     Checks if a certain user has the right to write a file
 * Arguments:       file - File name of the file to be written
 *                  ob - object wanting to do the write
 *		    func - The calling function.
 * Returns:         True if write is allowed.
 */
int
valid_write(string file, mixed writer, string func) 
{
    string junk, dom, wname, dir, sstr;
    string *dirs, *open_dir;
    int i, flag, sval;
    mapping sanct;
    object wob;

    string eff_user;

    if (stringp(writer))
	eff_user = writer;
    else
    {
	if (writer == this_object())
	    return 1;
	eff_user = explode(query_auth(writer), ":")[1];
    }

    dirs = explode(file, "/");
    while (sizeof(dirs) && dirs[0] == "")
	dirs = dirs[1..sizeof(dirs)-1];

    /* 
     * All paths should be resolved before this.
     */
    if ((member_array("..", dirs) >= 0) ||
	(member_array("", dirs) >= 0) ||
	(member_array(".", dirs) >= 0))
	return 0;

    /* 
     * Anonymous objects can`t do anything.
     */
    if (eff_user == 0)
	return 0;

    /*
     * Root, keepers & arches can always do as they please.
     */
    if ((eff_user == ROOT_UID) || 
	(query_wiz_rank(eff_user) >= WIZ_ARCH))
    {
	return 1;
    }

    /*
     * You can always write in /open.
     */
    if (dirs[0] == "open")
	return 1;

    /* 
     * Must be /d/Domname/something
     */
    if (sizeof(dirs) < 3)  
	return 0;

    /*
     * Domain writes.
     */
    if (dirs[0] != "d")
	return 0;

    dom = dirs[1];

    if (sizeof(dirs) >= 3) 	/* Can be /d/domname/dirname/something */
	wname = dirs[2];
    else
	wname = "";

    if (sizeof(dirs) > 4)
	dir = dirs[3];
    else
	dir = "";

    if (sizeof(dirs) > 2)
	dirs = dirs[2..sizeof(dirs)];
    /*
     * A wizard can write in his directory.
     */
    if (eff_user == wname)
	return 1;

    /*
     * Special sanctioning.
     * This must be done here since even the private dir might be
     * revealed through this special sanction.
     */
    if (special_sanct(dirs, eff_user, dom, "W"))
	return 1;

    /*
     * No-one except the lord can write in a wizards private directory.
     */
    if (dir == "private" && 
	query_domain_lord(dom) != eff_user)
	return 0;

    /*
     * Domain lords can write anywhere in their domains.
     */
    if (eff_user == query_domain_lord(dom))
	return 1;

    /*
     * The special wizard domain has no special dirs such as open / common
     */
    if (dom == WIZARD_DOMAIN)
	return 0;

    /*
     * A wizard can write in the domain directories that is not wiz dirs.
     */
    if ((query_wiz_dom(eff_user) == dom || eff_user == dom) && 
	query_wiz_dom(wname) != dom)
	return 1;

    /*
     * Sanctioning
     *
     * This breaks down into two cases: 
     *
     * (a) Private sanctioning.
     * (b) Domain sanctioning.
     *
     */
    
    /*
     * Begin with domain sanctioning, the most general case.
     */
    sanct = query_domain_sanction(dom);

    /*
     * Check for the 'all', domain, individual case.
     */
    sstr = "" + sanct["all"];
    sstr += "" + sanct[query_wiz_dom(eff_user)];
    sstr += "" + sanct[eff_user];

    if (strlen(sstr))
    {
	for (i = 0 ; i < strlen(sstr) ; i++)
	    if (sstr[i] == 'w')
		sval = 1;
	
	for (i = 0 ; i < strlen(sstr) ; i++)
	    if (sstr[i] == 'W' && query_wiz_rank(eff_user) >= WIZ_NORMAL)
		sval = 2;

	/*
	 * Santion to write anywhere.
	 */
	if (sval == 2)
	    return 1;
    
	/*
	 * Trickier case: 
         * Sanction to write in all non-wiz directories.
	 */
	if (sval == 1)
	{
	    if (!strlen(wname))
		return 1;

	    if (member_array(wname, query_domain_members(dom)) < 0)
		return 1;
	}
    }
    
    /* 
     * Private sanctioning.
     * Check that the domain is right as well as the sanctioning.
     * You must be in a domain subdir for this to work.
     */
    if (strlen(wname) && query_wiz_dom(wname) == dom)
    {
	wob = find_player(wname);
	if (!wob)
	{
	    if (wob = finger_player(wname))
	    {
		sstr = wob->query_sanctioning(eff_user);
		wob->remove_object();
	    }
	}
	else
	    sstr = wob->query_sanctioning(eff_user);
	
	if (strlen(sstr))
	{
	    for (i = 0 ; i < strlen(sstr) ; i++)
		if (sstr[i] == 'w')
		    return 1;
	}
    }

    /*
     * Special sanctioning.
     */
    return 0;
}

/*
 * Function name:   valid_read
 * Description:     Checks if a certain user has the right to read a file
 * Arguments:       file - File name of the file to be read
 *                  reader - object wanting to do the read or name to check
 *		    func - The calling function.
 * Returns:         True if read is allowed.
 */
int
valid_read(string file, mixed reader, string func) 
{
    string dom, wname, dir, sstr;
    string *dirs;
    mapping sanct;
    object wob;
    int i, sval;

    string eff_user;

    if (stringp(reader))
	eff_user = reader;
    else
    {
	if (reader == this_object())
	    return 1;
	eff_user = explode(query_auth(reader), ":")[1];
    }

    /*
     * Anyone can determine time & size of any file.
     */
    if (func == "file_time" ||
	func == "file_size")
	return 1;

    dirs = explode(file, "/");
    while (sizeof(dirs) && dirs[0] == "")
	dirs = dirs[1..sizeof(dirs)-1];

    /* 
     * All paths should be resolved before this.
     */
    if ((member_array("..", dirs) >= 0) ||
	(member_array("", dirs) >= 0) ||
	(member_array(".", dirs) >= 0))
	return 0;

    /* 
     * Anonymous objects can`t do anything.
     */
    if(eff_user == 0)
	return 0;

    /*
     * Root, keepers & arches can always do as they please.
     */
    if ((eff_user == ROOT_UID) || 
	(query_wiz_rank(eff_user) >= WIZ_ARCH))
    {
	return 1;
    }

    /*
     * Allow read in /
     */
    if (file == "/")
	return 1;

    /*
     * Check for the "closed" directories.
     */
    if ((dirs[0] == "players") ||
	(dirs[0] == "binaries") ||
	(dirs[0] == "syslog" && dirs[1] == "log"))
	return 0;

    /*
     * Allow read in all that is not /d/something
     */
    if (dirs[0] != "d" || sizeof(dirs) == 1)
	return 1;

    dom = dirs[1];
    if (sizeof(dirs) > 2)
	wname = dirs[2];
    if (sizeof(dirs) > 3)
    {
	dir = dirs[3];
	dirs = dirs[2..sizeof(dirs)];
    }
    else
	dir = "";

    /*
     * Anyone can read in the domain and wizards open directory.
     */
    if ((dir == "open") || (wname == "open"))
	return 1;
    /*
     * A wizard can read in his own directory.
     */
    if (wname == eff_user)
	return 1;

    /*
     * Special sanctioning.
     * This must be done here since even the private dir might be
     * revealed through this special sanction.
     */
    if (special_sanct(dirs, eff_user, dom, "R"))
	return 1;

    /*
     * No-one except the lord can read in a wizards private directory.
     */
    if (dir == "private" && 
	query_domain_lord(dom) != eff_user)
	return 0;

    /* 
     * These are specific users, that for some reason or other should
     * be able to read anywhere. Specific examples are local users that
     * can read the files outside the mud anyway but most particularly
     * reviewers if such services are employed.
     */
    if (query_global_read()[eff_user])
	return 1;

    /*
     * All wizards in the domain can read everything in the domain.
     * unless it is the 'lonely wizard' domain. Then each wizard can only
     * read his own files.
     */
    if ((query_wiz_dom(eff_user) == dom) || (eff_user == dom)) {
	if (dom != WIZARD_DOMAIN)
	    return 1;
	else
	    return 0;
    }

    /*
     * Sanctioning
     *
     * This breaks down into two cases: 
     *
     * (a) Private sanctioning.
     * (b) Domain sanctioning.
     * (c) Special domain sanctioning. Taken care of above.
     *
     */
    
    /*
     * Begin with domain sanctioning, the most general case.
     *
     * First check that we are trying to read in a domain.
     */
 
    if (query_domain_number(dom) == -1)
        return 0;

    sanct = query_domain_sanction(dom);

    /*
     * Check for the 'all', domain, individual case.
     */
    sstr = "" + sanct["all"];
    sstr += "" + sanct[query_wiz_dom(eff_user)];
    sstr += "" + sanct[eff_user];

    sval = 0;
    if (strlen(sstr))
    {
	for (i = 0 ; i < strlen(sstr) ; i++)
	    if (sstr[i] == 'r')
		sval = 1;
	
	for (i = 0 ; i < strlen(sstr) ; i++)
	    if (sstr[i] == 'R')
		sval = 2;

	/*
	 * Santion to read anywhere.
	 */
	if (sval == 2)
	    return 1;
    
	/*
	 * Trickier case: 
         * Sanction to read in all non-wiz directories.
	 */
	if (sval == 1)
	{
	    if (!strlen(wname))
		return 1;

	    if (member_array(wname, query_domain_members(dom)) < 0)
		return 1;
	}
    }
    
    /* 
     * Private sanctioning.
     * Check that the domain is right as well as the sanctioning.
     * You must be in a domain subdir for this to work.
     */
    if (strlen(wname) && query_wiz_dom(wname) == dom)
    {
	wob = find_player(wname);
	if (!wob)
	{
	    if (wob = finger_player(wname))
	    {
		sstr = wob->query_sanctioning(eff_user);
		wob->remove_object();
	    }
	}
	else
	    sstr = wob->query_sanctioning(eff_user);
	
	if (strlen(sstr))
	{
	    for (i = 0 ; i < strlen(sstr) ; i++)
		if (sstr[i] == 'r')
		    return 1;
	}
    }

    return 0;
}

/*
 * Function name: special_sanct
 * Description:   Check for special sanctioning.
 * Arguments:	  dirs: The path to check.
 * 		  eff_user: The effective user.
 *		  dom: The domain to check in.
 *                access: The required access.
 */
static int
special_sanct(string *dirs, string eff_user, string dom, string access)
{
    mapping sanct, spart;
    int i, j, sval;
    string *sdirs, path, priv;

    sanct = query_special_sanction(dom);
    path = implode(dirs, "/");

    /*
     * Domain sanction.
     */
    spart = sanct[query_wiz_dom(eff_user)];
    if (mappingp(spart))
    {
	sdirs = m_indexes(spart);

	for (i = 0 ; i < sizeof(sdirs) ; i++)
	{
	    if (strlen(path) < strlen(sdirs[i]))
		continue;
	    
	    /*
	     * Only check for specific sanctioning if 'W' is required.
	     * "R" is implicit.
	     */
	    if (access == "W")
	    {
		sval = 0;
		priv = spart[sdirs[i]];
		for (j = 0 ; j < strlen(priv) ; j++)
		    if (priv[j] == 'W')
			sval = 1;
	    }
	    else
		sval = 1;

	    if (!sval)
		continue;

	    if (sdirs[i] == path[0..(strlen(sdirs[i]) - 1)])
		return 1;
	}
    }

    /*
     * Wizard sanction.
     */
    spart = sanct[eff_user];
    if (mappingp(spart))
    {
	sdirs = m_indexes(spart);

	for (i = 0 ; i < sizeof(sdirs) ; i++)
	{
	    if (strlen(path) < strlen(sdirs[i]))
		continue;
	    
	    /*
	     * Only check for specific sanctioning if 'W' is required.
	     * "R" is implicit.
	     */
	    if (access == "W")
	    {
		sval = 0;
		priv = spart[sdirs[i]];
		for (j = 0 ; j < strlen(priv) ; j++)
		    if (priv[j] == 'W')
			sval = 1;
	    }
	    else
		sval = 1;

	    if (!sval)
		continue;

	    if (sdirs[i] == path[0..(strlen(sdirs[i]) - 1)])
		return 1;
	}
    }

    return 0;
}

int
valid_move(object ob, object dest)
{
    return 1;
}

/*
 * Function name:   valid_trace
 * Description:     Checks if a certain user has the right to use trace
 *		    This can be used to minimize the cost of trace if it
 *		    is only to be used by some higher level wizards.
 * Arguments:       ob: Object that wants to set trace
 *                  param: Either a string or a number, if a string then it
 *			   is a call from efun traceprefix(), if a number other
 *			   then '0' the it is a call from trace()
 * Returns:         True if use is allowed.
 */
int
valid_trace(object ob, mixed param)
{
    return 1;
}

/*
 * Function name:   valid_snoop
 * Description:     Checks if a certain user has the right to use snoop
 *		    another user.
 * Arguments:       snooper: The prospective snooper.
 *		    snopee: The prospective snoopee.
 * Returns:         True if use is allowed.
 */
public int
valid_snoop(object initiator, object snooper, object snoopee)
{
    string by_name, po_name;

    by_name = geteuid(snooper);
    po_name = geteuid(initiator);

    /* 
     * Break snoop case:
     *
     * Valid if previous_object() (= breaker) has the right to
     * snoop the person currently doing the snooping.
     * Do not consider sanctioning in this case.
     */
    if (!snoopee)
    {
	/*
	 * Anyone can break his own snoop.
	 */
	if (by_name == po_name)
	    return 1;

	return check_snoop_validity(initiator, snooper, 0);
    }

    /*
     * Prevent accidental breaking of snoop.
     */
    if (efun::query_snoop(snoopee))
	return 0;

    /* 
     * Set up snoop case:
     *
     * Valid if previous_object() (= the one setting up the snoop) has
     * the right to snoop the snoopee.
     * Make sure this does not break a snoop though.
     * Do not consider sanctioning in this case.
     */
    if (po_name != by_name)
	return check_snoop_validity(initiator, snoopee, 0);
    
    /*
     * Ordinary snoop case:
     *
     * Valid if snooper can snoop snoopee.
     * Consider sanctioning in this case.
     */
    return check_snoop_validity(snooper, snoopee, 1);
}

/*
 * Function name:   check_snoop_validity
 * Description:     Do the actual validity checking.
 * Arguments:       snooper: The prospective snooper.
 *		    snopee: The prospective snoopee.
 *		    sanction: Consider sanctioning or not.
 * Returns:         True if use is allowed.
 */
static int
check_snoop_validity(object snooper, object snoopee, int sanction)
{
    int by_type, on_type;
    string by_name, on_name, sanct;
    object wob;
    int i;

    by_name = geteuid(snooper);
    by_type = query_wiz_rank(by_name);
    on_name = geteuid(snoopee);
    on_type = query_wiz_rank(on_name);
 
    /*
     * Only wizards can snoop.
     */
    if (by_type == WIZ_MORTAL)
	return 0;

    /*
     * Lords can snoop members everywhere, if the snoopee has lvl < ARCH
     * and they can snoop apprentices too.
     */
    if ((by_type == WIZ_LORD) && 
	(((query_domain_lord(query_wiz_dom(on_name)) == by_name) &&
	 (on_type < WIZ_ARCH)) ||
	 (on_type == WIZ_APPRENTICE)))
    {
	return 1;
    }

    /*
     * Arch snoops all but arch.
     */
    if (by_type >= WIZ_ARCH && on_type < WIZ_ARCH)
	return 1;

    /* 
     * Mortals are safe in sanctuary for all but arch++.
     */
    if (environment(snoopee) && environment(snoopee)->query_prevent_snoop())
	return 0;

    /*
     * Ordinary wizzes snoops all mortals.
     */
    if (on_type == WIZ_MORTAL)
	return 1;

    /* 
     * A wizard can sanction another wizard to snoop him.
     * Check that the domain is right as well as read privs.
     * We must be under a wiz subdir to be able to do this at all.
     */
    if (sanction)
    {
	wob = find_player(on_name);
	if (!wob)
	{
	    wob = finger_player(on_name);
	    sanct = wob->query_sanctioning(by_name);
	    wob->remove_object();
	}
	else
	    sanct = wob->query_sanctioning(by_name);
	
	if (strlen(sanct))
	{
	    for (i = 0 ; i < strlen(sanct) ; i++)
		if (sanct[i] == 's')
		    return 1;
	}
    }

    return 0;
}

/*
 * Function name:   creator_file
 * Description:     Gives the name of the creator of a file. This is a
 *                  direct function of the file_name().
 * Returns:         Name of the creator
 */
string 
creator_file(string file)
{
    string str, dom, wiz, residue;

    str = file;

    if (str[0] != '/')
	str = "/" + str;

    /* 
     * Domains: return the wizard name if the file is resident in
     * the directory of an active (not retired) wizard.
     * If the directory is "open" or "common", the domain is set 
     * to be the creator. Return the name of the Lord otherwize.
     */
    if ((str[1] == 'd') && (str[2] == '/'))
    {
	if (sscanf(str, "/d/%s/%s/%s", dom, wiz, residue) == 1)
	{
	    sscanf(str, "/d/%s/%s", dom, residue);
	    wiz = 0;
	}

	if ((wiz) && (query_wiz_dom(wiz) == dom))
	    return wiz;
	else
	    return dom;
    }

    /* 
     * /secure/... return root uid.
     */
    if (extract(str, 0, 7) == "/secure/")
	return ROOT_UID;

    /*
     * No cloning or loading from or /open.
     */
    if (extract(str, 0, 5) == "/open/")
	return 0;

    /*
     * All else: return backbone uid.
     */
    return BACKBONE_UID;

}

string
modify_path(string path, object ob)
{
    return path;
}

string
valid_compile_path(string path, string filename, string fun)
{
    return path;
}

/*
 * Convert a possibly relative path to an absolute path. We can assume
 * that there is a this_player(). This is called from within the editor.
 */
string 
make_path_absolute(string path)
{
    return FPATH(this_player()->query_path(), path);
}

/*
 * Function name: 	start_boot()
 * Description:		Loads master data, including list of all domains and
 *			wizards. Then make a list of preload stuff
 * Arguments:		load_empty: If true start_boot() does no preloading
 * Return:		List of files to preload
 */
string *
start_boot(int load_empty)
{
    string *prefiles;

    if (game_started)
	return 0;

    set_auth(this_object(), "root:root");
    /*
     * Fix the userids of the simul_efun object
     */
    simul_efun_ob = find_object("/secure/simul_efun");
    set_auth(simul_efun_ob, "root:root");

    write("Retrieving master data.\n");
    if (!restore_object(SAVEFILE))
    {
	write(SAVEFILE + " nonexistant. Using defaults.\n");
	this_object()->load_fob_defaults();
    }
    if (!mappingp(cmd_count))
	cmd_count = ([ ]);

    if (load_empty) 
    {
	write("Not preloading.\n");
	return 0;
    }
    
    /* 
     * Make list of preload stuff: Domain and wizard
     * 		
     */
    prefiles = query_domain_preload() + query_mage_preload();

#ifdef PRELOAD_FIRST
    if (stringp(PRELOAD_FIRST))
	prefiles = explode(read_file(PRELOAD_FIRST), "\n") + prefiles;
    else if (pointerp(PRELOAD_FIRST))
	prefiles = PRELOAD_FIRST + prefiles;
#endif PRELOAD_FIRST

    return prefiles;
}

void
preload_boot(string file)
{
    string err;
    int t1;

    set_auth(this_object(), "#:root");

    if (file_size(file + ".c") == -1)
	return;

    err = creator_file(file);
    set_auth(this_object(), "#:" + err);
    write(file + ".c (" + err + ")\n"); 

    if (err = (string)LOAD_ERR(file))
	write("\tCan not load: " + file + ":\n     " + err + "\n");
}

#define GAME_START "/GAME_START"

void
final_boot()
{
    int theport;
    string game_start;

    this_object()->setup_maplinks();
#ifdef UDP_MANAGER
    udp_manager = UDP_MANAGER;
    if (catch(udp_manager->teleledningsanka()))
	udp_manager = 0;

    if (stringp(udp_manager))
	udp_manager->send_startup_udp(MUDLIST_SERVER[0], MUDLIST_SERVER[1]);
    else
#endif    
	debug("send_udp", MUDLIST_SERVER[0], MUDLIST_SERVER[1],
	      "@@@" + UDP_STARTUP + this_object()->startup_udp() + "@@@\n");

    game_started = 1;

    theport = debug("mud_port");
    if (theport != 0)
    {
	game_start = GAME_START + "." + theport;
	write_file(game_start, ctime(time()) + "\n");
    }

    debug("set_swap",
	  ({
	      SWAP_MEM_MIN,
	      SWAP_MEM_MAX,
	      SWAP_TIME_MIN,
	      SWAP_TIME_MAX
	  }) );
}

object *
start_shutdown()
{
    return users();
}

void
cleanup_shutdown(object ob)
{
    set_this_player(ob);
    ob->quit();
}

void
final_shutdown()
{
    if (stringp(udp_manager))
    {
	udp_manager->send_shutdown_udp(MUDLIST_SERVER[0], MUDLIST_SERVER[1]);
	udp_manager->update_masters_list();
	set_auth(this_object(), "#:root");
	save_object(SAVEFILE);
    }
}

/*
 * Get the owner of a file. This is called from log_error(), so as
 * to be able to know which wizard should have an error message.
 * Some checks should be added to take care of the domain file tests.
 *
 */
/* This function is no longer used by the GD. But it is used once in this
 * file. It should be relocated
 */
string 
get_wiz_name(string file)
{
    string name, dom;

    return creator_file(file);
}

/*
 * Calculate a path for the logging of an error.
 */
string 
get_log_file(string file)
{
    string name, path;

    name = creator_file(file);
    path = query_wiz_path(name) + "/log";
    set_auth(this_object(), "root:root");

    if (file_size(path) != -2) 
	mkdir(path);

    return path + "/errors";
}

/*
 * Write an error message into a log file. The error occured in the object
 * 'file', giving the error message 'message'.
 */
void 
log_error(string file, string message)
{
    string name;

    name = get_log_file(file);
    if (name == 0)
        name = "/log/LOST_ERRORS";
    set_auth(this_object(), "root:root");
    if (file_size(name) == -1)
	write_file(name, "*\n* This is your error log file\n*\n\n");
    write_file(name, message);
}

/*
 * This function is called from GD when rooms are destructed so that master
 * can move players to safety.
 */
void
destruct_environment_of(object ob)
{
    if (environment(ob))
	catch(ob->move(environment(ob)));

    if (!query_ip_number(ob))
	return;
    ob->move_living("X", ob->query_default_start_location());
}

/*
 * Define  where the '#include' statement is supposed to search for files.
 * "." will automatically be searched first, followed in order as given
 * below. The path should contain a '%s', which will be replaced by the file
 * searched for.
 */
string *
define_include_dirs()
{
    return ({ "/sys/%s", "/secure/%s" });
}

/*
 * Function name: get_ed_buffer_save_file_name
 * Description  : When a wizard is in ed and goes linkdead, this function
 *                is called to get the name of the save-file. If the
 *                wizard does not have the necessary rights, the function
 *                will disallow save.
 * Arguments    : string - the name of the file to save
 * Returns      : string - the name of the secured save-file
 *                0      - the player has no write-rights.
 */
string
get_ed_buffer_save_file_name(string file) 
{
    string *path;

    if (!objectp(this_player()))
	return 0;

    if (!valid_write(file, this_player(), "ED"))
	return 0;

    path = explode(file, "/");
    path[sizeof(path) - 1] = "dead_ed_" + path[sizeof(path) - 1];

    return implode(path, "/");
}

/* save_ed_setup and restore_ed_setup are called by the ed to maintain
   individual options settings. These functions are located in the master
   object so that the local gods can decide what strategy they want to use.

/*
 * The wizard object 'who' wants to save his ed setup. It is saved in the
 * file ~wiz_name/.edrc . A test should be added to make sure it is
 * a call from a wizard.
 *
 * Don't care to prevent unauthorized access of this file. Only make sure
 * that a number is given as argument.
 */
int 
save_ed_setup(object who, int code)
{
    string file;

    if (!intp(code))
	return 0;
    file = query_wiz_path((string)who->query_real_name()) + "/.edrc";
    rm(file);
    return write_file(file, code + "");
}

/*
 * Retrieve the ed setup. No meaning to defend this file read from
 * unauthorized access.
 */
int 
retrieve_ed_setup(object who) {
    string file;
    int code;

    file = query_wiz_path((string)who->query_real_name()) + "/.edrc";
    if (file_size(file) <= 0)
	return 0;
    sscanf(read_file(file), "%d", code);
    return code;
}

/*
 * The master object is asked if it is ok to shadow object ob. Use
 * previous_object() to find out who is asking.
 *
 * In this example, we allow shadowing as long as the victim object
 * has not denied it with a query_prevent_shadow() returning 1.
 */
int 
query_allow_shadow(object ob)
{
    if (ob == this_object())
	return 0;

    return !ob->query_prevent_shadow(previous_object());
}


/*
 * There are several occasions when the game driver wants to check if
 * a player has permission to specific things.
 *
 * These types are implemented so far:
 * "trace":		If the player is allowed to use tracing.
 * "wizard":		Is the player considered at least a "minimal" wizard ?
 * "error messages":	Is the player allowed to get run time error messages ?
 */
int 
query_player_level(string what)
{
    string name = this_player()->query_real_name();
    int    rank = query_wiz_rank(name);

    if (!objectp(this_player()))
	return 0;

    switch(what)
    {
    case "wizard":
	return (rank > 0);
    case "error messages":
	if (rank > 0)
	    return 1;
	if (this_player()->query_prop(PLAYER_I_SEE_ERRORS))
	    return 1;
	if (extract(name, -2) == "jr")
	    return 1;
	return 0;
    case "trace":
	return (rank >= WIZ_ARCH);
    }
}

/*
 * Function name:   valid_exec
 * Description:     Checks if a certain 'program' has the right to use exec()
 * Arguments:       name: Name of the 'program' that attempts to use exec()
 *                        Note that this is different from file_name(),
 *                        Programname is what 'function_exists' returns.
 *                  NOTE, the absence of a leading slash in the name.
 *                  to:   destination of socket
 *                  from: target of the socket
 * Returns:         True if exec() is allowed.
 */
int
valid_exec(string name, object to, object from)
{
    if (name == "secure/login.c" || 
	name == "std/possob.c" ||
	name == (extract(LOGIN_NEW_PLAYER,1) + ".c"))
	return 1;

    return 0;
}

void 
simul_efun_reload()
{
    set_auth(simul_efun_ob = find_object("/secure/simul_efun"), "root:root");
}

void
loaded_object(object lob, object ob)
{
    string creator = creator_object(ob); 
    string *auth = explode(query_auth(lob), ":");

    if (!creator)
    {
	do_debug("destroy", ob);
	throw("Loading a bad object from: " + file_name(lob) + ".\n");
	return;
    }
    if (auth[1] == "0")
    {
	creator = file_name(ob);
	do_debug("destroy", ob);
	throw("Unauthorized load: " + creator + " by: " +
	      file_name(lob) + "\n");
	return;
    }
    if ((creator == BACKBONE_UID) || (creator == auth[0]))
    {
	set_auth(ob, auth[1] + ":" + auth[1]);
	return;
    }
    set_auth(ob, creator + ":0");
}

void
cloned_object(object cob, object ob)
{
    string creator = creator_object(ob); 
    string *auth = explode(query_auth(cob), ":");

    if (!creator)
    {
	creator = file_name(ob);
	do_debug("destroy", ob);
	throw("Unauthorized clone: " + creator + " by: " +
	      file_name(cob) + "\n");
	return;
    }
    if (auth[1] == "0")
    {
	creator = file_name(ob);
	do_debug("destroy", ob);
	throw("Cloning without privilege: " + creator + " by: " +
	      file_name(cob) + "\n");
	return;
    }
    if ((creator == BACKBONE_UID) || (creator == auth[0]))
    {
	set_auth(ob, auth[1] + ":" + auth[1]);
	return;
    }
    set_auth(ob, creator + ":0");
}

/*
 * Function name:   approve_object
 * Description:     Separates approved and nonapproved objects.
 *                  Approved and nonapproved objects can not be mixed
 *		    with move_object().
 * Arguments:       ob: The object to check on
 * Returns:         1 if object approved.
 */
int
approve_object(object ob)
{
    if (function_exists("create", ob) == "/std/object")
	return 1;
    else
	return 0;
}

/*
 * Function name:   modify_command
 * Description:     Modify a command given by a certain living object.
 *                  This can be used for many quicktyper-like functions.
 *		    There is also some master.c defined substitutions.
 * Arguments:       cmd: string
 *                  ob: The object for which to modify the command
 * Returns:         The modified command to execute
 */
string
modify_command(string cmd, object ob)
{
    string str;

    if (ob->query_prop(LIVE_I_CONCENTRATE))
	ob->cmdhooks_break_spell(ob->query_prop(LIVE_S_BREAK_CONCENTRATE));

    if (strlen(str = command_substitute[cmd]))
	return str;

    /* We can not allow any handwritten VBFC
    */
    if (sscanf(" " + cmd + " ", "%s@@%s", str, str) == 2)
	cmd = implode(explode(cmd, "@@"), "#");

    if (!query_ip_number(ob))
	return (cmd[0] == '$' ?
		extract(cmd, 1) : cmd);   /* Currently no modification */
    else
    {
	if (cmd[0] == '$')
	    return extract(cmd, 1);
	/* Count commands for ranking list */
	if (environment(ob) && !ob->query_wiz_level())
	    cmd_count[environment(ob)->query_domain()]++;
	return ob->modify_command(readable_string(cmd));
    }
}

/*
 * Function name: query_memory_percentage
 * Description  : This function will return the percentage of memory usage
 *                of the game so far. When the counter reaches 100, it is
 *                time to reboot.
 * Returns      : int - the relative memory usage.
 */
nomask public int
query_memory_percentage()
{
    int    f;
    int    cval;
    string mc;
    string foobar;

    mc = debug("malloc");
    sscanf(mc, "%ssbrk requests: %d %d (a) %s", foobar, f, cval, foobar);

    return (cval / (memory_limit / 100));
}

/*
 * Function name:   memory_failure
 * Description:     This function is called when the gamedriver considers
 *                  itself in trouble and need the game shut down in a
 *		    graceful manner. This function _must_ be called
 *                  via a call_other. It may only be called by root itself
 *                  or by a member of the administration.
 */
static void
memory_failure()
{
    if (!mem_fail_flag)
    {
	mem_fail_flag = 1;

	set_auth(this_object(), "root:root");
	ARMAGEDDON->start_shutdown("The memory is almost used up!", 5,
	    ROOT_UID);
    }
}

/*
 * Function name:   memory_reconfigure
 * Description:	    This function is called when the gamedriver receives
 *		    an external signal, denoting that the memory status
 *		    has changed.
 * Arguments:       mem: Memory size, 0 small, 1 large.
 */
static void
memory_reconfigure(int mem)
{
    string mess;
    object          *list;
    int             i;

#ifdef LARGE_MEMORY_LIMIT
    if ((mem == 0 && memory_limit == SMALL_MEMORY_LIMIT) ||
	(mem == 1 && memory_limit == LARGE_MEMORY_LIMIT))
	return;

    if (mem == 0)
    {
	memory_limit = SMALL_MEMORY_LIMIT;
	mess = "small";
    }
    else
    {
	memory_limit = LARGE_MEMORY_LIMIT;
	mess = "large";
    }
    check_memory(0);
#endif

    list = users();
    for (i = 0; i < sizeof(list); i++)
	if (list[i]->query_wiz_level())
	    list[i]->catch_msg("@ Armageddon: I have switched to " + 
			       mess + " memory mode.\n");
}

/* This function is called if the driver gets sent a signal that it catches. */
void
external_signal(string sig_name)
{
    switch (sig_name)
    {
    case "HUP":
        write_file("/halt", "apa");
    case "INT":
    case "KILL":
        debug("shutdown");
        break;
    case "QUIT":
    case "TERM":
        debug("shutdown");
        break;
    case "USR1":
	memory_reconfigure(0);
	break;
    case "USR2":
	memory_reconfigure(1);
	break;
    case "TSTP":
    case "CONT":
    case "UNKNOWN":
    }
}

/*
 * Function name: query_memory_limit
 * Description:   This function returns the current memory limit.
 */
public int
query_memory_limit()
{
    return memory_limit;
}

/*
 * Function name: query_memory_failure
 * Description:   This function returns 1 if memory failure is detected.
 */
public int
query_memory_failure()
{
    return mem_fail_flag;
}

/*
 * Function name:  incoming_service
 * Description:    Handle incoming requests from other programs
 * Arguments:      String containing the request
 * Returns:        A string holding the answer to the request
 */
string
incoming_service(string request)
{
    string *tmp, str;
    object ob;

    if (!strlen(request))
	return "ERROR Bad request\n";
    tmp = explode(request, "\n");
    if (sizeof(tmp))
	request = tmp[0];
    tmp = explode(request, "\r");
    if (sizeof(tmp))
	request = tmp[0];
    tmp = explode(request, " ");
    switch (lower_case(tmp[0]))
    {
    case "user":
	if (sizeof(tmp) != 2)
	    return "ERROR Wrong number of parameters\n";
	ob = find_player(lower_case(tmp[1]));
	if (ob)
	{
	    if (query_wiz_rank(tmp[1]) >= WIZ_NORMAL)
		return ob->query_password() + ":" +
		    query_wiz_level(tmp[1]) + ":" +
			query_wiz_path(tmp[1]) + "\n";
	}
	else
	{
	    ob = finger_player(tmp[1]);
	    if (ob)
	    {
		str = ob->query_password() + ":" +
		    query_wiz_level(tmp[1]) + ":" +
			query_wiz_path(tmp[1]) + "\n";
		ob->remove_object();
		if (query_wiz_rank(tmp[1]) >= WIZ_NORMAL)
		    return str;
	    }
	    else if (query_domain_number(capitalize(tmp[1])) >= 0)
		return "*:0:/d/" + capitalize(tmp[1]) + "\n";
	}
	return "ERROR No such user\n";
    case "read":
	if (sizeof(tmp) != 3)
	    return "ERROR Wrong number of parameters\n";
	if (valid_read(tmp[2], lower_case(tmp[1]), "FTP"))
	    return "READ access\n";
	return "ERROR No access\n";
    case "write":
	if (sizeof(tmp) != 3)
	    return "ERROR Wrong number of parameters\n";
	if (valid_write(tmp[2], lower_case(tmp[1]), "FTP"))
	    return "WRITE access\n";
	return "ERROR No access\n";
    default:
	return "ERROR Unknown request\n";
    }
}


/*
 * Function name:   valid_save_binary
 * Description:     This function is called when a file has ordered the GD
 *                  to save a binary image of the program. This might not
 *		    be allowed by any and every file so master is asked.
 * Arguments:       file: Filename of the object.
 */
int 
valid_save_binary(string filename)
{
    return 1;
}

/* ob wishing to inherit inherit_file */
int
valid_inherit(object ob, string inherit_file)
{
    return 1;
}
/* ob trying to load file */
int 
valid_load(object ob, string file)
{
    return 1;
}

/*
 * Function name:   master_reload
 * Description:     Called from GD after a reload of the master object
 */
void
master_reload()
{
}

void
recreate(object old_master)
{
    create();
    game_started = 0;
    start_boot(1); /* This does what we want */
    game_started = 1;
#ifdef UDP_MANAGER
    udp_manager = UDP_MANAGER;
#endif
}

/*
 * Function name:   incoming_udp
 * Description:     Called from GD if a udp message has been received. This
 *		    can only happen if CATCH_UDP_PORT has been defined in
 *		    the GD's config.h file.
 * Arguments:	    from_host: The IP number of the sending host
 *		    message:   The message sent.
 */
void
incoming_udp(string from_host, string message)
{
    if (stringp(udp_manager))
	udp_manager->incoming_udp(from_host, message);
    else
    {
	set_auth(this_object(), "#:root");
	log_file("LOST_UDP", "(" + from_host + ") " + message + "\n", -1);
    }
}
 
/*
 * Function name: remove_interactive
 * Description  : Called from GD if a player logs out or goes linkdead. If
 *                the player quit the game, we don't do anything.
 * Arguments    : object ob    - the player that leaves the game.
 *                int linkdead - true if the player linkdied.
 */
void 
remove_interactive(object ob, int linkdied)
{
    QUEUE->dequeue(ob);

    /* If someone who logs in linkdies, we just dispose of it. Also,
     * people who are trying to create a character, will have to start
     * over again.
     */
    if ((MASTER_OB(ob) == LOGIN_OBJECT) ||
	(MASTER_OB(ob) == LOGIN_NEW_PLAYER))
    {
	ob->remove_object();
	return;
    }

    /* Player left the game. */
    if (!linkdied)
    {
	/* Notify the wizards of the fact that the player quit. */
	notify(ob, 1);
        return;
    }

    /* Notify all wizards of the linkdeath. */
    notify(ob, 2);

#ifdef STATUE_WHEN_LINKDEAD
    ob->linkdie();
#endif STATUE_WHEN_LINKDEAD
}

/*
 * Function name: gamedriver_message
 * Description  : This function may (only) be called by the gamedriver to
 *                give a message to all players if that is necessary.
 * ARguments    : string str - the message to tell the people
 */
void
gamedriver_message(string str)
{
    users()->catch_tell(str);
}

/*
 * Function name: runtime_error
 * Description  : In case a runtime error occurs, we tell the message to
 *                the people who need to hear it.
 * Arguments    : string error   - the error message.
 *                object ob      - the object that has the error.
 *                string program - the program name of the error.
 *                string file    - the filename of the error.
 */
void
runtime_error(string error, object ob, string prog, string file)
{
/*
 * We only give the message to the interactive player and not to the members
 * of the domain or the creator of the stuff. If you want that to happen,
 * you'll have to re-install that stuff into this function. Check it
 * carefully, since I didn't bother to make the code functional. I only
 * disabled it since it wasted our time. /Mercade
 */
    string fmt_error, cr, path;
    
#if 0
    string *domains = ({ });
    string creator_pgm = creator_file(prog);
    string creator_ob = creator_object(ob);
#endif

    if (this_interactive())
    {
	if (this_interactive()->query_wiz_level() ||
	    this_interactive()->query_prop(PLAYER_I_SEE_ERRORS))
	{
	    fmt_error =
		"\n\nRuntime error: " + error +
		"       Object: " + (ob ? file_name(ob) : "<???>") + 
		"\n      Program: " + prog +
		"\n         File: " + file + "\n\n";
	    this_interactive()->catch_tell(fmt_error);
	}
	else
	{
	    this_interactive()->catch_tell("Your sensitive mind notices " +
		"a wrongness in the fabric of space.\n");
	}
    }
    else
    {
	path = "";
	if (objectp(ob))
	{
	    cr = creator_object(ob);
	    path = query_wiz_path(cr);
	}
	path += "/log/runtime";
	fmt_error = ctime(time()) +
	    "\nRuntime error: " + error +
	    "       Object: " + (ob ? file_name(ob) : "<???>") + 
	    "\n      Program: " + prog +
	    "\n         File: " + file + "\n\n";
	
	write_file(path, fmt_error);
    }

#if 0
    if (creator_ob == creator_pgm)
	creator_ob = 0;
    if (creator_pgm)
	if (creator_pgm != ROOT_UID &&
	    creator_pgm != BACKBONE_UID &&
	    find_player(creator_pgm))
	    find_player(creator_pgm)->catch_error(fmt_error);
	else
	    domains += ({ creator_pgm });
    if (creator_ob)
	if (creator_ob != ROOT_UID &&
	    creator_ob != BACKBONE_UID &&
	    find_player(creator_ob))
	    find_player(creator_ob)->catch_error(fmt_error);
	else
	    domains += ({ creator_ob });

    switch (sizeof(domains))
    {
    case 1:
      filter(all_wizards, "domain_member", this_object(),
               domains[0])->catch_error(fmt_error);
        break;
    case 2:
        filter(all_wizards, "domains_member", this_object(),
               domains)->catch_error(fmt_error);
    }
#endif
}

/* 
 *    ----------------------------------------------------------------
 *    The code below this divisor is never called from the gamedriver.
 *    ----------------------------------------------------------------
 */

/* To allow the change of uids of the souls. */
void
remote_setuid()
{
    if (function_exists("open_soul", previous_object()) ==
	"/cmd/std/command_driver")
	set_auth(previous_object(), "0:0");
}

/*
 * Function name:   creator_object
 * Description:     Gives the name of the creator of an object. This is a
 *                  direct function of the file_name() of the object.
 * Returns:         Name of the wizard / domain
 */
string
creator_object(object obj)
{
    string ret;

    if (objectp(obj))
	ret = creator_file(file_name(obj));
    else
	ret = 0;

    /* write("File: " + file_name(obj) + ", Creator: " + ret + "\n"); */
    return ret;
}

/*
 * Function name:   domain_object
 * Description:     Gives the name of the domain of an object. This is a
 *                  direct function of the file_name() of the object.
 * Returns:         Name of the domain
 */
string
domain_object(object obj)
{
    string str,dom,wiz,name;

    if (!obj) return 0;
    
    str = file_name(obj);
    if (str[1] == 'd')
	sscanf(str,"/d/%s/%s/%s",dom,wiz,name);
    else
	dom = 0;
    return dom;
}


/*
 * Function name: load_old_player
 * Descripton:    This function is called from the login player object
 *                /std/player_sec when the player object is loaded initially. 
 *                It sets the euid of the player to root for 
 *                the duration of the load.
 */
object
load_old_player(string oldplayer_filename)
{
    int res;
    object pobj, op;
    string oname;

    pobj = previous_object();

    if (function_exists("load_player", pobj) !=  "/std/player_sec")
	return 0;

    oname = pobj->query_real_name();

    if ((file_size("/op/" + extract(oname, 0, 0) + "/" + oname + ".o") <= 0) &&
	(file_size("/op/" + oname + ".o") <= 0))
	return 0;

    op = clone_object(oldplayer_filename);

    if (!op)
	return 0;

    set_auth(this_object(), "#:root");
    export_uid(op);

    if (!op->enter_here(pobj->query_real_name()))
    {
	write("Couldn't restore your old character.\n");
	do_debug("destroy", op);
	return 0;
    }
    set_auth(this_object(), "#:" + creator(op));
    export_uid(op);

    return op;
}

/*
 * Function name: load_player
 * Descripton:    This function is called from /std/player_sec 
 *		  when the player object is loaded initially. 
 *                It sets the euid of the player to root for 
 *                the duration of the load.
 */
int
load_player()
{
    int res;
    object pobj;

    pobj = previous_object();

    if (function_exists("load_player", pobj) !=  "/std/player_sec" ||
	!LOGIN_NEW_PLAYER->legal_player(pobj))
	return 0;
    else
    {
	set_auth(this_object(), "#:root");
	export_uid(pobj);
	res = (int)pobj->load_player(pobj->query_real_name());
	set_auth(this_object(), "#:" + (pobj->query_wiz_level() ?
			  pobj->query_real_name() : BACKBONE_UID));
	export_uid(pobj);
	set_auth(this_object(), "#:root");
	return res;
    }
}

/*
 * Function name:   save_allow
 * Description:     Gives an object permission to write in a wizards dir
 */
int
save_allow(mixed extra)
{
    int res;
    object pobj = previous_object();
    string obname, save_auth;

    obname = function_exists("save_info", pobj);
    if (!this_interactive() || obname !=  "/std/board") 
	return 0;
    else
    {
	save_auth = query_auth(pobj);
	set_auth(this_object(), "#:root");
	export_uid(pobj);
	res = pobj->save_info(this_interactive(), extra);
	set_auth(pobj, save_auth);
	return res;
    }
}

    
/*
 * Function name:   save_player
 * Description:     Saves a player object.
 */
int
save_player()
{

    int res;
    object pobj;

    pobj = previous_object();
    
    if (function_exists("save_player", pobj) !=  "/std/player_sec" ||
	!LOGIN_NEW_PLAYER->legal_player(pobj))
	return 0;
    else
    {
	set_auth(this_object(), "#:backbone");
        pobj->fix_saveprop_list();
	set_auth(this_object(), "#:root");
	export_uid(pobj);
	res = (int)pobj->save_player(pobj->query_real_name());
	pobj->open_player();
	set_auth(this_object(), "#:" + (pobj->query_wiz_level() ?
					pobj->query_real_name() :
					BACKBONE_UID));
	export_uid(pobj);
	set_auth(this_object(), "#:root");
	return res;
    }
}

/*
 * Function name:   load_wiz_souls
 * Description:     Load the correct wizard souls for the player
 */
int
load_wiz_souls()
{

    int res;
    object pobj;

    pobj = previous_object();

    if ((function_exists("enter_game", pobj) !=  "/std/player_sec") &&
	(pobj != this_object()))
	return 0;
    else
	pobj->load_wiz_souls();
}

/*
 * Info should exist on this object but we do not want to inherit 
 * the entire /std/object
 */
mixed
query_prop(string str)
{
    if (str == OBJ_S_WIZINFO)
	return "This is the master object, it handles administration and security\n";
    else
	return 0;
}

object
check_caller()
{
    return this_object();
}

int
check_set_sponsor(mixed called_by_object)
{
    return 0;
}

/*
 * Function name: check_inherit
 *                Checks if an object is legal.
 *                file: File name of inherited file
 *                obj:  The object doing the inherit
 */
int
check_inherit(string file, mixed obj)
{
    /*
     * Rules /std/living only /std/player_sec, /std/npc
     * /std/player_sec only /std/player_pub
     */
    return 0;
}

/*
 * Function name: notify_error
 * Description:   Notify player and creator of the offending object
 *      	  that an error has occured.
 * Arguments:     where: In which routine the error occured,
 *		  err:   The error message to the creator.
 *		  info:  Optional extra information to the creator.
 */
void
notify_error(mixed where, string err, string info)
{
}

/* 
   Called from move when a destination room can not be loaded
   Logs the error in /log/wizname.name, /log/domainname.room
   and /log/room.ERRORS If the wiz is logged in then he gets the error too
*/
void
log_loaderror(string efile, mixed from, string verb, mixed pobj, string erl)
{
    string          wiz,
                    player,
                    emsg,
                    lfile1, lfile2,
                    gdriverror;
    object          pl;

    /*
     * Find the responsible wizard or someone else if wiz is not logged in
     */
    wiz = creator_object(pobj);
    if ((!wiz) || (wiz == BACKBONE_UID))
    {
	wiz = BACKBONE_UID;
	pl = find_admin();	/* Tell Gameadmin when error in /room */
	lfile1 = 0;
	lfile2 = 0;
    }
    else {
	pl = find_player(wiz);
	lfile1 = FPATH("/log",get_wiz_name(file_name(pobj))) + ".move";
	if ((domain_object(pobj)) && (query_wiz_level(wiz)))
	    lfile2 = "/d/" + domain_object(pobj) + "/common/errors.move.wiz";
	else
	    lfile2 = 0;
    }

    if ((!pl) && (this_player()) && (this_player()->query_wiz_level()))
	pl = this_player();

    if (!pl)
	pl = find_someone(wiz);	/* Tell someone else if wiz not logged in */

    /*
     * Find the name of the player or object that tried to move
     */
    if (!this_player())
	player = "(NULL,Prev: " + file_name(pobj) + ")";
    else
	player = capitalize((string) this_player()->query_real_name()) + " (Level: " +
	    (int) this_player()->query_average() + ")";

    /*
     * Construct error message
     */
    emsg = " Player: " + player + ", from:\n (" + file_name(from);
    if (from != pobj)
	emsg += ":by:" + file_name(pobj);
    emsg += ") " + verb + " to (" + efile + ")";
    gdriverror = (string)LOAD_ERR(efile);
    if (!gdriverror)
    {
	gdriverror = " In reset(): " + erl;
    }
    else
	gdriverror = "Can't load object: " + erl;

    /*
     * Tell the player that he encountered an error
     */
    if ((this_player()) && (pl != this_player()))
    {
	write("** Error **\n");
	write("Due to a slight mistake in this Creation you can't move there.\n");
	write("The creator responsible has been notified of this and will fix it.\n");
    }

    /*
     * Log the error in three files: wizname.room domainname.room and
     * room.ERRORS
     */
    if ((pl) && (pl->err_report(wiz, 0)))
	player = "[Told: " + capitalize((string) pl->query_real_name()) + "]";
    else
	player = "[LOGONLY]";

    if (lfile1)
	write_file(lfile1, player + ctime(time()) + " " + emsg +
	     "\nErr: " + gdriverror + "\n");
    
    if (lfile2)
	write_file(lfile2, player + ctime(time()) + " " + emsg +
		   "\nErr: " + gdriverror + "\n");

    log_file("Move_errors", player + " " + ctime(time()) + " " + emsg +
	     "\nErr: " + gdriverror + "\n");

    /*
     * Tell the wizard he has a bug in his code, or tell someone else.
     */
    if (pl)
    {
	if (wiz == (string)pl->query_real_name())
	    wiz = "your";
	else if (pl == this_player())
	    wiz = capitalize(wiz + "'s");
	else
	{
	    wiz = capitalize(wiz + "'s");
	    pl->err_report(wiz, "The below wizard is not logged in, you get it this report in stead:\n");
	}
	pl->err_report(wiz, "\nError in " + wiz + " room files, the move was:\n");
	pl->err_report(wiz, emsg + "\n");
	pl->err_report(wiz, "The error given by the Game Driver was:\n" + gdriverror + "\n");
    }
}

/* 
   Find someone else to tell the error to:
   1) The domain lord
   2) Someone else in the domain
   3) Mage / Arch
   4) Another domainlord
*/
static object
find_someone(string wiz)
{
    object          apa;
    object          *bepa;
    string          dom,
                    dlord;

    dom = query_wiz_dom(wiz);	/* Find the domain of the wizard */
    dlord = query_domain_lord(dom);

    apa = find_player(dlord);
    if (apa->err_report("other", 0))
	return apa;

    bepa = filter(users(), "qf_domain", this_object(), dom);
    if (bepa)
	return bepa[random(sizeof(bepa))];

    bepa = filter(users(), "qf_arch", this_object());
    if (bepa)
	return bepa[random(sizeof(bepa))];

    bepa = filter(users(), "qf_lord", this_object());
    if (bepa)
	return bepa[random(sizeof(bepa))];
    return 0;
}

static int
qf_domain(object ob, string dom)
{
    if (query_wiz_dom(ob->query_real_name()) != dom)
	return 0;
    if (ob->err_report("other", 0))
	return 1;
    return 0;
}

static int
qf_arch(object ob)
{
    if (query_wiz_rank(ob->query_real_name()) < WIZ_MAGE)
	return 0;
    if (ob->err_report("other", 0))
	return 1;
    return 0;
}

static int
qf_lord(object ob)
{
    if (query_wiz_rank(ob->query_wiz_name()) < WIZ_LORD)
	return 0;
    if (ob->err_report("other", 0))
	return 1;
    return 0;
}

static object
find_admin()
{
    object *apa;

    apa = filter(users(), "qf_admin", this_object());
    if (apa)
	return apa[random(sizeof(apa))];
    return 0;
}

static int
qf_admin(object ob)
{
    if (query_wiz_rank(ob->query_real_name()) < WIZ_ARCH)
	return 0;
    if (ob->err_report("other", 0))
	return 1;
    return 0;
}

int
rem_def_start_loc(string str)
{
    if (!def_locations)
        def_locations = STARTING_PLACES;

    if (WIZ_TYPE(MYLEV) < WIZ_ARCH)
    {
        write("Only arches or keepers may remove starting locations.\n");
        return 1;
    }

    set_auth(this_object(), "#:root");
    while (member_array(str, def_locations) >= 0) /* Delete  */
        def_locations = def_locations - ({ str });

    save_object(SAVEFILE);
}

int
add_def_start_loc(string str)
{
    if (!def_locations)
	def_locations = STARTING_PLACES;
    
    if (WIZ_TYPE(MYLEV) < WIZ_ARCH)
    {
	write("Only arches or keepers may add starting locations.\n");
	return 1;
    }
    
    set_auth(this_object(), "#:root");
    if (file_size(str + ".c") < 0)
    {
	write("No such file: " + str + "\n");
	return 1;
    }
    while (member_array(str, def_locations) >= 0) /* Delete copies */
	def_locations = def_locations - ({ str });

    def_locations = def_locations + ({ str });
    save_object(SAVEFILE);
}

int
rem_temp_start_loc(string str)
{
    if (!temp_locations)
        temp_locations = TEMP_STARTING_PLACES;

    if (WIZ_TYPE(MYLEV) < WIZ_ARCH)
    {
        write("Only arches or keepers may remove starting locations.\n");
        return 1;
    }
    set_auth(this_object(), "#:root");
    while (member_array(str, temp_locations) >= 0) /* Delete copies */
        temp_locations = temp_locations - ({ str });

    save_object(SAVEFILE);
}

int
add_temp_start_loc(string str)
{
    if(!temp_locations)
	temp_locations = TEMP_STARTING_PLACES;
    
    if (WIZ_TYPE(MYLEV) < WIZ_ARCH)
    {
	write("Only arches or keepers may add starting locations.\n");
	return 1;
    }
    set_auth(this_object(), "#:root");
    if (file_size(str + ".c") < 0)
    {
	write("No such file: " + str + "\n");
	return 1;
    }
    while (member_array(str, temp_locations) >= 0) /* Delete copies */
	temp_locations = temp_locations - ({ str });

    temp_locations = temp_locations + ({ str });
    save_object(SAVEFILE);
}

public string *
query_list_def_start()
{
    if (SECURE_ARRAYS)
	return slice_array(def_locations,0,sizeof(def_locations));
    else
	return def_locations;
}

public string *
query_list_temp_start()
{
    if (SECURE_ARRAYS)
	return slice_array(temp_locations,0,sizeof(temp_locations));
    else
	return temp_locations;
}

int
check_temp_start_loc(string str)
{
    return member_array(str, temp_locations);
}

int
check_def_start_loc(string str)
{
    if (!def_locations)
	def_locations = STARTING_PLACES;
    return member_array(str, def_locations);
}

void
log_syslog(string file, string text)
{
    string fname;

    fname = calling_program();

    if(fname[0..5] != "secure" &&
       fname[0..3] != "cmd/" &&
       fname[0..9] != "std/living")
	return;
    set_auth(this_object(), "#:root");
    log_file(file, text);
}

void
log_public(string file, string text)
{
    int fsize, msize;
    string fname;

    fname = calling_program();

    file = OPEN_LOG_DIR + "/" + file;
    
    if(fname[0..5] != "secure" &&
       fname[0..9] != "std/living")
	return;

#ifdef CYCLIC_LOG_SIZE
    fsize = file_size(file);
    msize = CYCLIC_LOG_SIZE["root"];

    if (msize > 0 && fsize > msize)
	rename(file, file + ".old");
#endif /* CYCLIC_LOG_SIZE */

    set_auth(this_object(), "#:root");
    write_file(file, text);
}

/*
 * Function name:   exist_player
 * Description:     Checks if a player exist or not
 * Arguments:	    pl_name: Name of player
 * Returns:         True if player exist.
 */

int
exist_player(string pl_name)
{
    object ob;
    int ret;

    if (!pl_name)
	return 0;
    
    set_auth(this_object(), "#:root");
    return file_size("/players/" + extract(pl_name, 0, 0) +
		     "/" + pl_name + ".o") >= 0;
}

/*
 * Function name:   finger_player
 * Description:     Returns a player object restored with the values from
 *		    the players save file.
 * Arguments:	    pl_name: Name of player
 *		    file: (optional) Name of player_file
 * Returns:         The restored player object or 
 */
varargs object
finger_player(string pl_name, string file)
{
    object ob;
    int ret, lev;
    string f;

    if (strlen(pl_name) == 0)
	return 0;

    if (!file)
	file = FINGER_PLAYER;

    set_auth(this_object(), "#:backbone");
    ob = clone_object(file);

    f = function_exists("load_player", ob);
    if (f !=  "/std/player_sec" && f != FINGER_PLAYER)
    {
	do_debug("destroy", ob);
	return 0;
    }

    ob->master_set_name(pl_name);
    ob->open_player();               /* sets euid == 0 */
    set_auth(this_object(), "#:root");
    export_uid(ob);
    ret = ob->load_player(pl_name);

    set_auth(this_object(), "#:backbone");
    export_uid(ob);			/* Make the object powerless */
    ob->set_trusted(1);
    set_auth(this_object(), "#:root");
    ob->set_adj(0);			/* Set the adjectives correctly */

    lev = query_wiz_level(pl_name);
    if (lev)
	ob->set_wiz_level(lev);

    if (ret)
	return ob;
    else
    {
	ob->remove_object();
	return 0;
    }
}

/*
 * Function name:   note_something
 * Description:     Handle all types of logfiles and write them in the
 *		    correct directories.
 * Arguments:	    str:	The string to log
 *		    file_end:	The filename
 *		    id:		The log id
 *		    env:	The environment of this_player()
 */
void
note_something(string str, string file_end, int id, object env)
{
    string cr, file;

    if (id == LOG_SYSBUG_ID)
    {
	set_auth(this_object(), "#:root");
	log_file("SYSBUGS", extract(ctime(time()), 4, 9) + " "
	       + file_name(env)
	       + " (" + capitalize((string) this_player()->query_real_name())
	       + ")\n" + str + "\n", -1);
	return;
    }

    if (id == LOG_DONE_ID)
	cr = this_player()->query_real_name();
    else
	cr = creator_object(env);

    file = query_wiz_path(cr) + "/log";

    if (!file)
	return;

    set_auth(this_object(), "#:root");

    if (file_size(file) != -2)
	mkdir(file);

    if (id == LOG_DONE_ID)
    {
	write_file(file + file_end, ctime(time()) + ":\n" +
	           str + "\n");
    }
    else
    {
	write_file(file + file_end, extract(ctime(time()), 4, 9) + " " +
		   file_name(env) + " (" +
	           capitalize((string) this_player()->query_real_name()) +
	           ")\n" + str + "\n");
    }
}

/*
 * Function name:   query_snoop
 * Description:     Tells caller if a user is snooped.
 * Arguments:	    snoopee: pointer to a user object
 * Returns:         0 if not snooped, 1 if snooped and caller is lord or lower
 *                  object pointer to snooper if caller is arch or higher
 */
mixed
query_snoop(object snoopee)
{
    object snooper;
    int type = GETTYPE;

    if (type >= WIZ_ARCH)
	return efun::query_snoop(snoopee);
    else if (check_snoop_validity(previous_object(), snoopee, 1) &&
		(snooper = (efun::query_snoop(snoopee))) &&
		(type >= query_wiz_rank(snooper->query_real_name())))
	return 1;
    else
	return 0;
}

/*
 * Function name:   query_start_time
 * Description:     Return the time when the game started.
 */
public int
query_start_time()
{
    int theport;
    string game_start;

    theport = debug("mud_port");
    if (theport != 0)
    {
	game_start = GAME_START + "." + theport;
	if (file_size(game_start) > 0)
	    return file_time(game_start);
    }

    return object_time(this_object()); /* Wrong if master updated */
}

/*
 * Function name: commune_log
 * Description  : Logs a commune from a mortal
 * Arguments    : string str  - the message.
 */
public void
commune_log(string str)
{
    log_public("COMMUNE", sprintf("%s: %-11s: %s", ctime(time()),
	this_interactive()->query_real_name(), str));
}

/*
 * Function name: master_shutdown
 * Description  : Perform the final shutdown. This function may only be
 *                called from the armageddon object.
 * Returns      : 1 - Ok, 0 - No shutdown performed.
 */
public int
master_shutdown(string reason)
{
    if (MASTER_OB(previous_object()) != ARMAGEDDON)
    {
	return 0;
    }

#ifdef LOG_SHUTDOWN
    log_file(LOG_SHUTDOWN, ctime(time()) + " " + reason, -1);
#endif LOG_SHUTDOWN
    
    /* This MUST be a this_object()->
       If it is removed the game wont go down, so hands off!
    */
    this_object()->do_debug("shutdown");
    return 1;
}

/*
 * Function name: request_shutdown
 * Description  : When a wizard wants to shut down the game, this
 *                function is called to invoke Armageddon. The function
 *                should be called from the shutdown command in
 *                WIZ_CMD_NORMAL.
 * Arguments    : string reason - the reason to shut down the game.
 *                int    delay  - the delay in minutes.
 */
public void
request_shutdown(string reason, int delay)
{
    string euid    = getwho();
    string shutter = ARMAGEDDON->query_shutter();

    if (strlen(shutter))
    {
	write("Game is already being shut down by " + shutter + ".\n");
	return;
    }

    if (query_wiz_rank(euid) < WIZ_NORMAL)
    {
	write("Illegal euid. Shutdown rejected.\n");
	return;
    }

    if (!strlen(reason))
    {
	write("No reason for shutdown. Shutdown rejected.\n");
	return;
    }

    if (reason == "memory_failure")
    {
	/* Arches and keepers can force a memory failure every time. Other
	 * wizards can only do so if the memory usage is >= 99%.
	 */
	if ((query_wiz_rank(euid) < WIZ_ARCH) &&
	    (query_memory_percentage() < 99))
	{
	    write("There is no reason to ask for a memory_failure yet.\n");
	    return;
	}

	memory_failure();
	return;
    }

    ARMAGEDDON->start_shutdown(reason, delay, euid);
}

/*
 * Function name: calcel_shutdown
 * Description  : When the wizard has second thoughts and does not want
 *                to shut the game down after all, this function is
 *                called. The function should be called from
 *                WIZ_CMD_NORMAL.
 */
public void
cancel_shutdown()
{
    string euid    = getwho();
    string shutter = ARMAGEDDON->query_shutter();
    int    rank    = query_wiz_rank(euid);

    if (mem_fail_flag)
    {
	write("Game is shutting down due to insufficient memory. Cancel " +
	    "is not possible.\n");
	return;
    }

    if (rank <= WIZ_RETIRED)
    {
	write("Illegal euid. Cancel shutdown rejected.\n");
	return;
    }

    if ((euid != shutter) &&
	(rank <= WIZ_LORD))
    {
	write("You are not allowed to cancel a shutdown by " +
	    shutter + ".\n");
	return;
    }

    ARMAGEDDON->cancel_shutdown(euid);
}
/*
 * Function name:  wiz_home
 * Description:    Gives a default 'home' for a wizard, domain or a player
 * Arguments:      wiz: The wizard name.
 * Returns:        A filename for the 'home' room.
 */
string
wiz_home(string wiz)
{
    string path;

    if (query_wiz_rank(wiz) == WIZ_MORTAL)
	if (query_domain_number(wiz) < 0)	/* Not even a domain */
	    return "";

    path = query_wiz_path(wiz) + "/workroom.c";
    set_auth(this_object(), "#:root");
    if (file_size(path) <= 0)
	write_file(path, "inherit \"/std/workroom\";\n\ncreate_workroom()\n{\n  ::create_workroom();\n}\n");

    return path;
}

/*
 * Function name:  wiz_force_check
 * Description:    Checks if one wizard is allowed to force another
 * Arguments:      forcer: Name of wizard trying to force
 *		   forced: Name of wizard being forced
 * Returns:        True if ok
 */
int
wiz_force_check(string forcer, string forced)
{
    int             rlev,
                    dlev;
    if (forcer == forced)
	return 1;

    rlev = query_wiz_rank(forcer);
    if ((rlev == WIZ_KEEPER) || (forcer == ROOT_UID))
	return 1;

    dlev = query_wiz_rank(forced);

    if ((rlev >= WIZ_ARCH) && (dlev <= WIZ_LORD))
	return 1;

    return 0;
}

/*
 * Function name: set_sanctioned
 * Description:   Set the 'sanctioned' field in the player.
 * Arguments:     wizname - The wizard to set in
 *		  map - The 'sanctioned' map to set.
 */
public int
set_sanctioned(string wizname, mapping map)
{
    string wname;
    object wiz;

    wname = geteuid(previous_object());

    if ((wname != wizname) && (query_wiz_rank(wname) < WIZ_ARCH))
	return 0;

    wiz = find_player(wizname);
    if (!wiz)
	return 0;

    wiz->set_sanctioned(map);
    return 1;
}

/*
 * Function name: banish
 * Description:   Banish a name, info about name, remove a banishment.
 * Arguments:     name - the name to perform banish operation on.
 *		  what - what to do.
 * Returns:       A list with information.
 */
mixed *
banish(string name, int what)
{
    string file;
    mixed *info;

    info = allocate(2);
    
    if (function_exists("get_soul_id", previous_object()) !=  
	 "/cmd/wiz_cmd_normal")
	return ({});

    file = "/syslog/banish/" + extract(name, 0, 0) + "/" + name;
    
    if (file_size(file) > -1)
    {
	info[0] = read_file(file);
	info[1] = file_time(file);
    }

    switch (what)
    {
    case 0: /* Information */
	if (file_size(file) > -1)
	    return info;
	break;

    case 1: /* Remove */
	if (file_size(file) > -1)
	{
	    rm(file);
	    return info;
	}
	break;

    case 2: /* Add */
	if (file_size(file) > -1)
	    return info;
	write_file(file, geteuid(previous_object()));
	break;

    default: /* Strange */
	break;
    }

    return ({});
}

#define DEBUG_RESTRICTED ({ "mudstatus", "swap", "shutdown", "send_udp" })
/*
 * Function name:  do_debug
 * Description:    Does a lot of debug things
 * Arguments:      icmd: Command
 * Returns:        information relevant to given command
 */
varargs mixed
do_debug(string icmd, mixed a1, mixed a2, mixed a3)
{
    if (member_array(icmd, DEBUG_RESTRICTED) >= 0)
    {
	if (geteuid(previous_object()) != ROOT_UID &&
	    previous_object() != this_object() &&
	    previous_object() != simul_efun_ob &&
	    previous_object() != find_object(WIZ_CMD_ARCH) &&
	    previous_object() != find_object(WIZ_CMD_KEEPER))
	    return 0;
    }

    return debug(icmd, a1, a2, a3);
}

/*
 * Function name: no_trans_of_mudlib
 * Description  : This function can set the notrans flag of a wizard to
 *                indicate that he/she would not like to see the mudlib
 *                transed for he/she is working on some part that is not
 *                finished at the moment.
 * Arguments    : the command line argument
 * Returns      : string - the result of the operation.
 */
string
no_trans_of_mudlib(string str)
{
    string cmder = getwho();
    string *list;
    int    i;

    if (!strlen(cmder))
        return "You are not allowed to do this.";

    if (!mappingp(notrans_map))
        notrans_map = ([ ]);

    if (str == "on")
    {
        if (notrans_map[cmder])
            return "You already set the notrans flag.";

        notrans_map[cmder] = time();
        save_master();
        return "Ok. Set your notrans flag.";
    }

    if ((str == "off") || (str == "remove"))
    {
        if (!notrans_map[cmder])
            return "You have not set the notrans flag.";

        notrans_map = m_delete(notrans_map, cmder);
        save_master();
        return "Ok. Removed your notrans flag.";
    }

    if ((strlen(str)) &&
        (sizeof(list = explode(str, " ")) == 2) &&
        (list[0] == "remove"))
    {
        if (query_wiz_rank(cmder) < WIZ_ARCH)
            return "You are not allowed to remove someones notrans flag.";

        list[1] = lower_case(list[1]);
        if (!notrans_map[list[1]])
            return "Wizard \"" + capitalize(list[1]) +
                "\" has not set a notrans flag.";

        notrans_map = m_delete(notrans_map, list[1]);
        save_master();
        return "Removed notrans flag of \"" + capitalize(list[1]) + "\".";
    }

    if (strlen(str))
        return "Syntax: notrans [on] / [off] / [remove [wizname]]";

    if (!m_sizeof(notrans_map))
        return "No wizard has set the notrans flag.";

    list = m_indices(notrans_map);

    write("The following wizards have set the notrans flag:\n");

    for (i = 0; i < sizeof(list); i++)
        write(sprintf("%-12s  %1s\n", capitalize(list[i]),
            ctime(notrans_map[list[i]])));

    /* No reason to return something here. You already have the list. */
    return "";
}

/*
 * Function name:   send_udp_message
 * Description:     Sends a udp message to arbitrary host, port
 * Arguments:	    to_host: Hostname or IP-number
 *		    to_port: Portnumber
 *		    msg:     Message to send
 * Returns:	    True if the message is sent. There is of course no
 *		    guarantee it will be received.
 */
int
send_udp_message(string to_host, int to_port, string msg)
{
    if (stringp(udp_manager) && 
	previous_object() == find_object(udp_manager))
	return debug("send_udp", to_host, to_port, msg);
    else
	return 0;
}

/*
 * Function name:  check_memory
 * Description:    Checks with 'debug malloc' if it is time to reboot
 * Arguments:      dodecay - decay xp or nto.
 *		   The limit can be defined in config.h as MEMORY_LIMIT
 */
public void
check_memory(int dodecay)
{
    int    f;
    string foobar;

    if (dodecay == 1)
    {
	memory_check_alarm =
	    set_alarm(MEMORY_CHECK_TIME, 0.0, "check_memory", 1);
    }

    /* Is the game too big? */
    if (query_memory_percentage() >= 100)
    {
	memory_failure();
    }

    /* Is it time for a regular reboot?
       Must have been up one hour to reboot
    */
#ifdef REGULAR_REBOOT
    if ((time() - query_start_time()) > 3600)
    {
	sscanf(ctime(time()), "%s %s %d %d:%d:%d %d",
	    foobar, foobar, f, h, f, f, f);

	if (h == REGULAR_REBOOT) 
	{
	    set_auth(this_object(), "root:root");
	    ARMAGEDDON->start_shutdown("It is past " + REGULAR_REBOOT +
		":00, which is our dayly reboot time!", 5, ROOT_UID);
	}
    }
#endif

    /* We should add a decay here for the xp stored for each domain
       we should also save the master object here
    */
    if (dodecay == 1)
    {
	decay_exp();
	set_auth(this_object(), "#:root");
	save_object(SAVEFILE);
    }
}
    

/*
 * Function name:  startup_udp
 * Description:    Give the contents of the package to send as startup
 *		   message to the mudlist server. This is default if we
 *		   have no UDP_MANAGER.
 * Returns:        The message.
 */
string 
startup_udp()
{
    return 
	"||NAME:" + this_object()->get_mud_name() +
	"||VERSION:" + do_debug("version") +
	"||MUDLIB:" + MUDLIB_VERSION +
	"||HOST:" + query_host_name() +
	"||PORT:" + debug("mud_port") +
	"||PORTUDP:" + debug("udp_port") +
	"||TIME:" + ctime(time());
}

/*
 * Function name:  set_known_muds
 * Description:    The UDP manager can set what muds are known.
 * Returns:	   True if set.
 */
int
set_known_muds(mapping m)
{
    if (stringp(udp_manager) &&
	previous_object() == find_object(udp_manager))
    {
	known_muds = m;
	set_auth(this_object(), "#:root");
	save_object(SAVEFILE); 
	return 1;
    }
    return 0;
}

/*
 * Function name:  query_known_muds
 * Description:    Give the currently known muds
 * Returns:        A mapping of information indexed with mudnames
 */
mapping
query_known_muds()
{
    if (mappingp(known_muds))
	return known_muds + ([]);
    else
	return 0;
}

/*
 * Function name:  
 * Description:    
 * Arguments:      
 * Returns:        
 */
