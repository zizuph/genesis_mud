/* Vingaard keep coded by Percy. */
/* Modified by Morrigan 10/6/96. */
/* Modified again for the new Vingaard Keep by Morrigan 11/11/96 */

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include "../../guild.h"

inherit TRAIN_BASE;
inherit OUT_BASE;

#define OUTKEEP       VROOM + "inner_gate"
object kn1, kn2, ob;

object ob;
int gate_closed  = 0;

void
set_up_skills()
{
    sk_add_train(SS_RIDING, "ride horses", 0, 0, 75);
    sk_add_train(SS_MOUNTED_COMBAT, "fight while mounted",  0, 0, 100);
}

public void
reset_vin_room()
{
    object trainer;
    
    trainer = query_guild_trainer();
    if (!objectp(trainer))
    {
        trainer = clone_object(VNPC + "thomas");
        set_guild_trainer(trainer);
        trainer->move(TO);
    }
    if (!kn1)
    {
    	kn1 = clone_object(NPCSTD + "vin_knight_base");
    	kn1->set_act_time(30);
    	kn1->move(TO);
    }
    if (!kn2)
    {
    	kn2 = clone_object(NPCSTD + "vin_knight_base");
    	kn2->set_act_time(30);
    	kn2->move(TO);
    }
}

void
create_vin_room()
{
    set_short("Inner Courtyard of Vingaard Keep");
    set_long("@@long_desc");

    AE(VROOM + "train1", "west", 0);
    AE(VROOM + "joinroom", "north", "@@bookroom", 0);
    AE(VROOM + "train2", "east", 0);
    AE(OUTKEEP, "south", "@@go_south");

    AI("hatch", "@@hatch_desc");
    AI(({"wall", "walls", "great walls", "great wall"}), "The walls " +
      "are massive and hint at a history of pride and honour, and " +
      "a refusal to yield attitude.\n");
    AI(({"gate", "gates","portcullis"}), "@@gate");
    AI("courtyard", "@@court");
    AI(({"hall","guild hall", "guild"}),"Located to the north, it " +
      "is the home of the Knights of Solamnia.\n");

    ACI(({"portcullis","gate","gates"}),({"open","raise"}),
      "@@open_portcullis");
    ACI(({"portcullis","gate","gates"}),({"close","lower"}),
      "@@lower_portcullis");

    add_prop(ROOM_M_NO_TELEPORT, "The walls of Vingaard Keep prevent " +
      "teleportation in this area... or is it something else?\n");
    create_skill_raise();
    set_up_skills();

    reset_vin_room();

}

string
hatch_desc()
{
    if (!gate_closed)
	return "The portcullis is not closed, you cannot see the "+
	"hatch when it's open.\n";
    return "There is a small hatch about eye-level on the gate, "+
    "which you can probably peek through, to see the outside "+
    "of the gate.\n";
}

string
long_desc()
{
    string str;
    string description = tod()+season()+"You stand in the Inner Courtyard of "+
    "Vingaard Keep. " +
    "Surrounded by two great walls, you feel dwarfed. To the north " +
    "lies the guild hall, and to the west and east are areas that can " +
    "only be training rooms. Those rooms would be where the Knights of " +
    "Solamnia learn to become skilled and noble fighters. The inner " +
    "gate stands firm and ready to the south, keeping constant vigil "+
    "on the inner courtyard.\n";

    if (!P(kn1, TO) && !P(kn2, TO))
	str = " There are currently no Knights and Squires training here, "+
	"a bad sign indeed!";
    else
	str = " The courtyard rages with Squires in mock combat, "+
	"sparring each other, occasionally sparring the Knights who instruct "+
	"them. You see most of the Squires here being instructed on how to "+
	"dodge and parry blows. ";

    if (!P(query_guild_trainer(), TO))
	return description + str +"Oddly, you see no trainer here...\n";

    return description + str +gTrainer->query_The_name(TP)+" looks around "+
    "the courtyard calmly, giving tips to the training Knights.\n";

}

void
init()
{
    add_action("hatch", "peek");
    init_skill_raise();
    ::init();
}

int
hatch(string str)
{
    object *inv, *live, *dead, room;

    if (!str)
	return 0;

    if (!gate_closed)
	return 0;

    if (str != "through hatch" && str != "hatch")
	return 0;

    inv = ({});
    if ((room = find_object(OUTKEEP)) != 0)
	inv += all_inventory(room);

    if (inv && sizeof(inv) > 0)
    {
	live = FILTER_LIVE(inv);
	live -= ({ TP });
	dead = FILTER_DEAD(inv);
	if (sizeof(live) > 0 && sizeof(dead) > 0)
	{
	    write("As you slide open the hatch and peek through "+
	      "the gate, you see " + COMPOSITE_LIVE(live) + ", as "+
	      "well as " + COMPOSITE_DEAD(dead) + ".\n");
	    return 1;
	}
	else if (sizeof(live) > 0)
	{
	    write("As you slide open the hatch and peek through "+
	      "the gate, you see " + COMPOSITE_LIVE(live) + ".\n");
	    return 1;
	}
	else if (sizeof(dead) > 0)
	{
	    write("As you slide open the hatch and peek through "+
	      "the gate, you see " + COMPOSITE_DEAD(dead) + ".\n");
	    return 1;
	}
    }

    write("As you slide open the hatch and peek through the "+
      "gate, you see nothing.\n");
    return 1;
}

string
gate()
{
    if (gate_closed)
	write("The gate is made of iron. It looks extremely solid. At the "+
	  "moment, the gates are closed! A most disturbing sign! You notice "+
	  "a small hatch about eye-level on the gate.\n");
    else
	write("The gate is made of iron. It looks extremely solid. At the "+
	  "moment, however, the gate lies open, a sign of the knights' "+
	  "confidence in their power to defeat the evil in the world.\n");
    return "";
}

string
court()
{
    write("The courtyard is expansive and could easily hold many Solamnian" +
      " Knights. Its usual purpose is to provide room for " +
      "marching and parading Knights, although it is also a general " +
      "place to gather under the open sky and in the fresh air.\n");
    return "";
}

/* Returns 0 to allow travel under gate. */
int
go_south()
{
    if (gate_closed)
	write("The portcullis is down, you can't go outside.\n");
    else
	write("You pass through the gates into a dimly lit archway.\n");
    return gate_closed;
}

int
lower_portcullis()
{
    if (!gate_closed && (TP->id("knight") || TP->query_guild_name_occ() == 
	"Solamnian Knights"))
    {
	gate_closed = 1;
	write("You hit the hook holding the portcullis in place.\n");
	tell_room(TO,"With a loud rumble the portcullis slams down and " +
	  "effectively seals off the entrance.\n");
	tell_room(OUTKEEP,"With a loud rumble the portcullis slams down and "+
	  "effectively seals off the entrance.\n");
	return 1;
    }
    NF("What?\n");
    return 0;
}

void
do_open_portcullis()
{
    gate_closed = 0;
    tell_room(TO,"With a slow rumble the portcullis winds upwards into " +
      "the huge wall, opening the entrance again.\n");
    tell_room(OUTKEEP,"With a slow rumble the portcullis winds upwards into " +
      "the huge wall, opening the entrance again.\n");
}

int
open_portcullis()
{
    if (gate_closed && (TP->id("knight") || TP->query_guild_name_occ() == "Solamnian Knights"))
    {
	write("You wind the cable back up.\n");
	do_open_portcullis();
	return 1;
    }
    NF("What?\n");
    return 0;
}

int
query_portcullis_closed()
{
    return gate_closed;
}


public varargs int
sk_hook_allow_train(object who, string str, string verb)
{
    if (!::sk_hook_allow_train(who, str, verb))
    {
        return 0;
    }
    
    if (who->query_knight_level() < L_CROWN)
    {
        who->catch_msg("Only full Knights in good standing may train here.\n");
        return 0;
    }

    return 1;
}
