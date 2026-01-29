/* created by Aridor, 08/29/94
 *  a teleporting ring, which teleports only
 *  randomly to random places. There is no
 *  way of controlling it.
 */


/* Navarre May 14th 2006, remove lose_me alarm before setting it again,
 * to avoid possibility of spamming "get ring, drop ring, get ring etc"
 * previously it resulted in a build up of alarms. Creating huge memory
 * consuming objects.
 *
 * Navarre June 5th, commented out mecien rooms in Terel as they are unaccessible
 *
 * Arman Sept 20 2016, updated Calia hall room
 */

inherit "/std/armour";

#include "/d/Krynn/common/defs.h"
#include <wa_types.h>

mixed *rooms = ({   ({ "/d/Ansalon/taman_busuk/neraka/outer/black/b18",
		       "/d/Ansalon/balifor/flotsam/room/street25",
                       "/d/Ansalon/balifor/flotsam_forest/coastline/mist1",
                       "/d/Ansalon/kalaman/city/s1"
 
 		       }),
                    ({ "/d/Krynn/solace/graves/o_grave1",
		       "/d/Krynn/xak/crypt/northcrypt3",
		       "/d/Krynn/solace/new_village/shop",
                       "/d/Krynn/solamn/moor/room/moor2"}),
 
                    ({
			 "/d/Calia/guilds/calians/rooms/light/hall"
                    }),
	
		    ({ "/d/Gondor/ithilien/road/crossroads",
			 "/d/Gondor/rohan/horn/gorge/breach",
			 "/d/Gondor/anorien/druedain/forest5",
			 "/d/Gondor/lebennin/road/wqroad4",
			 "/d/Gondor/rohan/edoras/pspub" }),

		    ({	 "/d/Terel/common/road/cornerstone",
			 "/d/Terel/mortricia/camp/house/house_9" 
                    }),
		
		    ({  "/d/Sparkle/area/faerie/rooms/forest/ctroad01",
			  "/d/Genesis/start/human/town/pier4",
			  "/d/Genesis/start/dwarf/lvl1/shop" })
	      });
string *cant_take_it = ({ });
string wear_room;
int lose_alrm = 0;
int teleport_alrm = 0;
int return_alrm = 0;

void
create_armour()
{
    set_name("ring");
    add_name("kitring");
    set_adj("beautiful");
    add_adj("ruby");
    set_short("beautiful ruby ring");
    set_long("This is a beautiful ring, made of fine platinum and set " +
	     "onto it is a flaming ruby. It sparkles deep red and " +
	     "you believe you can see something moving inside.\n");
    add_item(({"inside ruby","ruby","inside"}),
	     "Red curls are swirling inside the ruby, giving life to the " +
	     "stone.\n");
    set_af(TO);
    set_ac(0);
    set_at(A_ANY_FINGER);
    add_prop(OBJ_I_VALUE, 4000);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({ "This is a magic ring.", 1,
				  "It will start to excert its power over " +
				  "you when you wear it.", 15,
				  "There is no way of controlling its power",
				    25,
				  "The ring is able to move you to far away " +
				  "places.", 40,
				  "Removing the ring again after wearing " +
				  "will not stop the ring's influence on you.",
				    60,
				  "The ring withdraws itself from you if " +
				  "you do not invoke the powers.", 80 }));
    add_prop(OBJ_S_WIZINFO, "Kitiara's ring is a teleporting ring that will teleport " +
	     "the wearer around Genesis. The teleporting is started when the ring is " +
	     "worn for the first time. Removing the ring again won't stop the teleporting, " +
	     "only slow it down a little. After dropping the ring, it will return to " +
	     "the last owner and continue the teleporting unless someone else finds " +
	     "the ring and wears it instead. If the owner doesn't wear the ring for some " +
	     "time, the ring will return to where it was found. Currently there is no " +
	     "use nor cure for this ring, but it'll come sooner or later.\n");
}

void
enter_env(object dest, object old)
{
    if (member_array(dest->query_real_name(), cant_take_it) != -1)
      set_alarm(2.0,0.0,"move",old);
    else if (dest->query_name() != "Kitiara")
    {
     if(lose_alrm)
     {  
       remove_alarm(lose_alrm);
     }
     lose_alrm = set_alarm(500.0,0.0,"lose_me", dest);
    }
    ::enter_inv(dest, old);
}

void
leave_env(object from, object to)
{
    if (teleport_alrm)
      {
	  remove_alarm(teleport_alrm);
	  teleport_alrm = 0;
	  return_alrm = set_alarm(itof(100 + random(500)),0.0,
			       "return_to_dropper",from);
      }
    ::leave_env(from, to);
}

void
return_to_dropper(object who)
{
    if (!who)
      return;
    move(who);
    teleport_alrm = set_alarm(itof(random(500) + 20),0.0,"teleport_me");
}

mixed
wear(object what)
{
    remove_alarm(lose_alrm);
    lose_alrm = 0;
    if (return_alrm)
      remove_alarm(return_alrm);
    return_alrm = 0;
    if (TP->query_name() != "Kitiara")
      {
/*   Removed 95/07/82 by Jeremiah.  Somehow this can cause a player */
/*   to get teleported into a room to which they have no access.    */
/*
	  wear_room = file_name(E(TP));
	  rooms += ({ ({ wear_room }) });
*/      
	  teleport_alrm = set_alarm(itof(random(500) + 20),0.0,"teleport_me");
      }
    return 0;
}

mixed
remove(object what)
{
/*  (look at note in previous function) */
/*
    rooms -= ({ ({ wear_room }) });
*/
    return 0;
}

void
teleport_me()
{
    mixed *domain;
    mixed newroom;
    object owner = E(TO);
    if (interactive(owner) && E(owner))
      {
	  if (E(owner)->query_prop(ROOM_M_NO_TELEPORT) ||
	      owner->query_prop(OBJ_M_NO_TELEPORT))
	    owner->catch_msg("\n\n\nSuddenly, there is smoke all around " +
			     "you. But when it clears, you still find " +
			     "yourself in the same place!\n\n\n");
	  else
	    {
		domain = rooms[random(sizeof(rooms))];
		newroom = domain[random(sizeof(domain))];
		/*
		if (owner->query_average_stat() > 80 && random(100) > 60)
		  newroom = "/d/Krynn/solamn/splains/lab/laboratory";
		  */
		if (file_name(E(owner)) != newroom)
		  {
		      owner->catch_msg("\n\n\nSuddenly, there is smoke all " +
				       "around you. When it clears, you " +
				       "find yourself in a completely " +
				       "different place!\n\n\n");
		      owner->move_living("X",newroom,1,0);
		  }
	    }
      }
    if (query_worn())
      teleport_alrm = set_alarm(itof(random(500) + 20),0.0,"teleport_me");
    else
      teleport_alrm = set_alarm(itof(random(500) + 1020),0.0,"teleport_me");
}


void
lose_me(object who)
{
   if (E(TO) == who && teleport_alrm == 0)
     {
	 cant_take_it += ({ who });
	 move(E(who));
     }
   lose_alrm = 0;
}
