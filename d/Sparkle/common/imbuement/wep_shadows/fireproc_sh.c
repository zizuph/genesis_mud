/*
 * An imbuement-shadow.
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

#define    HE(x)                x->query_pronoun()


inherit "/std/shadow";

int strenght;


// We add some fancy desc addon to the item
string
short()
{
		if (strenght == 1)
		{	
    		return "bizarre "+shadow_who->short();
    }
    
    if (strenght == 2)
		{	
    		return "weird "+shadow_who->short();
    }
    
    if (strenght == 3)
		{	
    		return "rare "+shadow_who->short();
    }
}

// We add something additional to the regular longdesc of the item.
string
long()
{	
		if (strenght == 1)
		{
				return shadow_who->long()+"You notice that it is emitting " +
				"a low-pitched ringing sound.\n";
		}
		
		if (strenght == 2)
		{
				return shadow_who->long()+"You notice that it is emitting " +
				"a dull ringing sound.\n";
		}
		
		if (strenght == 3)
		{
				return shadow_who->long()+"You notice that it is emitting " +
				"a high-pitched ringing sound.\n";
		}
}


// Here we add the actual effect we want stowed on the item.
void
make_imb_effect()
{
		
		return;
}


// Combat special for weapons.
void 
hurt_enemy(object enemy, string hit_loc = "body")
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


// Masking wield for more phat effects.
void
wield(object ob)
{
}


// Masking wield for phat effects.
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
query_imb_shadow_weaponproc()
{
		return 1;
}


// Initiation of the shadow on the item.
void
init_imb_shadow(int i)
{   
		
		strenght = i;
		
    shadow_who->add_prop(MAGIC_AM_MAGIC,({ 20, "enchantment" }));    
    shadow_who->add_prop(MAGIC_AM_ID_INFO,({ "The "+
    this_object()->short()+" has an engravement that is magical.\n",1,
              "This weapon do additional firedamage when it " +
              "hits.\n",55}));
              
    make_imb_effect();
}

