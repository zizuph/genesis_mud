/////////////// ~Kalad/std/kalad_object.c /////////////////////////////////
//
// Name:        Kalad Wizard's Key
// Purpose:     Gives us some nifty extra commands
// Clones:      Each Kalad wiz has one
// Created by:  Ashbless    In the beginning... (`91-`93?)
// Credits:     Some code borrowed from Windwalker's domain line.
// Modified by: Antharanos  ?           added some directories
//              Korat       ?           added some dirs
//              Ashbless    96          many new commands (?)
//              Sarr        Feb 97      added inkalad() and some defs
//              Ashbless    7/29/97     fixed bug with finger_player clones
//              Ashbless    7/30/97         idle time added to klist
//
///////////////////////////////////////////////////////////////////////////

inherit "/std/object";
#include "/d/Kalad/defs.h"
#include <std.h>
#include <options.h>
#include <filepath.h>
#include <time.h>


/***************************************************
 * Defines
 ***************************************************/
#define COMFILE            "/cmd/wiz/apprentice"
#define TOOLFILE           "/cmd/std/tracer_tool_base"
#define KIOSK              CENTRAL(test/kiosk)
#define SHOWCASE           CENTRAL(test/showcase)
#define MOTD               KALAD(motd)
#define DOM_BOARD          KALAD(private/private_board)
#define CUSTOM_LIMIT       10
#define SAVE_DIR           LOGS(custom_alias/)

// Used by kd()
#define WIZARD_AS_DIRPATH  "_wizard_as_dirpath"
#define WIZARD_S_LAST_DIR  "_wizard_s_last_dir"

#define DIR_ALIASES  ([                                                  \
"log"    : ({ KALAD(log),              "Kalad logs directory"        }), \
"priv"   : ({ KALAD(private),          "Kalad private code directory"}), \
"cent"   : ({ COMMON(central) ,        "Central District of Kabal"   }), \
"port"   : ({ COMMON(port) ,           "Port District of Kabal"      }), \
"cvan"   : ({ COMMON(caravan) ,        "Caravan District of Kabal"   }), \
"wild"   : ({ COMMON(wild) ,           "Wild lands outside Kabal"    }), \
"pass"   : ({ WILD(pass) ,             "Pass NE of Kabal"            }), \
"high"   : ({ WILD(high) ,             "Highlands North of Kabal"    }), \
"farm"   : ({ WILD(farm) ,             "Farmlands West of kabal"     }), \
"undr"   : ({ CPASS(drow) ,            "Drow city of Undraeth"       }), \
"acad"   : ({ CPASS(guild) ,           "The Academy"                 }), \
"vill"   : ({ CPASS(kaldoro) ,         "Village of Kaldoro"          }), \
"des"    : ({ CPASS(desert) ,          "Great Kalad Waste"           }), \
"sewer"  : ({ COMMON(sewers) ,         "Sewers under Kabal"          }), \
"trade"  : ({ COMMON(trade) ,          "Trade District of Kabal"     }), \
"mark"   : ({ COMMON(market) ,         "Market District of Kabal"    }), \
"open"   : ({ KALAD(open) ,            "Kalad Open code and info"    }), \
"noble"  : ({ COMMON(noble) ,          "Noble District of Kabal"     }), \
"std"    : ({ KALAD(std) ,             "Kalad standard inherits dir" }), \
"com"    : ({ KALAD(common) ,          "Kalad common code directory" }), \
"kal"    : ({ "/d/Kalad" ,             "Kalad home directory"        }), \
"cant"   : ({ COMMON(canthyr) ,        "Empire of Canthyr"           }), \
"raum"   : ({ COMMON(raum) ,           "Kingdom of Raumdor"          }), \
"dwarf"  : ({ CPASS(dwarf) ,           "Dwarven city of Underhome"   }), \
"uc"     : ({ CPASS(uc) ,              "Underground Connection dir"  }), \
"mind"   : ({ CPASS(mind) ,            "Mind Flayer directory"       }), \
"gnome"  : ({ CPASS(dgnome) ,          "Deep Gnome city of Heartrock"}), \
"than"   : ({ CVAN(thanar) ,           "Thanarian Human race guild"  }), \
"drow"   : ({ CPASS(drow/guild) ,      "Drow race guild"             }), \
"acc"    : ({ CPASS(drow/guild1) ,     "Accursed guild"              }), \
"guild"  : ({ COMMON(guilds) ,         "Kalad guilds directory"      }), \
"duer"   : ({ GUILDS(duergar) ,        "Duergar Dwarven race guild"  }), \
"shad"   : ({ GUILDS(shadow_walkers) , "Shadow Walkers thieves guild"}), \
"merc"   : ({GUILDS(merchant),         "Merchant guild"              }), \
"merc"   : ({GUILDS(merchant),         "Merchant guild"            }), \
"sship"  : ({ PORT(shipline1) ,        "Shipline to Shire domain"    }), \
"tship"  : ({ PORT(shipline2) ,        "Shipline to Terel domain"    }), \
"eship"  : ({ PORT(shipline5) ,        "Shipline to Emerald domain"  }), \
"rship"  : ({ PORT(shipline6) ,        "Shipline to Raumdor"         })  \
])

#define ROOM_ALIASES  ([                                                               \
"post"  : ({ "/d/Genesis/wiz/post"   ,"Goto wizard's post office"                  }), \
"cvan"  : ({ CVAN(shop/wayfar_guild) ,"Goto Wayfarer's Guild in Caravan District"  }), \
"port"  : ({ PORT(s8)                ,"Goto liftroom in Port District"             }), \
"trade" : ({ TRADE(tsquare/c2)       ,"Goto center of the Trade District"          }), \
"cent"  : ({ CENTRAL(plaza/sq_mon)   ,"Goto monument in Central District"          }), \
"kal"   : ({ KALAD(workroom)         ,"Goto Kalad domain workroom"                 }), \
"pass"  : ({ CPASS(w31)              ,"Goto Hill Giant village in NE wilderness"   }), \
"drow"  : ({ CPASS(drow/d5)          ,"Goto entrance of the Drow city of Undraeth" }), \
"des"   : ({ CPASS(desert/d1)        ,"Goto western edge of the Great Kalad Waste" }), \
"sdock" : ({ PORT(s81)               ,"Goto Shire shipline dock"                   }), \
"tdock" : ({ PORT(s97)               ,"Goto Terel shipline dock"                   }), \
"edock" : ({ PORT(s1)                ,"Goto Emerald shipline dock"                 }), \
"rdock" : ({ PORT(s104)              ,"Goto Raumdor shipline dock"                 })  \
])


/***************************************************
 * Globals
 ***************************************************/
mapping custom_dir;
mapping custom_room;


/****************************
 *   Prototypes
 ****************************/
int get_body(string arg);
void kiosk_post(string body);
void get_type(string body);
void showcase_post(string type, string body);
void cleanup_msg(string filename, string str);
void cleanup_run();
void cleanup_typo();
void cleanup_err();
void cleanup_bug();
void cleanup_ideas();
int kd(string str);
int motd();
void latest_domain_note();
int klist(string flag);
void do_login();
int kg(string arg);


masterp()
{
    string a;
    return sscanf( file_name( TO ), "%s#%s", a, a ) != 2;
}

create_object()
{
    ::create_object();
    if (masterp())
	return;

    set_name("key");
    add_name("wizard key");
    add_name("wizard's key");
    set_adj("kalad");
    set_short("kalad wizard's key");
    set_pname("keys");
    set_pshort("kalad wizard's keys");
    set_long("This is one of the fabled 'Keys to Kalad'. " +
      "It allows the wizards of Kalad certain powers. " +
      "For a listing of these powers type 'khelp'.\n");

    add_prop(OBJ_M_NO_DROP,"Now why would you want to drop the key?\n");

    move( TP );
    do_login();
    restore_object(SAVE_DIR + TP->query_real_name());
}


void
do_login()
{
    if ("secure/master"->query_wiz_dom(TP->query_name()) == "Kalad")
    {
	motd();                       /* show message of the day */

	/* If board isn't loaded, leave some time for it to load */
	if (DOM_BOARD->query_latest_note())
	    latest_domain_note();
	else
	{
	    write("\n");
	    ALARM(1.0,latest_domain_note);
	}

	klist("-a");                /* show info on Kalad wizzes */
    }
}


void
latest_domain_note()
{
    string fname, author, timestr, month, daystr;
    int time, last, day;

    if (fname = DOM_BOARD->query_latest_note())
	if (sscanf(fname,"b%d",time) == 1)
	{
	    author = DOM_BOARD->query_author(DOM_BOARD->query_num_messages());
	    write("\nLast note on Kalad domain board written by ");
	    timestr = ctime(time);
	    sscanf(timestr,"%s %s %d %d:",daystr,month,day,time);
	    write(sprintf("%s on %s %s %d at %d o'clock.\n",C(author),daystr,month,day,time));
	}

    write("\n");
}


int
motd()
{
    if (file_size(MOTD) > 0)
    {
	write("\n"); 
	cat(MOTD,0,25);
    }

    return 1;
}


void init()
{
    NF("The key is for Kalad wizzes only!\n");
    if (E(TO) != TP)
	return 0;
    if (!TP->query_wiz_level())
    {
	write("You're not a wizard so the key self-destructs!\n");
	remove_object();
	return 0;
    }
    if ("secure/master"->query_wiz_dom(TP->query_name()) != "Kalad")
    {
	write("You're not a member of the Kalad domain...\n" +
	  "The key melts, leaving a slimy substance on your hands.\n");
	remove_object();
	return 0;
    }

    reset_euid();

    AA(khelp,khelp);

    AA(ker,ker);
    AA(kbug,kbug);
    AA(kid,kid);
    AA(ktyp,ktyp);
    AA(krun,krun);
    AA(kpr,kpr);
    AA(kered,kered);
    AA(kbuged,kbuged);
    AA(ktyped,ktyped);

    AA(klist,klist);
    add_action("show_exits","exits");
    AA(proj,proj);
    AA(reader,reader);
    AA(get_body,knote);
    AA(get_body,decree);
    AA(kd,kd);
    AA(motd,motd);
    AA(kg,kg);
    AA(inkalad,inkalad);
}

int
inkalad()
{
    int i;
    object *obs;
    string s1;
    obs = users();
    for(i=0;i<sizeof(obs);i++)
    {
	if(E(obs[i]))
	{
	    sscanf(file_name(E(obs[i])),"/d/%s/",s1);
	    if(s1 == "Kalad")
	    {
		tell_object(TP,"In Kalad: "+obs[i]->query_name()+"  "+
		  file_name(E(obs[i]))+"\n");
	    }
	}
    }
    return 1;
}


int
kd(string arg)
{
    int len, i;
    string old_path, new_path, *parts, *indexes, alias, msg;
    object ob;

    old_path = TP->query_path(); // remember the old path

    // If no argument was given, change to wizard's home directory
    if ( !stringp(arg) || ((len = strlen(arg)) < 1) )
	new_path = SECURITY->query_wiz_path(TP->query_real_name());

    else // A command line argument was given. See what it was...
	switch(arg[0]) // check if the 1st character of the arg is special
    {
    case '@':
	indexes = m_indexes(DIR_ALIASES);

	if (len == 1) // if no alias given, list all aliases
	{
	    // Show all predefined aliases
	    msg = " #    Directory Alias   Description\n" +
	    "---   ---------------   -----------\n";          
	    for (i=0;i<sizeof(indexes);i++)
		msg += sprintf("%2d)   %15-s   %s\n", i+1, indexes[i],
		  DIR_ALIASES[indexes[i]][1]);

	    // Show all custom aliases 
	    if ( mappingp(custom_dir) && sizeof(indexes = m_indexes(custom_dir)) )
	    {
		msg += "\n #    Custom Alias   Directory\n" +
		"---   ------------   ---------\n";
		for (i=0;i<sizeof(indexes);i++)
		    msg += sprintf("%2d)   %12-s   %s\n", i+1, indexes[i],
		      RPATH(custom_dir[indexes[i]]));
	    } 

	    TP->more(msg); // This might be long. let's use more.
	    return 1;
	}

	else // otherwise process the given alias...
	{
	    alias=extract(arg,1,(len-1)); // parse the alias from the arg

	    // is it a predefined alias? If so, change to the aliased dir
	    // and write the description of the alias
	    if ( (i = member_array(alias, indexes)) >= 0 )
	    {
		new_path = DIR_ALIASES[indexes[i]][0];
		write(DIR_ALIASES[indexes[i]][1] + ": ");
		break;
	    }

	    else // if not, is it a custom alias?
	    {
		// if so, change to the aliased directory
		if ( mappingp(custom_dir) && sizeof(indexes = m_indexes(custom_dir)) )
		    if ( (i = member_array(alias, indexes)) >= 0 )
		    {
			new_path = custom_dir[indexes[i]];
			break;
		    }

		// If not, it's not an alias at all. Fail.
		NF("'" + alias + "' is not a directory alias.\n");
		return 0;
	    }
	}

    case '+':
	if ( len == 1 ) // If there is no subargument following the plus sign...
	{
	    // Show only custom aliases (not built-ins)
	    if ( mappingp(custom_dir) && sizeof(indexes = m_indexes(custom_dir)) )
	    {
		msg = " #    Custom Alias   Directory\n" +
		"---   ------------   ---------\n";
		for (i=0;i<sizeof(indexes);i++)
		    msg += sprintf("%2d)   %12-s   %s\n", i+1, indexes[i],
		      RPATH(custom_dir[indexes[i]]));
	    } 

	    if (strlen(msg)) 
		TP->more(msg);
	    else
		write("You have not set any custom directory aliases.\n");

	    return 1;
	}

	// Make sure there are the right number of subarguments                
	NF("To add a custom directory alias: kd +<alias> <path>.\n");
	if ( (sscanf(arg,"+%s %s", alias, new_path) != 2) ||
	  (strlen(alias) < 1) )
	    return 0;

	// We don't want aliases that are too long
	NF("That alias is too long. Aliases must be no longer than 12 characters.\n");
	if (strlen(alias) > 12)
	    return 0;

	// Don't allow built-in aliases to be redefined
	NF("'"+alias+"' is a predefined alias and cannot be redefined.\n");
	if ( member_array(alias, m_indexes(DIR_ALIASES)) >= 0 )
	    return 0;

	// Make sure the pathname is a valid directory
	new_path = TPATH(TP->query_real_name(),new_path);
	NF("No such directory '" + new_path + "'.\n");
	if (file_size(new_path) != -2)
	    return 0;

	if (!mappingp(custom_dir)) // initialize the mapping
	    custom_dir = ([]);

	// If there are already some custom aliases...       
	if ( sizeof(indexes = m_indexes(custom_dir)) )
	{
	    // If the wiz is not redefining an existing custom alias,
	    // make sure the custom alias limit is not exceeded
	    NF("You cannot have more than " + CUSTOM_LIMIT + " custom aliases.\n" +
	      "Try removing an old alias first.\n");
	    if ( ((i = member_array(alias, indexes)) < 0) && (sizeof(indexes) >= CUSTOM_LIMIT) )
		return 0;

	    if (i >= 0)
		write("Removing previous alias '" + alias + "' which was aliased to '" +
		  RPATH(custom_dir[indexes[i]]) + "'.\n");
	} 

	// Add the custom alias and save changes to a save file
	custom_dir = custom_dir + ([ alias : new_path ]);
	indexes = m_indexes(custom_dir);
	write("Custom directory alias '" + alias + "' added to '" + RPATH(new_path) + "'.\n");                
	save_object(SAVE_DIR + TP->query_real_name());                      
	return 1;

    case '-':
	// If there is no alias following the minus sign...
	if ( len == 1 )
	{
	    new_path = TP->query_prop(WIZARD_S_LAST_DIR);
	    break;
	}

	sscanf(arg,"-%s",alias);

	// Only remove the alias if the alias exists, and it is not a built-in alias
	if ( (i = member_array(alias, (indexes = m_indexes(custom_dir)))) < 0 )
	{
	    if ( member_array(alias, m_indexes(DIR_ALIASES)) < 0 )
		NF("'" + alias + "' cannot be removed because it's not an alias.\n");
	    else
		NF("'" + alias + "' is a predefined alias. You can't remove it!\n");

	    return 0;
	}

	// Make a new mapping excluding the alias, save changes to a save file,
	// and tell the wizard what alias they removed.
	write("Removing  alias '" + alias + "' which was aliased to '" +
	  RPATH(custom_dir[indexes[i]]) + "'.\n");
	custom_dir = mkmapping(exclude_array(indexes,i,i),
	  exclude_array(m_values(custom_dir),i,i));           
	save_object(SAVE_DIR + TP->query_real_name());  
	return 1;

    default: // No special 1st character. Check the whole string
	if ( arg == "." ) // Kd to current directory
	{
	    write(old_path + "\n\n");
	    ls(old_path,"F");
	    return 1;
	}

	else // Kd to the new directory given by the pathname
	    new_path = FTPATH(old_path, arg);

	break;
    } // end switch(arg[0])

    // If the given arg is not a directory, see if it is an object
    if (file_size(new_path) != -2)
    {
	// If it's not an object, it's a bad path. Fail.
	if (!objectp(ob = TOOLFILE->parse_list(arg)))
	{
	    NF("No such directory '" + arg + "'.\n");
	    return 0;
	}

	// otherwise, change to the dir containing the object's file
	parts = explode(FN(ob), "/");
	new_path = implode(parts[0..(sizeof(parts) - 2)], "/");
    }

    // Change to new dir, display dir name, and list contents of dir
    write(new_path + "\n\n");
    TP->add_prop(WIZARD_S_LAST_DIR, old_path);
    TP->set_path(new_path);
    ls(new_path,"F");

    return 1;
}


int
get_body(string arg)
{
    string file, home, subdir;

    if (!arg)
	if (query_verb() == "knote")
	    "/std/edit"->edit("kiosk_post");
	else
	    "/std/edit"->edit("get_type");

    else
    {
	if ( sscanf(arg, "~%s/%s", home, subdir) == 2)
	    if (home == "Kalad")
		arg = "/d/Kalad/" + subdir;
	    else
		arg = "/d/Kalad/" + home + "/" + subdir;

	NF(arg + ": No such file!\n");
	if (! (file = read_file(arg)) )
	    return 0;

	if (query_verb() == "knote")
	    kiosk_post(file);
	else
	    get_type(file);
    }

    return 1;
}


void
kiosk_post(string body)
{ 
    if (!strlen(body))
    {
	write("No message entered.\n");
	return;
    }

    write("Message posted.\n");      
    KIOSK->post_it(body);
}


void
get_type(string body)
{
    int type;

    if (!strlen(body))
    {
	write("No message entered.\n");
	return;
    }

    write("\n" +
      " #  Message Type:           Author:\n" +
      "--- --------------------    --------------------------\n" +
      " 0) Royal Proclamation      High Lord\n" +
      " 1) Royal Decree            High Minister\n" +
      " 2) Council Edict           Speaker of High Council\n" +
      " 3) Church Bull             Arch Prelate of Solara\n" +
      " 4) Military Declaration    Knight General of Armies\n" +
      " 5) Principal Statute       Ring Prince\n" +
      " 6) Royal Canon             High Cleric of the Citadel\n" +
      " 7) City Ordinance          High Council\n" +
      " 8) Public Safety Mandate   Knight Captain of Militia\n" +
      " 9) Official Announcement   High Council\n" +
      "10) Official Notice         Knight Captain of Militia\n" +
      "11) Public Announcement     Public Relations Minister\n" +
      "\n");

    write("choice [11]: ");
    input_to("showcase_post",0,body);
}


void
showcase_post(string entry, string body)
{
    int type;

    if ( (sscanf(entry,"%d",type) != 1) || type < 0 || type > 11 )
	type = 11;

    write("Message posted.\n");      
    SHOWCASE->post_it(body, type);
}


khelp()
{
    TP->more(STD(khelp),1);   
    return 1;
}


//////////////////////////////////////////
// Kalad goto command with room aliases //
//////////////////////////////////////////
int
kg(string arg)
{
    string room, msg, *indexes, alias;
    int i, len;

    indexes = m_indexes(ROOM_ALIASES);

    // If no argument is given, list all room aliases
    if ( !stringp(arg) || ((len = strlen(arg)) < 1) )
    {
	// Show all built-in room aliases
	msg = " #    Room Alias   Description\n" +
	"---   ----------   -----------\n";          
	for (i=0;i<sizeof(indexes);i++)
	    msg += sprintf("%2d)   %10-s   %s\n", i+1, indexes[i],
	      ROOM_ALIASES[indexes[i]][1]);

	// Show all custom room aliases 
	if ( mappingp(custom_room) && sizeof(indexes = m_indexes(custom_room)) )
	{
	    msg += "\n #    Custom Alias   Room\n" +
	    "---   ------------   ---------\n";
	    for (i=0;i<sizeof(indexes);i++)
		msg += sprintf("%2d)   %12-s   %s\n", i+1, indexes[i],
		  RPATH(custom_room[indexes[i]]));
	}

	TP->more(msg);  // This might be long so we'll use more()
	return 1;
    }

    else // An argument was given
	switch (arg[0]) // Check if the first character is special
    {
    case '+':
	if ( len == 1 ) // If there is no subargument following the plus sign...
	{
	    // Show only custom aliases (not built-ins)
	    if ( mappingp(custom_room) && sizeof(indexes = m_indexes(custom_room)) )
	    {
		msg = " #    Custom Alias   Room\n" +
		"---   ------------   ---------\n";
		for (i=0;i<sizeof(indexes);i++)
		    msg += sprintf("%2d)   %12-s   %s\n", i+1, indexes[i],
		      RPATH(custom_room[indexes[i]]));
	    } 

	    if (strlen(msg)) 
		TP->more(msg);
	    else
		write("You have not set any custom room aliases.\n");

	    return 1;
	}

	// Make sure there are the right number of subarguments                
	NF("To add a custom room alias: kg +<alias> <path>.\n");
	if ( (sscanf(arg,"+%s %s", alias, room) != 2) ||
	  (strlen(alias) < 1) )
	    return 0;

	// We don't want aliases that are too long
	NF("That alias is too long. Aliases must be no longer than 12 characters.\n");
	if (strlen(alias) > 12)
	    return 0;

	// Don't allow built-in aliases to be redefined
	NF("'"+alias+"' is a predefined alias and cannot be redefined.\n");
	if ( member_array(alias, m_indexes(ROOM_ALIASES)) >= 0 )
	    return 0;

	// Make sure the pathname is a valid room
	room = TPATH(TP->query_real_name(),room);
	NF("No such room '" + room + "'.\n");
	if ( LOAD_ERR(room) || !room->query_prop(ROOM_I_IS) )
	    return 0;

	if (!mappingp(custom_room)) // initialize the mapping
	    custom_room = ([]);

	// If there are already some custom aliases...       
	if ( sizeof(indexes = m_indexes(custom_room)) )
	{
	    // If the wiz is not redefining an existing custom alias,
	    // make sure the custom alias limit is not exceeded
	    NF("You cannot have more than " + CUSTOM_LIMIT + " custom aliases.\n" +
	      "Try removing an old alias first.\n");
	    if ( ((i = member_array(alias, indexes)) < 0) && (sizeof(indexes) >= CUSTOM_LIMIT) )
		return 0;

	    if (i >= 0)
		write("Removing previous alias '" + alias + "' which was aliased to '" +
		  RPATH(custom_room[indexes[i]]) + "'.\n");
	} 

	// Add the custom alias and save changes to a save file
	custom_room = custom_room + ([ alias : room ]);
	indexes = m_indexes(custom_room);
	write("Custom room alias '" + alias + "' added to '" + RPATH(room) + "'.\n");                
	save_object(SAVE_DIR + TP->query_real_name());                      
	return 1;

    case '-':
	// If there is no alias following the minus sign, fail.
	NF("To remove a custom room alias: kg -<alias>.\n");
	if ( len == 1 )
	    return 0;

	sscanf(arg,"-%s",alias);

	// Only remove the alias if the alias exists, and it is not a built-in alias
	if ( (i = member_array(alias, (indexes = m_indexes(custom_room)))) < 0 )
	{
	    if ( member_array(alias, m_indexes(ROOM_ALIASES)) < 0 )
		NF("'" + alias + "' cannot be removed because it's not an alias.\n");
	    else
		NF("'" + alias + "' is a predefined alias. You can't remove it!\n");

	    return 0;
	}

	// Make a new mapping excluding the alias, save changes to a save file,
	// and tell the wizard what alias was removed.
	write("Removing  alias '" + alias + "' which was aliased to '" +
	  RPATH(custom_room[indexes[i]]) + "'.\n");
	custom_room = mkmapping(exclude_array(indexes,i,i),
	  exclude_array(m_values(custom_room),i,i));           
	save_object(SAVE_DIR + TP->query_real_name());  
	return 1;

    default: // If it is not special, process the given alias...
	// Is it a predefined alias? If so, move to the aliased room
	// and write the description of the alias
	if ( (i = member_array(arg, indexes)) >= 0 )
	{
	    room = ROOM_ALIASES[indexes[i]][0];
	    write(ROOM_ALIASES[indexes[i]][1] + ":\n\n");
	    break;
	}

	else // if not, is it a custom alias?
	{
	    // if so, move to the aliased room
	    if ( mappingp(custom_room) && sizeof(indexes = m_indexes(custom_room)) )
		if ( (i = member_array(arg, indexes)) >= 0 )
		{
		    room = custom_room[indexes[i]];
		    break;
		}

	    // If not, it's not an alias at all. Fail.
	    NF("'" + arg + "' is not a room alias.\n");
	    return 0;
	}
    } // end switch

    TP->move_living("X",room); // Do the actual move
    return 1;
}


ker()
{
    NF("There are currently no errors logged.\n");
    if ( MTAIL(LOGS(errors),cleanup_err) )
	return 1;  
    else
	return 0;
}


kbug()
{
    NF("There are currently no bugs logged.\n");
    if ( MTAIL(LOGS(bugs),cleanup_bug) )
	return 1;  
    else
	return 0;
}


kid()
{
    NF("There are currently no typos logged.\n");
    if ( MTAIL(LOGS(ideas),cleanup_ideas) )
	return 1;  
    else
	return 0;
}


ktyp()
{
    NF("There are currently no typos logged.\n");
    if ( MTAIL(LOGS(typos),cleanup_typo) )
	return 1;  
    else
	return 0;
}


kpr()
{
    NF("There are currently no typos logged.\n");
    if ( MTAIL(LOGS(praise),"") )
	return 1;  
    else
	return 0;
}


krun()
{
    NF("There are currently no runtime errors logged.\n");
    if ( MTAIL(LOGS(runtime),cleanup_run) )
	return 1;
    else
	return 0;
}


void cleanup_run()
{ cleanup_msg(LOGS(runtime),"runtime errors when they have been fixed."); }


void cleanup_typo()
{ cleanup_msg(LOGS(typos),"typos when they have been fixed."); }


void cleanup_bug()
{ cleanup_msg(LOGS(bugs),"bugs when they have been fixed."); }


void cleanup_err()
{ cleanup_msg(LOGS(errors),"errors when they have been fixed."); }


void cleanup_ideas()
{ cleanup_msg(LOGS(ideas),"ideas when they have been implemented."); }


void
cleanup_msg(string filename, string str)
{
    int size, flen;

    if ( (size = file_size(filename)) > 50000)
	write("\n******************************************************************\n" +
	  "* \""+filename+"\" too large to tail in more format: "+size+" bytes!\n" +
	  "* Please purge this log as soon as possible!\n" +
	  "******************************************************************\n\n");

    else
    {
	flen = sizeof(explode(read_file(filename), "\n"));

	if (flen > 0)
	    write("******************************************************************\n" +
	      "* Please clean out your " + str + "\n" +
	      "* The log currently contains " + flen + " lines.\n" +
	      "******************************************************************\n");
    }
}


kbuged()
{
    ed("/d/Kalad/log/bugs");
    return 1;
}


ktyped()
{
    ed("/d/Kalad/log/typos");
    return 1;
}


kered()
{
    ed("/d/Kalad/log/errors");
    return 1;
}


show_exits()
{
    if (!find_object("/d/Kalad/room_std"))
	"/d/Kalad/room_std"->load_it();

    write("/d/Kalad/room_std"->list_exits(E(TP)));
    return 1;
}


/* List all Kalad wizzes currently on. Shows name, level, and
* Kalad wizline busy status. With "-a" flag will show all
* Kalad wizzes, including those not on.
*/ 
int
klist(string flag)
{
    string head, *members, last, biz, idle;
    int c, logtime, deadtime, *itime;

    string USAGE = "Usage: 'klist'    - list info on Kalad wizzes currently on.\n" +
    "       'klist -d' - list working directory of Kalad wizzes on.\n" +
    "       'klist -a' - list info on all Kalad wizzes.\n";

    NF(USAGE);   
    if ( flag && (flag != "-a") && (flag != "-d") )
    {
	write(flag + ": bad option!\n");
	return 0;
    }

    head="Name         Lvl  ";
    if (flag == "-a")
	write("Listing all Kalad members:\n\n" + head + "Last Login");      
    else
    {
	write("Listing Kalad members currently on:\n\n" + head + "Busy       "+
	  "Idle        ");
	if (flag)
	    write("Current Working Directory");
	else
	    write("Location");
    }
    write("\n\n");

    members = "/secure/master"->query_domain_members("Kalad");
    for (c=0; c < sizeof( members ); c++)
    {
	int show_member=0;
	object player=find_player(members[c]);

	if (flag == "-a")
	    show_member=1;
	else if (player)
	    if (!player->query_linkdead())
		show_member=1;

	if (show_member)
	{
	    int klev = "/secure/master"->query_wiz_level(members[c]);
	    string name = C(members[c]) + "            ";

	    name = extract(name,0,12);

	    if (!flag)
		last = RTILDE(file_name(E(player)));

	    else
	    if (flag == "-d")
		last = RTILDE(player->query_path());

	    else
	    {
		if (player)
		    if (deadtime=player->query_linkdead())
		    {
			deadtime = time() - deadtime;
			last="linkdead for "+"/lib/time"->convtime(deadtime);
		    }
		    else
			last = "currently in the game";
		else
		{
		    player = (object)SECURITY->finger_player(members[c]);
		    logtime = time() - (int)player->query_login_time();
		    player->remove_object(); // Kill that nasty finger_player!                 
		    last = "/lib/time"->convtime(logtime);
		    last = last + " ago";
		}
	    }

	    if (flag == "-a")
		write(name + klev + "   " + last + "\n");
	    else
	    {
		biz = COMFILE->busy_string(player->query_prop(WIZARD_I_BUSY_LEVEL));
		biz = extract(biz + "           ",0,10);

		itime = TIME2NUM(query_idle(player));
		idle = "";
		if (itime[1]) idle = sprintf("%dh ", itime[1]);
		if (itime[2]) idle = sprintf("%s%dm ", idle, itime[2]);
		if (itime[3]) idle = sprintf("%s%ds", idle, itime[3]);
		idle = extract(idle + "            ",0,11);

		write(name + klev + "   " + biz + idle + last + "\n");
	    }
	}
    }

    return 1;
}


int
proj()
{
    TP->more("/d/Kalad/korat/log/projects",1,(int)TP->query_prop(PLAYER_I_MORE_LEN));
    return 1;
}


reader()
{
    object ob;
    int i;

    ob = deep_inventory(TP);
    for (i=0; i<sizeof(ob); i++)
    {
	if (ob[i]->id("mailreader"))
	{
	    "secure/master"->do_debug("destroy",ob[i]);
	    write("Mail reading is now off.\n");
	    return 1;
	}
    }

    ob = clone_object("/secure/mail_reader");
    ob->move(TP);
    write("Mail reading is now on.\n");
    return 1;
}


string query_auto_load()
{
    return MASTER;
}
