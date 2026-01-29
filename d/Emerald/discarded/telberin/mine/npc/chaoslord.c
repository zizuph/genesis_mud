

/* mine/npc/chaoslord.c is cloned by mine/maze31.c */
 
inherit "/std/monster";

#pragma save_binary
#include <stdproperties.h>
#include <ss_types.h>
#include "../defs.h"
#include <const.h>
#include <language.h>
#include "/d/Emerald/lib/prestige.h"
#include "/d/Emerald/lib/make_money.h"

/* Prototypes */
void arm_me();
void react_smile(object actor);
void react_shake(object actor);
void react_bow(object actor);

void
create_monster()
{
    set_name("chaoslord");
    set_adj("dewar");
    set_race_name("dwarf");
    set_short("dewar chaoslord");
    set_long( "This insane dewar has no feeling and this "+
              "is clearly visible in his dark beady eyes.\n");
 
    set_base_stat(SS_STR, 180);         /* Mortals were complaining that */
    set_base_stat(SS_DEX, 170);         /* he was too easy to kill for them */
    set_base_stat(SS_CON, 160);         /* so i've updated it slightly. */
    set_base_stat(SS_INT, 100);
    set_base_stat(SS_WIS, 100);
    set_base_stat(SS_DIS, 100);
 
    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_BLIND_COMBAT,80);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_2H_COMBAT, 95);
    set_skill(SS_DEFENCE, 85);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 45);
 
    set_alignment(-250-random(51));
 
    add_prop(OBJ_I_WEIGHT, 19000);
    add_prop(LIVE_I_SEE_DARK,3);
 
    add_prop(CONT_I_MAX_WEIGHT, 180000);
    add_prop(OBJ_I_VOLUME, 89000);
    add_prop(LIVE_O_ENEMY_CLING, 1);
    add_prop(CONT_I_MAX_VOLUME, 100000);
 
    set_chat_time(10);                     /* Set speaking interval */
    add_chat("Do you think that you are invincible?");
    add_chat("Do not mess with me mortal!");
 
    set_cchat_time(4);              /* Set combat speaking interval */
    add_cchat("I am invincible, mortal!");
    add_cchat("This is not a game now, you have pushed me too far.");
 
    set_act_time(10);            /* Set action interval           */
    add_act("grin");
    add_act("growl");
 
    set_cact_time(3);
    add_cact("grip hilt tightly");
    add_cact("cackle madl");
    add_cact("grip hilt tightly");
    add_cact("emote growls: You'll never take me alive.");
    add_cact("grip hilt tightly");
 
    setuid();
    seteuid(getuid());
}

void
emote_hook(string emote, object actor, string adverb)
{
    switch(emote)
    {
    case "smile":
        react_smile(actor);
        break;
    case "shake":
        react_shake(actor);
        break;
    case "bow":
        react_bow(actor);
        break;
    default:
        break;
    }
}

 
void
react_bow(object actor)
{
    string who = actor->query_real_name();

    switch (random(3))
    {
    case 0:
        command("say Who the hell do you think you are?");
        break;
    case 1:
        command("snarl at " + who);
        break;
    default:
        command("say to " + who +
                " Bow down again and I'll chop your head off.");
        command("grin nastily");
        break;
    }
}
 
void
react_smile(object actor)
{
    string who = actor->query_real_name();
    
    switch(random(3))
    {
    case 0:
        command("say Who are you smiling at, " + actor->query_race() +
                "?\n");
        break;
    case 1:
        command("growl at " + who);
        break;
    default:
        command("say I'll wipe that smile off your face soon, " +
                actor->query_race() + "!\n");
        break;
    }
}

void
add_introduced(string who)
{
    int ran = random(3);
    if (who)
    {
        if (ran == 0)
        {
            command("say Nice to meet you, " +
                    present(lower_case(who),
                            environment(this_player()))->query_name() + ".");
            command("bow to " + who);
        }
        else if (ran == 1)
        {
            command("bow to " + who);
        }
        else if (ran == 2)
        {
            command("say I'll kill you, " +
                    present(lower_case(who),
                            environment(this_object()))->query_race() + "!");
            command("bow to " + who);
        }
    }
}
 
void
react_shake(object actor)
{
    switch(random(3))
    {
    case 0:
        command("say Don't touch me, " + actor->query_race() + "?");
        break;
    case 1:
        command("say I agree with you, "
                + (actor->query_gender() == G_MALE ? "master" : "lady") + ".");
        break;
    default:
        command("say Why do " + LANG_PWORD(actor->query_race()) +
                " always disagree?");
        break;
    }
}
 
void
arm_me()
{ 
    clone_object(MINE_DIR + "wep/osword")->move(this_object(), 1);
    clone_object(MINE_DIR + "wep/odag")->move(this_object(), 1);
    clone_object(MINE_DIR + "obj/emerald2")->move(this_object(), 1);
    clone_object(MINE_DIR + "obj/emerald")->move(this_object(), 1);
    clone_object(MINE_DIR + "arm/o_gre")->move(this_object(), 1);
    clone_object(MINE_DIR + "arm/o_pl")->move(this_object(), 1);
    clone_object(MINE_DIR + "arm/o_hel")->move(this_object(), 1);
    clone_object(MINE_DIR + "arm/o_bra")->move(this_object(), 1);
    command("wear all");
    command("wield all");
    get_money();
}
 
public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    command("grip hilt tightly");
}
