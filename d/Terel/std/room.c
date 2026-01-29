/*
 * Terel standard room.
 *
 * All the rooms in the domain should inherit this room.  In the future
 * this can be used for weather, etc.
 *
 * Modifications
 *  12/12/2009 - Moved reset_room code into an alarm, to avoid possible
 *               runtime issues that are causing rooms to load incorrectly.
 *               (Petros)
 */

#include <macros.h>
inherit "/std/room";

#ifndef TO
# define TO      this_object()
#endif

/*
 * Global variables
 */
static object *mov_obj = ({ });

/*
 * Function name: create_terel_room
 * Description:   Configure this room
 */
public void
create_terel_room()     { }

/*
 * Function name: reset_terel_room
 * Description: Configure room's behavior on reset
 */
public void
reset_terel_room()      { }

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
    setuid();
    seteuid(getuid());

    if (!query_prop("_room_m_da_dragonsteed_no_land"))
    {
	add_prop("_room_m_da_dragonsteed_no_land",
            "You realize that summoning your dragon into these "+
            "lands would attract the attention of the great dragons "+
            "of Terel. Your dragon would surely die.\n");
    }

    create_terel_room();
}

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()             { return ({ }); }

/*
 * Function name: query_moving_object_list
 * Description:   return list of moving objects to clone at each reset.
 */
public string *
query_moving_object_list()      { return ({ }); }

public void
alarmed_reset_room()
{
    int i, j;
    object obj;
    string *object_list;
    mixed *objects_here;
    string *clone_list;

    object_list = query_object_list();

    if (i = sizeof(object_list))
    {
	clone_list = ({ });
	objects_here = map(all_inventory(TO), "convert_to_filename", TO);

	while (i--)
        {
	    j = member_array(object_list[i], objects_here);
	    if (j == -1)
		clone_list += ({ object_list[i] });
	    else
		objects_here = exclude_array(objects_here, j, j);
	}

	for (i = 0; i < sizeof(clone_list); i++)
        {
	    obj = clone_object(clone_list[i]);
	    obj->move(TO, 1);
	    if (living(obj))
		tell_room(environment(obj), QCTNAME(obj) + " arrives.\n");
	}
    }

    object_list = query_moving_object_list();

    if (j = sizeof(object_list))
    {
	for (i=0; i<j; i++)
        {
	    if (i < sizeof(mov_obj) && mov_obj[i])
                continue;

	    obj = clone_object(object_list[i]);

	    if (i < sizeof(mov_obj))
		mov_obj[i] = obj;
	    else
		mov_obj += ({ obj });

	    obj->move(TO, 1);
	    if (living(obj))
		tell_room(environment(obj), QCTNAME(obj) + " arrives.\n");
	}
    }

    set_searched(0); /* for herbs */
    reset_terel_room();
}

/*
 * Function name: reset_room
 * Description:   clone objects at each reset.
 */
public void
reset_room()
{
    set_alarm(0.0, 0.0, alarmed_reset_room);
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

/* This is insulting and unworthy of Genesis wizards.
 * Removed 5/31/2005 --Lilith
#define W_LOG "/d/Terel/log/wlog"
public void
enter_inv(object ob, object from)
{
   string str,domain,where;
   mixed rank;

    ::enter_inv(ob,from);
    if (ob->query_wiz_level())
    {
      where = file_name(ENV(ob));
      rank = WIZ_N[SECURITY->query_wiz_rank(ob->query_real_name())];
      domain = SECURITY->query_wiz_dom(ob->query_real_name());
      str = ob->query_real_name();
      str = str + ", " + rank + ", " + domain + ", " + where;
      if ((domain != "Terel") && (domain != "Khalakhor") && (domain != "Earthsea"))
	write_file(W_LOG, str + " (" + ctime(time()) + ")\n");
    }
}
*/
