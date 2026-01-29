/* Hero of the Lance - Tanis
 * beta version by Teth, March 28, 1996
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>

inherit M_FILE
static int gCounter = 1;

void
create_krynn_monster()
{
    set_name("tanis");
    add_name("_tanis_");
    set_living_name("tanis");
    set_title("Half-Elven");
    set_long("Even though this person is bearded, his elven origins " +
             "are apparent when his somewhat pointed ears are exposed. " +
             "He is tall and commanding, with astute eyes that betray " +
             "his always analyzing nature.\n");
    set_race_name("half-elf");
    set_adj("commanding");
    add_adj("bearded");
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
	    str = "say Not coming, we were hoping perhaps you could tell " +
		"us something.";
	    who = "_sturm_";
	    n_time = 2.0;
	    break;
        case 2:
	    str = "say Well, I suppose that's that.";
	    who = "_tanis_";
	    n_time = 0.2;
	    break;
        case 3:
	    str = "sigh";
	    who = "_tanis_";
	    n_time = 1.0;
	    break;
        case 4:
	    str = "say What of your relatives, Sturm? Did you find your " +
		"father?";
	    who = "_sturm_";
	    n_time = 1.5;
	    break;
        case 5:
	    str = "say We met some of them, asking about a staff.";
	    who = "_sturm_";
	    n_time = 3.0;
	    break;
    case 6:
	    
	    
    }

    set_alarm(time, 0.0, &do_talk(str, who, n_time));
    gCounter++;
}

