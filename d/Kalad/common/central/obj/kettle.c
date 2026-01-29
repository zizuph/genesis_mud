/*
* A kettle that can contain water (or anything else)
   *
* modified from bucket.c by Dust
   *
* and modified again from pot.c Olorin, Apr 1993
   * 
* By Korat january 1995
*/

inherit  "/std/container";
#include "/d/Kalad/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define COFFEE_FILE "/d/Kalad/common/central/obj/coffee.c"
#define WATER_FILE "/d/Kalad/common/central/obj/water.c"
#define ROOM_HAS_WATER "_obj_i_contain_water"
#define COFFEE_STRENGTH "_coffee_type"

int water_inside;
int coffee_inside;
object water;
object coffee;


void
create_container()
{
   set_name("kettle");
   set_adj("iron");
   add_adj("coffee");
   add_name("_boiled_coffee_quest_kettle");
   set_long("This iron kettle is perfect for making coffee in. You "+
      "can smell the aroma of coffee from it, so this old kettle "+
      "have probably been used a lot.\n");
   add_prop(CONT_I_WEIGHT, 1000);
   add_prop(CONT_I_MAX_WEIGHT, 2500);
   add_prop(CONT_I_VOLUME, 1500);
   add_prop(CONT_I_MAX_VOLUME, 3000);
   add_prop(OBJ_I_VALUE, 200);
   add_prop(OBJ_M_NO_SELL,1);
   add_prop(CONT_I_TRANSP,1);
   add_prop(CONT_I_RIGID,1);
   add_prop("_korat_quest_kettle",1);
   coffee_inside = 0;
   water_inside = 0;
}

void
init()
{
   ::init();
   add_action("do_fill","fill",0); /* filling the kettle */
   add_action("do_pour","pour",0); /* pour water out */
   add_action("do_pour","empty",0); /* pour water out */
   add_action("do_drink","drink",0); /* drink water or coffee from kettle */
   add_action("do_cook","cook");     /* the actual cooking of it... */
   add_action("do_cook","boil");     /* with different syntax: */
      add_action("do_cook","heat");
}

int
do_fill(string str)
{
   seteuid(getuid());
   if (!str)
      {
      notify_fail("Fill what?\n");
      return 0;
   }
   if (parse_command(str,environment(TP), "'kettle' [with] 'water'") ||
         parse_command(str,environment(TP), "'water' [in] 'kettle'"))
   {
      if (volume_left() < 1000 || weight() > 2000)
         {
         notify_fail("But the kettle isn't empty...\n");
         return 0;
       }
      
      /* any water around here ? */
      if (environment(TP)->query_prop(ROOM_HAS_WATER) ||
            environment(TP)->query_prop(ROOM_I_TYPE) == ROOM_BEACH)
      {
         
         /* yes! Then lets put the water there....*/
         water_inside = 1;
         water = clone_object(WATER_FILE);
         if(!water->move(TO))
            TO->add_prop(OBJ_I_CONTAIN_WATER,1);
         
         write("You fill the kettle with water.\n");
         say(QCTNAME(TP) + " fills a kettle with water.\n");
         return 1;
       }
      
      /* no, so we give a fail message: */
      notify_fail("You look everywhere, but find no water.\n");
      return 0;
   }
   /* wrong syntax! */
   notify_fail("What do you want to fill with what?\n");
   return 0;
}

int
do_pour(string str)
{
   seteuid(getuid());
   notify_fail("Empty what?\n");
   if (!str) return 0;
   if (str != "kettle") return 0;
   notify_fail("But the kettle doesn't contain any liquid!\n");
   if (water_inside)
      {
      write("You pour the water from the kettle on the ground.\n");
      water_inside = 0;
      water->remove_object();
      TO->remove_prop(OBJ_I_CONTAIN_WATER);
      write("The water vanishes in the ground immediately.\n");
      return 1;
   }
   if (coffee_inside)
      {
      write("You pour the coffee from the kettle on the ground.\n");
      coffee_inside = 0;
      coffee->remove_object();
      TO->remove_prop(OBJ_I_CONTAIN_WATER);
      write("The coffee spreads out on the ground, and vanishes "+
         "after a while.\n");
      return 1;
   }
   return 0;
}

do_drink(string str)
{
   int drink_coffee;
   int drink_water;
   notify_fail("Drink what?\n");
   if(!str) return 0;
   
   notify_fail("Drink water from where?\n");
   if(str == "water") return 0;
   
   notify_fail("Drink coffee from where?\n");
   if(str == "coffee") return 0;
   
   notify_fail("Drink what from where?\n");
   drink_water = parse_command(str,environment(TP), "'water' [from] 'kettle'");
   drink_coffee = parse_command(str,environment(TP), "'coffee' [from] 'kettle'");
   
   if (drink_water) {
      notify_fail("But there is no water in the kettle.\n");
      if(!water_inside) return 0;
   }
   
   if (drink_coffee) {
      notify_fail("But there is no coffee in the kettle.\n");
      if(!coffee_inside) return 0;
   }
   
   if (drink_water)
      {
      notify_fail("The water is too much for you.\n");
      if(!TP->drink_soft(water->query_soft_amount())) return 0;
      
      write("You drink the water from the kettle.\n");
      say(QCTNAME(TP) + " drinks water from a kettle.\n");
      
      water_inside = 0;
      water->remove_object();
      TO->remove_prop(OBJ_I_CONTAIN_WATER);
      write("You feel refreshed.\n");
      return 1;
   }
   
   if (drink_coffee)
      {
      notify_fail("The coffee is too much for you.\n");
      if(!TP->drink_soft(coffee->query_soft_amount())) return 0;
      
      write("You drink the coffee from the kettle.\n");
      say(QCTNAME(TP) + " drinks coffee from a kettle.\n");
      
      coffee_inside = 0;
      coffee->remove_object();
      TO->remove_prop(OBJ_I_CONTAIN_WATER);
      write("Ahh that was good! You feel more awake now.\n");
      return 1;
   }
   notify_fail("Drink what from what?\n");
   return 0;
}

int
do_cook(string str)
{
   object *inv_kettle, *inv_room;
   object stove;
   status grains_inside;
   int i;
   int num_of_grains;
   
   num_of_grains = 0;
   grains_inside = 0;
   
   seteuid(getuid());
   notify_fail("Heat what?\n");
   if(!str)
      return 0;
   if (str != "water" && str != "coffee" && str != "kettle") return 0;
   inv_kettle = all_inventory(TO);
   for (i=0; i<sizeof(inv_kettle); i++){
      if(inv_kettle[i]->query_prop("_korat_quest_grains"))
         {
         grains_inside = 1;
         num_of_grains = inv_kettle[i]->num_heap();
        }
   }
   notify_fail("What? There is nothing inside the kettle to heat!\n");
   if (sizeof(inv_kettle) == 0)
      return 0;
   
   /* ok, something is inside it, so is the stove in the room? */
   notify_fail("You cannot heat it here! There is no stove to put it on.\n");
   if (!objectp(stove = present("stove", environment(TP))))
      return 0;
   notify_fail("The stove is not warm, so you cannot heat the kettle "+
         "there!\n");
   if (stove->query_prop(OBJ_I_LIGHT) < 1) return 0;
   
   /* Ahh finally! The stove is lit and the stove is here! */   
   write("You put the kettle on the stove "+
      "and watch it start to warm up.\n");
   tell_room(TO, QCTNAME(TP) + " puts a kettle on the stove and watches "+
      "it heat up.\n");
   
   notify_fail("The kettle starts to heat up; its edges begins to glow!\n"+
      "Something must be wrong...You take the hot kettle off the stove.\n");
   if (!water_inside) return 0;
   notify_fail("You watch the kettle heating up on the stove for a while. "+
         "Suddenly it starts to boil fiercly, spilling its content out "+
      "on the stove! The water quickly evaporates on the hot surface, so "+
      "you take the kettle off. What a mess! It fits the kitchen though.\n");
   if(sizeof(inv_kettle) > 2 && !grains_inside) return 0;
   notify_fail("After some time you bend over and sniff at the "+
         "kettle. It does start to smell like coffee, but "+
      "its not like what you expected ... you take the "+
      "kettle off the stove.\n");
   if(sizeof(inv_kettle) > 2 && grains_inside) return 0;
   notify_fail("You watch the kettle heating up on the stove for a while. "+
         "After a while you bend over and sniff at the kettle...doesn't smell "+
      "like coffee at all! A bit let down, you take the kettle off "+
      "the stove.\n");
   
   if (!grains_inside)
      return 0;
   
   /* ok...the coffee is made. Lets tell all of the event */
   /* and make the coffee */
   tell_room(TO,
      QCTNAME(this_player()) + " sniffs at the heating kettle " +
      "and then takes it off.\n");
   
   for (i=0; i<sizeof(inv_kettle); i++)
   inv_kettle[i]->remove_object();
   
   coffee = clone_object(COFFEE_FILE);
   if (coffee->move(this_object(), 1)) {
      write ("inside the brackets!!!!\n");
      coffee->remove_object();
   }
   write("The kettle starts to boil. You take it off the stove and "+
      "are delighted by the aroma from it.\n");
   coffee->add_prop(COFFEE_STRENGTH, num_of_grains);
   TO->add_prop(OBJ_I_CONTAIN_WATER,1);
   coffee_inside = 1;
   water_inside = 0;
   return 1;
}   

