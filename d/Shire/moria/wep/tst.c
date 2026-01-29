
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include <filter_funs.h>
#include "/d/Shire/common/defs.h"
inherit "/std/object";
/* inherit "/std/room/description.c"; */
  
void
create_object()
{
   set_name("headbutter");
   set_pname("headbutters");
   set_long("With this object you may headbut someone, "
	 +"causing a nosebleed.\n");
 
   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 200);
   add_prop(OBJ_I_NO_DROP, "Drop what?\n"); /* Let's fool tricky people */
   /*set_noshow();*/ /* Use this since some mortals can see invis. :) */
                     /* (I suspect you were using invis for debugging?) */
   add_prop(OBJ_I_INVIS, 0);
 
}
init(){
       ::init();
        add_action("head_but", "headbutt");
      }
 
public int /* It must be int or player will always get fail messages */
head_but(string person)
{
  object blood, victim; /* We have to add object victim because person */
                        /* is a string, not an object */
 
   FIXEUID;
  if(!person) 
	NFN0("Headbutt who?"); /* present returns an object pointer */
  if(!victim = present(person,ENV(TP))) 
	NFN0("You can't find that person!.\n");
 
/* We call catch_msg in victim because victim is an object, person is a */
/* string.  In order to call anything in a string, it must be a complete */
/* filename.  Otherwise we can't use it. */

  victim->catch_msg(QCTNAME(TP)+ " headbutts you in the nose!!!\n");

/* Again, victim is the object.  Also say() is a useful function. */

  say(QCTNAME(TP)+" headbutts "+QTNAME(victim)+" right in the "+
    "nose!!!\n", ({ victim, TP }));

/* You might want a write() in here somewhere, to let the player know the */
/* successfully headbutted. */

   blood = clone_object("/d/Shire/dain/nosebled");
/* Again, replaced person with victim; also, move() should be used. */
   blood->move(victim);
   return 1; /* Return 1 to say we succeeded */
}
 
