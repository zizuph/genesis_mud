/*
 *    The master ranger for the Northern company of the ranger guild
 *
 *    Created by Elessar.
 *
 *    Modified to use the new master ranger file
 *    - Olorin, 20-Jan-1995
 */
#pragma strict_types

inherit "/d/Gondor/common/guild/lib/master_ranger";

#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define LOST_RANGER_SEARCHER "_ranger_i_searching_for_lost_ranger"
#define MASTER_RANGER_FILE  RANGER_DIR+"lib/halbarad_save"
#define CO_NO   3

void
create_master_ranger()
{
    set_living_name("halbarad");
    set_name("halbarad");
    set_adj("tall");

    set_company_no(CO_NO);
    set_company("the North");
    set_master_ranger_file(MASTER_RANGER_FILE);

    set_long(BSN(
        "He is a fair-skinned man, dark of hair, with dark eyes, and "
      + "a proud face. You realize that he must be one of the Dunedain "
      + "of the North, a man of the line of the Lords of Westernesse."));

    set_stats(({ 85, 85, 90, 73, 83, 90 }));
 
    add_prop(CONT_I_HEIGHT,216);
    add_prop(CONT_I_WEIGHT,99000);

    set_skill(SS_WEP_SWORD,87);
    set_skill(SS_PARRY,80);
    set_skill(SS_DEFENCE,65);
    set_skill(SS_BRAWLING,100);
    set_skill(SS_HEARING,100);
    set_skill(SS_AWARENESS,77);
    set_skill(SS_TRACKING,85);
    set_skill(SS_LOC_SENSE,75);
    set_skill(SS_LANGUAGE,51);
    set_skill(SS_HUNTING,65);
    set_skill(SS_ANI_HANDL,34);
    set_skill(SS_SWIM,78);
    set_skill(SS_CLIMB,48);

    set_alignment(1000);

    add_chat("Beware the Wights at the Barrow-downs!");
    add_chat("Strange men from the South are watching Bree.");
    add_chat("We are the last Dunedain of Arnor; wardens of the lost kingdom.");
    add_chat("Our organization depends on secrecy.");

    add_ask(({"about rangers","rangers"}),"say We, the Rangers of the "
      + "North have one main duty: To protect the lost kingdom until the "
      + "return of the King!",1);
    add_ask(({"about duty","duty"}), "say Our Duty is to protect the Free "
      + "Peoples, especially the hobbits in the Shire, from the Enemy!", 1);
}
    

void
enchant_seed()
{
    command("say Amaron, the Master Ranger of the Gondor Company sent");
    command("say me a message that their main supplier of herbs");
    command("say has asked him for help. Maybe you could go and");
    command("say talk to Amaron for further information?");
}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(WEP_DIR + "dlsword")->move(TO);
    command("wield longsword");
    clone_object(RANGER_DIR + "north/obj/travel_cloak")->move(TO);
    command("wear cloak");
    clone_object(RANGER_DIR + "north/obj/travel_boots")->move(TO);
    command("wear boots");
}

varargs string
introduce(mixed who)
{
    object  player;

    if (objectp(who))
    {
        player = who;
        who = player->query_real_name();
    }
    else if (stringp(who))
    {
        who = LOW(who);
        player = find_living(who);
    }

    if (!objectp(player))
        player = TP;
    if (!interactive(player))
        return "";
 
    if (!present(player,ENV(TO)))
        return "";
 
    command("hail " + who);
    command("say My name is "+query_name()+" Dunadan. I am the Master Ranger here.");
    command("introduce me");
    return "";
}

string
missing_ranger()
{
    command("say The Ithilien Company reported the existence of a large");
    command("say army camped in Ithilien, and the Gondor Company quickly");
    command("say sent a ranger to scout the area more closely.");
    command("say In my opinion, they should have left that to the");
    command("say Rangers of Ithilien, who are more at home there.");
    command("say The ranger never returned. Amaron, master ranger in");
    command("say Gondor wants to know what happened to him: If he is");
    command("say alive, help him back home.");
    command("say If not - bring proof of his demise to Amaron or me.");
    TP->add_prop(LOST_RANGER_SEARCHER, 1);
}

string
inform_ithilien()
{
  command("say Ithilien is even fairer than Gondor, they say!");
  command("say I have never been there - yet. But I had a dream");
  command("say not long ago, in which I was travelling through the");
  command("say Ithilien, cleaning out the remains of Evil.");
  command("chuckle");
  command("say I have tasted rare wine from Ithilien. It was the best in");
  command("say Middle-earth, only rivalled by wine from Dorwinion!");
  command("sigh");
  command("say There is a bastion of Rangers still protecting Ithilien.");
  command("say They are fighting an impossible war of harassing the");
  command("say vast numbers of Evil minions there.");
  command("say May the Valar grant them success.");
}

string
inform_north()
{
  command("say The North was once known as the kingdom of Arnor,");
  command("say sister-kingdom to Gondor, and ruled by the Line of");
  command("say Isildur, son of Elendil. But the Dark One sent his");
  command("say Captain, the Witch-king, who gathered his forces in");
  command("say Angmar. About a thousand years ago now, the last parts");
  command("say of Arnor fell for the Witch-kings feet, although at");
  command("say the same time crushing his armies. From then on, the");
  command("say Line of Isildur, the Kings of Arnor, have lived in");
  command("say hiding, as Chieftains of the Rangers of the North.");
  command("smile");
  command("say We are the remnants of the Dunedain settlements in");
  command("say Arnor, and we protect our ancestrial lands until");
  command("say the time comes for the King to return!");
  command("smile");
  return "";
}

