 /*****************************************************************************
*  /d/Kalad/common/set/beggar/beggarsovercoat.c
*
*  beggarsovercoat File for Beggars Set
*
*  Created Oct 20th 2020, Greneth
*
*  Info  : Filthy Tattered Overcoat
*
*  Credit: Mirandus, Shanoga
 *****************************************************************************/

 /*****************************************************************************
*  Includes
 *****************************************************************************/
#include "/d/Kalad/common/set/beggar/defs.h";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"

 /*****************************************************************************
*  Inherits
 *****************************************************************************/
inherit "/d/Kalad/std/armour.c";
inherit "/d/Kalad/common/set/beggar/set_bonus";

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
   set_name("overcoat");
   set_adj("filthy");
	add_adj("tattered");
   set_short("filthy tattered overcoat");
   set_long("Stitched for durability rather than looks this "
	+ "overcoat has easily proven its worth. Multiple unknown "
	+ "stains and tears are scattered from top to bottom. "
	+ "Whatever material was used to create it must be special.\n");


   set_at(A_ROBE);
   set_ac(30);
   set_af(TO);

	add_prop(OBJ_S_SET_ITEM, "beggars_set");
   add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
   add_prop(MAGIC_AM_MAGIC,({30,"enchantment"}));
   add_prop(OBJ_I_RES_MAGIC, 10);

   add_prop(MAGIC_AM_ID_INFO,({"You recognize the material as wool "
	+ "from a rare Bastite Sheep. Which is said to be tough like "
	+ "leather yet pliable and slightly resistant to magic.\n",20}));
   add_prop(OBJ_S_WIZINFO,"Enchanted for better protection AC/30 "
	+ "and protection against Magic by 10.\n");
    
	add_prop(OBJ_I_WEIGHT,1000);
   add_prop(OBJ_I_VOLUME,1000);
   add_prop(OBJ_I_VALUE,1000);
	add_prop(OBJ_M_NO_SELL, "I don't want these rags!\n");
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

	write ("You wear the overcoat, which fits surprisingly well.\n");
	say(QCTNAME(TP) + " wears the " + short() + ", it fits them well.\n");

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
	write ("You remove the overcoat and feel more vulnerable now.\n");
	say(QCTNAME(TP) + " removes their " + short() + ".\n");
   TP->remove_prop("_live_i_beggars_set");
   check_set_bonus(TP, "beggars_set");

	return 1;
}