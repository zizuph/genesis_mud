/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * Terel standard room.
 *
 * All the rooms in the domain should inherit this room.  In the future
 * this can be used for weather, etc.
 */

#include "/d/Terel/include/Terel.h"
inherit "/std/room";

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */

public void
init()
{
    ::init();
/*    add_action("do_smell",  "smell",  0);*/
}

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({ });
}

/*
 * Function name: reset_room
 * Description:   clone objects at each reset.
 */
public void
reset_room()
{
    int i, j;
    object obj;
    string *object_list;
    mixed *objects_here;
    string *clone_list;

    set_searched(0); /* for herbs */

    object_list = query_object_list();
    if (sizeof(object_list) == 0)
	return;

    clone_list = ({ });
    objects_here = map(all_inventory(TO), "convert_to_filename", TO);
    
    i = sizeof(object_list);
    while (i--) {
	j = member_array(object_list[i], objects_here);
	if (j == -1)
	    clone_list += ({ object_list[i] });
	else
	    objects_here = exclude_array(objects_here, j, j);
    }

    seteuid(getuid());    
    for (i = 0; i < sizeof(clone_list); i++) {
	
	obj = clone_object(clone_list[i]);
	if (living(obj)) {
	    if (function_exists("equip_me", obj)) 
		obj->equip_me();
	    if (function_exists("equip_actions", obj)) 
		obj->equip_actions();	    
	    obj->move_living("arrives", TO);
	}
	else
	    obj->move(TO, 1);
    }
}

string
convert_to_filename(object ob)
{
    return MASTER_OB(ob);
}

string *
query_herb_list()
{

/*
 * List of herbs.  athelas and some others are not listed on the advice
 * of Olorin.
 */
    
    string *herbs = ({
	"angurth",
	"attanar",
	"basil",
	"blueberry",
	"blung",
	"bpotato",
	"caraway",
	"catnip",
	"chervil",
	"clove",
	"culkas",
	"curugwath",
	"dill",
	"fennel",
	"foxglove",
	"frostheal",
	"garlic",
	"ginger",
	"gonion",
	"hemlock",
	"holly",
	"laurel",
	"lothore",
	"madwort",
	"marjoram",
	"mint",
	"morgurth",
	"myrtle",
	"oregano",
	"red_pepper",
	"redweed",
	"rosemary",
	"rpotato",
	"saffron",
	"sage",
	"savory",
	"seregon",
	"sumac",
	"suranie",
	"tarragon",
	"thyme",
	"tyelka",
	"ungolestel"
	});

    return herbs;
}
