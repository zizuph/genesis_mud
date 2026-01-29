/* Navarre July 3rd 2006, fixed typo, changed uncontrolably to uncontrollably. */

inherit "/std/drink";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

int old_size;


create_drink()
{
    set_soft_amount(50);
    set_alco_amount(50);
    set_name("Draught of Doom");
    add_name("draught");
    set_short("Draught of Doom");
    set_pshort("Draughts of Doom");
    set_long("This is a so called Draught of Doom. You wonder why "
      + "though, it is just a clear liquid in a small bottle. "
      + "It looks almost as harmless as water. Who knows ? " 
      + "Maybe you should smell it, just to make sure.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);

    seteuid(getuid());
}

void
init()
{
    ::init();
    ADA("smell");
}

int
smell(string str)
{
    NF("Smell what?\n");

    if (!str)
	return 0;

    if (str != "Draught of Doom" && str != "draught")
	return 0;

    TP->catch_msg("You stagger uncontrollably backwards as you "
      + "get a whiff of the contents of the small bottle of "
      + "Draught of Doom. That stuff is vicious! You almost "
      + "passed out.\n");
    tell_room(E(TP), QCTNAME(TP)+ " staggers uncontrollably backwards "
      + "as " + PRONOUN(TP) + " smells the contents of a small bottle "
      + "of clear liquid.\n", ({TO, TP}));

    return 1;
}


string
cause_pass_out(object who)
{
    if (living(who));
    {
	clone_object(SOBJ + "pass_out_object")->move(who);
    }
    return "";
}


void
special_effect(int numofdrinks)
{
    set_alarm(3.0, 0.0, cause_pass_out(TP));
}
