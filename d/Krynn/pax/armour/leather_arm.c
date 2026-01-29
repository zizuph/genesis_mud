/*
   Sla Mori, leather armour for the zombies in the crypt.

   leather_arm.c
   -------------

   Coded ........: 95/04/26
   By ...........: Jeremiah

   Latest update : 95/04/26
   By ...........: Jeremiah

*/

inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Krynn/pax/local.h"


void
create_armour()
{
   set_name(({"leather armour","leather"}));
   set_short("leather armour");
   set_long("This is a hardened leather armour. The front side is " +
            "decorated with beautiful ornaments and pieces of jewelry. " + 
            "The shoulders are covered with pieces of chainmail, " +
            "adding some extra protection. This must once have been " +
            "a wonderful piece of armour, but time has left its marks. " +
            "The ornaments and jewelry looks dull and its former " +
            "splendor has faded.\n");

   set_adj("hardened");
   set_ac(15);
   set_at(A_BODY);
}


string
query_recover()
{
    return PARMOUR + "leather_arm.c:" + query_arm_recover();
}


void
init_recover(string arg)
{
    init_arm_recover(arg);
}
