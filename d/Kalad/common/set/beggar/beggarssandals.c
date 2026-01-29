 /*****************************************************************************
*  /d/Kalad/common/arm/set/beggar/beggarssandals.c
*
*  beggarssandals File for Beggars Set
*
*  Created Oct 20th 2020, Greneth
*
*  Info  : Worn-out Sandals
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
static int				fatigue_alarm;

 /*****************************************************************************
*  Function name: create_armour
*  Description  : Creates the armour
 *****************************************************************************/
void
create_armour()
{

   ::create_armour();
   set_name("sandals");
   set_adj("worn-out");
   set_short("pair of worn-out sandals");
	set_pshort("pairs of worn-out sandals");
   set_long("You can't exactly tell what these used to be but "
	+ "they have now turned into some odd creation that resembles "
	+ "a pair of sandals. Multiple split straps are along the edge "
	+ "of the soles and travel up the heel to just above the ankle. "
	+ "The bottom of the sole however is littered with studs, though "
	+ "you're not sure as to why.\n");


   set_at(A_FEET);
   set_ac(10);
   set_af(TO);

	add_prop(OBJ_S_SET_ITEM, "beggars_set");
   add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
   add_prop(MAGIC_AM_MAGIC,({30,"enchantment"}));
   add_prop(MAGIC_AM_ID_INFO,({"You're not sure what material these "
	+ "sandals are made of but they feel ridiculously comfortable. You "
	+ "get the sense that you could travel a long distance without tiring.\n",20}));
   add_prop(OBJ_S_WIZINFO,"Restores fatigue on a timer.\n");
    
	add_prop(OBJ_I_WEIGHT,300);
   add_prop(OBJ_I_VOLUME,300);
   add_prop(OBJ_I_VALUE,1000);
	add_prop(OBJ_M_NO_SELL, "I don't want your smelly sandals!\n");
}

 /*****************************************************************************
*  Function name: alarm_function
*  Description  : Alarm that repeats every 5 seconds to give +1 fatigue
 *****************************************************************************/
void alarm_function()
{

   TP->add_fatigue(1);

   set_alarm(5.0, 0.0, &alarm_function());

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

	write ("You wear the sandals, they are extremely comfortable and "
	+ "your feet thank you.\n");
	say(QCTNAME(TP) + " wears the " + short() + " with a satisfied sigh.\n");

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
	write ("You unstrap the sandals from your feet.\n");
	say(QCTNAME(TP) + " removes their " + short() + ".\n");
   TP->remove_prop("_live_i_beggars_set");
   check_set_bonus(TP, "beggars_set");

	return 1;
}