/**********************************************************************
 * - arinia.c                                                       - *
 * - Women's shop owner in SaMorgan.                                - *
 * - /d/Khalakhor/sw_speir/samorgan/room/dshop.c                    - *
 * - Created by Damaris@Genesis 08/2005                             - *
 **********************************************************************/
#pragma strict_types
#include "/d/Khalakhor/sys/defs.h"

#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <const.h>   // for G_FEMALE
#include <macros.h>  // for OB_NAME
#include <files.h>
#include <std.h>
#include "npc.h"
#define TUNIC "/d/Khalakhor/sw_speir/samorgan/arm/ftunic"
#define BOOTS "/d/Khalakhor/sw_speir/samorgan/arm/hboots"
#define BELT "/d/Khalakhor/sw_speir/samorgan/arm/fbelt"
#define SHEARS "/d/Khalakhor/sw_speir/samorgan/wep/dshears"

inherit STDHUMAN;
inherit "/d/Khalakhor/lib/knowledge_base";
inherit "/d/Khalakhor/lib/clan_support";
inherit "/d/Khalakhor/se_speir/port/npc/help_me";

static mapping remembered = ([]), failed = ([]);
#define TIQRN        this_interactive()->query_real_name()
object shop;
object last_attacker;
int return_alarm_id,
    attacker_alarm_id,
    has_armed;
void
create_khalakhor_human()
{
	set_name("arinia");
	set_title("Estel, weaver of cloths and shop keeper");
	add_name(({"shopkeeper","keeper", "woman"}));
	set_race_name("human");
	set_gender(G_FEMALE);
	add_adj(({"smiling", "well-dressed"}));
	set_long("She is a fine seamstress who considers herself "+
	"more a weaver of cloths and shopkeeper.\n"+
	"She has delicate blue eyes.\n"+
	"She has smooth light skin.\n"+
	"Her hair is shoulder length, light red and crimped "+
	"along the sides.\n");
        set_all_hitloc_unarmed(50);
        set_stats(({70,70,70,70,70}));
        add_prop(CONT_I_WEIGHT,48000);
        add_prop(CONT_I_HEIGHT,190);
        add_prop(NPC_I_NO_RUN_AWAY,1);
        
        set_alignment(100);
        set_mm_in("arrives brushing a stray lock of hair from her face.");
        MONEY_MAKE_SC(random(40))->move(this_object());
        set_act_time(15);
        seteuid(getuid());
        
        clone_object(TUNIC)->move(TO);
        clone_object(BOOTS)->move(TO);
        clone_object(BELT)->move(TO);
        clone_object(SHEARS)->move(TO);
        command("wield all");
        command("wear all");

        add_act("ponder");
        add_act("smile profession");
        add_act("whistle");
        add_act("emote hums a tune.");
        add_act("say Oh I do hope you will be pleased with my clothes.");
        add_act("say All my clothing is intricately sewn with care.");
        add_act("emote sighs: Oh I wish I had bought some perfume today.");
        add_act("say Have you been to the forests? I hear many changes "+
        "are underway.");
        add_ask(({"undead"}),
        "say You had better just watch thy step they might hear "+
          "and seek you out.", 1);
        add_ask(({"elves", "elf"}),
          "say Ahh yes, elves. I've known a few but they do rather "+
          "keep to themselves afterall. I have sold a few dresses "+
          "to some traveling though.", 1);
        add_ask(({"human", "humans"}),
          "say I know quite a few. SaMorgan's population is of humans "+
          "and a few half humans or half elves, depends on how you "+
          "wish to look at it.", 1);
        add_ask(({"goblin", "goblins", "hobgoblin", "hobgoblins"}),
          "say Goblins! Hide everything! Quickly! Pray they not be "+
          "coming back!", 1);
        add_ask(({"samorgan", "fishing village", "village"}),
          "say SaMorgan is a nice fishing village don't you think?", 1);
        add_ask(({"help"}),
          "say I could always use a bit of help, but not today.",1);
        add_ask(({"task"}),
          "say I have no tasks for you to do.", 1);
        add_ask(({"quest"}),
          "say Ahh now there is something I wish I could do, and "+
          "that is a quest. If only I could go off and discover "+
          "something.", 1);
        add_ask(({"dwarf", "dwarves"}),
          "say I've had to fit dwarves before. Not an easy fit at "+
          "times. Their shoulders are quite differently proportioned.", 1);
        add_ask(({"hobbit", "hobbits"}),
          "say Hobbits! Yes yes. A wonderful lot they are, I've enjoyed "+
          "fitting them in so many dashing clothes.", 1);
        add_ask(({"minotaur", "minotaurs"}),
          "say You mean the cow... err uhh... No I haven't fitted one "+
          "myself.", 1);
        add_ask(({"clothes", "clothing"}),
          "say I have many clothes for you to choose try to 'list' "+
          "them.", 1);
        add_ask(({"cloth", "cloths", "fabric", "fabrics"}),
          "say I use only the finest fabrics in my clothing.", 1);
        add_ask(({"cloak room", "cloakroom", "shop"}),
          "say I pride myself in having a colourful shop.", 1);
        add_ask(({"gnome", "gnomes"}),
          "emote giggless sweetly as she says: I have fitted a few in "+
          "my lifetime and am grateful to survive such a feat.", 1);
        add_ask(({"half-elf", "half-elves"}),
          "say Of course I know a few half-elven folk. They do exist "+
          "around here after all.", 1);
        add_ask(({"half-human", "half-humans"}),
          "say Yes, yes. There are those that are considered half-human. "+
          "But what has that to do with my dresses and gowns?",1);
        add_ask(({"kender"}),
          "say I haven't met too many kender in my lifetime.",1);
        add_ask(({"orc", "orcs"}),
          "say What is that?",1);
}
/*********************************************************************
 * - Function name: hook_return_intro                              - *
 * - Description  : Called when someone introduces themselves.     - *
 * - Arguments    : str - Name of the player introducing.          - *
 * - Returns      : 1                                              - *
 *********************************************************************/
public int
hook_return_intro(string str)
{
	if (SECURITY->query_wiz_rank(TIQRN) >= WIZ_ARCH)
	{
		command("asay devoted Blessed be my soul!");
		present(str, environment(TO))->add_introduced("arinia");
		command("kneel " + str);
		command("asay devoted Greetings to thee, " +
		capitalize(str) +
		". I am " + query_name() + " " + query_title() + 
		", thy humble servant.");
		command("asay devoted Ask anything of me and I shall do "+
		"my best to please thee.");
		remembered[str] = "nice";
	}
	else if (SECURITY->query_wiz_rank(TIQRN, "Khalakhor"))
	{
		command("asay devoted Greetings to thee, " + 
		capitalize(str) +
		". I am " + query_name() + " " + query_title() + 
		". I am most pleased that thee has graced me with "+
		"thy pressence. How may I serve thee, a new dress or "+
		"perhaps you would prefer a gown?");
		present(str, environment(TO))->add_introduced("arinia");
		command("kneel " + str);
		remembered[str] = "nice";
	}
	else if (!remembered[str])
	{
		command("say Greetings to thee, " + capitalize(str) +
		", I am " + query_name() + " " + query_title() +
		". A pleasure to make thy acquaintance.");
		present(str, environment(TO))->add_introduced("arinia");
		command("curtsey " + str);
		remembered[str] = "nice";
	}
	else if (remembered[str] == "bad")
	{
		command("growl sof");
		command("say I remember thou very well. So be on "+
		"thy way!");
	}
	else
	{
		command("emote beams with pleasure.");
		command("say I remember thee very well from thy "+
		"last visit, " + capitalize(str) + ". How could I "+
		"ever forget thee.");
		command("curtsey " +str);
		command("say I hope thou art faring well, and "+
		"enjoying our fine city?");
	}
	return 1;
}
public void
add_introduced(string who)
{
	kb_add_introduced(who);
}

public void
init_living()
{
	::init_living();
	kb_init_living();
}

public void
enter_env(object to, object from)
{
	::enter_env(to, from);
	kb_enter_env(to, from);
}
