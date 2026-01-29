
/* 
   Wolfhelm for Calians. 
   Decent helms available at twice ordinary armour cost (no tangible
   special benefits - helms of the same quality and price are 
   available from the smith Bubba in Gelan). 

   Coded by Maniac, Jan 4 96.
 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include "defs.h"
#include CALIAN_HEADER

string wolfhelm_a;


int 
is_calian(object player)
{
    return (player->query_guild_name_occ() == GUILD_NAME);
}

void
set_wolfhelm_a(string s)
{
    if (stringp(wolfhelm_a))
        remove_adj(wolfhelm_a);
    wolfhelm_a = s; 
    set_adj(wolfhelm_a);
    set_short(wolfhelm_a + " wolfhelm");
}

string
query_recover()
{
  string rec;
  rec = MASTER + ":";
  rec += "#a#";
  rec += wolfhelm_a;
  rec += "#myend";
  rec += query_arm_recover();
  return rec;
}


void
init_recover(string arg)
{
  string foobar, wa;

  sscanf(arg, "%s#a#%s#myend%s",
                foobar, wa, foobar);
  set_wolfhelm_a(wa);
  init_arm_recover(arg);
}


/* Special wear effect, player is shadowed with "resonance" sound
   shadow when helm is worn. */
mixed
wear(object what)
{
    object s, tp;

    tp = this_player();

    if (tp->query_alignment() < 0) {
        tp->catch_msg("The " + short() + " bites you!\n");
        say("The " + short() + " bites " + QTNAME(tp) + "!\n");
        tp->heal_hp(-1);
        return "Looks like you can't wear it!\n";
    }

    if (!is_calian(tp)) {
        tp->catch_msg("The " + short() + " growls at you!\n");
        say("The " + short() + " growls at " + QTNAME(tp) + "!\n");
        return "Looks like you can't wear it!\n";
    }
        
    seteuid(getuid());
    s = clone_object(GLYKRON_SPECIALS+"resonance_shadow");
    s->shadow_me(tp);
    return 0;
}


/* Shield remove effect, "resonance" sound shadow is removed 
   when helm is removed.  */
mixed
remove(object what)
{
    wearer->remove_resonance_shadow();
    return 0;
}


void
create_armour()
{
    set_name("wolfhelm");
    if (!stringp(wolfhelm_a))
         set_wolfhelm_a("steel");
    add_name("helm");
    set_long("A grim helm crafted in the shape of a wolf's head. " +
           "The level of detail of its features suggest that " +
           "it is of fine workmanship. The eyes and mouth of the wolf " +
           "are set in the right positions for the sight and speech of " +
           "the wearer.\n"); 

    add_prop(OBJ_I_WEIGHT, 3300);
    add_prop(OBJ_I_VOLUME, 3300);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(40));
    add_prop(OBJ_M_NO_BUY, 1);
    set_af(this_object());
    set_ac(30);
    set_am(A_NAKED_MOD);
    set_at(A_HEAD); 
}

