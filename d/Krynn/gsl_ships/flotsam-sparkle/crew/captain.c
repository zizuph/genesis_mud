inherit "/d/Genesis/ship/captain";
#include "/d/Ansalon/balifor/flotsam/ship/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/sys/filter_funs.h"
#include "/d/Ansalon/common/defs.h"
#include <filter_funs.h>

#define ENV(xxx) environment(xxx)

int intro = 0;


void
create_monster()
{
    set_name("hull");
    add_name("captain");
    set_race_name("human");
    add_adj("leather-skinned");
    set_adj("muscular");
    set_long("This is the captain of the Golden Lion, the " +
      "ship that travels from Flotsam to Sparkle. This captain " +
      "must be pretty brave, or desperate, to sail the Bloodsea " +
      "of Istar for a living.\n");
    set_stats(({ 80, 80, 100, 60, 60, 90 }));
    set_skill(SS_SWIM, 100);
    set_skill(SS_LOC_SENSE,100);
    set_skill(SS_UNARM_COMBAT,80);
    set_skill(SS_DEFENCE,50);
    heal_hp(10000);

    set_chat_time(8);
    add_chat("I'm the captain of the Golden Lion, fastest " +
      "ship to sail the Bloodsea!");
    add_chat("One of my passengers, an elf from Silvanesti, needs someone " +
      "to do a job for him. He is in the cabin below if you are interested.");
    add_chat("My ship's fast enough to outsail the dragonarmy " +
      "war galleys... so is she fast enuff for ya?");
    add_chat("Never fear, I've sailed the Bloodsea all my " +
      "life.");

    set_cchat_time(11);
    add_cchat("Stop it, you pestering dog!");
    add_cchat("Right, you'll pay for that!");
    add_cchat("Come on! I'll beat the living daylights out of you!");
    add_cchat("Right! I'm really gonna stump you this time!");
    add_cchat("Give it to me, big-nose!");
    add_cchat("I'm gonna smack you so hard....");

    trig_new("%w 'introduces' %s", "react_introduce");

    add_prop(OBJ_M_NO_ATTACK,
      "You feel this man is under strong protection.\n");
    add_prop(OBJ_I_RES_MAGIC, 200);
   add_prop(OBJ_M_NO_MAGIC_ATTACK, "Somehow no harm can be done to "+
      "the captain by means of magic. How strange.\n");

    set_ticket(TICKET);
    set_price(PRICE);

}    

string
query_my_title()
{
    return "Pirate Lord of the Bloodsea";
}

int
buy(string str)
{
    if (this_player()->query_average_stat() < 20)
    {
	notify_fail("You don't need to buy any ticket. " +
	  "Young travel for free.\n");
	return 0;
    }

    return ::buy(str);
}

void
react_introduce(string person,string who)
{
    if (!intro)
	intro = set_alarm(4.0,0.0,"introduce_me");
}

void
introduce_me()
{
    tell_room(E(TO),QCTNAME(TO) + " introduces himself as:\n" +
      "Captain Hull Nightstar, " +query_my_title() +
      ", champion, male human.\n");
    FILTER_LIVE(all_inventory(E(TO)))->add_introduced("hull");
    intro = 0;
}


