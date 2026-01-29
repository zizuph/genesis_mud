/* EKL -ok */
inherit "/std/creature";
inherit "/std/act/action";
inherit "/std/combat/unarmed";
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <wa_types.h>
#include "/d/Emerald/defs.h"
 
#define W_OBJECTS "/d/Emerald/starninja/"
 
#define BRANCH1 0
#define BRANCH2 1
#define BRANCH3 2
#define BRANCH4 3
#define BRANCH5 4
#define BRANCH6 5
 
#define TRUNK      0
#define H_BRANCH1  1
#define H_BRANCH2  2
#define H_BRANCH3  3
#define H_BRANCH4  4
#define H_BRANCH5  5
#define H_BRANCH6  6
 
int times;
string *weapons = ({ });
 
string
query_long_desc()
{
   int i,a;
   string desc;
   string *is = ({ "is a","are" });
 
   desc = "";
   if( sizeof( weapons ) )
   {  if( sizeof( weapons ) > 1 ) a = 1; else a = 0;
      desc = "And there " + is[a] + " ";
      for( i = 0 ; i < sizeof( weapons ) ; i ++ )
      {    desc = desc + weapons[i];
           if( i != sizeof( weapons ) - 1 )
               if( i == sizeof( weapons ) - 2 ) desc = desc + " and ";
               else desc = desc + ", ";
      }
      desc = desc + " stuck in his bark.\n";
   }
   return "This looks like a simple tree, but when you " +
          "examine it closer, you notice that it is somewhat " +
          "sticky.\n" + desc;
 
}
 
 
void
create_creature()
{
    set_race_name( "tree" );
    set_name( "tree" );
    set_living_name( "sticky_tree" );
    set_short( "sticky tree" );
    set_long( "@@query_long_desc" );
 
    set_stats( ({ 50,20,60,90,90,50 }) );
 
    set_hp( query_max_hp() );
 
    add_prop( LIVE_I_NEVERKNOWN,1 );
 
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill( SS_DEFENCE,50 );
    set_skill( SS_UNARM_COMBAT,50 );
 
    set_attack_unarmed( BRANCH1,10,10,W_SLASH,17,"first branch" );
    set_attack_unarmed( BRANCH2,10,10,W_SLASH,17,"second branch" );
    set_attack_unarmed( BRANCH3,10,10,W_SLASH,17,"third branch" );
    set_attack_unarmed( BRANCH4,10,10,W_SLASH,17,"fourth branch" );
    set_attack_unarmed( BRANCH5,10,10,W_SLASH,16,"fifth branch" );
    set_attack_unarmed( BRANCH6,10,10,W_SLASH,16,"sixth branch" );
 
    set_hitloc_unarmed( TRUNK,({15,15,15,15}),40,"trunk" );
    set_hitloc_unarmed( H_BRANCH1,({10,10,10,10}),10,"first branch" );
    set_hitloc_unarmed( H_BRANCH2,({10,10,10,10}),10,"second branch" );
    set_hitloc_unarmed( H_BRANCH3,({10,10,10,10}),10,"third branch" );
    set_hitloc_unarmed( H_BRANCH4,({10,10,10,10}),10,"fourth branch" );
    set_hitloc_unarmed( H_BRANCH5,({10,10,10,10}),10,"fifth branch" );
    set_hitloc_unarmed( H_BRANCH6,({10,10,10,10}),10,"sixth branch" );
 
    set_alignment( 500 );
}
 
static void
tell_watcher(string str, object me, object enemy)
{
    object *ob;
    int i;
 
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}
 
mixed
hit_me( int wc_pen,int dt,object att,int att_id )
{
    object weapon;
    int *ret;
 
 
    ret = ::hit_me( wc_pen,dt,att,att_id);
    weapon = att->query_weapon( att_id );
    if( weapon && !random( 1 ) )
    {   weapons += ({ weapon->query_short() });
        TO->set_long( "@@query_long_desc" );
        weapon->move( TO );
        att->catch_msg( "Your weapon stucks in the tree!.\n" );
        tell_watcher( QCTNAME( att ) + "s weapon stucks in " +
               "in the tree!\n",TO,att );
    }
    return ret;
}
 
