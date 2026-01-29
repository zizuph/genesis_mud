/* 
 * Magical ring for Faerie.
 * Raises dis for newbies
 * Finwe, June 2001
 */

#pragma save_binary

inherit "/std/armour";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include <macros.h>
#include "defs.h"

#define RING_ID "_faerie_dis_ribbed_ring"

int added_skill = 2;
int newbie_max = 64, 
    ring_worn = 0;

void
create_armour()
{
    seteuid(getuid());

    if (!IS_CLONE)
      return;
   
    set_name("ring");
    add_name(RING_ID);
    set_adj("mithral");
    set_adj("ribbed");
    set_short("mithral ribbed ring");
    set_long("This is a ring made of mithral by expert silversmiths. It " +
        "has a few diagonal, vertical ribs that run around the outside " +
        "of it. The ring looks priceless and beautiful.\n");
       
    set_ac(0);            /* Not much use as armour, to be honest */
    set_at(A_ANY_FINGER);    /* This ring is worn around the fingers */
    set_wf(TO);
      
    add_prop(OBJ_I_WEIGHT, 60);  /* Weight 60g */
    add_prop(OBJ_I_VOLUME, 3);   /* Volume 3ml */
}

public string
query_recover()
{
    return 0;
}

void enter_env(object env, object from)
{
  ::enter_env(env, from);

  // we don't want more than one ring at a time
//    filter(all_inventory(env) - ({ this_object() }),         &->id(RING_ID))->remove_object(); 
}

int
wear(object arm)
{
    object tp=environment(arm);
    
    if(tp->query_average_stat() < newbie_max)
    {
        tp->catch_msg("As you put the ring on your finger, you feel bolder " +
            "about your environment.\n");
        tp->set_stat_extra(SS_DIS, added_skill);
/*
 * in case they grow and are no longer a 'newbie' they can remove the ring
 * and have the ring's dis value removed.
 */
        ring_worn = 1; 
        return 0;
    }
    else
    {
        tp->catch_msg("The ring appears useless to someone as experienced as you.\n");
        return 1;
    }
}

int
remove(object arm)
{
    object tp=query_worn();
    
    if(!living(tp)) return 0;

    if(ring_worn == 1)
    {
write(added_skill+"\n");
        TP->set_stat_extra(SS_DIS, -2);
        ring_worn = 0;
    }
        tp->catch_msg("You remove the ring, and everything looks normal.\n");

    return 1;

}
