/*
 * Soul Merchant
 * Abaddon, June, 2020
 * 
 * Created from corpse ritual 
 * In the day, soul merchants go to humanoid settlements and sell things,
 * for considerably less than they're worth. They do not care for profit,
 *
 * Solo Merchants are feral
 * Every merchant only wants gold for souls, will take any price for wares
 *
 * They may commit ritual suicide after quest completed.
 *
 * They use souls as consumable familiars. Complete the task --> afterlife
 * See "nakedmerchant.c"
 */
 
inherit "/std/monster";
#include <macros.h>
create_monster()
{
    set_name("axiom");
    add_name("soul merchant");
    set_race_name("soul merchant");
    set_adj( ({"short", "cloaked"}) );
    set_stats( ({30, 60, 50, 45, 45, 30}) );
    set_alignment(0);
    set_gender(G_MALE);
    set_chat_time(180);

    add_prop(NPC_I_NO_FEAR, 1);     /* all soul merchants defend each other */
    add_prop(CONT_I_WEIGHT,7782);  /* 35 Kg */
    add_prop(CONT_I_HEIGHT,79);     /* 79 cm */
    add_prop(LIVE_I_SEE_DARK,10);

    add_ask( ({"wares", "soul", "souls", "special wares", "special"}), VBFC_ME("ask_soul"));
    set_default_answer(VBFC_ME("default_answer"));
    set_act_time(25);
    add_act("emote nods approvingly at a customer's offer.");
    add_act("emote grunts and points at the wares, beckoning those nearby.");

    set_long("This creature is small in stature and is dressed in thick robes"+
        " that cover its whole body, shrouding themselves from the view of pr"+
        "ying eyes. Over its face rests a mask, devoid of emotion, carved out"+
        "of ivory. This merchants tends to carry all of its wares strung abou"+
        "t its body, on display for the potential buyer.\n");
}
public string
ask_soul()
{
    command("emote stops everything and immediately rifles through his bag.);
    command("emote leans closer to show you what appears to be a vial of light.");
    return "";
}
public string
default_answer()
{
    command("emote grunts indifferently.");
    return "";
}