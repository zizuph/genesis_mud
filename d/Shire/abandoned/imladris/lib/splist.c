/*
 * spell_list.c
 *
 * This is the base cmdsoul which takes care of the different spells.
 *
 * Revision: I want more data in this file!
 *           - Name of spells.
 *           - Classes. 
 *           - Power.
 *           This is due to being able to call the spells from
 *           other things than this soul.
 *           
 * spell_data format: 
 *
 * INDEXED ON : spell-verb
 * VALUES     : [0] = spell-file
 *              [1] = class-mapping
 *                    Indexed on: spell-class
 *                    Values are: [0] - power [mana]
 *                                [1] - req level to cast it  
 * Example:
 *   ([ 
 *      spell-verb1 : ({ spell-file1, ([ spell-class11: ({ power11, lev11 }),
 *                                       spell-class12: ({ power12, lev12 }) ]),
 *      spell-verb2 : ({ spell-file2, ([ spell-class21: ({ power21, lev21 }) ]),
 *      .... 
 *   ])
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

static	mapping spell_data;  /* Indexes on spell_name */

#undef SPELL_FILE
#define SPELL_FILE(verb)               spell_data[verb][0]
#define SPELL_POWER(verb, class)       spell_data[verb][1][class][0]
#define SPELL_REQ_LEVEL(verb, class)   spell_data[verb][1][class][1]
#define IS_SPELL(verb)                 sizeof(spell_data[verb])
#define IS_SPELL_AT_CLASS(verb, class) sizeof(spell_data[verb][1][class])
#define SPELL_CLASSES(verb)            m_indexes(spell_data[verb][1])

#define ADD_ELEMENT(list, elem)        list += ({ elem })


static	string spell_list_name;
static	string spell_list_short;
static	string spell_list_realm;
static	string spell_list_short_name;

#define LIST_SUBLOC    "rogon_spell_list_subloc"
#define DEB(x) if(TP->query_real_name()=="rogon") write(x)

int is_spell_list() {
    return 1;
}

/*------------------------ Soul parts -------------------------------------*/

void init_list() {	
    spell_data = ([]);
}

string get_soul_id() {
   seteuid(getuid());
   if (!strlen(spell_list_name))
       return "A Spell List";
   else
       return spell_list_name+" Spell List";
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

int query_cmd_soul() { return 1; }

/***************************************************************************
 * The list of verbs and functions. Please add new in alfabetical order.
 */

string
wrap_to_command(string value)
{
    return "do_spell";
}

mapping
query_cmdlist()
{
    mapping cmds = ([]);

    if (m_sizeof(spell_data)) 
	cmds += map(spell_data, "wrap_to_command", this_object());

    seteuid(getuid());
    if (spell_list_short)
	cmds += ([spell_list_short:"list_me"]);

    cmds += ([
         "cast"  :"do_spell",
	 "deb"   :"do_deb",
	 "mana"  :"do_mana",
	 "sinfo" :"do_sinfo"
    ]);

    return cmds;
}

/***************************************************************************/

set_realm(string realm) { 
    spell_list_realm = realm;
}

string 
query_realm() { 
    return spell_list_realm; 
}

set_list_name(string name) {
    spell_list_name = name;
}

string query_list_name() {
    return spell_list_name;
}

set_list_short(string name) {
    spell_list_short = name;
}

string query_list_short() {
    return spell_list_short;
}

void
set_list_short_name(string sh_name) {
    spell_list_short_name = sh_name;
}

string
query_list_short_name() {
    return spell_list_short_name;
}

mapping
query_spell_data()
{
    return spell_data;
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


/***************************************************************************/


/*
 * Function name: add_spell
 * Description:   Add the spell to the list of active spells.
 * Arguments:	  verb	 - The activating verb string.
 *		  file	 - The file name for this spell.
 */
int
add_spell(string spell_verb, string file, mapping classes)
{
    if (spell_data[spell_verb])
	return 0;

    spell_data[spell_verb] = ({ file, classes });
    update_commands();
//  command_loaded = 0; 
}

/*
 * Function:	add_spell_file(sting file, string spell_name)
 * Description: If spell_name is not set, the system assumes
 *	        that it is in the property SPELL_S_NAME of the file.
 */
varargs int
add_spell_file(string file, string spell_name, mapping classes = ([]))
{
    FIXEUID;

    if (!stringp(file) || catch(file->load_me()))
	return 0;

    if (!stringp(spell_name))
	spell_name = file->query_prop(SPELL_S_NAME);

    if (stringp(spell_name))
	return add_spell(spell_name, file, classes);
    else
	return 0;
}

varargs void
setup_list(mixed elem1, ...)
{
    mixed *list = ({});
    int i, sz;

    ADD_ELEMENT(list, elem1);
    list += argv;

    for (i=0, sz=sizeof(list); i<sz; i++) 
	spell_data[list[i][1]][1] += ([ list[i][2] : ({ list[i][3], list[i][0] }) ]);

}

/*
 * Function name: remove_spell
 * Description:   Remove the spell with the given verb string.
 * Arguments:	  name - The name of the spell to remove.
 */
int
remove_spell(string spell_name)
{
    spell_data = m_delete(spell_data, spell_name);
    update_commands();
//    command_loaded = 0;
    return 1;
}

int
do_deb(string str)
{
    int i;
    if (!strlen(str))
	return 0;
    
    if (!id(str))
	return notify_fail("Which spell list?\n");

    
    write(sprintf("%O\n", spell_data)); 
    return 1;
}


/*-------------------------- Info mechanisms ---------------------------------*/
int
filter_is_at_level(int index, mixed data)
{
    return data[0][index] == data[1];
}

mixed
spells_at_level(int lvl)
{
    mixed spell = m_indexes(spell_data);
    mixed class;
    mixed ret = ({});
    int i, j;

    FIXEUID;

    for (i=0; i<sizeof(spell); i++)
    {
	class = SPELL_CLASSES(spell[i]);
	if (!class)
	    ADD_ELEMENT(ret, ({ spell[i], 0 }));
	else
	    for (j=0; j<sizeof(class); j++) 
		if (SPELL_REQ_LEVEL(spell[i], class[j]) == lvl)
		    ADD_ELEMENT(ret, ({ spell[i], class[j] }));
    }
    return ret;
}

string
quenya_name(string verb, int class)
{
    if (sizeof(SPELL_CLASSES(verb)) == 1)
	return verb;
    else
	return sprintf("%s %s", verb, num2quenya(class));
}

string
quenya_name_ext(string verb, int class)
{
    string ret = quenya_name(verb, class);
    if (class)
	return sprintf("%-14s (%s)", ret, CAP(roman_str(class)));
    else
	return ret;
}

int
list_me() 
{
    mixed spells;
    int i,j, do_sep;
    string spell_name;

    write("Spell list: "+spell_list_name+" ["+spell_list_short+"]\n");
    write("Of "+CAP(spell_list_realm)+"\n");
    write("-------------------------------\n");

    for(i = 1, do_sep = 0; i<=level(TP) && i<=30; i++)
    {
	if (do_sep && i%5 == 1) {
	    write("- - - - - - - - - - - - - - - -\n");
	    do_sep = 0;
	}

	spells = spells_at_level(i);

	if (!sizeof(spells))
	    continue;

	
	for(j=0;j<sizeof(spells);j++) {
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
 * Parses str -> 'verb' 'class' 'arg'
 */
mixed
parse_spell(string str)
{
    string spell;
    string *expl;
    int class, sz;
    mixed classes;
    string arg;

    DEB("parse_spell: 1\n");
    if (!strlen(str))
	return 0;
    
    expl = explode(str, " ");
    sz = sizeof(expl);
    if (sz == 1) {
	spell = str; 
	class = 0;
	arg = "";
    } else {
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
        
    classes = SPELL_CLASSES(spell);
    
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

#define spell parsed[0]
#define class parsed[1]
#define arg   parsed[2]
    
varargs int
do_mana(string str = "")
{
    int left, power;
    mixed parsed;

    notify_fail("There is no such spell '" + str + "'.\n");

    parsed = parse_spell(str);

    if (!parsed)
	return 0;

    power = SPELL_POWER(spell, class);

    if (TP->query_wiz_level())
	write("WIZINFO: " + power + " mana points.\n");

    write(sprintf("The '%s' spell would require %s of all your mana.\n",
		  quenya_name(spell, class), 
		  ratio_str(power, TP->query_max_mana())));

    left = TP->query_mana() - power;

    if (left<0)
	write("You can not cast the spell, since you do not have that much mana.\n");
    else if (left == 0)
	write("You would loose all your mana in an attempt to cast it.\n");
    else
	write("You would have "+ratio_str(left, TP->query_max_mana())+
	      " mana left if you cast it successfully.\n");

    if (level(TP) < SPELL_REQ_LEVEL(spell, class))
	write("NOTE: You can not cast this spell, since you are only a "+
	      num2order(level(TP))+" level spell caster, and the spell is at "+
	      "level "+ SPELL_REQ_LEVEL(spell, class)+".\n");
    return 1;
}

varargs int
do_sinfo(string str = "")
{
    mapping classes;
    string *words;
    int n, left;
    object spell_obj;
    int mana;
    int normal_time;
    int wanted_time;
    mixed parsed;
    string spell_name;
    int req_level;
    int power;

    parsed = parse_spell(str);
    if (!parsed)
	return notify_fail("Eh.. what spell?\n");

    spell_obj = find_object(SPELL_FILE(spell));
    spell_obj -> set_caster(TP);
    spell_obj -> set_spell_class(class);

    normal_time = spell_obj->query_normal_casting_time();
    wanted_time = spell_obj->query_casting_time();

    spell_name = quenya_name(spell, class);
    req_level = SPELL_REQ_LEVEL(spell, class);
    power     = SPELL_POWER(spell, class);
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
		  spell, spell_obj->query_prop(SPELL_S_SYNTAX),
		  spell_obj->query_prop(SPELL_S_DESC)));
    return 1;
}

/*-------------------------- Casting of Spells -------------------------------*/

object
create_spell_obj(string spell_name, int class_wanted)
{
    object spell_obj;
    string file = SPELL_FILE(spell_name);
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

    spell_obj -> set_caster(TP);
    spell_obj -> set_mana(SPELL_POWER(spell_name, class_wanted));
    spell_obj -> set_data(spell_name, class_wanted, 
			  quenya_name(spell_name, class_wanted));
    spell_obj -> add_prop(SPELL_O_ENVIRONMENT, EP);
    spell_obj -> set_sf(spell_obj);

    return spell_obj;
}

/*
 * Function:    do_spell
 * Desc:	This is the starting point for all spells. This is called from
 *		the command driver.
 *		 - Find the spell.
 *		 - Call the spell object.
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
    if (FindCallOut(TP, "cmdhooks_do_spell")>0 ||
       TP->query_prop(LIVE_O_CONSENTRATES_SPELL))
	return notify_fail("You already consentrate on another spell!\n");

    verb = query_verb();

    notify_fail(CAP(verb) + "?\n");

    if (verb == "cast") {
	notify_fail("Cast which spell?\n");
	parsed = parse_spell(str);
	if (!parsed)
	    return 0;
    } else {
	if (!strlen(str))
	    str = verb;
	else
	    str = verb + " " + str;
	parsed = parse_spell(str);
	if (!parsed)
	    return 0;
    }
    
    if (SPELL_REQ_LEVEL(spell, class) > level(TP))
	return notify_fail("You are not allowed to cast this high level spell.\n");

    spell_obj = create_spell_obj(spell, class);
    if (!spell_obj) 
	return notify_fail("The spell could not load.\n");

    return spell_obj->cast_spell(arg);
}

#undef spell
#undef class


