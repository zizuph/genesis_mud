/*
 * spell_list.c
 *
 * This is the base cmdsoul which takes care of the different spells.
 * You can think of a spell list as a collection of magical spells
 * ordered for specific purposes. 
 *
 * Note that we have to be careful with this file, since it is a soul.
 * We can not have data specific for a player in this file, simply 
 * because the soul is shared by all members of the spellcasting guild.
 *
 * Revision 1, Aug 3, 1994.
 *   I want more data in this file!
 *    - Name of spells.
 *    - Classes. 
 *    - Power.
 *   This is due to being able to call the spells from
 *   other things than this soul.        
 *
 * Sir Rogon.
 *
 * Revision 2, Dec 28, 1994.
 *   - Moved this file to /d/Shire/imladris/lib/spell_list.c
 *   - Made a whole lot of new comments for Dunstable and Odin.
 *   - Introduced some macros to handle the delicious data 
 *     structure 'spell_list_data'.     
 * 
 * Sir Rogon.
 */

#include "defs.h"

inherit "/cmd/std/command_driver";
inherit EXTRA_FILE;
inherit TELLEM_FILE;
inherit "/d/Shire/common/lib/special"; /* FindCallOut */

#include "/secure/std.h"
#include <tasks.h>
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <stdproperties.h>

static	string spell_list_name;
static	string spell_list_short; 
static	string spell_list_realm;
static	string spell_list_short_name;

static	mapping spell_list_data;  
/*           
 * spell_list_data format: 
 *
 *  spell_list_data[spell]              == SPLD(spell)              == array (size 2):
 *  spell_list_data[spell][0]           == SPLD_FILENAME(spell)     == string.
 *  spell_list_data[spell][1]           == CLD(spell)               == mapping of classes.
 *  spell_list_data[spell][1][class]    == SPLD_DATA(spell, class)  == array (size 2)
 *  spell_list_data[spell][1][class][0] == SPLD_MANA(spell, class)  == int.
 *  spell_list_data[spell][1][class][1] == SPLD_LEVEL(spell, class) == int.
 *
 * spell_list_data = ([
 *   "spell1" : ({ "/filepath/filename1", ([ 1 : ({ 210, 4 }), 
 *                                           5 : ({ 340, 10 }) ]) }),
 *   "spell2" : ({ "/filepath/filename2", ([ 3 : ({ 260, 5 }) ]) })
 * ]);
 *
 * Example: We want the spell Alka in classes I, II, III, V and X.
 *      Alka I at level 3, mana used 60.
 *      Alka II at level 7, mana used 120.
 *      Alka III at level 12, mana used 180.
 *      Alka V at level 15, mana used 240.
 *      Alka X at level 25, mana used 300. 
 *   The resulting spell_list_data will be:
 *   spell_list_data = ([
 *     "alka" : ({ "/d/Shire/Imladris/spell/lw/alka", 
 *                 ([ 1: ({ 60, 3 }), 2: ({ 120, 7 }), 3: ({ 180, 12 }), 
 *                    5: ({ 240, 15 }), 10: ({ 300, 25 }) ]) 
 *              }),
 *     ...
 *   ]);
 *   Note that now will 
 *     spell_list_data["alka"][1][10][1] = SPLD_LEVEL("alka", 10) = 25.
 *
 * To easen up this horrible structure, the following macros.
 * SPLD = "Spell list data". CLD = "Class data".
 */

/* The spell's data.                     */
#define SPLD(spell)                      spell_list_data[spell]
				
/* The filename of a spell.              */
#define SPLD_FILENAME(spell)             SPLD(spell)[0]

/* The extra class data of a spell.      */
#define CLD(spell)                       SPLD(spell)[1]

/* The specific data for a spell.        */
#define SPLD_DATA(spell, class)          CLD(spell)[class]

/* The mana required for a spell.        */
#define SPLD_MANA(spell, class)          SPLD_DATA(spell, class)[0]

/* The required spell level for a spell. */
#define SPLD_LEVEL(spell, class)         SPLD_DATA(spell, class)[1]

/* The spell's list of classes.          */
#define SPLD_CLASSES(spell)              m_indexes(CLD(spell))

/* Is this a spell?                      */
#define IS_SPELL(spell)                  sizeof(SPLD(spell))

/* Is there a spell at this class?       */
#define IS_SPELL_AT_CLASS(spell, class)  sizeof(SPLD_DATA(spell, class))

/* DEB() is used for debugging purposes. */
#ifdef DEBUGGING 
# define DEB(x) if(TP->query_real_name()=="rogon") write("#splist.c#" + x)
#endif


/***************************************************************************
 *
 * Parts needed for a cmdsoul.
 *
 ***************************************************************************/

/*
 * is_spell_list - To identify that this is a spell list.
 */
int 
is_spell_list() 
{ 
    return 1; 
}

void 
init_list() 
{	
    spell_list_data = ([]);
}

string 
get_soul_id() 
{
    seteuid(getuid());
    if (!strlen(spell_list_name))
	return "A Spell List";
    else
	return spell_list_name + " Spell List";
}

/* This soul is auto_loading */
string
query_auto_load()
{
    seteuid(getuid());
    return MASTER_OB(TO);
}

void
using_soul(object live)
{
    seteuid(getuid());
    init_list();
}

int 
query_cmd_soul() 
{ 
    return 1; 
}

int
id(string str)
{
    str = lower_case(str);
    return str==spell_list_short ||
	   str=="list" ||
	   str==spell_list_name ||
	   str==spell_list_realm;
}

/*
 * wrap_to_command(value) is used to map the spell_list_data structure into
 * a cmdlist structure. See query_cmdlist().
 */
string
wrap_to_command(string value)
{
    return "do_spell";
}

/*
 * Function name:  query_cmdlist
 * Description:    This function should return a cmdlist. 
 *                 All spells are pointed at "do_spell"
 *                 in this file.
 */
mapping
query_cmdlist()
{
    mapping cmds = ([]);

    if (m_sizeof(spell_list_data)) 
	cmds += map(spell_list_data, "wrap_to_command", this_object());
    
    seteuid(getuid());
    if (spell_list_short)
	cmds += ([ spell_list_short: "list_me"]);
    
    cmds += ([
	"cast"  : "do_spell",
	"deb"   : "do_deb",
	"mana"  : "do_mana",
	"sinfo" : "do_sinfo"
	]);

    return cmds;
}

/***************************************************************************
 *
 * The following part consists of set_XXX and query_XXX functions for
 * accessing data in the spell list, except for the spells themselves.  
 *
 ***************************************************************************/

void set_realm(string realm)          { spell_list_realm = realm; }
void set_list_name(string name)       { spell_list_name = name; }
void set_list_short(string name)      { spell_list_short = name; }
void set_list_short_name(string name) { spell_list_short_name = name; }

string  query_realm()           { return spell_list_realm; }
string  query_list_name()       { return spell_list_name; }
string  query_list_short()      { return spell_list_short; }
string  query_list_short_name() { return spell_list_short_name; }
mapping query_spell_list_data() { return spell_list_data; }


/***************************************************************************
 *
 * Here comes the special functions to make life easier for the one 
 * programming a list of spells. These functions define an interface
 * to the spell list specific parts of this file.
 *
 ***************************************************************************/

/*
 * Function name: add_spell
 * Description:   Add the spell to the list of active spells.
 * Arguments:	  verb	 - The activating verb string.
 *		  file	 - The file name for this spell.
 */
int
add_spell(string spell_verb, string file, mapping classes)
{
    if (spell_list_data[spell_verb])
	return 0;

    spell_list_data[spell_verb] = ({ file, classes });
    update_commands();  /* Reload command list. */
}

/*
 * Function:	add_spell_file(string file, string spell_name)
 * Description: If spell_name is not set, the system assumes
 *	        that it is in the property SPELL_S_NAME of the file.
 * Note:        !!! OBSOLETE !!!
 *              You should provide class info in the spell list now.
 */
varargs int
add_spell_file(string file, string spell_name, mapping classes = ([]))
{
    if (!stringp(spell_name)) 
    {
	FIXEUID;
	if (!stringp(file) || catch(file->load_me()))
	    return 0;
	spell_name = file->query_prop(SPELL_S_NAME);
    }

    if (stringp(spell_name))
	return add_spell(spell_name, file, classes);
    else
	return 0;
}

/*
 * The L_ is for the setup_list() function. 
 */
#define L_LEVEL 0
#define L_VERB  1
#define L_CLASS 2
#define L_MANA  3

void
map_setup(mixed elem)
{
    CLD(elem[L_VERB]) += ([ elem[L_CLASS] : ({ elem[L_MANA] , elem[L_LEVEL] }) ]);
}

/*
 * Function name: setup_list
 * Description:   This important function sets up vital information.
 *                Each spell may come in several versions, called
 *                classes. A (spell, class) combination is one 
 *                spell. The format for the the call is
 *
 *                setup_list( ({ lvl, name, class, mana }),
 *                            ({ lvl, name, class, mana }),
 *                            :
 *                            : 
 *                            ({ lvl, name, class, mana }) );
 * 
 * Note:          A class == 0 means that the spell is single,
 *                i.e. comes in no separate classes.
 */
varargs void
setup_list(mixed elem1, ...)
{
    map( ({ elem1 }) + argv, "map_setup", this_object());
}

/*
 * Function name: remove_spell
 * Description:   Remove the spell with the given verb string.
 * Arguments:	  name - The name of the spell to remove.
 */
int
remove_spell(string spell_name)
{
    spell_list_data = m_delete(spell_list_data, spell_name);
    update_commands();
    return 1;
}

#ifdef DEBUGGING
int
do_deb(string str)
{
    int i;

    if (!TP->query_wiz_level())
	return 0;

    if (!strlen(str))
	return 0;
    
    if (!id(str))
	return notify_fail("Which spell list?\n");
    
    write(sprintf("%O\n", spell_list_data)); 
    return 1;
}
#endif

/***************************************************************************
 *
 * Here comes the special functions to make life easier for the one 
 * programming a list of spells. These functions define an interface
 * to the spell list specific parts of the file.
 *
 ***************************************************************************/

/*
 * Function name:  spells_at_level
 * Arguments:      int lvl
 * Description:    This support function returns a list of all spells 
 *                 at spell level 'lvl'.
 * Returns:        The list where each element is a ({ name, class }) 
 *                 combination.
 */
mixed
spells_at_level(int lvl)
{
    mixed spells = m_indexes(spell_list_data);
    mixed classes;
    mixed ret = ({});
    int i, j, sz;

    for (i=0, sz = sizeof(spells); i<sz; i++)
    {
	classes = SPLD_CLASSES(spells[i]);
	if (!classes)
	    ret += ({ ({ spells[i], 0 }) });
	else
	    for (j=0; j<sizeof(classes); j++) 
		if (SPLD_LEVEL(spells[i], classes[j]) == lvl)
		    ret += ({ ({ spells[i], classes[j] }) });
    }
    return ret;
}

/*
 * Function name:  quenya_name
 * Arguments:      string verb  - The spell name.
 *                 int class    - The spell's class.
 * Returns:        A string of the name for a spell in Quenya.
 * Example:        queny_name("rilme", 1) == "rilme etta"
 */
string
quenya_name(string verb, int class)
{
    if (sizeof(SPLD_CLASSES(verb)) == 1)
	return verb;
    else
	return sprintf("%s %s", verb, num2quenya(class));
}

/*
 * Function name:  quenya_name_ext
 * Arguments:      string verb  - The spell name.
 *                 int class    - The spell's class.
 * Returns:        Extended output of a Quenya name for use
 *                 in the listing of spells.
 */
string
quenya_name_ext(string verb, int class)
{
    string qname = quenya_name(verb, class);

    if (class)
	return sprintf("%-14s (%s)", qname, CAP(roman_str(class)));
    else
	return qname;
}

/* 
 * Function name:  list_me
 * Description:    Writes out a nice print of the spells in this
 *                 spell list. 
 */
int
list_me() 
{
    mixed spells;
    int i, j, do_sep;
    string spell_name;

    write("Spell list: " + spell_list_name + " [" + spell_list_short + "]\n");
    write("Of " + CAP(spell_list_realm) + "\n");
    write("-------------------------------\n");

    for (i = 1, do_sep = 0; i <= level(TP) && i <= 30; i++)
    {
	if (do_sep && i%5 == 1) {
	    write("- - - - - - - - - - - - - - - -\n");
	    do_sep = 0;
	}

	spells = spells_at_level(i);

	if (!sizeof(spells))
	    continue;
	
	for (j=0; j<sizeof(spells); j++) 
	{
	    spell_name = CAP(quenya_name_ext(spells[j][0], spells[j][1]));

	    if (j==0)
		write(sprintf("%3d. %s\n", i, spell_name));
	    else
		write(sprintf("%3s  %s\n", " ", spell_name));
	    do_sep = 1;
	}
    }
    write("-------------------------------\n");
    return 1;
}

/*
 * Parses str -> 'verb' 'class' 'args'
 */
mixed
parse_spell(string str)
{
    string spell;
    string *expl;
    int class, sz;
    mixed classes;
    string arg;

    DEB("parse_spell: start\n");
    if (!strlen(str))
	return 0;
    
    expl = explode(str, " ");
    sz = sizeof(expl);

    if (sz == 1) 
    {
	spell = str; 
	class = 0;
	arg = "";
    } 
    else 
    {
	spell = expl[0];
	class = class2num(expl[1]);
	if (!class) 
	    arg = implode(expl[1..sz-1], " ");
	else	
	    if (sz > 2) 
		arg = implode(expl[2..sz-1], " "); 
	    else                                          
		arg = "";                                 
    } 
    
    if (!IS_SPELL(spell)) 
	return 0;
        
    classes = SPLD_CLASSES(spell);
    
    if (!classes)
	return 0;
    
    if (class == 0) {
	if (sizeof(classes) == 1)
	    return ({ spell, classes[0], arg });
	else
	    return ({ spell, 1, arg });
    }
    return ({ spell, class, arg });    
}

/*
 * From now on we will use the above.
 * We define these macros:
 */

#define P_NAME(x)  (x[0])     /* Parsed spellname     */
#define P_CLASS(x) (x[1])     /* Parsed class         */ 
#define P_ARGS(x)  (x[2])     /* Additional arguments */

/*
 * Function name:  do_mana
 * Description:    This is the function called when the spellcaster
 *                 wants to know how much mana he has, or how much
 *                 mana a spell will cost him.
 */    
varargs int
do_mana(string str = "")
{
    int left, power;
    mixed parsed;

    notify_fail("There is no such spell '" + str + "'.\n");

    parsed = parse_spell(str);

    if (!parsed)
	return 0;

    power = SPLD_MANA(P_NAME(parsed), P_CLASS(parsed));

    if (TP->query_wiz_level())
	write("WIZINFO: " + power + " mana points.\n");

    write(sprintf("The '%s' spell would require %s of all your mana.\n",
		  quenya_name(P_NAME(parsed), P_CLASS(parsed)), 
		  ratio_str(power, TP->query_max_mana())));

    left = TP->query_mana() - power;

    if (left<0)
	write("You can not cast the spell, since you do not have that much mana.\n");
    else if (left == 0)
	write("You would loose all your mana in an attempt to cast it.\n");
    else
	write("You would have "+ratio_str(left, TP->query_max_mana())+
	      " mana left if you cast it successfully.\n");

    if (level(TP) < SPLD_LEVEL(P_NAME(parsed), P_CLASS(parsed)))
	write("NOTE: You can not cast this spell, since you are only a "+
	      num2order(level(TP))+" level spell caster, and the spell is at "+
	      "level "+ SPLD_LEVEL(P_NAME(parsed), P_CLASS(parsed))+".\n");
    return 1;
}

/* 
 * Function name:  do_sinfo
 * Description:    Displays spell information to the caster.
 */
varargs int
do_sinfo(string str = "")
{
    mapping classes;
    string *words;
    int     n, left;
    object  spell_obj;
    int     mana;
    int     normal_time;
    int     wanted_time;
    mixed   parsed;
    string  spell_name;
    int     req_level;
    int     power;

    parsed = parse_spell(str);
    if (!parsed)
	return notify_fail("Eh.. what spell?\n");

    /* Fix this, all data like this should be in the 
       spell_list.c file. Also, is really all this 
       information nescessary for mortal spellcasters? */

    spell_obj = find_object(SPLD_FILENAME(P_NAME(parsed)));
    spell_obj -> set_caster(TP);
    spell_obj -> set_spell_class(P_CLASS(parsed));

    normal_time = spell_obj->query_normal_casting_time();
    wanted_time = spell_obj->query_casting_time();

    spell_name = quenya_name(P_NAME(parsed), P_CLASS(parsed));
    req_level = SPLD_LEVEL(P_NAME(parsed), P_CLASS(parsed));
    power     = SPLD_MANA(P_NAME(parsed), P_CLASS(parsed));
    mana      = TP->query_mana();

    write(sprintf("===============================================================\n"
		  + "Spell name     : %s\n"
		  + "Spell list     : %s [%s]\n"
		  + "Realm of Power : Of %s\n"
		  + "---------------------------------------------------------------\n"
		  + "Spell level             : %d\n" 
		  + "Mana requirements       : %s\n"
		  + "Enough mana to cast     : %s\n"
		  + "Normal chanting time    : %d secs\n"
		  + "Current chanting time   : %d secs\n"
		  + "Difficulty to cast      : %s\n"
		  + "Syntax                  : cast %s %s\n"
		  + "---------------------------------------------------------------\n"
		  + "Description:\n%s\n" 
		  + "===============================================================\n",
		  CAP(spell_name),
		  CAP(spell_list_name), spell_list_short,
		  CAP(spell_list_realm), 
		  req_level,
		  ratio_str(power, mana),
		  (power > mana ? "No" : "Yes"),
		  normal_time,
		  wanted_time,
		  desc_diff(spell_obj->query_real_difficulty()),
		  P_NAME(parsed), spell_obj->query_prop(SPELL_S_SYNTAX),
		  spell_obj->query_prop(SPELL_S_DESC)));
    return 1;
}

/***************************************************************************
 *
 * Casting of Spells.
 *
 ***************************************************************************/

/*
 * Function name:   start_spell_msg
 * Arguments:	    arg - The arguments passed with the spell.
 * Description:     Handles the output given when the caster begins
 *		    to chant a spell.
 */
int
start_spell_msg(object spell, string spell_name)
{
    string mess, element, form;

    element = ELEMENT_NAME[spell->query_element()];
    form    = FORM_NAMES[spell->query_form()];

    write("You start singing an arcane hymn of Illuvatar.\n" +
	  "You sing: Hyarmen Eru Illuvatar tananda " + +"!\n"+
	  "You gain great wisdom in twisting the essence of " + 
	  element + ", forming "+ LANG_ADDART(form)+ " spell.\n");

    mess = " starts singing: Hyarmen Eru Illuvatar tananda " + 
	CAP(spell_name);

    say( ({ METNAME + mess + "!\n",
	    TART_NONMETNAME + mess + "!\n",
	    "Someone" + mess + "!\n" }) );

    return 1;
}

object
create_spell_obj(string spell_name, int class_wanted)
{
    string file = SPLD_FILENAME(spell_name);
    string caught;

    FIXEUID;

    if (caught = catch(spell_obj = clone_object(file)))
    {
	if (TP->query_wiz_level())
	    write("WIZINFO: "+caught+"\n");
	return 0;
    }
    if (!spell_obj) 
	return 0;

    spell_obj -> default_config_spell();
    spell_obj -> set_spell_mana(SPLD_MANA(spell_name, class_wanted));
    spell_obj -> set_spell_name(quenya_name(spell_name, class_wanted));

    spell_obj -> set_spell_verb(spell_name);
    spell_obj -> set_spell_class(class_wanted);

    return spell_obj;
}

/*
 * Function:    do_spell
 * Desc:	This is the starting point for all spells. This is called from
 *		the command driver when a spell caster wants to cast a spell.
 */
int 
do_spell(string str) 
{
    string mess;
    string *words;
    object spell_obj;
    mixed parsed;
    string verb;

    /* First check conflicts with other spell systems (Genesis spells.) */
    if (FindCallOut(TP, "cmdhooks_do_spell") > 0 ||
	TP->query_prop(LIVE_O_CONSENTRATES_SPELL))
	return notify_fail("You already consentrate on another spell!\n");

    verb = query_verb();

    notify_fail(CAP(verb) + "?\n");

    if (verb == "cast") 
    {
	notify_fail("Cast which spell?\n");
	parsed = parse_spell(str);
	if (!parsed)
	    return 0;
    } 
    else 
    {
	if (!strlen(str))
	    str = verb;
	else
	    str = verb + " " + str;
	parsed = parse_spell(str);
	if (!parsed)
	    return 0;
    }
    
    if (SPLD_LEVEL(P_NAME(parsed), P_CLASS(parsed)) > level(TP))
	return notify_fail("You are not allowed to cast this high level spell.\n");
    
    spell_obj = create_spell_obj(P_NAME(parsed), P_CLASS(parsed));
    
    if (!spell_obj) 
	return notify_fail("Conflicts in the fabric of space resulted " +
			   "in a premature collapse!\nYour spell failed to work!\n");
    
    start_spell_msg(spell_obj, quenya_name(spell_name, spell_class));        
    return spell_obj->cast_spell(P_ARGS(parsed));
}

#undef P_NAME
#undef P_CLASS
#undef P_ARGS


