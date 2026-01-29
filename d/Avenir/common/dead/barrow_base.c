// file name:   /d/Avenir/common/dead/barrow_base.c
// creator(s):  Lilith, Aug 2021: separated from dead.c for SMIS placer purposes.
// last update: Lilith, Sept 2021: typo fix.
//              Lilith, Oct 2021: fixed set_terrain runtime error.
//              Lilith, May 2022: Fixed typo.
//
// purpose:  The Barrow under the cairn hill is the place where the goblins 
//           work on the island live.
//           This file contains standard descriptions and most of the 
//           functions called from the barrow rooms.
// note:     Thanks to Zizuph for his help.
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/room";
inherit "/d/Avenir/inherit/room_tell";

/* Include the herb search functions */
#include "/d/Avenir/common/herbs/herbsearch.h"
#include "/sys/terrain.h"
#include "dead.h"
string *cv = HERB_MASTER->query_herbs( ({"cave"}) );

string *gob_desc = ({"Massive tree timbers line the ceiling "
  +"of this space, supported by monolithic stones.", 
   "You feel as though the weight of the mound of earth above "
  +"is pressing into you.",
   "The feldspar in the white granite monoliths scatter "
  +"light, giving a somewhat festive air to this dismal place.",
   "The granite stone walls glisten with condensed moisture.",
   "Inside this barrow mound, it is obvious that its residents "
  +"are very much alive.",
   "The air is redolent with goblin-musk and the scent of fish.",
   });
  
  
string *gob_desc2 = ({"The floor is mostly well-packed dirt "
  +"and mats made from marsh grasses.",
  "The evidence of daily life is scattered throughout the space. ",
  "Rushlights line the walls, laying in little niches chipped into "
  +"the standing stones.",
  "A burial mound isn't a place most people would want to live in "
  +"but it is obvious that many people call it home.", 
  "There is a surprising lack of filth and clutter here. There is "
  +"mess, of course, but nothing like you might expect.",
  "The earthen floor absorbs the sound of your footsteps.",
  "A few mats are lined up against the wall and piled with dried "
  +"grasses and herbs. These beds look more comfortable than "
  +"many you have slept on in the past."});

string *gob_adjs = ({"dank","warm","close","smelly","tidy",
   "messy","smoky","dim", "musty", "cozy", "earth"});
string *gob_shorts =({ "barrow room", "niche", "nook", "tomb" });

/* This is for creating the rooms */
void create_barrow_room()
{
	
}

public void 
reset_domain_room()  
{
    set_searched(0);
	::reset_domain_room();
}

/*
 * Function name: create_domain_room
 * Description:   This function creates a SMIS-enabled room.
 */

public void
create_domain_room()
{
    set_area("barrowp");
    create_barrow_room();
    reset_domain_room();
	
}

/* Descriptions and functions for the barrow rooms,
 * in /common/dead/barrow/
 */
void
gob_long(string desc)
{
    set_long("Deep inside a cairn, in a dim space that feels "+
	    "small and close despite its massive scale. "+desc+"\n");
    set_short(gob_adjs[random(sizeof(gob_adjs))] + " " +
        gob_shorts[random(sizeof(gob_shorts))]);
    add_item(({"grass","grasses","plants","herbs","piles"}),
        "Herbs and marsh grasses have been strewn onto the mats "
        +"that are used for bedding.\n");
    add_item(({"mat", "mats"}),"Mats have be spread out on "
	+"the dirt floor. Herbs and marsh grasses have been "
	+"added to make them more comfortable and sweet-smelling.\n");
    add_item(({"ground", "floor","dirt floor","earthen floor"}),
	"The dirt underfoot is hard-packed and mostly dry.\n");
    add_item(({"ceiling","roof","timbers","tree trunks","wood"}),
	"Straining your eyes in the dim light, you can see that "
        +"the ceiling is made of whole trees stretched across the "
	+"tops of the megaliths the cairn is built from.\n");
    add_item(({"stones","stone","megaliths", "monoliths", "walls"}),
	"Massive stones made of white granite flecked with feldspar "
        +"and quartz, they support the tremendous weight of the "
        +"hill above you.\n");
    add_item(({"lights", "rushlights", "rushlight", "candles"}),
	"These simple light sources are made of rushes taken from "
	+"the marsh, their stems peeled and then dipped in animal "
	+"fat to make them burn longer and brighter.\n");
    add_cmd_item(({"ground","here","hole","in ground","earth"}),
        "dig","It is too hard-packed to make digging into "
        +"it worthwhile.\n");
    IN;    // underground
    IN_IN; // indoors
    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_I_HIDE, 1);
    set_terrain(TERRAIN_RESIDENCE | TERRAIN_SHADOWS | TERRAIN_UNDERGROUND | TERRAIN_ROCK);

}


/* Barrow goblin camp */
void 
gob_exit(string locus, string dir)
{
    add_exit(BARROW+"barrow"+locus, dir);
}

/* In misty rooms, we cover up objects
 * that are dropped.
 */
void cover(object ob)
{
    int   foggy;

    if(!objectp(ob) || !present(ob) || ob->query_prop(OBJ_I_HIDE))
	return;

    if(!(foggy = ENV(ob)->query_prop("cover_in_fog")))
	return;
    else
	tell_room(ENV(ob), CAP(LANG_THESHORT(ob)) +
	  (function_exists("create_heap", ob) && 
	    ob->num_heap() != 1 ? " are " : " is ") +
	  "covered over by mist.\n");

    ob->add_prop(OBJ_I_HIDE, foggy + random(40));
    // Thanks to Aridor for the is/are toggle
}

/* Start up the room tells now */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
	start_room_tells();
    set_tell_time(150);

    if(query_prop("cover_in_fog") && !living(ob))
    {
        set_alarm(itof(random(10) + 1), 0.0, &cover(ob) );
    }
}

