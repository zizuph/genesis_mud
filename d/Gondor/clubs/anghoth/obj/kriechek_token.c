/*
 *  The Anghoth token worn by Kriechek.
 *    (code borrowed from the Ranger emblem)
 *
 *  Alto, 03 June 2002.
 *
 */
#pragma save_binary

#include "../anghoth_defs.h"

inherit ANGHOTH_OBJ + "anghoth_token";

#include <wa_types.h>
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

create_emblem()
{
  set_name("ring");
  add_name(({"kriechek_token", "kriechek_emblem"}));
  add_name("anghoth_kriechek_token");
  set_adj("shield-shaped");
  set_at(A_ANY_FINGER);

  seteuid(getuid(TO));
}

string set_emblem_short(object pl)
{
  if (TP == environment(TO))
      {
      return emblem_type + " shield-shaped ring of the Kriechek Anghoth";
      }
  return emblem_type + " shield-shaped ring";
}  

string set_emblem_long(object pl)
{
    if (TP == environment(TO)) 
    {
        if (ANGHOTH_MEMBER(TP))
            return ("This is a ring of " + emblem_type + " shaped like a "
            + "shield. A grand black tower adorns its face. This serves to "
            + "remind you of your failed duty as an Anghoth, Shield of Minas "
            + "Morgul. On the outside is engraved: " + anghoth_name 
            + ", Kriechek Anghoth.\n"
            + "\tThe ring is forged of rough and rusted tin from "
            + "the roof of a barn where cattle slumber. Such is the worth "
            + "of its bearer, dishonoured of the Anghoth.\n"
            + "\tYou feel the immense disappointment of your Lord " 
            + sponsor_name + " radiating from the ring. It is deadly cold "
            + "to the touch.\n");
        return ("This is a ring of " + emblem_type + " shaped like a shield. "
            + "On one side is engraved: "+ anghoth_name 
            + ", Kriechek Anghoth.\n");
    }
    if (ANGHOTH_MEMBER(TP))
        return ("It is a ring of " + emblem_type + " shaped like a shield, "
            + "the emblem of the Kriechek Anghoth, which someone must "
            + "have carelessly dropped.\n");
    return ("It is a ring of " + emblem_type + " shaped like a shield.\n");
}

wear(object ob)
{
  if (ANGHOTH_MEMBER(TP) || TP->query_npc()) 
  {
    	 write("You slip the " + emblem_type + " shield-shaped ring on your "
          + "finger.\n"
          + "The weight of your responsibilities bear heavily upon your "
          + "soul as you feel the Eye upon you.\n");
	     say(QCTNAME(TP) + " wears the "
	         +(stringp(emblem_type) ? emblem_type : "")
	         + " ring on " + POSSESSIVE(TP) + " finger.\n", TP);
      return 1;
  }
  return "You try to wear the ring, but it burns you painfully!\n";
}
