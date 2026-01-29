// file name:        panther.c
// creator(s):       Lilith
// revision history: 
// purpose:          
// note:             
// bug(s):           
// to-do:            

#pragma strict_types

#include "../holm.h"
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/creature";

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2
#define A_RLEG  4
#define A_LLEG  8
#define A_TAIL  16

#define H_HEAD 0
#define H_BODY 1
#define H_LFQ  2
#define H_RHQ  4

void
create_creature()
{
    string size = ({ "tiny", "small", "fierce", "large", "huge" })[random(5)],
           tnt =  ({ "brown", "black", "white" })[random(3)];

    set_name("panther");
    add_name("cat");
    set_race_name("panther");
    set_adj(size);
    add_adj(tnt);
    set_short(size + " " + tnt + " panther");
    set_long("This panther has a " + tnt + " glossy, short-haired "+
	     "coat. She is " + size + " in size and packed with long, "+ 
	     "flowing muscles that seem to be in constant motion.\n"+
	     "Her eyes are glowing golden orbs.\n");
    set_gender(G_FEMALE);
/*              str, con, dex, int, wis, dis           */
    set_stats(({ 70,  90,  90,  70,  70, 70}));

    set_skill(SS_BLIND_COMBAT, 40);
    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_AWARENESS, 40);

    set_alignment(10);
    set_random_move(10, 1);

    add_prop(LIVE_O_ENEMY_CLING, 1);
    add_prop(NPC_I_NO_FEAR, 1); 
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_QUICKNESS, 120 + random(100));
    add_prop(LIVE_I_SEE_DARK, 40);
    add_prop(NPC_I_NO_LOOKS, 1);

    set_cact_time(3);
        add_cact("emote bares her fangs and hisses at you.");
        add_cact("emote growls in a deeply terrifying way.");
   
    set_act_time(5);
        add_act("emote basks in the light of the Source.");
        add_act("emote stares through you.");
        add_act("emote twitches her tail idly.");
        add_act("emote shrugs the muscles beneath her gleam"+
            "ing coat.");
        add_act("emote gazes about with serene golden eyes.");
        add_act("emote cleans her front paw, extending "+
            "prodigious claws.");        


    set_attack_unarmed(A_BITE,   15, 75,  W_IMPALE,   15, "jaws");
    set_attack_unarmed(A_LCLAW,  35, 40,  W_SLASH,    15, "left claw");
    set_attack_unarmed(A_RCLAW,  40, 35,  W_SLASH,    15, "right claw");
    set_attack_unarmed(A_RLEG,   40, 35,  W_BLUDGEON, 15, "right hind leg");
    set_attack_unarmed(A_LLEG,   40, 35,  W_BLUDGEON, 15, "left hind leg");    
    set_attack_unarmed(A_TAIL,   10, 30,  W_BLUDGEON, 15, "tail");

    set_hitloc_unarmed(H_HEAD, ({ 70 }), 10, "head");
    set_hitloc_unarmed(H_BODY, ({ 90 }), 50, "body");
    set_hitloc_unarmed(H_LFQ,  ({ 70 }), 20, "right foreleg");
    set_hitloc_unarmed(H_RHQ,  ({ 70 }), 20, "left hind-quarter");

}

public void
enter_env(object from, object to)
{
    if (from == 0 && to != 0)
    {
	set_restrain_path(JUNG);
	set_monster_home(file_name(to));
    }
}

void
react_meet(object tp)
{
    if (present(tp, environment(TO)))
	command("kill "+ tp->query_real_name());
}

void
init_living()
{
    ::init_living();

    if (interactive(TP) && 
        CAN_SEE(TO, TP) &&
        TP->query_average_stat() >= 30)
    {
	set_alarm(3.0, 0.0, &react_meet(TP));
    }
}

int
query_knight_prestige() { return 100; }

int cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
    if (aid == A_LCLAW)
    {
        tell_object(enemy, "The "+ short() +"'s left claw gleams "+
            "with the redness of your blood!\n");
    }
    if (aid == A_RCLAW)
    {
        tell_object(enemy, "You can see bits of your own flesh on "+
            short() +"'s right claw!\n");
    }
   return 0;
}
