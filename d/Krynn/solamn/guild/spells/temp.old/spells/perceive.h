/* ***************************************************************************
   perceive.h
         
   NAME:       Perceive
   COST:       30 Mana
   TAX:        0.25 * 1.5 (no material component) = 0.375
   CLASS:      I (information)
   AoE:	       object/target
   TASK:       simple
   SKILLS:     SS_SPELLCRAFT, SS_ELEMENT_LIFE, SS_FORM_DIVINATION, 
               SS_AWARENESS
   STATS:      TS_WIS
   DESC:       Success gives MAGIC_AM_ID_INFO
   REQUIRED:   Knight of Sword or Rose, KNIGHT_I_DEVOTION > 500
   
               Grace October 1994   
               Thanks to Olorin for help, guidance, and code.
	       Updated by Rastlin 
*************************************************************************** */

#include <cmdparse.h>
#include <comb_mag.h>
#include <formulas.h>
#include <macros.h>
#include <tasks.h>

#include "/d/Krynn/solamn/guild/guild.h"

#define PER_TARG     ({MAGIC_I_RES_IDENTIFY})
#define PER_MANA     25   (Same for failure and success)
#define PER_TASK     TASK_SIMPLE
#define PER_LIST     ({SKILL_AVG, SS_ELEMENT_LIFE, SS_FORM_DIVINATION, \
                     SKILL_END, SKILL_AVG, SS_SPELLCRAFT, SS_AWARENESS, \
                     SKILL_END, TS_WIS})
#define DEBUG 1
// FORMULA: (average(life,divination) + average(spellcraft,awareness) + 100*wis)/100


void
create_spell_perceive(string arg)
{
    set_spell_element(SS_ELEMENT_LIFE, 25);
    set_spell_form(SS_FORM_DIVINATION, 25);
    set_spell_mana_needed(25);
    set_spell_time(2);
    set_spell_message("perceive_message");
    set_spell_area_function("perceive_area");
}

mixed
do_perceive(string str)
{
   object  pl = query_caster(), targ, *targs;
   string  info = "";
   int     is_a_wiz = pl->query_wiz_level(), result, i;
   mixed   magic_str, prop;

#if DEBUG
   is_a_wiz = 0;
#endif
   if (pl->query_knight_level() < 3)
      return "Only Sword and Rose Knights may attempt this spell!\n";
   if (pl->query_prop(KNIGHT_I_DEVOTION) < 1000)
      return "Only Dedicated Knights may call upon Paladine.\n";

   if (!strlen(str))
      return "Which item do you wish to test for magic?";

   if (!sizeof(targs))
      return "Which item do you wish to test for magic?\n";
   else
      targ = targs[0];
}

public object *
perceive_area(string str)
{
   return FIND_STR_IN_OBJECT(str, query_caster()) + 
	  FIND_STR_IN_OBJECT(str, environment(query_caster()));
}

public void
perceive_message(object pl, object targ, int result)
{
    int i;
    string *magic_str, info;

    tell_room(E(pl), "\n" + QCTNAME(pl) + 
        " clasps a platinum medal in " + pl->query_possessive() + " fist " +
        " and mumbles a prayer under " + pl->query_possessive() + " breath.\n", pl); 

    pl->catch_msg("\nYou pray to Paladine and Kiri-Jolith, reciting the words:\n" +
        "\"In my hand your Symbol. In my heart the Oath.\nIn my memory the " +
        "Measure. Upon my lips this plea:\nPray reveal unto me the secret " +
        "nature of " + check_call(targ->short()) + ".\"\n\n");
        
/*
 *  Allows for restriction of MAGIC_AM_ID_INFO to players 
 */
    if (result < 25)
        result = 25;
    if (result > 75)
        result = 75;
    result *= 2;

    magic_str = targ->query_prop(MAGIC_AM_ID_INFO);
    for (i = 0; i < sizeof(magic_str); i += 2)
    {
        if (magic_str[i + 1] <= result)
        {
            info += magic_str[i];
        }
    }

    if (strlen(info))
        write(info);
    else
    {
        write("A trickle of energy flows into the medal and withdraws.\n " + 
           "You feel certain that the " + check_call(targ->short()) + " is "+
           "what it appears to be, and nothing more.\n");
    }
}







