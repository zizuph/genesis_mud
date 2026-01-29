/* file name:       /d/Avenir/common/holm/t_camp/nasty_troloby.c
*  creator(s):      (Rangorn , Feb 97)
*  revisions:
*  purpose:  This is the bodyguard for the wizard
*  note:
*  bug(s):
*  to-do:
*/

inherit "/d/Genesis/specials/npc/stat_based_specials";
inherit "/std/monster";

#include "../holm.h";
#include "/d/Avenir/include/relation.h"
#include <ss_types.h>
#include <wa_types.h>
#include <math.h>

#define FIXEUID         setuid(); seteuid(getuid())
#define INSULT_SEED   57757
#define NAME_TO_POO   ({ "sewer-breath", "feces-eater", "dirt-scratcher", \
                         "turd-head", "dung heap", "flea-chewer", \
                         "bum-kisser", "urine-drinker", "tail-sniffer"})


void
create_monster()
{
    set_name("nasty");
    add_name("wizard_troloby_guard");
    set_race_name("troloby");
    set_gender(G_NEUTER);
    set_adj("towering");
    set_adj("huge");
    set_long("It is a huge towering troloby.\n"+
        "It is perhaps the best-fed of the trolobies you've seen, "+
        "as its belly bulges round and shiny.\n"+
        "Instead of a left hand the troloby has giant claw growing " +
        "from its left arm.\n");

    default_config_npc(random(20) + 150);    
    refresh_mobile();
  
    set_skill(SS_BLIND_COMBAT, 30);
    set_skill(SS_UNARM_COMBAT, 90);
    set_skill(SS_DEFENCE, 90);
    set_all_attack_unarmed(50, 50);
    set_all_hitloc_unarmed(15);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(OBJ_I_WEIGHT,80000);
    add_prop(OBJ_I_VOLUME,70000);
  
    set_act_time(3);
    add_act("grin evil");
    add_act("smirk amused");
    add_act("flex"); 
    add_act("emote gives you an intimidating look.");
    add_act("burp");

    set_chat_time(4);
    add_chat("So you have come here for the Hunt?");
    add_chat("Maybe I will spare your life, pure one."); 
    add_chat("Take care that you do not offend my Master.");
  
    set_cchat_time(4);
    add_cchat("Now the Hunter becomes the Hunted.");
    add_cchat("More meat for the pot! We'll eat well tonight.");
   
    FIXEUID;
}

public void
equip_me()
{
    object leather_tunic;

    leather_tunic = clone_object(HOLM_OBJ + "leather");
    leather_tunic->move(this_object());
    command("wear all");
}

public void
add_introduced(string name)
{
    int insult;

    if (name == "nemur")
        return;

    insult = NAME_TO_RANDOM(name, INSULT_SEED, 9);
    command("say Well you sure got an ugly name there "+ capitalize(name));
    command("think");
    command("say It reminds me of the sybarite word for: "+
        NAME_TO_POO[insult] +"!");
    command("cackle");
}

public int
special_attack(object enemy)
{
    string wiever_message, player_message;
    int hp, i, health;
    float test, damage; 
 
    i = random(100);

    damage = 0;
    switch(i)
    {
        case 0..8:
            damage = 0.05;
            break;
        case 9..14:
            damage = 0.10;
            break;
        case 15..18:
            damage = 0.12;
            break;
        case 19..20:
            damage = 0.15;
            break;
        case 21:
            damage = 0.20;  
            break;
        default:
            return 0; 
    }

    // We intended to do a special attack, but it was evaded.
    if (enemy->query_not_attack_me(this_object(), -1))
    {
        return 1;
    }
  
    /* The damage will be a fraction of their total HP */
    health = enemy->query_max_hp();
    test = itof(health); /* Converts the integer:health to a float:test. */ 
    damage = damage * test;  /* Calculates the actual damage that is done. */ 
    hp = ftoi(damage); 

    // cb_tohit check to see if we hit.    
    if (!query_special_did_hit(this_object(), enemy))
    {
        hp = 0;
    }
    
    mixed* hitresult = enemy->hit_me(hp, W_SLASH, this_object(), -1);
    
    switch(hitresult[0])
    {
        case -3..0:
            player_message = "barely misses you";
            wiever_message = "but the troloby barely misses";
            break;
        case 1..5:
            player_message = "barely scratches you";
            wiever_message = "but the troloby barely scratches";
            break;
        case 6..15:
            player_message = "tears up a shallow wound in your body";
            wiever_message = "tears up a shallow wound in";
            break;
        case 16..30:
            player_message = "tears a deep wound into your body";
            wiever_message = "and tears a deep wound into";
            break;
        case 31..50:
            player_message = "rips savagely into your body";
            wiever_message = "and rips savagely into";
            break;
        default:
            player_message = "tears deep into your body, ripping your flesh";
            wiever_message = "and brutaly grinds its claw deep into";  
            break;
    }
    
    enemy->catch_msg("The troloby makes a vicious slash towards you and " +
                   player_message + " with its claw.\n");
  
    tell_watcher("The troloby makes a vicious slash towards " + 
                 QCTNAME(enemy) +" "+ wiever_message + " " + 
                 enemy->query_objective() + " with its claw.\n",enemy);
    if (i < 10)
    {
        refresh_living();
        enemy->catch_msg("The troloby managed to drain life from you " +
            "and looks healthy again.\n");
        tell_watcher("The troloby regains his health.\n");
    }
    return 1;
}

void
throw_myself(object ob)
{
    object          *enemies, *ene;
    int             i, j, hp, max;
    string          rescue, *rescue2;

    if (!present(ob, environment(this_object())))
        return;

    enemies = all_inventory(environment(this_object())) - 
              ({ ob, this_object() });

    for (i = 0; i < sizeof(enemies); i++)
    if (enemies[i]->query_attack() == ob)
    {
        this_object()->attack_object(enemies[i]);
        enemies[i]->attack_object(this_object());
    }
}

/* Stop knights from cheating with mercy. */
public int
query_disallow_mercy(void)
{
        return 1;
}
