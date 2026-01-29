/*
   mage stones

   Part of the wizard quest. 920513 /Tintin
*/
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Genesis/obj/wizquest/"
string mage;
string secret;

void
create_object()
{
    string *val;

    seteuid(getuid(this_object()));

    val = call_other(PATH + "mage_central", "get_desc");
    set_name("stone"); set_pname("stones");
    set_short("wizard stone"); set_pshort("wizard stones");
    set_adj("wizard");
    set_no_show_composite(1);
    set_long("A tall stone with the inscription:\n" +
	     "Raised in the honour of the great magician " + val[1] + ".\n");
    secret = val[0];
    mage = val[1];
    add_prop(OBJ_I_LIGHT,0);
    add_prop(OBJ_I_WEIGHT, 1000000); /* 1 ton */
    add_prop(OBJ_I_VOLUME, 250000); /* 250 l */
    add_prop(OBJ_I_VALUE, 10); /* 10 copper */
    add_prop(MAGIC_AM_MAGIC, ({100, "enchantment"}) ); /* Yes, it's magic */
}

void
init()
{
    add_action("polish", "polish");  
}

int
polish(string str)
{
    object ob;

    notify_fail("What do you want to polish?\n");
    if (!str)
	return 0;
    if (!parse_command(str, this_object(), "%o", ob))
	return 0;
    write("You polish the wizard stone.\n");
    say(QCTNAME(this_player()) + " polishes the wizard stone.\n");
    if (this_player()->query_average_stat() >= 100)
    {
	write("You can see faint gold traces in the stone forming the letters:\n" +
	      secret + "\n");

	/* Just a little confusing cosmetics /Cmd 
	   We could add a prop to the dust here?
	*/
	if (present("dust", this_player()))
	  write("Some dust from the stone swirls around in the air and suddenly swoops down\ninto the pile you are carrying.\n");
    }
    return 1;
}

void
enter_env(object dest, object old)
{
    dest->add_my_desc("There is a wizard stone here.\n", this_object());
}

leave_env(object old, object dest)
{
    if (!old)
        return;

    old->remove_my_desc(this_object());
}

void
remove_object()
{
    call_other(PATH + "mage_central", "return_desc", ({ secret, mage }));
    ::remove_object();
}
