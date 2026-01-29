
/* The two-handed sword 'Honour' 
 * By Elmore. 
 * Type: Sword. 
 * Info: 20% chance to give double damage against an evil enemy.
 * 
 */ 

inherit "/std/weapon"; 
inherit "/lib/keep"; 

#include <wa_types.h> 
#include <stdproperties.h> 
#include <formulas.h> 
#include <macros.h> 
#include <ss_types.h> 
#include <options.h> 
#include <filter_funs.h> 
#include "/d/Ansalon/common/defs.h" 

#define HIT 49 
#define PEN 43 

create_weapon() 
{ 
    set_name("sword"); 
    add_name("claymore"); 
    add_name("honour"); 
    set_adj("shimmering"); 
    add_adj("white-steel");
    set_short("shimmering white-steel claymore"); 
    set_long("Forged from an unknown white steel this massive "+ 
             "claymore measures nearly 60 inches in length. "+ 
             "the downsloping cross-hilt is constructed out "+ 
             "of wood and brass and gives the weapon a very "+ 
             "distinctive look.\n"+ 
             "A soft white glow surrounds the blade.\n"); 
    set_hit(HIT); 
    set_pen(PEN); 
    set_wt(W_SWORD); 
    set_dt(W_SLASH); 
    set_hands(W_BOTH); 
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN) + random(80)); 
    add_prop(OBJ_I_VOLUME, 7500); 
    add_prop(OBJ_I_WEIGHT, 7000); 
    set_wf(this_object()); 

    add_prop(OBJ_S_WIZINFO, "This holy weapon have a 20% chance "+ 
                            "to deliver double damage against an enemy "+ 
                            "if he is evil.\n"); 

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1); 
    add_prop(MAGIC_AM_MAGIC,({ 10, "enchantment"})); 
    add_prop(MAGIC_AM_ID_INFO, 
      ({"The weapon is enchanted.\n", 5, 
        "Enchanted by a priest of Paladine, this weapon will strike at evil beings "+ 
        "with amazing fury.\n", 30})); 
} 

public mixed 
wield(object what) 
{ 
    if (this_player()->query_alignment() < 0) 
    { 
        wielder->catch_msg("The "+short()+ "senses your dark soul and refuses to be wielded "+ 
                           "by you.\n"); 
        wielder->tell_watcher(QCTNAME(wielder)+ " fails to wield " +HIS(wielder)+ " "+ 
                 short()+ ".\n"); 
        return ""; 
    } 
    return 0;
} 

public mixed 
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam) 
{ 
  if(random(5) == 0) 
  { 
    if(phurt > 0) 
    { 
      if (enemy->query_aligment() <= -500) 
      { 

        write("Your "+short()+" glows brightly!\n"); 
        dam = dam * 2; 
      } 
    } 
  } 
  return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam); 
} 

