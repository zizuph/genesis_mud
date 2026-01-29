/* 
 * Hero of the Lance - Tanis Half-Elven
 * by Teth, March 28, 1996
 *
 * Quest stuff by Rastlin
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include TIME_FLOW
#include "hero_tanis.h"

inherit M_FILE
inherit CMD_MODULE;

void
create_krynn_monster()
{
    set_name("tanis");
    add_name(TANIS_NAME);
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


/*
 * Function name: solace_forest
 * Description:   Here the actual talking will take place
 */
public void
solace_forest(float time)
{
    mixed talk = SOLACE_FOREST;

    if (sizeof(talk) > gCmd_counter)
        set_alarm(time, 0.0, &do_command(talk[gCmd_counter],
					 "solace_forest"));
}

/*
 * Function name: solace_forest_start
 * Description:   This starts the actions of Tanis in the Solace forest.
 */
public void
solace_forest_start()
{
    gCmd_counter = 0;
}

public void
remove_object()
{
    INTERRUPT_PERIOD("tanis", "Tanis died");
    ::remove_object();
}


/*
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


*/
