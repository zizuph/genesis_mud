/* Edited by Mortis 02.2006 to change seperate to separate.
 * Changed set_long(long_descr); to set_long("@@long_descr")
 * so it would work with <tend> and neidar <mark>.
 */

inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"

#define DIAMOND "/d/Genesis/gems/obj/diamond_black"

object wearer;
int diamond = 1;

string pry_diamond();
string long_descr();

void
create_armour()
{
   set_name("circlet");
   set_ac(5);
   set_at(A_HEAD);
   set_am( ({ 0, 0, 5 }) );
   set_adj("silver");
   add_adj("braided");
   set_short("silver braided circlet");   
   set_long("@@long_descr");
   add_prop(OBJ_I_VOLUME, 50);
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(9, A_HEAD));
   add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(9));

   set_af(TO);

   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
   add_prop(MAGIC_AM_ID_INFO,
      ({"This circlet was once owned by an elven archer-mage who enchanted " +
        "the circlet to enhance his hunting skills. The wearer of this circlet "+
        "gains a heightened perception of depth, improving his ability with missile "+
        "weapons, as well as heightened awareness of their " +
        "surroundings. The black diamond is the focus of the enchantment, so if " +
        "pried from the circlet the magic enhancements are lost.\n",30}));
   add_prop(MAGIC_AM_MAGIC,({10,"enchantment"}));

   add_cmd_item(({"diamond from circlet","black diamond from circlet","black diamond"}),
      "pry", pry_diamond);

}

string
long_descr()
{
    if(diamond)
    {
        return "This is a beautifully crafted circlet, braided from many fine " +
     "threads of silver. These threads of silver separate at the front of the " +
     "circlet, where they twine around a beautiful black diamond that shines " +
     "with a dark brilliance.\n";
    }
    else
        return "This is a beautifully crafted circlet, braided from many fine " +
     "threads of silver. These threads of silver separate at the front of the " +
     "circlet, where it looks like a gem of some sort may have once resided.\n";
}

string
pry_diamond()
{
    if(!diamond)
      return "There is no diamond to pry from the circlet.\n";

    if(TP == wearer)
      return "You cannot pry the black diamond from the circlet while you are " +
        "wearing it!\n";

    write("You pry the black diamond from the silver braided circlet.\n");
    say(QCTNAME(TP) + " pries a black diamond from the silver braided circlet.\n");

    seteuid(getuid());
 
    clone_object(DIAMOND)->move(TP);
    diamond = 0;

    return "";
}

void
wear_message()
{
    if(E(TO) != wearer)
	return;

    wearer->catch_msg("You feel a moment of disorientation as you wear the " +
      "silver braided circlet, followed by a sharpening of your visual senses.\n");

}


mixed
wear(object what)
{
    if(diamond)
    {
      TP->set_skill_extra(SS_AWARENESS, TP->query_skill_extra(SS_AWARENESS) + 10);
      TP->set_skill_extra(SS_WEP_MISSILE, TP->query_skill_extra(SS_WEP_MISSILE) + 10);
      wearer = TP;
      set_alarm(0.5, 0.0, "wear_message");
    }

    return 0;
}

mixed
remove(object what)
{
    if(diamond)
    {
      wearer->set_skill_extra(SS_AWARENESS, TP->query_skill_extra(SS_AWARENESS) -10);
      wearer->set_skill_extra(SS_WEP_MISSILE, TP->query_skill_extra(SS_WEP_MISSILE) -10);
    }

    wearer = 0;
    return 0;
}
