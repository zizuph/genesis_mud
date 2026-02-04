/*
 * modified by Lilith Feb, 2008
 *  Stuff here in the treasure rooms are boring.
 *  Lets make them more interesting -- worthy
 *  of a King's treasure house.
 *
 * A magical dagger used to take down Darknight
 * can also be used to take down other evil boss 
 * npcs in Terel.
 */
inherit "/std/weapon";
inherit "/lib/keep";
#include "/d/Terel/include/Terel.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>  /* wa_types.h contains some definitions we want */

void
create_weapon()
{
    /* Set the name, short description and long description */
   set_name("dagger");
   set_short("blood stained dagger");
   set_long(break_string(
   "This dagger is the same dagger that was used by Mortock to " +
   "kill Darknight.  His blood still stains the blade.\n", 70));
   add_adj(({ "small", "blood stained" }));

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(20);
    set_pen(9);

    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_KNIFE); /* It's of 'knife' type */
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */
    add_prop (OBJ_I_VALUE,  200);
    add_prop (OBJ_I_WEIGHT, 500);
    add_prop (OBJ_I_VOLUME, 500);
    add_prop (OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop (MAGIC_AM_MAGIC,({ 80, "death" }));
    add_prop (OBJ_S_WIZINFO, 
	      ("This knife is a magical weapon from the treasure house "+
	       "of the King of Ribos. It was used to kill Darknight, " +
             "the predecessor of Mergula, and is designed to be very "+
             "effective against evil boss npcs in Terel, doing one-"+
             "quarter max health damage on a successful hit, which, "+
             "with 20 to_hit, won't happen very often. It is randomly "+
             "cloned to chests in the storerooms in /d/Terel/ribos/castle/ "+
             "and thus requires searching through 10 chests to find. "+
             "There is also an identical 'dud' version. Players will " +
	       "not know which is which unless they have magical "+
             "identify or they make a successful hit.\n"));

    add_prop (MAGIC_AM_ID_INFO,
	      ({("The "+ short() +" reeks of Death.\n",10,
		 "Which comes to the most evil beings in Terel.\n",20,
             "If only you can strike them with this knife!\n"),50 }));

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH); /* You can wield it in any hand. */
}


/* This can be used to kill evil boss npcs in Terel */
public varargs int
did_hit (int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    int res, special;

    if ((phurt > 0) && (enemy->query_prop(BOSS_NPC)))
    {
        query_wielded()->catch_msg("Your "+ short() +" slams into "+
            QTNAME (enemy)+" to the hilt!\n");
        enemy->catch_msg(QCTNAME (wielder) + " drives the " + short() +
            "deep into your flesh!\n");
        say(QCTNAME (wielder) + " drives the " + short() +
            " into "+ QTNAME (enemy) + "'s flesh.\n", ({ enemy, TP}));

        special = ((enemy->query_max_hp()) / 4);           
        enemy->hit_me(special, MAGIC_DT, TP, -1); 
    }
	
    return 1;
}
