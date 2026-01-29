/*
 * /d/Gondor/lebennin/sirith/master.c
 *
 * adds itself to /d/Gondor/common/master.c's msg_place list when loaded.
 * notifies sirith rooms that need to know about sunrise/sunset.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "/d/Gondor/defs.h"
#include "defs.h"		/* for SIRITH_FARMS_DIR, SIRITH_MASTER */

/* if change this, also change reset_msg_places() at end of file */
string *msg_place = ({
		       SIRITH_FARMS_DIR+"farm2/trees",
		       SIRITH_FARMS_DIR+"farm1/trees",
		       SIRITH_FARMS_DIR+"farm2/barn",
		       SIRITH_FARMS_DIR+"farm1/barn2",
                    });


/* prototypes */
public void	create_object();
public void	sunrise();
public void	sunset();
public int	query_msg_place(string place_str);
public int	add_msg_place(string place_str);
public int	remove_msg_place(string place_str);
public string	reset_msg_places();
public string	*query_msg_places();


/*
 * Function name:	create_object
 * Description	:	set up the master object
 */
public void
create_object()
{
    string myname;

    set_short("the Master-object of Sirith in Gondor");
    set_long("This object is not supposed to be cloned.\n");
    FIX_EUID;
    myname = file_name(TO);
    (COMMON_DIR+"master")->add_msg_place(myname);

    /* paranoia, perhaps, but not very expensive and could be
     * useful if files get out of sync
     */
    if (myname != SIRITH_MASTER)
    {
	ERR_LOG("master object '"+myname+
	    "' differs from #define'd SIRITH_MASTER '"+SIRITH_MASTER+"'\n");
    }
} /* create_object */


/*
 * Function name:	sunrise
 * Description	:	call sunrise() in our list of places
 */
public void
sunrise()
{
    int n;
    object place;
    restore_object(file_name(TO));
    if (!pointerp(msg_place))
    {
        return;
    }
    n = sizeof(msg_place);
    while (n-- > 0)
    {
        place = find_object(msg_place[n]);
        place->short();
        place->sunrise();
    }
    return;
} /* sunrise */


/*
 * Function name:	sunset
 * Description	:	call sunset() in our list of places
 */
public void
sunset()
{
    int n;
    object place;
    restore_object(file_name(TO));
    if (!pointerp(msg_place))
    {
        return;
    }
    n = sizeof(msg_place);
    while (n-- > 0)
    {
        place = find_object(msg_place[n]);
        place->short();
        place->sunset();
    }
    return;
} /* sunset */


/*
 * Function name:	query_msg_place
 * Description	:	is arg in our list of places?
 * Arguments	:	string place_str -- the place to find
 * Returns	:	int -- 1 if place_str is in our list of places
 *			       0 if it is not
 */
public int
query_msg_place(string place_str)
{
    if (!place_str ||
	!stringp(place_str))
    {
        return 0;
    }
    restore_object(file_name(TO));
    if (member_array(place_str, msg_place) == -1)
    {
        return 0;
    }
    return 1;
} /* query_msg_place */


/*
 * Function name:	add_msg_place
 * Description	:	add arg to our list of places
 * Arguments	:	string place_str -- the place to add
 * Returns	:	1 if added, 0 if not
 */
public int
add_msg_place(string place_str)
{
    if (!place_str ||
	!stringp(place_str) ||
        query_msg_place(place_str))
    {
        return 0;
    }
    if (sizeof(msg_place) < 1)
    {
        msg_place = ({place_str});
    }
    else
    {
        msg_place += ({place_str});
    }
    save_object(file_name(TO));
    return 1;
} /* add_msg_place */


/*
 * Function name:	remove_msg_place
 * Description	:	remove arg from our list of places
 * Arguments	:	string place_str - the place to remove
 * Returns	:	1 if found and removed, 0 if not
 */
public int
remove_msg_place(string place_str)
{
    int n;
    if (!place_str ||
	!stringp(place_str))
    {
        return 0;
    }
    if ((n = member_array(place_str, msg_place)) == -1)
    {
        return 0;
    }
    msg_place = exclude_array(msg_place,n,n);
    save_object(file_name(TO));
    return 1;
} /* remove_msg_place */


/*
 * Function name:	reset_msg_places
 * Description	:	reset to default list of places
 * Returns	:	string "Places reset." (why??)
 */
public string
reset_msg_places()
{
    msg_place = ({ 
		   SIRITH_FARMS_DIR+"farm2/trees",
		   SIRITH_FARMS_DIR+"farm1/trees",
		   SIRITH_FARMS_DIR+"farm2/barn",
		   SIRITH_FARMS_DIR+"farm1/barn2",
                });
    save_object(file_name(TO));
    return "Places reset.";
} /* reset_msg_places */


/*
 * Function name:	query_msg_places
 * Description	:	query our list of places
 * Returns	:	string * -- the list
 */
public string *
query_msg_places()
{
    restore_object(file_name(TO));
    return msg_place;
} /* query_msg_places */
