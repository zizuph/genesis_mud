#include "/d/Roke/common/defs.h"
#include <composite.h>
#include <macros.h>
#include "/d/Roke/common/qbits.h"
#include <stdproperties.h>
#include "/d/Roke/common/qbits.h"

inherit "/std/leftover";



object farmer;


void
create_leftover()
{
    set_name(({"skull", "wolf's skull"}));
    add_name("rokeskull");
    set_long("The skull of a grey wolf, it would look good on a helm.\n");
    set_decay_time(10);
    set_amount(1500);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 2);


}


init()
{
    add_action("give_skull", "give");
    ::init();
}
 

give_skull(str)
{

object rokeskull;

seteuid(getuid());
farmer = clone_object(ATUAN + "cape/monsters/farmer");

if((str == "skull to farmer") || (str == "wolf skull to farmer")){

   if(!QDONE(GROUP1,WOLFQUEST))
    {
      write(BS("The farmer shakes your hand and thanks you.",70));
      TP->catch_msg("You feel more experienced.\n");
      TP->add_exp(2000);
      TP->set_bit(GROUP1,WOLFQUEST);
        QLOG("wolfquest");

        if(farmer=present("rokefarmer",environment(TP)))
        {
        farmer->remove_object();
        }
        if(rokeskull = present("rokeskull",TP))
                rokeskull->remove_object();
      return 1;
    }
  else
    {
      write(BS("The farmer thanks you again and smiles happily.",70));
        if(farmer=present("rokefarmer",environment(TP)))
        {
        farmer->remove_object();
        }
        remove_object();
      return 1;
    }
}

return 0;
}
