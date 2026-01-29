
/*      This is an object in a Gelan trash heap

    coder(s):  Maniac 
    history:
                12/4/98    rabbit -> gopheroo                Maniac
                25.1.95    Modified on quest change          Maniac
                19.9.94    Created                           Maniac

    quests:     Catch a gopheroo quest in Gelan. This object 
                can be used as part of completing the quest, by catching
                the gopheroo, but only if it's in good condition. 

    special:    none

    to do:      none
    bug:        none known
*/

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "object.h"
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
      "A tatty looking old fishing net, large enough for fish " +
      "weighing up to a few pounds by the look of it.";

   if (this_player()->query_skill(SS_AWARENESS) >= 25) 
     if (condition)
        str2 = " It seems to be in reasonable condition.. for trash.\n";
     else
        str2 = " It is in bad condition, there is a large hole in it " +
               "big enough for a fish to squirm through.\n";
   else
        str2 = "\n";

   return (str1 + str2); 
}


string
fail_catch()
{
  return "The gopheroo manages to squirm through a large hole in the " 
       + "fishing net. Oh dear, it looks like the net was in " 
       + "bad repair.\n";
}


string
succeed_catch()
{  
  return "The gopheroo struggles frantically to get out of the net, "
       + "but only manages to get even more tangled up. After a " 
       + "while it is so tangled that it can't struggle anymore, " 
       + "though the net appears to have been ripped somewhat in the " 
       + "process.\n";
}


/* deals with attempt to catch the gopheroo using this object */
int
trap_gopheroo(string str)
{
  object tp = this_player();
  object ob1, ob2, stroker;
  int gopheroo = 0;
  int net = 0; 
  int ob1_access = 0;
  int ob2_access = 0;  
  

  if (!str) { 
    notify_fail("Trap what with what?\n");
    return 0;
  }

  if (parse_command(str, environment(tp), 
                   " %o 'with' %o ", ob1, ob2))   {
     gopheroo = ob1->id(GOPHEROO_NAME);
     net = ob2->id(NET_NAME);

     if (net && (ob2 != this_object())) {
       notify_fail("Which net?\n");
       return 0;
     }
          
     if (present(ob1, tp)) ob1_access = ON_TP;
     else if (present(ob1, environment(tp))) ob1_access = IN_ROOM;
     else ob1_access = CANT_SEE;

     if (present(ob2, tp)) ob2_access = ON_TP;
     else if (present(ob2, environment(tp))) ob2_access = IN_ROOM;
     else ob2_access = CANT_SEE;

     if (ob2_access == CANT_SEE) {
        notify_fail("What's that you want to trap something with?\n");
        return 0;
     }

     if (ob1_access == CANT_SEE) {
        notify_fail("What's that you want to trap?\n");
        return 0;
     }
     /* Now we know they can actually see both objects */

     if (!net) {
        notify_fail("Hmm, can't seem to do any trapping using " +
                    LANG_THESHORT(ob2) + ".\n");
        return 0;
     }

     if (!gopheroo) {
        notify_fail("Now why would you want to trap " +
                    LANG_THESHORT(ob1) + "?\n");
        return 0;
     }
     /* Now we know they are trying to trap gopheroo with net */
 
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
     /* Now we know they're trying to trap it right, so they
        can attempt to trap the gopheroo using the net */
    
    this_object()->move(environment(tp));
    tell_room(environment(tp), QCTNAME(tp) + " traps the " + 
              ob1->short() + " with " + LANG_THESHORT(this_object()) +
              "!\n", tp);
    tp->catch_msg("You trap the " + ob1->short() + " with " +
                  LANG_THESHORT(this_object()) + "!\n"); 

    /* If net was in bad condition, gopheroo gets away */
    if (!condition)  {
      tell_room(environment(tp), fail_catch());
      ob1->bolt();
      return 1;
    }

    ob1->make_docile(); 
    tell_room(environment(tp), succeed_catch());
    condition = 0;
    tell_room(environment(tp), QCTNAME(tp) + " is able to unravel the " +
              "net carefully and get the " + ob1->short() + ".\n", tp); 
    tp->catch_msg("You are able to unravel the net carefully and get " +
              "the " + ob1->short() + ".\n");
    ob1->move(tp);
    tp->add_prop(I_TRAPPED_GOPHEROO, 1);
    return 1;
   }
   else {
     notify_fail("Trap what with what?\n");
     return 0;
   }

}



void
create_object()
{
    set_name("net");
    add_name(NET_NAME);
    set_adj(({"old", "fishing", "tatty" }) );
    set_short("tatty fishing net");
    set_pshort("tatty fishing nets"); 
    set_long("@@long_desc");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 4000);
 
    condition = 0;
}


void
init()
{
    object tp = this_player();

    ::init();
    
    add_action(trap_gopheroo, "catch");
    add_action(trap_gopheroo, "trap");
}


