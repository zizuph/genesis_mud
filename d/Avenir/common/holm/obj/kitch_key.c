// kitchen chest key  
// creator(s):         Lilith  1/29/97
// last update: 
// purpose:            For opening the lock on kichen chest
// bug(s):
// to-do:


inherit "/std/key";

#include "../holm.h"

void
create_key()
{

    set_short("cast-iron key");
    set_adj(({"cast-iron", "iron"}));
    set_name("key");
    set_long("This key made from cast iron.\n");

    set_key(KITCH_KEY);
}
