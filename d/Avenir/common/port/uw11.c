// Underwater storeroom   (/d/Avenir/common/port/water11.c)
// creator(s):             Glinda may -95
// last update:            Lilith, Oct 2004 - fixed cloning bug in search.
//                         Gorboth, Jun 2008 - Escorcelled amulet is now
//                                             limited to 2 copies. See
//                                             comment below for more info.
//                         Lucius, Sep 2008 - More amulets are back as the
//                            "invoke" ability was removed.
//                         Zielia Jan 2009 - changed the way the octo holds
//                            people and slows them
// 		           Lucius, Jan 2009: Re-written for new water code.
// purpose:                "Noise" for the underwater quest. Is also
//                         supposed to hold some treasures that can be
//                         found if you stay long enough to kill the octopus
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/water";
inherit "/lib/unique";

#include "/d/Avenir/common/common.h"
#include <money.h>

#define SLOW_OBJ	(PORT +"obj/octo_slow")
#define SLOWED(x)	present("octo::slow", x)

private object *held = ({});
private int octo_type, search_counter = 0;


public void
reset_room(void)
{
   if (!present("octopus", TO))
   {
        octo_type = random(2);
        object ob = clone_object( PORT + "mon/octopus");
        
        if (octo_type)
            ob->config_octo(octo_type);

        tell_room("Something emerges from the shadows.\n");
        ob->move(TO);        
   }
   search_counter = 0;
}

public string 
do_search(object searcher, string str)
{
   int i;
   object ob;
   string msg;

   if (str != "crates" && str != "crate" && str != "chest" &&
       str != "chests" && str != "debris" )
   {
      return "Your search reveals nothing special.\n";
   }

   switch (search_counter)
   {
      case 0:
      {
         MONEY_MAKE_GC( 3 + random(12))->move(TP);
         msg = "You find some gold coins.\n";
         break;
      }
      case 1:
      {
         ob = clone_unique(PORT + "obj/uw_ring", 6,
	     PORT + "obj/uw_dagger", 1, 50);
         ob->move(searcher, 1);
         msg = "You find a " + ob->query_short() + ".\n";
         break;
      }
      case 2:
      {
        if (TP->query_prop(LIVE_I_UNDEAD))
        {
            write("You stir up some mud among the crates.\n");
            break;
        }
         ob = clone_unique(PORT + "obj/uw_amulet", 6,
              PORT + "obj/uw_necklace", 1, 25);
         ob->move(searcher, 1);
         msg = "You find a " + ob->query_short() + ".\n";
         break;
      }
      case 3:
      {
         for(i=0; i<(1+ random(3)); i++)
         {
            ob = clone_object( PORT + "obj/uw_potion");
            ob->move(searcher, 1);
         }
         msg = "You find something interesting among some vials.\n";
         break;
      }
      case 4:
      {
          ob = clone_unique(PORT + "obj/uw_gauntlets", 6,
	      PORT + "obj/uw_driftwood", 1, 25);
          ob->move(searcher, 1);
          msg = "You find a " + ob->query_short() + ".\n";
          break;
      }
      default:
         msg ="Your search reveals nothing special.\n";
   }
   search_counter++;
   return msg;
}

public int
check_held(object ob)
{
    if (IN_ARRAY(ob, held))
	return 1;
}

public object *
list_held(void)
{
    return held;
}

public  int
hold_me(object me, int arms)
{ 
    if (sizeof(held) < arms)
    {
	held = held + ({me});
	
	if (octo_type == 1)
	{
	    object ob = clone_object(SLOW_OBJ);
	    ob->move( me );  
	    me->catch_tell("The octopus slides a tentacle around your body " +
		"with a good grip. Its entangling arms make you feel slower.\n");
	}    
	else
	{
	    me->catch_tell("Too late you notice the octopus sliding a " +
	        "tentacle around your body with a good grip. You are stuck.\n");
	}
	return 1;
    }
    return 0;
}

public int
let_go(object ob, int arms = 0)
{
    if (!check_held(ob))
    {
	if ((random(arms)+1) > (sizeof(held)))
	{
	    return 0;
        }
        
        ob = one_of_list(({held}));
    }
    
    int sz = sizeof(held);
    while (sz--)
    {
	if (ob == held[sz])
	{
	    held[sz] = 0;
	    break;
	}
    }

    held = filter(held, objectp);

    if (objectp(SLOWED(ob)))
    	SLOWED(ob)->remove_object();

    ob->catch_tell("The tentacle releases its hold on your body.\n");
    return 1;
}

public int
check_exit(void)
{
    if (!present("octopus" , TO))
	return 0;
    
    if (!check_held(TP))
	return 0;

    /* if barely alive */
    if (!random(3) && (TP->query_hp() <= (TP->query_max_hp() * 2 / 11)))
	return 0;

    return 1;
}

public int
swim_exit(void)
{
    if (!check_exit())
    {
	write("You swim through the hole in the ceiling.\n");
	return 0;
    }

    write("You try to leave, but cannot break free from the " +
	"firm grip the octopus has on you.\n");
    say(QCTNAME(TP) + " tries to leave, but the octopus holds " +
	TP->query_pronoun() + " back.\n");

    TP->add_fatigue(-(calc_fat(TP)/2));
    return 1;
}

public void
create_room(void)
{
    underwater_room();
    set_no_drift(1);

    set_short("In storage room of a shipwreck");
    set_long("You are in the storage room of a large shipwreck. Large " +
	"crates and chests, some reasonably intact, and some rotten, pile " +
	"up in the aft end of the room. Apart from some small scratches " +
	"and holes the planks that make up the hull of the ship are as " +
	"sound as they were while the ship proudly sailed the seas of " +
	"the world. The influence of the sea is everpresent in the form " +
	"of slime and alga which covers all the surfaces in the room. In "+ 
	"the ceiling is an opening leading back to the deck.\n");
    add_item(({"ceiling","hole","hatch","opening"}),
	"There is an opening in the ceiling, leading back to the deck.\n");
    add_item(({"scratches","holes","wounds","planks","hull"}),
	"There are some wounds in the planks of the hull. Some of the " +
	"scratches seem to be oddly circle formed.\n");
    add_item(({"crates","chests","debris"}),
	"Most of the crates are rotten, and some seem to have been " +
	"broken by strong forces, resulting in large piles of debris. " +
	"Still there are a few reasonably intact chests embedded in all " +
	"the debris.\n");
    add_item(({"slime","alga","mud","surfaces","walls","wall"}),
	"A thin layer of mud and alga covers all surfaces.\n");
    add_item(({"wreck","shipwreck","irregularity","hull","ship"}),
	"Amazing. This ship must have been swallowed by the currents " +
	"and somehow transported into this cave. You can tell it has been " +
	"here for a long time since the seaweed is growing everywhere.\n");
    add_item(({"water"}),
	"The dark water envelops you completely.\n");

    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 10);
    // Prevent players to gem home.
    add_prop(ROOM_M_NO_TELEPORT_FROM,
	"You can't seem to do that underwater.\n");

    add_exit(PORT + "uw8", "up");
    add_exit(PORT + "uw8", "hole");
    add_exit(PORT + "uw8", "opening");

    reset_room();
}

public void
release_all(void)
{   
    foreach (object ob: held)
	let_go(ob);
}

public void
leave_inv(object ob, object to)
{
    while (check_held(ob))
	let_go(ob);
    
    ::leave_inv(ob, to);
}
