/*
 * goblin_lord.c
 * The goblin lord in the obsidian caves in Mirkwood.
 * The player will not fall asleep if they have the property
 * MAGIC_I_RES_MAGIC defined greater than 10.
 * Written by Trenix@Genesis, 8-16-93
 *
 */

inherit "/std/monster";

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include "/secure/std.h"

#define COINS     "/std/coins"
#define WEP_PATH  "/d/Rhovanion/common/weapons/"
#define ARM_PATH  "/d/Rhovanion/common/armours/"
#define OBJ_PATH  "/d/Rhovanion/common/objects/"
#define SLEEPER   "/d/Rhovanion/common/objects/sleeper"
#define SLEEPROOM "/d/Rhovanion/common/ob_caves/sleep_room"

void add_speech(string str);  /* A handy little function. */

void
create_monster()
{
    if ( !IS_CLONE )
    {
        return;
    }
    seteuid(getuid());
    set_name( ({ "lord", "goblin" }) );
    set_pname( ({ "lords", "goblins" }) );
    set_short("goblin lord");
    set_pshort("goblin lords");
    set_long("@@query_long");
    set_race_name("goblin lord");
    set_gender(0); /* Male */    /* str, dex, con, int, wis, dis */
    set_stats( ({ 150+random(5), 170+random(8), 115+random(5), 
                  40+random(5),  40+random(5), 110+random(5) }) );
    set_hp(query_max_hp());
    set_mana(query_max_mana());
    set_alignment(-300);
    set_all_hitloc_unarmed(40); /* AC of 40 without armor */
    set_living_name("_trenix_goblin_lord_");
    set_aggressive(1);
    set_attack_chance(100);
    set_chat_time(1);  /* He just doesn't talk enough. */
    set_cchat_time(1); /* All those monks with their plexus hits.. */
    add_speech("How dare you invade my caves.");
    add_speech("You've made your last mistake.");
    add_speech("At last, your life is mine.");
    add_speech("If you're lucky, I'll let you serve me as a slave.");
    add_speech("Another day, another death.");
    add_speech("Meet thy doom you fool.");
    add_speech("You won't escape me.");
    add_speech("I take no prisoners.");
    add_speech("Over my dead body.");
    add_speech("Only I hold the key."); /* Quest hint */
    set_skill(SS_WEP_SWORD,80);
    set_skill(SS_2H_COMBAT,50);
    set_skill(SS_UNARM_COMBAT,70);
    set_skill(SS_WEP_CLUB,80);
    set_skill(SS_WEP_KNIFE,40);
    set_skill(SS_PARRY,70);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_AWARENESS,30); /* Dumb goblin */
    add_prop(CONT_I_HEIGHT,193);
    add_prop(CONT_I_WEIGHT,50000);
    add_prop(LIVE_I_SEE_DARK,50);
    add_prop(LIVE_I_SEE_INVIS,10);
    add_prop(LIVE_I_NEVERKNOWN,1);
    call_out("arm_me",1);
}

string query_long()
{
    return (break_string("You've invaded on the goblin lord of the "+
            "obsidian caves in Mirkwood. He's not known to be the "+
            "most welcoming of hosts.\n",65));
}

void add_speech(string str)
{
    add_chat(str);
    add_cchat(str);
}

arm_me()
{
    object sword, platemail, shield, helmet, key, cash;

    sword     = clone_object(WEP_PATH+"ob_sword");
    platemail = clone_object(ARM_PATH+"ob_plate");
    shield    = clone_object(ARM_PATH+"ob_shield");
    helmet    = clone_object(ARM_PATH+"ob_helm");
    key       = clone_object(OBJ_PATH+"ob_key");
    cash      = clone_object(COINS);

    if ( objectp(sword) )
    {
        sword->move(this_object());
    }
    if ( objectp(platemail) )
    {
        platemail->move(this_object());
    }
    if ( objectp(shield) )
    {
        shield->move(this_object());
    }
    if ( objectp(helmet) )
    {
        helmet->move(this_object());
    }
    if ( objectp(key) )
    {
        key->move(this_object());
    }
    if ( objectp(cash) )
    {
        cash->set_coin_type("silver");
        cash->set_heap_size(100);
        cash->move(this_object());
    }
    command("wield all");
    command("wear all");
    command("grin");
}

attacker_out_of_mana(object enemy)  /* Called from his sword during attack */
{
    object sleeper, env;
    string str, name;

    if ( !objectp(enemy) )
    {
        return;  /* Oh well. */
    }
    if ( enemy->query_wiz_level() )
    {
        write("Your opponent fails to fall asleep.\n");
        tell_object(enemy,"You fail to fall asleep.\n");
        enemy->set_mana(enemy->query_max_mana());
        command("say away with you.");
        command("say nasty wizards always pick on me.");
        command("sob");
        return;
    }
    if ( enemy->query_prop(MAGIC_I_RES_MAGIC) > 10 )
    {
        write("Your opponent resists your magic.\n");
        tell_object(enemy,"You have a protected feeling.\n");
        command("spit");
        command("say How powerful you are. Next time I'll bring friends.");
        command("cackle");
        return;
    }        
    sleeper = clone_object(SLEEPER);
    if ( !objectp(sleeper) )
    {
        write("You sigh helplessly.\n");
        say("The goblin lord sighs helplessly.\n");
        command("say We've encountered a bug, I can't put you to sleep.");
        command("say Please make sure and bug it.");
        enemy->stop_fight(this_object());
        this_object()->stop_fight(enemy);
        set_aggressive(0);
        set_attack_chance(0);
        SECURITY->do_debug("destroy",sleeper);
        return;
    }
    sleeper->move(enemy);
    sleeper->assign_owner(enemy);
    enemy->stop_fight(this_object());
    this_object()->stop_fight(enemy);
    name = capitalize(enemy->query_name());
    str = name+" falls asleep from exhaustion.\n";
    env = environment(this_object());
    write(str);
    tell_object(enemy,"You fall asleep from exhaustion.\n");
    if ( objectp(env) )
    {
        tell_room(env,str,enemy);
    }
    /* The player shouldn't wake up wielding a sword. */
    enemy->command("unwield all");
    enemy->command("remove all");
    if ( objectp(env) )
    {
        tell_room(env,name+" is quickly carried away.\n",enemy);
    }
    enemy->move_living( "M", SLEEPROOM, 1 );
    sleeper->start_sleep();
    return;
}

/* Solamnian Knights are honored by this kill. */

query_knight_prestige()
{
    return 300;
}

/* EOF */
