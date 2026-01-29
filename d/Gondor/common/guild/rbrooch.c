#pragma save_binary

inherit "/d/Gondor/common/guild/lib/rtoken";
#include <wa_types.h>
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

create_token()
{
  set_name("brooch");
  add_name(({"ranger_brooch", "North_Ranger_Brooch"}));
  set_adj("star-shaped");
  set_at(A_NECK);
  seteuid(getuid(TO));
}

string set_token_short()
{
  if (TP == environment(TO)) 
      return token_type+" star-shaped brooch of the Rangers of the North";
  return token_type+" star-shaped brooch";
}  

string set_token_long()
{
    if (TP == environment(TO)) 
    {
        if (is_ranger(TP))
            return BSN("This is an brooch of "+token_type+" shaped like a rayed star. "+
                   "It is the membership token of the Rangers of the North. "+
                   "On the backside is enscribed: "+ranger_name+", Ranger of the North.");
        return BSN("This is a brooch of "+token_type+" shaped like a rayed star. "+
               "On the backside is enscribed: "+ranger_name+", Ranger of the North.");
    }
    if (is_ranger(TP))
        return BSN("It is an brooch of "+token_type+" shaped like a rayed star, the "+
               "token of the Rangers of the North, which someone must have dropped.");
    return BSN("It is an brooch of "+token_type+" shaped like a rayed star.");
}

wear(object ob)
{
  if (is_ranger(TP)) 
  {
      write("You wear the "+token_type+" brooch upon your left shoulder.\n"+
            "It feels good to be back with the Rangers of the North.\n");
      say(QCTNAME(TP)+" wears the "
          +(stringp(token_type) ? token_type : "")
          +" star-shaped brooch upon "+POSSESSIVE(TP)+" left shoulder.\n",TP);
      return 1;
  }
  return "You try to wear the brooch, but it just drops off!\n";
}
