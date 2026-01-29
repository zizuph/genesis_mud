// file name:        /d/Avenir/common/dead/catacombs/crypt_placer.c
// creator(s):       Lilith, May 2021
// revisions: Lilith, Sep 2021 updated placements
//            Lilith, Oct 2021 moved myth revs to guard room outside
//                   since they are really big and block access to
//                   sarcophagi, making Mask quest too hard. 
//                   Updated do_climb checks and messages.   
//              Lilith Jan 2022: modified do_climb to test for living
//                   as volume test was too low at 100k, changed to 150k.                 
// purpose:          Module that places mobs and objs in the Crypt
// note:             This makes it easier to update clone locations 
//                   in such a big area (140 rooms)
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
#define CTHULUJR  "/d/Avenir/common/dead/mon/cthulujr"
#define GRUB      "/d/Avenir/common/outpath/mon/grub"
#define GRUB_MOM  "/d/Avenir/common/outpath/mon/mommy"
#define HEGEMON   "/d/Avenir/common/dead/mon/hegemon_ghost"
#define HBENDER   "/d/Avenir/common/dead/mon/hellbender"
#define MILLI     "/d/Avenir/common/outpath/mon/millipede"
#define MREVENANT "/d/Avenir/common/dead/mon/revenant_m"
#define RAT       "/d/Avenir/common/dead/mon/rat"
#define REVENANT  "/d/Avenir/common/dead/mon/revenant"
#define REV_SARC  "/d/Avenir/common/dead/mon/revenant_sarc"
#define SKELETON  "/d/Avenir/common/dead/mon/skeleton"
#define SPIDER    "/d/Avenir/common/outpath/mon/spider"

#define COFFIN    "/d/Avenir/common/dead/obj/sarcophagus"
#define CRATE     "/d/Avenir/common/dead/obj/bogl_crate"
#define ROTCLOTH  "/d/Avenir/common/dead/obj/rotted_cloth"
#define RUSHLT    "/d/Avenir/common/dead/obj/rushlight"
#define SHELF     "/d/Avenir/common/dead/obj/shelf_pool"


void create_placer()
{

    /* Prevents computation of the list of rooms this module operates
       on: keeps rooms from cluttering the decision tables. */
    disable_notifications_autoset();

    set_module_id("catacombs");
    set_module_description("Placer module for the crypts");

    /* NPC Cloning: */
    /* gatekeeper */
    set_location_npc(CRYPT  + "crypt_entr", MON +"chatelaine");
    /* goblin workers */
    set_location_npcs(CRYPT + "crypt66",  ({ BOGL, BOGL, BOGL }));

    /* Sarcophagus rooms */
    set_location_npc(CRYPT  + "crypt_s1",    REV_SARC);
    set_location_npc(CRYPT  + "crypt_s2",    REV_SARC);
    set_location_npc(CRYPT  + "crypt_s3",    REV_SARC);
    set_location_npc(CRYPT  + "crypt_s4",    REV_SARC);
    set_location_npc(CRYPT  + "crypt_s5",    REV_SARC);
    set_location_npc(CRYPT  + "crypt_s6",    REV_SARC);	
    set_location_npcs(CRYPT + "crypt_s7", ({ REV_SARC, HEGEMON}));

    /* Locations for this group are just outside the sarcophagus rooms */	
    set_location_npc(CRYPT  + "crypt1",      MREVENANT);
    set_location_npc(CRYPT  + "crypt9",      MREVENANT);
    set_location_npc(CRYPT  + "crypt12",     MREVENANT);   	
    set_location_npc(CRYPT  + "crypt36",     MREVENANT);
    set_location_npc(CRYPT  + "crypt81",     MREVENANT); 	
    set_location_npc(CRYPT  + "crypt90",     MREVENANT);		
    set_location_npc(CRYPT  + "crypt100",    MREVENANT);

    /* Rooms grouped by tens */
    set_location_npcs(CRYPT + "crypt2",   ({ GRUB, GRUB_MOM, RAT }));
    set_location_npcs(CRYPT + "crypt4",   ({ REVENANT, RAT }));
    set_location_npcs(CRYPT + "crypt5",   ({ GRUB, REVENANT }));
    set_location_npcs(CRYPT + "crypt7",   ({ REVENANT, REVENANT }));
    set_location_npcs(CRYPT + "crypt8",   ({ REVENANT, SPIDER }));

    set_location_npc(CRYPT  + "crypt10",     RAT);
    set_location_npcs(CRYPT + "crypt11",  ({ HBENDER, CTHULUJR }));
    set_location_npcs(CRYPT + "crypt14",  ({ REVENANT, RAT }));
    set_location_npcs(CRYPT + "crypt15",  ({ REVENANT, GRUB }));
    set_location_npcs(CRYPT + "crypt17",  ({ REVENANT, GRUB_MOM }));
    set_location_npcs(CRYPT + "crypt18",  ({ HBENDER, HBENDER }));

    set_location_npcs(CRYPT + "crypt20",  ({ REVENANT, MILLI }));
    set_location_npcs(CRYPT + "crypt21",  ({ REVENANT, REVENANT }));
    set_location_npcs(CRYPT + "crypt22",  ({ GRUB, GRUB_MOM, RAT}));
    set_location_npcs(CRYPT + "crypt25",  ({ REVENANT, SKELETON }));
    set_location_npcs(CRYPT + "crypt28",  ({ REVENANT, SKELETON }));
    set_location_npcs(CRYPT + "crypt29",  ({ REVENANT, SPIDER }));

    set_location_npcs(CRYPT + "crypt30",  ({ RAT, GRUB }));	
    set_location_npcs(CRYPT + "crypt33",  ({ REVENANT, MILLI}));
    set_location_npcs(CRYPT + "crypt35",  ({ REVENANT, RAT}));
    set_location_npcs(CRYPT + "crypt37",  ({ REVENANT, SKELETON}));
    set_location_npc(CRYPT  + "crypt38",     REVENANT);
    set_location_npcs(CRYPT + "crypt39",  ({ REVENANT, REVENANT }));

    set_location_npc(CRYPT  + "crypt40",  ({ RAT, REVENANT }));
    set_location_npcs(CRYPT + "crypt42",  ({ GRUB_MOM, MILLI, RAT }));
    set_location_npcs(CRYPT + "crypt44",  ({ REVENANT, SPIDER }));
    set_location_npc(CRYPT  + "crypt45",     REVENANT);
    set_location_npc(CRYPT  + "crypt47",     REVENANT);

    set_location_npc(CRYPT  + "crypt50",     REVENANT);
    set_location_npc(CRYPT  + "crypt50",     REVENANT);
    set_location_npc(CRYPT  + "crypt50",     RAT);
    set_location_npcs(CRYPT + "crypt55",  ({ REVENANT, REVENANT }));
    set_location_npc(CRYPT  + "crypt58",     REVENANT);

    set_location_npc(CRYPT  + "crypt60",     RAT);
    set_location_npcs(CRYPT + "crypt62",  ({ GRUB, GRUB_MOM }));
    set_location_npcs(CRYPT  + "crypt65", ({ REVENANT, SPIDER }));
    set_location_npc(CRYPT  + "crypt68",     REVENANT);
    set_location_npc(CRYPT  + "crypt69",     REVENANT);

    set_location_npcs(CRYPT + "crypt70",  ({ RAT, SKELETON }));
    set_location_npc(CRYPT  + "crypt71",     REVENANT);
    set_location_npcs(CRYPT + "crypt73",  ({ MILLI, REVENANT }));
    set_location_npcs(CRYPT + "crypt75",  ({ GRUB, SKELETON }));
    set_location_npc(CRYPT  + "crypt76",     REVENANT);
    set_location_npcs(CRYPT + "crypt77",  ({ REVENANT, REVENANT }));

    set_location_npc(CRYPT  + "crypt80",     SPIDER);
    set_location_npcs(CRYPT + "crypt82",  ({ RAT, GRUB, GRUB_MOM }));
    set_location_npc(CRYPT  + "crypt83",     MILLI);
    set_location_npc(CRYPT  + "crypt84",     REVENANT);
    set_location_npcs(CRYPT + "crypt85",  ({ SPIDER, SKELETON }));	
    set_location_npc(CRYPT  + "crypt87",     REVENANT);
    set_location_npcs(CRYPT + "crypt88",  ({ HBENDER, HBENDER }));
    set_location_npcs(CRYPT + "crypt89",  ({ REVENANT, SKELETON, RAT }));

    set_location_npc(CRYPT  + "crypt91",     REVENANT);
    set_location_npcs(CRYPT + "crypt92",  ({ SPIDER, MILLI, REVENANT }));
    set_location_npcs(CRYPT + "crypt93",  ({ REVENANT, MILLI }));
    set_location_npc(CRYPT  + "crypt94",     REVENANT);
    set_location_npc(CRYPT  + "crypt95",     RAT);
    set_location_npc(CRYPT  + "crypt96",     REVENANT);

    set_location_npcs(CRYPT + "crypt101", ({ HBENDER, SKELETON}));
    set_location_npcs(CRYPT + "crypt102", ({ REVENANT, GRUB_MOM }));
    set_location_npcs(CRYPT + "crypt103", ({ REVENANT, MILLI }));
    set_location_npcs(CRYPT + "crypt108", ({ HBENDER, SKELETON }));
    set_location_npc(CRYPT  + "crypt109",    REVENANT);

    set_location_npcs(CRYPT + "crypt110", ({ MILLI, SKELETON, REVENANT }));
    set_location_npc(CRYPT  + "crypt116",    REVENANT);
    set_location_npcs(CRYPT + "crypt117", ({ REVENANT, SPIDER }));

    set_location_npcs(CRYPT + "pit_of_despair", ({ GRUB, GRUB_MOM }));

    /* Object cloning */	
    set_location_object(CRYPT  + "crypt_s1",    COFFIN);
    set_location_object(CRYPT  + "crypt_s2",    COFFIN); 
    set_location_object(CRYPT  + "crypt_s3",    COFFIN); 
    set_location_objects(CRYPT + "crypt_s4", ({ COFFIN, COFFIN }));
    set_location_objects(CRYPT + "crypt_s5", ({ COFFIN, COFFIN })); 
    set_location_objects(CRYPT + "crypt_s6", ({ COFFIN, COFFIN })); 
    set_location_object(CRYPT  + "crypt_s7",    COFFIN);

    set_location_object(CRYPT  + "crypt2",      ROTCLOTH);
    set_location_object(CRYPT  + "crpt12",      ROTCLOTH);
    set_location_object(CRYPT  + "crypt42",     ROTCLOTH);
    set_location_object(CRYPT  + "crypt52",     ROTCLOTH);

    set_location_object(CRYPT  + "crypt104",    CRATE);
    set_location_object(CRYPT  + "crypt84",     CRATE);
    set_location_object(CRYPT  + "crypt64",     CRATE);	
    set_location_object(CRYPT  + "crypt93",     CRATE);	
    set_location_object(CRYPT  + "crypt24",     CRATE);
    set_location_object(CRYPT  + "crypt4",      CRATE);

    /* Same location as the pools */
    set_location_object(CRYPT  + "crypt11",     SHELF);
    set_location_object(CRYPT  + "crypt18",     SHELF);
    set_location_object(CRYPT  + "crypt88",     SHELF);
    set_location_object(CRYPT  + "crypt101",    SHELF);
    set_location_object(CRYPT  + "crypt108",    SHELF);

    /* Room actions */
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


    set_location_commands(CRYPT +"crypt4",    ({ "climb", MASTER, "do_climb",
	"jump",  MASTER, "do_climb"}));
    set_location_commands(CRYPT +"crypt14",   ({ "climb", MASTER, "do_climb",
	"jump",  MASTER, "do_climb"}));
    set_location_commands(CRYPT + "crypt24",  ({ "climb", MASTER, "do_climb",
	"jump",  MASTER, "do_climb"}));
	set_location_commands(CRYPT +"crypt34",   ({ "climb", MASTER, "do_climb",
	"jump",  MASTER, "do_climb"}));
    set_location_commands(CRYPT +"crypt44",   ({ "climb", MASTER, "do_climb",
	"jump",  MASTER, "do_climb"}));
    set_location_commands(CRYPT +"crypt54",   ({ "climb", MASTER, "do_climb",
	"jump",  MASTER, "do_climb"}));
    set_location_commands(CRYPT + "crypt64",  ({ "climb", MASTER, "do_climb",
	"jump",  MASTER, "do_climb"}));
    set_location_commands(CRYPT +"crypt74",   ({ "climb", MASTER, "do_climb",
	"jump",  MASTER, "do_climb"}));	
    set_location_commands(CRYPT + "crypt84",  ({ "climb", MASTER, "do_climb",
	"jump",  MASTER, "do_climb"}));
	set_location_commands(CRYPT +"crypt94",   ({ "climb", MASTER, "do_climb",
	"jump",  MASTER, "do_climb"}));
    set_location_commands(CRYPT + "crypt93",  ({ "climb", MASTER, "do_climb",
	"jump",  MASTER, "do_climb"}));	
    set_location_commands(CRYPT + "crypt104", ({ "climb", MASTER, "do_climb",
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
 * Function name:  do_climb
 * Description:    Do we climb into the niche?
 * Returns:        0 or 1
 */
int
do_climb(string str)
{
    object tp = this_player();
    object oroom;
    int niche;
    string room;

    if (!str)
	return 0;

    notify_fail(capitalize(query_verb()) +" what?\n");
    if (!parse_command(str, ({ }), "[up] [on] / [into] [the] 'chest' / 'niche' / 'tier'"))
	return 0;    
    niche = (ENV(TP))->query_prop("_catacomb_niche");     	
    switch (niche)
    {
    case 0:  break;
    case 1:  room = "crypt_n1"; break;
    case 2:  room = "crypt_n2";	break;
    case 3:  room = "crypt_n3"; break;
    case 4:  room = "crypt_n4"; break;
    case 5:  room = "crypt_n5"; break;
    case 6:  room = "crypt_n6"; break;
    default: break;
    }

    if ((!niche) || (!room))
    {   
	write("You try to climb into the niche but there isn't enough "+
	  "room for you.\n");
        return 1;
    }

	// If the player's volume exceeds the size of the space 
    // then the player can't fit into it.
	if (this_player()->query_prop(OBJ_I_VOLUME) > 150000)
    {   
	write("You try to climb into the niche but there isn't enough "+
	  "room for you.\n");
        return 1;
    }
	
	// There is already someone in there.
    oroom = find_object(CRYPT+room);		
    if(oroom && sizeof(filter(deep_inventory(oroom), living)))
    {   
	write("You try to climb into the niche but there isn't enough "+
	  "room for you.\n");
        return 1;
    }

    // Like the Stump in the Holm, it is a safe place, if it isn't full.
    write("You climb up on the chest and scootch into a niche.\n");
    say(QCTNAME(tp) + " leaves.\n");
    tp->move_living("M", CRYPT+room, 1, 1);
    STATSERV_LOG_EVENT("crypt", "Entered niche");
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
      "of water, but the smell stops you. It's brackish water "+
      "that's too salty for drinking.\n");
    say(QCTNAME(tp) + " starts to drink from the pool and stops.\n");
    return 1;
} 
