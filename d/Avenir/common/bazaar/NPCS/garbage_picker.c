//-*-C++-*-
// goblin garbage picker 
// /d/Avenir/common/bazaar
// creator(s): Lilith, July 1997
// revised:
// purpose:    To clean 
// note:       
// bug(s): 
// to-do:

// Call_for_help drags killers to the pillory.
inherit "/d/Avenir/common/bazaar/NPCS/call_for_help";

#include "/d/Avenir/include/defs.h"      /* Short-hand macros */
#include "/d/Avenir/include/paths.h"     /* Avenirian path defines */
#include "/d/Avenir/include/macros.h"    /* ADD_SKIN, etc */
#include "/d/Avenir/include/relation.h"  
#include <macros.h>                      /* macros like VBFC and QNAME */
#include <stdproperties.h>               /* properties */
#include <wa_types.h>                    /* weapon and armour defs */
#include <ss_types.h>                    /* skill and stat defs */

int    alarm_id;
string *randadj;
string my_long();

/* Masking can_pick() from /std/act/ranpick.c
 * to give specific instructions to npc as to 
 * what it should pick up -- in this case, 
 * broken items.
 */
int
can_pick(object ob)
{
    if (ob->query_prop(OBJ_I_NO_GET))
        return 0;

    /* If its broken, get it */
    if (ob->query_prop(OBJ_I_BROKEN))
        return 1;
    /* If its not broken and its one of these, leave it */
    if (ob->id("armour") || ob->id("weapon"))
        return 0;
    /* If its magical, don't touch */
    if (ob->query_prop(MAGIC_AM_MAGIC))
        return 0;
    /* If its a container, leave it */
    if (ob->query_prop(CONT_I_IN))
        return 0;

    /* Otherwise, grab it */
    return 1;
}

void
create_monster()
{
    ::create_monster();

    randadj = ({"little", "trimmed", "lean", "perfumed", "burly",
                "slender", "happy", "kindly", "helpful", "tireless",
                "smiling", "wide-eyed", "innocent", "eager",
                "pleasant", "industrious", "gentle"});

    set_name("picker");
    add_name(({"janitor", "laborer"}));
    set_adj(randadj[random(sizeof(randadj))]);
    set_race_name("goblin");
    set_gender(random(3));
    set_long(my_long);
    set_stats(({130,140,50,40,40,50}));
 
    set_alignment(0);
    set_pick_up(95);
    set_all_hitloc_unarmed(5);
    set_all_attack_unarmed(20, 11);

    set_random_move(5, 1);
    set_restrain_path("/d/Avenir/common/bazaar/");
    set_monster_home("/d/Avenir/common/bazaar/extr/str10");   

    set_skill(SS_DEFENCE, 30);
    set_skill(SS_WEP_CLUB, 50);
    set_skill(SS_AWARENESS, 20);
    set_skill(SS_UNARM_COMBAT, 20);

    add_prop(CONT_I_HEIGHT, 100 + random(100)); 
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(LIVE_I_NEVERKNOWN,1);

    set_act_time(10);
    add_act("emote gathers garbage.");
    add_act("emote stops to stretch, but notices you looking and "+
		  "gets back to work.");
	 add_act("emote hums tunelessly.");
	 add_act("laugh loud");
	 add_act("scratch");
	 add_act("emote belches rather delicately, for a goblin.");
	 add_act("smile shy");
	 add_act("ponder");

	 set_default_answer(VBFC_ME("what_me"));
	 add_ask(({"help","task","job","errand","quest","assignment"}),
		  VBFC_ME("give_job"), 1);
	 seteuid(getuid(TO));
}

string
my_long()
{
    return "A "+ query_adj() +" goblin worker.\n"+
	capitalize(this_object()->query_pronoun()) +" appears to be "+
        "hard at work keeping up the grounds.\n"+
	capitalize(this_object()->query_pronoun()) +" is a proud "+
	"member of B.O.G.L., the Brotherhood Of Goblin Laborers.\n";
}

string
what_me()
{
	 switch(random(7))
	 {
		  case 0:
				command("say Me not permitted to answer.");
				break;
		  case 1:
				command("say Me picks up the trash that Outlanders leave "+
					 "behind. Me knows only this.");
				break;
		  case 2:
				command("emote struggles to answer, but does not seem able "+
					 "to get the words out.");
				break;
		  case 3:
				command("mumbles around pointy teeth: Me likes to work.");
				break;
		  case 4:
				command("emote looks anxiously around.");
				command("say Has me done something wrong?");
				break;
		  case 5:
				command("say Me not wants your attention.");
				break;
		  case 6:
				command("emote pretends not to hear.");
				break;
	 }
	 return "";
}

string
give_job()
{
	 command("say B.O.G.L gives good jobs.");
	 command("smile proud " + TP->query_name());
			return "";
}

public void
enter_inv(object obj, object from)
{
	 ::enter_inv(obj, from);

	 if (living(from))
	 {
		  command("say Me find use for this!");
	 }

	 obj->remove_object();
	 return;
}

/*
 * check_meet enables the npc to greet players it
 * comes into contact with, according to guild.
 */
void
check_meet(object tp)
{
	 int     i;
	 i = random(10);

	 if (!present(tp, environment(TO)))
		  return;

	 if(tp->query_prop("_is_cat_"))
	 {
		if(i<6)
		{
			command("say to "+tp->query_real_name()+" Skat!");
			command("say Me don't like cats.");
			return;
		}
		return;
	 }
}

void
init_living()
{
	 ::init_living();

	 if (interactive(TP) && CAN_SEE(TO, TP))
	 {
		  if (alarm_id)
				return;
		  alarm_id = set_alarm(2.0, 0.0, &check_meet(TP));
		  return;
	 }

}
