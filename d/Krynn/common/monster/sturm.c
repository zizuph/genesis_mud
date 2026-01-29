/* Hero of the Lance - Sturm
 * beta version by Teth, March 28, 1996
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>

inherit M_FILE
static int gCounter = 1;

void
create_krynn_monster()
{
    set_name("sturm");
    add_name("_sturm_");
    set_living_name("sturm");
    set_title("Brightblade, Hopeful Knight of Solamnia");
    set_long("This young human bears a long moustache, that droops past " +
             "his chin. His eyes are deepset, suggesting that he is often " +
             "deep in thought. He carries himself with a noble bearing.\n");
    set_race_name("human");
    set_adj("melancholy");
    add_adj("noble");
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
	    str = "say All? Kitiara?";
	    who = "_tanis_";
	    n_time = 2.0;
	    break;
        case 2:
	    str = "say Not I. We traveled north together and parted soon " +
		"after crossing the Sea Narrows into Old Solamnia. She was " +
		"going to look up relatives of her father, she said. That " +
		"was the last I saw of her.";
	    who = "_tanis_";
	    n_time = 6.0;
	    break;
        case 3:
	    str = "say I heard rumors. Some say my father is dead. Some " +
		"say he's alive. But no one knows where he is.";
	    who = "_caramon_";
	    n_time = 3.0;
	    break;
        case 4:
	    str = "smile";
	    who = "_sturm_";
	    n_time = 0.5;
	    break;
        case 5:
	    str = "say I wear it, my armour and my weapon.";
	    who = "_caramon_";
	    n_time = 2.5;
	    break;
        case 6:
	    str = "say According to the legend, this sword will break " +
		"only if I do. It was all that was left of my father's-";
	    who = "_tasselhoff_";
	    n_time = 0.0;
        case 7:
	    str = "say I found them wandering around on the road outside " +
		"of town. The woman appeared near exhaustion, the man just " +
		"as bad. I brought them here, told them they could get " +
		"food and rest for the night. They are proud people and " +
		"would have refused my help, I think, but they were lost " +
		"and tired and there are things on the road these days " +
		"that it is better not to face in the dark.";
	    who = "_tanis_";
	    n_time = 8.0;
	    break;
    case 8:
	    str = "say A Seeker guard questioned me about a staff outside, " +
		"blue crystal, wasn't it?";
	    who = "_caramon_";
	    n_time = 2.0;
	    break;
    case 9:
	    str = "say There are rumors of worse to come. Armies are " +
		"gathering in the north. Armies of strange creatures - " +
		"not human. There is talk of war.";
	    who = "_tanis_";
	    n_time = 2.0;
	}

    set_alarm(time, 0.0, &do_talk(str, who, n_time));
    gCounter++;
}

