/* Changed the alignment to 250
 * 1000 seems rather extreme for this NPC
 * Damaris 2/2002
 */
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include <money.h>
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("bassil");
    add_name("head shipwright");
    add_name("shipwright");
    set_race_name("elf");
    set_adj("ancient");
    add_adj("weathered");
    set_short("shipwright");
    set_long("This withered old elf reminds you of a piece of parchment "+
      "paper, that due to old age and poor care has been crinkled into a "+
      "myriad number of wrinkles and whose luster has faded away. Yet from "+
      "those pair of sparkling sea blue eyes is a timeless quality, one "+
      "unique to elves.\n");
    set_stats(({90,110,60,75,75,80}));
    set_alignment(250);
    set_skill(SS_UNARM_COMBAT,80);
    set_skill(SS_BLIND_COMBAT,50);
    set_skill(SS_DEFENCE,60);
    set_skill(SS_AWARENESS,50);
    set_act_time(3);
    add_act("say Greetings, strange one.");
    add_act("smile .");
    add_act("ponder");
    add_act("say How I wish I could finish my ship.");
    add_act("say I'm afraid I might never complete the ship.");
    set_cact_time(3);
    add_cact("say Have you no respect for the elderly!");
    add_cact("spit");
    add_cact("say You younger folk are all barbarians!");
    add_cact("scream");
    add_speak("I wish I could finish the ship I am working on.\n");
    set_knight_prestige(-10);
    set_title("Korahf, Head Shipwright");
    set_default_answer("The shipwright says: I'm sorry, I didn't catch "+
      "that last word.\n");
    add_ask(({"ship"}),"The shipwright says: I need just a few more parts "+
      "for my ship, before it can be completed...\n");
    add_ask(({"few more parts","few parts","parts","part"}),"The shipwright "+
      "says: I'll need some more tar...a sail or two...and some other "+
      "material.\n");
    add_ask(({"keys","key"}),"The shipwright says: Hmm...I don't know "+
      "which one, but one of the keys I've got opens up a prison door "+
      "somewhere.\n");
    add_ask(({"door"}),"The shipwright says: I haven't the vaguest clue "+
      "where it might be.\n");
    add_ask(({"how"}),"The shipwright says: You mean how I got these "+
      "keys?\n"+
      "The shipwright smiles mysteriously.\n"+
      "The shipwright says: When you've lived several centuries, you get "+
      "to know lots of things.\n");
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
    set_alarm(1.0,0.0,"my_stuff");
}

void
my_stuff()
{
    object item;
    seteuid(getuid(TO));
    item = clone_object("/d/Kalad/common/port/seahawk/door_key");
    item -> move(TO);
    item = clone_object("/d/Kalad/common/port/obj/iron_key");
    item -> move(TO);
    item = clone_object("/d/Kalad/common/port/seahawk/door_key");
    item -> move(TO);
    item = clone_object("/d/Kalad/common/port/obj/iron_key");
    item -> move(TO);
    item = clone_object("/d/Kalad/common/port/seahawk/door_key");
    item -> move(TO);
    item = clone_object("/d/Kalad/common/port/obj/iron_key");
    item -> move(TO);
    item = clone_object("/d/Kalad/common/port/seahawk/door_key");
    item -> move(TO);
    item = clone_object("/d/Kalad/common/port/obj/iron_key");
    item -> move(TO);
    MONEY_MAKE_SC(random(25))->move(TO,1);
}
void
enter_inv(object ob,object from)
{
    if(from)
    {
	if(MASTER_OB(ob) == "/d/Kalad/common/port/obj/sail")
	    set_alarm(2.0,0.0,"return_sail",from);
	if(MASTER_OB(ob) == "/d/Kalad/common/port/obj/tar")
	    set_alarm(2.0,0.0,"return_tar",from);
    }
}

void
return_tar(object obj){
    if(present(obj, environment())){
	command("say Many thanks fer the tar, matey.");
	command("say I think ye might find some use fer this...");
	command("give steel key to " + (obj->query_real_name()));
    }
}
void
return_sail(object obj){
    if(present(obj, environment())){
	command("say Thank ye fer the sail, matey.");
	command("say This might come in handy...");
	command("give iron key to " + (obj->query_real_name()));
    }
}
