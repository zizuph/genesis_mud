/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * treas_list.c
 *
 * Vader
 * modified by Sorgum 950707
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
#include <cmdparse.h>
#include <language.h>

inherit STDOBJECT;


public int do_read(string str);
public int do_page(string str);

int charon_chest = 0;

/*
 * Function name: create_object
 * Description:   Default constructor.
 */
public void
create_object()
{
    ::create_object();
    set_name("treasure list");
    add_name("list");
    set_short("list of stored treasures");
    set_long("This is a comprehensive listing of all of the rare " +
	     "and precious treasures that the King keeps stored " +
	     "away.  There are ten pages.  You wonder if your eyes " +
	     "were meant for this document....\n");
    
    add_prop(OBJ_I_NO_GET, 1);

    charon_chest = random(10);
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    ::init();
    add_action(do_read, "read");
    add_action(do_page, "page");        
}

/*
 * Function name: do_read
 * Description:   Handle the read actions
 * Returns:       1/0
 */
public int
do_read(string str)
{
    string page;
    
    if (!strlen(str) || (str != "list")) {
	NF("read what?\n");
	return 0;
    }

    write ("Use 'page <x>' where x is the page number (one - ten)\n");
    return 1;
}

/*
 * Function name: query_chest_contents
 * Description:   return list of objects to put in the chest
 */
public string*
query_chest_contents(int i)
{
    string *list = ({ });
   
    switch (i) {
    case 0:
	list += ({OBJ_DIR + "chalice1",
		  OBJ_DIR + "dagg",
		  OBJ_DIR + "torbas_staff",		 
		  OBJ_DIR + "log"});
	break;
    case 1:
	list += ({OBJ_DIR + "lars_cap",
		  OBJ_DIR + "fatty_belt",
		  OBJ_DIR + "catspaw"});
	break;
    case 2:
	list += ({OBJ_DIR + "odo_bucket",
		  OBJ_DIR + "bogdrum",
		  OBJ_DIR + "goblin_brain",		 
		  OBJ_DIR + "snipes_jar"});
	break;
    case 3:
	list += ({OBJ_DIR + "trumpet",
		  OBJ_DIR + "vader_sword",
		  OBJ_DIR + "met_cloak"});
	break;
    case 4:
	list += ({OBJ_DIR + "norm_tab",
		  OBJ_DIR + "quorm_amulet",
		  OBJ_DIR + "mortricia_hair",		 
		  OBJ_DIR + "quest_book"});
	break;
    case 5:
	list += ({OBJ_DIR + "crown",
		  OBJ_DIR + "pocket_protector",
		  OBJ_DIR + "fire_amulet"});
	break;
    case 6:
	list +=({OBJ_DIR + "fatty_chin",
		 OBJ_DIR + "cedric_disc",
		 OBJ_DIR + "jorl_anvil",		 
		 OBJ_DIR + "nick_paste"});
	break;
    case 7:
	list += ({OBJ_DIR + "sceptre",
		  OBJ_DIR + "baton",
		  OBJ_DIR + "broom"});
	break;
    case 8:
	list += ({OBJ_DIR + "briefcase",
		  OBJ_DIR + "hope_amulet",
		  OBJ_DIR + "oscar",		 
		  OBJ_DIR + "hairspray"});
	break;
    case 9:
	list += ({OBJ_DIR + "chalice2",
		  OBJ_DIR + "death_amulet",
		  OBJ_DIR + "mecien_axe"});
	break;
    }

    if (charon_chest == i)
	list += ({OBJ_DIR + "charon_amulet"});

    return list;
}

/*
 * Function name: do_page
 * Description:   Handle the page action
 * Returns:       1/0
 */
public int
do_page(string str)
{
    string *items;
    string st;
    int len;
    int i;

    FIX_EUID;
    
    i = LANG_NUMW(str);
    if ((i < 1) || (i > 9)) {
	NF("There is no page number " + str + "\n");
	return 0;
    }
    i--;
    st = "List of stored treasures:\n" + "*=*=*=*=*=*=*=*=*=*=*=*=*\n";
    st += "storage " + str + "\n"; 

    items = query_chest_contents(i);    
    if ((len = sizeof(items)) == 0) {
	st += "<Empty>\n";
    }
    else 
	for (i = 0; i < len; i++) {
/*	    items[i]->teleledningsanka(); */

	    st += items[i]->query_short() + "\n"; 
	}
    write(st + "\n");
    return 1;
}
    
