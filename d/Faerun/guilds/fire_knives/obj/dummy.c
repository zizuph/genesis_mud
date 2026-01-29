/* test dummy */

inherit "/std/monster";
inherit "/std/combat/unarmed";   /* Get standard unarmed routines */

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>

#define SECONDS  600  

int remainingHP;
int currentHP = 5000;
int damage;
int dps;

int defeated = 0;


#define LOG(x,y)  write_file("/w/nerull/open/" + x, extract(ctime(time()), \
                  4, 15) +" "+ y )      


void
do_measure()
{
    
     remainingHP = this_object()->query_hp();
    
     damage = currentHP - remainingHP;
     dps = damage / 600;
    
     this_object()->command("say DPS DONE = "+dps+", DAMAGE DONE = "
     +damage+".\n");
     this_object()->command("say DAMAGE DONE = "+damage+".\n");
     
     
     
     currentHP = this_object()->query_hp();  
     this_object()->command("say HP LEFT = "+currentHP+".\n\n\n");
     LOG("dps_log_50", "DPS: "+dps+", DAMAGE: "+damage+", HP LEFT: "
     +currentHP+".\n");
     this_object()->command("say RESETTING TESTDUMMY.\n");
     
     clone_object("/w/nerull/benchmark/dummytest_50")->move(environment(this_object()));
     remove_object();
     
}


void
do_die(object killer)
{ 
    this_object()->command("emote looks crushed and defeated!\nSuddenly, "
    +"some magical energies restores it to former fixed stature.\n");
    
    this_object()->set_hp(5000);
    this_object()->set_mana(5000);
    this_object()->set_fatigue(2000);
    
    defeated = defeated + 1;
}


int
request_defeated()
{ 
    write("This dummy is defeated "+defeated+" times.\n");
    
    return 1;
}


int
reset_defeated()
{
    if (defeated == 0)
    {
        write("The counter is set to zero already.\n");
    
        return 1;  
    }
    
    write("You reset the defeated-counter to zero.\n");
    
    defeated = 0;
    
    return 1;
}


create_monster()
{

    set_race_name("hobbit");
    set_name("Dummy"); 
    add_name("dummy");
    set_short("wooden test dummy");
    set_adj(({"wooden", "test" }));
    set_long("This is a wooden test dummy shaped like a human. Its purpose " 
    +"is to measure combat efficiencies of different weaponry and offensive "
    +"specials. You may <dummystatus> to check how many times the "
    +"dummy has 'died, or"
    +"<reset> to nullify that counter.\n");

    /* str, dex, con, int, wis, dis */
    
    set_stats(({200, 200, 200, 200, 200, 200}));

    set_skill(SS_DEFENCE, 100);
    //set_skill(SS_PARRY, 100);
    
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_FEAR, 1);
    //add_prop(LIVE_I_SEE_INVIS, -1);
   // add_prop(LIVE_I_ATTACK_DELAY, 9999);
    
    /*           hit/pen           %% on usage per c-round */
      
    set_attack_unarmed(0,  60, 50, W_BLUDGEON, 0, "steel fist");

   
    /* Give the elemental some hit locations */

    /* Arguments to set_hitloc_unarmed:
     *   hit location id, ac, percent hit, description
     */
    set_hitloc_unarmed(A_HEAD, 40, 15, "head");
    set_hitloc_unarmed(A_R_ARM, 40, 10, "right arm");
    set_hitloc_unarmed(A_L_ARM, 40, 10, "left arm");
    set_hitloc_unarmed(A_BODY, 40, 45, "body");
    set_hitloc_unarmed(A_LEGS, 40, 20, "legs");
}


int
special_attack(object enemy)
{
    object me = this_object();

    mixed *hitresult;
    string how;



    if (random(7))
    {
        return 0;  /* Continue with the normal attacks */
    }

    
    enemy->set_hp(5000);
    enemy->set_mana(5000);
    enemy->set_fatigue(2000);
     
    enemy->catch_tell(query_The_name(enemy) 
    + " REFILLS YOUR MANA/HP/FATIGUE.\n");
    tell_watcher(QCTNAME(me) + " REFILLS THE HP, MANA AND FATIGUE OF " 
    + QTNAME(enemy) + ".\n", enemy);

    return 1; /*  Important! Should not have two attacks in a round. */
}


public int query_panic() 
{ 
    return 0; 
} 


void
init_living()
{
    ::init_living();

    add_action(reset_defeated, "reset");
    add_action(request_defeated, "dummystatus");
}

