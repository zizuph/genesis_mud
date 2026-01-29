inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include "/d/Shire/common/defs.h"
#define GOB_SOUL ANNUM_DIR+"club/gob_soul"

void
create_object()
{
        set_name("tome");
        add_name("_new_sciddy_");
        set_short("great dusty tome");
        set_long("It is the book filled with what goblins have learned "+
                 "throughout their existence. The arcane term 'ghelp' has been "+
                 "scratched on the side.\n");
        add_prop(OBJ_I_WEIGHT, 20);
        add_prop(OBJ_I_VOLUME, 5);
        add_prop(OBJ_I_VALUE, 0);
        add_prop(OBJ_M_NO_DROP,"Such wonderful knowledge should "+
                 "not be left behind.\n");
		//add_subloc("_goblin_look", TO);
}

void
init()
{
   ::init();

    if(TP->query_race_name() != "goblin" && TP->query_wiz_level() < 1) {
     write("This club is for smart goblins only! Get out!\n");
     write("Your tome disintegrates into dust.\n");
      remove_object();
     }

   
   add_action("do_read","read");
   //set_alarm(1.0, 0.0, "get_me_soul", TP);
}

string
query_auto_load() { return MASTER + ":"; }

/*
void
get_me_soul(object ob)
{
	seteuid(getuid());
	ob->add_cmdsoul(GOB_SOUL);
	ob->update_hooks();
	ob->add_subloc("_goblin_look");
}
*/

string
show_subloc(mixed subloc, object on, object who)
{
	if (subloc != "_goblin_look")
		return "";
	if (who == ENV(TO))
		return "You are one of them smart Goblins.\n";
	else
		return CAP(HE_SHE(ENV(TO)))+" is a very smart Goblin, for a goblin to be.\n";
}

public void
leave_env(object to, object from)
{
	TP->remove_cmdsoul(GOB_SOUL);
	TP->remove_subloc("_goblin_look");
	TP->update_hooks();
}

enter_env(object to, object from)
{
	remove_name("_new_sciddy");
	if (present("_new_sciddy", ETO))
	{
		tell_room(ETO, "The tome vanishes into one single piece.\n");
		remove_object();
		return;
	}

	add_name("_new_sciddy");
	if (living(ETO))
		to->add_subloc("_goblin_look", TO);
		to->add_cmdsoul(GOB_SOUL);
		to->update_Hooks();
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
