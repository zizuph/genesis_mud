inherit "/std/act/action.c";
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

inherit AM_FILE

/* Sarr */
/* Borrowed from Sarrs code of a dog in the Neraka npc directory */

object Aowner;

int sX = 20 + random(20);

int *gGender = ({1});

string *gRace = ({"human","human","human","half-elf"});

string gMaster = "master";

int react_kick(object who, string adverb);
int react_touch(object who, string adverb);
int react_anger(object who, string adverb);
int react_forgive(object who, string adverb);

EMOTE_HOOK

#ifndef ONE_OF
#define ONE_OF(x) (x[random(sizeof(x))])
#endif


void
create_krynn_monster()
{
    set_name("wench");
    add_adj("serving");
    set_race_name(ONE_OF(gRace));
    set_gender(ONE_OF(gGender));
    set_short("serving wench");
    set_long("A serving wench for the feasthall under The Resting " +
      "Blade Inn.\n");
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(CONT_I_HEIGHT, 150 + random(50));
    add_prop(CONT_I_WEIGHT, 49000 + random(5000));
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    set_stats(({sX,sX,sX,sX,sX,sX}));
    set_act_time(28);
    add_act("emote picks up a glass off the floor.");
    add_act("emote brings out more glasses of Dragonbrew.");
    add_act("emote puts another platter of food on the table.");

    add_emote_hook("kick",1.0,react_kick);
    add_emote_hook("knee",1.0,react_kick);
    add_emote_hook("slap",1.0,react_kick);
    add_emote_hook("tickle",1.0,react_kick);
    add_emote_hook("pinch",1.0,react_kick);
    add_emote_hook("lick",1.0,react_touch);
    add_emote_hook("caress",1.0,react_touch);
    add_emote_hook("kiss",1.0,react_touch);
    add_emote_hook("french",1.0,react_touch);
    add_emote_hook("fondle",1.0,react_touch);
    add_emote_hook("grope",1.0,react_touch);
    add_emote_hook("poke",1.0,react_touch);
    add_emote_hook("explode",1.0,react_anger);
    add_emote_hook("growl",1.0,react_anger);
    add_emote_hook("fume",1.0,react_anger);
    add_emote_hook("glare",1.0,react_anger);
    add_emote_hook("scold",1.0,react_anger);
    add_emote_hook("scream",1.0,react_anger);
    add_emote_hook("forgive",1.0,react_forgive);


    seteuid(getuid());
}

int
react_kick(object who, string adverb)
{
	command("say For a tough soldier, you hit like a girl!");
        return 1;
}


int
react_touch(object who, string adverb)
{
    command("slap " +who->query_real_name());
    command("say Hands off the merchandise sweety! If you want a bit of candy, " +
      "you know where the brothel is!");
    return 1;
}

int
react_anger(object who, string adverb)
{
	command("giggle");
	set_alarm(1.0,0.0,"command","say I live in a city of dragons.. you think " +
          "i'll find you intimidating?");
    return 1;
}

int
react_forgive(object who, string adverb)
{
    command("emote looks around with disbelief.");
    return 1;
}


