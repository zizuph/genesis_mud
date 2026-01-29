/* magical,invisible armour for herb coded by Elizabeth Cook/Mouse */
/* February 1997 */

inherit "std/armour";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#define TP this_player() 

void create_armour()
{
   set_name("magic_invis_armour");
   set_no_show();
   add_prop(OBJ_M_NO_DROP,1);
   add_prop(OBJ_M_NO_GIVE,1);
   add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
   set_ac(3);
   set_at(A_MAGIC);
   set_af(this_object());
   add_prop(OBJ_I_WEIGHT,0);
   add_prop(OBJ_I_VOLUME,0);
}

int *
query_shield_slots()
{
   return ({ A_HEAD, A_BODY, A_L_ARM, A_R_ARM, A_LEGS});
}

void init()
{
   wear_me();
   set_alarm(600.0,0.0,&remove_object());
}

int wear(object ob)
{
   TP->catch_msg("You sense an aura of protection enveloping you.\n");
   return 1;
}

int remove(object ob)
{
   TP->catch_msg("You sense the aura of protection slipping away.\n");
   return 1;
}

