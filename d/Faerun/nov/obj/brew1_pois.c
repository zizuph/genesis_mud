
#include <poison_types.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../nov.h";

inherit "/std/poison_effect";



int
do_neffect1()
{
      object shadow;

  
  
       
        setuid();
         seteuid(getuid());

         shadow = clone_object(NOV_DIR +"shadows/brew1_sh");
         shadow->shadow_me(this_player());
         shadow->init_brew1_shadow(200);
         write("The brew of lifestealing takes effect!\n");
         
         return 1;
}
         

 
   
  

   
   




void 
create_poison_effect()
{
   ::create_poison_effect();
   set_interval(10);
   set_time(3);
   set_damage(({ POISON_HP, 5, }));
   set_strength(1);
   set_poison_type("nbrew1");
   add_prop(OBJ_M_NO_DROP,"");
   
        if (this_player()->query_guild_name_lay() != GUILDNAME)
    	{
    		return;
    	}

        if (this_player()->query_prop(IHAVEBREW1))
    	{
    		return;
    	}
   
   
   set_alarm(0.1,0.0, &do_neffect1());
}
