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
 * Global variables
 */
static object *mov_obj = ({ });

public string *query_object_list();
public string *query_moving_object_list();

/*
 * Function name: create_terel_room
 * Description:   Configure this room
 */
public void
create_terel_room()
{
}

/*
 * Function name: create_room
 * Description:   This should be nomask, but since existing Terel rooms
 *                already mask it, that's impractical.  We'll have to hope
 *                that most of them call ::create_room().  New rooms should
 *                *not* use this function to configure themselves; instead,
 *                they should use create_terel_room()
 */
public void
create_room()
{
    /* Resets are turned on by default since we have reset_room() defined.
     * We want to turn them off, though, if we don't have anything to clone.
     */
    if (!sizeof(query_object_list()) && !sizeof(query_moving_object_list()) &&
        (function_exists("reset_room", this_object()) == STDROOM))
    {
        enable_reset(0);
    }

    create_terel_room();
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
 * Function name: query_moving_object_list
 * Description:   return list of moving objects to clone at each reset.
 */
public string*
query_moving_object_list()
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
    
    if (i = sizeof(object_list)) {

        clone_list = ({ });
        objects_here = map(all_inventory(TO), "convert_to_filename", TO);

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
            obj->move(TO, 1);
	    if (living(obj))
	    {
		tell_room(environment(obj), QCTNAME(obj) + " arrives.\n");
	    }
        }
    }
    
    object_list = query_moving_object_list();
    
    
    if (j = sizeof(object_list)) {
        seteuid(getuid());
        for (i=0; i<j; i++) {
            if (i < sizeof(mov_obj) && mov_obj[i]) continue;
        
            obj = clone_object(object_list[i]);
        
            if (i < sizeof(mov_obj))
                mov_obj[i] = obj;
            else
                mov_obj += ({ obj });

            obj->move(TO, 1);
	    if (living(obj))
	    {
		tell_room(environment(obj), QCTNAME(obj) + " arrives.\n");
	    }
        }
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
