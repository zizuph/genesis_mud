
/* 

    This is an object in a Gelan trash heap

    coder(s):  Maniac 
    history:
                12/8/98    rabbit -> gopheroo                Maniac
                25.1.95    Modified for changed quest        Maniac
                19.9.94    Created                           Maniac

    quests:     Catch a gopheroo quest in Gelan. This object 
                can be used as part of completing the quest, by catching
                the gopheroo, but only if it's in good condition. 

    special:    none

    to do:      none
    bug:        none known
*/

inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <ss_types.h>
#include <macros.h>
#include "weapon.h"
#include GOPHEROO_QUEST


int condition;   /* 0 for bad, 1 for good */

void
set_good_condition()
{
    condition = 1;
}


int
query_condition()
{ 
    return condition;
}


string
long_desc()
{
    string str1, str2;

    str1 =
      "A very light-weight wooden club, which looks a bit old and " +
      "scratched.\n";

   return str1; 
}


string
fail_catch()
{
  return "The " + short() + ", when swung, breaks in half before " 
       + "it has even hit, falling into two uesless pieces "
       + "which roll slowly away. Oh dear, it looks like the "
       + "club was in bad repair.\n";
}


string
succeed_catch()
{
  return "The gopheroo is rapped on the head by the " + short() 
       + ", a blow that a human would barely notice, but " 
       + "still enough to leave the little creature completely " 
       + "stunned for a short period. The " + short() + " looks to "
       + "have been affected as well, and seems to be in worse "
       + "condition than it was.\n";
}


int
try_to_hit(object target)
{
  object hitter = environment(this_object());

  if (condition) {
     condition = 0;
     hitter->catch_msg("The " + short() + " seems to be in "
                    +  "worse condition than it was.\n");  
     return ::try_hit();
  }

  tell_room(environment(hitter), QCTNAME(hitter) + " swings " +
            hitter->query_possessive() +  " " + short() +  
            " at " + QTNAME(target) + ".\n", 
            ({ hitter, target }) );

  target->catch_msg(QCTNAME(hitter) + " swings " + 
            hitter->query_possessive() + " " + short() +
            " at you.\n"); 

  hitter->catch_msg("You swing your " + short() + " at " +
          QTNAME(target) + ".\n"); 

  hitter->command("unwield " + short());
  tell_room(environment(hitter), fail_catch());

  set_alarm(0.2, 0.0, "remove_object");
  return 0;
}



/* Mask */
int
try_hit(object target)
{
  return try_to_hit(target);
}


string
wep_condition_desc()
{
   if (this_player()->query_skill(SS_AWARENESS) >= 25) 
     if (condition) 
        return "It seems to be in reasonable condition.. for trash.\n";
     else
        return "It is in bad condition, it is split across the middle " +
               "so that with one good swing it will probably fall " +
               "apart.\n";
   else return ::wep_condition_desc();
}


/* deals with attempt to hit the gopheroo and stun it using this object */
int
hit_gopheroo(string str)
{
  object tp = this_player();
  object ob1, ob2, stroker;
  int gopheroo = 0;
  int club = 0; 
  int ob1_access = 0;
  int ob2_access = 0;  
  

  if (!str) { 
    notify_fail("Hit what with what?\n");
    return 0;
  }

  if (parse_command(str, environment(tp), 
                   " %o 'with' %o ", ob1, ob2))   {
     gopheroo = ob1->id(GOPHEROO_NAME);
     club = ob2->id(CLUB_NAME);

     if (club && (ob2 != this_object())) {
       notify_fail("Which club?\n");
       return 0;
     }
          
     if (present(ob1, tp)) ob1_access = ON_TP;
     else if (present(ob1, environment(tp))) ob1_access = IN_ROOM;
     else ob1_access = CANT_SEE;

     if (present(ob2, tp)) ob2_access = ON_TP;
     else if (present(ob2, environment(tp))) ob2_access = IN_ROOM;
     else ob2_access = CANT_SEE;

     if (ob2_access == CANT_SEE) {
        notify_fail("What's that you want to hit something with?\n");
        return 0;
     }

     if (ob1_access == CANT_SEE) {
        notify_fail("What's that you want to hit?\n");
        return 0;
     }
     /* Now we know they can actually see both objects */

     if (!club) {
        notify_fail("Hmm, can't seem to do any hitting using " +
                    LANG_THESHORT(ob2) + "\n");
        return 0;
     }

     if (!gopheroo) {
        notify_fail("Now why would you want to hit " +
                    LANG_THESHORT(ob1) + "?\n");
        return 0;
     }

     /* Now we know they are trying to hit gopheroo with club */
 
     if (ob1_access == ON_TP) {
       notify_fail("But you've already got " + 
                   LANG_THESHORT(ob1) + "!\n");
       return 0;
     }

     if (ob2_access == IN_ROOM) {
       notify_fail("You need to get " + LANG_THESHORT(ob2) + 
                   " first!\n");
       return 0;
     }
     /* Now we know they're trying to hit it right, so they
        can attempt to hit the gopheroo using the club */
    
    tell_room(environment(tp), QCTNAME(tp) + " swings " + 
              LANG_THESHORT(this_object()) + " at the head " +
              "of the " + ob1->short() + "!\n", tp); 
    tp->catch_msg("You swing " + 
              LANG_THESHORT(this_object()) + " at the head " +
              "of the " + ob1->short() + "!\n"); 

    /* If club was in bad condition, gopheroo gets away */
    if (!condition)  {
      tell_room(environment(tp), fail_catch());
      ob1->bolt();
      set_alarm(0.2, 0.0, "remove_object");
      return 1;
    }

    /* succeed in stunning the gopheroo */
    ob1->make_docile(); 
    tell_room(environment(tp), succeed_catch());
    condition = 0;
    tp->add_prop(I_TRAPPED_GOPHEROO, 1);
    return 1;
   }
   else {
     notify_fail("Hit what with what?\n");
     return 0;
   }

}






create_weapon() {
  set_name("club");
  add_name(CLUB_NAME);
  set_short("light wooden club");
  set_pshort("light wooden clubs");
  set_long("@@long_desc");
  set_adj("light");
  set_adj("wooden");
  set_default_weapon(8,8,W_CLUB,W_BLUDGEON,W_ANYH,0);
  add_prop(OBJ_I_WEIGHT,4000);
  add_prop(OBJ_I_VOLUME,4000);
  add_prop(OBJ_I_VALUE,0);
  condition = 0;
}


void
init()
{
    object tp = this_player();

    ::init();
    
    add_action(hit_gopheroo, "hit");
    add_action(hit_gopheroo, "stun");
}

