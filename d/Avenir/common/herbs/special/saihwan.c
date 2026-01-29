// Saihwan       (/d/Avenir/common/herbs/saihwan.c)
//               'saihwan' is Gothic for 'see'
//               -=* An herb allowing person to see invisible *=-
// Creator:      Lilith	 22 Jun 96
// Purpose:      Balance. To provide a detection for invisibility.
/* Note          There are (to my knowledge) four different ways for 
 *               mortals to turn invis: 
 *               1) Invis potion in Neraka, Krynn
 *               2) Monk humbleleaf herb in Roke
 *               3) Spirit in Re Albi castle, Roke 
 *               4) Morgul mage potion, which allows up to five levels of
 *                  invisibilty at a time.  
 *             
 *               Saihwan does the following:
 *               -  Makes _live_i_see_invis additive, up to ~40.
 *                  (Once it reaches 100, they can see wizards :)
 *               -  Uses resolve_task, based upon con and awareness, to 
 *                  determine whether or not the player will be poisoned
 *                  or granted sight.
 *               -  Mildly poisoning (reduces STR,etc), if resolve_task 
 *                  (ie awareness and con) not high enough.
 */

inherit "/std/herb";

#include "/d/Avenir/common/common.h"
#include <herb.h>
#include <poison_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <tasks.h>     /* For difficulty and stat defines */
#include <ss_types.h>  /* For skill defines */

int  a_id = 0;

void
create_herb()
{
  set_name("fungus");
  set_pname("fungi");
  add_name(({"herb", "mushroom", "mushrooms"}));
  set_short("orange-white fungus");
  set_pshort("orange-white fungi");
  set_adj("orange");
  add_adj(({"white", "orange-white"}));

  set_herb_name("saihwan");
  set_unid_long("This is a mushroom with an orange cap and "+
     "a fleshy white stalk. Like most other fungi, it is a "+
     "saprophyte, growing in dark, dank places and feeding "+
     "on dead matter. It looks quite tasty.\n");
  set_id_long("Saihwan is a mushroom with an orange cap and " +
     "a fleshy white stalk. Like most other fungi, it is a "+
     "saprophyte, growing in dark, dank places and feeding "+
     "on dead matter.\n"+
     "It is rumoured that saihwan is used ritually by Sybarites "+
     "to enable them to discern the forms of concealed spirits "+
     "and other invisible creatures.  "+
     "People with less robust constitutions will find the "+
     "mushrooom to be mildly poisonous. It looks quite tasty."+
     "\n");
  set_find_diff(4);
  set_id_diff(26);
  set_herb_value(250);
  set_ingest_verb("eat");
  set_decay_time(700);

  set_effect(HERB_SPECIAL, "", 10);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }


special_effect()
{
   object ob;
   int task;

   task = this_player()->resolve_task(TASK_ROUTINE, ({TS_CON, SS_AWARENESS}));

   seteuid(getuid());
   
   if (task < 50)
   {
       ob = clone_object("/d/Avenir/lilith/temp/saihwan_poison");
       ob->set_poison_type("saihwan");
       ob->set_strength(10 + random(5));
       ob->set_damage(({POISON_HP, 5 + random(5),
                        POISON_STAT, SS_STR,
                        POISON_FATIGUE, 5 + random(5)}));
       write("This " + short() + " tastes odd...\n");
       ob->move(this_player());
       ob->start_poison();
   }
   else
   {
       ob = clone_object("/d/Avenir/lilith/temp/saihwan_see");
       ob->set_time(110 + random(100));
       ob->move(this_player());
   }

}
