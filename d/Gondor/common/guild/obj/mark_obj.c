/*
 * /d/Gondor/common/guild/obj/mark_obj.c
 *
 * This is the mark left by a ranger if he wishes to leave a mark with a
 * secret ranger message for someone.
 *
 * /Mercade, 13 April 1994
 *
 * Revision history:
 */

#pragma save_binary

inherit "/std/object";

#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define MARK_OBJ          "_secret_ranger_mark_"

#define TRACKING_ALWAYS    50
#define WIS_CLUE           50
#define SECONDS_PER_LEVEL  60
#define BASE_SECONDS      600

#define MESSAGES ({ "I WAS HERE", "WAIT HERE", "DANGER", "FOLLOW ME" })

static private string my_name;
static private string for_name;
static private string exit;
static private int    message;
static private int    skill;
static private status tmp_check = 0;
static private object gotten_by;

void
create_object()
{
    set_name("mark");
    add_name( ({ "rock", "twig", "stick", MARK_OBJ }) );
    set_pname( ({ "marks", "rocks", "twigs", "sticks", MARK_OBJ }) );
    set_adj("secret");
    add_adj("ranger");
    add_adj("small");
    add_adj("uninteresting");

    set_long("@@long_description@@");

    /*
     * This is sneaky and ugly, but it suits my needs. By immitating a
     * heap, we can return the short we want to use whatever the short
     * is. It will take care of the obnoxious "a" added to every singular
     * short.
     */
    add_prop(HEAP_I_IS        ,   1);
    add_prop(HEAP_S_UNIQUE_ID , MARK_OBJ);

    add_prop(OBJ_I_VALUE      ,   0);
    add_prop(OBJ_I_VOLUME     , 350);
    add_prop(OBJ_I_WEIGHT     , 550);
    add_prop(OBJ_M_NO_BUY     ,   1);
    add_prop(OBJ_M_NO_DROP    ,   1);
    add_prop(OBJ_M_NO_GET     , "@@obj_m_no_get@@");
    add_prop(OBJ_M_NO_SELL    ,   1);
    add_prop(OBJ_M_NO_STEAL   ,   1);
    add_prop(OBJ_M_NO_TELEPORT,   1);
    add_prop(OBJ_S_WIZINFO    ,
        BSN("This object is a secret mark left here by a ranger for other " +
        "rangers to be found. Non-rangers will not be able to see the " +
        "object, though it they find it, they will not be able to tell what " +
        "it is. Coded by /Mercade."));
}

/*
 * Function name: check_number_of_marks
 * Description  : This ugly function counts the number of marks in the
 *                environment of this mark.
 * Returns      : int - the number of marks other than this one.
 */
int
check_number_of_marks()
{
    object *inv    = all_inventory(environment()) - ({ this_object() });
    int    *checks = (int *)inv->set_tmp_secret_ranger_mark_check();

    return sizeof(checks - ({ 0 }) );
}

varargs mixed
short(mixed tp)
{
    if (tmp_check)
    {
	return 0;
    }

    if (!objectp(tp))
    {
        tp = TP;
    }

    if (!objectp(tp))
    {
        return "something";
    }

    if (!(IS_RANGER(tp)))
    {
        return (query_prop(OBJ_I_HIDE) ? 0 : "some small rocks and twigs");
    }

    if ((query_verb() == "look") && (check_number_of_marks() > 0))
    {
	return "some secret marks, left by rangers";
    }

    return "a secret mark, left by a ranger";
}

#if 0
varargs mixed
pshort(mixed tp)
{
    if (!objectp(tp))
    {
        tp = TP;
    }

    if (!objectp(tp))
    {
        return "something";
    }

    if (!(IS_RANGER(tp)))
    {
        return (query_prop(OBJ_I_HIDE) ? 0 : "some small rocks and twigs");
    }

    return "some secret marks, left by rangers";
}
#endif

/*
 * Function name: understand
 * Description  : This function will return whether you are able to
 *                understand the mark. If either you or the sender has a
 *                low tracking skill, you cannot make out the message.
 * Returns      : 1/0 - success/failure
 */
status
understand()
{
    int    tracking = TP->query_skill(SS_TRACKING);
    status chance1  = (random(75) >= (TRACKING_ALWAYS - skill));
    status chance2  = (random(75) >= (TRACKING_ALWAYS - tracking) / 2);

    return (chance1 & chance2);
}

string
long_description()
{
    string long   = "You carefully examine the rocks and twigs. ";
    string *exits = ENV()->query_exit_cmds();
    object tp     = TP;

    if (!(IS_RANGER(tp)))
    {
        long += ((tp->query_stat(SS_WIS) > WIS_CLUE) ?
            "They appear to form some kind of message, but you fail to " +
            "make out what it means, if indeed they form one." :
            "They look rather unintersting to you.");

        return BSN(long);
    }

    long += "They appear to form a secret ranger message";
    long += ((my_name == 0) ? " without sender. " :
        (understand() ? (" from " +
            ((my_name == tp->query_real_name()) ? "you" :
                capitalize(my_name)) +
            ". ") :
        ", but you fail to see from whom. "));

    long += "It says \"" + (understand() ?
        MESSAGES[message] :
        ONE_OF_LIST(MESSAGES)) + "\". ";

    long += "The message is " + ((for_name == 0) ?
        "not meant for anyone in particular. " :
        (understand() ? ("meant for " +
            ((for_name == tp->query_real_name()) ?
            "you. " : (capitalize(for_name) + ". "))) :
        "meant for someone, but you cannot make out for whom. "));

    if ((exit != 0) && (exit != "here"))
    {
        long += "You also see an arrow pointing " +
            (understand() ? exit :
            ((sizeof(exits)) ? ONE_OF_LIST(exits) :
                "in a general direction")) + ".";
    }

    return BSN(long);
}

mixed
obj_m_no_get()
{
    gotten_by = TP;
    set_alarm(0.2, 0.0, "remove_object");
    write("As you try to " + query_verb() + " the " + short() +
        ", you mess it up and therewith erase it.\n");
    return 0;
}

void
set_my_name(string str)
{
    my_name = str;
}

void
set_for_name(string str)
{
    for_name = str;
}

void
set_exit(string str)
{
    exit = str;
}

void
set_message(int i)
{
    message = i;
}

void
set_skill(int i)
{
    skill = i;

    set_alarm(itof(BASE_SECONDS + (skill * SECONDS_PER_LEVEL)), 0.0,
	"blow_away");
}

void
blow_away()
{
    tell_room(ENV(), BSN("A mild breeze blows through the area. Small " +
	"sticks and leaves blow along the ground."));
}

void
set_hide(int hide)
{
    int room = ENV()->query_prop(OBJ_I_HIDE);

    if ((room < 0) || (room >= hide))
    {
        return;
    }

    hide -= room;
    hide /= 2;
    hide += random(hide);

    add_prop(OBJ_I_HIDE, hide);
}

status
set_tmp_secret_ranger_mark_check()
{
    tmp_check = 1;

    set_alarm(0.5, 0.0, "reset_tmp_secret_ranger_mark_check");

    return 1;
}

void
reset_tmp_secret_ranger_mark_check()
{
    tmp_check = 0;
}

void
remove_object()
{
    if ( ENV() == gotten_by )
    {
	tell_object(gotten_by, 
	    "The secret mark is useless now; you toss it away.\n");
    }
    ::remove_object();
}
