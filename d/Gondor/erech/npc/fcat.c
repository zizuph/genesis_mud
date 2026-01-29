/* This is /d/Gondor/common/npc/wrabbit.c
 * A white rabbit
 * Dunstable, Septembet 1993
 */
inherit "/std/creature";
inherit "/std/act/action";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";

#include <const.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../erech.h"

inherit E_QUEST + "tasker";

/*
 * Define some attack and hitloc id's
 */
#define A_JAWS 0
#define A_LPAW 1
#define A_RPAW 2

#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2
#define H_PAWS 3

/* Global variables */
int thirsty;

/* Prototypes */
string long_desc();
int feed(string arg);
void set_thirsty(int arg);
void
create_creature()
{
    set_name("cat");
    set_short("cute gray cat");
    set_long(&long_desc());

    add_adj("cute");
    add_adj("gray");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_NO_GET, 0);

    set_act_time(7);
    add_act("emote purrs and curls himself up.");
    add_act("emote plays with his tail.");
    add_act("emote licks his paws.");
    add_act("purr");

    set_skill(SS_DEFENCE, 25);
    set_skill(SS_UNARM_COMBAT, 15);

    set_attack_unarmed(A_JAWS, 8, 15, W_IMPALE, 30, "jaws");
    set_attack_unarmed(A_LPAW, 10, 10, W_SLASH|W_BLUDGEON, 25, "left paw");
    set_attack_unarmed(A_RPAW, 10, 10, W_SLASH|W_BLUDGEON, 25, "right paw");

    set_hitloc_unarmed(H_HEAD, ({10, 15, 8}), 20, "head");
    set_hitloc_unarmed(H_BODY, ({10, 10, 10}), 50, "head");
    set_hitloc_unarmed(H_TAIL, ({25, 5, 5}), 20, "tail");
    set_hitloc_unarmed(H_PAWS, ({25, 5, 10}), 10, "paws");

    reset_creature();
}

void
reset_creature()
{
    ::reset_creature();
    thirsty = 1;
}

string
long_desc()
{
    if (thirsty == 1)
        return "The cute gray cat looks thirsty.\n";
    else
        return "It is a cute gray cat. It looks playfull.\n";
}

void
init_living()
{
    ::init_living();
    add_action(feed, "feed");
}

int
feed(string arg)
{
    object plate;

    plate = present("Erech_farm_plate", environment(this_object()));

    if (plate == 0)
    {
	write("You stroke the cat on his back.\n");
	say(QCTNAME(this_player()) + " strokes the cat on his back.\n");
	return 1;
    }

    if (arg == "cat")
    {    
        write("You stroke the cat on his back.\n");
	say(QCTNAME(this_player()) + " strokes the cat on his back.\n");
	command("emote purrs luckily.");
	if (thirsty == 1 && plate->query_content() == "milk")
	{
	    command("drink from plate");
	    //	    complete_task(2);
	    set_thirsty(0);
	}
	return 1;
    }
    return 0;
}

void 
set_thirsty(int arg) 
{ 
    if (arg == 0)
        complete_task(2);

    thirsty = arg; 
}
int query_thirsty() { return thirsty; }
