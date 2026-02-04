inherit "/std/object.c";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>

#include "/d/Terel/include/Terel.h";



decay()
{
    object corpse;
    corpse = this_object();
    
    if(corpse)
    {
        tell_room(ETO, "The " + short() + " decays into dust.\n");
        corpse->remove_object();
        return 1;
    }
    return 0;
}


void
create_object()
{
   seteuid(geteuid(this_object()));
   
   set_name("corpse");
   set_pname("corpses");
   set_short("corpse of a white chicken");
   set_long("This is the dead body of white chicken.\n " +
      "You might be able to pluck its feathers.\n");
   
   add_prop(OBJ_M_NO_SELL,1);
   add_prop(OBJ_I_VALUE,2);
   add_prop(OBJ_I_WEIGHT, 1000);
   add_prop(OBJ_I_VOLUME, 400);
   add_prop("chicken_feathers",(random(20)+1));
   set_alarm(60.0, 0.0, decay);
   add_cmd_item(({"corpse","feather","chicken"}),"pluck","@@pluck");

}


pluck()
{
    object feather;
    object feathers;
    object ob;
    feathers=query_prop("chicken_feathers");

    if (feathers <= 0)
    {
         set_long("This is the dead body of white chicken.\n " +
            "Someone has plucked out its feathers.\n");
         write("There are no feathers left on this bird.\n");
         return 1;
     }
          add_prop("chicken_feathers", feathers -1);  
          seteuid(getuid(TO));
          ob = clone_object(CALATHIN_DIR + "farms/obj/feather");
          ob->move(TP);
          write("You pluck a feather from the corpse of a chicken.\n");
          say(QCTNAME(TP) + " pulls a feather from the corpse of a chicken.\n");
          return 1;
     
}

     
