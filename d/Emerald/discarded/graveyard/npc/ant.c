 
/* graveyard/npc/ant.c is cloned by various files in graveyard/ */
 
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
 
#include <wa_types.h>
 
#include "/d/Emerald/defs.h"
 
#define A_BITE 0
 
#define H_HEAD 0
#define H_BODY 1
 
create_creature()
{
    set_name("ant");
    set_race_name("ant");
    set_short("giant ant");
    set_adj("giant");
    set_long( "A giant black ant with vicious looking mandibles "+
        "that drip a disgusting green liquid. Its body is covered by overlapping "+
        "black plates that reflect your light.\n" );
 
    set_stats(({40,35,40,20,20,35}));
    set_hp(10000);
 
    set_skill(SS_DEFENCE, 30);
 
    set_attack_unarmed(A_BITE,20,25,W_BLUDGEON,100,"mandibles");
 
    set_hitloc_unarmed(H_HEAD,15,20,"head");
    set_hitloc_unarmed(H_BODY,25,80,"body");
 
    set_gender(G_NEUTER);
    add_prop(LIVE_I_NEVERKNOWN,1);
}
