/*   undead_std.c
 *
 *  A standard used for undead creatures in
 *  the tunnel system.
 *
 * Baldacin@Genesis, Aug 2003
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <wa_types.h>
#include <ss_types.h>
#include "/d/Genesis/gems/gem.h"
#include "../defs.h"

#define A_CLAWS 0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1
#define H_ARMS 2
#define H_LEGS 3

void
create_creature()
{
    object gem;

    set_name("soulless being");
    add_name("undead");

    if (random(5))
    {
        gem=RANDOM_GEM_BY_RARITY(GEM_SLIGHTLY_COMMON);
        gem->move(TO);
    }

    add_prop(LIVE_I_NO_CORPSE,1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    set_alignment(-(350 + random(200)));
    set_gender(G_NEUTER);

}

void 
setup_undead(string race, int level)
{
    int stat   = (level / 2) + random(level / 3) + random(level / 3);
    int skill  = (level / 2) + random(level / 3);
    int undead = (level / 2) + random(level / 3);
    string *adj1 = ({"ugly","evil","rancid","wicked", "rotting", "repulsive", "loathsome"});
    string *adj2 = ({"ethereal","unearthly", "unholy", "vile", "undead"});
    
    set_stats(({ (stat + random(5)),     
                 ((stat + 10) + random(5)),     
                 ((stat + 10) + random(5)),     
                 ((stat - 15) + random(5)),     
                 ((stat - 15) + random(5)),     
                 (stat + random(5))}));
    heal_hp(query_max_hp());

    set_skill(SS_UNARM_COMBAT, skill + random(10));
    set_skill(SS_BLIND_COMBAT, skill + random(10));
    set_skill(SS_WEP_SWORD,    skill + random(10));
    set_skill(SS_DEFENCE,      skill + random(10));
    set_skill(SS_AWARENESS,    skill);
    
    add_prop(LIVE_I_UNDEAD, undead);
                
    set_attack_unarmed(A_CLAWS, 35, 40, W_SLASH, 30, "claws");
    set_attack_unarmed(A_LCLAW, 25, 25, W_SLASH, 35, "left claw");
    set_attack_unarmed(A_RCLAW, 25, 25, W_SLASH, 35, "right claw");
    
    set_hitloc_unarmed(H_HEAD, ({2,2,2,2}), 20, "head");
    set_hitloc_unarmed(H_BODY, ({7,7,7,7}), 40, "body");
    set_hitloc_unarmed(H_ARMS, ({3,3,3,3}), 20, "arms");
    set_hitloc_unarmed(H_LEGS, ({4,4,4,4}), 20, "legs");
    
    set_adj(RONE(adj1));
    add_adj(RONE(adj2));
    set_race_name(race);
    set_long("This "+ TO->short()+ " seems to be some kind "+
      "of spawn of death! You begin to wonder what brought them "+
      "here. And perhaps even more interesting, WHO brought "+
      "them here.\n");
}