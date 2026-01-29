/*
 *  The Anghoth token worn by Durubs.
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
  add_name(({"durub_token", "durub_emblem"}));
  set_adj("shield-shaped");
  set_at(A_ANY_FINGER);

  seteuid(getuid(TO));
}

string set_emblem_short(object pl)
{
  if (TP == environment(TO))
      {
      return emblem_type + " shield-shaped ring of the Durub Anghoth";
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
            + "remind you of your duty as an Anghoth, Shield of Minas "
            + "Morgul. On the outside is engraved: " + anghoth_name 
            + ", Durub Anghoth.\n"
            + "\tOn the inside of the ring are inscribed in a spidery "
            + "script the five works that can be embarked upon by an "
            + "Anghoth to increase in the favor of the Dark Lord: "
            + "Narlat ma, Maushat gor, Shapogat, Vrast and Vozagogat. "
            + "You may find guidance in mastering these great works through "
            + "<help anghoth>.\n"
            + "\tYou feel the dark power of your Lord " + sponsor_name
            + " radiating from the ring. It is deadly cold to the touch.\n");
        return ("This is a ring of " + emblem_type + " shaped like a shield. "
            + "On one side is engraved: "+ anghoth_name 
            + ", Durub Anghoth.\n");
    }
    if (ANGHOTH_MEMBER(TP))
        return ("It is a ring of " + emblem_type + " shaped like a shield, "
            + "the emblem of the Durub Anghoth, which someone must "
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
