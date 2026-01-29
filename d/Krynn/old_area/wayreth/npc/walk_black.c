


    /*    Written and coded by Belize    */
    /*    With a great help of Teth    */
    /*    17.01.1997    */




#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h";
inherit M_FILE
inherit AUTO_TEAM

inherit "/std/act/domove";    /* Allows Moroth to move */
inherit "/std/act/action";    /* Allows Moroth to act */
inherit "/d/Krynn/std/patrol";



void
create_krynn_monster()
{
    string str;

    set_name("moroth");
    set_living_name("moroth");
    set_race_name("human");
    set_title("of Haven, the Lesser Novice of Sorcery");
    set_long("This dark-robed human seems to be young and very slim - " +
        "he must have spent all his short life reading books, and mastering "+
        "his magic skills. That's also why his skin is yellow and thick. " +
        "He is all worn in a dark robe, and his face is deeply hidden in " +  
        "depths of his silk hood. His moves seem to be gentle, almost " +
        "sneaky. A spellbook he holds makes him look much more powerful " +
        "and sure of his knowledge.\n");
    set_adj(({"dark-robed","hooded"}));
    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop("_npc_may_pass", 1);
    set_introduce(1);

    set_alarm(3.0, 0.0, "add_cmdsoul", "/d/Krynn/wayreth/guild/black/mage_soul");
    set_alarm(4.0, 0.0, "update_hooks");

    set_stats(({120,108,160,90,90,80}));
    set_skill(SS_HERBALISM, 70);
    set_skill(SS_SPELLCRAFT, 60);
    set_skill(SS_ALCHEMY, 30);
    set_skill(SS_FORM_ENCHANTMENT, 30);
    set_skill(SS_FORM_ABJURATION, 30);
    set_skill(SS_FORM_ILLUSION, 30);
    set_skill(SS_FORM_CONJURATION, 30);
    set_skill(SS_FORM_DIVINATION, 30);
    set_skill(SS_ELEMENT_FIRE, 30);
    set_skill(SS_ELEMENT_WATER, 30);
    set_skill(SS_ELEMENT_AIR, 30);
    set_skill(SS_ELEMENT_DEATH, 35);
    set_skill(SS_LANGUAGE, 50);
    set_skill(SS_DEFENCE, 20);
    set_skill(SS_AWARENESS, 35);

    set_alignment(-500);
   
    set_default_answer("Moroth whispers: Alas, I fail to understand what " +
        "you speak about.\n");
    add_ask("test","Moroth whispers: Indeed... Each apprentice of magic has " +
        "to pass it. It is told to be very dangerous. Many have already " +
        "paid with their lives, attempting to get through it. " +
        "Yet, you need to pass it, in order to become a True Mage.\n");
    add_ask("magic","Moroth whispers: Magic... magic... Balance of the world depends on the " +
        "magic. We should keep it secret, for I fear to think what would " +
        "happen, if unauthorized hands mastered it. To control the True "+
        "Magic, one has to pass the test. \n");
    set_act_time(4);
    add_act("emote turns page in his spellbook silently.");
    add_act("emote slowly repeats some strange words. ");
        add_act("smile absent");
    add_act("emote whispers: One day I will leave this place as a full mage! ");
    add_act("emote whispers silently: I see only one way in my life! It is the dark side of magic! ");
    add_act("emote whispers: Well... I know, that we should keep the balance between the forces of good and evil, but " +
             "dark side of magic is the most powerful kind of magical art... ");
    add_act("emote focuses his attention on something.");
    add_act("wsmile");
    add_act("wpace");
    add_act("wsilent");
    set_patrol_time(30);

    set_patrol_path( ({ "e", "d", "d", "d", "w", "exa board",
        "say Intresting notes..", "e", "d", "w", "w", "say You should read "+
        "books! A lot of wisdom can be found there..",
        "e", "e", "d", "w", "e", "d",
        "u", "u", "u", "u", "u", "u", "w" }) );
 
}


public void
arm_me()
{
    clone_object("/d/Krynn/wayreth/guild/black/robe")->move(TO);
    command("wear all");
}

string
query_guild_name_occ()
{
    return "Wizards of High Sorcery";
}
