/*
 *  The Anghoth token worn by Ashuk (the Lost).
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
  add_name(({"ashuk_token", "ashuk_emblem"}));
  set_adj("shield-shaped");
  set_at(A_ANY_FINGER);

  seteuid(getuid(TO));
}

string set_emblem_short(object pl)
{
  if (TP == environment(TO))
      {
      return "crumbling shield-shaped ring of the Ashuk Anghoth";
      }
  return "crumbling shield-shaped ring";
}  

string set_emblem_long(object pl)
{
    if (TP == environment(TO)) 
    {
        if (ANGHOTH_MEMBER(TP))
            return ("This is a crumbling ring, shaped like a shield. Although "
            + "the face of the ring is broken and tarnished, you make out a "
            + "black tower through the cracks. You are an Ashuk Anghoth, "
            + "and you have no Lord to shield. You "
            + "are lost. On the outside is engraved: " + anghoth_name 
            + ", Ashuk Anghoth.\n"
            + "\tOn the inside of the ring are inscribed in a spidery "
            + "script the five works that can be embarked upon by an "
            + "Anghoth to increase in the favor of the Dark Lord: "
            + "Narlat ma, Maushat gor, Shapogat, Vrast and Vozagogat. "
            + "You may find guidance in mastering these great works through "
            + "<help anghoth>.\n");
        return ("This is a crumbling ring shaped like a shield. "
            + "On one side is engraved: "+ anghoth_name 
            + ", Ashuk Anghoth.\n");
    }
    if (ANGHOTH_MEMBER(TP))
        return ("It is a crumbling ring shaped like a shield, "
            + "the emblem of the Ashuk Anghoth, which someone must "
            + "have carelessly dropped.\n");
    return ("It is a crumbling ring shaped like a shield.\n");
}

wear(object ob)
{
  if (ANGHOTH_MEMBER(TP) || TP->query_npc()) 
  {
      write("You slip the crumbling shield-shaped ring on your finger.\n"
          + "You feel lost without a Lord.\n");
          say(QCTNAME(TP) + " wears the crumbling ring on " 
          + POSSESSIVE(TP) + " finger.\n", TP);
      return 1;
  }
  return "You try to wear the ring, but it burns you painfully!\n";
}

