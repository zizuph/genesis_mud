/* Telenavar's sword, stolen from a member of a noble elven family.
   Code (c) 1999 Damian Horton - BKA Casimir.
*/

#pragma strict_types
#pragma save_binary

inherit "/std/weapon.c";
#include "/sys/wa_types.h"
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>

//prototypes:
string rune_descrip();

void create_weapon()
{
  set_name("sword");
  add_name("longsword");
  set_short("finely-crafted elven longsword");
  set_long("This is an elegant weapon, clearly of elvish craft. The blade "+
	"is of finely forged steel, and is decorated with runes. "+
	"The hilt and pommel are made of silver, and are heavily "+
        "adorned with ornamentation. The weapon glides easily through "+
	"the air when swung. There can be no doubt that this is "+
	"an excellent weapon.\n");

  set_adj ("elven");
  add_adj ("finely-crafted");

  set_hit(35);
  set_pen(29);

  // Magic weapon, made to last:
  likely_dull = 3;
  likely_corr = 3;
  likely_break = 3;

  set_wt(W_SWORD);
  set_dt(W_SLASH | W_IMPALE);
  set_hands(W_LEFT);
  add_prop(OBJ_I_WEIGHT,6200);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(35,29) + 300 + random(200));
  add_prop(OBJ_I_VOLUME,4100);

  //Magic weapon, therefor naturally resistant:

  add_prop(OBJ_I_RES_ACID, 30);
  add_prop(OBJ_I_RES_COLD, 50);
  add_prop(OBJ_I_RES_ELECTRICITY, 60);
  add_prop(OBJ_I_RES_FIRE, 50);

  add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
  add_prop(MAGIC_AM_MAGIC,({25,"elven enchantment"}));
  add_prop(MAGIC_AM_ID_INFO,({"This blade is a product of elven magic.\n",
			        10, "Like most elvish magic, it will only "+
				"benefit an elf.\n", 30,"However, in this "+
				"instance, the weapon should respond to "+
				"any within which flows blood of elven "+
				"ancestry, thus it may also be triggered "+
				"by partial elves in whom the elvish "+
				"strain is sufficiently strong.\n", 50}));
  add_prop(OBJ_S_WIZINFO, "This weapon becomes 39/35 when wielded by "+
	    "anyone of elven blood. I.e. elves and half elves.\n"); 
  set_wf(this_object());

  add_item("runes", rune_descrip);
}
    
/* VBFC function to descrip the runes on the sword. The return value
   depends upon the players mastery of the elvish written language, and
   his mastery of magic. */

string
rune_descrip()
{
    string return_value = "Runes are inscribed along the center of "+
	"sword's fine blade. ";
    
    if ((this_player()->query_race() == "elf" || this_player->
	query_skill(SS_LANGUAGE) > (50 + random(20))) &&
	this_player->query_skill(SS_SPELLCRAFT) > 40 + random(20))
    {
	return_value += "The runes are representative of elven "+
	    "enchantment. They make the blade sharper and stronger "+
	    "than it would otherwise be.\n";
    }
    
    else
    {
	return_value += "You do not comprehend their signifigance.\n";
    }

    return return_value;
}

/* This function is called when something attempts to wield the
   sword. */

mixed
wield(object to)
{

// note that wielder is a variable defined in /std/weapon.c

    if ((wielder->query_race() == "elf") || (wielder->query_race() == "half-elf"))
    {
	set_hit(39);
	set_pen(35);
	wielder->catch_tell("As you wrap your hand around the hilt of "+
			    "the sword, a welcoming warmth issues "+
			    "forth from it, pulsing in rhythme with "+
			    "elvish blood which is beating in your veins.\n");
    }

    else
    {
	set_hit(35);
	set_pen(29);
    }

// We use the alarm to ensure that the wield() function is completed before
// updating.
    set_alarm(0.0, 0.0, &wielder->update_weapon(this_object()));
    return 0; // print the usual messages, and wield the weapon as normal.
}









