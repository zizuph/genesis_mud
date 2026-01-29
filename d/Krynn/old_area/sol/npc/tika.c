/* Tika Waylan, in the Inn of the Last Home
 * by Rastlin  1995
 * set_long correction by Grace Dec 9 1995
 * modified by Teth, April 18, 1996 - new add_acts, descrip, intros
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>

inherit M_FILE

int gAlarm_sounded = 0;

void
create_krynn_monster()
{
    int i;


    set_name("tika");
    set_living_name("tika");
    set_race_name("human");
    set_title("Waylan, Barmaid of the Inn of the Last Home");
    set_adj("red-haired");
    add_adj("freckled");
    set_long("This barmaid is attractive, yet not overly beautiful. "+
             "Her red hair is curly, several locks of it resting on " +
             "her forehead. Her emerald green eyes dance with fun, and " +
             "freckles are lightly smattered across her nose and cheeks. "+
             "Although she is young, perhaps two decades old, her well-" +
             "muscled hands and arms indicate that she is no stranger to " +
             "hard work.\n");

    set_gender(G_FEMALE);
    add_prop(NPC_I_NO_LOOKS, 1);
    set_introduce(1);

    set_act_time(6);
    add_act("emote slams a serving of pan-fried potatoes down, in front " +
            "of a rude customer.");
    add_act("emote straightens her back with a sigh, then flexes her " +
            "shoulders, presumably to ease her cramped muscles.");
    add_act("say Can I help you?");
    add_act(({"emote smiles fondly.","say Otik has always been good " +
            "to me. He's treated me as if I was his daughter."}));
    add_act("say I miss my father. He was an illusionist of some renown, " +
            "you know.");
    add_act("emote gets a worried look on her face. She mutters something " +
            "to herself about wars in the north, then goes on " +
            "doing her work.");
    add_act("say I walked my feet off yesterday and got little thanks " +
	    "and less tips!");
    add_act(({"say Everybody is nervous, jumping at every sound.", "say " +
	    "I dropped a mug last night and -I swear- Retark drew his " +
	    "sword!"}));
    add_act((("frown","say The dragon scares away the people from the " +
            "streets, if someone could get rid of him it would be " + 
            "marvelous.")));

    set_cact_time(7);
    add_cact("shout Help me! Someone!");
    add_cact("say Please! Have mercy on me!");

    set_knight_prestige(-3);
    set_alignment(330);

    for (i = 0; i < 6; i++)
        set_base_stat(i, 35+random(5));

    set_all_attack_unarmed(10, 8);
    set_all_hitloc_unarmed(2);

}

void
init_living()
{
    ADA("kiss");
    ADA("hug");
    ADA("pinch");
}

int
pinch(string str)
{
    if (str == "tika bottom")
        set_alarm(1.0,0.0,"command","emote bites her lower lip, barely " +
                    "tolerating this assault on her.");
    return 0;
}

int
kiss(string str)
{
    if (str == "tika")
      set_alarm(2.0,0.0,"command","blush");
    return 0;
}

int
hug(string str)
{
    if (str == "tika")
	set_alarm(2.0,0.0,"player_hug", TP);
    return 0;
}

void
player_hug(object ob)
{
    object ob2;

    command("blush");

    if ((ob2 = present("tour2", ob)) && (!ob2->query_arr("tika"))) 
    {
	ob2->set_arr("tika");
	command("say Well, thank you.");
	seteuid(getuid(TO));
	if (!clone_object(OBJ + "potatoes")->move(ob))
	{
	    command("say Wait, I will give you something.");
	    write("You get some spiced potatoes from Tika.\n");
	    say(QCTNAME(ob) + " gets some spiced potatoes from Tika.\n");
	}
    }
}

public int
in_solace(object who)
{
    string place;

    if (!who || !E(who)) return 0;
    
    if (sscanf(file_name(E(who)), "/d/Krynn/solace/new_village/%s", place) == 1)
    {
        if (place == "inn")
	    who->catch_msg("Suddenly Tika starts screaming for help!\n");
	else
	    who->catch_msg("Suddenly you hear a heartaching cry from a female, " +
			   "it sounded like 'HELP' and was coming from the Inn.\n");
	return 1;
    }
    return 0;
}

public void
shout_for_help()
{
    filter(users(), "in_solace", this_object());
    return;
}

public int
query_not_attack_me(object who, int aid)
{
    if (!gAlarm_sounded)
    {
	gAlarm_sounded = 1;
	set_alarm(2.0, 0.0, shout_for_help);
    }
}

public int
second_life(object killer)
{
    K_KILL_LOG("kills", "Tika Waylan", killer);
    return 0;
}


