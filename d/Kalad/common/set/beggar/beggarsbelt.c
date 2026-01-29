 /*****************************************************************************
*  /d/Kalad/common/arm/set/beggar/beggarsbelt.c
*
*  beggarsbelt File for Beggars Set
*
*  Created Oct 20th 2020, Greneth
*
*  Info  : Frayed Rope-Belt
*
*  Credit: Mirandus, Shanoga
 *****************************************************************************/

 /*****************************************************************************
*  Includes
 *****************************************************************************/
#include "/w/cedivar/beg/defs.h";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"

 /*****************************************************************************
*  Inherits
 *****************************************************************************/
inherit "/d/Kalad/std/armour.c";
inherit "/w/cedivar/beg/set_bonus";

 /*****************************************************************************
*  Prototypes
 *****************************************************************************/
int set_pieces_worn = 0;

 /*****************************************************************************
*  Function name: create_armour
*  Description  : Creates the armour
 *****************************************************************************/
void
create_armour()
{

   ::create_armour();
   set_name("rope-belt");
	add_name("belt");
	add_name("_beggars_set_belt");
   set_adj("frayed");
   set_short("frayed rope-belt");
   set_long("A plain, simple piece of rope that someone decided "
	+ "to use as a belt. The ends are frayed and there is nothing "
	+ "noticeable about it other than a worn spot where something "
	+ "was probably attached.\n");


   set_at(A_WAIST);
   set_ac(5);
   set_af(TO);
    
	add_prop(OBJ_S_SET_ITEM, "beggars_set");
	add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,100);
   add_prop(OBJ_I_VALUE,1000);
	add_prop(OBJ_M_NO_SELL, "What do I want an old piece of rope for?\n");
}

 /*****************************************************************************
*  Function name: wear
*  Description  : Mask of the parent function to perform a average level check, 
*                 apply skill bonuses and count the number of set pieces worn
*  Argument     : object ob - The armour to wear
 *****************************************************************************/
public mixed
wear(object ob)
{
   object *invns = all_inventory(TP);

   if (TP->query_average() > 154) 
	{
		return "You refuse to wear such a degrading thing.\n";
	}

	write ("With a double loop and a pull the belt rests snugly in "
	+ "place.\n");
	say(QCTNAME(TP) + " double loops their " + short() + " and pulls "
	+ "it snugly in place.\n");

   set_pieces_worn = 0;

   foreach (object invn: invns)
   {
      if (invn->query_worn())
      {
         if (invn->query_prop(OBJ_S_SET_ITEM) == "beggars_set")
				set_pieces_worn += 1;
      }
   }

   if (set_pieces_worn == 3)
   {
      TP->add_prop("_live_i_beggars_set", 1);                                              
      write("You're wearing the whole set.\n");
   }
   else
   {
      TP->add_prop("_live_i_beggars_set", 0);
      write("You are missing one or more pieces to the set.\n");
   }
    
   check_set_bonus(TP,"beggars_set");
    
   return 1;
}

 /*****************************************************************************
*  Function name: remove
*  Description  : Mask of the parent function to perform a removal of bonus
*                 skills and remove the number of set items on the counter
*  Argument     : object ob - The armour to remove
 *****************************************************************************/
public mixed
remove(object ob)
{
	write("You untie the belt and remove it.\n");
	say(QCTNAME(TP) + " unties their " + short() + ".\n");
   TP->remove_prop("_live_i_beggars_set");
   check_set_bonus(TP, "beggars_set");

	return 1;
}