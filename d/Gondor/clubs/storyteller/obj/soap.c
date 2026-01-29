/*
 * /d/Gondor/clubs/storytellers/obj/.c
 * Borrowed from:
 * /d/Gondor/common/guild/north/obj/soap.c
 *
 * Soap for the northern guild's baths -- Gnadnar March 98
 * Soap for the Storyteller's club bath.
 *
 */

#pragma strict_types

inherit "/std/object";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define BATHING			"i_am_bathing"
#define	SOAP_ID			"_northern_baths_soap"

public void	create_object();
public void	init();
public void	do_lather(string arg);
public void	do_smell(string arg);


/*
 * Function name:	create_object
 * Description	:	set up the bar of soap
 */
public void
create_object()
{
    set_name("soap");
    add_name( ({ "bar", "bar of soap", SOAP_ID }) );
    set_pname("soaps");
    add_pname( ({ "bars", "bars of soap" }) );
    set_short("bar of soap");
    set_pshort("bars of soap");
    set_long("The oblong bar of soap is fairly soft, and "+
	"sweetly scented.\n");
    add_prop(OBJ_I_WEIGHT, 113);	/* 4 oz */
    add_prop(OBJ_I_VOLUME, 98);		/* 3x2x1 inches */
    add_prop(OBJ_I_VALUE, 0);
} /* create_object */

/* 
 * Function name:	init
 * Description	:	add player verbs
 */
public void
init()
{
    ::init();
    add_action(do_lather, "soap");
    add_action(do_lather, "lather");
/*
    add_action(do_lather, "wash");
    add_action(do_lather, "bathe");
*/
    add_action(do_smell, "smell");
    add_action(do_smell, "sniff");
} /* init */

/*
 * Function name:	do_lather
 * Description	:	handle attempts to soap/lather me
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_lather(string arg)
{
    object	tp = TP,
		*who;
    string	vb = QVB;
   
    if (ENV(TO) != tp)
    {
	/* soap is not in player's inv */
	return 0;
    }

    if ((vb == "wash" ||
	 vb == "bathe") &&
	file_name(ENV(tp)) == RANGER_NORTH_DIR+"bathroom")
    {
	/* let bathroom handle wash/bathe */
	return 0;
    }
    if (!strlen(arg) ||
        arg == "me" ||
	arg == "myself" ||
	LOW(arg) == tp->query_real_name())
    {
	if (!tp->query_prop(BATHING))
	{
	    NF0("But you aren't in a tub!\n");
	}
	write("You lather yourself with soap.\n");
	SAY(" lathers "+OBJECTIVE(tp)+"self with soap.");
	return 1;
    }
    if (parse_command(arg, all_inventory(ENV(tp)), "%l", who) &&
        sizeof(who = NORMAL_ACCESS(who, 0, 0)))
    {
	if (!who[0]->query_prop(BATHING))
	{
	    NF0(CAP(PRONOUN(who[0])) + " isn't bathing.\n");
	}
        write("You lather " + who[0]->query_the_possessive_name(tp) +
            " back.\n");
	who[0]->catch_tell(tp->query_The_name(who[0]) + " lathers " +
            "your back.\n");
	say(QCTNAME(tp)+" lathers " + QTPNAME(who[0]) + " back.\n",
	    ({ who[0], tp }));
	return 1;
    }
    NF0(CAP(arg) + " isn't here.\n");
} /* do_lather */

/*
 * Function name:	do_smell
 * Description	:	handle attempts to smell/sniff soap
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_smell(string arg)
{
    object	ob;
    if (!strlen(arg) ||
	!parse_command(arg, ({ TO }), "%o", ob))
    {
	NF0(CAP(QVB)+" what?\n");
    }
    write("The soap has a faint fragrance of lavender.\n");
    SAY(" "+QVB+"s a bar of soap.");
    return 1;
} /* do_smell */
