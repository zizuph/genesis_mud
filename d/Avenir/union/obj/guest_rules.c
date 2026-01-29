#pragma strict_types
// file name:	guest_rules.c	
// creator(s): 	Lilith Feb 2004
// last update:	
// purpose:	to educate visitors to the halls
/*
 * Revisions:
 *   Lucius Jun 2016: Modified to use Text blocks.
 *
 */
inherit "/std/scroll";

#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"

// Kept as a failsafe.
#define TEXT "This is a piece of vellum, inscribed in simple common "+ \
    "with the following words:\n\n"+ \
    "    Terms of Welcome to the Halls of Shadow:\n\n"+ \
    "[1] When encountering a Warrior within the Halls, please introduce\n"+ \
    "    yourself. If you do not, you may be viewed as a hostile unknown.\n"+ \
    "[2] Do not wield weapons in the Halls. Warriors do not do so unless\n"+ \
    "    they are preparing for a Hunt or the Halls are under attack.\n"+ \
    "    Thus, an armed Outlander in the Halls will be considered hostile.\n"+ \
    "[3] Avoid using magic in the Halls. This includes forms of telepathy.\n"+ \
    "    Doing so may bring the very stones of the Halls down upon your\n"+ \
    "    head, as well as the wrath of every Warrior of Shadow.\n"+ \
    "[4] Do not sneak about nor hide your identity with concealing \n"+ \
    "    clothing or magics. Visitors to the Halls have no need to hide\n"+ \
    "    from Us or eachother.\n"+ \
    "[5] Refrain from sharing the location of the Halls with others.\n"+\
    "    Do not bring others here unless you have seen them previously\n"+\
    "    in the Halls.\n\n"+\
    "    If you abide by the above, you are free to guest in our Halls.\n"+ \
    "    Treat our home with the same respect and courtesy we extend to\n"+ \
    "    you, and you are welcome to refresh yourself at our Table and\n"+ \
    "    bathe in our Pool.\n\n"

public string
view_rules(void)
{
    string text = LIST->query_union_text("guest_rules");
    if (!strlen(text)) text = TEXT;

    return text;
}

public void
create_scroll(void)
{
    set_name("rules");
    add_name(({"_terms_of_welcome", "notice", "vellum"}));
    add_adj("vellum");
    set_short("piece of vellum");
    set_pshort("pieces of vellum");

    set_long(view_rules);
}

public void 
read_it(string verb)
{
    string text = LIST->query_union_text("guest_rules");
    if (!strlen(text)) text = TEXT;

    write(text);
    say(QCTNAME(this_player()) + " reads the " +
      QSHORT(this_object()) + ".\n");
}

public void
enter_env(object inv, object from)
{
    ::enter_env(inv, from);

    if (!from)
	return;

    if (inv->query_prop(ROOM_I_IS))
    {
	set_alarm(0.5, 0.0, &remove_object(this_object()));
	tell_room(inv, "The "+ short() +" takes wing on a "+
	  "breeze and floats away.\n");
    }
}
