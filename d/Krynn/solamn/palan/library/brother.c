/* created by Aridor, 06/06/94 */

#include "local.h"

inherit M_FILE

#include <macros.h>

void
create_krynn_monster()
{
    set_name("deggart");
    add_name("brother");
    add_name("aesthetic");
    set_long("A brother of the Aesthetic Order. He is on public duty and " +
	     "is ready to serve you.\n");
    set_race_name("human");
    default_config_npc(50);

    ALWAYSKNOWN;
    set_default_answer(VBFC_ME("default_ans"));
    add_ask(({"private", "private study", "study", "south"}),
	    "say To the south is the private study of our master, Astinus.", 1);
    add_ask(({"master","astinus","audition"}),VBFC_ME("ans_astinus"));
    add_ask(({"library","book","books"}),
	    "say This is the great Library of Palanthas. All " +
	    "history of Krynn is recorded here. Astinus, the master " +
	    "himself, is working here. There are many books stored here, " +
	    "invaluable information and knowledge can be found in them.",1);
    add_ask(({"history"}),"say Yes, you can find out a lot about the history " +
	    "of Krynn by reading the books here.",1);
    add_ask(({"aesthetics","aesthetic","order","librarians","librarian"}),
	    "say The Aesthetics are the order of librarians supporting " +
	    "Astinus in his work.",1);

    set_act_time(1000);
    add_act("take statue");
}

string
default_ans()
{
    command("say Shhhh! Don't disturb the quiet here.");
    return "";
}

string
ans_astinus()
{
    mixed prp;
    int i;
    command("say He is the master of time. It is he who writes " +
	    "history as it passes.");
    prp = TP->query_prop(PLAYER_M_PAL_LIB_AUDITION);
    if (!prp)
      {
	  command("say Under no circumstances may he be disturbed.");
	  return "";
      }
    if (pointerp(prp))
      for(i = 0; i < (sizeof(prp) - 1); i++)
	command(prp[i]);
    else
      command("say I see you are on an important quest, please enter.");
    command("point south");
    return "";
}

