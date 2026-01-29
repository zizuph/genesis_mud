/* created by Aridor 07/11/93 */
/* changed by Korat */

inherit "/std/object";

#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include <macros.h>

/* each cloud can only spread once to neighbour rooms */
int has_spread = 0;

create_object()
{
   set_name("acid");
   add_name("cloud");
   set_name("cloud");
   set_adj("rust-red");
   add_adj("acidios");
   set_long("The thick, rust-red acid cloud envelopes you in "+
      "a nauseating embrace, making your breathing become "+
      "shallow and hard. The acidious cloud seems to eat its way through "+
      "your equipment, slowly.\n");
   add_prop(OBJ_I_WEIGHT, 20000);
   add_prop(OBJ_I_VOLUME, 200000);
   add_prop(OBJ_M_NO_GET, "You cannot take a cloud!.\n");
   add_prop(OBJ_I_RES_ACID, 100);
   add_prop("_korat_acid_is_main_cloud",1);
   
   set_alarm((itof(random(80)+30)), 0.0, "evapourate");
   set_alarm(4.0, (itof(random(4)+8)), "hurt_everyone_around");
}

/* function: Evapourate
* description: removes this cloud from the room.
*/
void
evapourate()
{
   this_object()->change_prop(CONT_I_NO_REM, 0);
   tell_room(environment(this_object()), "The acidious cloud "+
      "drifts away slowly.\n");
   this_object()->remove_object();
}

/*
* function: hurt_it
* description: gives damage to all livings inside the cloud.
* arguments: the living to damage
*/
void
hurt_it(object livin)
{
   object co;
   int hitp;
   string str;
   hitp = livin->query_hp();
   write ("b" + hitp);
   co = livin->query_combat_object();
   if (hitp <42)
      hitp = -random(hitp+1);
   else if (hitp < 550)
      hitp = -hitp / 2 - 1;
   else
      hitp = -250;
   
   /*hitpoint modifier on RES_ACID:*/
      hitp -= hitp * (livin->query_prop(OBJ_I_RES_ACID) + livin->query_magic_res(MAGIC_I_RES_ACID));
   
   hitp /= 6;
   
   if (hitp > 0)
      hitp = 0;
   else
      {
      if (hitp > -40)
         str = "a little ";
      else if (hitp > -100)
         str = "partly ";
      else if (hitp > -200)
         str = "badly ";
      else
         str = "very badly ";
      tell_object(livin,"You choke and gasp for air, feeling yourself "+
         str + "damaged by the acidious cloud.\n");
   }
   livin->heal_hp(hitp);
   co->cb_add_panic(-hitp / 4);
   if (!livin->query_ghost())
      livin->do_die(this_object());
}


/*
* function destroy_it
 * description: removes object <obje>
*/
void
destroy_it(object obje)
{
   tell_room(environment(obje), "The " + obje->short() + " is dissolved by the acidious clud.\n");
   /* moves the inventory of <obje> to the room. */
   obje->move_all_to(environment(obje));
   obje->remove_object();
}

/*
* function: hurt_everyone_around
* description: gives damage to all living in the room of the cloud
*/
void
hurt_everyone_around()
{
   int i;
   object *things;
   mixed *exits;
   object cloud;
   int did_hurt_someone = 0;
   seteuid(getuid(this_object()));
   things = all_inventory(environment(this_object()));
   for (i = 0; i < sizeof(things); i++)
   {
      /* we check if they are resistant to acid.*/
         if (things[i]->query_prop(OBJ_I_RES_ACID) > random(100)) break;
      /* undeads doesnt really breath do they ... lucky them */
      if (things[i]->query_undead() >0) break;
      /* only damage livings */
      if (things[i]->query_prop(LIVE_I_IS))
         {
         hurt_it(things[i]);
         did_hurt_someone = did_hurt_someone + 1;
        }
      else
         {
         if (!random(4) && things[i]->query_prop(OBJ_I_VOLUME) <= 5000
               && things[i]->query_prop(OBJ_I_WEIGHT) <= 5000 && 
            !things[i]->query_prop(MAGIC_AM_MAGIC))
         destroy_it(things[i]);
        }
   }
   
   if (did_hurt_someone > 1)
      tell_room(E(TO),"You notice that the others seems to be coughing "+
      "loudly.\n");

   if (random(10)) return;
   
   /* let the cloud spread out to all exits */
   if(query_prop("_korat_acid_is_main_cloud") == 0) return; /* let only main cloud spread */
   /* ok, lets spread it */
   if(has_spread) return;
   has_spread = 1;
   exits = E(TO)->query_exit();
   if(!sizeof(exits))
      return;
   for (i=0;i<sizeof(exits);i+=3)
   {
      cloud = clone_object(CPASS(dwarf/obj/acid));
      cloud -> add_prop("_korat_acid_is_main_cloud",0);
      cloud -> move(exits[i]);
   }
   tell_room(E(TO),"The acidious cloud seems to spread further out.\n");
}

