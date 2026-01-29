#pragma strict_types

#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include "rider_defs.h"

inherit "/d/Genesis/steed/steed";
inherit "/d/Genesis/steed/feeding";
inherit "/std/act/action";


#define RAND_ONEOF(arr)      arr[random(sizeof(arr))]

static int Def_bonus = 0;
static string owner = "milashk";

void
create_steed()
{
    set_race_name("bear");
    set_name("smokey");
    set_long("Unconfigured Bear rider bear. You should never see "
    +"this, please report to the guildmaster.\n");
    set_stats(({ 140, 100, 140, 30, 30, 120 }));
    set_skill(SS_CLIMB, 25);
    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_SWIM, 40);

    set_act_time(10);
//    add_act(VBFC_ME("bear_act"));

    set_stuffed(TO->query_prop(LIVE_I_MAX_EAT));
    set_allowed_food (({ "hay", "oats", "barley",
        "sugar", "grass", "fruit", "apple", "herb",
        "vegetable" }));

    add_valid_dest(ROOM_I_ALLOW_STEED);
    add_invalid_dest(ROOM_I_NO_ALLOW_STEED);

    set_max_riders(1);
    allow_mounted_combat(1);
    set_no_trans(0);
}

public void
configure_rider_steed(string name,object o,string desc,string colour,int gender)
{
    owner = o->query_real_name();
    set_name(lower_case(name));
    set_adj(({desc,colour}));
    set_gender(gender);
    set_long(CAP(PRONOUN(TO))+" is a " + desc + " " + colour + " bear, "
    +"a ferocious creature bred for combat by .\n");
    remove_prop(LIVE_I_NEVERKNOWN); 
    add_prop(LIVE_I_NON_REMEMBER,1);
}

public void
set_owner(object o)
{
    owner = o->query_real_name();
}

public string
query_owner()
{
    return owner;
}

public int
is_owner(object o)
{
    return o->query_real_name() == owner;
}

public int
notmet_me(object obj) // Owner should always know his horse
{
    if (is_owner(obj))
        return 0;
    return ::notmet_me(obj);
}

public int
can_lead(object living)
{
    return IS_RIDER(living);
}

public int
can_mount(object living)
{
    return IS_RIDER(living);
}

string
bear_act()
{
    object env = environment(this_object());
/*
    if(wildmatch(GUILD_DIR + "stable*", file_name(env)))
    {
        return "emote nibbles at the high grass.";
    }
*/

}


public void
emote_hook(string emote, object actor, string adverb = 0)
{
    switch (emote)
    {
    case "pet":
    case "cuddle":
    case "ruffle":
    case "pat":
    case "kiss":
    case "lick":
    case "fondle":
    case "hug":
        command ("emote whinnies " +
                 RAND_ONEOF (({ "happily", "contentedly", "merrily", "joyfully"}))
                 + ".");
        break;

    case "poke":
    case "kick":
    case "swear":
    case "spit":
    case "curse":
        command ("emote snorts " +
                 RAND_ONEOF (({ "angrily", "ill-temperedly", "unhappily", "menacingly" }))
                 + ".");
        break;

    case "chastise":
        command ("emote hangs its head in shame.");
        break;
    }
}

string query_guild_name_occ() { return "Rider Bear"; }

public varargs int
do_mount(object rider, int silent = 0)
{
    // messages are handle by can_mount
    if (!::do_mount(rider, silent))
        return 0;

    if (member_array(rider, query_riders()) < 0)
       return 0;

    //Rider_ob = clone_object(RIDER_OBJECT);
    //Rider_ob->move(rider);

    Def_bonus = rider->query_skill(SS_MOUNTED_COMBAT) / 3;

    if (rider->query_skill(SS_DEFENCE) + Def_bonus > 100)
       Def_bonus = 100 - rider->query_skill(SS_DEFENCE);

    rider->set_skill_extra(SS_DEFENCE,
      rider->query_skill_extra(SS_DEFENCE) + Def_bonus);
    return 1;
}

public varargs int
sh_do_dismount(object rider, int silent = 0, int force = 0)
{
    int i = rider->query_skill(SS_RIDING);

    if (!(::sh_do_dismount(rider, silent, force)))
        return 0;

    //Rider_ob->remove_object();
    rider->set_skill_extra(SS_DEFENCE,
      rider->query_skill_extra(SS_DEFENCE) - Def_bonus);
    remove_prop(OBJ_M_NO_ATTACK);
    return 1;
}

// --- actions ---

int
water_bear(string str)
{
    object here = ENV(TO);

    if (query_driver() != TP)
        return 0;

    NF("There is no water here for your "+short_old()+" to drink.\n");
    if (!(here->query_prop(ROOM_I_TYPE) == 1) &&
      (!here->query_prop(OBJ_I_CONTAIN_WATER)))
        return 0;

    NF("Your "+short_old()+" doesn't seem to be thirsty.\n");
    if (query_soaked() + 100 >= query_prop(LIVE_I_MAX_DRINK))
        return 0;

    tell_room(ENV(TO), "The "+short_old()+" drinks from the water.\n");
    set_soaked(query_soaked() + 100);
    return 1;
}

int
feed_bear(string str)
{
    object here = ENV(TO);

    if (query_driver() != TP)
        return 0;

    NF("There is nothing here for your "+short_old()+" to graze on.\n");
    if (!here->item_id("grass") && !here->item_id("bushes") &&
      (!here->item_id("shrubbery")) && !here->item_id("herbs"))
        return 0;

    NF("Your "+short_old()+" doesn't seem to be hungry.\n");
    if (query_stuffed() + 25 >= query_prop(LIVE_I_MAX_EAT))
        return 0;

    tell_room(ENV(TO), "The "+short_old()+" munches on some nearby "+
      "grass.\n");
    set_stuffed(query_stuffed() + 25);
    return 1;
}

// add some actions
void
init_living()
{
    add_action(feed_bear, "graze");
    add_action(water_bear, "water");
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
        rider->catch_tell("Your bear struggles against the reins, "+
          "but you expertly jerk them back, retaining control of "+
          "the nervous animal.\n");
        tell_room(ENV(rider), "You notice "+QTNAME(rider)+" jerk the "+
          "reins as the "+short_old()+" struggles against them briefly.",
          rider);
        return;
    }
    else if (i > 25)
    {
        rider->catch_tell("Your bear bucks against the reins, "+
          "nearly bolting as you barely retain control of "+
          OBJECTIVE(TO)+".\n");
        tell_room(ENV(rider), "You notice "+QTNAME(rider)+" struggling "+
          "with the reins of "+POSSESSIVE(rider)+" "+short_old()+", "+
          "which looks to be on the verge of bolting.", rider);
        return;
    }
    else if (i < 10)
    {
        rider->catch_tell("Your bear bolts in a random direction, "+
          "throwing you off as "+PRONOUN(TO)+" bucks wildly.\n");
        tell_room(ENV(rider), QCTNAME(rider)+"'s "+short_old()+" bolts "+
          "in a random direction, throwing "+OBJECTIVE(rider)+
          " off.", rider);
        dismount_all(1);
        return ::run_away();
    }

    here = ENV(TO);
    exits = here->query_exit_cmds();
    i = 1;

    rider->catch_tell("Your bear bolts! You manage to hang on to "+
      "the reins, but have no control over your steed!\n");
    tell_room(ENV(rider), QCTNAME(rider)+"'s "+short_old()+" bolts! "+
      QCTNAME(rider)+" manages to hang on to the reins.", rider);

    while (i < sizeof(exits) && ENV(TO) == here)
    {
        rider->command(exits[i - 1]);
        i++;
    }
}

void
do_die(object killer)
{
    if (query_hp() > 0)
        return;
    (RIDER_DIR+"stables")->steed_has_died(query_real_name());
    ::do_die(killer);
}

/*****************************************************************
 * Everything below is cut'n'paste from the original steed file,
 * but adjusted to accomodate for steeds having proper names.
 */

public void
mount_hook(object o)
{
   o->catch_tell("You mount " + query_the_name(o) + ".\n");
   tell_room(environment(this_object()), QCTNAME(o) + " mounts " +
      QTNAME(TO) + ".\n", o);
}

public void
dismount_hook(object o)
{
   o->catch_tell("You dismount " + query_the_name(o) + ".\n");
   tell_room(environment(this_object()), QCTNAME(o) +
      " dismounts " + QTNAME(TO) + ".\n", o);
}

public varargs void
invalid_dest_hook(object o, string where_to)
{
   o->catch_tell(query_The_name(o) +
      " refuses to " + (strlen(where_to) ? where_to : "go there") +
      ".\n");
}

public void
steed_is_tired_hook(object o)
{
   o->catch_tell(query_The_name(o) +
      " is too tired to go there.\n");
}

public void
lead_hook(object o)
{
   o->catch_tell("You start leading " + query_the_name(o) + ".\n");
   tell_room(environment(), QCTNAME(o) + " starts leading " +
      QTNAME(TO) + ".\n", o);
}

public void
unlead_hook(object o)
{
   o->catch_tell("You stop leading " + query_the_name(o) + ".\n");
   tell_room(environment(), QCTNAME(o) + " stops leading " +
      QTNAME(TO) + ".\n", o);
}

public int
check_combat(object o)
{
   if (mounted_combat())
      return 1;

   if (objectp(o->query_attack()))
   {
      o->catch_tell("You are too busy fighting to mount " +
         query_the_name(o) + ".\n");
      return 0;
   }

   if (objectp(query_attack()))
   {
      o->catch_tell(query_The_name(o) + " is occupied in combat and " +
         "it is too difficult too mount.\n");
      return 0;
   }

   return 1;
}

public string
query_rider_m_in(object rider)
{
   return "arrives riding "+LANG_ADDART(TO->query_nonmet_name());
}

public string
query_rider_m_out(object rider)
{
   return "rides the "+TO->query_nonmet_name();
}

