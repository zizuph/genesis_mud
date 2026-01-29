/*
*    Key for the beholders chest.
*/

#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
inherit "/std/key";
#define MITHAS_FOREST_CHEST "_mithas_forest_key"


void
remove_the_key()
{
    write("The "+short()+" turns into dust, and disappears.\n");
    this_object()->remove_object();
}

void
create_key() 
{
   ::create_key();
   set_name("key");
   set_short("slimy silver key");
   set_adj("silver");
   add_adj("slimy");
   set_long("This was once a beautiful silver "+
            "key, but now it's covered with thick green-brown "+
            "slime.\n");
   set_alarm(100.0, 0.0, &remove_the_key());
   set_key(MITHAS_FOREST_CHEST);
}

