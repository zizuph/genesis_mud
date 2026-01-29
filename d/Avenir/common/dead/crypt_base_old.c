// file name:   crypt_base.c
// creator(s):  Lilith -- separated from dead.c for SMIS placer purposes.
// last update: Lilith, Jul-Aug 2021 modifications in preparation of 
//                opening the catacombs. 
// purpose: Inheritable base file for the Catacomb rooms.
//          Contains standard descriptions and most of the functions.
// note:    Thanks to Zizuph for his help.
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/room";
inherit "/d/Avenir/inherit/room_tell";

/* Include the herb search functions */
#include "/d/Avenir/common/herbs/herbsearch.h"
#include "/sys/terrain.h"
#include "dead.h"

string *cv = HERB_MASTER->query_herbs( ({"cave"}) );

string *crypt_desc = ({"The gloom around is nearly impenetrable.",
  "Moisture glistens on the walls here, giving the "
  +"pale limestone a glossy sheen.",
  "Galleries of bodies line the walls as far as "
  +"your eyes can see. The dead appear to far outnumber "
  +"the living.",
  "Niches stuffed with bodies rise in tiers along "
  +"the walls.",
  "Stacked in tiers five or six high, there are "
  +"recesses in the walls filled with countless "
  +"bodies.",
  "Here and there, mushrooms bloom in the dank, "
  +"dark niches, one of the few signs of life in "
  +"these catacombs.",
  "This is another gallery of death and decay, nearly "
  +"identical to the last. You find being here disorienting.", 
  "The scent of death and decay are heavy in the air.",  
  "You feel as if you are violating some sort of "
  +"ageless peace by being here.",
  "Long, deep grooves have been scraped into the walls. "
  +"They look like claw marks made by a preternaturally "
  +"large beast.",
  "A feeling of restlessness and rage presses down on you "
  +"here. It might be a good idea to leave."});
  
string *crypt_desc2 = ({"The ground underfoot is damp and "
  +"with slippery with gore.",
  "The darkness here is oppressive, as if it is "
  +"trying to crush you within it, leaving little "
  +"trace of you and the life you've lived.",
  "The air around you is cold and menacing.",
  "There is an ineffable peace here. The spirits of "
  +"the dead are all around.",
  "A faintly glowing mist rolls along the ground, moved "
  +"by a cold wind from some unknown source.",
  "The floor beneath you is covered by a thin blanket "
  +"of slow moving fog.",
  "There is something disturbing about this mist - it seems "
  +"almost sentient.",
  "A soft, chill wind is moving along the floor here.",
  "Of one thing you feel deeply in your bones, "
  +"nothing alive lives here for very long.",
  "The sound of your footsteps are loud in this quiet, "
  +"subterranean space."});

string *crypt_adjs = ({"black","dark","silent","misty",
  "winding","dismal","haunted"});
string *crypt_shorts = ({"crypts","catacombs","tombs",
  "tunnel", "gallery"});


/* This is for creating the rooms */
void create_crypt_room()
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
    set_area("catacombs");
    create_crypt_room();
    reset_domain_room();
	
}

/* Descriptions and functions for the crypt rooms,
 * in /common/dead/catacombs/
 */
void crypt_long(string desc)
{
    set_long("Hollow white tunnels extend into a stygian "
      +"darkness all about you. The soft limestone "
      +"walls seem to have been chisled from the living "
      +"rock, and above you can only be seen an encompass"
      +"ing impenetrable blackness. "+desc+
	  "\n");
		
    set_short(crypt_adjs[random(sizeof(crypt_adjs))] + " " +
      crypt_shorts[random(sizeof(crypt_shorts))]);

	add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop("cover_in_fog", 40 + random(20));
	add_prop(ROOM_I_LIGHT, -4);
    add_prop(ROOM_I_HIDE, 1);
  	
    add_item(({"wall","walls","limestone", "moisture"}),
	   "The walls of the "
      +"catacombs are made from soft and porous limestone "
      +"that glistens with moisture. Recesses filled with "
	  +"bodies have have been cut into the stone, stretching "
	  +"upwards into the darkness, row upon row.\n");
	add_item(({"hollow", "hollows", "crypt", "crypts", "shelf",
	   "shelves", "recess", "recesses", "tiers", "gallery",
	   "niche", "niches"}), 
	   "Horizontal, oblong niches have been cut into the living stone "
 	  +"of the walls, part of a seemingly endless gallery of "
	  +"vertical tiers holding numerous bodies in various stages "
      +"of decay. \n");
	add_item(({"body", "bodies"}), "The bodies are decayed beyond "
      +"recognition.\n");
	add_item(({"catacomb", "catacombs"}), "These catacombs "
	  +"are where those who die in Sybarus are laid to rest.\n");
    add_item(({"ceiling"}),"The ceiling is farther up than you "
      +"can see. It is obscured from sight.\n");
    add_item(({"floor","ground"}),"The floor is uneven, "
      +"dark, and damp, making footing treacherous.\n");
    add_item(({"mist","fog"}),"A thin white mist moves along "
      +"the ground, making the floor wet and slippery.\nThe "
	  +"mist seems to be moving towards the "
      +TO->query_exit_cmds()[random(sizeof(TO->query_exit_cmds()))]
      +".\n");
    add_item(({"dark","darkness","black","blackness","gloom"}),
      "Darkness is, by its nature, invisible.\n");
    add_item(({"wind","breeze","air"}),"The breeze moving along "
      +"the ground feels cold and damp around your ankles.\n");
	add_item(({"bones", "bonee"}), "There are bones everywhere, "
	  +"some as part of intact skeletons, some stacked neatly "
	  +"by unknown hands, and others strewn about--probably "
	  +"dragged there by rats.\n");

    set_up_herbs(({ GET_ONE(cv), GET_ONE(cv), GET_ONE(cv) }), 
        ({ "walls", "wall", "stone", "ground", "niche",
           "niches", "hollow", "hollows"}), 3);
 	
	set_tell_time(100);
	add_tell("The faintly glowing mist curls into strange shapes.\n");
	add_tell("A peace settles upon this place.\n");
	add_tell("A chill crawls up your spine.\n");
	add_tell("The air is damp and smells faintly of decay.\n");
	add_tell("A droplet of what you hope is water splatters "
	    +"on your face.\n");
	add_tell("A low moaning sound emerges from somewhere nearby.\n");
	add_tell("Something skitters past you, unseen.\n");
	add_tell("You catch a whiff of rotting flesh.\n"); 
	add_tell("Two goblins quietly and unobtrustively place a corpse into "
	    +"one of the niches and then slip away.\n");
	add_tell("A luminous and hauntingly beautiful female figure "
	    +"materializes and then fades from view.\n"); 
    IN_IN;
	set_terrain(({TERRAIN_ROCK, TERRAIN_SHADOWS, TERRAIN_HASDEAD,
        TERRAIN_UNDERGROUND	}));
	
    add_prop(ROOM_S_DARK_MSG, "The darkness around is much too "
      +"thick to");
    add_prop(ROOM_S_DARK_LONG, "The darkness here is thick "
      +"and oppressive. You feel it weigh upon your "
      +"soul.\n");
	 add_prop(ROOM_M_NO_TELEPORT_TO, 1);
	add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_I_HIDE, 1);

		
 }

void
niche_long(string desc)
{
	
    set_long("This is one of the niches hollowed out of the limestone. "
	    +"Normally there would be a corpse decaying here, but it looks "
		+"like the goblin workers use it as a place to rest. There "
		+"is a mat for sleeping on, and you can see crumbs of food "
		+"and bits of fish scattered around. Surprisingly, there "
		+"aren't any rats. "+desc+ "\n"); 
	set_short("funeral niche");
    add_item(({"mat", "sleeping mat"}), "It is a mat woven from the "
        +"grasses that grow in the mashes above. It looks fairly new "
        +"and smells like fresh herbs.\n");
    add_item(({"crumbs", "bits of fish" }), "Whoever was here last "
        +"must have been very hungry, or a messy eater.\n");	
    IN_IN;
	
    add_prop(ROOM_S_DARK_MSG, "The darkness around is much too "
      +"thick to");
    add_prop(ROOM_S_DARK_LONG, "The darkness here is thick "
      +"and oppressive. You feel it weigh upon your "
      +"soul.\n");
    set_up_herbs(({ GET_ONE(cv), GET_ONE(cv), GET_ONE(cv) }), 
        ({ "walls", "wall", "stone", "ground", "niche",
           "niches", "hollow", "hollows"}), 3);
		
	set_terrain(({TERRAIN_ROCK, TERRAIN_SHADOWS, TERRAIN_HASDEAD,
        TERRAIN_UNDERGROUND	}));

	
}	
/* Add_edits for the various rooms. */

/*
 * Function name: block_exit()
 * Description  : Blocks the exit if a skeleton is present.
 * Returns      :   0 - the player gets through
 *                  1 - the player is blocked
 */ 
int
block_exit(string locus, string exit)
{

    object bones;
    object skeleton = present("_Dead_Isle_Skeleton", TO);
    string skeleton_desc = skeleton->query_short();

    if(skeleton)
    {
		if (random(5) > 3) // 1 in 5 chance of being blocked
		{	
            write("The " + skeleton_desc + " prevents you from "
                +"going in that direction.\n");
            say(QCTNAME(skeleton) + " stops " + QTNAME(TP) 
                +" from going "+ exit + ".\n", 
		        ({ TP, skeleton }));
            return 1;
		}
		else return 0;
    }
    if (random(5) > 3)  // 1 in 5 chance of exit making a skeleton.
    {
        seteuid(getuid()); 
		write("Oops! You knocked over some bones as you "
            +"walked by.\n");
		say(QCTNAME(TP) +" knocks over some bones while "
		    +"trying to move "+ exit +".\n");
        bones = clone_object("/d/Avenir/common/dead/mon/skeleton")->move(TO);
//		bones->equip_me();  called by the skeleton itself.
		return 1;
	}		
	
   return 0;  
}
/* Add exit and the skeleton block function */
void
acat(string locus,string dir)
{
    add_exit(CRYPT+"crypt"+locus,dir,&block_exit(locus, dir),1);
}

/* Start up the room tells now */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
	start_room_tells();
    set_tell_time(150);
}

