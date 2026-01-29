


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
inherit "/d/Krynn/std/equip";


inherit "/std/act/domove";   /* Allows Dranin to move */
inherit "/std/act/action";   /* Allows Dranin to act */
inherit "/d/Krynn/std/patrol";



void
create_krynn_monster()
{
    string str;

    set_name("dranin");
    set_living_name("dranin");
    set_race_name("human");
    set_title("of Northern Ergoth, Initiate of Sorcery");
    set_long("This is a handsome young human man with perfectly chiseled features. " +
        "He is studying his spellbook and silently repeating some harder " +
        "spells. His robe is red - it is the sign of the followers of the " +
        "neutral path of magic. He is hooded and that is why you can't " +
        "see his face in full light. You feel his deep gaze for a short " +
        "moment. \n");
    set_adj(({"crimson-robed","hooded"}));
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

    set_alignment(0);
   
    set_default_answer("Dranin whispers: I am sorry, but I don't know " + 
        "what you are talkin about. \n");
    add_ask("test","emote whispers: Yes... Every apprentice of magic has " + 
        "to pass this Test. It is very dangerous, you can pay with your " + 
        "life. \n");
    
    set_act_time(4);
    add_act("emote silently turns one page from his spellbook. ");
    add_act("emote slowly repeats some strange words. ");
    add_act("emote absentmindedly smiles at you. ");
    add_act("emote whispers: One day I will leave this place as a full mage! ");
    set_patrol_time(30);

    set_patrol_path(({"d","d","d","w","examine board","e","d","w",
                          "examine board","w",
                          "say Our library contains a lot of books with " +
                          "useful informations!","e","e","d","w","w","e","e",
                          "u","u","u","u","u"}));
    
    equip(({ "/d/Krynn/wayreth/guild/red/robe" }));
}


string
query_guild_name_occ()
{
    return "Wizards of High Sorcery";
}
