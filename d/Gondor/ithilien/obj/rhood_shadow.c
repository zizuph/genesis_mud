/*
 * /d/Gondor/ithilien/obj/rhood_shadow.c
 *
 * This shadow will be added to the player that masks his face with the hood
 * of the rangers of ithilien. It serves several purposes. The shadow will
 * add the command 'unmask' to the players that encounter the hooded player
 * to enable him to unmask the player. Also, several destriptions will be
 * added to give nice descriptions.
 *
 * /Mercade, 20 October 1993
 *
 * Revision History:
 */

inherit "/std/shadow";

#include "/d/Gondor/defs.h"
#include <living_desc.h>
#include <ss_types.h>
#include <tasks.h>

#define LIVE_I_I_MASKED_MY_FACE_WITH_A_HOOD \
      "_live_i_i_masked_my_face_with_a_hood"
#define LIVE_O_PREVIOUS_OBJECT "_live_o_previous_object" 

#define MASKED_DESCRIPTION "hooded and masked"
#define MAXIMUM_STATS_TO_GET_A_CHANCE 20

#define QSW query_shadow_who()

/*
 * Function name: init_living
 * Description  : This function will add the command 'unmask' to other
 *                players that will encounter this_player().
 */
void
init_living()
{
    QSW->init_living();

    add_action("do_unmask_hooded_player", "unmask");
}

/*
 * Function name: do_unmask_hooded_player
 * Description  : This function will be used to unmask a hooded player.
 * Arguments    : string str - the command string added to 'unmask'
 * Returns      : int - 1 on success, 0 on failure
 */
int
do_unmask_hooded_player(string str)
{
    NFN("You cannot unmask anyone yet.");
    return 0;
}

/*
 * Function name: my_previous_object
 * Description  : This function will return the object that wants to know the
 *                (non)met description of this player. It will always return
 *                an objectpointer, either the player who really wants to know
 *                or a pointer to 'this_player()'
 * Returns        object - the objectpointer who wants to know.
 */
object
my_previous_object()
{
    object prevo = (object)(QSW->query_prop(LIVE_O_PREVIOUS_OBJECT));

    if (objectp(prevo))
    {
        return prevo;
    }

    return TP; /* maybe I should return this_object rather than this_player */
}

/*
 * Function name: hooded_description
 * Description  : This function will return the 'hooded' description of
 *                the shadowed player.
 * Returns      : string - the mentioned description
 */
string
hooded_description()
{
    return (string)(MASKED_DESCRIPTION + " " + QSW->query_race_name() +
        (QSW->query_wiz_level() ? (" " + LD_WIZARD) : ""));
}

/*
 * Function name: query_met_name
 * Description  : If you do know someone who is hooded, there are several
 *                possibilities to see whether you can recognize him/her
 *                or whether you get his hooded description.
 */
public string 
query_met_name()
{
    object prevo = my_previous_object();

    /* a wizard will always get the name */
    if (prevo->query_wiz_level())
    {
        return QSW->query_met_name();
    }

    if (0 < prevo->resolve_task(
        TASK_DIFFICULT,
        ({ SKILL_WEIGHT, 70, SS_AWARENESS,
           SKILL_WEIGHT, 50, TS_INT,
           SKILL_WEIGHT, 70, SS_APPR_OBJ }),
        QSW,
        ({ SKILL_WEIGHT, 70, SS_HIDE,
           SKILL_WEIGHT, 50, TS_DEX }) ))
    {
        return QSW->query_met_name();
    }

    /*
     * If you are a newbie player you get a chance regardless your skills,
     * though even the few skills that you have will help you.
     */
    if ((prevo->query_average_stat() <= MAXIMUM_STATS_TO_GET_A_CHANCE) &&
        (0 < prevo->resolve_task(
        TASK_ROUTINE,
        ({ SS_AWARENESS,
           TS_INT,
           SS_APPR_OBJ }),
        QSW,
        ({ SKILL_WEIGHT, 35, SS_HIDE,
           SKILL_WEIGHT, 25, TS_DEX }) )))
    {
        return QSW->query_met_name();
    }

    return hooded_description();
}

/*
 * Function name: query_nonmet_name
 * Description  : If you don't know someone who is hooded, you will always
 *                get his/her hooded description.
 * Returns      : the hooded description
 */
public string
query_nonmet_name()
{
    return hooded_description();
}

/*
 * Function name: query_art_name
 * Description  : All this function does is save the object that wants to
 *                know the description.
 */
public varargs string 
query_art_name(object pobj = previous_object())
{
    QSW->add_prop(LIVE_O_PREVIOUS_OBJECT, pobj);

    return QSW->query_art_name(pobj);
}

/*
 * Function name: query_the_name
 * Description  : All this function does is save the object that wants to
 *                know the description.
 */
public varargs string
query_the_name(object pobj = previous_object())
{
    QSW->add_prop(LIVE_O_PREVIOUS_OBJECT, pobj);

    return QSW->query_the_name(pobj);
}

/*
 * Function name: short
 * Description  : All this function does is save the object that wants to
 *                know the description.
 */
public varargs string 
short(object for_obj = this_player())
{
    QSW->add_prop(LIVE_O_PREVIOUS_OBJECT, for_obj);

    return QSW->short(for_obj);
}

/*
 * Function name: long
 * Description  : All this function does is save the object that wants to
 *                know the description
 */
public varargs string 
long(mixed for_obj)
{
    if (objectp(for_obj))
    {
        QSW->add_prop(LIVE_O_PREVIOUS_OBJECT, for_obj);
    }
    else
    {
        QSW->add_prop(LIVE_O_PREVIOUS_OBJECT, TP);
    }

    return QSW->long(for_obj);
}    

/*
 * Function name: remove_rhood_shadow
 * Description  : This function is called to get rid of the shadow and to make
 *                sure that no other shadows are removed from the player.
 */
void
remove_rhood_shadow()
{
    destruct();
}


