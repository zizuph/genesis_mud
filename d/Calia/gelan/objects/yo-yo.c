/* 	this is a object of gelan

    coder(s):   Deinonychus

    history:	DD.MM.YY	what done			who did
    		15.04.93	created				Deinonychus

    purpose:    fun

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/


inherit "/std/object";
#include "object.h"
#include <stdproperties.h>
#include <macros.h>

create_object()
{
    /* descriptions */

    set_name("yo-yo");
    set_short("yo-yo");
    set_pshort("yo-yos");
    set_long("It's a wooden blue painted yo-yo. On one side you see "
	     + "the sign of Gelan on the other are the words 'yair' "
	     + "and 'ysleep' written.\n");

    /* properties */

    add_prop(OBJ_I_VALUE, 12);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 60);

} /* create_object */

void
init()
{
    add_action("ysleep", "ysleep");
    add_action("yair", "yair");
}

int
ysleep()
{
    say(QCTNAME(TP) + " hurls a yo-yo down to the floor.\n" +
	"Suddenly it stops and starts to turn very fast near the ground.\n" +
	"As unexpected as it stopped it rolls back an lands in the\n" +
	"throwers hand.\nYou watch amazed!\n");
    write(BS("You hurl down the yo-yo to the floor. Then it suddenly stops " +
	"and starts to turn very fast near the ground. With a tight movement " +
        "of your finger you roll it back and it lands in your hand.\n"));
    return 1;
}

int
yair()
{
    say(QCTNAME(TP) + " throws a yo-yo high in the air.\n" +
	"As all of the cord is rolled out, the yo-yo falls very\n" +
	"tenderly down to the floor while rolling back into the\n" +
	"throwers hand.\nBoy, what a toy!\n");
    write(BS("You throw the yo-yo high in the air. As all of the cord is " +
        "rolled out, the yo-yo falls very tenderly down to the floor " +
        "while rolling back into your hand.\n"));
    return 1;
}

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
