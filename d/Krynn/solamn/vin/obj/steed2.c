// Fysix, April 1997
// May 2003, added new steed code

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solamn/vin/knight/guild.h"
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>

#define KNIGHT_I_MANEUVERED "_knight_i_maneuvered"

inherit "/d/Genesis/steed/new/steed";
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

    return "A " + short(TO) + str + "\n";
}

void
create_steed()
{
    // --- usual stuff ---
    set_name("horse");
    add_name(({ "steed", "warhorse" }));
    set_adj(({"tall", "white"}));
    set_gender(2);

    set_stats(({ 140, 100, 140, 30, 30, 120 }));
    set_skill(SS_CLIMB, 25);
    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_SWIM, 40);
    set_skill(SS_AWARENESS, 40);
    set_long(long_desc);

    set_m_in("comes galloping in");
    set_m_out("gallops");


    set_stuffed(TO->query_prop(LIVE_I_MAX_EAT));
    add_acts();

    // --- Steed functions ---
    // Added two riders to allow passanger (Boron Dec 1999)
    set_max_riders(2);   // standard only 1 rider can ride the horse
    set_no_trans(0);

    allow_mounted_combat(1);

    // set allowed food for the steed
    set_allowed_food(({"apple", "oat", "hay", "oats",
    "carrot", "celery", "brocooli", "barley", "sugar"}));

    // Optional: use what file as shadow? the shadow should inherit the
    // genuine steed shadow. Otherwise you just use the standard shadow
    set_rider_shadow_file(STEED_SHADOW);

    add_prop(KNIGHT_I_NO_RESCUE, 1);
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
      "powerful muscles rippling beneath "+POSSESSIVE(TO)+" hair.");
    add_act("emote tosses "+POSSESSIVE(TO)+" head around and snorts "+
      "playfully.");

    set_cact_time(20);
    add_cact("emote rears back on "+POSSESSIVE(TO)+" hindlegs and "+
      "whinnies defiantly!");
}

void
st_hook_fail_mount(object rider)
{
    tell_object(rider,
      "You gather too much momentum as you throw yourself "+
      "onto the saddle, and slide off of the other side, landing "+
      "rather unceremoniously on the ground.\n");
    tell_room(E(rider),
      QCTNAME(rider)+" pulls "+OBJECTIVE(rider)+"self up onto the "+
      short(TO)+", but is dumped rather unceremoniously on the "+
      "ground as "+PRONOUN(rider)+" slips off the saddle.\n", rider);
}

public int
st_hook_try_mount(object rider)
{
   if ((rider->query_skill(SS_RIDING) == 0) ||
       (!TP->query_knight_sublevel()) )
    {
    return 0;
    }

    return 1;
}

void
st_hook_did_mount(object rider)
{
    int skill = random(rider->query_skill(SS_RIDING));

    if (skill < 5)
    {
    rider->catch_tell(
        "You manage to pull yourself onto the "+short(TO)+".\n");
    tell_room(E(rider),
      QCTNAME(rider)+" manages to pull "+OBJECTIVE(rider)+"self onto "+
      "the "+short(TO)+".\n", rider);
    }
    else
    {
    rider->catch_tell("You skillfully pull yourself onto the back of the "+
      short(TO)+", feeling comfortable in the saddle.\n");
    tell_room(E(rider),
      QCTNAME(rider)+" skillfully pulls "+OBJECTIVE(rider)+"self onto "+
      "the back of the "+short(TO)+".\n", rider);
    }

    if (!(ADMIN)->query_cavalry(rider->query_name()))
    return;

    Rider_ob = clone_object(RIDER_OBJECT);
    Rider_ob->move(rider);

    Def_bonus = rider->query_skill(SS_MOUNTED_COMBAT) / 3;
    if (rider->query_skill(SS_DEFENCE) + Def_bonus > 100)
       Def_bonus = 100 - rider->query_skill(SS_DEFENCE);

    rider->set_skill_extra(SS_DEFENCE,
      rider->query_skill_extra(SS_DEFENCE) + Def_bonus);
}

public void
st_hook_did_dismount(object rider)
{
    int i = rider->query_skill(SS_RIDING);

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
          short(TO)+".\n");
        tell_room(E(rider),
          QCTNAME(rider)+" easily slips out of "+POSSESSIVE(rider)+" saddle, "+
          "dismounting the "+short(TO)+".\n", rider);
    }

    if (!(ADMIN)->query_cavalry(rider->query_name()))
    return;

    Rider_ob->remove_object();
    rider->set_skill_extra(SS_DEFENCE,
      rider->query_skill_extra(SS_DEFENCE) - Def_bonus);
    remove_prop(OBJ_M_NO_ATTACK);
}

// --- actions ---

int
water_horse(string str)
{
    object here = E(TO);

    if (TP->query_name() != query_owner() && query_driver() != TP)
    return 0;

    NF("There is no water here for your "+short(TO)+" to drink.\n");
    if (!(here->query_prop(ROOM_I_TYPE) == 1) &&
      (!here->query_prop(OBJ_I_CONTAIN_WATER)))
    return 0;

    NF("Your "+short(TO)+" doesn't seem to be thirsty.\n");
    if (query_soaked() + 100 >= query_prop(LIVE_I_MAX_DRINK))
    return 0;

    tell_room(E(TO), "The "+short(TO)+" drinks from the water.\n");
    set_soaked(query_soaked() + 100);
    return 1;
}

int
feed_horse(string str)
{
    object here = E(TO);

    if (TP->query_name() != query_owner() && query_driver() != TP)
    return 0;

    NF("There is nothing here for your "+short(TO)+" to graze on.\n");
    if (!here->item_id("grass") && !here->item_id("bushes") &&
      (!here->item_id("shrubbery")) && !here->item_id("herbs"))
    return 0;

    NF("Your "+short(TO)+" doesn't seem to be hungry.\n");
    if (query_stuffed() + 25 >= query_prop(LIVE_I_MAX_EAT))
    return 0;

    tell_room(E(TO), "The "+short(TO)+" munches on some nearby "+
      "grass.\n");
    set_stuffed(query_stuffed() + 25);
    return 1;
}

// add some actions
void
init_living()
{
    ::init_living();
    add_action(feed_horse, "graze");
    add_action(water_horse, "water");
}

void
do_die(object killer)
{
    object rider = query_driver(),
           own = (query_owner() ? find_player(L(query_owner())) : 0);

    if (query_hp() > 0)
      return;

    if (own &&
    (own == rider || E(own) == E(TO)))
    {
    own->catch_msg("You lose prestige for getting your horse killed.\n");
    own->sub_prestige(own->query_skill(SS_PRESTIGE_ACC)/6);
    }

    ::do_die(killer);
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
    rider->catch_tell("Your horse struggles against the reins, "+
      "but you expertly jerk them back, retaining control of "+
      "the nervous steed.\n");
    tell_room(E(rider), "You notice "+QTNAME(rider)+" jerk the "+
      "reins as the "+short(TO)+" struggles against them briefly.",
      rider);
    return;
    }
    else if (i > 25)
    {
    rider->catch_tell("Your horse bucks against the reins, "+
      "nearly bolting as you barely retain control of "+
      OBJECTIVE(TO)+".\n");
    tell_room(E(rider), "You notice "+QTNAME(rider)+" struggling "+
      "with the reins of "+POSSESSIVE(rider)+" "+short(TO)+", "+
      "which looks to be on the verge of bolting.", rider);
    return;
    }
    else if (i < 10)
    {
    rider->catch_tell("Your horse bolts in a random direction, "+
      "throwing you off as "+PRONOUN(TO)+" bucks wildly.\n");
    tell_room(E(rider), QCTNAME(rider)+"'s "+short(TO)+" bolts "+
      "in a random direction, throwing "+OBJECTIVE(rider)+
      " off.", rider);
    dismount_all(1);
    return ::run_away();
    }

    here = E(TO);
    exits = here->query_exit_cmds();
    i = 1;

    rider->catch_tell("Your horse bolts! You manage to hang on to "+
      "the reins, but have no control over your steed!\n");
    tell_room(E(rider), QCTNAME(rider)+"'s "+short(TO)+" bolts! "+
      QCTNAME(rider)+" manages to hang on to the reins.", rider);

    while (i < sizeof(exits) && E(TO) == here)
    {
    rider->command(exits[i - 1]);
    i++;
    }
}


int
st_hook_try_lead(object player)
{
    return MEMBER(player);
}
