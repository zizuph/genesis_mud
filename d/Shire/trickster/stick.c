#pragma save_binary
#pragma strict_types

inherit "/std/object";


#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include "trickster.h"
#include "/d/Shire/sys/defs.h"

#define MORE(x)    this_player()->more(read_file(x,2))

//  Prototypes
void welcome_player(object ob, int news);

void
create_object()
{
    set_name("stick");
    add_name("_trickster_stick_");
    set_short("big heavy stick");
    add_adj(({"big","heavy"}));
    set_long("This is a big heavy stick, used to bonk people over the "+
      "head with.  It is filled with many nooks and holes in which "+
      "you can store various things a Trickster uses for making mischief. "+
      "You can read the stick.\n");
    add_prop(OBJ_I_WEIGHT, 750);    /*  It is heavy after all */
    add_prop(OBJ_I_VOLUME, 100);  /* It's fairly big as well */
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_DROP,1);

    add_item("words","The words are not legible but seem to mean something "+
      "like:  'help trickster'.\n");
}

void
enter_env(object inv, object from)
{
    int flag = 0;

    ::enter_env(inv,from);
    if (!interactive(inv))
	return;
    if (inv->query_login_time() <= file_time(TRICKSTER_NEWS))
    {
	flag = 1;
    }
    set_alarm(3.0,0.0, &welcome_player(inv,flag));
}

void
init()
{
    ::init();
    add_action("do_help","help");
    add_action("do_read","read");
}


int
do_read(string str)
{
    if(str != "stick")
	return 0;

    write("The stick has words on it that read: help trickster.\n");
    return 1;
}

void
welcome_player(object ob, int news)
{
    if (!IS_MEMBER(ob))
    {
	if (!ob->query_wiz_level())
	    set_alarm(0.0,0.0,remove_object);
	return;
    }
    ob->catch_msg("Welcome, you silly Trickster, you.\n");
    if (news)
	ob->catch_msg("There is NEW news about the Tricksters guild. Check out "+
	  "the Trickster help for more information.\n");
    setuid; seteuid(getuid());
    ob->add_cmdsoul(TRICKSTER_GUILD_SOUL);
    ob->update_hooks();
    return;
}

string
query_auto_load() { return MASTER + ":"; }

public string
query_recover() { return 0; }

int
do_help(string str)
{
    setuid(); seteuid(getuid());
    if(str == "trickster")
    {
	MORE(TRICK_HELP + "general");
	/* write("And please report any problems you may encounter with "+
	  "the Trickster guild to "+ COMPOSITE_WORDS(TRICKSTER_GUILD_MASTER) +".\n");
        */
    write("And please report any problems you may encounter with "+
	  "the Trickster guild to Finwe or Igneous.\n");
	return 1;
    }
    if(str == "trickster guild")
    {
	MORE(TRICK_HELP + "guild");
	return 1;
    }
    if(str == "trickster emotions")
    {
	MORE(TRICK_HELP + "emotes");
	return 1;
    }
    if(str == "trickster abilities")
    {
	MORE(TRICK_HELP + "abilities");
	return 1;
    }
    if (str == "trickster mischief")
    {
	MORE(TRICK_HELP + "mischief");
	return 1;
    }
    if (str == "trickster titles")
    {
	MORE(TRICK_HELP + "titles");
	return 1;
    }
    if (str == "trickster disguise")
    {
	MORE(TRICK_HELP + "disguise");
	return 1;
    }
    if (str == "trickster adjectives" || str == "trickster disguise adjectives")
    {
	MORE(TRICK_HELP + "adjectives");
	return 1;
    }
    if (str == "trickster news")
    {
	MORE(TRICKSTER_NEWS);
	return 1;
    }
    return 0;
}
