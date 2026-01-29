/*
 * An imbuementtehpain/shadow.
 *
 * Nerull 14/3/09.
 */


#include <stdproperties.h>
#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <filter_funs.h>
#include "../../defs.h"


inherit "/std/shadow";


// We add something additional to the regular longdesc of the item.
string
long()
{
		return shadow_who->long()+"Its engraved with an intricate " +
		"red-glowing rune.\n";
}


// Here we add the actual effect we want stowed on the item.
void
make_imb2_effect()
{

    shadow_who->set_hit(50);
    shadow_who->set_pen(50);

		return;
}


// Combat special for weapons.
void 
hurt_enemy(object enemy, string hit_loc)
{
	  object user = environment(shadow_who);	  
	  enemy = user->query_enemy();
	
	  string effect, how;
    int dam = 0, pen, res;
    mixed tehpain;
   	
	  if (!objectp(enemy))
    {
        return;
    }
        
		pen = random(70);
    res = enemy->query_magic_res(MAGIC_I_RES_FIRE);
    
    pen -= pen* res/ 100;
     
    tehpain = enemy->hit_me(400, MAGIC_DT, user, -1);


    if (pointerp(tehpain))
    {
        dam = tehpain[0];
    }
    
    switch (pen)
    {
        case  0..8:        
        effect = "shoots a tiny bolt of fire at";
        break;
        case  9..20:        
        effect = "shoots two tiny bolts of fire at";
        break;
        case 21..40:        
        effect = "shoots a massive bolt of fire at";
        break;
        case 41..55:       
        effect = "shoots two massive bolts of fire at";
        break;
        default:        
        effect = "shoots a huge spear of fire at";
        break;
    }

    switch (dam)
    {
        case  -1..0:
        how = "unharmed";
        break;
        case   1..9:
        how = "slightly hurt";
        break;
        case  10..20:
        how = "somewhat hurt";
        break;
        case 21..30:
        how = "hurt";
        break;
        case 31..50:
        how = "rather hurt";
        break;
        case 51..70:
        how = "very hurt";
        break;
        default:
        how = "badly hurt";
        break;
    }
    
    
    user->catch_msg("The red-glowing intricate rune on your "+
    shadow_who->short() + " " + effect + " the " + hit_loc +
    " of " +QTNAME(enemy) + ".\n" + capitalize(HE(enemy)) +
    " looks " + how + " by the effects.\n");
      
    
    enemy->catch_msg("The red-glowing intricate rune on " +
    QPNAME(user) + "'s  " + shadow_who->short() + " " +effect+
    " your " + hit_loc + ".\n"+
    "You are " + how + " by the effects.\n");
    
    
    user->tell_watcher("The red-glowing intricate rune on "+
    QPNAME(user) + "'s " + shadow_who->short() + " " + effect+
    " the " + hit_loc + " of " + QTNAME(enemy) + ".\n" +
    "looks " + how + " by the effects.\n",enemy);
  
      
    if (enemy->query_hp() <= 0)
    {
        user->catch_msg(QCTNAME(enemy)+ " gasps last breath as " +
        "the effects of Orodruin consume.\n" );
        
        enemy->catch_msg("You gasp you last breath as the effects of "+
            "Orodruin consume your body.\n" );
            
        user->tell_watcher(QCTNAME(enemy)+ " gasps last breath as " +
        "the effects of Orodruin consume.\n");
         
        enemy->do_die(user);
       
    }

}

void
wield(object ob)
{
}

void
unwield(object ob)
{
}


public varargs int did_hit( int aid, string hdesc, int phurt, object enemy,
int dt, int phit, int dam )
{
    int tehpain =
    shadow_who->did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if (!objectp(enemy))
    {
        return (tehpain);
    }
       
    if (phurt > 0)
    {
        set_alarm(0.0, 0.0, &hurt_enemy(enemy, hdesc));
    }
    
    return (tehpain);
}

// Simple check to see if the shadow is present in the item.
int
query_imb2_shadow()
{
		return 1;
}


// Initiation of the shadow on the item.
void
init_imb2_shadow()
{   
		shadow_who->add_prop(I_AM_IMBUED2, 1);
    shadow_who->add_prop(MAGIC_AM_MAGIC,({ 20, "enchantment" }));    
    shadow_who->add_prop(MAGIC_AM_ID_INFO,({ "The "+
    this_object()->short()+" has an engravement that is magical.\n",1,
              "This weapon do additional firedamage when it " +
              "hits.\n",55}));
              
    make_imb2_effect();
}