/*
 * Giant DragonFly.
 *                Napture.
 */

inherit "/std/monster";
inherit "/std/combat/unarmed"; /* standard unarmed routines */
inherit "/std/act/domove";     /* creature to move */
inherit "/std/act/action";     /* creature to act */

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>

#include <my.h>

/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE 0
#define A_LEG  1

#define H_HEAD 0
#define H_BODY 1
#define L_WING 2
#define R_WING 3

create_creature()
{
    set_name("draggy");
    set_race_name("dragonfly");
    set_short("giant dragonfly");
    add_name("fly");
    set_adj(({"giant"}));
    set_long("This dragonfly is hovering with a slight buzzing " +
        "sound, beating its wings very fast. It must have been attracted " +
        "to a sweet smell nearby.\n");

    set_gender(G_NEUTER);
    add_prop(LIVE_I_NEVERKNOWN);
    
    /* str, dex, con, int, wis, dis */
    set_stats(({ 10, 250, 8, 1, 1, 20}));

    set_hp(query_max_hp());

    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_HUNTING, 50);
    set_skill(SS_TRACKING, 50);
    set_skill(SS_AWARENESS, 58);
    
                        /* Hit, pen, damage type, %use, desc */
    set_attack_unarmed(A_BITE,  15, 10, W_IMPALE, 75, "bite");
    set_attack_unarmed(A_LEG ,  15,  5, W_SLASH,  25, "legs");
    
                        /* Impale, slash, bludgeon, %hit, desc */
    set_hitloc_unarmed(H_HEAD, ({  5, 10, 12 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({  5, 15, 15 }), 36, "body");
    set_hitloc_unarmed(L_WING, ({ 10,  5, 10 }), 22, "left wing");
    set_hitloc_unarmed(R_WING, ({ 10,  5, 10 }), 22, "right wing");

  /* object (path), name (one word), nitems, vbfc to call ("" or 0 = okay), 
              remains left after total decay, has to be cut (not tear) */
    add_leftover("/std/leftover", "wing", 2, 0, 0, 0);

#if 0
    set_follow("napture");
#endif
    trig_new("%s 'Napture' %s", "trig_telep");
}

public void
do_die(object killer)
{
    if (query_hp() > 0)  /* Shouldn't be here anyway */
        return;

    tell_room(environment(this_object()), "As the " + short() + " dies, it " +
              "slumps to the ground.\n");
    ::do_die(killer);
    return;    
}

trig_telep(string s1, string s2)
{
    set_alarm(1.0, 0.0, "do_telep", s1, s2);
}

do_telep(string s1, string s2)
{
    object *o;

    o = all_inventory(environment(this_object()));
    if (member_array(find_player("napture"), o) == -1)
        this_object()->move_living("flying", environment(find_player("napture")));
}
