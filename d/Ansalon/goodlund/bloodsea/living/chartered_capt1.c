#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"

inherit AM_FILE
object Aowner;
string Aowner_name;

string *gAdj1 = ({"tanned","rugged","dark-eyed","grey-bearded",
  "muscular","friendly","jovial","red-faced",
  "ugly","big-eared","big-nosed","tall","short","fat"});

/*
void sail_dir(string str);
*/

EMOTE_HOOK

#define WEP1 "/d/Ansalon/balifor/flotsam/obj/weapon/b_pin"
#define FARM "/d/Ansalon/balifor/flotsam/obj/armour/"

#define PEARL "/d/Genesis/gems/obj/pearl"
#define NET "/d/Calia/sea/objects/fish_net"
#define sX 30 + random(60)
#define SAILING_SKILL 143020

#define CURRENTLY_SAILING  "_charter_captain_currently_sailing"

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

int captain_lvl = 0;

void
set_owner_name(object ob)
{
    if(!ob)
	return;

    if(!ob->query_real_name())
	return;

    Aowner_name = ob->query_real_name();
    return;
}

string
query_owner_name()
{
    return Aowner_name;
}


int
set_owner(object ob)
{
    if(!ob)
	return 0;

    Aowner = ob;
    set_owner_name(ob);
    return 1;
}

object
query_owner()
{
    return Aowner;
}

public void
not_enough_skill_response()
{
    set_alarm(0.5,0.0, &command("$say That way looks " +
        "too dangerous! I don't think aye have the " +
        "sailing skill to take you there!"));
    return;
}

public void
ship_too_small_response()
{
    set_alarm(0.2,0.0, &command("$say That way looks " +
        "too dangerous for this lugger! We'll need " +
        "a bigger ship to sail those waters!"));
    return;
}

void
create_charter_captain()
{
    remove_name("fisherman");

    switch(captain_lvl)
    {
        case 1:
            set_name("mariner");
            add_name("_ansalon_charter_captain");
            set_adj(ONE_OF(gAdj1)); 
            set_short(query_adj() + " mariner");
            set_race_name("human");
            set_long("You look upon a skilled mariner, one who is experienced " +
              "at sailing the seas of Krynn. " +
              "This particular mariner has been chartered to sail " +
              "passengers around the coastline, and can be <order>ed to " +
              "sail along the safer sea routes and some of the more challenging " +
              "reefs and rough waters.\n");
            set_stats(({145,145,145,145,145,140}));
            set_hp(10000);

            set_skill(SS_WEP_CLUB, 80);
            set_skill(SS_WEP_SWORD, 80);
            set_skill(SS_WEP_AXE, 80);
            set_skill(SS_DEFENCE, 65);
            set_skill(SS_PARRY, 65);
            set_skill(SAILING_SKILL, 75);

            set_alignment(0);
            set_all_hitloc_unarmed(40); 

            set_act_time(13);
            add_act("ahoy Ahoy landlubber!");
            add_act("assist");
            add_act("peer");
            add_act("shout All hands to deck!");
            add_act("say Ware the reefs! Many a sailor has met their " +
                "doom holing their ship!");
            add_act("emote adjusts the ropes of a sail.");
            add_act("emote trims the sails slightly.");
            break;
        case 2:
            set_name("captain");
            add_name("_ansalon_charter_captain");
            set_adj(ONE_OF(gAdj1)); 
            add_adj("sea");
            set_short(query_adj() + " sea captain");
            set_race_name("human");
            set_long("You look upon a master mariner, an experienced " +
              "sea captain that has sailed the four corners of the seas of Krynn. " +
              "This particular sea captain has been chartered to sail " +
              "passengers around the coastline, and can be <order>ed to " +
              "sail routes from the mundane to the extremely adventurous!\n");
            set_stats(({195,195,195,195,195,190}));
            set_hp(10000);

            set_skill(SS_WEP_CLUB, 90);
            set_skill(SS_WEP_SWORD, 90);
            set_skill(SS_WEP_AXE, 90);
            set_skill(SS_DEFENCE, 85);
            set_skill(SS_PARRY, 85);
            set_skill(SAILING_SKILL, 90);

            set_alignment(0);
            set_all_hitloc_unarmed(60); 

            set_act_time(13);
            add_act("ahoy Ahoy landlubber!");
            add_act("assist");
            add_act("peer");
            add_act("shout All hands to deck!");
            add_act("say Ware the reefs! Many a sailor has met their " +
                "doom holing their ship!");
            add_act("emote adjusts the ropes of a sail.");
            add_act("emote trims the sails slightly.");
            break;
        default:
            set_name("fisherman");
            add_name("_ansalon_charter_captain");
            set_adj(ONE_OF(gAdj1)); 
            set_short(query_adj() + " fisherman");
            set_race_name("human");
            set_long("You look upon the muscular figure of one of " +
              "the many fisherman who ply a living on the Turbidus Ocean. " +
              "This particular fisherman has been chartered to sail " +
              "passengers around the coastline, and can be <order>ed to " +
              "sail along the safer sea routes.\n");
            set_stats(({85,85,85,85,85,90}));
            set_hp(10000);

            set_skill(SS_WEP_CLUB, 50 + random(50));
            set_skill(SS_WEP_SWORD, 50 + random(50));
            set_skill(SS_WEP_AXE, 50 + random(50));
            set_skill(SS_DEFENCE, 30 + random(70));
            set_skill(SS_PARRY, 30 + random(70));
            set_skill(SAILING_SKILL, 60);

            set_alignment(0);
            set_all_hitloc_unarmed(20); 

            set_act_time(8);
            add_act("ahoy Ahoy landlubber!");
            add_act("assist");
            add_act("peer");
            add_act("shout All hands to deck!");
            add_act("say I know there is a shoal of fish around here!");
            add_act("emote checks his nets for fish.");
            add_act("emote trims the sails slightly.");
            break;
    }

    return;
}

public void
set_captain_lvl(int lvl)
{
    captain_lvl = lvl;
    create_charter_captain();
    return;
}

public int
query_captain_lvl()
{
    return captain_lvl;
}

mixed
no_attack()
{
   if(captain_lvl > 1)
   {
      TP->catch_msg("You approach " +QTNAME(TO)+ " threateningly. " +
          QCTNAME(TO)+ " notices, and calls a dozen sailors to " +
          "throw you overboard!\n");
      tell_room(environment(TP), QCTNAME(TP)+ " approaches " +
          QTNAME(TO)+ " threateningly. A dozen sailors jump upon " +
          QTNAME(TP)+ " and throws " +HIM(TP)+ " off the ship!\n", ({ TP }), TP);

      E(TO)->kick_out(TP);
      return "";
   }

   return 0;
}

void
create_krynn_monster()
{
    if (!IS_CLONE)
	return;

    add_prop(OBJ_M_NO_ATTACK, "@@no_attack");
    create_charter_captain();
}

void
sail_dir(string str, object vessel_loc)
{
    TO->remove_prop(CURRENTLY_SAILING);

    if(!vessel_loc->try_row(str))
    {
        TO->command("say Argh, I can't sail in that direction!");
        return;
    }


    return;
}

int
order(string str)
{
    float sail_time = 1.0;
    object vessel_loc = E(TO)->query_boat_loc();

    if(!str)
	return 0;

    if(TO->query_owner_name() != TP->query_real_name())
    {
      set_alarm(1.0, 0.0, "command","say I only take orders from the " +
         "person who chartered me!  Sorry, we ain't moving!");
      return 1;
    }

    if((str != "north") && (str != "south") && (str != "east") &&
       (str != "west") && (str != "northeast") && (str != "northwest") &&
       (str != "southwest") && (str != "southeast") && (str != "n") &&
       (str != "s") && (str != "e") && (str != "w") && (str != "ne") &&
       (str != "nw") && (str != "se") && (str != "sw"))
    {
	NF("Order the " +TO->short()+ " to sail in which direction?\n");
	return 0;
    }

    if(str == "n")
     str = "north";
    if(str == "e")
     str = "east";
    if(str == "s")
     str = "south";
    if(str == "w")
     str = "west";
    if(str == "ne")
     str = "northeast";
    if(str == "nw")
     str = "northwest";
    if(str == "se")
     str = "southeast";
    if(str == "sw")
     str = "southwest";

    if(TO->query_prop(CURRENTLY_SAILING))
    {
	NF("The " +TO->short()+ " is currently acting on your previous " +
            "sailing command. Be patient!\n");
	return 0;
    }

    if(query_captain_lvl() == 1)
        sail_time = 0.7;
    else if(query_captain_lvl() == 2)
        sail_time = 0.4;
    else
        sail_time = 1.0;

    TO->add_prop(CURRENTLY_SAILING, 1);
    write("You order " +TO->short()+ " to sail " +str+ ".\n");
    say(QCTNAME(TP)+ " orders " +TO->short()+ " to set sail.\n");

    set_alarm(sail_time, 0.0, &sail_dir(str, vessel_loc));

    return 1;
}

void
init_living()
{
    ::init_living();
    ADA("order");
}

void
arm_me()
{
    seteuid(getuid(TO));

    clone_object(WEP1)->move(TO,1);
    command("wield all");
    clone_object(FARM + "shirt")->move(TO,1);
    clone_object(FARM + "bandana3")->move(TO,1);
    clone_object(NET)->move(TO,1);
    command("wear all");
    if(random(8) == 1)
	clone_object(PEARL)->move(this_object(), 1);
}
