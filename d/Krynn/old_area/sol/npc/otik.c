/*
 * Otik the Innkeeper of Solace
 * modified from Toede.
 * by Teth
 * Apr 29,'96 
*/

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h";
inherit M_FILE

inherit "/std/act/domove";     /* Allows Otik to move */
inherit "/std/act/action";     /* Allows Otik to act  */

public void
create_krynn_monster()
{
    string str;

    set_name("otik");
    set_living_name("otik");
    set_race_name("human");
    set_title("the Innkeeper of the Inn of the Last Home");
    set_long("This man is overweight, but since he appears to be the " +
             "owner of this establishment, it is probably the result of " +
             "eating the fine cooking here every day of the year. He is " +
             "balding, with a crescent of hair ringing his head. His hands " +
             "are toned with years of manual labour.\n");
    add_name("innkeeper");
    set_adj("pudgy");
    add_adj("balding"); 
    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS,1);
    set_introduce(1);

    set_stats(({33,28,54,45,64,33}));
    set_skill(SS_DEFENCE,        50);
    set_skill(SS_PARRY,          50);
    set_skill(SS_BLIND_COMBAT,   50);
    set_skill(SS_AWARENESS,      50);
    set_skill(SS_UNARM_COMBAT,   75);

    set_alignment(415);
    set_knight_prestige(-1);

    set_default_answer("Otik answers: I'm sorry, but I know little about " +
            "that.\n");
    add_ask(" [about] 'inn'","Otik says: The Inn of the Last Home was " + 
            "built by a man named Krale the Strong.\n");
    add_ask(" [about] 'krale'", "Otik says: It was rumoured he could " + 
            "tuck a barrel of ale under one arm, then climb up the tree " +
            "one-handed.\n");
    add_ask(" [about] 'ale'","Otik proudly declares: We serve the best " +
            "ale in Solace!\n");
    add_ask(" [about] 'potatoes' / 'potatos'","Otik exclaims: My spiced " +
            "potatoes are talked about far and wide!\n");
    add_ask(" [about] 'tika'","Otik says: Ever since Tika lost her " +
            "father, I've treated her as if she was my own daughter. " +
            "She's returned the love I have given her, and what more " +
            "could a substitute father ask for?\n");
    add_ask(" [about] 'solace'","Otik shares: Solace is a small peaceful " +
            "village, I hope you don't plan on making any trouble!\n");

    set_act_time(6);
    add_act("say An inn is blessed or cursed by its ale!");
    add_act(({"emote pats his belly.","say It's a labour of love, and " +
            "the Inn has loved me back."}));
    add_act(({"emote smiles broadly.","say Welcome to the Inn of the " +
            "Last Home!"}));
    add_act("emote chuckles: It must be thirsty work, haranguing people " +
            "about the New Gods day in and day out - that's why Hederick " +
            "is good for business!");
    add_act("emote gives a sly wink.");
    add_act("say I hope this year's ale batch is as good as the last " +
            "one!");    

    set_cact_time(4);
    add_cact("shout Help me! I'm being attacked!");
    add_cact("say Have pity on a poor old man, please!");
    add_cact("emote tries to escape, but fails."); 
    add_cact("say Where's a strong swordarm when you need one?!?!");
}

/*
public void
arm_me()
{
    clone_object(OBJ + "tsword")->move(TO);
    clone_object(OBJ + "tarmour")->move(TO);
    clone_object(OBJ + "tshinguard")->move(TO);
    clone_object(OBJ + "tboots")->move(TO);
    clone_object(OBJ + "tgauntlets")->move(TO);
    clone_object(OBJ + "thelmet")->move(TO);
    command("wear all");
    command("wield all");
}
*/

public int
second_life(object killer)
{
    K_KILL_LOG("kills", "Otik", killer);
    return 0;
}
