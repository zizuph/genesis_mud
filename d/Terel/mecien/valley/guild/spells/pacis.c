/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>

#define MANA_LIMIT      25  /* How much mana does it cost to cast this spell? */
#define CAST_LIMIT      25 /* How wise and skilled must the caster be? */
#define SPELL_DIR"/d/Terel/mecien/valley/guild/spells/" /* Where is our spell dir? */

/* Function name: pacis
 * Description:   Will light up the room if it's a success with 1 factor
 *                It costs equal mana on success or failure.
 * Arguments:     str - the string from the light spell casted, must be 'room'
 * Returns:       Failure msg or 1
 */
 
nomask mixed
pacis(string str)
{
   int duration;
   object ob;
   
   ob = present("spirit_of_peace", environment(this_player()));
   if (ob) return "There is already a spirit of peace here!\n";

   if (this_player()->query_mana() < MANA_LIMIT)
      return "You do not have the strength.\n";
   
   this_player()->add_mana(-MANA_LIMIT);
   
   if (random(this_player()->query_skill(SS_FORM_CONJURATION) +
            this_player()->query_skill(SS_ELEMENT_LIFE)) < random(CAST_LIMIT))
   {
      return "Your prayer is not heard.\n";
   }
   
   write("You hail the spirits of peace with a holy song of summons.\n");
   say(QCTNAME(this_player()) + " reaches out and intones a holy song.\n");
   
   seteuid(getuid(this_object()));
   ob = clone_object(SPELL_DIR + "pacis_anima");
   duration = 45 + random(this_player()->query_stat(SS_INT)) +
                   random(this_player()->query_skill(SS_SPELLCRAFT));
   ob->move(environment(this_player()));
   ob->make_peace(duration);
   return 1;
}
