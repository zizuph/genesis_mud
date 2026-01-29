/* Telenavar's sword, stolen from a member of a noble elven family.
   Code (c) 1999 Damian Horton - BKA Casimir.
*/

#pragma strict_types
#pragma save_binary

inherit "/std/weapon.c";
#include "/sys/wa_types.h"
#include <formulas.h>
#include <macros.h>

void create_weapon()
{
  set_name("sword");
  add_name("longsword");
  set_short("finely-crafted elven longsword");
  set_long("This is an elegant weapon, clearly of elvish craft. The blade "+
	"is of finely forged steel, and is decorated with runes. "+
	"The hilt and pommel are made of silver, and are highly ornate in "+
	"their design and ornamentation. The weapon glides easily through "+
	"the air easily when swung. There can be no doubt that this is "+
	"an excellent weapon.\n");

  set_adj ("elven");
  add_adj ("finely-crafted");

  set_hit(35);
  set_pen(29);

  set_wt(W_SWORD);
  set_dt(W_SLASH | W_IMPALE);
  set_hands(W_LEFT);
  add_prop(OBJ_I_WEIGHT,6200);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(35,29) + 300 + random(200));
  add_prop(OBJ_I_VOLUME,4100);
 
  add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
  add_prop(MAGIC_AM_MAGIC,({25,"elven enchantment"}));
  add_prop(MAGIC_AM_ID_INFO,({"This blade is a product of elven magic.\n",
				10,"Like most elvish magic, it will only "+
				"benefit an elf.\n",30,"However, in this "+
				"instance, the weapon should respond to "+
				"any within which flows blood of elven "+
				"ancestry, thus it may also be triggered "+
				"by partial elves in whom the elvish "+
				"strain is sufficiently strong.\n",50}));
  add_prop(OBJ_S_WIZINFO,"This weapon becomes 39/35 when wielded by "+
	    "anyone of elven blood. I.e. elves and half elves.\n"); 
  set_wf(this_object());
}
       
mixed
wield(object to)
{
    object wielder = environment(this_object());

    if ((wielder->query_race() == "elf") || (wielder->query_race() == "half-elf"))
    {
	set_hit(39);
	set_pen(35);
	this_player()->catch_tell("As you wrap your hand around the hilt of "+
			     "the sword, a welcoming warmth issues "+
			     "forth from it, pulsing in rhythme with "+
			     "elvish blood which is beating in your veins.\n");
    }

    else
    {
	set_hit(35);
	set_pen(29);
    }

    set_alarm(0.0, 0.0, &wielder->update_weapon(this_object()));
    return 0; // print the usual messages, and wield the weapon as normal.
}










