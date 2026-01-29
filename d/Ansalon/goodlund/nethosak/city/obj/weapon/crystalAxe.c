/* Name: Crystal axe.
 * Stats: 40/55.
 * Hands: Left-handed.
 * Abilities: Will change it's description after what alignment
 *            the wielder has. Can't be wielded by dwarves.
 * By: Elmore, July 2000.
 * Made into spell enhancers, Ckrik 2022/02/07
 */


#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <options.h>
#include <filter_funs.h>

int type = 0;   //The type of description used. 0 = Neutral, 1 = Good, 2 = Evil.

void
create_weapon()
{
    mixed *arr;
    int n;
    
    set_name("axe");
    set_adj("flaming");
    add_adj("mithril");
    set_short("flaming crystal axe");
    set_hit(40);
    set_pen(55);
    // This value will affect spell damage for spellcasters.
    set_magic_spellpower(48);
    set_spellpower_elements(({
        SS_ELEMENT_DEATH, SS_ELEMENT_LIFE, SS_ELEMENT_FIRE,
        SS_ELEMENT_EARTH
    }));
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_LEFT);
    add_prop(OBJ_I_VALUE, 9000); 
    add_prop(OBJ_I_VOLUME, 5200);
    add_prop(OBJ_I_WEIGHT, 5120); 
   
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

   set_likely_dull(0);
   set_wf(this_object()); 
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(MAGIC_AM_MAGIC, ({70, "enchantment"}));
   add_prop(MAGIC_AM_ID_INFO, ({"This weapon is a lost artifact "+
         "from Ergoth. Forged by a young sorcerer as his apprentice "+
         "project, this weapon became far more powerful "+
         "then he could ever imagine. One of the "+
         "enchantments that the sorcerer used, backfired "+
         "and killed him instantly. This made the "+
         "weapon extremely lethal, giving it an increased "+
         "penetration. After the creation of this weapon "+
         "some thieves entered the sorcerers home and "+
         "stole it. Lost for centuries this weapon seems "+
         "to appear sometimes, only to be lost again. Forged "+
         "by elves this weapon despises dwarves and will "+
         "refuse anyone trying to wield it.\n", 45}));

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
         "refuse anyone trying to wield it.\n");
}

mixed
wield(object what)
{
    if(TP->query_race_name() == "dwarf")
	return "The axe refuses to be wielded by you!\n";

    if ((TP->query_alignment() >= -449) && (TP->query_alignment() <= 449))
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
        if (type == 0)
        {
            wielder->catch_msg("You wrap your left hand around the "+
                               "soft leather on the handle of the "+
                               short()+". You feel a surge through "+
                               "your body as the weapon searches "+
                               "your soul.\n");
        }
        if (type == 1)
        {
            remove_adj("holy");
            wielder->catch_msg("You wrap your left hand around the "+
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
            wielder->catch_msg("You wrap your left hand around the "+
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

    if (TP->query_alignment() >= 450)
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
        if (type == 1)
        {
            wielder->catch_msg("You wrap your left hand around the "+
                               "soft leather on the handle of the "+
                               short()+". You feel a surge through "+
                               "your body as the weapon searches "+
                               "your soul.\n");
        }
        if (type == 0)
        {
            remove_adj("flaming");
            wielder->catch_msg("You wrap your left hand around the "+
                               "soft leather on the handle of the "+
                               short()+". You feel a surge through "+
                               "your body as the weapon searches "+
                               "your soul.\n");
            wielder->catch_msg("The reddish flame surrounding the "+
                               short()+ " suddenly vanishes! A bright "+
                               "white light begins to pulsate from the blade.\n");
        }
        if (type == 2)
        {
            remove_adj("unholy");
            wielder->catch_msg("You wrap your left hand around the "+
                               "soft leather on the handle of the "+
                               short()+". You feel a surge through "+
                               "your body as the weapon searches "+
                               "your soul.\n");
            wielder->catch_msg("The evil aura surrounding the "+
                               short()+ " suddenly vanishes! A bright "+
                               "white light begins to pulsate from the blade.\n");
        }
    wielder->update_weapon(TO);
    type = 1;
    }

    if (TP->query_alignment() <= -450)
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
                 "air you notice a evil aura surrounding the blade.\n");

        set_short("unholy crystal axe");
        add_adj("unholy");
        if (type == 2)
        {
            wielder->catch_msg("You wrap your left hand around the "+
                               "soft leather on the handle of the "+
                               short()+". You feel a surge through "+
                               "your body as the weapon searches "+
                               "your soul.\n");
        }
        if (type == 0)
        {
            remove_adj("flaming");
            wielder->catch_msg("You wrap your left hand around the "+
                               "soft leather on the handle of the "+
                               short()+". You feel a surge through "+
                               "your body as the weapon searches "+
                               "your soul.\n");
            wielder->catch_msg("The reddish flame surrounding the "+
                               short()+ " suddenly vanishes! An evil "+
                               "aura begins to glow from the blade.\n");
        }
        if (type == 1)
        {
            remove_adj("holy");
            wielder->catch_msg("You wrap your left hand around the "+
                               "soft leather on the handle of the "+
                               short()+". You feel a surge through "+
                               "your body as the weapon searches "+
                               "your soul.\n");
            wielder->catch_msg("The bright white light surrounding the "+
                               short()+ " suddenly vanishes! An evil "+
                               "aura begins to glow from the blade.\n");
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

    if (type == 0)
    {
	if(!random(5))
	{
	    if(phurt > 0)
	    {
                dam = 100 + random(105);
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
		enemy->catch_msg("You scream in pain, as your " +
		   QTNAME(wielder)
		  + "'s " + short() + " emits a flame that "+
                  dam_descr + "your " + hdesc + ".\n");
		wielder->tell_watcher(QCTNAME(enemy) + " screams in pain as "
		  + QTNAME(wielder) + "'s " + short() + "emits a flame that "+
                  dam_descr + POSSESSIVE(enemy) + " " + hdesc + ".\n", enemy);

		enemy->heal_hp(-dam);
	    }
	}
    }
    if (type == 1)
    {
	if(!random(5))
	{
	    if(dam)
	    {
                dam = 150 + random(55);
		wielder->catch_msg("Your " +short()+ " glows with a "+
                  "silvery light, as the wounds on your " +
		  hdesc + " heals.\n");
		enemy->catch_msg(QCTNAME(wielder)+ " looks healthier, as " +
		   HIS(wielder) + " " +short()+ " glows with a silvery light. "+
		   "Suddenly the wounds on "+QCTNAME(wielder)+"'s "+
                   hdesc + " begins to heal!\n");
		wielder->tell_watcher(QCTNAME(wielder)+ " looks healthier, as " +
		   HIS(wielder) + " " +short()+ " glows with a silvery light. "+
		   "Suddenly the wounds on "+QTNAME(wielder)+"'s "+
                   hdesc + " begins to heal!\n", enemy);

		wielder->heal_hp(dam);
	    }
	}
    }
    if (type == 2)
    {
	if(!random(5))
	{
	    if(dam)
	    {
                dam = 75 + random(50);
		wielder->catch_msg("Your "+short()+ " sends out a bolt of "+
                  "black energy. The bolt strikes " +QCTNAME(enemy) + "'s " +
		  hdesc + ".\nYou feel healthier!\n");
		enemy->catch_msg("The " +short()+ " wielded by "+
		   QCTNAME(wielder)+ "sends out a bolt of black energy. The "+
		   "bolt hit your " + hdesc + ".\nYou feel drained!\n");
		wielder->tell_watcher("The "+short()+ " wielded by "+
		  QCTNAME(wielder) + " sends out a bolt of black energy that "+
                  "hits "+ POSSESSIVE(enemy) + "'s " + hdesc + ".\n", enemy);

		enemy->heal_hp(-dam);
		wielder->heal_hp(dam);
	    }
	}
    }
    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

void 
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}
