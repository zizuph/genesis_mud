
/*  Work-Man's sign.
 *			Napture.
 */

#pragma save_binary

inherit "/std/object.c";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message)	break_string(message,70)
#define TP              this_player()
#define TO              this_object()

#define EXIT_DIRECTION  "south"
#define EXIT_SHORT      "s"

init()
{
    ::init();
    add_action("attempt_get", "get");
    add_action("attempt_get", "take");
    add_action("read_sign", "read");
    add_action("go_exit", EXIT_DIRECTION);
    add_action("go_exit", EXIT_SHORT);
}

create_object()
{
    set_name("sign");
    add_adj(({"small", "workman", "workmans", "workman's"}));
    set_short("small workman's sign blocking the way to the "
              + EXIT_DIRECTION);
    set_pshort("small signs belonging to workmen");
    set_long("It is a small sign:\n\n" +
	"           ________________________________\n" +
	"           |                              |\n" +
	"           |        Gnomes at work        |\n" +
	"           |                              |\n" +
	"           |   Do NOT pass this notice!   |\n" +
	"           |                              |\n" +
	"           --------------------------------\n" +
	"                          |                \n" +
	"                          |                \n" +
	"                          |                \n" +
	"                         / \\               \n");

    add_prop(OBJ_I_NO_GET, 1);
}

/* are the workman's trousers falling down? */
trousers()
{
    string tmp;
    
    if (random(2))  tmp="The gnome then leaves shaking his head.\n";
        else  tmp="The gnome then leaves with his trousers falling down!\n";
    write(tmp);
    say  (tmp);
}

read_sign(string str)
{
    object ob1;
    
    if (!str || (!parse_command(str, environment(TP), "%o", ob1)))  return 0;
    if (ob1!=TO)  return 0;

    write("The sign tells you not to go this way.\n");
    say(QCTNAME(TP) + " peers at the sign.\n");
    return 1;
}

attempt_get(string str)
{
    object ob1;

    if (!str || (!parse_command(str, environment(TP), "%o", ob1)))  return 0;
    if (ob1!=TO)  return 0;

    say(QCTNAME(TP) + " attempts to grab the sign!\nAs " +
           TP->query_possessive() + " hands touch the sign, a tiny " +
           "gnome wearing strange overalls\nand a funny looking hat that " +
           "doesn't quite fit properly arrives.\nThe gnome waves his hands " +
           "at " + QCTNAME(TP) + ".\nForcing " + TP->query_pronoun() +
           " to be hurled against the floor.\n");
    write(BS("As you attempt to grab the sign, a tiny gnome appears " +
              "wearing strange overalls and a funny looking hat.  He " +
              "sends you flying away from the sign with a single wave " +
              "of his hands.\n"));
    trousers();
    return 1;
}

go_exit()
{
    say("As " + QCTNAME(TP) + " attempts to leave " + EXIT_DIRECTION +
        ",\na small gnome appears, saying: \"Can't you read?\".\n" +
        "The gnome then leaves, pointing at the sign.\n");
    write(BS("As you start to leave " + EXIT_DIRECTION + ", a small " +
             "gnome appears and tells you: \"Can't you read?\".  " +
             "The gnome then leaves, pointing at the sign.\n"));
    return 1;
}

          