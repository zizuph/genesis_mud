inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/clubs/sgc/gobdefs.h"
//#define GOB_SOUL ANNUM_DIR+"club/gob_soul"

// Prototypes
void get_me_soul(object ob);

void
create_object()
{
    set_name("tome");
    add_name("_sciddy_");
    set_short("great dusty tome");
    set_long("It is the book filled with what goblins have learned "+
      "throughout their existence. The arcane term 'ghelp' has been "+
      "scratched on the side.\n");
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_DROP,"Such wonderful knowledge should "+
      "not be left behind.\n");
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);

    if(env->query_race() != "goblin")
    {
	env->catch_tell("This club is for goblins only\n"+
	  "Away with you!\nYour tome disintegrates into dust.\n");
	remove_object();
	return;
    }
    set_alarm(1.0,0.0, &get_me_soul(env));
}

string
query_auto_load() { return MASTER + ":"; }

void
get_me_soul(object ob)
{
    int i;
    string *souls;

    seteuid(getuid());
    ob->add_cmdsoul(GOB_SOUL);
    ob->update_hooks();
}


int
do_read(string str)
{
    if (str != "tome")
	return 0;

    write("You stare at the "+query_short()+" for quite some time, deciphering only "+
      "the word ghelp. Strange.\n");
    say(QCTNAME(TP)+" stares lingeringly at some tome.");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_read, "read");
}
