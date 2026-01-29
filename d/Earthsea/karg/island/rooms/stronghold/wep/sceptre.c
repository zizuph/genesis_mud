inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

#define DEBUG(x) find_player("ged")->catch_msg(x+"\n")

int griped=0;

void create_weapon()
{
 set_name("sceptre");
 add_name("club");
 add_name("weapon");
 set_adj("golden");
 set_wt(W_CLUB);
 set_dt(W_BLUDGEON);
 set_pen(38+random(4));
 set_hit(38+random(4));
 set_hands(W_RIGHT);
 set_wf(TO);

 add_prop(OBJ_I_WEIGHT,4100);
 add_prop(OBJ_I_VOLUME,4100);
 add_prop(OBJ_I_VALUE,1);

 add_cmd_item("sceptre","grip","@@grip");
 add_cmd_item("sceptre","ungrip","@@ungrip");

 set_long("This sceptre is used by highest of karg commanders. "+
   "It is done of good steel and covered with gold. As soon as you "+
   "grip the sceptre it will be firmly held in your hand , disabling "+
   "your enemies to disarm you.\n");
}

int grip()
{
 object wldr=query_wielded();

 NF("You need to wield it first.\n");
 if(!wldr) return 0;

 NF("But "+short()+" is already griped by you.\n");
 if(griped) return 0;

 griped=1;
 add_prop(OBJ_M_NO_DROP,"You try to unwield the "+short()+", but "+
   "your firm grip does not let you. You need to <ungrip> the sceptre "+
   "first.\n");
 wldr->catch_msg("You grip the "+short()+" firmly in your right "+
   "hand.\n");
 tell_room(ENV(wldr),QCTNAME(wldr)+" firmly grips the "+short()+
   " in "+POS(wldr)+" right hand.\n",wldr);
 return 1;
}

int ungrip()
{
 object wldr=query_wielded();

 NF("You need to wield it first.\n");
 if(!wldr) return 0;

 NF("But "+short()+" is not griped by you.\n");
 if(!griped) return 0;

 griped=0;
 remove_prop(OBJ_M_NO_DROP);
 wldr->catch_msg("You ungrip the "+short()+".\n");
 tell_room(ENV(wldr),QCTNAME(wldr)+" ungrips the "+short()+".\n",wldr);
 return 1;
}

mixed wield(object weapon)
{
 set_alarm(0.1,0.0,&grip());
 return 0;
}

mixed unwield(object weapon)
{
 if(!previous_object(-1)) ungrip();

 if(griped) return "You try to unwield the "+short()+", but your "+
   "firm grip does not let you. You need to <ungrip> the sceptre "+
   "first.\n";

 return 0;
}
