inherit "/std/monster";
/*  this is trenix's goblin_lord   (sorry, i dont know how to put 
 *  this on the top of the code :(   */
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

#define PHRASES ({ "How dare you come here!", \
                   "You've made your last mistake.", \
                   "At last, your life is mine.", \
                   "If you're lucky, I'll let you serve me as a slave.", \
                   "Another day, another death.", \
                   "Meet thy doom you fool.", \
                   "You won't escape me.", \
                   "I take no prisoners.", \
		   "Over my dead body." })


create_monster()
{
    if ( !IS_CLONE )
    {
        return;
    }
    seteuid(getuid());
    set_name( ({ "creature", "monster","killer" }) );
    set_pname( ({ "creatures", "monsters","killers" }) );
    set_short("evil looking creature");
    set_pshort("evil looking creatures");
    set_long("@@query_long");
    set_race_name("creature");
    set_gender(0); /* Male */    /* str, dex, con, int, wis, dis */
    set_stats( ({ 400, 300, 400, 20, 40, 200 }) );
    set_hp(query_max_hp());
    set_alignment(-300);
    set_all_hitloc_unarmed(30); /* AC of 30 without armor */
    set_living_name("_briaeros_goblin_lord_");
    set_aggressive(1);
    set_attack_chance(100);
    set_cact_time(15);
    add_cact("@@growl");
    set_skill(SS_WEP_SWORD,100);
    set_skill(SS_2H_COMBAT,50);
    set_skill(SS_UNARM_COMBAT,70);
    set_skill(SS_WEP_CLUB,80);
    set_skill(SS_WEP_KNIFE,40);
    set_skill(SS_PARRY,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_AWARENESS,30); /* Dumb goblin */

    set_chat_time(2);
    add_chat("You do want to live forever?");
    add_chat("You ever danced with the devil?");

    set_cchat_time(2);
    add_cchat("Die! die! die! die!");
    add_cchat("I'm going to kill you");

    add_prop(CONT_I_HEIGHT,193);
    add_prop(CONT_I_WEIGHT,50000);
    add_prop(LIVE_I_SEE_DARK,50);
    add_prop(LIVE_I_SEE_INVIS,10);
    add_prop(LIVE_I_NEVERKNOWN,1);
    call_out("arm_me",1);
}

string query_long()
{
    return (break_string("You've invaded on the creature in it's domain."+
	    "He's not known to be the most welcoming of hosts.\n",65));
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
        cash->set_heap_size(50);
        cash->move(this_object());
    }
    command("wield all");
    command("wear all");
    command("grin");
}

string random_growl()
{
    return (PHRASES[random(sizeof(PHRASES))]);
}

growl(string str)
{
    object env;

    env = environment(this_object());
    if ( !stringp(str) || !strlen(str) )
    {
        str = random_growl();
    }
    write("You growl: "+str+"\n");
    if ( objectp(env) )
    {
        tell_room(env,"The goblin lord growls: "+str+"\n",this_object());
    }
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
    if ( enemy->query_prop(MAGIC_I_RES_MAGIC) )
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
        SECURITY->do_debug("destroy",sleeper);
        write("You sigh helplessly.\n");
        say("The goblin lord sighs helplessly.\n");
        command("say We've encountered a bug, I can't put you to sleep.");
        command("say Please make sure and bug it.");
        enemy->stop_attack(this_object());
        this_object()->stop_attack(enemy);
        return;
    }
    sleeper->move(enemy);
    sleeper->assign_owner(enemy);
    enemy->move(SLEEPROOM);
    sleeper->start_sleep();
    enemy->add_prop(LIVE_S_EXTRA_SHORT," is sleeping");
    name = capitalize(enemy->query_name());
    str = name+" falls asleep from exhaustion.\n";
    env = environment(this_object());
    write(str);
    tell_object(enemy,"You fall asleep from exhaustion.\n");
    if ( objectp(env) )
    {
        tell_room(env,str,enemy);
        tell_room(env,name+" is quickly carried away.\n",enemy);
    }
    return;
}

/* Solamnian Knights are honoured by this kill. */

query_knight_prestige()
{
    return 300;
}

/* EOF */
