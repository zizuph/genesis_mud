/*
 * horse for imladris stables
 * By finwe Sept 1998
 */
 
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
 
#include "/d/Shire/sys/defs.h"
#include "/sys/ss_types.h"
#include <wa_types.h>
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
 
create_creature()
{
 
    int x, y;
    string *descr, *color;
 
    descr = (({ "strong", "mighty", "friendly", 
        "large", "powerful", "beautiful", "majestic"}));
    color = (({"white", "brown", "roan", "pied"}));
 
    x = random(sizeof(descr));
    y = random(sizeof(color));
 
    set_name("horse");
    add_adj(descr[x]);
    add_adj(color[y]);
 
    set_alignment(200 + random(50));
    set_race_name("horse"); 
    set_long("The horse looks glorious. Its lustrous coat seems " +
        "to glimmer in the light and looks very soft. A thick " +
        "mane falls gracefully down the back of the animal's " +
        "neck. The horse looks very healthy and well " +
        "excercised. The eyes of the horse look intelligent and " +
        "inquisitive as the animal watches you.\n");
 
 
    add_prop(CONT_I_WEIGHT,87000);   /* 87  Kg */
    add_prop(CONT_I_HEIGHT,153);     /* 153 cm */

    set_m_in("trots in");
    set_m_out("gallops");
 
    set_stats(({ 14, 15, 12, 18, 12, 40}));
    set_skill(SS_UNARM_COMBAT,30);
    set_skill(SS_DEFENCE,60);
    set_skill(SS_SNEAK, 100);
    set_skill(SS_HIDE, 100);
 
    set_attack_unarmed( 0, 10, 20, W_IMPALE, 50, "teeth");
    set_attack_unarmed( 1, 20, 10, W_BLUDGEON, 25, "left hoof");
    set_attack_unarmed( 2, 20, 10, W_BLUDGEON, 25, "right hoof");
 
    set_hitloc_unarmed( 0, ({ 30, 25, 25, 5 }), 20, "head");
    set_hitloc_unarmed( 1, ({ 15, 23, 20, 5 }), 50, "body");
    set_hitloc_unarmed( 2, ({ 40, 12, 10, 5 }), 30, "legs");
 
    set_hp(500); /* Heal fully */
 
    set_act_time(6);
    add_act("emote nuzzles his nose up to you.");
    add_act("emote whinnies happily at you.");
    add_act("emote tosses his head back in the air.");
    add_act("emote neighs loudly.");
    add_act("emote chews on some food.");
    add_act("emote gazes thoughtfully at you.");
    add_act("emote paws the ground.");
    add_act("emote shakes his haunches and shakes his tail.");
    add_act("emote swishes his tail across his haunches.");
    add_act("emote shakes his mighty head back and forth a " +
        "couple of times.");
    add_act("emote prances about the stables a bit.");
   
    set_cact_time(1);
 
    add_prop(LIVE_I_NEVERKNOWN, 1); /* You never get to meet him */
}

query_knight_prestige() { return(-25); }
