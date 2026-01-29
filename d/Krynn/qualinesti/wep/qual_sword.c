/*
 * File : qual_sword.c
 * Qualthas longsword.
 *
 * Blizzard, 02/2003
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include "../local.h"

create_weapon()
{
   set_name(({"broadsword", "sword"}));
   set_short("jeweled silvery broadsword");
   set_adj( ({"light", "jeweled", "silver", "broad", "silvery" }) );
   set_long("This is an extremely well-crafted blade of a strong, " +
       "brilliantly shining metal. It appears to be razor-sharp, and " +
       "is surprisingly light for its size. its wide blade is " +
       "engraved with sinuous runes up half its length. The straight " +
       "hilt and crossguards are inset with gold and small jewels.\n");
       
   add_item("jewels", "There are several small jewels placed along the " +
       "hilt and crossguards.\n");
   add_item("hilt", "The hilt of this sword is inset with a few small " +
       "jewels.\n");
   add_item("runes", "The runes adorning the blade are obviously elven, " +
       "but you are not able to understand them. Maybe they are just " +
       "a decoration.\n");
       
   set_default_weapon(36, 37, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
   set_wf(TO);
   add_prop(OBJ_I_VOLUME, 1800);
   add_prop(OBJ_I_WEIGHT, 5000);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(36,35) + 800);
   
}

int 
wield_check(object ob)
{
    if ( query_wielded()->query_npc() )
    {
        set_hit(45);
        set_pen(46);
        query_wielded()->update_weapon(TO);
        
        return 1;
    }
}

mixed
wield(object ob)
{
    if ( !interactive(TP) )
    {
        set_alarm(1.0, 0.0, &wield_check(TO));
        return 1;
    }
}

int
unwield(object what)
{
    set_hit(36);
    set_pen(37);
    query_wielded()->update_weapon(TO);
    
    return 0;
}
  