/* Hero of the Lance - Caramon
 * alpha version by Teth, March 28, 1996
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>

inherit M_FILE
static int gCounter = 2;

void
create_krynn_monster()
{
    set_name("caramon");
    add_name("_caramon_");
    set_living_name("caramon");
    set_title("Majere");
    set_long("This man is both massive and muscular. Veins bulge from " +
             "his arms whenever he flexes. He has a gentle face, however " +
             "it appears that he would be quite formidable if angry!\n");
    set_race_name("human");
    set_adj("massive");
    add_adj("muscular");
    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS, 1);
    set_introduce(1);

    set_alignment(900);
}

static void
do_talk(string str, string who, float time)
{
    object hero;
    
    command(str);
    hero = present(who, environment(this_object()));
    if (!hero)
	return;

    hero->conversation(time);
}

public void
start_talk()
{
    this_object()->conversation(2.0);
}

public void
conversation(float time)
{
    float n_time;
    string who, str;
    
    switch (gCounter)
    {
        case 1:
	    str = "say Really?";
	    who = "_flint_";
	    n_time = 2.0;
	    break;
        case 2:
	    str = "say Your inheritance?";
	    who = "_sturm_";
	    n_time = 3.5;
	    break;
        case 3:
	    str = "say That's a beauty. They don't make them like that " +
		"these days. My sword broke in a fight with an ogre. " +
		"Theros Ironfeld put a new blade on it today, but it " +
		"cost me dearly.";
	    who = "_caramon_";
	    n_time = 6.0;
	    break;
        case 4:
	    str = "say So you're a knight now?";
	    who = "_sturm_";
	    n_time = 2.0;
	    break;
    }

    set_alarm(time, 0.0, &do_talk(str, who, n_time));
    gCounter++;
}




