// file name:   /d/Avenir/common/dark/smis/darkl2p.c
// creator(s):  Casca, 01/13/00
// purpose:     For placing objects in the Dark L2 area
// revisions:   Lilith Nov 2021: changes due to re-jigger of rooms.
//              Lilith Dec 2021: added ablity to collect bat guano  
//              Lilith Dec 2021: modified do_crack to test for living  

#include <macros.h>                            /* macros like VBFC and QNAME */
#include <stdproperties.h>                     /* self-explanatory */

#include "/d/Avenir/smis/smis.h"
#include "/d/Avenir/include/defs.h"            /* Short-hand macros */
#include "/d/Avenir/include/paths.h"           /* Avenirian path defines */
#include "/d/Avenir/include/macros.h"          /* ADD_SKIN, IN_IN, etc */
#include "/d/Genesis/gems/gem.h"               /* macros and defs for Gems */

#define DMON	  DARK +"mon/"
#define ALBUS     DMON +"albus"
#define ARCHITECT DMON +"architect"
#define BAT       DMON +"bat"
#define BAT_R     DMON +"bat_resting"
#define CHIMERA   DMON +"chimera"
#define DRAKE     DMON +"drake"
#define GNOME     DMON +"gneiss_gnome"
#define GRUB      "/d/Avenir/common/outpath/mon/grub"
#define GRUB_MOM  "/d/Avenir/common/outpath/mon/mommy"
#define MILLI     "/d/Avenir/common/outpath/mon/millipede"
#define SPIDER    "/d/Avenir/common/outpath/mon/spider"

inherit SMIS_MODULE_PLACER;

#define UNIQUE(filen,num,alternatefile) ((!filen->load_file() && \
                        sizeof(filter(object_clones(find_object(filen)), \
                        (&operator(==)(0) @ &->query_prop("_obj_i_broken")))) \
                        < num) ? filen : alternatefile)



void 
create_placer()
{
    disable_notifications_autoset();
    /* Prevents computation of the list of rooms this module operates
       on: keeps rooms from cluttering the decision tables. */

    set_module_id("darkl2p");
    set_module_description("Level two of the Dark.");


    set_location_object(L2 + "n6",
                         DARK + "smis/tools_crate");
    set_location_object(L2 + "s6",
                         DARK + "smis/mixed_crate");
    set_location_object(L2 + "w1",
                         DARK + "smis/torch_crate");
    set_location_object(L2 + "add/r1",
                         DARK + "smis/tools_crate");
    set_location_object(L2 + "e10",
                         DARK + "smis/torch_crate");
    set_location_object(L2 + "add/t6",
                         DARK + "smis/torch_crate");
    set_location_object(L2 + "add/t23",
                         DARK + "smis/torch_crate");	
    set_location_object(L2 + "add/t40",
                         DARK + "smis/torch_crate");							 
    set_location_object(L2 + "add/c1",
                         DARK + "obj/campfire");
    set_location_object(L2 + "add/c2",
                         DARK + "obj/campfire");
    set_location_object(L2 + "add/c3",
                         DARK + "obj/campfire");
    set_location_object(L2 + "add/c4",
                         DARK + "obj/campfire");
    set_location_object(L2 + "add/c5",
                         DARK + "obj/campfire");
    set_location_object(L2 + "add/c6",
                         DARK + "obj/campfire");
    set_location_object(L2 + "add/c7",
                         DARK + "obj/campfire");
    set_location_object(L2 + "add/c8",
                         DARK + "obj/campfire");
    set_location_object(L2 + "add/r2",
                         DARK + "obj/campfire");
    set_location_object(L2 + "add/r3",
                         DARK + "obj/campfire");
    set_location_object(L2 + "add/r4",
                         DARK + "obj/campfire");
    set_location_object(L2 + "add/t62",
                         DARK + "obj/campfire");
    set_location_object(L2 + "add/t63",
                         DARK + "obj/campfire");
    set_location_object(L2 + "add/t65",
                         DARK + "obj/campfire");
    set_location_object(L2 + "add/t66",
                         DARK + "obj/campfire");


    set_location_objects(L2 + "e5", ({
                         DARK + "smis/food_crate",
                         DARK + "obj/t_pickaxe"}));
    set_location_objects(L2 + "add/r9b", ({
                         (UNIQUE("/d/Avenir/common/dark/obj/bones",
                             5, "/d/Avenir/common/obj/knife")),
                         (UNIQUE("/d/Avenir/common/bazaar/Obj/worn/qbracer",
                             4, "/d/Avenir/common/bazaar/Obj/worn/qbracel")),
                         BAZAAR + "Obj/misc/ptorch"}));

    set_location_npc(L2 + "center" , ARCHITECT);
    set_location_npc(L2 + "e4" , DMON + "foreman_s");
    set_location_npc(L2 + "n6", DRAKE);
    set_location_npc(L2 + "w3", BAT);						 
    set_location_npc(L2 + "add/r8" , CHIMERA);
    set_location_npc(L2 + "add/r9" , DMON + "w_wolf");
    set_location_npc(L2 + "add/r10" , DMON + "w_wolf");
    set_location_npc(L2 + "add/t44" , DRAKE);
    set_location_npc(L2 + "add/r5" , DMON + "oddone");
	
    set_location_npcs(L2 + "s7", ({ BAT, BAT, GRUB_MOM }));
	set_location_npcs(L2 + "e3", ({ DMON + "mtroll_s",
                                    DMON + "mtroll_s",
                                    DMON + "mtroll_s",
                                    DMON + "mtroll_s"}));
    set_location_npcs(L2 + "e13", ({ DMON + "lizard",
                                     DMON + "lizard", BAT }));
    set_location_npcs(L2 + "e12", ({ DMON + "lizard",
                                     DMON + "lizard", SPIDER }));
    set_location_npcs(L2 + "add/t54b", ({ BAT_R, BAT_R, BAT_R }));
	
    set_location_npcs(L2 + "add/c1", ({ DMON + "albus",
                                    DMON + "albus"}));
    set_location_npcs(L2 + "add/c2", ({ DMON + "albus",
                                    DMON + "albus"}));
    set_location_npcs(L2 + "add/c3", ({ DMON + "albus",
                                    DMON + "albus",
                                    DMON + "albus_l"}));
    set_location_npcs(L2 + "add/c4", ({ DMON + "albus",
                                    DMON + "albus"}));
    set_location_npcs(L2 + "add/c5", ({ DMON + "albus",
                                    DMON + "albus"}));
    set_location_npcs(L2 + "add/c6", ({ DMON + "albus",
                                    DMON + "albus"}));
    set_location_npcs(L2 + "add/c7", ({ DMON + "albus",
                                    DMON + "albus"}));
    set_location_npcs(L2 + "add/c8", ({ DMON + "gavriel",
                                    DMON + "albus",
                                    DMON + "albus_l"}));
    set_location_npcs(L2 + "add/r2", ({ DMON + "albus_f",
                                    DMON + "albus_f",
                                    DMON + "albus_f"}));
    set_location_npcs(L2 + "add/r3", ({ DMON + "albus_f",
                                    DMON + "albus_f",
                                    DMON + "albus_f"}));
    set_location_npcs(L2 + "add/r4", ({ DMON + "albus_f",
                                    DMON + "albus_f",
                                    DMON + "albus_f",
                                    DMON + "albus_f"}));

    set_location_npcs(L2 + "add/t61", ({ GNOME, GNOME, BAT, BAT_R }));
    set_location_npcs(L2 + "add/t62", ({ GNOME, GNOME, BAT }));
    set_location_npcs(L2 + "add/t63", ({ GNOME, GNOME, GNOME }));	
    set_location_npcs(L2 + "add/t64", ({ GNOME, GNOME, GNOME, GNOME }));
    set_location_npcs(L2 + "add/t65", ({ GNOME, GNOME, GNOME, GNOME }));
    set_location_npcs(L2 + "add/t66", ({ GNOME, GNOME, GNOME }));
    set_location_npcs(L2 + "add/t67", ({ GNOME, GNOME, GNOME, GNOME }));
    set_location_npcs(L2 + "add/t68", ({ GNOME, GNOME, BAT }));
    set_location_npcs(L2 + "add/t69", ({ GNOME, GNOME, GNOME }));
    set_location_npcs(L2 + "add/t70", ({ GNOME, GNOME, BAT }));	
    set_location_npcs(L2 + "add/t71", ({ GNOME, GNOME, BAT }));



    set_location_commands(L2 + "n6", 
        ({"mine", MASTER, "do_mine", 
          "dig", MASTER, "do_mine",
          "pick", MASTER, "do_mine",
          "cut", MASTER, "do_mine",
          "hammer", MASTER, "do_mine", 
          "chisel", MASTER, "do_mine"}));
		  
    set_location_commands(L2+ "add/r9b", 
        ({"mine", MASTER, "do_crack", 
          "dig", MASTER, "do_crack",
          "pick", MASTER, "do_crack",
          "widen", MASTER, "do_crack",
          "move", MASTER, "do_crack"}));
		  
    set_location_commands(L2 + "s7", 
        ({"mine", MASTER, "do_mine", 
          "dig", MASTER, "do_mine",
          "pick", MASTER, "do_mine",
          "cut", MASTER, "do_mine",
          "hammer", MASTER, "do_mine", 
          "chisel", MASTER, "do_mine"}));

    set_location_commands(L2 + "w3", 
        ({"mine", MASTER, "do_mine", 
          "dig", MASTER, "do_mine",
          "pick", MASTER, "do_mine",
          "cut", MASTER, "do_mine",
          "hammer", MASTER, "do_mine", 
          "chisel", MASTER, "do_mine"}));

    set_location_commands(L2+ "add/t23", 
        ({"mine", MASTER, "do_mine", 
          "dig", MASTER, "do_mine",
          "pick", MASTER, "do_mine",
          "cut", MASTER, "do_mine",
          "hammer", MASTER, "do_mine", 
          "chisel", MASTER, "do_mine"}));

    set_location_commands(L2+ "add/t24", 
        ({"mine", MASTER, "do_mine", 
          "dig", MASTER, "do_mine",
          "pick", MASTER, "do_mine",
          "cut", MASTER, "do_mine",
          "hammer", MASTER, "do_mine", 
          "chisel", MASTER, "do_mine"}));

    set_location_commands(L2+ "add/t3", 
        ({"mine", MASTER, "do_mine", 
          "dig", MASTER, "do_mine",
          "pick", MASTER, "do_mine",
          "cut", MASTER, "do_mine",
          "hammer", MASTER, "do_mine", 
          "chisel", MASTER, "do_mine"}));		  

    set_location_commands(L2+ "add/t25", 
        ({"mine", MASTER, "do_mine", 
          "dig", MASTER, "do_mine",
          "pick", MASTER, "do_mine",
          "cut", MASTER, "do_mine",
          "hammer", MASTER, "do_mine", 
          "chisel", MASTER, "do_mine"}));	

    set_location_commands(L2+ "add/t26", 
        ({"mine", MASTER, "do_mine", 
          "dig", MASTER, "do_mine",
          "pick", MASTER, "do_mine",
          "cut", MASTER, "do_mine",
          "hammer", MASTER, "do_mine", 
          "chisel", MASTER, "do_mine"}));

    set_location_commands(L2+ "add/t44", 
        ({"mine", MASTER, "do_crack", 
          "dig", MASTER, "do_crack",
          "pick", MASTER, "do_crack",
          "widen", MASTER, "do_crack", 
          "move", MASTER, "do_crack"}));

    set_location_commands(L2+ "add/t54b", 
        ({"mine", MASTER, "do_collect", 
          "dig", MASTER, "do_crack",
          "pick", MASTER, "do_crack",
          "widen", MASTER, "do_crack", 
          "move", MASTER, "do_crack",
		  "collect", MASTER, "do_collect",
		  "scrape", MASTER, "do_collect",
          "harvest", MASTER, "do_collect",
		  "gather", MASTER, "do_collect"}));
		  
    set_location_commands(L2+ "add/t54c", 
        ({"mine", MASTER, "do_collect", 
		  "collect", MASTER, "do_collect",
		  "scrape", MASTER, "do_collect",
          "harvest", MASTER, "do_collect",
		  "gather", MASTER, "do_collect"}));
		  
    set_location_commands(L2+ "add/t59", 
        ({"mine", MASTER, "do_mine", 
          "dig", MASTER, "do_mine",
          "pick", MASTER, "do_mine",
          "cut", MASTER, "do_mine",
          "hammer", MASTER, "do_mine", 
          "chisel", MASTER, "do_mine"}));

    set_location_commands(L2+ "add/t60", 
        ({"mine", MASTER, "do_mine", 
          "dig", MASTER, "do_mine",
          "pick", MASTER, "do_mine",
          "cut", MASTER, "do_mine",
          "hammer", MASTER, "do_mine", 
          "chisel", MASTER, "do_mine"}));		

    set_location_commands(L2+ "add/t61", 
        ({"mine", MASTER, "do_mine", 
          "dig", MASTER, "do_mine",
          "pick", MASTER, "do_mine",
          "cut", MASTER, "do_mine",
          "hammer", MASTER, "do_mine", 
          "chisel", MASTER, "do_mine"}));	

    set_location_commands(L2+ "add/t68", 
        ({"mine", MASTER, "do_mine", 
          "dig", MASTER, "do_mine",
          "pick", MASTER, "do_mine",
          "cut", MASTER, "do_mine",
          "hammer", MASTER, "do_mine", 
          "chisel", MASTER, "do_mine"}));	

    set_location_commands(L2+ "add/t70", 
        ({"mine", MASTER, "do_mine", 
          "dig", MASTER, "do_mine",
          "pick", MASTER, "do_mine",
          "cut", MASTER, "do_mine",
          "hammer", MASTER, "do_mine", 
          "chisel", MASTER, "do_mine"}));	

    set_location_commands(L2+ "add/t72", 
        ({"mine", MASTER, "do_mine", 
          "dig", MASTER, "do_mine",
          "pick", MASTER, "do_mine",
          "cut", MASTER, "do_mine",
          "hammer", MASTER, "do_mine", 
          "chisel", MASTER, "do_mine"}));

		  		  
}

/*
 *  Commands added via set_location_commands
 */

/*
 * Function name: do_mine
 * Description:   Do we mine here?
 * Returns:       0 - no; 1 - yes.
 */

int do_mine(string str)
{
    string   what, with;
    object   wep, ob;
    int      n;

    notify_fail(capitalize(query_verb()) + " where with what?\n");
    if(!str || !strlen(str))
    return 0;

    if(!parse_command(str, ({}), "'here' / 'wall' / 'vein' [for] [ore] / [gems] / [coal] %s", with))
    return 0;

    notify_fail("You are too busy fighting right now.\n");
    if(this_player()->query_attack())
    return 0;

    notify_fail("It is too dark to see.\n");
    if(!CAN_SEE_IN_ROOM(this_player()))
    return 0;

    notify_fail("You are too tired.\n");
    if(this_player()->query_fatigue() < 20)
    return 0;

    if(!strlen(with))
    {
        write("You try to "+ query_verb() +" with your bare hands, to "
         +"little effect.\n");
        this_player()->add_fatigue(-5);
        return 1;
    }

    notify_fail(capitalize(query_verb()) + " what with what?\n");
    if(!parse_command(with, this_player(), "'with' [my] / [the] %o", wep))
    return 0;

    if(wep->query_wielded() != this_player())
    {
        this_player()->catch_msg("You would need to be wielding " 
            + LANG_THESHORT(wep)+ " first.\n");
        return 1;
    }

    /* Start mining */
    this_player()->catch_msg("You begin to "+ query_verb() +" with " + 
        LANG_THESHORT(wep) +".\n");
    say(QCTNAME(this_player()) +" "+ query_verb() +"s with "+
       LANG_THESHORT(wep) +".\n");  
    /* Mining is tiring */
    this_player()->add_fatigue(-5);
    /* Mining dulls tools */
    wep->set_dull(wep->query_dull() + 1);      

    /* If I've found 20 objects already, I'm not finding any more */   
    n = this_player()->query_prop("_avenir_dark_found");
    if (n > 20)
    {
        this_player()->catch_msg("You don't make a single dent. "+
           "You shouldn't even bother trying again.\n");
        return 1;    
    }
    /* What I can find */
    switch (random(5))
    {   
        case 0:
            ob = RANDOM_GEM_BY_RARITY(GEM_RARE);    break;
        case 1:
            ob = clone_object(DARK +"obj/ore");    break;
        case 2..4:
            ob = clone_object("/d/Avenir/common/obj/coal");    break;        
        default: ob = clone_object("/d/Avenir/common/obj/coal");
    }

    /* Make sure to add to the counter */
    this_player()->add_prop("_avenir_dark_found", n + 1);

    /* I get some general experience for succeeeding */
    this_player()->add_exp_general(50 + random(20));
    ob->move(this_player(), 1);          
    this_player()->catch_msg("You find "+LANG_ASHORT(ob)+".\n");
    return 1;
}



/*
 * Function name: do_crack
 * Description:   Do we move or mine stuff here?
 * Returns:       0 - no; 1 - yes.
 */

int do_crack(string str)
{
    int iprop;
    object tp = this_player();
    object ospace;
    string space;
	
    notify_fail(capitalize(query_verb()) + " what?\n");
    if(!str || !strlen(str))
    return 0;

    if(!parse_command(str, ({}), "'crack' / 'rent' / 'rubble' / 'opening'"))
    return 0;

    notify_fail("You are too busy fighting right now.\n");
    if(this_player()->query_attack())
    return 0;

    notify_fail("It is too dark to see.\n");
    if(!CAN_SEE_IN_ROOM(this_player()))
    return 0;

    notify_fail("You are too tired.\n");
    if(this_player()->query_fatigue() < 20)
    return 0;

    /* Start mining */
    this_player()->catch_msg("You begin to "+ query_verb() +".\n");
    say(QCTNAME(this_player()) +" "+ query_verb() +"s here.\n");  
    /* Mining and moving rubble is tiring */
    this_player()->add_fatigue(-5);

    if (random(7) != 0)	
    {
	    write("You've managed to widen the opening a bit, but there isn't "+
          "enough room for you to fit through it.\n");
		return 1;
    }
	else
    {
        iprop = (ENV(TP))->query_prop("_av_mine_special");
        if (iprop == 1) 
          space = "t44b";
        if (iprop == 2) 
          space = "r9c";
        if (iprop == 3) 
          space = "t54c";	  
 	}	

    if ((!iprop) || (!space))
    {   
      write("There just isn't enough space for you there.\n");
      return 1;
    }

    ospace = find_object(L2+"add/"+space);

	// If the player's volume exceeds the size of the space 
    // then the player can't fit into it.
	if (this_player()->query_prop(OBJ_I_VOLUME) > 100000)
    {   
        write("You aren't able to widen the opening any further.\n"+
        "There isn't enough room for you.\n");
        return 1;
    }

    write("You widen the opening and wedge yourself into it "+
	    "deeply enough to avoid notice.\n");
    say(QCTNAME(tp) + " leaves.\n");
    tp->move_living("X", L2 +"add/"+space, 1, 0);
    return 1;

		
}

/*
 * Function name: do_collect
 * Description:   Do we collect bat guano here?
 * Returns:       0 - no; 1 - yes.
 */
 

int do_collect(string str)
{
	object ob;
	int n;
	
    notify_fail(capitalize(query_verb()) + " what?\n");
    if(!str || !strlen(str))
    return 0;

    if(!parse_command(str, ({}),
        "[bat] 'guano' [from] / [on] [the] [floor] / [ground]"))
    return 0;

    notify_fail("You are too busy fighting right now.\n");
    if(this_player()->query_attack())
    return 0;

    notify_fail("It is too dark to see.\n");
    if(!CAN_SEE_IN_ROOM(this_player()))
    return 0;

    notify_fail("You are too tired.\n");
    if(this_player()->query_fatigue() < 20)
    return 0;

    /* Start collecting */
    this_player()->catch_msg("You try to "+ query_verb() +" "+
       "bat guano from the floor.\n");
    say(QCTNAME(this_player()) +" seems to be looking for something on "+
        "the floor.\n");
		
    /* If I've found 20 objects already, I'm not finding any more */   
    n = this_player()->query_prop("_avenir_guano_found");
    if (n > 3)
    {
        this_player()->catch_msg("You manage to smear your hands "+
           "with bat guano but it is too thin to collect.\n"+
           "You shouldn't even bother trying again.\n");
        return 1;    
    }
 
    /* Make sure to add to the counter */
    this_player()->add_prop("_avenir_guano_found", n + 1);

    /* I get some general experience for succeeeding */
    this_player()->add_exp_general(50 + random(20));

    ob = clone_object("/d/Avenir/common/obj/guano");
    ob->move(this_player(), 1);          
    this_player()->catch_msg("You collect "+LANG_ASHORT(ob)+" from "+
        "the floor.\n");
    return 1;
}

