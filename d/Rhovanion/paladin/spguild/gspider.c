inherit "/std/creature";
inherit "/std/act/action";
inherit "/std/combat/unarmed";
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <wa_types.h>
#include "/d/Rhovanion/defs.h"
#include <spguild.h>
 
#define LEG1 0
#define LEG2 1
#define LEG3 2
#define LEG4 3
#define LEG5 4
#define LEG6 5
#define BODY 6
#define HEAD 7
 
#define H_LEG1 0
#define H_LEG2 1
#define H_LEG3 2
#define H_LEG4 3
#define H_LEG5 4
#define H_LEG6 5
#define H_BODY 6
#define H_HEAD 7
 
 
void
create_creature()
{
    set_race_name( "spider" );
    set_name( "spider" );
    add_name( "spider" );
    set_short( "huge black spider" );
    set_long( "The huge black spider, who seems very strong.\n" );
 
    set_stats( ({ 90,90,90,90,90,50 }) );
 
    set_hp( query_max_hp() );
 
    add_prop( LIVE_I_NEVERKNOWN,1 );
    add_prop( CONT_I_VOLUME,50000 );
    add_prop( CONT_I_WEIGHT,50000 );
    add_prop( CONT_I_MAX_VOLUME,100000 );
    add_prop( CONT_I_MAX_WEIGHT,100000 );
 
    set_skill( SS_DEFENCE,70 );
    set_skill( SS_UNARM_COMBAT,70 );
 
    set_attack_unarmed( LEG1,25,25,W_BLUDGEON|W_IMPALE,13,"front right leg"     );
    set_attack_unarmed( LEG2,25,25,W_BLUDGEON|W_IMPALE,13,"front left leg" )    ;
    set_attack_unarmed( LEG3,25,25,W_BLUDGEON|W_IMPALE,13,"middle right leg"     );
    set_attack_unarmed( LEG4,25,25,W_BLUDGEON|W_IMPALE,13,"middle left leg"     );
    set_attack_unarmed( LEG5,25,25,W_BLUDGEON|W_IMPALE,13,"rear right leg" )    ;
    set_attack_unarmed( LEG6,25,25,W_BLUDGEON|W_IMPALE,13,"rear left leg" );
    set_attack_unarmed( HEAD,35,35,W_BLUDGEON,22,"head" );
 
    set_hitloc_unarmed( H_LEG1,({20,20,20,20}),10,"front right leg" );
    set_hitloc_unarmed( H_LEG2,({20,20,20,20}),10,"front left leg" );
    set_hitloc_unarmed( H_LEG3,({20,20,20,20}),10,"middle right leg" );
    set_hitloc_unarmed( H_LEG4,({20,20,20,20}),10,"middle left leg" );
    set_hitloc_unarmed( H_LEG5,({20,20,20,20}),10,"back right leg" );
    set_hitloc_unarmed( H_LEG6,({20,20,20,20}),10,"back left leg" );
    set_hitloc_unarmed( H_BODY,({30,30,30,30}),25,"body" );
    set_hitloc_unarmed( H_HEAD,({25,25,25,25}),15,"head" );
 
    set_alignment( 0 );
}
 
