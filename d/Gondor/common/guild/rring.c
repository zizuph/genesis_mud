#pragma save_binary

inherit "/d/Gondor/common/guild/lib/rtoken";
#include <wa_types.h>
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

create_token()
{
  set_name("ring");
  add_name(({"ranger_ring", "Gondorian_Ranger_Ring"}));
  set_at(A_ANY_FINGER);
  seteuid(getuid(TO));
}

string set_token_short()
{
  if (TP == environment(TO)) 
      return token_type+" ring of the Rangers of Gondor";
  return token_type+" ring";
}  

string set_token_long()
{
    if (TP == environment(TO)) 
    {
        if (is_ranger(TP))
            return BSN("This is a "+token_type+" ring, " +
                   "the membership token of the Rangers of Gondor. "+
                   "On the inside is enscribed: "+ranger_name+", Ranger of Gondor.");
        return BSN("This is a plain "+token_type+". " +
               "On the inside is enscribed: "+ranger_name+", Ranger of Gondor.");
    }
    if (is_ranger(TP))
        return BSN("It is a "+token_type+" ring of the Rangers of Gondor. " +
               "Someone must have dropped it here.");
    return BSN("It is a plain "+token_type+" ring. You see nothing special about it.");
}

wear(object ob)
{
    if (is_ranger(TP)) 
    {
        write("You wear the "+token_type+" ring on your finger.\n"+
              "It feels good to be back with the Rangers of Gondor.\n");
        say(QCTNAME(TP)+" wears the "
          +(stringp(token_type) ? (token_type + " ") : "")
          +"ring on "+POSSESSIVE(TP)+" finger.\n",TP);
        return 1;
    }
    return "You try to wear the ring, but it is too small!\n";
}
