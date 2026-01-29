// Test steed
// Fysix, April 1997

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solamn/vin/knight/guild.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#define KNIGHT_I_MANEUVERED "_knight_i_maneuvered"
// (il)legal destinations
#define ROOM_I_ALLOW_STEED "_room_i_allow_steed"
#define ROOM_I_NO_ALLOW_STEED "_room_i_no_allow_steed"

inherit "/d/Gondor/fysix/open/steed";

inherit "/std/act/action";
inherit "/std/act/chat";

// --- globals ---
static int     Def_bonus;
static string  Owner, Barding;
static object  Rider_ob;  // emote object

// --- prototypes ---

void add_acts();

public void   set_owner(object who) { Owner = who->query_name(); }
public string query_owner()         { return Owner; }

public void   set_barding(string s) { Barding = s; }
public string query_barding()       { return Barding; }

string
long_desc()
{
    string str = ", the type favoured by the Knights of Solamnia. "+
    (query_barding() ? "The great steed is adorned in "+query_barding()+"." : "");

    return "A " + short_old() + str + "\n";
}

public int
check_destination(mixed to_dest)
{
    object here = E(TO), room;

    if (!stringp(LOAD_ERR(to_dest)))
	if (!objectp(to_dest))
	    to_dest = find_object(to_dest);

    room = to_dest; 

    if (room->query_prop(ROOM_I_INSIDE))
    {
	if (!here->query_prop(ROOM_I_INSIDE))
	{
	    return room->query_prop(ROOM_I_ALLOW_STEED);
	}
	else
	{
	    return (room->query_prop(ROOM_I_NO_ALLOW_STEED) ? 0 : 1);
	}
    }

    return (room->query_prop(ROOM_I_NO_ALLOW_STEED) ? 0 : 1);
}


void
create_steed()
{
    // --- usual stuff ---
    set_name("horse");
    set_adj(({"tall", "white"}));
    set_gender(2);

    set_stats(({ 120, 80, 120, 30, 30, 100 }));
    set_long(long_desc);

    set_m_in("comes galloping in.");
    set_m_out("gallops");


    set_stuffed(TO->query_prop(LIVE_I_MAX_EAT));
    add_acts();

    // --- Steed functions ---   
    set_max_riders(1);   // standard only 1 rider can ride the horse

    // Standard the horse doesn't allow mounted combat
    allow_mounted_combat(1);         // Allow mounted combat

    // set allowed food for the steed
    set_allowed_food(({"hay", "oats", "barley", "sugar"}));

    add_valid_dest(ROOM_I_ALLOW_STEED);
    add_invalid_dest(ROOM_I_NO_ALLOW_STEED);

    // Optional: use what file as shadow? the shadow should inherit the
    // genuine steed shadow. Otherwise you just use the standard shadow
    set_steed_shadow(STEED_SHADOW);
}

// add acts
void
add_acts()
{
    set_act_time(15);
    add_act("emote suddenly snorts, and tosses "+POSSESSIVE(TO)+ " mane.");
    add_act("emote swings "+POSSESSIVE(TO)+" tail to the side, slapping "+
      POSSESSIVE(TO)+" flank.");
    add_act("emote stomps "+POSSESSIVE(TO)+" hoof on the ground, neighing "+
      "softly.");
    add_act("lowers "+POSSESSIVE(TO)+" head slightly and takes a step "+
      "forward, seemingly preoccupied with something.");
    add_act((query_driver() ? "emote turns "+POSSESSIVE(TO)+" head to the "+
	"side, "+POSSESSIVE(TO)+" large eye studying the rider curiously.\n" :

	"emote suddenly snorts, and tosses "+POSSESSIVE(TO)+" mane."));
    add_act("emote lowers "+POSSESSIVE(TO)+" head, tossing "+POSSESSIVE(TO)+
      " mane from one side to the other.");
    add_act("emote throws back "+POSSESSIVE(TO)+" head and whinnies loudly.");
    add_act("emote shifts "+POSSESSIVE(TO)+" great weight slightly, the "+
      "powerful muscles rippling beneath "+POSSESSIVE(TO)+" fur.");
    add_act("emote tosses "+POSSESSIVE(TO)+" head around and snorts "+
      "playfully.");

    set_cact_time(20);
    add_cact("emote rears back on "+POSSESSIVE(TO)+" hindlegs and "+
      "whinnies defiantly!");
}

// returns 1 if player may mount
public int
can_mount(object rider)
{
    int i = random(rider->query_skill(SS_RIDING));

    if (i == 0)
    {
	NF("You gather too much momentum as you throw yourself "+
	  "onto the saddle, and slide off of the other side, landing "+
	  "rather unceremoniously on the ground.\n");
	tell_room(E(rider), 
	  QCTNAME(rider)+" pulls "+OBJECTIVE(rider)+"self up onto the "+
	  short_old()+", but is dumped rather unceremoniously on the "+
	  "ground as "+PRONOUN(rider)+" slips off the saddle.\n", rider);
	return 0;
    }

    if (i < 5)
    {
	rider->catch_tell("You manage to pull yourself onto the "+short_old()+".\n");
	tell_room(E(rider),
	  QCTNAME(rider)+" manages to pull "+OBJECTIVE(rider)+"self onto "+
	  "the "+short_old()+".\n", rider);
    }
    else
    {
	rider->catch_tell("You skillfully pull yourself onto the back of the "+
	  short_old()+", feeling comfortable in the saddle.\n");
	tell_room(E(rider),
	  QCTNAME(rider)+" skillfully pulls "+OBJECTIVE(rider)+"self onto "+
	  "the back of the "+short_old()+".\n", rider);
    }
    return 1;
}

// masking do-mount to add some extras
public varargs int
do_mount(object rider, int silent = 0)
{
    // messages are handle by can_mount
    if (!::do_mount(rider, 1))
	return 0;

    Rider_ob = clone_object(RIDER_OBJECT);
    Rider_ob->move(rider);

    Def_bonus = rider->query_skill(SS_MOUNTED_COMBAT) / 3;
    rider->set_skill_extra(SS_DEFENCE,
      rider->query_skill_extra(SS_DEFENCE) + Def_bonus);
    return 1;
}

// masking do_dismount to add some extras
public varargs int
sh_do_dismount(object rider, int silent = 0, int force = 0)
{
    int i = rider->query_skill(SS_RIDING);

    if (!(::sh_do_dismount(rider, 1, force)))
	return 0;

    if (!silent)
    {
	// Give some cool messages
	if (i == 0)
	{
	    rider->catch_tell("You attempt to dismount, but lose your balance and find "+
	      "yourself short of breath, flat on your back.\n");
	    tell_room(E(rider),
	      QCTNAME(rider)+" loses "+POSSESSIVE(rider)+" balance while trying "+
	      "to dismount, and falls to the ground.\n", rider);
	}
	else if (i < 5 && i > 0)
	{
	    rider->catch_tell("You manage to dismount, though somewhat awkwardly.\n");
	    tell_room(E(rider), 
	      QCTNAME(rider)+" dismounts, somewhat awkwardly.\n", rider);
	}
	else if (i >= 5)
	{
	    rider->catch_tell("You easily slip out of the saddle, and dismount the "+
	      short_old()+".\n");
	    tell_room(E(rider), 
	      QCTNAME(rider)+" easily slips out of "+POSSESSIVE(rider)+" saddle, "+
	      "dismounting the "+short_old()+".\n", rider);
	}
    } // end-if silent

    // some extras
    Rider_ob->remove_object();
    rider->set_skill_extra(SS_DEFENCE,
      rider->query_skill_extra(SS_DEFENCE) - Def_bonus);
    remove_prop(OBJ_M_NO_ATTACK);
    rider->remove_prop(KNIGHT_I_MANEUVERED);
    rider->remove_prop("_kcharge_resetting");
    return 1;
}

// --- actions ---

int
water_horse(string str)
{
    object here = E(TO);

    if (TP->query_name() != query_owner() && query_driver() != TP)
	return 0;

    NF("There is no water here for your "+short_old()+" to drink.\n");
    if (!(here->query_prop(ROOM_I_TYPE) == 1) && 
      (!here->query_prop(OBJ_I_CONTAIN_WATER)))
	return 0;

    NF("Your "+short_old()+" doesn't seem to be thirsty.\n");
    if (query_soaked() + 100 >= query_prop(LIVE_I_MAX_DRINK))
	return 0;

    tell_room(E(TO), "The "+short_old()+" drinks from the water.\n");
    set_soaked(query_soaked() + 100);
    return 1;
}

int
feed_horse(string str)
{
    object here = E(TO);

    if (TP->query_name() != query_owner() && query_driver() != TP)
	return 0;

    NF("There is nothing here for your "+short_old()+" to graze on.\n");
    if (!here->item_id("grass") && !here->item_id("bushes") &&
      (!here->item_id("shrubbery")) && !here->item_id("herbs"))
	return 0;

    NF("Your "+short_old()+" doesn't seem to be hungry.\n");
    if (query_stuffed() + 25 >= query_prop(LIVE_I_MAX_EAT))
	return 0;

    tell_room(E(TO), "The "+short_old()+" munches on some nearby "+
      "grass.\n");
    set_stuffed(query_stuffed() + 25);
    return 1;
}

// add some actions
void
init_living()
{
    add_action(feed_horse, "graze");
    add_action(water_horse, "water");
    ::init_living();
}

void
run_away()
{
    object rider = query_driver(), here;
    int dis = rider->query_stat(SS_DIS);
    int skill = rider->query_skill(SS_RIDING);
    int i = random((dis+skill) / 2);
    string *exits;

    if (!rider)
	return ::run_away();

    /*
    if (rider->query_wiz_level())
       return;
    */

    if (i > 50)
    {
	rider->catch_tell("Your horse struggles against the reigns, "+
	  "but you expertly jerk them back, retaining control of "+
	  "the nervous steed.\n");
	tell_room(E(rider), "You notice "+QTNAME(rider)+" jerk the "+
	  "reigns as the "+short_old()+" struggles against them briefly.",
	  rider);
	return;
    }
    else if (i > 25)
    {
	rider->catch_tell("Your horse bucks against the reigns, "+
	  "nearly bolting as you barely retain control of "+
	  OBJECTIVE(TO)+".\n");
	tell_room(E(rider), "You notice "+QTNAME(rider)+" struggling "+
	  "with the reigns of "+POSSESSIVE(rider)+" "+short_old()+", "+
	  "which looks to be on the verge of bolting.", rider);
	return;
    }
    else if (i < 10)
    {
	rider->catch_tell("Your horse bolts in a random direction, "+
	  "throwing you off as "+PRONOUN(TO)+" bucks wildly.\n");
	tell_room(E(rider), QCTNAME(rider)+"'s "+short_old()+" bolts "+
	  "in a random direction, throwing "+OBJECTIVE(rider)+
	  " off.", rider);
	dismount_all(1);
	return ::run_away();
    }

    here = E(TO);
    exits = here->query_exit_cmds();
    i = 1;

    rider->catch_tell("Your horse bolts! You manage to hang on to "+
      "the reigns, but have no control over your steed!\n");
    tell_room(E(rider), QCTNAME(rider)+"'s "+short_old()+" bolts! "+
      QCTNAME(rider)+" manages to hang on to the reigns.", rider);

    while (i < sizeof(exits) && E(TO) == here)
    {
	rider->command(exits[i - 1]);
	i++;
    }
}

