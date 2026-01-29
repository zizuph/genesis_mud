// A Monstrance
// This is a ritualist tool used to transport and display cons. shamrocks
// container for a consecrated shamrock simulated
// used in some spells, for meditation.
//
// History:
// Date         Coder         Action
// -------- ----------------  -----------------------------------------
// 4/11/98  Zima              Created
// 5/16/98  Zima              Recoded as a holdable object, not a wep
// 7/20/98  Zima              Removed ability to remove; added "amt"
//                            Added support for meditation
// 26Mar2005 Mercade          Removed lethal penalty when picking up.

inherit "/std/object";
inherit "/lib/holdable_item";
#include "defs.h"
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../room/meditation.h"
#define  MIN_ALIGN_HURT_LEVEL -50
 
int      here=0;            // amt of "mana" in the shamrock; 0=no shamrock
string*  Meditator = ({});  // list of names of priest who've meditated
int*     MedAmt    = ({});  // parallel list; # meditate increments received
 
//
// player_can_get - check this player to see if he can get montrance
//
public int player_can_get(object tp)
{
   object shawl;
   if ((!objectp(tp))||(!living(tp))||(!here)) return 1;
   shawl = present(SR_MON_SHAWL,tp);
   if ((objectp(shawl)) && (objectp(shawl->query_worn())))
      return 1;
   return 0;
}
 
//
// do_check_player - check this player & make him drop monstrance
//                   if he's not allowed to have it.
//
public void do_check_player()
{
   object tp=ENV(TO);
   string mshort=query_short();
 
   if (!player_can_get(tp))
      {
      tp->catch_msg("The "+mshort+" burns your hands!\n"+
                    "You drop the "+mshort+"!\n");
      tell_room(ENV(tp),QCTNAME(tp)+" yelps in pain!\n"+
                        QCTNAME(tp)+" drops the "+mshort+"!\n",tp);
      move(ENV(tp));
      }
}
 
//
// check_ok_move - for move(), player must be wearing the shawl
//
int check_ok_move(object tp)
{
   int align=(tp->query_alignment());
   int hp;

   if (player_can_get(tp)) return 1; // ok, he can have it
   if (align < MIN_ALIGN_HURT_LEVEL)
   {
      write("You attempt to take the "+short()+"...\n");
      tell_room(ENV(tp),QCTNAME(tp)+" attempts to take the "+short()+".\n",TP);
      write("The "+short()+" sends waves of pain through your "+
                    "body!\nYou scream out in pain and terror!\n");
      tell_room(ENV(tp),QCTNAME(tp)+" screams in pain!\n",tp);
 
      /* hit = (40% of max_hp) * (percent evil, which is align/max) */
      hp = ((tp->query_max_hp())*align*4)/(10*F_MAX_ABS_ALIGNMENT);
      tp->heal_hp(hp);
      if (tp->query_hp()<=0) tp->do_die(TO);
   }
   else
   {
      write("The "+short()+" resists you.\n");
   }
   return 0; // he can't have it
}
 
//
// move - masked to make sure player can take the monstrance
//
varargs public int move(mixed dest, mixed subloc)
{
   if (objectp(dest)&&living(dest))
      if (check_ok_move(dest))
         return (::move(dest,subloc));
      else
         return 7; // code in /std/object::move = no move, I print msgs
   return (::move(dest,subloc));
}
 
//
// show_glow - indicate when the obj begins/ends glowing
//
void show_glow()
{
   object room;
   if (ENV(TO)->query_prop(ROOM_I_IS))
      room=(ENV(TO));
   else if (ENV(TO)->query_prop(LIVE_I_IS))
      room=(ENV(ENV(TO)));
   else
      room=0;
 
   if (objectp(room))
      if (here)
       tell_room(room,"The "+query_short()+" begins to glow faintly.\n");
      else
       tell_room(room,"The faint glow of the "+query_short()+" dims out.\n");
}
 
//
// update_desc - updates the state of the obj
//
void update_desc(int is_here) {
   string long=
      "It is a monstrance made of gold, a ritualistic tool which looks "+
      "like a large flat sunburst set on a candlestick. In the center of "+
      "the sunburst is a round crystal ";
 
   here = is_here;
   show_glow();
   if (here)
      {
      long += "which encases a trifoil leaf. The monstrance is glowing "+
              "faintly.\n";
      set_short("glowing monstrance");
      add_adj("glowing");
      remove_item("crystal");
      add_item(({"shamrock","consecrated shamrock","shamrock in monstrance",
                 "shamrock in crystal","crystal"}),
                 "The crystal in the center of the monstrance encases a "+
                 "trefoil leaf.\n");
       do_check_player();
      }
   else
      {
      long += "in which a very small object could be placed.\n";
      set_short("golden monstrance");
      remove_adj("glowing");
      remove_item(({"shamrock","consecrated shamrock","shamrock in monstrance",
                 "shamrock in crystal","crystal"}));
      add_item("crystal",
               "The crystal in the center of the monstance is designed to "+
               "encase a very small object, which must be placed in it.\n");
      // no shamrock here, so can erase Meditation lists
      Meditator = ({});
      MedAmt    = ({});
      }
   set_long(long);
}
 
//
// query_shamrock - returns amt of "mana" left, 0=no shamrock here
//
int query_shamrock()     { return here; }
int query_max_shamrock() { return MED_MONST_MAX_MANA; }
string* query_meditators() { return Meditator; }
int*    query_medamts()    { return MedAmt;    }
 
//
// add_amt - add to the amt of "mana" left.
//
int add_amt(int amt)
{
   here += amt;
   if (here>MED_MONST_MAX_MANA) here = MED_MONST_MAX_MANA;
   if (here <0) here = 0;
   update_desc(here);
   return here;
}
 
//
// create_object
//
void create_object() {
   set_name("monstrance");
   add_name(SR_MONSTRANCE);
   add_adj("golden");
   update_desc(0);
   set_slots(W_BOTH);
}
 
//
// enter_env - when entering a living, check is OK
//
public void enter_env(object inv, object from)
{
   ::enter_env(inv,from);
   set_alarm(1.0,0.0,&do_check_player());
}
 
//
// leave_env - make sure we realease if being held
//
public void leave_env(object env, object to)
{
    ::leave_env(env, to);
    holdable_item_leave_env(env, to);
}
 
/* Function name: appraise_object (MASK)
 * Description  : Appraise the object.
 * Arguments    : int num - The appraise number, randomized.
 * Returns      : n/a
 */

public void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_holdable_item();
}
 
//
// do_place - allows player to place shamrock in monstrance
//
int do_place(string cmd) {
   object ob;
   int    rc;
   string obshort, mshort=(query_short());
   object *inv=all_inventory(TP);
 
   notify_fail("Place what in the monstrance?\n");
   if (!stringp(cmd)) return 0;
   if (!parse_command(cmd,inv,"%o 'in' [the] 'monstrance' / 'crystal'",ob))
      return 0;
 
   obshort = (ob->query_short());
   if (here)
      write("There is already something in the monstrance.\n");
   else if (ENV(ob)!=TP)
      write("You must have the "+obshort+" in your possession to do that.\n");
   else if (!(ob->id("shamrock")))
      write("The "+obshort+" does not belong in the monstance.\n");
   else if (!(ob->query_prop(SR_CONSECRATED)))
      write("The "+obshort+" must be consecrated.\n");
   else
      {
      write("You place a "+obshort+" in the "+(query_short())+".\n");
      tell_room(ENV(TP),QCTNAME(TP)+" places something in "+HIS_HER(TP)+
                " "+(query_short())+".\n", TP);
      ob->remove_object();
      update_desc(MED_MONST_MAX_MANA);
      }
   return 1;
}
 
//
// allowed_to_med - can the player meditate anymore from this monstrance?
//
int allowed_to_med(object tp)
{
   int    ndx;
   string tpn = lower_case(tp->query_name());
 
   // obviously not if not a saggart
   if (!(tp->is_saggart())) return 0;
 
   // if list empty, add player to list and yes he can meditate
   if (sizeof(Meditator)<=0)
      {
      Meditator = ({tpn});
      MedAmt    = ({0});
      return 1;
      }
 
   // search for player in list
   ndx = member_array(tpn,Meditator);
   if (ndx >= 0)
      if (MedAmt[ndx] >= MED_INDIV_MAX_MANA)
         return 0;
      else
         return 1;
 
   // player not in list, so need to add
   Meditator += ({tpn});
   MedAmt    += ({0});
   return 1;
}
 
//
// report_med - update monstrance when a player meditates and draws
//              mana from the monstrance
void report_med(object tp, int mana)
{
   string tpn   = lower_case(tp->query_name());
   int    allow = allowed_to_med(tp); // ensure he's in the list
   int    ndx   = member_array(tpn,Meditator);
 
   if (ndx>=0) MedAmt[ndx] += mana;
   add_amt(-mana);
}
 
//
// init - add actions
//
void init()
{
   ::init();
   add_action(&do_place(), "place");
}
