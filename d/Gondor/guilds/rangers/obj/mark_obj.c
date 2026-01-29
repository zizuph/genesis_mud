/*
 * /d/Gondor/guilds/rangers/obj/mark_obj.c
 *
 * This is the mark left by a ranger if he wishes to leave a mark with a
 * secret ranger message for someone.
 *
 * /Mercade, 13 April 1994
 *
 * Revision history:
 * Moved to /d/Gondor/guilds/rangers/obj/mark_obj.c
 * Gwyneth 20 April 2001
 */
inherit "/std/object";

#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

#define MARK_OBJ          "_secret_ranger_mark_"

#define TRACKING_ALWAYS    50
#define WIS_CLUE           50
#define SECONDS_PER_LEVEL  60
#define BASE_SECONDS       600

#define MESSAGES ({ "I WAS HERE", "WAIT HERE", "DANGER", "FOLLOW ME" })

static private string MyName;
static private string ForName;
static private string Exit;
static private int    Message;
static private int    Skill;
static private status TmpCheck = 0;
static private object GottenBy;

string long_description();
mixed obj_m_no_get();

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

    set_long(&long_description());

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
    add_prop(OBJ_M_NO_GET     , &obj_m_no_get());
    add_prop(OBJ_M_NO_SELL    ,   1);
    add_prop(OBJ_M_NO_STEAL   ,   1);
    add_prop(OBJ_M_NO_TELEPORT,   1);
    add_prop(OBJ_S_WIZINFO    ,
        "This object is a secret mark left here by a ranger for other " +
        "rangers to be found. Non-rangers will not be able to see the " +
        "object, though it they find it, they will not be able to tell what " +
        "it is. Coded by /Mercade.\n");
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
    object *inv = all_inventory(environment()) - ({ this_object() });
    int *checks = (int *)inv->set_tmp_secret_ranger_mark_check();

    return sizeof(checks - ({ 0 }) );
}

varargs mixed
short(mixed tp)
{
    if (TmpCheck)
        return 0;

    if (!objectp(tp))
        tp = TP;

    if (!objectp(tp))
        return "something";

    if (!(RANGERS_MEMBER(tp)))
        return (query_prop(OBJ_I_HIDE) ? 0 : "some small rocks and twigs");

    if ((query_verb() == "look") && (check_number_of_marks() > 0))
        return "some secret marks, left by rangers";

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
    int tracking    = TP->query_skill(SS_TRACKING);
    status chance1  = (random(75) >= (TRACKING_ALWAYS - Skill));
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

        return (long + "\n");
    }

    long += "They appear to form a secret ranger message";
    long += ((MyName == 0) ? " without sender. " :
        (understand() ? (" from " +
            ((MyName == tp->query_real_name()) ? "you" :
                capitalize(MyName)) +
            ". ") :
        ", but you fail to see from whom. "));

    long += "It says \"" + (understand() ?
        MESSAGES[Message] :
        ONE_OF_LIST(MESSAGES)) + "\". ";

    long += "The message is " + ((ForName == 0) ?
        "not meant for anyone in particular. " :
        (understand() ? ("meant for " +
            ((ForName == tp->query_real_name()) ?
            "you. " : (capitalize(ForName) + ". "))) :
        "meant for someone, but you cannot make out for whom. "));

    if ((Exit != 0) && (Exit != "here"))
    {
        long += "You also see an arrow pointing " +
            (understand() ? Exit :
            ((sizeof(exits)) ? ONE_OF_LIST(exits) :
                "in a general direction")) + ".";
    }

    return (long + "\n");
}

mixed
obj_m_no_get()
{
    GottenBy = TP;
    set_alarm(0.2, 0.0, "remove_object");
    write("As you try to " + query_verb() + " the " + short() +
        ", you mess it up and therewith erase it.\n");
    return 0;
}

void
set_my_name(string str)
{
    MyName = str;
}

void
set_for_name(string str)
{
    ForName = str;
}

void
set_exit(string str)
{
    Exit = str;
}

void
set_message(int i)
{
    Message = i;
}

void
blow_away()
{
    tell_room(ENV(), "A mild breeze blows through the area. Small " +
        "sticks and leaves blow along the ground.\n");
}

void
set_skill(int i)
{
    Skill = i;

    set_alarm(itof(BASE_SECONDS + (Skill * SECONDS_PER_LEVEL)), 0.0,
        &blow_away());
}

void
set_hide(int hide)
{
    int room = ENV()->query_prop(OBJ_I_HIDE);

    if ((room < 0) || (room >= hide))
        return;

    hide -= room;
    hide /= 2;
    hide += random(hide);

    add_prop(OBJ_I_HIDE, hide);
}

void
reset_tmp_secret_ranger_mark_check()
{
    TmpCheck = 0;
}

status
set_tmp_secret_ranger_mark_check()
{
    TmpCheck = 1;

    set_alarm(0.5, 0.0, &reset_tmp_secret_ranger_mark_check());

    return 1;
}

void
remove_object()
{
    if ( ENV() == GottenBy )
    {
        tell_object(GottenBy, 
            "The secret mark is useless now; you toss it away.\n");
    }

    ::remove_object();
}
