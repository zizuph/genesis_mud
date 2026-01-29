/*
 *  Undead creature based on the Deathshrieker.
 *  Emit panic when speaking the last words of someone who died.
 *  When it dies, it unleashes a horrible painful scream that harms anyone in the room.
 *
 *  Navarre March 18th 2007
 */

#include <wa_types.h>
#include <ss_types.h>
#include <poison_types.h>
#include <stdproperties.h>
#include <const.h>
#include "/d/Genesis/gems/gem.h"
#include "defs.h"

inherit "/std/monster";
inherit "/std/combat/unarmed";

#define A_CLAWS 0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1
#define H_ARMS 2
#define H_LEGS 3

string* horror_descr = ({"terrifying", "chilling", "horrible", "frightening",
                         "terrorizing", "alarming", "paralyzing", "overwhelming",
                         "startling", "disturbing", "shocking"});

string* gems = ({"diamond_black", "pearl_black", "moonstone", "diamond",
                 "bloodstone", "carnelian", "topaz_yellow"});


string* kill_descr = ({"the apparition crouch and leap forward bringing both muscular " +
                       "arms upwards in an powerful arch violently gutting a brown-cloaked " +
                       "female half-elf from abdomen to throat.", 
                       "the apparition fueled by an unholy bloodthirst slashing "+
                       "its yellow claws deep into a blue-uniformed goblin's " +
                       "chest, only to rise him hooked and twitching. A sickening rip follows " +
                       "and the dead goblin falls to the ground.",
                       "the apparition grasping a wolf-headed hobbit's helm, and with a grim motion " +
                       "tearing the head upwards separating it from the gushing headless corpse slumping "+
                       "to the ground.",
                       "the apparition tearing off the right leg of an young slender female kender, only then "+
                       "to crush the kenders throat as it savours the kenders last scream.",
                       "a muscular brown-eyed male human striking at the apparition's solar plexus effectlessly, "+
                       "only to find himself staring down at the bone-white wrist disappearing into his stomach as "+
                       "he drops to the ground emiting his last scream.",
                       "a stout long-bearded male dwarf roaring as he swing his axe at the apparition, who easily "+
                       "grasps the axe handle with its left claw as it backhands the dwarf in the face, breaking in "+
                       "his skull.",
                       "the apparition easily stopping a charging minotaur by grabing him by the horns. While still carrying "+
                       "the surprised look on his face, the minotaur's head is split into two and tossed on the ground.",
                       "the apparition staring coldly at an ethereal shadowy female presence as it rushes forward aggressively "+
                       "tearing her neck with its left claw. The female presence's eyes widens in reckoning terror " +
                       "as a gaping maw enclose her face. The faceless corpse falls to the ground."});

string* adjs1 = ({"hovering", "aggressive", "repulsive", "shadowy"});
string* adjs2 = ({"intangible", "rapacious", "vengeful", "menacing", "vultuous", "ravening"});

string adj1 = ONE_OF(adjs1);
string adj2 = ONE_OF(adjs2);

object *gHunted = ({ });
int gHaveSetTrigger = 0;

void arm_me();

void
create_monster()
{
    set_name("undead");
    add_name("soulless being");
    add_name("shrieker");

    add_prop(LIVE_I_NO_CORPSE,1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    // Doubt anyone thinks this guy looks like the image of perfection.
    add_prop(NPC_I_NO_LOOKS, 1);

    set_race_name("apparition");
    set_adj(adj1);
    add_adj(adj2);
    set_short(adj1+" "+adj2+" "+"apparition");
    add_prop(LIVE_I_NO_FOOTPRINTS, 1);
    set_gender(G_NEUTER);
    set_aggressive(1);
    add_prop(LIVE_I_UNDEAD, 100);
    
    set_long("This horrible apparition floats above the ground, " +
             "its skeletal face twisted in horrible pain while it "+
             "emits a harsh discordance of sounds. Undead spirits such as "+
             "this soulless creature are known to embody the "+
             "horrible cries and shrieks of the dying as they utter " +
             "their last gasps of life.\n");

    set_stats(({130+random(30),130+random(30),200+random(30),
                130+random(30),130+random(30),130+random(30)}));
    set_hp(query_max_hp());

    //Paralyze, Hunting, Life Drain, and Poison effects.
    set_exp_factor(200);

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT, 60+random(40));
    set_alignment(-600 -random(300));


    set_attack_unarmed(A_CLAWS, 35, 40, W_SLASH, 30, "claws");
    set_attack_unarmed(A_LCLAW, 25, 25, W_SLASH, 35, "left claw");
    set_attack_unarmed(A_RCLAW, 25, 25, W_SLASH, 35, "right claw");

    set_hitloc_unarmed(H_HEAD, 50, 20, "head");
    set_hitloc_unarmed(H_BODY, 50, 40, "body");
    set_hitloc_unarmed(H_ARMS, 50, 20, "arms");
    set_hitloc_unarmed(H_LEGS, 50, 20, "legs");
    set_alarm(0.0, 0.0, &arm_me());
}

void
arm_me()
{
    for(int i = 0; i < 7; i++)
    {
        clone_object("/d/Genesis/gems/obj/"+ONE_OF(gems))->move(TO, 1);
    }
}


int
set_hunting(object ob)
{
    if(!ob)
        return 0;

    if (!gHaveSetTrigger)
    {
        trig_new("%s 'leaves' / 'sneaks' / 'rides' / 'panics' [and] [rides] [flees] [limping] %w", "react_leave");
    }

    gHaveSetTrigger = 1;

    if (member_array(ob, gHunted) == -1)
    {
        if(environment(ob) == environment(TO))
        {
            ob->catch_msg(QCTNAME(TO) + " turns its eyes at you.\n");
            tell_room(environment(TO),QCTNAME(TO) + " turns its eyes at " +
                      QTNAME(ob) +".\n", ob);
        }
        gHunted += ({ ob });
    }
    gHunted -= ({ 0 });
    return 1;
}


void
follow_player(object me, string dir)
{
    me->command(dir);
}

void
react_leave(string name, string dir)
{
    object tone;

    tone = find_player(lower_case(name));

    if(!tone)
    {
        return;
    }
    if(member_array(tone,gHunted) != -1)
    {
        dir = extract(dir,0,-3);
        set_alarm(0.0, 0.0, &follow_player(this_object(), dir));
    }
}

void
attack_object(object ob)
{
    // Let us not hunt the smallest ones.
    if(ob->query_average_stat() < 110)
    {
        ::attack_object(ob);
        return;
    }
    set_alarm(0.0,0.0,&set_hunting(ob));
    ::attack_object(ob);
}

void
attacked_by(object ob)
{
    // Let us not hunt the smallest ones.
    if(ob->query_average_stat() < 110)
    {
        ::attacked_by(ob);
        return;
    }
    set_alarm(0.0,0.0,&set_hunting(ob));
    ::attacked_by(ob);
}


int
find_interactive(object ob)
{
    return interactive(ob);
}

int
special_attack(object enemy)
{
    mixed *hitresult;
    string how;
    object poison;
    object *players;

    object me = this_object();


    if (!random(4))
    {
        if(!random(3))
        {

            tell_room(environment(me), "As the " +short()+ " lets out a "+ ONE_OF(horror_descr) +
                      " scream from one " + "of its many victims a vision appears in your " +
                      "mind. You see "+ONE_OF(kill_descr)+"\nYou feel despair creeping over you.\n");

            players = filter(all_inventory(environment(me)), find_interactive);

            for(int i = 0; i < sizeof(players); i++)
            {
                if(present(players[i], environment(me)) && !present("_shriker_stun", players[i]))
                {
                    
                    clone_object(TUN_OBJECTS+"shrieker_stun")->move(players[i], 1);
                    players[i]->add_panic(100+random(150));
                }
            }
        }
        else
        {
            hitresult = enemy->hit_me(600+random(300), W_SLASH, me, -1);

            if(enemy->query_hp() < 1)
            {

                enemy->catch_msg(QCTNAME(me) + " grabs you by the throat and squeezes its "+
                                  "claws deep into your flesh, forcing you to scream out in pain, "+
                                  "as it breaks your neck!\n");

                tell_room(environment(me), QCTNAME(me) + " grabs " + QTNAME(enemy) + 
                          " by the throat and squeezes its claws deep into "+HIS(enemy)+
                          " flesh, forcing "+HIM(enemy)+" to scream out in pain as it breaks "+
                          HIS(enemy)+" neck!\n", enemy);
                enemy->command("scream");

                enemy->do_die(this_object());       
                return 1;
            }

            switch (hitresult[0])
            {
                case 0:
                    enemy->catch_msg(QCTNAME(me) + " charges at you!\n"+
                                      "You evade its attack.\n");

                    tell_room(environment(me), QCTNAME(me) + " charges at " + QTNAME(enemy) + "!\n" +
                              QCTNAME(enemy) + " evades the attack.\n", enemy);
                    break;
                case 1..10:
                    enemy->catch_msg(QCTNAME(me) + " sinks its claws into your flesh!\n"+
                                      "You feel your life force ebbing away.\n");
                    

                    tell_room(environment(me), QCTNAME(me) + " sinks its claws into " + QTNAME(enemy) + "!\n" +
                              QCTNAME(enemy) + " turns pale.\n", enemy);
                    me->heal_hp(hitresult[3]/2);
                    break;
                default:
                    enemy->catch_msg(QCTNAME(me) + " slashes its claws across your body!\n"+
                                      "You feel a weakness spreading instantly through your veins.\n");

                    tell_room(environment(me), QCTNAME(me) + " slashes its claws across " + QTNAME(enemy) +
                              "'s body!\n", enemy);

                    poison = clone_object("/std/poison_effect");
                    poison->move(enemy, 1);
                    poison->set_time(60+random(60)); // Short but nice.
                    poison->set_interval(20);
                    poison->set_strength(100);
                    poison->set_damage(({POISON_FATIGUE, 90, POISON_STAT, SS_CON}));
                    poison->set_poison_type("shrieker_poison");
                    poison->start_poison();
             }
        }
        return 1;
    }
    return 0;
}

 
