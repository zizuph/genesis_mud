#include "/d/Shire/sys/defs.h"
#include <ss_types.h>
#include <formulas.h>
#include <wa_types.h>

inherit SHIRE_MONSTER;

#define TROLL_HOME    (SHAWS_DIR + "troll_home")
#define TROLL_STATUE  (SHAWS_DIR + "obj/troll_statue")

// Prototypes
void try_go_home();
void turn_to_stone();

void create_troll() {}

nomask void
create_shire_monster()
{
    set_name("_Shire_troll_");
    set_race_name("troll");
    set_long("This ugly creature is a troll.\n");
    set_stats(({100,100,100,100,100,100}));

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK,   4);

    create_troll();
}

void
sunrise()
{
    if (ENV(TO)->query_prop(ROOM_I_INSIDE))
	return;

    if (objectp(query_attack()))
    {
	command("say "+ONE_OF(({"Arrgghh da sun comes!!","I better smash in "+
	      "yer skull fast "+query_attack()->query_race_name()+
	      " before da sun rises any higher.", "Hmmm me betta run before "+
	      "me turn to stone.","Oh this no gud.","Me better go before me "+
	      "end up like Birt!","Me hungry, me grab dis "+
	      query_attack()->query_race_name()+" fer dinner!"})));
	set_alarm(itof(60 + random(31)),0.0,try_go_home);
	return;
    }
    command("say "+ONE_OF(({"Ahh da sun comes me better get going.",
	  "Me eyes hurt!","Me hungry, lets go.","Stupid sun, me hates you!",
	  "Me better hide soon.","Arrrrggggh da sun comes!!"})));
    command("emote makes "+HIS_HER(TO)+" way home.");
    move_living("M",TROLL_HOME,1,1);
}

void
try_go_home()
{
    if (query_attack())
    {
	command(ONE_OF(({"scream pain","scream loud","scream slow",
	      "shout Noooooooooooooooo!!!","say This no gud.","grumble ang",
	      "emote covers "+HIS_HER(TO)+" eyes."})));
	turn_to_stone();
	return;
    }
    command("emote makes "+HIS_HER(TO)+" way home.");
    move_living("M",TROLL_HOME, 1, 1);
}

void
turn_to_stone()
{
    object statue;

    stop_fight(query_enemy(-1));
    command("emote slowly turns to stone, as the "+
      "Sun's rays shine brightly on "+HIM_HER(TO)+".");
    FIXEUID;
    statue = clone_object(TROLL_STATUE);
    statue->move(ENV(TO), 1);
    statue->configure(TO);
    remove_object();
}
