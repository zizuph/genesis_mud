#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/intro";

#include "herb_witch.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

public void
create_earthsea_monster()
{
    set_name("aunty");
    add_name("witch");
    set_living_name("_herb_witch_");
    set_adj(({"motherly", "middle-aged"}));
    add_adj("herb");
    add_name("woman");
    set_race_name("human");
    set_gender(G_FEMALE);
    set_long("A motherly middle-aged woman. Her "+
        "long black hair, touched with a bit of grey, is tangled and "+
        "tied with loveknots and charms. She seems to have an interesting "+
        "smell about her, which reminds you of herbs and good cooking. "+
        "Her appearance is friendly enough, however, there is "+
        "something about her, which strikes you as unusual ... Hmmm... "+
        "you can't quite put your finger on it.\n");
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_ask(SKILLS_ASK, VBFC_ME("skills_response"));
    add_ask(TASK_ASK, VBFC_ME("return_task_ask"));
    add_ask(LUCKY_ITEMS, VBFC_ME("return_lucky_items"));
    add_ask(GOAT_ASK, VBFC_ME("goat_respond"));
    add_ask(KITTY_ASK, VBFC_ME("kitty_response"));
    add_ask(PUPIL_ASK, VBFC_ME("pupil_response"));
    add_ask(PARCHMENT_ASK, VBFC_ME("parchment_response"));
    add_ask(SHELL_ASK, VBFC_ME("respond_shell_ask"));
    set_default_answer("Aunty says: I don't "+
        "understand your question. I am just a humble herb woman, "+
        "you know.\n");
    set_act_time(40);
    set_chat_time(80);
    set_stats(({90, 90, 90, 20, 50, 75}));
    add_equipment(({ "/d/Earthsea/gont/tenalders/arm/dress" }));
    set_all_hitloc_unarmed(50);
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_WEP_AXE,90);
    set_skill(SS_WEP_POLEARM, 90);
    set_skill(SS_PARRY, 80);
    add_prop(OBJ_M_NO_MAGIC_ATTACK, (QCTNAME(this_object()) + " raises "+
        "her hand, palm outward, and shouts: Avert!\n"));
    add_prop(OBJ_M_NO_ATTACK, "The witch is protected "+
        "by unseen powers.\n");
    add_act("emote tosses a small handful of herbs into the kettle.");
    add_act("emote mutters a charm under her breath.");
    add_act("emote stirs the kettle, which bubbles vigorously.");
    add_chat("You know...wizards don't know everything!");
    add_chat("I can teach you some skills here.");
    add_act("smile wisely");
}
