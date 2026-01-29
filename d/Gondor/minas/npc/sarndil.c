/*
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */
inherit "/std/monster";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/logkill.c"

void
create_monster() 
{
    int      r = random(21);

    set_name("sarndil");
    add_name(({"shopkeeper", "jeweller", "goldsmith"}));
    set_race_name("human");
    set_adj(({"dexterous","noble"}));

    set_long("This is Sarndil, Jeweller and Goldsmith. He trades in jewels of "
      + "many kinds.\n");
    set_title("of Minas Tirith, Jeweller and Goldsmith");
    default_config_npc(65);
    set_base_stat(SS_DEX,80 + r);
    set_base_stat(SS_CON,75 + r);
    set_base_stat(SS_INT,80 + r/2);

    set_skill(SS_WEP_SWORD, 50 + r);
    set_skill(SS_WEP_KNIFE, 50 + r);
    set_skill(SS_DEFENCE,   60 + r);
    set_skill(SS_PARRY,     50 + r);
    set_skill(SS_AWARENESS, 90 + r/2);

    set_alignment(100 + 5*r);

    set_chat_time(12);
    add_chat("Can I help you?");
    add_chat("Welcome to my shop!");
    add_chat("My name is Sarndil.");
    add_chat("Have you got any nice gems to sell?");
    add_chat("Perhaps you want to buy some valuable jewels?");

    add_cchat("Get out of here, you thieving scoundrel!");
    add_cchat("You won't get away with this, you know!");
    add_cchat("Guards! Help!");

    add_ask(({"silver", "dust", "silver dust"}), "say I'm sorry, I " +
        "don't have any. Perhaps my cousin in Pelargir has some.", 1);
    add_ask(({"pelargir", "Pelargir", "cousin"}), "say My cousin " +
        "lives in Pelargir. We were apprentices together! He owns a " +
        "gem store too you know.", 1);
    trig_new("%s 'introduces' %s","react_introduce");
    trig_new("%s 'bows' %s","react_bow");
    seq_new("do_things");
    seq_addfirst("do_things",({"@@get_armed","say Well, I'm back in business."}));  
}

void
get_armed()
{
    object  arm;

    FIX_EUID

    clone_object(WEP_DIR + "dlsword")->move(TO);
    command("wield sword");
    arm = clone_object(MINAS_DIR +"obj/mtarmour");
    arm->set_armtype(0);
    arm->set_metal(random(4)+4);
    arm->set_const(random(3)+2);
    arm->move(TO);
    arm = clone_object(MINAS_DIR +"obj/ltunic");
    arm->move(TO);
    command("wear all");
}

void
intro_me()
{
    command("present me");
    command("I run the most exclusive business in Minas Tirith! ");
}

void
react_introduce()
{
    if (interactive(TP))
        set_alarm(2.0, 0.0, "intro_me");
}

void
do_bow()
{
    if(TP)
      command("bow " + TP->query_real_name());
    else
      command("bow");
    command("say What can I do for you?");
    command("say Perhaps you want to buy some valuable jewels?");
}

void
react_bow()
{
    if(interactive(TP))
        set_alarm(2.0, 0.0, "do_bow");
}

query_knight_prestige() { return -5; }
