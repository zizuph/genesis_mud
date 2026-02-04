/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>

#define CAST_LIMIT    40   /* The limit for this to become a success */
#define SPELL_DIR"/d/Terel/mecien/valley/guild/spells/"
#define TP this_player()


/* Function name: fortudo
* Description:   grants temporary discipline
* Arguments:     str - 
* Returns:       1/0
*/
nomask mixed
fortudo(string str)
{
   object who;
   int mana_limit, sum;
   int ds, dt;
   
   if (str)
      who = present(lower_case(str), environment(this_player()));
   if (!who)
      {
      if (!str || (str == "me"))
         who = this_player();
      else
         return "To whom shall this power be called?.\n";
   }
   
   if (NPMAGIC(who)) /* See if it is possible to cast a magic spell on obj. */
      return "Something blocks the power.\n";
   
   mana_limit = 40;
   if (who == this_player()) /* Costs more on yourself */
      mana_limit = 50;
   
   if (this_player()->query_mana() < mana_limit)
      return "You are to weak to attempt this.\n";
   
   if (random(this_player()->query_skill(SS_ELEMENT_LIFE) +
            this_player()->query_skill(SS_FORM_ENCHANTMENT)) < random(CAST_LIMIT))
   {
      write("Your call in not heard.\n");
      this_player()->add_mana(-mana_limit / 3);
      return 1;
   }
   
   this_player()->add_mana(-mana_limit);
   write("You call upon the spirits of courage and heroism.\n"
      + "A deep trembling begins within your soul.\n");
   say("Intoning a solemn prayer, " + QCTNAME(this_player()) +
      " opens " + this_player()->query_possessive() + 
      " hands and holds them aloft.\n");
   tell_room(environment(this_player()),
      "A strange feeling passes over you, a trembling and shifting within\n"
      + "the air. You hear the sounds of distant trumpets.\n");
   ds = (1 + random(15) + (TP->query_stat(SS_WIS)/15));
   dt = (10 + (TP->query_stat(SS_WIS)/4));
   seteuid(getuid());
   who->add_tmp_stat(SS_DIS, ds, dt);
   who->catch_msg("A spirit of courage descends upon you.\n");
   return 1;
}

/* Function name:
* Description:
* Arguments:
* Returns:
*/

