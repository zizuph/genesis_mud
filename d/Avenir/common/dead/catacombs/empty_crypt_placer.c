// file name:        /d/Avenir/common/dead/catacombs/crypt_placer.c
// creator(s):       Lilith, May 2021
// revision history: Lilith, Sep 2021 updated placements
// purpose:          Module that places mobs and objs in the Crypt
// note:             This makes it easier to update clone locations 
//                   in such a big area (100+ rooms)
// bug(s):           
// to-do:

#include <macros.h>

#include "../dead.h"

#include "/d/Avenir/smis/smis.h"
#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/smis/sys/statserv.h"

inherit SMIS_MODULE_PLACER;

// Could have put these in dead.h but they are only used here.
#define BOGL      "/d/Avenir/common/dead/mon/bogl_on_duty"
#define GRUB      "/d/Avenir/common/outpath/mon/grub"
#define GRUB_MOM  "/d/Avenir/common/outpath/mon/mommy"
#define HEGEMON   "/d/Avenir/common/dead/mon/hegemon_ghost"
#define HBENDER   "/d/Avenir/common/dead/mon/hellbender"
#define MILLI     "/d/Avenir/common/outpath/mon/millipede"
#define MREVENANT "/d/Avenir/common/dead/mon/revenant_m"
#define RAT       "/d/Avenir/common/dead/mon/rat"
#define REVENANT  "/d/Avenir/common/dead/mon/revenant"
#define SPIDER    "/d/Avenir/common/outpath/mon/spider"
#define SKELETON  "/d/Avenir/common/dead/mon/skeleton"
#define CRATE     "/d/Avenir/common/dead/obj/bogl_crate"
#define COFFIN    "/d/Avenir/common/dead/obj/sarcophagus"
#define RUSHLT    "/d/Avenir/common/dead/obj/rushlight"
#define ROTCLOTH  "/d/Avenir/common/dead/obj/rotted_cloth"
#define WALLSAIR  "/d/Avenir/common/dead/obj/wall_sair"

void create_placer()
{

    /* Prevents computation of the list of rooms this module operates
       on: keeps rooms from cluttering the decision tables. */
    disable_notifications_autoset();
	
    set_module_id("catacombs");
    set_module_description("Placer module for the crypts");

    /* gatekeeper */
    set_location_npc(CRYPT  + "crypt_entr", MON +"chatelaine");
	
	set_location_npc(CRYPT  + "crypt_s1",   REVENANT);
    set_location_npc(CRYPT  + "crypt_s2",   REVENANT);
    set_location_npc(CRYPT  + "crypt_s3",   REVENANT);
    set_location_npc(CRYPT  + "crypt_s4",   REVENANT);
    set_location_npc(CRYPT  + "crypt_s5",   REVENANT);
    set_location_npc(CRYPT  + "crypt_s6",   REVENANT);	
	set_location_npcs(CRYPT + "crypt_s7",  ({ REVENANT, HEGEMON}));

    set_location_npc(CRYPT  + "crypt12",    MREVENANT);   	
    set_location_npc(CRYPT  + "crypt81",    MREVENANT); 	
    set_location_npc(CRYPT  + "crypt9",     MREVENANT);
    set_location_npc(CRYPT  + "crypt90",    MREVENANT);		
	set_location_npc(CRYPT  + "crypt100",   MREVENANT);
    set_location_npc(CRYPT  + "crypt1",     MREVENANT);
	set_location_npc(CRYPT  + "crypt36",    MREVENANT);
   
	set_location_npc(CRYPT  + "crypt5",     GRUB);
    set_location_npc(CRYPT  + "crypt15",    GRUB);
    set_location_npc(CRYPT  + "crypt25",    GRUB);
    set_location_npc(CRYPT  + "crypt35",    GRUB);
    set_location_npc(CRYPT  + "crypt45",    GRUB);
    set_location_npc(CRYPT  + "crypt55",    GRUB);
    set_location_npc(CRYPT  + "crypt65",    GRUB);
	set_location_npcs(CRYPT + "crypt75",  ({ GRUB, MILLI }));
	
	set_location_npc(CRYPT  + "crypt73",    MILLI);
	set_location_npc(CRYPT  + "crypt83",    MILLI);
	set_location_npc(CRYPT  + "crypt93",    MILLI);
	set_location_npc(CRYPT  + "crypt103",   MILLI);
	set_location_npcs(CRYPT + "crypt110", ({ MILLI, RAT }));

	set_location_npc(CRYPT  + "crypt10",    RAT);
	set_location_npc(CRYPT  + "crypt20",    RAT);
	set_location_npc(CRYPT  + "crypt30",    RAT);
	set_location_npcs(CRYPT + "crypt40", ({ RAT, SPIDER }));
	set_location_npc(CRYPT  + "crypt50",    RAT);
	set_location_npc(CRYPT  + "crypt60",    RAT);
	set_location_npcs(CRYPT + "crypt70", ({ RAT, SPIDER}));

	set_location_npc(CRYPT  + "crypt80",    SPIDER);
	set_location_npc(CRYPT  + "crypt85",    SPIDER);
	set_location_npc(CRYPT  + "crypt13",    SPIDER);
	set_location_npc(CRYPT  + "crypt95",    SPIDER);

    set_location_npcs(CRYPT + "crypt4",   ({ RAT, RAT}));	
    set_location_npcs(CRYPT + "crypt29",  ({ RAT, SPIDER }));
	
	// worker crew
    set_location_npcs(CRYPT + "crypt66",  ({ BOGL, BOGL, BOGL }));
	
	set_location_npcs(CRYPT + "crypt22",  ({ GRUB, GRUB_MOM, RAT}));
    set_location_npcs(CRYPT + "crypt42",  ({ GRUB, MILLI }));
    set_location_npcs(CRYPT + "crypt62",  ({ GRUB, GRUB_MOM }));
    set_location_npcs(CRYPT + "crypt82",  ({ GRUB, GRUB, GRUB_MOM }));
    set_location_npcs(CRYPT + "crypt102", ({ GRUB, GRUB_MOM }));
    set_location_npcs(CRYPT + "crypt92",  ({ SPIDER, MILLI }));
    set_location_npcs(CRYPT + "pit_of_despair", ({ GRUB, GRUB_MOM }));
	
    set_location_npcs(CRYPT+ "crypt11", ({ HBENDER,HBENDER }));
	set_location_npcs(CRYPT+ "crypt18", ({ HBENDER, HBENDER }));
	set_location_npcs(CRYPT+ "crypt88", ({ HBENDER,HBENDER }));
	set_location_npcs(CRYPT+ "crypt101",({ HBENDER,HBENDER}));
	set_location_npcs(CRYPT+ "crypt108",({ HBENDER }));
	
    set_location_object(CRYPT  + "crypt_s1",  COFFIN);
    set_location_object(CRYPT  + "crypt_s2",  COFFIN); 
    set_location_object(CRYPT  + "crypt_s3",  COFFIN); 
    set_location_objects(CRYPT + "crypt_s4", ({ COFFIN, COFFIN }));
    set_location_objects(CRYPT + "crypt_s5", ({ COFFIN, COFFIN })); 
    set_location_objects(CRYPT + "crypt_s6", ({ COFFIN, COFFIN })); 
    set_location_object(CRYPT  + "crypt_s7",   COFFIN);
	
    set_location_object(CRYPT + "crypt2",    ROTCLOTH);
    set_location_object(CRYPT + "crpt12",    ROTCLOTH);
    set_location_object(CRYPT + "crypt42",   ROTCLOTH);
    set_location_object(CRYPT + "crypt52",   ROTCLOTH);
	
    set_location_object(CRYPT + "crypt104",  CRATE);
    set_location_object(CRYPT + "crypt84",   CRATE);
    set_location_object(CRYPT + "crypt64",   CRATE);	
    set_location_object(CRYPT + "crypt93",   CRATE);	
    set_location_object(CRYPT + "crypt24",   CRATE);
    set_location_object(CRYPT + "crypt4",    CRATE);
	
    set_location_object(CRYPT + "crypt105",  WALLSAIR);
    set_location_object(CRYPT + "crypt72",   WALLSAIR);
    set_location_object(CRYPT + "crypt78",   WALLSAIR);
    set_location_object(CRYPT + "crypt99",   WALLSAIR);
	
    set_location_commands(CRYPT +"crypt11",  ({ "enter", MASTER, "do_dive",
	    "jump",  MASTER, "do_dive", "swim", MASTER, "do_dive",
		"drink", MASTER, "do_drink", "sip", MASTER, "do_drink"}));
    set_location_commands(CRYPT +"crypt18",  ({ "enter", MASTER, "do_dive",
	    "jump",  MASTER, "do_dive", "swim", MASTER, "do_dive",
		"drink", MASTER, "do_drink", "sip", MASTER, "do_drink"}));
    set_location_commands(CRYPT +"crypt88",  ({ "enter", MASTER, "do_dive",
	    "jump",  MASTER, "do_dive", "swim", MASTER, "do_dive",
		"drink", MASTER, "do_drink", "sip", MASTER, "do_drink"}));
    set_location_commands(CRYPT +"crypt101",  ({ "enter", MASTER, "do_dive",
	    "jump",  MASTER, "do_dive", "swim", MASTER, "do_dive",
		"drink", MASTER, "do_drink", "sip", MASTER, "do_drink"}));
    set_location_commands(CRYPT +"crypt108",  ({ "enter", MASTER, "do_dive",
	    "jump",  MASTER, "do_dive", "swim", MASTER, "do_dive",
		"drink", MASTER, "do_drink", "sip", MASTER, "do_drink"}));

    set_location_commands(CRYPT +"crypt4",  ({ "climb", MASTER, "do_climb",
	    "jump",  MASTER, "do_climb"}));
    set_location_commands(CRYPT + "crypt104", ({ "climb", MASTER, "do_climb",
	    "jump",  MASTER, "do_climb"}));
    set_location_commands(CRYPT + "crypt64",  ({ "climb", MASTER, "do_climb",
	    "jump",  MASTER, "do_climb"}));	
    set_location_commands(CRYPT + "crypt84",  ({ "climb", MASTER, "do_climb",
	    "jump",  MASTER, "do_climb"}));
    set_location_commands(CRYPT + "crypt93",  ({ "climb", MASTER, "do_climb",
	    "jump",  MASTER, "do_climb"}));	
    set_location_commands(CRYPT + "crypt24",  ({ "climb", MASTER, "do_climb",
	    "jump",  MASTER, "do_climb"}));
 		

}

/*
 * Function name: do_dive
 * Description:   Do we dive into the pool?
 * Returns:       0 - no; 1 - yes.
 */
int
do_dive(string str)
{
    object tp = this_player();

    if (!str)
        return 0;

    notify_fail("You can't do that.\n");
    if (!parse_command(str, ({ }), "[into] [the] 'water' / 'pool'"))
        return 0;    
   
    // In they go! Good luck!
    write("You dive into the brackish pool of water.\n");
    say(QCTNAME(tp) + " dives into the water and sinks below the surface!\n");
	tp->move_living("M", CRYPT+"crypt_pool");
	STATSERV_LOG_EVENT("crypt", "Left by pool");
    return 1;
}

/*
 * Function name:  do_drink
 * Description:    Do we drink from the water?
 * Returns:        0 - no; 1 - yes.
 */
int
do_drink(string str)
{
    object tp = this_player();

    if (!str)
        return 0;

    notify_fail("You can't do that.\n");
    if (!parse_command(str, ({ }),  "[from] [the] 'water' / 'pool'"))
        return 0;    

    write("You kneel at the water's edge and scoop up a handful "+
        "of water, but the smell stops you. It's not fresh water.\n");
    say(QCTNAME(tp) + " starts to drink from the pool and stops.\n");
    return 1;
} 


// climb into the niche
int
do_climb(string str)
{
    object tp = this_player();
    int niche;

	string room;
	
    if (!str)
        return 0;

    notify_fail("What?\n");
    if (!parse_command(str, ({ }), "[up] [on] / [into] [the] 'chest' / 'niche' / 'tier'"))
        return 0;    
	niche = (ENV(TP))->query_prop("_catacomb_niche");     	
	switch (niche)
	{
	    case 0: 
	         break;
		case 1:
		    room = "crypt_n1";
			break;
		case 2:
		    room = "crypt_n2";
			break;
		case 3:
		    room = "crypt_n3";
		    break;
		case 4:
		    room = "crypt_n4";
		    break;
		case 5:
		    room = "crypt_n5";
			break;
		case 6:
		    room = "crypt_n6";
			break;
		default:
	}

    if (!niche)
        return 0;	     
		        
    // Up they go!
    write("You climb up on the chest and scootch into a niche.\n");
    say(QCTNAME(tp) + " leaves.\n");
	tp->move_living("M", CRYPT+room, 1, 1);
	STATSERV_LOG_EVENT("crypt", "Found niche");
    return 1;
}