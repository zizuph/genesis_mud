/*
 *    The master ranger for the Ithilien company of the ranger guild
 *
 *    Created by Elessar.
 *
 *    Modification Log:
 *      Modified to use the new master ranger file
 *      - Olorin, 20-Jan-1995
 *      Moved and modified to fit new rangers code
 *      - Alto, 24-Feb-2002
 *
 */
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

inherit RANGERS_NPC + "master_ranger.c";

#define TRAINING_HALL        (RANGERS_ITH_DIR + "ithilien_train")
#define LOST_RANGER_SEARCHER "_ranger_i_searching_for_lost_ranger"
#define MASTER_RANGER_FILE   RANGERS_NPC + "mablung_save"
#define CO_NO                1

public string   ask_train();
public string   ask_curtain();

void
create_master_ranger()
{
    set_living_name("mablung");
    set_name("mablung");
    set_adj("serious");

    set_company_no(CO_NO);
    set_master_ranger_file(MASTER_RANGER_FILE);

    set_title("the Master Ranger of Ithilien");

    set_long("He is a fair-skinned man, dark of hair, with dark eyes, and "
      + "a proud face. You realize that he must be one of the Dunedain "
      + "of the South, a man of the line of the Lords of Westernesse.\n");

    set_stats(({ 85, 85, 90, 73, 83, 90 }));

    add_prop(CONT_I_HEIGHT, 201);
    add_prop(CONT_I_WEIGHT, 95000);

    set_skill(SS_WEP_SWORD, 97);
    set_skill(SS_PARRY,     80);
    set_skill(SS_DEFENCE,   75);
    set_skill(SS_BRAWLING,  100);
    set_skill(SS_HEARING,   89);
    set_skill(SS_AWARENESS, 58);
    set_skill(SS_TRACKING,  85);
    set_skill(SS_LOC_SENSE, 75);
    set_skill(SS_LANGUAGE,  51);
    set_skill(SS_HUNTING,   65);
    set_skill(SS_ANI_HANDL, 34);
    set_skill(SS_SWIM,      78);
    set_skill(SS_CLIMB,     48);

    set_alignment(1000);

    add_chat("Armies are moving up from Harad to the Morannon.");
    add_chat("Fierce Southrons are bringing huge Mumakil to fight for them.");
    add_chat("Stay away from Minas Morgul; unnamable foes reside there!");
    add_chat("As long as we can get supplies we can stay here.");

    add_ask(({"about rangers","rangers"}), "say We Rangers of Ithilien "
      + "have one main duty: To harass the minions of the Evil One!",1);
    add_ask(({"about duty","duty"}), "say Our Duty is to protect the Free "
      + "Peoples from the Enemy in Mordor!", 1);
    add_ask(({"train", "training", "learn", "improve", "skills", "teach me", }),
        ask_train);
    add_ask(({"curtain", "untie curtain", "open curtain", }),
        ask_curtain);
}
    
string
enchant_seed()
{
    command("say Amaron, master ranger of the Ranger Headquarters sent " +
        "me a message that their main supplier of herbs " +
        "has asked him for help. Maybe you could go and " +
        "talk to Amaron for further information?");
}

string
inform_gondor()
{
    command("say Gondor is a beautiful land.");
    command("say The main problem is the Enemy in the East.");
    command("say How can we live peacefully when large armies are "
      + "mustering to attack them?");
    command("sigh");
    return "";
}

string
missing_ranger()
{
    command("say As soon as we heard of the large army camped in Ithilien, " +
        "we sent a ranger to scout the area further.");
    command("say He hasn't returned. I want you to find out what has " +
        "happened to him. If he is alive - bring him back " +
        "to me. If not - bring proof of his demise.");
    TP->add_prop(LOST_RANGER_SEARCHER, 1);
}

string
inform_ithilien()
{
    command("say Ithilien is even fairer than Gondor! Green forests " +
        "abundant with flora and fauna, rich with the smells " +
        "of flowers in bloom, herbs for any use and food enough " +
        "for any traveller. Once the finest wine district of " +
        "Middle-earth, only rivalled by Dorwinion in the north.");
    command("sigh");
    command("say But now we are the last bastion, the last remnants of " +
        "the Ithilien populace, the rest fled a hundred years " +
        "ago, when Orcs started pouring out of the east.");
    command("spit");
    return "";
}

/*
 * Function name: ask_train
 * Description  : respond to questions re training
 * Returns      : "" -- answer is written here
 */
public string
ask_train()
{
    string name;
    if (file_name(ENV()) == TRAINING_HALL)
    {
        command("say Please read the plaque and the poster.");
        command("smile");
    }
    else if (present("ith_curtain", ENV())->query_locked())
    {
        name = TRAINING_HALL->query_tied_by();
        command("say I am afraid I cannot help you with that " +
            "while the recess is closed.");
        ask_curtain();
    }
    else
    {
        command("say Ahhh, the recess seems to be open again.");
        command("smile " + OB_NAME(TP));
        command("say Please follow me.");
        command("east");
    }
    return "";
}

/*
 * Function name: ask_curtain
 * Description  : respond to questions re curtain
 * Returns      : "" -- answer is written here
 */
public string
ask_curtain()
{
    string name;

    if (file_name(ENV()) == TRAINING_HALL ||
      !present("ith_curtain", ENV())->query_locked())
    {
        command("peer " + OB_NAME(TP));
        command("say It's very attractive curtain, I think.");
        command("say Good heavy cloth, and a nice shade of grey.");
    }
    else
    {
        command("smile seriously " + OB_NAME(TP));
        command("say An officer of the Rangers is using the recess " +
            "for a private meeting just now.");
        command("ponder");
        command("say If you urgently need access to the recess, " +
            "you could ring the bell.");
        command("say If it's not urgent, however, it would be " +
            "better to wait until they're finished.");
    }
    return "";
}
