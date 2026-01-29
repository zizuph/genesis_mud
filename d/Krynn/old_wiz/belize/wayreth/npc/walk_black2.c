


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
    set_long("This dark-robed human is young, but his face is hidden in the dephts " +
             "of the silk hood. His moves are gentle, almost sneaky. " +
             "The young mage is slim - he probably spent all his life reading " +
             "books and improving magic skills. That's why his skin is almost " +
             "yellow and thick. He is carrying his spellbook, and with this " +
             "item he seems more powerful and sure of his knowledge. \n");
    set_adj(({"dark-robed","hooded"}));
    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop("_npc_may_pass", 1);
    set_introduce(1);


    set_stats(({120,108,160,90,90,80}));
    set_skill(SS_DEFENCE,        90);
    set_skill(SS_PARRY,          75);
    set_skill(SS_WEP_POLEARM,    60);
    set_skill(SS_BLIND_COMBAT,   50);
    set_skill(SS_AWARENESS,      50);

    set_alignment(-500);
   
    set_default_answer("Moroth whispers: I am sorry, but I don't know what you are talking about. \n");
    add_ask("test","emote whispers: Yes... Every apprentice of magic has to pass this Test. " +
            "It is very dangerous, you can pay with your life. \n");
    set_act_time(4);
    add_act("emote silently turns one page from his spellbook. ");
    add_act("emote slowly repeats some strange words. ");
    add_act("emote absentmindedly smiles at you. ");
    add_act("emote whispers: One day I will leave this place as a full mage! ");
    add_act("emote whispers silently: I see only one way in my life! It is the dark side of magic! ");
    add_act("emote whispers: Well... I know, that we should keep the balance between the forces of good and evil, but " +
             "dark side of magic is the most powerful kind of magical art... ");
    set_patrol_time(30);

    set_patrol_path(({"e","d","d","d","w","exa board","say Well... Interesting notes...","e","d","w","w","say Read books! You can " +
                    "find a lot of wizdom there... ","e","e","d","w","e","d","u","u","u","u","u","u","w" }));
 
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
