/* This is the basefile for the barbarians of Que Kiri
 * Aridor 07/97
 */

#include "../local.h"
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <const.h>
#include "/d/Krynn/common/defs.h"

#define ADJ1 ({"determined","weathered","worn","noble","alert"})
#define ADJ2 ({"brown-haired", "brown-eyed", "dark-haired", \
               "green-eyed", "blue-eyed", "grey-eyed", \
               "light-haired", "dark-eyed", "long-haired"})
#define MSACK     ("/d/Krynn/que/shu/obj/sack")
#define CLOAK     ("/d/Krynn/que/shu/obj/cloak")
#define ARM       ("/d/Krynn/que/shu/obj/larmour")
#define KNIFE       ("/d/Krynn/que/shu/obj/knife")

inherit M_FILE

string village = ONE_OF(({"Que Shu","Que Kiri","Que Teh"}));
int give_quest = 1;

void arm_me();

void
create_barbarian()
{

}

nomask void
create_krynn_monster()
{
    add_name("plainsman");
    add_name("plainsfolk");
    set_race_name("human");

    add_pname(({"plainsmen","humans"}));
    set_long("This is a @@short@@ of the @@query_village@@ tribe who had " +
         "been captured by the Dragonarmies and put to work in the " +
         "mines of Pax Tharkas, but managed to escape into the Tharkadan " +
         "mountain range and is now a refugee - far from home on the " +
         "plains of Abanasinia.\n");
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
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(CONT_I_HEIGHT,176+random(19));
    set_alignment(1 + random(200));
    set_knight_prestige(-1);

    set_appearance(random(100));
    set_appearance_offset(random(5));

    set_default_answer("@@def_answer");

    create_barbarian();

    add_adj("barbarian");
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
    if(TO->query_gender() == G_MALE) 
      return ::query_nonmet_name() + " plainsman";
    else
      return ::query_nonmet_name() + " plainsfolk";
}

string
query_village()
{
    return village;
}

public void
set_village(string str)
{
    village = str;
}

