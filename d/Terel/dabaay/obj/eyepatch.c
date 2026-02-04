/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * eyepatch.c
 *
 * Dabaayhab's eyepatch.
 *
 * Goldberry February 2000
 */

#include <wa_types.h>
#include <ss_types.h>
#include "/d/Terel/include/Terel.h"

#define PARRY_MOD 10
#define DEF_MOD   10
#define AWARE_MOD 20

inherit "/d/Terel/std/wearable_item";

int p_mod, d_mod, a_mod;

void
create_terel_wearable_item()
{
    set_name("eyepatch");
    set_adj("black");
    set_pname("eyepatches");
    set_short("black eyepatch");
    set_pshort("black eyepatches");

    set_terel_wearable_item_size(ANY_SIZE);
    set_slots(A_EYES);
    set_looseness(0);
    set_layers(1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC,({60,"enchantment"}));
    add_prop(OBJ_S_WIZINFO,
        "Increases awareness by 20, and decreases defense and parry "+
        "by 10 each.\n");

    add_prop(MAGIC_AM_ID_INFO,({
        "This item will increase the wearer's awareness of their "+
        "surroundings.\n",40}));

    set_long(
        "A triangle of black leather with a leather thong attached "+
        "to it. It appears to be an eyepatch.\n");


    add_prop(OBJ_I_WEIGHT, 30);
    add_prop(OBJ_I_VOLUME, 60);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "conjuration" }));
    add_prop(OBJ_I_VALUE, 1600);
}

public mixed
wear_terel_item(object obj)
{
  if(!(TP->query_npc()))
   {
    if(TP->query_skill(SS_AWARENESS) > (100 - AWARE_MOD))
      a_mod = 100 - TP->query_skill(SS_AWARENESS);    
    else
      a_mod = AWARE_MOD;
    if(TP->query_skill(SS_PARRY) < PARRY_MOD)
      p_mod = TP->query_skill(SS_PARRY);
    else
      p_mod = PARRY_MOD;
    if(TP->query_skill(SS_DEFENCE) < DEF_MOD)
      d_mod = TP->query_skill(SS_DEFENCE);
    else
      d_mod = DEF_MOD;
    
    TP->set_skill_extra(SS_AWARENESS,TP->query_skill_extra(SS_AWARENESS)+a_mod);
    TP->set_skill_extra(SS_PARRY, TP->query_skill_extra(SS_PARRY)-p_mod);
    TP->set_skill_extra(SS_DEFENCE, TP->query_skill_extra(SS_DEFENCE)-d_mod);
    TP->add_prop("Hand_patch",1);
    TP->catch_tell("Your vision becomes clearer but your peripheral sight "+
                   "seems to be diminished.\n");
   }

    return 0;
}

int
remove_terel_item(object item)
{
  if(!(TP->query_npc()))
   {
    TP->set_skill_extra(SS_AWARENESS,TP->query_skill_extra(SS_AWARENESS)-a_mod);
    TP->set_skill_extra(SS_PARRY, TP->query_skill_extra(SS_PARRY)+p_mod);
    TP->set_skill_extra(SS_DEFENCE, TP->query_skill_extra(SS_DEFENCE)+d_mod);
    TP->remove_prop("Hand_patch");
   }

    return 0;
}

