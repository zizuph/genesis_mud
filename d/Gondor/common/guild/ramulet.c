#pragma save_binary

inherit "/d/Gondor/common/guild/lib/rtoken";
#include <wa_types.h>
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

create_token()
{
  set_name("amulet");
  add_name(({"ranger_amulet", "Ithilien_Ranger_Amulet"}));
  set_adj("moon-shaped");
  set_at(A_NECK);
  seteuid(getuid(TO));
}

string set_token_short()
{
  if (TP == environment(TO)) 
      return token_type+" moon-shaped amulet of the Rangers of Ithilien";
  return token_type+" moon-shaped amulet";
}  

string set_token_long()
{
    if (TP == environment(TO)) 
    {
        if (is_ranger(TP))
            return BSN("This is an amulet of "+token_type+" shaped like a rising moon. "+
                   "It is the membership token of the Rangers of Ithilien. "+
                   "On the backside is enscribed: "+ranger_name+", Ranger of Ithilien.");
        return BSN("This is a amulet of "+token_type+" shaped like a rising moon. "+
               "On the backside is enscribed: "+ranger_name+", Ranger of Ithilien.");
    }
    if (is_ranger(TP))
        return BSN("It is an amulet of "+token_type+" shaped like a rising moon, the "+
               "token of the Rangers of Ithilien, which someone must have dropped.");
    return BSN("It is an amulet of "+token_type+" shaped like a rising moon.");
}

wear(object ob)
{
  if (is_ranger(TP)) 
  {
      write("You wear the "+token_type+" amulet around your neck.\n"+
            "It feels good to be back with the Rangers of Ithilien.\n");
      say(QCTNAME(TP)+" wears the "
          +(stringp(token_type) ? token_type : "")
          +" amulet around "+POSSESSIVE(TP)+" neck.\n",TP);
      return 1;
  }
  return "You try to wear the amulet, but it just drops off!\n";
}
