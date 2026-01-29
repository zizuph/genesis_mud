/* Horses for the Knights */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solamn/vin/knight/guild.h"
#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>

#define KNIGHT_I_MANEUVERED "_knight_i_maneuvered"
#define RIDER_SUBLOC "_live_i_mounted"

inherit C_FILE

inherit "/std/act/action";
inherit "/std/act/domove";

object rider, rider_ob;
string owner, barding;
int def_bonus;

void set_owner(object who) { owner = who->query_name(); }
string query_owner() { return owner; }
void set_rider(object who) { rider = who; }
object query_rider() { return rider; }
void set_barding(string s) { barding = s; }
string query_barding() { return barding; }

string short_desc()
{
    return "testing horse";
}

string long_desc()
{
    string str = ", the type favoured by the Knights of Solamnia. "+
    (query_barding() ? "The great steed is adorned in "+query_barding()+"." : "");

    if (!query_rider())
	return "A "+short()+str+"\n";

    if (query_rider() == TP)
	return "You are riding the "+short()+str+"\n";

    return query_rider()->query_The_name(TP)+" is riding the "+short()+
    str+"\n";
}

void create_creature()
{
    set_name("warhorse");
    set_race_name("horse");
    add_name("horse");
    set_short("@@short_desc");
    set_long("@@long_desc");
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_stats(({125, 80, 120, 50, 50, 100}));
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_UNARM_COMBAT, 75);
    set_attack_unarmed(0, 35, 40, W_BLUDGEON, 50, "right hoof");
    set_attack_unarmed(1, 35, 40, W_BLUDGEON, 50, "left hoof");

    set_hitloc_unarmed(0, 30, 25, "head");
    set_hitloc_unarmed(1, 40, 50, "body");
    set_hitloc_unarmed(2, 25, 10, "foreleg");
    set_hitloc_unarmed(3, 30, 10, "hindleg");
    set_hitloc_unarmed(4, 20, 5, "tail");

    set_m_in("comes galloping in.");
    set_m_out("gallops");

    set_alarm(1.0, 0.0, "add_acts");
}

void add_acts()
{
    set_act_time(15);
    add_act("emote suddenly snorts, and tosses "+POSSESSIVE(TO)+ " mane.");
    add_act("emote swings "+POSSESSIVE(TO)+" tail to the side, slapping "+
      POSSESSIVE(TO)+" flank.");
    add_act("emote stomps "+POSSESSIVE(TO)+" hoof on the ground, nighing "+
      "softly.");
    add_act("lowers "+POSSESSIVE(TO)+" head slightly and takes a step "+
      "forward, seemingly preoccupied with something.");
    add_act((query_rider() ? "emote turns "+POSSESSIVE(TO)+" head to the "+
	"side, "+POSSESSIVE(TO)+" large eye studying the rider curiously.\n" :

	"emote suddenly snorts, and tosses "+POSSESSIVE(TO)+" mane."));
    add_act("emote lowers "+POSSESSIVE(TO)+" head, tossing "+POSSESSIVE(TO)+
      " mane from one side to the other.");
    add_act("emote throws back "+POSSESSIVE(TO)+" head and brays loudly.");
    add_act("emote shifts "+POSSESSIVE(TO)+" great weight slightly, the "+
      "powerful muscles rippling beneath "+POSSESSIVE(TO)+" fur.");
    add_act("emote tosses "+POSSESSIVE(TO)+" head around and snorts "+
      "playfully.");

    set_cact_time(20);
    add_cact("emote rears back on "+POSSESSIVE(TO)+" hindlegs and "+
      "brays defiantly!");
}

void init_living()
{
    add_action("mount", "mount");
    add_action("dismount", "dismount");
    add_action("feed_horse", "feed");
    add_action("water_horse", "water");
    ::init_living();
}

void do_mount(object who)
{
    TO->set_no_show();
    TO->unset_no_show();
    TO->set_rider(who);
    clone_object(STEED_SHADOW)->shadow_me(query_rider());
    query_rider()->set_mount(TO);
    rider_ob = clone_object(RIDER_OBJECT);
    rider_ob->move(query_rider());

    def_bonus = query_rider()->query_skill(SS_MOUNTED_COMBAT) / 3;
    query_rider()->set_skill_extra(SS_DEFENCE,
      query_rider()->query_skill_extra(SS_DEFENCE) + def_bonus);
    query_rider()->add_prop(LIVE_O_STEED, TO);
    add_prop(KNIGHT_I_NO_RESCUE, 1);
}

int mount(string str)
{
    int i = random(TP->query_skill(SS_RIDING));

    NF("Mount what?\n");
    if (!str && (!str && TP->query_name() != query_owner()) ||
      (str && !TO->id(str)))
	return 0;

    NF("You are already riding a mount.\n");
    if (TP->query_prop(LIVE_O_STEED))
	return 0;

    NF("You are already riding the " + short() + ".\n");
    if (rider == TP)
	return 0;

    NF("The " + short() + " already has a rider.\n");
    if (rider)
	return 0;

    if (i == 0)
    {
	write("You gather too much momentum as you throw yourself "+
	  "onto the saddle, and slide off of the other side, landing "+
	  "rather unceremoniously on the ground.\n");
	say(QCTNAME(TP)+" pulls "+OBJECTIVE(TP)+"self up onto the "+
	  short()+", but is dumped rather unceremoniously on the "+
	  "ground as "+PRONOUN(TP)+" slips off the saddle.\n");
	return 1;
    }

    if (i < 5)
    {
	write("You manage to pull yourself onto the "+short()+".\n");
	say(QCTNAME(TP)+" manages to pull "+OBJECTIVE(TP)+"self onto "+
	  "the "+short()+".\n");
    }
    else
    {
	write("You skillfully pull yourself onto the back of the "+
	  short()+", feeling comfortable in the saddle.\n");
	say(QCTNAME(TP)+" skillfully pulls "+OBJECTIVE(TP)+"self onto "+
	  "the back of the "+short()+".\n");
    }

    do_mount(TP);
    return 1;
}

void do_dismount()
{
    TO->unset_no_show_composite();
    query_rider()->remove_shadow(STEED_SHADOW);
    rider_ob->remove_object();
    query_rider()->set_skill_extra(SS_DEFENCE,
      query_rider()->query_skill_extra(SS_DEFENCE) - def_bonus);
    remove_prop(OBJ_M_NO_ATTACK);
    remove_prop(KNIGHT_I_NO_RESCUE);
    query_rider()->remove_prop(KNIGHT_I_MANEUVERED);
    query_rider()->remove_prop("_kcharge_resetting");
    query_rider()->remove_prop(LIVE_O_STEED);
    set_rider(0);
}

int dismount(string str)
{
    int i = TP->query_skill(SS_RIDING);

    if (str && (str != "horse" && str != "warhorse"))
	return 0;

    if (rider != TP)
	return 0;

    if (i == 0)
    {
	write("You attempt to dismount, but lose your balance and find "+
	  "yourself short of breath, flat on your back.\n");
	say(QCTNAME(TP)+" loses "+POSSESSIVE(TP)+" balance while trying "+
	  "to dismount, and falls to the ground.\n");
    }
    else if (i < 5 && i > 0)
    {
	write("You manage to dismount, though somewhat awkwardly.\n");
	say(QCTNAME(TP)+" dismounts, somewhat awkwardly.\n");
    }
    else if (i >= 5)
    {
	write("You easily slip out of the saddle, and dismount the "+
	  short()+".\n");
	say(QCTNAME(TP)+" easily slips out of "+POSSESSIVE(TP)+" saddle, "+
	  "dismounting the "+short()+".\n");
    }

    do_dismount();
    return 1;
}

void remove_object()
{
    do_dismount();
    ::remove_object();
}

int water_horse(string str)
{
    object here = E(TO);

    if (TP->query_name() != query_owner() && query_rider() != TP)
	return 0;

    NF("There is no water here for your "+short()+" to drink.\n");
    if (!(here->query_prop(ROOM_I_TYPE) == 1) && 
      (!here->query_prop(OBJ_I_CONTAIN_WATER)))
	return 0;

    NF("Your "+short()+" doesn't seem to be thirsty.\n");
    if (query_soaked() + 100 >= query_prop(LIVE_I_MAX_DRINK))
	return 0;

    tell_room(E(TO), "The "+short()+" drinks from the water.\n");
    set_soaked(query_soaked() + 100);
    return 1;
}

int feed_horse(string str)
{
    object here = E(TO);

    if (TP->query_name() != query_owner() && query_rider() != TP)
	return 0;

    NF("There is nothing here for your "+short()+" to graze on.\n");
    if (!here->item_id("grass") && !here->item_id("bushes") &&
      (!here->item_id("shrubbery")) && !here->item_id("herbs"))
	return 0;

    NF("Your "+short()+" doesn't seem to be hungry.\n");
    if (query_stuffed() + 25 >= query_prop(LIVE_I_MAX_EAT))
	return 0;

    tell_room(E(TO), "The "+short()+" munches on some nearby "+
      "grass.\n");
    set_stuffed(query_stuffed() + 25);
    return 1;
}

void run_away()
{
    object rider = query_rider(), here;
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
	  "reigns as the "+short()+" struggles against them briefly.",
	  rider);
	return;
    }
    else if (i > 25)
    {
	rider->catch_tell("Your horse bucks against the reigns, "+
	  "nearly bolting as you barely retain control of "+
	  OBJECTIVE(TO)+".\n");
	tell_room(E(rider), "You notice "+QTNAME(rider)+" struggling "+
	  "with the reigns of "+POSSESSIVE(rider)+" "+short()+", "+
	  "which looks to be on the verge of bolting.", rider);
	return;
    }
    else if (i < 10)
    {
	rider->catch_tell("Your horse bolts in a random direction, "+
	  "throwing you off as "+PRONOUN(TO)+" bucks wildly.\n");
	tell_room(E(rider), QCTNAME(rider)+"'s "+short()+" bolts "+
	  "in a random direction, throwing "+OBJECTIVE(rider)+
	  " off.", rider);
	do_dismount();
	return ::run_away();
    }

    here = E(TO);
    exits = here->query_exit_cmds();
    i = 1;

    rider->catch_tell("Your horse bolts! You manage to hang on to "+
      "the reigns, but have no control over your steed!\n");
    tell_room(E(rider), QCTNAME(rider)+"'s "+short()+" bolts! "+
      QCTNAME(rider)+" manages to hang on to the reigns.", rider);

    while (i < sizeof(exits) && E(TO) == here)
    {
	rider->command(exits[i - 1]);
	i++;
    }
}

/*
int special_attack(object enemy)
{
    int             penet;
    mixed          *hitresult;
    string         *how;
    int             i;

    i = random(4);
    if (i != 1)
	return 0;

    penet = query_stat(SS_STR);
    penet += random(2 * penet);
    hitresult = enemy->hit_me(penet, W_BLUDGEON, TO, -1);
    how = ({"misses your " + hitresult[1] + " with " + POSSESSIVE(TO) + 
      " front hooves.\n", "misses " + QTNAME(enemy) + "'s " + hitresult[1] + 
      " with " +POSSESSIVE(TO) + " front " + "hooves.\n"});
    if (hitresult[0] > 0)
	how = ({"hits your " + hitresult[1] + " with " + POSSESSIVE(TO) + 
	  " front hooves.\n", "hits " + QTNAME(enemy) + "'s " + 
	  hitresult[1] + " with " +POSSESSIVE(TO) + " front " +
	  "hooves.\n"});
    if (hitresult[0] > 10)
	how = ({"hurts your " + hitresult[1] + " with " + POSSESSIVE(TO) + 
	  " front hooves.\n", "hurts " + QTNAME(enemy) + "'s " + 
	  hitresult[1] + " with " +POSSESSIVE(TO) + " front hooves.\n"});
    if (hitresult[0] > 20)
	how = ({"strikes your " + hitresult[1] + " fiercefully with " +
	  POSSESSIVE(TO) + " front hooves.\n", "strikes " + QTNAME(enemy) + 
	  "'s " + hitresult[1] + " fiercefully with " + POSSESSIVE(TO) + 
	  " front hooves.\n"});
    if (hitresult[0] > 35)
	how = ({"pounds your " + hitresult[1] + " forcefully with " +
	  POSSESSIVE(TO) + " front hooves.\n", "pounds " + QTNAME(enemy) + 
	  "'s " + hitresult[1] + " forrcefully with " + POSSESSIVE(TO) + 
	  " front hooves.\n"});
    if (hitresult[0] > 50)
	how = ({"crushes your " + hitresult[1] + " with a mighty blow of " +
	  POSSESSIVE(TO) + " front hooves.\n", "crushes " + QTNAME(enemy) + 
	  "'s "+ hitresult[1] + " a mighty blow of "+ POSSESSIVE(TO)+
	  " front hooves.\n"});
enemy->catch_tell(rider->query_The_name(enemy)+"'s "+short()+" rises up on "+
      POSSESSIVE(TO) + " hindlegs and " + how[0] + ".\n");
    rider->catch_tell("Your " + short() + " rises up on " + POSSESSIVE(TO) + 
      " hindlegs " + "and " + how[1] + ".\n");
    tell_watcher(QCTNAME(rider) + "'s " + short() + " rises up on " +
      POSSESSIVE(TO) + " hindlegs and " + how[1] + ".\n", ({enemy, rider}));
    return 1;
}
*/

