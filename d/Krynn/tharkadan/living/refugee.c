/* This is the basefile for the barbarians of Que Kiri
 * Aridor 07/97
 */

#include "../local.h"
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

#define ADJ1 ({"determined","weathered","worn","noble","alert"})
#define ADJ2 ({"brown-haired","brown-eyed","dark-haired","green-eyed", \
               "blue-eyed","grey-eyed","light-haired","dark-eyed", \
               "long-haired"})
#define MSACK     ("/d/Krynn/que/shu/obj/sack")
#define CLOAK     ("/d/Krynn/que/shu/obj/cloak")
#define ARM       ("/d/Krynn/que/shu/obj/larmour")
#define KNIFE       ("/d/Krynn/que/shu/obj/knife")

inherit M_FILE

string faction = "Free Folk";
string village = ONE_OF(({"Haven","New Ports","Solace","Solace",
                          "Gateway"}));

void arm_me();

void
create_refugee()
{

}

nomask void
create_krynn_monster()
{
    add_name("refugee");
    set_race_name("human");

    add_pname(({"refugee","humans"}));
    set_long("This is a @@short@@ from @@query_village@@ who had been " +
         "captured by the Dragonarmies and put to work in the mines of " +
         "Pax Tharkas, but managed to escape with a group of other " +
         "prisoners into the Tharkadan mountain range, finding refuge " +
         "in this valley. While the prisoners were unified in their " +
         "escape, they are far from united as a people " +
         "now. @@query_faction_long@@ \n");
    set_gender(random(2));

    if (random(20))
    {
	set_adj(ONE_OF(ADJ1));
	if (random(20))
	  add_adj(ONE_OF(ADJ2));
    }
    else
      add_adj(ONE_OF(ADJ2));
    add_adj(0);

    default_config_npc(30);
    set_skill(SS_AWARENESS, 20);
    set_skill(SS_DEFENSE, 21);
    set_skill(SS_UNARM_COMBAT, 30);

    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(CONT_I_HEIGHT,176+random(19));
    set_alignment(1 + random(200));
    set_knight_prestige(-1);

    set_appearance(random(100));
    set_appearance_offset(random(5));

    set_default_answer("@@def_answer");

    create_refugee();

    add_adj("refugee");
    set_alarm(1.0,0.0,arm_me);
}

string
def_answer()
{
    command("emote looks blankly back at you.");
    return "";
}


void
arm_me()
{
    object b;

    if (!random(4))
    {
	b = clone_object(MSACK);
	b->move(TO,1);
    }
    else
      b = TO;

    MONEY_MAKE_CC(random(20))->move(b,1);
    MONEY_MAKE_SC(random( 5))->move(b,1);

    clone_object(CLOAK)->move(TO,1);
    clone_object(ARM)->move(TO,1);
    clone_object(KNIFE)->move(TO,1);
    
    set_alarm(1.0,0.0,&command("wear all"));
    set_alarm(1.0,0.0,&command("wield all"));
}

string
query_nonmet_name()
{
    return ::query_nonmet_name() + " refugee";
}

// The factions are Seekers, Believers, Free Folk

public string
set_faction(string str)
{
    faction = str;
}

string
query_faction()
{
   return faction;
}

string
query_faction_long()
{
    string fl = query_faction();

    switch(fl)
    {
       case "Seekers":
         return "This refugee is a Seeker from the Lordcity of Haven. " +
            "Widely detested by the other Townsfolk refugees for their " +
            "earlier involvement with the Dragonarmies, the Seekers " +
            "make no friends by being openly hostile towards the " +
            "'pagan' plainsmen and the 'usurping' Believers faction.";
         break;
       case "Believers":
         return "This refugee is a recent convert to the " +
            "Old Gods, and is part of a small fledgingly group amongst " +
            "the people of the Vale calling themselves the Believers. " +
            "While trying to stay above the petty politics forming " +
            "within the refugee factions, they are viewed with " +
            "suspicion by the plainsmen and with hostility by the " +
            "Seekers.";
         break;
       default:
         return "This refugee was a town dweller of the north, with a " +
            "historic distrust of the Plainsfolk. The recent meddling " +
            "of the Seekers from Haven that resulted in their " +
            "imprisonment by the Dragonarmies has also led to a level " +
            "of resentment with that faction.";
         break;
    }
}

string
query_village()
{
    if(faction == "Seekers")
      return "Haven";
    else
      return village;
}

public void
set_village(string str)
{
    village = str;
}

