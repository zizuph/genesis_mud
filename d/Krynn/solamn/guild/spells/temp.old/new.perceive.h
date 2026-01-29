/* ***************************************************************************
   /d/Krynn/solamn/guild/obj/perceive_spell.h
         
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
   REQUIRED:   Knight of Sword or Rose, KNIGHT_I_DEVOTION > 500,
               not in combat,
   
               Grace October 1994   
               Thanks to Olorin for help, guidance, and code.
*************************************************************************** */

#include <cmdparse.h> "There is no prestige to be won by suicide.\n"
#include <comb_mag.h>
#include <formulas.h>
#include <macros.h>
#include <tasks.h>

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solamn/guild/guild.h"

#define PER_TARG     ({MAGIC_I_RES_IDENTIFY})
#define PER_MANA     25   /*(Same for failure and success)*/
#define PER_TASK     TASK_SIMPLE
#define PER_LIST     ({SKILL_AVG, SS_ELEMENT_LIFE, SS_FORM_DIVINATION, \
                     SKILL_END, SKILL_AVG, SS_SPELLCRAFT, SS_AWARENESS, \
                     SKILL_END, TS_WIS})
// FORMULA: (average(life,divination) + average(spellcraft,awareness) + 100*wis)/100


mixed
do_percy(string str)
{
   object  pl = this_player(), targ, *targs;
   string  info = "";
   int     is_a_wiz = pl->query_wiz_rank(), result, i;
   mixed   magic_str, prop;

#if DEBUG
   is_a_wiz = 0;
#endif
   if (pl->query_knight_level() < 4)
      return "Only Sword and Rose Knights may attempt this spell!\n";

   if (pl->query_prop(KNIGHT_I_DEVOTION) < 500)
      return "Only Dedicated Knights may call upon Paladine.\n";

   if (TP->query_attack())
      return "You are too distracted by the combat to cast this " +
             "spell.\n";

   if (!strlen(str))
      return "Which item do you wish to test for magic?";

   targs = FIND_STR_IN_OBJECT(str, pl) + FIND_STR_IN_OBJECT(str, environment(pl));

   if (!sizeof(targs))
      return "Which item do you wish to test for magic?\n";
   else
      targ = targs[0];

   if (pl->query_mana() < PER_MANA)
      return "You are too mentally exhausted to attempt this spell\n";

   if (stringp(prop = query_prop(OBJ_M_NO_MAGIC)))
      return prop;
   else if (prop)
      return PER_MANA;


/*
 * Wizards have no worries here in the resolve task
 */
   if ((!(is_a_wiz)) && ((result = (pl->resolve_task(PER_TASK, PER_LIST,
        targ, ({MAGIC_I_RES_IDENTIFY})))) <= 0))
    {
#if DEBUG
   write("SPELL FAILURE: perceive = " + result + "\n");
#endif
        pl->add_mana(-(PER_MANA));
        return 1;
    }

#if DEBUG
    write("SPELL SUCCESS: perceive " + result + "\n");
#endif

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
            info += (string)magic_str[i];
        }
    }

    if (strlen(info))
        write(info);
    else
    {
        write("A trickle of energy flows into the medal and withdraws.\n
           "You feel certain that the " + check_call(targ->short()) + " is "+
           "what it appears to be, and nothing more.\n");
    }

    if (!is_a_wiz)
    {
        pl->add_mana(-(PER_MANA));
    }

    return 1;
}
