/*
 * /d/Gondor/morgul/city/mm_stables/obj/rider_shadow.c
 *
 * Rider shadow modified to make the mounted rider appear as "black rider"
 * to those he hasn't met before.
 *
 * This module is strange in that it takes care of exactly the peculiarities
 * associated with moving while mounted. In the creation of steeds, normally
 * the steed is shown in the room and the player is not shown in the "composite"
 * description of the room. However, when moving it is the other way around,
 * namely the person is shown moving, and the horse is moved invisibly.
 *
 * Since the query_m_in/out is queried only once in move_living, we need to
 * put the description of the player with his horse in the name, whereas for
 * default steed movement the horse is described as integral part of the
 * m_in/out. We cannot use that in this case as for nonmet people we want to
 * compactly refer to the "black rider".
 *
 * Created by Mercade, November 2, 2002
 */

inherit "/d/Genesis/steed/new/rider_shadow";

#include <language.h>
#include <macros.h>

/*
 * Global variable. Used to keep track of whether we're moving or not.
 */
int is_moving = 0;

/*
 * Function name: query_mm_mounted
 * Description  : Identifies this player as a mounted mage.
 * Returns      : int 1 - always.
 */
int
query_mm_mounted()
{
    return 1;
}

/*
 * Function name: query_nonmet_name
 * Description  : If we are moving, then show us as "black rider" to people
 *                we have not met before. Otherwise just return the normal
 *                description.
 * Returns      : string - the description.
 */
string
query_nonmet_name()
{
    if (is_moving)
    {
        return "black rider";
    }
    else
    {
        return shadow_who->query_nonmet_name();
    }
}

string *parse_command_adjectiv_id_list()
{
    string* ids = shadow_who->parse_command_adjectiv_id_list();
    ids += ({ "black" });
    return ids;
}

string *parse_command_id_list()
{
    string* ids = shadow_who->parse_command_id_list();
    ids += ({ "rider" });
    return ids;
}  

string *parse_command_plural_id_list()
{
    string* ids = shadow_who->parse_command_plural_id_list();
    ids += ({ "riders" });
    return ids;
}


/*
 * Function name: query_name
 * Description  : When we aren't moving, return the normal name of the person.
 *                During movement, we want to describe the horse as integral
 *                part of the name since the nonmet description "black rider"
 *                refers to the complete rider/steed combo. A complicating
 *                factor is that we must have the sentences right for both the
 *                moving out and the moving in.
 *                To do this, we consider the fact that move_living() first
 *                prints the leaving message, then moves the person and prints
 *                the arrival message in the new room. Now, hereto we increase
 *                the is_moving variable to 2 as a flag to indicate that it is
 *                time to print the entrance message next.
 * Returns      : string - the name.
 */
string
query_name()
{
    if (is_moving)
    {   
        /* First out ... */
        if (is_moving == 1)
        {
            is_moving++;
            return shadow_who->query_name() +
                " spurs " + shadow_who->query_possessive() + " " +
                steed->steed_short() + " and";
        }
        /* ... then in. */
        else
        {
            return capitalize(LANG_ADDART(steed->steed_short())) + " with " +
                shadow_who->query_name() +
                " mounted";
        }
    }
    else
    {
        return shadow_who->query_name();
    }
}

/*
 * Function name: move_living
 * Description  : This routine is masked because we want to know when the
 *                person is moving. The reason for this is that we want to
 *                adjust his appearance. So before we start the actual move,
 *                set the move flag, and after we are done moving, reset it
 *                so that the normal name and nonmet description are printed
 *                again.
 * Arguments    : See move_living() original.
 * Returns      : See move_living() original.
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    is_moving = 1;

    catch(::move_living(how, to_dest, dont_follow, no_glance));

    is_moving = 0;
}
