/*
 *  Carrier raven for the Morgul Mages.
 *
 *  Olorin, 5-jan-1994
 */

#pragma save_binary

inherit "/d/Gondor/common/guild/obj/pigeon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

/* The delay between sending the message and the receiving of it. */
#define SLOWLY random(20) + 30

/* The number of times the pigeon will carry a message. */
#define TIMES 3

void create_creature()
{
   ::create_creature();
   set_name("raven");
   set_pname("ravens");
   set_race_name("raven");
   remove_adj("white");
   set_adj("black");
   set_short("black raven");
   set_pshort("black ravens");
   set_long("@@long_func");
   set_alignment(-100);
}

string long_func()
{
  if (gOwner && gOwner == TP) 
    return BS("This is your raven. You can send messages to "+
      "other players by typing 'send <player>'" +
#if TIMES > 1
      " or 'send reply'" +
#endif
      ". If the raven fails to deliver the message you can tell it to " +
      "try again with the 'resend' command. " +
      "If you don't want the raven anymore, you can do 'return raven'.\n");
  if (gOwner && gOwner != TP)
    return BS("This is "+gOwner->query_cap_name()+"'s raven. It is " +
      "however a friendly bird, and you might be able to send messages to " +
      "others by 'send <player>' or 'send reply'. You may also 'return raven'. "+
      "That will make the raven fly back to "+gOwner->query_cap_name()+".\n");
  return BS("This is a black raven, which you can use to send messages "+
    "to other players with 'send <player>'.\n");
}
