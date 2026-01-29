/* Name: Crystal axe.
 * Stats: 40/50.
 * Hands: Left-handed.
 * Abilities: Will change it's description after what alignment
 *            the wielder has. Can't be wielded by dwarves.
 * By: Elmore, July 2000.
 * Changes:
 * 	  - added mana-drain (10 points) as balacing thing
 * 	    Torqual, Jul 2002
 *
 * Navarre: June 25th 2006:
 * The axe has from the beginning been designed to be dislike
 * dwarves, and most dwarves wasn't supposed to be able to wield
 * the axe. Since it was created, players have grown much bigger
 * than expected, due to changes in the game.
 * Instead of increasing the requirement for a dwarf to wield it
 * the effect for a dwarf using it was lowered.
 *
 * This was done while fixing the bug of the axe being able to 
 * keep hitting and keep healing players while they sheathed
 * the axe to the PKC holster and used a different weapon.
 *
 * Navarre July 3rd, Fixed typo "heals" versus "heal"
 * Navarre July 7th, Fixed typo, it had: his's, instead of his.
 * Navarre April 16th, Changed to use new light constants.
 * Navarre September 9th 2009, Changed to right handed, added cap,
 *                             increased mana cost, added mana check,
                               added stat average check for special.
 *                             All changed based on request from AoB!
 *
 * Arman January 15th 2020, Added code so breaks when item_expiration.c
                            called.
 */
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <options.h>
#include <filter_funs.h>
#include <const.h>

int type = 0;   //The type of description used. 0 = Neutral, 1 = Good, 2 = Evil.

void
create_weapon()
{
    mixed *arr;
    int n;
    
    set_name("axe");
    add_adj("crystal");
    set_adj("flaming");
    set_short("flaming crystal axe");
    set_hit(40);
    set_pen(50);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_RIGHT);
    add_prop(OBJ_I_VALUE, 9000); 
    add_prop(OBJ_I_VOLUME, 5200);
    add_prop(OBJ_I_WEIGHT, 5120); 
    add_prop(OBJ_I_LIGHT,LIGHT_PASSIVE_RARE);
   
    set_long("The "+ short() +" is a very large axe made out "+
             "of the purest crystal. The blade itself looks "+
             "almost as clear as glass, and as your hand "+
             "glides over the blade you can feel some "+
             "words or runes carved into it. The shaft is "+
             "likewise constructed out of the same material, giving "+
             "the impression that the entire weapon has been "+
             "made out of one solid block of crystal. Around "+
             "the hilt some soft leather has been wrapped to "+
             "protect the wielder and give a better grip "+
             "around the axe. A bright reddish flame surrounds "+
             "the blade.\n");

   add_item(({"words", "runes"}),"The runes are almost "+
             "invisible, you can only feel them.\n");

   set_likely_dull(1);
   set_likely_corr(1);
   set_likely_break(1);
   set_wf(this_object()); 
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(MAGIC_AM_MAGIC, ({70, "enchantment"}));
   add_prop(MAGIC_AM_ID_INFO, ({"This weapon is enchanted.\n", 10,
         "This weapon is a lost artifact "+
         "from Ergoth. Forged by a young sorcerer as his apprentice "+
         "project, this weapon became far more powerful "+
         "then he could ever imagine. One of the "+
         "enchantments that the sorcerer used, backfired "+
         "and killed him instantly. This made the "+
         "weapon extremely lethal, giving it an increased "+
         "penetration. After the creation of this weapon, "+
         "thieves entered the sorcerers home and "+
         "stole the weapon. Lost for centuries it seems "+
         "to appear sometimes, only to be lost again.\n", 20,
         "This weapon despises dwarves and will "+
         "attempt to refuse anyone trying to wield it.\n", 45}));

    add_prop(OBJ_S_WIZINFO, "This weapon is a lost artifact "+
         "from Ergoth. Forged by a young sorcerer as his apprentice "+
         "project, this weapon became far more powerful "+
         "then he could ever imagine. One of the "+
         "enchantments that the sorcerer used, backfired "+
         "and killed him instantly. This made the "+
         "weapon extremely lethal, giving it an increased "+
         "penetration. After the creation of this weapon "+
         "some thieves entered the sorcerers home and "+
         "stole it. Lost for centuries this weapon seems "+
         "to appear sometimes, only to be lost again. "+
         "The weapon will change it's descriptions after "+
         "what alignment the wielder has. Forged by "+
         "elves this weapon despises dwarves and will "+
         "attempt to refuse anyone trying to wield it.\n");
}

/*
 * Function name: remove_broken
 * Description  : The weapon got broken so the player has to stop
 *                wielding it.
 * Arguments    : int silent - true if no message is to be genereated
 *                             about the fact that the weapon broke.
 */
varargs void
remove_broken(int silent = 0)
{
    if (calling_function() == "item_expiration_break") 
        ::remove_broken(silent);

    return;
}


/*
 * Function name: set_dull
 * Description:   Use this to increases the dull status on weapons.
 * Arguments:     cond - The new condition we want (can only be raised)
 * Returns:       1 if new condition accepted
 */
int
set_dull(int du)
{
    return 0;
}


mixed
unwield(object what)
{
    return 0;   
}

mixed
wield(object what)
{
    if (TP->query_race_name() == "dwarf" && TP->query_stat(5) < 135)
	    return "The axe refuses to be wielded by you!\n";

    if (TP->query_skill(2) < 75)
	    return "The axe refuses to be wielded by you!\n";

    if ((TP->query_alignment() >= -699) && (TP->query_alignment() <= 699))
    {
        set_long("The flaming crystal axe is a very large axe made out "+
                 "of the purest crystal. The blade itself looks "+
                 "almost as clear as glass, and as your hand "+
                 "glides over the blade you can feel some "+
                 "words or runes carved into it. The shaft is "+
                 "likewise constructed out of the same material, giving "+
                 "the impression that the entire weapon has been "+
                 "made out of one solid block of crystal. Around "+
                 "the hilt some soft leather has been wrapped to "+
                 "protect the wielder and give a better grip "+
                 "around the axe. A bright reddish flame surrounds "+
                 "the blade.\n");

        set_short("flaming crystal axe");
        add_adj("flaming");
        add_prop(OBJ_I_LIGHT,LIGHT_PASSIVE_RARE);
        if (type == 0)
        {
            wielder->catch_msg("You wrap your hand around the "+
                               "soft leather on the handle of the "+
                               short()+". You feel a surge through "+
                               "your body as the weapon searches "+
                               "your soul.\n");
        }
        if (type == 1)
        {
            remove_adj("holy");
            wielder->catch_msg("You wrap your hand around the "+
                               "soft leather on the handle of the "+
                               short()+". You feel a surge through "+
                               "your body as the weapon searches "+
                               "your soul.\n");
            wielder->catch_msg("The bright white light surrounding the "+
                               short()+ " suddenly vanishes! A reddish "+
                               "flame begins to pulsate from the blade.\n");
        }
        if (type == 2)
        {
            remove_adj("unholy");
            wielder->catch_msg("You wrap your hand around the "+
                               "soft leather on the handle of the "+
                               short()+". You feel a surge through "+
                               "your body as the weapon searches "+
                               "your soul.\n");
            wielder->catch_msg("The evil aura surrounding the "+
                               short()+ " suddenly vanishes! A reddish "+
                               "flame begins to pulsate from the blade.\n");
        }
    wielder->update_weapon(TO);
    type = 0;
    }

    if (TP->query_alignment() >= 700)
    {
        set_long("The holy crystal axe is a very large axe made out "+
                 "of the purest crystal. The blade itself looks "+
                 "almost as clear as glass, and as your hand "+
                 "glides over the blade you can feel some "+
                 "words or runes carved into it. The shaft is "+
                 "likewise constructed out of the same material, giving "+
                 "the impression that the entire weapon has been "+
                 "made out of one solid block of crystal. Around "+
                 "the hilt some soft leather has been wrapped to "+
                 "protect the wielder and give a better grip "+
                 "around the axe. As you hold the weapon in the "+
                 "air you notice a bright white light surrounding "+
                 "the blade.\n");

        set_short("holy crystal axe");
        add_adj("holy");
        add_prop(OBJ_I_LIGHT, LIGHT_PASSIVE_RARE);
        if (type == 1)
        {
            wielder->catch_msg("You wrap your hand around the "+
                               "soft leather on the handle of the "+
                               short()+". You feel a surge through "+
                               "your body as the weapon searches "+
                               "your soul.\n");
        }
        if (type == 0)
        {
            remove_adj("flaming");
            wielder->catch_msg("You wrap your hand around the "+
                               "soft leather on the handle of the "+
                               short()+". You feel a surge through "+
                               "your body as the weapon searches "+
                               "your soul.\n");
            wielder->catch_msg("The reddish flame surrounding the "+
                               short()+ " suddenly vanishes! A bright "+
                               "white light begins to glow from the blade.\n");
        }
        if (type == 2)
        {
            remove_adj("unholy");
            wielder->catch_msg("You wrap your hand around the "+
                               "soft leather on the handle of the "+
                               short()+". You feel a surge through "+
                               "your body as the weapon searches "+
                               "your soul.\n");
            wielder->catch_msg("The evil aura surrounding the "+
                               short()+ " suddenly vanishes! A bright "+
                               "white light begins to glow from the blade.\n");
        }
    wielder->update_weapon(TO);
    type = 1;
    }

    if (TP->query_alignment() <= -700)
    {
        set_long("The unholy crystal axe is a very large axe made out "+
                 "of the purest crystal. The blade itself looks "+
                 "almost as clear as glass, and as your hand "+
                 "glides over the blade you can feel some "+
                 "words or runes carved into it. The shaft is "+
                 "likewise constructed out of the same material, giving "+
                 "the impression that the entire weapon has been "+
                 "made out of one solid block of crystal. Around "+
                 "the hilt some soft leather has been wrapped to "+
                 "protect the wielder and give a better grip "+
                 "around the axe. As you hold the weapon in the "+
                 "air you notice an evil aura surrounding the blade.\n");

        set_short("unholy crystal axe");
        add_adj("unholy");
        remove_prop(OBJ_I_LIGHT);
        if (type == 2)
        {
            wielder->catch_msg("You wrap your hand around the "+
                               "soft leather on the handle of the "+
                               short()+". You feel a surge through "+
                               "your body as the weapon searches "+
                               "your soul.\n");
        }
        if (type == 0)
        {
            remove_adj("flaming");
            wielder->catch_msg("You wrap your hand around the "+
                               "soft leather on the handle of the "+
                               short()+". You feel a surge through "+
                               "your body as the weapon searches "+
                               "your soul.\n");
            wielder->catch_msg("The reddish flame surrounding the "+
                               short()+ " suddenly vanishes! An evil "+
                               "aura begins to flow from the blade.\n");
        }
        if (type == 1)
        {
            remove_adj("holy");
            wielder->catch_msg("You wrap your hand around the "+
                               "soft leather on the handle of the "+
                               short()+". You feel a surge through "+
                               "your body as the weapon searches "+
                               "your soul.\n");
            wielder->catch_msg("The bright white light surrounding the "+
                               short()+ " suddenly vanishes! An evil "+
                               "aura begins to flow from the blade.\n");
        }
    wielder->update_weapon(TO);
    type = 2;
    }
    return 1;
}



public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    string dam_descr;
    if(!(this_object()->query_wielded()==environment(this_object())))
    {
      return 0;
    }

    int mana_cost = 20;
    int special_cap = 300;

    if(wielder->query_mana() >= mana_cost &&
       enemy->query_average_stat() > 50)
    {
      if (type == 0)
      {
	if(!random(5))
	{
	  if(phurt > 0)
	  {
	    if(wielder->query_race_name() == "dwarf")
	    {
	      dam = dam + ((dam/2)+5);
	    }
	    else
	    {
	      dam = dam + ((3*(dam/2)) + 10);
	    }
	    switch(dam)
	    {
	      case 0..125:
	        dam_descr = "burns ";
	        break;
	      
	      case 126..200:
		dam_descr = "ignites ";
		break;

	      default:
		dam_descr = "engulfes ";
		break;
	    }

	    wielder->catch_msg(QCTNAME(enemy) + " screams in pain " +
			       "as your "+ short() +" emits a flame that " + dam_descr
			       + POSSESSIVE(enemy) + " " + hdesc + ".\n");
	    enemy->catch_msg("You scream in pain, as " +
			     QTNAME(wielder)
			     + "'s " + short() + " emits a flame that "+
			     dam_descr + " your " + hdesc + ".\n");
	    wielder->tell_watcher(QCTNAME(enemy) + " screams in pain as "
				  + QTNAME(wielder) + "'s " + short() + " emits a flame that "+
				  dam_descr + POSSESSIVE(enemy) + " " + hdesc + ".\n", enemy);
	    
	    enemy->heal_hp(-MIN(dam, special_cap));
	    wielder->add_mana(-mana_cost); 
	  }
	}
      }
      if (type == 1)
      {
	if(!random(5))
	{
	  if(phurt > 0)
	  {
	    if(wielder->query_race_name() == "dwarf")
	    {
	      dam = dam+((dam/3)+5);
	    }
	    else
	    {
	      dam = dam + (3*(dam/3) + 10);
	    }
	    wielder->catch_msg("Your " +short()+ " glows with a "+
			       "silvery light, as the wounds on your " +
			       hdesc + " heal.\n");
	    enemy->catch_msg(QCTNAME(wielder)+ " looks healthier, as " +
			     HIS(wielder) + " " +short()+ " glows with a silvery light. "+
			     "Suddenly the wounds on "+QCTNAME(wielder)+"'s "+
			     hdesc + " begins to heal!\n");
	    wielder->tell_watcher(QCTNAME(wielder)+ " looks healthier, as " +
				  HIS(wielder) + " " +short()+ " glows with a silvery light. "+
				  "Suddenly the wounds on "+QTNAME(wielder)+"'s "+
				  hdesc + " begins to heal!\n", enemy);
	    
	    wielder->heal_hp(MIN(dam, special_cap));
	    wielder->add_mana(-mana_cost);
	  }
	}
      }
      if (type == 2)
      {
	if(!random(5))
	{
	  if(phurt > 0)
	  {
	    if(wielder->query_race_name() == "dwarf")
	    {
	      dam = dam +((dam/4)+5);  
	    }
	    else
	    {
	      dam = dam + ((3* dam/4) + 10);
	    }
	    wielder->catch_msg("Your "+short()+ " sends out a bolt of "+
			       "black energy. The bolt strikes " +QTNAME(enemy) + "'s " +
			       hdesc + ".\nYou feel healthier!\n");
	    enemy->catch_msg("The " +short()+ " wielded by "+
			     QCTNAME(wielder)+ "sends out a bolt of black energy. The "+
			     "bolt hits your " + hdesc + ".\nYou feel drained!\n");
	    wielder->tell_watcher("The "+short()+ " wielded by "+
				  QCTNAME(wielder) + " sends out a bolt of black energy that "+
				  "hits "+ HIS(enemy) +" " + hdesc + ".\n", enemy);
	    
	    enemy->heal_hp(-MIN(dam, special_cap/2));
	    wielder->heal_hp(MIN(dam, special_cap/2));
	    wielder->add_mana(-mana_cost);
	  }
	}
      }
    }
    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}
