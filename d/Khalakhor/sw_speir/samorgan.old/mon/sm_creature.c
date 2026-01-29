/* smaller creatures for Eil-Galaith isle
 * Created by Damaris 12/Y2K
 */
#pragma strict_types
inherit "/std/creature";
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */
inherit "/std/act/action";
inherit "/std/act/domove";
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
private string query_creature_one();
private string query_creature_two();
private string query_creature_three();
private string query_creature_name();

string _ADJ = query_creature_one();
string __ADJ = query_creature_two();
string ___ADJ = query_creature_three();
string CREATURE = query_creature_name();
/*
 * Define some attack and hitloc id's
 */
#define A_BITE  1
#define A_LCLAW 2
#define A_RCLAW 4

#define H_HEAD 1
#define H_BODY 2
void
create_creature()
{
    set_name( CREATURE );
    set_race_name( CREATURE );
    set_short(""+_ADJ+" "+ __ADJ+" "+ CREATURE+"");
    set_adj( _ADJ  );
    add_adj( __ADJ );
    add_adj(___ADJ);
    set_gender(G_FEMALE);
    set_act_time(15);

    /* Sets the desciption */
    set_long("This is a " + short() + ".\n"+
      "She has soft "+ ___ADJ+" eyes.\n"+
      "She looks cute and cuddly.\n");
    add_act("purr sof");
    add_act("emote scampers around a bit staring at you.");
    add_act("yawn slee");
     /* str, con, dex, int, wis, dis */
    set_stats(({ 10, 10, 10, 10, 15, 45}));

    set_skill(SS_DEFENCE, 30);
    set_skill(SS_SWIM, 80);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    
    /* Leftover 1 */
    add_leftover("/std/leftover", "skin", 1, 0, 0, 0);
    /* Leftover 2 */
    add_leftover("/std/leftover", "heart", 1, 0, 1, 1);

    /* Give the creature some attacks */

    /* Arguments to set_attack_unarmed:
     *   attack id, hit, pen, damage type, percent usage, description
     */
    set_attack_unarmed(A_BITE,  20, 30, W_IMPALE, 40, "jaws");
    set_attack_unarmed(A_LCLAW, 40, 20, W_SLASH,  30, "left paw");
    set_attack_unarmed(A_RCLAW, 40, 20, W_SLASH,  30, "right paw");

    /* Give the panther some hit locations */

    /* Arguments to set_hitloc_unarmed:
     *   hit location id, ac, percent hit, description
     */
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20,}), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30,}), 80, "body");
}

/*
 * Here we redefine the special_attack function which is called from
 * within the combat system. If we return 1 then there will be no
 * additional ordinary attack.
 *
 */
int
special_attack(object enemy)
{
    object me;
    mixed *hitresult;
    string how;

    /* Only execute the special attack 1 in 10 rounds */
    if (random(10))
    {
	return 0;  /* Continue with the normal attacks */
    }

    hitresult = enemy->hit_me(20+random(30), W_IMPALE, me, -1);
    switch (hitresult[0])
    {
        case 0:
            how = "unwounded";
            break;
        case 1..10:
            how = "barely wounded";
            break;
        case 11..20:
            how = "wounded";
            break;
        default:
            how = "seriously wounded";
            break;
    }

    enemy->catch_tell(query_The_name(enemy) + " tears into your throat!\n"+
      "You are " + how + ".\n");
    tell_watcher(QCTNAME(me) + " tears into " + QTNAME(enemy) + "!\n" +
        capitalize(enemy->query_pronoun()) + " is " + how + ".\n", enemy);

    if (enemy->query_hp() <= 0)
    {
	enemy->do_die(this_object());
    }

    return 1; /*  Important! Should not have two attacks in a round. */
}

private string
query_creature_one()
{
  string *adjectives = ({
        "small", "delicate", "timid", "fuzzy"
                        });

  return adjectives[random(sizeof(adjectives))];
}

private string
query_creature_two()
{
  string *adjectives = ({
        "black", "gold", "white", "red", "tan"
                        });

  return adjectives[random(sizeof(adjectives))];
}

private string
query_creature_three()
{
  string *adjectives = ({
        "black", "gold", "blue"
                        });

  return adjectives[random(sizeof(adjectives))];
}

private string
query_creature_name()
{
  string *names = ({
        "rabbit", "squirrel", "bunny", "puppy", "kitten" 
                   });

  return names[random(sizeof(names))];
}
