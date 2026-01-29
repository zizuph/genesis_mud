/*
 *  /d/Gondor/guilds/rangers/npc/halbarad.c
 *
 *    Created by Elessar.
 *
 *    Modified to use the new master ranger file
 *    - Olorin, 20-Jan-1995
 *    - Alto, 15-Mar-2002, moved to new ranger code structure
 *                         alternate to Aragorn npc
 *
 */
#include "/d/Gondor/defs.h"
#include "../rangers.h"

inherit RANGERS_NPC + "master_ranger.c";

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define MASTER_RANGER_FILE RANGERS_NPC + "halbarad_save"
#define CO_NO              2

public void introduce(object who);

void
create_master_ranger()
{
    set_living_name("halbarad");
    set_name("halbarad");
    set_adj("tall");

    set_company_no(CO_NO);
    set_master_ranger_file(MASTER_RANGER_FILE);

    set_title("the Master Ranger of the Rangers of the North");

    set_long("He is a fair-skinned man, dark of hair, with dark eyes, and "
      + "a proud face. You realize that he must be one of the Dunedain "
      + "of the North, a man of the line of the Lords of Westernesse.\n");

    set_stats(({ 85, 85, 90, 73, 83, 90 }));
 
    add_prop(CONT_I_HEIGHT, 216);
    add_prop(CONT_I_WEIGHT, 99000);

    set_skill(SS_WEP_SWORD, 87);
    set_skill(SS_PARRY,     80);
    set_skill(SS_DEFENCE,   65);
    set_skill(SS_BRAWLING,  100);
    set_skill(SS_HEARING,   100);
    set_skill(SS_AWARENESS, 77);
    set_skill(SS_TRACKING,  85);
    set_skill(SS_LOC_SENSE, 75);
    set_skill(SS_LANGUAGE,  51);
    set_skill(SS_HUNTING,   65);
    set_skill(SS_ANI_HANDL, 34);
    set_skill(SS_SWIM,      78);
    set_skill(SS_CLIMB,     48);

    set_alignment(1000);

    set_chat_time(12);
    add_chat("Beware the Wights at the Barrow-downs!");
    add_chat("Strange men from the South are watching Bree.");
    add_chat("My people are the last Dunedain of Arnor, the wardens of the "
      + "lost kingdom.");
    add_chat("Our organization depends on secrecy.");

    add_ask(({"about rangers","rangers"}),"say We, the Rangers of the "
      + "North have one main duty: To protect the lost kingdom until the "
      + "return of the King!", 1);
    add_ask(({"about duty","duty"}), "say Our Duty is to protect the Free "
      + "Peoples, especially the hobbits in the Shire, from the Enemy!", 1);

    add_cchat("So, you think you can best me? Run while you can!");
    add_cchat("Scoundrel! How did you get in here?");
    add_cchat("Guards! Foe in the hideout!");
}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(WEP_DIR + "dlsword")->move(TO);
    clone_object(RANGERS_OBJ + "travel_cloak")->move(TO);
    clone_object(RANGERS_OBJ + "travel_boots")->move(TO);

    command("wield longsword");
    command("wear all");
}

void
enchant_seed()
{
    command("say Amaron, the Master Ranger of the Ranger Headquarters " +
        "sent me a message that their main supplier of herbs " +
        "has asked him for help. Maybe you could go and " +
        "talk to Amaron for further information?");
}

public string
introduce(object who)
{
    command("hail " + OB_NAME(who));
    command("say My name is " + query_name() + " Dunadan. I am the " +
        "Master Ranger here.");
    command("introduce me to " + OB_NAME(who));
    return "";
}

string
inform_ithilien()
{
    command("say Ithilien is even fairer than Gondor, they say!");
    command("say I have never been there - yet. But I had a dream " +
        "not long ago, in which I was travelling through the " +
        "Ithilien, cleaning out the remains of Evil.");
    command("chuckle");
    command("say I have tasted rare wine from Ithilien. It was the best in " +
        "Middle-earth, only rivalled by wine from Dorwinion!");
    command("sigh");
    command("say There is a bastion of Rangers still protecting Ithilien.");
    command("say They are fighting an impossible war of harassing the " +
        "vast numbers of Evil minions there.");
    command("say May the Valar grant them success.");
}

string
inform_north()
{
    command("say The North was once known as the kingdom of Arnor, " +
        "sister-kingdom to Gondor, and ruled by the Line of " +
        "Isildur, son of Elendil. But the Dark One sent his " +
        "Captain, the Witch-king, who gathered his forces in " +
        "Angmar. About a thousand years ago now, the last parts " +
        "of Arnor fell for the Witch-kings feet, although at " +
        "the same time crushing his armies.");
    command("say From then on, the Line of Isildur, the Kings of Arnor, " +
        "have lived in hiding, as Chieftains of the Rangers of the North.");
    command("smile");
    command("say We are the remnants of the Dunedain settlements in " +
        "Arnor, and we protect our ancestrial lands until " +
        "the time comes for the King to return!");
    command("smile");
    return "";
}

