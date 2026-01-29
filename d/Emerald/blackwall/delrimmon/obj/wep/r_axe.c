/*
 *  /d/Emerald/blackwall/delrimmon/obj/wep/r_axe.c
 *
 *  This is one of the weapons from the very old Emerald domain. I
 *  have included it in a list of such weapons which are wielded at
 *  random by the orc captain in the caves at Del Rimmon. I figure
 *  that these weapons, while pretty lame, will warm a few old players
 *  hearts, and that isn't such a bad thing.
 *
 *  Resurrected by Gorboth - Fall 2001. Original Coder unknown.
 *
 *  Minor code fixes done, but a more significant cleanup is needed
 *  - Shiva Sept. 12 2003
 *  - Fixed Runtime, Cotillion, Jan 9 2017
 *  - Made into spell enhancer, Ckrik Feb 6 2022
 */
inherit "/std/weapon";
inherit "/lib/keep";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <stdproperties.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include "/d/Emerald/defs.h"

int smeared;   /* Int for the smearing of corpses for their power.    */
int power_on;  /* Int for the regeneration of the power on the Axe. */
public mixed        steal_check();

public int do_smear(string str);
public string desc();

void
create_weapon()
{
    set_name("axe");
    add_name("runed axe");
    set_short("runed axe");
    set_long(desc);
    add_item("surface","The surface is covered in a myriad of tiny runes "+
         "which make no sense at all to you.\n");
    set_adj("runed");
    add_adj("metal");  /* it is, isn't it? -Gorboth */
    
/*  This weapon is extremely heavy and so the pen value is larger than   */
/*  the hit value since it's fairly easy to hit but the hit itself will  */
/*  _hurt_ a lot.                                                        */
    set_default_weapon(33, 44, W_AXE, W_BLUDGEON, W_ANYH,  this_object());
    // This value will affect spell damage for spellcasters.
    set_magic_spellpower(38); // ranges from 38 to 45 
    set_spellpower_elements(({
        SS_ELEMENT_DEATH, SS_ELEMENT_AIR, SS_ELEMENT_WATER
    }));
    add_prop(OBJ_I_WEIGHT, 15163); 
    add_prop(OBJ_I_VOLUME,  1981); 
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(33, 44) + random(321) + 198);
 
    add_prop(MAGIC_AM_MAGIC, ({ 65, "enchantment" }));
     add_prop(OBJ_M_NO_STEAL, steal_check);
    add_prop(MAGIC_AM_ID_INFO, ({ 
         "This axe is fairly magical which you can feel "+
         "through your hand. It has an ability to cause great damage in "+
         "battle and can only release its power once until recharged. "+
         "To recharge the weapon 'smear blade' or 'smear axe' should work "+
         "fine which needs to be performed 6 times.\n", 100,
         "This magical axe can cause special damage "+
         "in battle by releasing magical power onto the opponent. To "+
         "get the power back once must smear the blade with blood from "+
         "a corpse.\n", 80,
         "The axe can deliver great damage in battle "+
         "but only once until recharged with the magical powers it "+
         "harnesses. To get the powers back the blood of dead enemies "+
         "must be smeared onto the blade.\n", 60,
         "Death swings with this double headed axe. "+
         "You can feel the very power it exhibits pulsing through the "+
         "blade whilst you are holding it. It can be recharged by smearing "+
         "blood onto the blade.\n", 40,
         "This extremely magical axe is a work of art. "+
         "It can release extreme energies in battle and must feed off the "+
         "blood of the dead.\n", 20 }));
 
    add_prop(OBJ_S_WIZINFO, "This was the runed axe of the "+
         "Emerald mines found on the warlord, back in the old days of " +
         "ancient Emerald. It has a special attack, hitting "+
         "extremely hard but it can only be performed once until it is "+
         "recharged by 'smear blade' or 'smear axe' using corpses which are "+
         "fairly easy to get hold of.\n");
 
    power_on = 1;
    smeared = 0;
}

/*
 * Function name: query_magic_spellpower
 * Description:   This function returns the spellpower that the item will
 *                provide when equipped.
 */
public int
query_magic_spellpower()
{
    // If fully charged, spellpower 45, i.e. 38 + 7
    if (power_on)
    {
        return magic_spellpower + 7;
    }
    // Else spellpower 38 + number of charges, max is 7
    return magic_spellpower + smeared;
}

string
desc()
{
   string extra_str = "";

   if (power_on)
   {
        extra_str = " The runes glow a strange colour of blue.";
   }

   return "This heavy axe feels remarkably light in your "+
        "expert hands, its leather covered handle seeming to grip to "+
        "your hands. The two blades of the axe look wicked with the "+
        "light sparkling in its reflection, illuminating the runes "+
        "a little."+extra_str+"\n";
}

mixed
wield(object wep)
{
    if (this_player()->query_skill(SS_WEP_AXE) < 60)
    {
        return "The blade is too heavy for you to wield.\n";
    }

    if (this_player()->resolve_task(TASK_ROUTINE, ({ TS_INT, SS_SPELLCRAFT})) <= 0)
    {
        write("The weapon stuns you with static!\n");
        this_player()->heal_hp(-60);
        if (this_player()->query_hp() <= 0)
        {
            this_player()->do_die(this_object());
        }

       return -1;
    }

    return 0;
}

void
init()
{
    ::init();

    if (this_player() == environment())
    {
        add_action(do_smear, "smear");
    }

}

public int
is_corpse(object ob)
{
    return IS_CORPSE_OBJECT(ob);
}

int
do_smear(string str)
{
    object *corpses;

    if (!strlen(str) || (str != "axe" && str != "blade"))
    {
   	notify_fail("Smear what?\n");
   	return 0;
    }
 
    corpses = filter(all_inventory(environment(this_player())) + all_inventory(this_player()), is_corpse);   
 
    if (!sizeof(corpses))
    {
   	notify_fail("There is no corpse here!\n");
   	return 0; 
    }
 
    write("You rip " + LANG_THESHORT(corpses[0]) +
   	  " apart thoroughly smearing the blade with blood.\n");
    say(QCTNAME(this_player())+" smears "+POS(this_player())+
   	 " runed axe with blood from " + LANG_THESHORT(corpses[0]) +
   	 ".\nThere is nothing left of the corpse.\n");
 
    // Corpses automatically move out their contents when removed.
    corpses[0]->remove_object();
 
    if (smeared <= 6) 
    {
   	smeared++;
    }
    else
    {
   	smeared = 0;
   	power_on = 1;
    }
 
    return 1;
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
   init_wep_recover(arg);
   init_keep_recover(arg);
}

/* Filter the people without see_blood, so they dont see the special hits */
static void
tell_watcher(string str, object enemy)
{
    query_wielded()->tell_watcher(str, enemy);
}

/* After we tried to hit something this function is called with the result. */
varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
        int phit, int dam)
{
    object blind;
    int ran;

    if (!objectp(enemy) || !objectp(query_wielded()))
        return 0;

    ran = random(12);

    if (phurt == -1 || phurt == -2)
    {
        query_wielded()->catch_msg("The axe swings so close to "+
           QTPNAME(enemy)+" head that "+enemy->query_pronoun()+" gulps "+
                "in fright.\n");
        enemy->catch_msg("The axe swings so close to your head that "+
           "you gulp in fright.\n");
        tell_watcher(QCTPNAME(query_wielded())+" axe swings so close to "+
           QTPNAME(enemy)+" head that "+QTNAME(enemy)+" gulps in "+
           "fright.\n", enemy);
        return 0;
    }
    if (phurt == 0)
    {
        query_wielded()->catch_msg("You grin evilly as you feel your axe "+
           "thump solidly into " + QTNAME(enemy) + ".\n");
        enemy->catch_msg(QCTPNAME(query_wielded())+" axe thumps solidly "+
           "into you.\n");
        tell_watcher(QCTNAME(query_wielded())+" grins evilly as "+
           POS(query_wielded())+" axe thumps solidly into "+QTNAME(enemy)
           +".\n",enemy);
    }
    else
    {
        if (ran == 1 && power_on)
        {
           query_wielded()->catch_msg("The runed axe discharges a blast "+
                "of static as it gouges deeply into "+QTNAME(enemy)+".\n");
           enemy->catch_msg("A blast of static rips into you from the "+
                "runed axe.\n");
           tell_watcher(QCTPNAME(query_wielded())+" runed axe discharges "+
                "a blast of static as it gouges into "+QTNAME(enemy)+".\n", enemy);
           enemy->heal_hp(-(200 + (query_wielded()->query_skill(SS_SPELLCRAFT)) -
                (enemy->query_skill(SS_ELEMENT_AIR)) + 
                (query_wielded()->query_stat(SS_STR) / 2)));
           enemy->command("$scream");

           if (enemy->query_hp() <= 0)
	   {
               enemy->do_die(query_wielded());
	   }

           power_on = 0;
           smeared = 0;
           return 1;
        }
        if (ran == 2 && power_on)
        {
           query_wielded()->catch_msg("Your runed axe warms as it slices "+
                "straight through "+QTPNAME(enemy)+" side.\n");
           enemy->catch_msg("You scream as "+QTPNAME(query_wielded())+
                " runed axe slices into your side.\n");
           tell_watcher(QCTPNAME(query_wielded())+" runed axe glows red "+
                "as it slices into "+QTPNAME(enemy)+" side.\n",enemy);
           enemy->heal_hp(-(100 + (query_wielded()->query_skill(SS_SPELLCRAFT)) -
                (enemy->query_skill(SS_ELEMENT_AIR)) +
                (query_wielded()->query_stat(SS_STR) / 2)));
           if(enemy->query_hp() <= 0)
	   {
                enemy->do_die(query_wielded());
	   }

           power_on = 0;
           smeared = 0;
           return 1;
        }
        return 0;
    }
}


/*
 * Function name:        steal_check
 * Description  :        this sword cannot be stolen from Akugla
 * Returns      :        string - can't steal msg, 0 - can steal
 */
public mixed
steal_check()
{
    if (environment(this_object())->id("del_rimmon_akugla"))
    {
        return "As you reach for the weapon, the fearsome orc"
          + " captain turns upon you and, with a single glance,"
          + " stops you cold.\n";
    }

    return 0;
} /* steal_check */

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
