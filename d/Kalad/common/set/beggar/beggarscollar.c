 /*****************************************************************************
*  /d/Kalad/common/set/beggar/beggarscollar.c
*
*  beggarscollar File for Beggars Set
*
*  Created Oct 20th 2020, Greneth
*
*  Info  : Discolored Copper Collar
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
   set_name("collar");
   set_adj("discolored");
   add_adj("copper");
   set_short("discolored copper collar");
   set_long("What was once a beautiful piece of jewelery has been "
   + "bested by the sands of time. Verdigris has set into the "
   + "twisted copper causing it to be littered with greenish, "
   + "spotted hues. You can somewhat make out some intricate "
   + "designs carved into the metal, but what they once were "
   + "no one will ever know.\n");

   set_at(A_NECK);
   set_ac(1);
   set_af(TO);

	add_prop(OBJ_S_SET_ITEM, "beggars_set");
   add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
   add_prop(MAGIC_AM_MAGIC,({30,"enchantment"}));
   add_prop(MAGIC_AM_ID_INFO,({"Though most of the enchantment has "
   + "been lost what is left should enhance your haggling and appraisal "
	+ " skills.\n",20}));
   add_prop(OBJ_S_WIZINFO,"Adds 30 points of Trading and Appraise Value "
	+ "to the wearer.\n");
   add_prop(OBJ_I_WEIGHT,300);
   add_prop(OBJ_I_VOLUME,100);
   add_prop(OBJ_I_VALUE,1000);
   add_prop(OBJ_M_NO_SELL, "What am I supposed to do with this hunk "
	+ "of metal?.\n");
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
	object skill, skill2;
   object *invns = all_inventory(TP);

   if (TP->query_average() > 154) 
	{
		return "You refuse to wear such a degrading thing.\n";
	}

   write("You feel invigorated as the collar latches around "
   + "your neck.\n");
	say(QCTNAME(TP) + " attaches the " + short() + " around their neck.\n");

   skill = E(ob)->query_skill_extra(SS_TRADING);
   E(ob)->set_skill_extra(SS_TRADING,skill +30);

   skill2 = E(ob)->query_skill_extra(SS_APPR_VAL);
   E(ob)->set_skill_extra(SS_APPR_VAL,skill2 + 30);

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
   int skill,skill2;

   set_this_player(query_worn());

   write("You feel a brief moment of loss as you remove the collar.\n");
	say(QCTNAME(TP) + " removes the " + short() + " from around their "
	+ "neck.\n");

   skill = TP->query_skill_extra(SS_TRADING);
   TP->set_skill_extra(SS_TRADING,skill - 30);

   skill2 = TP->query_skill_extra(SS_APPR_VAL);
   TP->set_skill_extra(SS_APPR_VAL,skill2 - 30);

   TP->remove_prop("_live_i_beggars_set");
   check_set_bonus(TP, "beggars_set");

   return 1;
}