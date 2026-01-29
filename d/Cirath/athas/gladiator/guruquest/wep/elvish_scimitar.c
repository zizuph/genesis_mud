/* This is Myrdoth's best scimitar. It has a steel blade, making it a 
   a prized possession on Athas. It would, not, however be an exceptional
   weapon were it not that it had been blessed by an elvish druid. As a
   result, it becomes a more potent weapon in the hands of an elf.
   Code (c) 1998 Damian Horton - BKA Dethraine.
   Updated, 2001 for Raumdor.
*/

#pragma strict_types
#pragma save_binary

#include "/sys/wa_types.h"
#include <formulas.h>
#include "/d/Cirath/defs.h"

inherit "/std/weapon";
inherit "/lib/keep"; //this weapon may be kept, and is kept by default

void create_weapon()
{
  set_name("sword");
  add_name("scimitar");
  set_short("elvish steel scimitar");
  set_long("The steel blade of this scimitar makes it stand out in these "+
	   "metal deprived parts. "+
	   "Its handle is fashioned from bone, and is beautifully "+
	   "ornamented in the style of the Makla Noth. There can be no "+ 
	   "question that this is a fine weapon.\n");
  set_adj ("elvish");
  add_adj ("steel");

  set_hit(31);
  set_pen(24);

  set_wt(W_SWORD);
  set_dt(W_SLASH);
  set_hands(W_ANYH);
  add_prop(OBJ_I_WEIGHT,4700);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(31,24) + random(300));
  add_prop(OBJ_I_VOLUME,3100);
  set_keep(1);
 
  add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
  add_prop(MAGIC_AM_MAGIC, ({20, "enchantment"}));
  add_prop(MAGIC_AM_ID_INFO, ({"You detect that this weapon has been blessed "+
      "by druidic elvish magic.\n",20,"Blessed by druidic elvish magic,you "+
      "note that the blessing will only improve this weapon when it is "+
      "wielded in the hands of an elf. In the hands of others, it is an "+
      "ordinary weapon.\n",40}));
  add_prop(OBJ_S_WIZINFO, "An ordinary weapon when wielded by a non-elf, "+
      "it becomes a 37/37 blade when wielded by an elf.\n");
  set_wf(TO);
}
       
mixed
wield(object to)
{
  if (TP->query_race() == "elf")
  {
      TO->set_hit(37);
      TO->set_pen(37);
      TP->catch_tell("The elvish steel scimitar somehow feels right in "+
	  "your hands, almost as if it has been specially designed "+
	  "for you.\n");
  }
  else
  {
      TO->set_hit(31);
      TO->set_pen(24);
  }

  //remove the alarm (see below) because it blew the Rockfriends grip 
  // command ... and it doesn't appear to be necessary
  wielder->update_weapon(this_object());

   // We use the alarm to ensure that the wield() function is completed before
  // updating.
  //  set_alarm(0.0, 0.0, &wielder->update_weapon(this_object()));
  return 0;
}


