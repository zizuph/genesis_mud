/* created by Aridor, 06/15/94 */

inherit "/std/object";
#include "brimsch.h"

object person;
int done = 0;

void
create_object()
{
    set_short("few drops of sweet liquid on the floor");
    set_pshort("few drops of sweet liquid on the floor");
    set_name("drop");
    add_name("drops");
    add_name("liquid");
    add_name("fluid");
    set_long("These drops smell sweet, but only a Gully Dwarf would prefer them on the floor like this.\n");
    set_alarm(5.0,0.0,"add_prop",OBJ_M_NO_GET, 1);
    seteuid(getuid(TO));
    /*set_heap_size(3);
    add_prop(HEAP_S_UNIQUE_ID, long());*/
}

void
set_person(object who)
{
    person = who;
}

void
init()
{
    set_alarm(itof(random(5) + 5),0.0,"gullydwarf_mops_up");
    ::init();
}


void
gullydwarf_mops_up()
{
    int prp;
    object dwarf = present("gully dwarf",E(TO));
    if (done || !dwarf)
      return;
    done = 1;
    dwarf->command("say Uh Oh, what that?");
    dwarf->command("emote points at the drops on the floor.");
    dwarf->command("say Me mop up!");
    dwarf->command("say Me good at mop up!");
    dwarf->command("emote kneels down and licks the drops from the floor.");
    if (person->query_race() != "goblin")
      person->catch_msg("YUCK!\n");
    else
      person->catch_msg("Yummy!\n");
    dwarf->command("smile contentedly");
    dwarf->command("burp");
    if (person && (E(person) == E(dwarf)))
      {
	  dwarf->command("hmm");
	  dwarf->add_prop(LIVE_I_SEE_DARK, 2);
	  dwarf->command("say Uh Oh, wait. I got somethin for you.");
	  dwarf->command("emote opens a pouch.");
	  dwarf->command("emote pulls a dead rat from the pouch!");
	  dwarf->command("oops");
	  dwarf->command("emote stores the rat back into the pouch.");
	  dwarf->command("emote pulls a piece of metal from the pouch.");
	  dwarf->command("say Here, for you.");
	  clone_object(METAL)->move(dwarf);
	  dwarf->command("give metal to " + person->query_real_name());
	  prp = person->query_prop(PLAYER_I_BRIMSCH_LIFE_QUEST);
	  person->add_prop(PLAYER_I_BRIMSCH_LIFE_QUEST, 2 | prp);
	  dwarf->command("emote closes the pouch.");
      }
    set_alarm(1.0,0.0,"remove_object");
}
