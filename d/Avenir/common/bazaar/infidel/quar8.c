
// file name: quar8
// creator: Ilyian (October 9, 1995)
// last update: Cirion, Jan 1996, added the spirits to protect
//              Nochipa
// purpose: Quarters in the Infidel Hideout where Nochipa lives
// note:
// bug(s):
// to_do:

inherit "/d/Avenir/common/bazaar/infidel/infidel";
#include "infidel.h"

void reset_room();
object nochipa;
static object *spirit = allocate(6);

void make_spirit(int i);

void
create_room()
{
   quar_long("using set_long");
   set_long("High walls and a large altar in the north wall "
           +"make this place seem sacred. On the floor have "
           +"been carved numerous designs that swirl together "
           +"in indescernible patterns.\n");
   set_short("sanctuary");

   AI(({"altar"}),"The altar is low and made from dark "
           +"granite. It must have taken massive effort "
           +"to get it in here, for the stone does not "
           +"look indiginous to the area. The top of the "
           +"altar is smooth and well-polished.\n");
   AI(({"floor","swirl","swirls","pattern","patterns","design",
            "designs"}),"The designs on the floor are "
           +"strange and almost hypnotizing.\n");
   hall_exit("15","southwest");

   reset_room();
}

void
reset_room()
{
    int i;
   if(!nochipa)
     {
        nochipa = clone_object(MON+"nochipa");
        nochipa->arm_me();
        nochipa->move(TO);
     }

   for(i=0; i<5 ; i++ )
     {
        set_alarm(itof(i+1), 0.0, &make_spirit(i));
      continue;
     }
}

void make_spirit(int i)
{
   if(!spirit[i])
     {
      spirit[i] = clone_object(MON+"spirit");
      spirit[i] -> move(TO);
      }
    return;
}

void attacker(object who)
{
   int i;
   for(i=0; i<3 ; i++ )
     {
       if(spirit[i]->query_attack() || !spirit[i] || !present(spirit[i], TO))
         continue;
       tell_object(who, "You feel a rush of wind blow between "
              +"you and "+nochipa->query_the_name()+".\n");

       spirit[i]->command("kill "+who->query_real_name());
       spirit[i]->remove_prop(OBJ_I_INVIS);
       who->attack_object(spirit[i]);
      return;
     }
}
