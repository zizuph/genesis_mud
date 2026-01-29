/* 7-headed Hydra
** Creature of mystery and myth in Argos, this is the baddest dude in the
** valley. He even has his own cult of human worshippers, who appease his
** appetite for praise, worship and occassionally human flesh.
** He has seven heads (duh) and two pair of legs with enormous claws,
** though he doesn't move around much. His front claws are used for
** cutting small mammals, like giants, to ribbons, as he props his
** rotund, scaly body back on his hind legs. Though slow of foot, his
** dragon-like heads atop his snake-like necks are agile and quick
** killing machines. His long tail with large sharp spikes crush skulls
** like eggshells. He is capable of attacking any mortal in the
** room, not just the "primary" enemy, making "tanks" in a team much
** less effective.
*/
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
 
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "defs.h"
 
#define HIT       70
#define PEN       75
#define BODY_HC   30
#define BODY_AC   80
#define HEAD_HC    6
#define HEAD_AC   60
#define CLAW_HC   10
#define CLAW_AC   60
#define TAIL_HC   20
#define TAIL_AC   70
#define BELLY_HC  10
#define BELLY_AC  50
 
 
void create_creature() {
    /* general descriptions */
    set_name("thanatos");
    set_race_name("hydra");
    set_adj(({"deadly","seven-headed"}));
    set_short("deadly seven-headed hydra");
    set_long(
        "This enormous creature exudes an aura of death and doom. It has "+
        "seven dragon-like heads, each with horns spiraling in various forms "+
        "and saber-like teeth twisting out of its mouths. Each head writhes "+
        "at the end of a serpentine neck, some with glowing gemstones for "+
        "eyes. It has a massive body, armoured with rock-like black scales "+
        "with red patterns on its back, and smooth gray scales in its belly. "+
        "It's front legs are relatively long and thin "+
        "but house long, sharp claws used for slashing, while its back "+
        "legs rest on large, flat claws. It has a long tail which writhes "+
        "nervously likes its necks, large sharp spikes on its end. A foul "+
        "stench of sulfur and death surrounds it like a protective cloud.\n");
 
    /* stats and skills */
    set_stats(({220,220,220,150,150,100}));
    set_skill(SS_DEFENCE, 110);
    set_skill(SS_UNARM_COMBAT, 110);
    set_skill(SS_BLIND_COMBAT, 110);
    set_hp(query_max_hp());
 
    /* properties */
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE,1);
    add_prop(LIVE_I_SEE_DARK,1);
    add_prop(MAGIC_I_RES_POISON,50);
    add_prop(MAGIC_I_RES_FIRE,50);
    add_prop(MAGIC_AM_ID_INFO,
       "The creature is resistant to poisons and fire.\n");
 
    /* normal unarmed attacks - not sure any of these will ever be used, */
    /* since special_attack() always returns 1, but here just in case!   */
    set_attack_unarmed(0,HIT,PEN,W_SLASH, 33, "long front claws");
    set_attack_unarmed(1,HIT,PEN,W_BLUDGEON, 33, "writhing spiked tail");
    set_attack_unarmed(2,HIT,PEN,W_IMPALE, 33, "horns of one of its heads");
 
    /* hit locations */
    set_hitloc_unarmed(0, BODY_AC, BODY_HC,"black scaled body");
    set_hitloc_unarmed(1, HEAD_AC, HEAD_HC, "ruby-eyed head");
    set_hitloc_unarmed(2, HEAD_AC, HEAD_HC, "diamond-eyed head");
    set_hitloc_unarmed(3, HEAD_AC, HEAD_HC, "spiraled-horned head");
    set_hitloc_unarmed(4, HEAD_AC, HEAD_HC, "twisted-horned head");
    set_hitloc_unarmed(5, HEAD_AC, HEAD_HC, "spike-horned head");
    set_hitloc_unarmed(6, HEAD_AC, HEAD_HC, "long-fanged head");
    set_hitloc_unarmed(7, HEAD_AC, HEAD_HC, "emerald-eyed head");
    set_hitloc_unarmed(8, CLAW_AC, CLAW_HC, "front claws");
    set_hitloc_unarmed(9, TAIL_AC, TAIL_HC, "spiked tail");
    set_hitloc_unarmed(10,BELLY_AC,BELLY_HC,"gray scaled belly");
 
 
    /* actions */
    set_act_time(10);
    set_alignment(-500);
}
#include "hydrasp.h"
