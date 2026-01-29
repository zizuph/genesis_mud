/* ctower/obj/bsaph.c is cloned by ctower/all1.c */
inherit "/d/Emerald/ctower/obj/gem_base";

#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>
#include "../ctower.h" 

void
create_gem()
{
  set_name("sapphire");
  add_name("ctower_bsaph");
  add_adj("black");
  set_long("This is a deep black sapphire gem that tingles when held.\n");

  add_prop(OBJ_I_VALUE, 984);
}
 
int
invoke(string str)
{
  object earth, air, fire, water, *who, newgem;
 
  notify_fail("Invoke what?\n");
  if (!strlen(str))
  {
    return 0;
  }

  if (str == "all" || str == "all gems" || str == "gems") 
  {
    if ((earth = present("earth_gem", this_player())) &&
        (water = present("water_gem", this_player())) &&
        (fire  = present("fire_gem",  this_player())) &&
        (air   = present("air_gem",   this_player())))
    {
      earth->remove_object();
      air  ->remove_object();
      fire ->remove_object();
      water->remove_object();

      if (environment(this_player())->query_transform()) 
      {
        setuid();
        seteuid(getuid());

        newgem = clone_object(CTOWER_OBJ + "starsaph");
        newgem->move(environment(this_player()), 1);

        write("You invoke all of the gems at once...\n");
        write( "The power of all the elements is unleashed, "+
            "causing the gems to explode in all their primal fury!  "+
            "However, all the energy is siphoned into the center of the "+
            "room and compacted into a small gem--a star sapphire!\n" );
        say(QCTNAME(this_player())  + " unleashes the power " +
            "of all the elements, causing the gems to explode in all " +
            "their primal fury!  However, all the energy is siphoned " +
            "into the center of the room and compacted into a small " +
            "gem--a star sapphire!\n");
              
        remove_object();
        return 1;
      }

      write("You invoke all of the gems at once...\n");
      write( "All of the gems release their power in one burst "+
          "of tremendous energy.  Steaming chunks of lava are hurled in "+
          "all directions.  The results of the uncontrolled power of " +
          "the elements.\n");
      say(QCTNAME(this_player()) + "screams as steaming lava explodes from " + 
          this_player()->query_possessive() + " hands!\n");
 
      who = FILTER_LIVE(all_inventory(environment(this_player())));
      if (sizeof(who))
      {
        who->catch_tell("You are hurt by the explosion!\n");
        who->heal_hp(-100);
        this_player()->heal_hp(-100);

        filter(who, &operator(>=)(0) @ &->query_hp())->do_die(this_object()); 
      }

      remove_object();
      return 1;
    }
    else
    {
      write("Nothing happens.\n");
      return 1;
    }
  }
 
  return 0;
}
