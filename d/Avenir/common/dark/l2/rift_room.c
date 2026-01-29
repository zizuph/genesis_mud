// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/rift_room.c
// creator(s):       Lucius & Zielia
// revisions:        
//     Lucius, Oct 08: Changed gems to point to /d/Genesis/gems/obj/
//     Lilith, Jan 2022: Added missinf room inside prop.
// purpose:          
// note:             
// bug(s):           
// to-do:            
inherit "/d/Avenir/inherit/room";

#include <money.h>
#include <tasks.h>
#include <macros.h>
#include "/d/Avenir/include/relation.h"
#include "../dark.h"
#include "/d/Avenir/include/basic.h"

#define OFFERED_PROP	"_live_i_offered_coin"
#define OFFERED_COIN(x) x->query_prop(OFFERED_PROP)
#define US_PURITY     139058
#define WATER_TRANS  "/d/Avenir/common/dark/l2/water_trans"

private static int reaction;

public void
create_domain_room(void)
{
    set_short("hollow in the rock");
    set_long("You stand inside what could best be termed an "
	+ "airbubble in the bedrock of the Underdark. The walls are "
	+ "rough-hewn, jagged and unfinished as they slope in a gentle "
	+ "curve over your head to form a ceiling, the apex of which "
	+ "features a starbust-shaped crack that exudes darkness. "
	+ "The southern wall has a rent torn into it, almost hidden "
	+ "amongst the jagged features. The floor of this hollow "
	+ "is bumpy, porous and reddish-black, though mostly level "
	+ "under your feet. The most unusual feature of this chamber, "
	+ "however, is the large trefoil-shaped pool inset in the "
	+ "center of the floor.\n");

    add_item(({"wall","walls"}),
	"The walls are rough-hewn and jagged, cool and smooth to "
	+ "the touch for all their hazardous appearance. They slope "
	+ "towards the ceiling, becoming the ceiling of this chamber. "
	+ "Nestled between jagged protrusions in the southern portion "
	+ "of the wall is a largish fissure.\n");
    add_item(({"south wall","southern wall"}),
	"The southern wall contains a large, though narrow, rent torn "
	+ "between jagged protrusions.\n");
    add_item(({"rent","fissure","rift","tear"}),
	"In the the southern wall is a rift, rough and jagged "
	+ "as though the rock were torn open by immortal hands.\n");
    add_item(({"other room","room beyond"}),
	"The rent in the southern wall is actually curved "
	+ "slightly, making it impossible to find an angle "
	+ "of view into the room beyond.\n");
    add_item("ceiling",
	"The ceiling is really nothing more than a sloped extension "
	+ "of the chamber walls. A starburst-shaped crack at its " 
	+ "apex seems to exude some type of darkness.\n");
    add_item(({"crack","starburst","starburst-shaped crack"}),
	"The crack with the starburst shape looks to have been "
	+ "chiseled out rather than being naturally occuring. "
	+ "It covers the entire apex of this bubble-like chamber "
	+ "and you cannot even see the sides of it due to the "
	+ "darkness exuding from it.\n");
    add_item("darkness",
	"Thick, exuding darkness hovers inside starburst crack. "
	+ "It has an almost gelatinous appearance and if you watch "
	+ "for long enough, you see miniscule pinpricks of multi-coloured "
	+ "lights appear then quickly fade again.\n");
    add_item("floor",
	"The chamber floor is mostly level, though bumpy, consisting "
	+ "of porous, reddish-black rock. Despite its fragile appearance "
	+ "it proves to be quite solid and hard underfoot. Except in the "
	+ "center where a large trefoil pool is inset.\n");
    add_item(({"pool","trefoil","trefoil pool","trefoil-shaped pool"}),
	"The trefoil-shaped pool is large, its three lobes taking up "
	+ "the center of this hollow in the rock. Where most of this "
	+ "chamber looks naturally formed, this pool most decidely "
	+ "doesn't. It is ringed completely by a knee-high, seemless "
	+ "lip of gleaming obsidian. The water of the pool is still "
	+ "and reflective, seeming to glow beneath the exuding "
	+ "darkness directly overhead.\n");
    add_item(({"lobes", "circles"}),
	"The three lobes would be perfectly round if they didn't overlap. "
	+ "They are equally sized and identical in every way except "
	+ "position. One protrudes to the north of the center, the others "
	+ "to the southwest and southeast.\n");	
    add_item(({"north lobe", "southwest lobe", "southeast lobe", "lobe",
    	"first lobe", "second lobe", "third lobe", "north circle", 
    	"southwest circle", "southeast circle", "circle",
    	"first circle", "second circle", "third circle"}),
	"The lobe is a rounded portion of the pool formed by a lip of "
	+ "black obsidian. It would be a perfect circle if it wasn't "
	+ "broken by the other two lobes which overlap it. The water "
	+ "within it almost seems to glow relative to the darkness above "
	+ "and silvery reflections prevent you from seeing beneath "
	+ "the surface.\n");		
    add_item(({"lip", "obsidian lip", "gleaming lip", 
        "gleaming obsidian lip",}),
	"The lip is seamless and made of gleaming black obsidian, "
	+ "perfectly smooth and glass-like except for inside the pool "
	+ "where, lit by the glow of the water, you can just make out "
	+ "some kind of carvings.\n");	
    add_item(({"carvings", "carving"}),
	"Carved into the gleaming obsidian lip of the pool, just above "
	+ "the surface of the reflective water you can make out "
	+ "a pattern of alternating wavy lines and a lock and key.\n");	
    add_item(({"water", "reflective water", "glowing water"}),
	"The water is dark and reflective and yet seems to glow with a "
	+ "silvery light. The depths of the water are obscured by "
	+ "the reflective surface, leaving no way to tell what lies "
	+ "beneath.\n");	
	
     add_prop(OBJ_S_SEARCH_FUN, "search_dark");
     add_prop(ROOM_I_INSIDE, 1);
     add_prop(ROOM_M_NO_SCRY, 1);
     add_prop(ROOM_M_NO_TELEPORT, 1);
     add_prop(ROOM_M_NO_TELEPORT_TO, 1);
     add_prop(ROOM_M_NO_TELEPORT_FROM, 1);     
}

public int
f_crawl(string str)
{
    if (!strlen(str))
	return 0;

    if (!parse_command(str, ({}),
	    "'through' [the] 'rift' / 'fissure' / 'rent'"))
	return notify_fail("Crawl through what?\n");
	
    write("You crawl your way through the rent in the wall.\n");
    say(QCTNAME(TP) +" crawls through a rent in the wall.\n");

    TP->move_living("M", L2 + "s7", 1, 0);
    say(QCTNAME(TP) +" arrives crawling through a rent in the wall.\n");

    return 1;
}

public void
react_infidel(object tp, int count)
{  
    reaction = 0;	
	
    switch(count++)
    {
    case 0:
        if (!present(tp, TO))
            return;    
	tp->catch_tell("As you reach toward the pool, you find you cannot "+
	    "penetrate the surface. It's almost like a thin, electric "+
	    "skin covers the water.\n");
	tell_room(TO, QCTNAME(tp) +" reaches toward the mirror-like pool, "+
	    HIS(TP) +" fingers just brushing the surface.\n", tp, TO);	 
	break;
    case 1:    
	if (present(tp, TO))
        {
	    tp->catch_tell("You feel a sharp, electric jolt "+ 
	        "shoot through you and the pool begins to bubble angrily. "+
	        "Discordant music fills the cavern.\n");
	    tp->heal_hp(-(tp->query_max_hp()/20));    
        }
	tell_room(TO, "The pool begins to bubble angrily and discordant "+
	    "music fills the cavern.\n", tp, TO);

	break;
    case 2:
	tell_room(TO, "The choatic, ringing music builds to a painful "+
	    "cacophony before all becomes silent and the pool is still "+
	    "once more.\n", 0, TO);
	if (present(tp, TO))
        {
	    tp->add_mana(-(tp->query_max_mana()/10));	 
        }   
	break;
    } 
    
    if (count < 3)
    {
	reaction = set_alarm(2.7, 0.0, &react_infidel(tp, count)); 
    }  	
}

public void
no_offering(object tp, int count)
{
    reaction = 0;	
	
    switch(count++)
    {
    case 0:
        if (!present(tp, TO))
            return;
	tp->catch_tell("As you reach toward the pool, you find you cannot "+
	    "penetrate the surface. It's almost like a thin, electric "+
	    "skin covers the water.\n");
	tell_room(TO, QCTNAME(tp) +" reaches toward the mirror-like pool, "+
	    HIS(TP) +" fingers just brushing the surface.\n", tp, TO);	 
	break;
    case 1: 
        if (present(tp, TO))
        {   
	    tp->catch_tell("You feel a warm, electric tingle flow along "+ 
	        "your skin and slow, silver-edged ripples spread across the "+
	        "pool and a single, musical note resonates throughout "+
	        "the cavern.\n");
        }
	tell_room(TO, "Slow, silver-edged ripples spread across the pool "+
            "and a single, musical note resonates throughout the cavern\n", 
            tp, TO);
	break;
    case 2:   
	tell_room(TO, "Beneath the ripples, you catch a brief glimpse of "+
	    "what looks like hundreds of coins on the bottom of the pool.\n", 
	    0, TO);
	break;	
    case 3:
	tell_room(TO, "The haunting, soulful note slowly fades until "+
	    "all becomes silent and the pool is still once more.\n", 0, TO);
	break;
    } 

    if (count < 4)
    {
	reaction = set_alarm(2.7, 0.0, &no_offering(tp, count)); 
    }  	
}

public int
query_can_touch(object tp)
{
    if(reaction)
    {
	tp->catch_tell("You should wait until it calms down.\n");
	return 0;
    }	
    else if (IS_INFIDEL(tp) || tp->query_race_name() == "ogre")
    {
	react_infidel(tp, 0);
	return 0;
    }
    else if(!OFFERED_COIN(tp))
    {			
	no_offering(tp, 0);
	return 0;
    }
    else
	return 1;
}

/*
 * Function name: search_dark
 * Description:   Search results for add_items in the Dark.
 *                Gives general experience 100 each for max of  
 *                10 successful searches per login.
 * Returns:       string for success
 */
string 
search_dark(object player, string str)
{
    object    ob;
    int       i, n; 
       
    /* If I've found objects already, I'm not finding any more */   
    n = player->query_prop("_avenir_dark_found");
    if (n > 5)
        return "";    

    /* Do I have the simple awareness to find something
     * and the wisdom to recognize it as being of value?
     */
    i = player->resolve_task(TASK_SIMPLE, ({ TS_WIS, SS_AWARENESS,}));
    if (i < 0)
        return "";    

    /* I can only find things in these places */
    if (!IN_ARRAY(str, ({"pool", "water", "lobes", "north lobe", 
    "southwest lobe", "southeast lobe", "lobe", "first lobe", 
    "second lobe", "third lobe", "circles", "north circle", 
    "southwest circle", "southeast circle", "circle", "first circle", 
    "second circle", "third circle"})))
        return "";
        
    /* Am I able to touch the pool and what can I find?*/
    if (!query_can_touch(player))
        return "";
    else    
    {
	switch (random(16))
	{
	case 0..3:
	    ob = MONEY_MAKE_CC(1);  break; 
	    break;          
	case 4:
	    ob = clone_object("/d/Genesis/gems/obj/sea_agate"); break;
	case 5..7:
	    ob = MONEY_MAKE_SC(1);  break; 
	case 8:
	    ob = clone_object("/d/Avenir/common/obj/syb_coin");  break;    
	case 9:
	    ob = MONEY_MAKE_GC(1);  break;                                    
	default:  return "";
	}
    }

    /* Make sure to add to the counter */
    player->add_prop("_avenir_dark_found", n + 1);

    /* I get some general experience for succeeeding */
    player->add_exp_general(100 + random(50));
    ob->move(player, 1);          
    
    return "You find "+LANG_ASHORT(ob) +".\n";
}

public int
do_search(string str)
{
    if (IN_ARRAY(str, ({"pool", "water", "lobes", "north lobe", 
    "southwest lobe", "southeast lobe", "lobe", "first lobe", 
    "second lobe", "third lobe", "circles", "north circle", 
    "southwest circle", "southeast circle", "circle", "first circle", 
    "second circle", "third circle"})) && !query_can_touch(TP))
    {
	return 1;
    }    

    return 0;
}

public int
do_touch(string str)
{
    if (!strlen(str) || !parse_command(str, ({}), " [the] 'pool' / "+
    "'water' "))
    {
	notify_fail("Touch what?\n");
	return 0;
    }

    if (query_can_touch(TP))
    {
	write("You lean out over the pool to touch the mirror-"+
	    "like water. It is wet and icy cold.\n");
	say(QCTNAME(TP) +" leans over the the mirror-like pool, "+
	    "and touches the water.\n");     
    }
    
    return 1;
}

public int
f_splash(string str)
{
    if (!strlen(str) || !parse_command(str, ({}), " [the] 'water' "))
    {
	notify_fail("Splash what?\n");
	return 0;
    }

    if (query_can_touch(TP))
    {
	write("You try to splash in the glowing water of the pool "+
    	    "but oddly the water barely moves.\n");
	say(QCTNAME(TP) +" tries to splash the glowing water of the "+
	    "pool, but the water barely stirs.\n");
    }
    
    return 1;
}

public int
do_wash(string str)
{
    if (!strlen(str) || !parse_command(str, ({}), " [in] [the] 'water' / "+
    "'pool'"))
    {
	notify_fail("Wash in what?\n");
	return 0;
    }

    if (query_can_touch(TP))
    {
	if (TP->query_guild_name_occ() == "Union of the Warriors of Shadow")
	{
	    TP->emote_adjust_union_virtue(US_PURITY, 50);
	    TP->add_prop("_Union_cleansed_in_astuary", time());
	}
	write("You kneel by the pool and wash yourself in the icy "+
	    "cold water.\n");
	say(QCTNAME(TP) +" kneels by the pool and washes "+ HIM(TP) +
	    "self in the dark water.\n");
    }
    
    return 1;
}

public int
do_drink(string str)
{
    if (!strlen(str) || !parse_command(str, ({}), " [water] [from] [the] "+
    "'pool' / 'water' "))
    {
	notify_fail("Drink what?\n");
	return 0;
    }

    if (query_can_touch(TP))
    {
        if (TP->drink_soft(TP->drink_max() / 16 , 0))
        {
            write("You cup your hands in the cold, dark water of the "+
	 	"pool and lift them to your lips, taking a mouthful " +
		"of crystal pure water.\n");
            say(QCTNAME(TP)+" dips "+ HIS(TP) +" cupped hands into the "+
              "still, dark water of the pool and raises them to "+
		HIS(TP) +" lips, drinking deeply.\n");
        }
        else
	{
            write("You aren't thirsty at the moment.\n");
	}
    }
    
    return 1;
}

private int
move_to_current(object tp, string str, string dest)
{
    object room = clone_object(WATER_TRANS);
    room->set_dest(dest);

    if (!objectp(room))
    {
        write("There seems to be an issue using the pool.\n"+
            "Notify an Avenir wizard of the problem.\n");
        return 1;
    }

    write("You jump into the "+ str +" of the pool but somehow do not "+
        "hit the bottom. You are sinking deep into watery darkness...\n");
    say(QCTNAME(tp) +" jumps into the pool and disappears without "+
        "so much as a splash.\n");

    tp->move_living("M", room, 1, 0);
    return 1;
}

public int
do_enter(string str)
{
    string what = query_verb();
    
    if (!strlen(str) || !parse_command(str, ({}), " [into] [in] [the] %s", str))
    {
	notify_fail(capitalize(what) +" what?\n");
	return 0;
    }

    if (str == "pool" || str == "water")
    {
	notify_fail("Which part of the "+ str +"?\n");
	return 0;
    }

    if (str == "lobe" || str == "circle")
    {
	notify_fail("Which "+ str +"?\n");
	return 0;
    }  

    if (!IN_ARRAY(str, ({"north lobe", "southwest lobe", "southeast lobe",
	"first lobe", "second lobe", "third lobe", "north circle",
	"southwest circle", "southeast circle", "first circle",
	"second circle", "third circle"})))
    {
	notify_fail(capitalize(what) +" what?\n");
	return 0;
    }
         
    if (query_can_touch(TP))
    {
	if (str == "north lobe" || str == "first lobe" || 
	str == "north circle" || str == "first circle")
	{
	    move_to_current(TP, str, "bazaar");		

	    return 1;
	}  
	
	//Holm lobe. Players shouldn't bypass holm
	//checks so those are included here.
	 
	if (str == "southwest lobe" || str == "second lobe" ||
	str == "southwest circle" || str == "second circle")
	{    
	    int holm = (TP->query_skill(139001));
	    int wei = ("/d/Avenir/inherit/avenir_time.c")->get_avenir_week();
	    if (wei > 9) 	wei = 1; 
	    
	    if ((TP->query_average_stat() > 87) && holm && (wei <= holm))
	    {
                 move_to_current(TP, str, "holm");
	    }
	    else
	    {
                 move_to_current(TP, str, "bazaar");
            }		  
	  
	    return 1;
	} 
	// Ziggurat lobe.
	if (str == "southeast lobe" || str == "third lobe" ||
	str == "southeast circle" || str == "third circle")
	{
            move_to_current(TP, str, "ziggurat");		
	    return 1;
	}
    }
    
    return 1;
}

public int
do_toss(string str)
{
    object ob;

    if (!strlen(str))
	return 0;

    if (!parse_command(str, all_inventory(TP),
	    "[a] / [the] %o [into] / [in] [the] [trefoil] 'pool' / "+
	    "'fountain'", ob))
    {
	notify_fail("Try "+ query_verb() +
	    "ing a coin into the pool instead.\n");
	return 0;
    }

    /* Make sure it's a coin (and a heap). */
    if (!ob->id("coin") || !ob->num_heap())
    {
	write("That would not be appropriate.\n"+
	    "Try "+ query_verb() +"ing a coin instead.\n");
	return 1;
    }

    /* Even if they specify several, we only toss one. */
    str = LANG_ADDART(ob->singular_short());

    write("You toss "+ str +" into the trefoil fountain.\n");
    say(QCTNAME(TP) +" tosses "+ str +" into the trefoil fountain.\n");

    str = ob->singular_short();

    if (ob->query_prop(HEAP_S_UNIQUE_ID) == "_coin_sybarun")
    {
	if (OFFERED_COIN(TP) || IS_INFIDEL(TP) || present("nasty_sickness", TP))
	{
	    tell_room(TO, "The surface of the pool flashes briefly "+
		"as the "+ str +" enters the water and sinks out of "+
		"sight.\n");
	}
	else
	{
	    TP->add_prop(OFFERED_PROP, 1);
	    set_alarm(300.0, 0.0, &(TP)->remove_prop(OFFERED_PROP));
	    tell_room(TO, "The pools surface crackles with electric "+
		"blue coruscating flashes as the "+ str +" comes into "+
		"contact with the water and sinks out of sight.\n");
	}
    }
    else
    {
	tell_room(TO, "The surface of the pool ripples briefly as the "+
	    str +" plops into the water.\n");
    }

    /* Even if they specify several, we only remove one. */
    ob->set_heap_size(ob->num_heap() - 1);
    return 1;
}

public void
init()
{
        ::init();

    add_action( do_touch, "touch"  );
    add_action( do_enter, "enter"  );
    add_action( do_enter, "dive"   );
    add_action( do_enter, "swim"   );
    add_action( do_drink, "drink"  );
    add_action( do_touch, "feel"   );
    add_action(  do_wash, "wash"   );
    add_action(do_search, "search" );
    add_action(  do_toss, "toss"   );
    add_action(  do_toss, "throw"  );
    add_action(  f_crawl, "crawl"  );
    add_action( f_splash, "splash" );
}
