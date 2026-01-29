//-*-C++-*-
// file name:    
// creator(s): Lilith, July 1997
// revised:    Lucius, Jan 2009: Runtime fix, query_short() -> short()
// purpose:    Scavenger   
// note:       This creature lives in dark places throughout 
//             Avenir; Ogres in the Utterdark are known to semi-
//             tame them as pets. Phrynos can squirt blood from
//             a gland near their eyes, and this tainted blood
//             can cause terrible pain and temporary blindness      
//             when it comes in contact with an enemy's eyes.
//             They are scavengers, feeding on rubbish and carrion.
// bug(s): 
// to-do:
#pragma strict_types
inherit "/std/creature";

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include "/d/Avenir/include/defs.h"      /* Short-hand macros */
#include "/d/Avenir/include/paths.h"     /* Avenirian path defines */
#include "/d/Avenir/include/macros.h"    /* ADD_SKIN, etc */
#include <macros.h>                      /* macros like VBFC and QNAME */
#include <stdproperties.h>               /* properties */
#include <wa_types.h>                    /* weapon and armour defs */
#include <ss_types.h>                    /* skill and stat defs */

/* These define what it will attack with */
#define A_LFORE  TS_LHAND
#define A_RFORE  TS_RHAND
#define A_RHLEG  TS_RFOOT
#define A_LHLEG  TS_LFOOT
#define A_HORN   TS_HEAD
#define A_LIP    TS_HEAD

/* These define what body parts will be hit in fights */
#define H_HEAD    TS_HEAD
#define H_ABDOM   TS_TORSO
#define H_RMID    TS_RARM  
#define H_LMID    TS_LARM
#define H_RHLEG   TS_RFOOT 
#define H_LHLEG   TS_LFOOT

string my_long();
string *randadj;

void
create_creature()
{
    randadj = ({ "ugly", "giant", "scarred", "horned", "squat", 
                 "stump-legged", "speckled", "yellow", "pale", 
                 "short-tailed", "enraged", "pregnant", "lumpy",
                 "long-nosed", "lumbering", "small", "huge"});

//    if (!IS_CLONE)
//        return;

    set_name("phrynos");
    set_pname("phryna");
    add_name(({"reptile", "toad"}));
    set_race_name("phrynos");
    set_adj("reptilian");
    set_adj(randadj[random(sizeof(randadj))]);
    set_long(my_long);
   
    if (query_adj() == "pregnant")
        set_gender(G_FEMALE);
    else
        set_gender(G_MALE);

    set_alignment(0);
    set_aggressive(1);     
   
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT, 90);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_AWARENESS,   100);

    add_prop(LIVE_O_ENEMY_CLING, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 100); /* A creature of the dark */
    add_prop(LIVE_I_QUICKNESS, -50);
    add_prop("_ranger_i_not_brawl", 1); 
    add_prop("_live_m_no_plexus", "Its belly is too close to the ground!\n");

    if (random(10))
        add_leftover("/d/Avenir/inherit/leftover", "gland",1, "", 0,0);
    if (query_gender() == G_FEMALE)
        add_leftover("/d/Avenir/inherit/leftover", "fetus",1, "", 0,0);

    set_act_time(10);
    add_act("emote roots around, looking for food.");
    add_act("emote snatches a bird out of the air with its long, "+
        "flexible tongue.");
    add_act("emote opens.");
    
    add_act("get all");
    add_act("eat all");
     
    /* Sets the stats for us, its a simple npc */
    default_config_creature(155 + random(45));

    /*               'weapon', hit, pen, damage type, %use, desc  */
    set_attack_unarmed(A_LFORE, 80, 40, W_SLASH,    20, "claws on its left foreleg");
    set_attack_unarmed(A_RFORE, 80, 40, W_SLASH,    20, "claws on its right foreleg");
    set_attack_unarmed(A_RHLEG, 80, 50, W_BLUDGEON, 10, "right hind leg");
    set_attack_unarmed(A_LHLEG, 80, 50, W_BLUDGEON, 10, "left hind leg");  
    set_attack_unarmed(A_HORN,  80, 40, W_IMPALE,   25, "crown of horns");
    set_attack_unarmed(A_LIP,   80, 40, W_SLASH,    15, "scaled upper lip");    

    /*                  where,     ac,  %hit,  desc  */
    set_hitloc_unarmed(H_HEAD,  ({ 55 }), 35, "horned head");
    set_hitloc_unarmed(H_ABDOM, ({ 15 }),  5, "soft yellow underbelly");
    set_hitloc_unarmed(H_RMID,  ({ 40 }), 15, "right foreleg");
    set_hitloc_unarmed(H_LMID,  ({ 40 }), 15, "left foreleg");
    set_hitloc_unarmed(H_RHLEG, ({ 40 }), 15, "right hind leg");
    set_hitloc_unarmed(H_LHLEG, ({ 40 }), 15, "left hind leg");


}

string
my_long()
{
    int i;
    string str;

    i = random(4);
    switch(i)
    {
        case 0:
            str = "seems to stagger under the weight of its cumbersome body. ";
            break;
        case 1:
            str = "moves with a slow, sinuous grace almost alien to its "+
                  "repulsive appearance. ";
            break;
        case 2:
            str = "is watching you with an inscrutible expression that warns "+
                  "you not to underestimate its intelligence.";
            break; 
        case 3:
            str = "smells so strongly of carrion that you must suppress an "+
                  "urge to vomit. ";
            break;
    }
    return "A fearsome "+ query_adj() +" phrynos.\n"+
           "This creature is reptilian, with the scales and horns "+
           "projecting from its head at various angles. "+
           "Its short and stumpy legs support a lozenge-shaped body "+
           "ridged with spiked scales.\n"+
           "It "+ str +"\n";
}

/* Functions used in the special_attack function, below */
int 
worn_helmet(object ob)
{
    return (ob->query_at() & A_HEAD && ob->query_adj() == "worn"); 
    /* Protects the eyes */
}

int
is_valid_enemy(object who)
{
    if (environment(who) == environment(TO) && !who->query_ghost())
        return 1;
    return 0;
}

object*
valid_enemies()
{
    object *ene = query_enemy(-1);
    object *ene_list = ({ });
    int i;
    ene -= ({ TO });
    for (i=0; i<sizeof(ene); i++)
        if (is_valid_enemy(ene[i]))
	      ene_list += ({ ene[i] });
        else
        {
            stop_fight(ene[i]);
            ene[i]->stop_fight(TO);
        }
        ene_list -= ({ 0 });
    return ene_list;
}

int squirt_fail(object ob, object helm)
{
    if (ENV(ob) != ENV(TO) || ob->query_ghost())
    {
        TO->stop_fight(ob);
        return 1;
    }
    ob->catch_tell("The phrynos' stream of blood is deflected "+
        "from your eyes by the "+ helm->short() + " you are "+
        "wearing!\n");
    tell_watcher(QCTNAME(ob) +" seems unaffected by the stream of "+
        "blood that the phrynos ejected in "+ ob->query_possessive()+
        " face.\n", ob);

    return 1;                
}

int squirt_eyes(object ob)
{
    if (ENV(ob) != ENV(TO) || ob->query_ghost())
    {
        TO->stop_fight(ob);
        return 1;
    }
    ob->catch_tell("The phrynos' blood lands full in your "+
        "face, burning your eyes! OUCH!\n");
    tell_watcher("The phrynos' blood lands full in "+ 
        QTPNAME(ob) +" face!\n", ob);   

    ob->command("$scream");
    ob->command("$unwield all");        

    if (!ob->query_prop(LIVE_I_ATTACK_DELAY))
        ob->add_attack_delay(5 + random(15));
    ob->catch_tell("You try to wipe the tainted blood from your "+
        "eyes, but succeed only in rubbing it in further.\n");
    ob->run_away();
    return 1;                
}
int
squirt_test(object ene)
{
    object *helmets, helm;

    if (ENV(ene) != ENV(TO) || ene->query_ghost())
    {
        TO->stop_fight(ene);
        return 1;
    }
    if (!ene)
    {
        tell_room(ENV(TO), "The blood splatters on the ground, sizzling "+
            "like acid.\n");
        return 0;
    }
    if (!CAN_SEE(ene, TO))
    {
        tell_room(ENV(TO), "The blood splatters on the ground, sizzling "+
            "like acid.\n");
        return 0;
    }
    if (sizeof(helmets = filter(all_inventory(ene), worn_helmet)))
    {
        helm = helmets[0];
        squirt_fail(ene, helm);
        return 1;
    }
    if (random(200) > DEX(ene))
    {
        squirt_eyes(ene);
        return 1;
    }
    ene->catch_tell("You move quickly out of the path of the "+ 
        short() +"'s stream of poisonous blood.\n");
    tell_watcher("In a display of remarkable dexterity, "+ 
        QTNAME(ene) +" twists out of the path of the phrynos' "+
        "'s poisonous blood.\n", ene);
    tell_room(ENV(TO), "The blood splatters on the ground, sizzling "+
        "like acid.\n");
}

void
squirt(object victim)
{
    object *ene = valid_enemies();
    object vic1, vic2;

    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
        TO->stop_fight(victim);
        return;
    }

    tell_watcher("The "+ short() +" seems to blink its lidless eyes, "+
        "ejecting a stream of blood in your direction.\n");
    
    if (random(4))
        vic1 = victim;
    else
        vic1 = ene[random(sizeof(ene))];
        vic2 = ene[random(sizeof(ene))];

    if (vic1 = vic2)
        set_alarm(2.0, 0.0, &squirt_test(vic1));
    else
    {
        set_alarm(2.0, 0.0, &squirt_test(vic1));
        set_alarm(2.0, 0.0, &squirt_test(vic2));
    }
}
int
special_attack(object victim)
{
    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
        TO->stop_fight(victim);
        return 1;
    }

    switch (random(6))
    {
        case 2: squirt(victim);
            return 1;
        case 5: squirt(victim);
            return 1;
        default: break;
    }
    return 0;
}

