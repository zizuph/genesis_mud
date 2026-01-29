// file name:   dead.c
// creator(s):  Ilyian
// last update: Ilyian, Sep 22, 1995
//              Cirion, Apr 10, 1996  Prepared it for opening
//              Lilith Aug 1, 2004: added interactive check to tells
//              Lucius, Jul 2007: Lowered panic cost, 250 is way, way
//                too much, it makes hunting there extremely difficult.
//              Lilith, Jul-Aug 2021 modifications in preparation of 
//                opening the catacombs. Thanks to Zizuph for his help.
//              Lilith, Oct 2021: added fishing prop to shore rooms.
// purpose: Inheritable file for all the rooms in the
//          /d/Avenir/common/dead/* areas. 
//          Contains standard descriptions and most of the functions 
//          called from those rooms.
// note:
// bug(s):
// to-do:
 inherit "/std/room.c";
inherit "/d/Avenir/inherit/room_tell"; // room tells (tm) by Aridor.

/* Include the herb search functions */
#include "/d/Avenir/common/herbs/herbsearch.h"
#include "/sys/terrain.h"
#include "dead.h"

int genrand1,genrand2;

string *st = HERB_MASTER->query_herbs( ({"marsh"}) );
string *cv = HERB_MASTER->query_herbs( ({"cave"}) );

>>(void)
{
    set_alarm(0.5, 0.0, &add_prop(ROOM_M_NO_TELEPORT_TO, 1));
}

/* prototypes... */
void reset_room()  
{
    set_searched(0);
}

/* And a couple of string defines. */
string *randmarsh = ({"This area seems more tolerably dry than "
  +"the rest of the marsh.","A foul odour "
  +"permeates this place.","There is an expectant "
  +"feeling in the air, as if the marsh was awaiting "
  +"the souls of the dying.","This is a foul and "
  +"lonely place. The spirits of the dead can be "
  +"felt all around.","Upon everything is a haze "
  +"of restlessness and oppression.","Everything "
  +"here seems to have a touch of unreality "
  +"and grotesqueness, as if some vital element "
  +"of perspective or chiaroscuro were awry.","The "
  +"mire around is worn and dismal.","The air is "
  +"stale and loathsome.","An unearthly sense of "
  +"hostility lies everywhere."});
 
string *marsh_shorts = ({"bog","fen","marsh","mire","slough",
  "sump","vlei","quag","swamp"});
string *marsh_adjs = ({"grey","dismal","lonely","damp","wet",
  "barren","desolate"});
string *sea_adjs = ({"black","menacing","calm","dark",
  "sunless","endless"});
string *path_shorts = ({"treacherous","dangerous","stone",
  "cobbled","cobblestone","stony","uneven","shore",
  "sea","narrow"});

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


/* Rooms along the center path */
void
path_long(string desc)
{
    set_long("You are on a long and narrow "
      +"cobblestone path. "+desc+"\n");
    set_short("cobbled path");

    AI(({"source","ceiling","cavern","cave"}),"The "
      +"ceiling of Sybarus cavern can barely be seen "
      +"from here, as some fog off the downs obscures "
      +"your vision, but you can just make out the "
      +"faint gloaming of the Source above.\n");
    AI(({"cobbles","cobblestones","stones","stone"}),
      "The cobblestones underfoot are rough and "
      +"uneven. They have been fitted together to "  
      +"form some sort of pattern, but the damp "
      +"ground has shifted so much that they retain "
      +"little of their origional order.\n");
    AI(({"path","road","ground","floor"}),"The path "
      +"underfoot is made up of rough cobblestones "
      +"placed unevenly together.\n");

    ACI(({"ground","here","hole","in ground","path"}),
      "dig","Impossible. The cobblestones are hard and "
      +"unyielding.\n");

    set_tell_time(100);
}

void
path_reset()
{ 
    /* Nothing for now */
}

/* Rooms along the shore path */
void
shore_long(string desc)
{
    set_short("shore path");
    set_long("This is a narrow stone path that runs "
      +"along the shoreline of the island. The "
      +"black water of the dark sea stretches "
      +"out as far as you can see, its gentle "
      +"waves lapping against the rocks of the "
      +"shore. "+desc+"\n");

    add_prop(ROOM_I_TYPE, ROOM_BEACH);
    add_prop(OBJ_I_CONTAIN_WATER, 1);
    add_prop("_live_i_can_fish", ({"subterranean", "saltwater", "freshwater"}));
	
    AI(({"water","sea","ocean","dark sea"}),"The dark sea "
      +"stretches out as far as you can see, its "
      +"murky black water obscuring what lies "
      +"beneath. The water laps gently against the "
      +"rocks of the shore, making them dark and "
      +"slippery.\n");
    AI(({"wave","waves"}),"The waves are slow and "
      +"lethargic, as if the water were as thick "
      +"as blood.\n");
    AI(({"rock","rocks"}),"The rocks that are scattered "
      +"along the shoreline are of many shapes "
      +"and sizes, but all seem to be some sort "
      +"of granite interspersed with traces of "
      +"gleaming feldspar.\n");
    AI(("feldspar"),"It glitters and gleams in the "
      +"pale light.\n");
    AI(({"shore","shoreline"}),"The shoreline is scattered "
      +"with rocks. It lies a little below the "
      +"level of the path, and small pools of "
      +"murky water have formed in some niches "
      +"between the rocks. The great dark sea "
      +"stretches off past the shore as far as you "
      +"can see.\n");
    AI(({"pools","pool","niche","niches"}),"There are "
      +"some niches between the rocks that have "
      +"been filled with water from the gentle "
      +"waves of the dark sea.\n");
    AI(({"path","road","pathway"}),"The path underfoot "
      +"is made from large blocks of whitish "
      +"limestone. The whole path is raised a bit "
      +"above the level of the rocky shoreline, "
      +"preventing it from getting wet from the "
      +"thick dark waves that roll into the island.\n");
    AI(({"limestone","blocks"}),"The blocks of limestone "
      +"that make up the path are chalky and porous, "
      +"making them extremely dry and easy to "
      +"walk on.\n");
    AI(({"light","ceiling","cavern","source","Source",
	"cave"}),"You can barely make out anything "
      +"of the cavern ceiling from here. Only "
      +"a pale dim light filters down through "
      +"a canopy of haze that rises from the moors.\n");

    HAS_WATER;  // defined in common.h

    add_tell("A particarly large wave rolls into the "
      +"rocky shore, sending droplets of water into the air.\n");
    add_tell("The water is perfectly still and silent for "
      +"a moment.\n");
    add_tell("Something causes a circle of ripples to form "
      +"in the water.\n");
    /* Add_items to do with the room tells.
     * This really should be better...
     */
    AI(({"drop","drops","droplet","droplets"}),"The "
      +"droplets of water splatter against the "
      +"rocks, making them dark and slippery.\n");
    AI(({"circle","ripple","ripples"}),"They must be "
      +"caused by something moving in the water.\n");

    ACI(({"water","sea","ocean"}),({"enter","dive","swim"}),
      "The dark water seems too vile and treacherous to "
      +"swim in.\n");
    ACI(({"ground","here","hole","in ground","path"}),
      "dig","The stone path cannot be dug through.\n");
    ACI(({"water","sea","ocean"}),({"drink","taste"}),
      "It is foul and brackish.\n");
}

void
shore_reset()
{
    /* nothing for now */
}

/* Rooms that can see the hill have this. */
void
add_hill()
{
    add_item(({"hill","hillock","slope"}),"It slopes "
      +"upwards and out of the marsh, forming "
      +"part of a very large hill that seems to "
      +"lie in the center of the swamp. Through the "
      +"mist, you can just make out some large shapes "
      +"at the top of the hill.\n");
    add_item(({"shape","shapes"}),"You cannot discern anything "
      +"about the shapes from this distance.\n");
}

/* Descriptions and functions for the marsh rooms,
 * in /common/dead/marsh/
 */
void
marsh_long(string desc)
{
    set_long("You stand in a gloomy and grey marsh. Thin "
      +"dead reeds rise up through the damp ground, and "
      +"lying over the area like a shroud is a thick cold "
      +"fog. "+desc+"\n");
    set_short(marsh_adjs[random(sizeof(marsh_adjs))] + " " +
      marsh_shorts[random(sizeof(marsh_shorts))]);

    add_prop("cover_in_fog", random(20) + 10);
    set_noshow_obvious(1);
    add_item(({"reed","reeds","grass","plant","plants","vegetation"}),
      "Dead reeds and marsh grass poke through the "
      +"ground at sporadic intervals.\n");
    add_item(({"fog","mist"}),"A thick grey fog covers the ground, "
      +"wrapping around your ankles and obscuring the "
      +"ground. All around the cold mist swirls into "
      +"bizarre shapes.\n");
    add_item(({"ground","swamp","marsh","floor","bog","fen",
	"marsh","slough","sump","vlei","quag"}),"The swampy "
      +"wet ground seems to be trying to suck your feet "
      +"down into it. Some grey reeds poke up through the "
      +"marsh, and everywhere is a blanket of thick cold "
      +"fog.\n");
    add_item(({"ceiling","cavern","cave"}),"You cannot make out "
      +"the ceiling of the great cavern through all "
      +"the fog.\n");
    add_item(({"source","Source","light"}),"The only light you "
      +"see is an unearthly glow reflected off of the "
      +"fog around you.\n");

    add_tell("A few blades of marsh reeds seem to bend over of their "
      +"own accord.\n");
    add_tell("The fog swirls around your ankles, leaving them "
      +"damp and cold.\n");
    add_tell("From across the marsh you hear a long and high "
      +"pitched wail.\n");
    add_tell("From the distance you can just make out a piercing "
      +"cry.\n");
    add_tell("A thick tendril of grey fog wraps around you and "
      +"dissipates.\n");
    add_tell("A soft moan is carried on the fog.\n");
    add_tell("A thick patch of mist passes before your eyes, "
      +"completely obscuring your vision for a moment.\n");
    add_tell("The wet ground beneath your feet shifts slightly.\n");

    add_prop(ROOM_I_LIGHT,1);
	set_terrain(TERRAIN_MUD | TERRAIN_SMALL_PLANT | TERRAIN_OUTSIDE |
        TERRAIN_HASDEAD);	

    ACI(({"ground","here","hole","in ground","marsh"}),
      "dig","The damp ground is so wet that the earth "
      +"just collapses back in to cover your attempts.\n");
    ACI(({"mist","fog","haze"}),({"touch","feel"}),
      "The fog is cold and dank, and seems to emanate from "
      +"itself some malevolant force.\n");

    set_up_herbs(({ GET_ONE(st), GET_ONE(st), GET_ONE(st) }), 
      ({ "reed","reeds","grass","plant","plants","vegetation",
    	"ground","swamp","marsh","floor","bog","fen",
	    "marsh","slough","sump","vlei","quag" }), 1 +random(4));   	

    set_tell_time(100);
}

/* Descriptions and functions for the hill rooms,
 * in /common/dead/hill/
 */
void
hill_long(string desc)
{
    set_long("You stand upon a rocky hill looking out "
      +"over the dismal marsh all around. Tufts of "
      +"sickly grey grass are interspered along the "
      +"hillside. "+desc+"\n");
    set_short("hillside");
    add_item(({"grass","plant","plants","vegetation"}),
      "It is amazing that anything can grow in "
      +"such a hostile environment.\n");
    add_item(({"swamp","marsh","floor","bog","fen",
	"marsh","slough","sump","vlei","quag"}),"You "
      +"can make out few details of the swamp that "
      +"spreads out at the base of the hillside, as "
      +"the entire area is enshrouded in a thick "
      +"grey fog.\n");
    add_item(({"hill","hillside","slope","ground"}),"The "
      +"hill you stand on is mostly rocky and barren, "
      +"and rises up steeply out of the desolate "
      +"marshland below.\n");
    add_item(({"ceiling","cavern","cave"}),"You can just "
      +"barely make out the ceiling of the great "
      +"cavern from here, mostly from the dull "
      +"glow given off from the Source.\n");
    add_item(({"source","Source","light"}),"The gloaming "
      +"light from the Source above makes the "
      +"fog below glow with an unearthly tint.\n");

    add_tell("Something is moving along the marsh below.\n");
    add_tell("You see a disturbance in the mist that lies "
      +"over the swamp.\n");
    add_tell("A thin wisp of fog blows up along the hillside.\n");
    add_tell("You hear a soft moan from the swamps below.\n");
    add_tell("A piercing cry suddenly rises from the "
      +"fog covered swamp.\n");

    add_prop(ROOM_I_LIGHT,1);

    ACI(({"ground","here","hole","in ground","hill"}),
      "dig","The hill is too rocky.\n");

    set_tell_time(120);
}

void
hill_reset()
{
    /* Nothing for now....
     */
}

void
marsh_reset()
{
    /* Not using do_fall for marshes afterall.
       set_alarm(itof(random(200)),0.0,"do_fall",this_object());
       Not until the crypts are open...
     */
}


/* Old do fall for marshes
void
do_fall(object this_place)
{
    object *room_list = all_inventory(this_place);
    int i = random(sizeof(room_list));

    
	*Make it fall only if there actually is something in
    *the room, and only if that thing is interactive.

    if (i>0 && interactive(room_list[i]))
    {
	room_list[i]->catch_msg("The ground beneath you "
	  +"suddenly gives way!\nYou fall into darkness.\n");
	tell_room(ENV(room_list[i]),QCTNAME(room_list[i])+
	  " suddenly falls through the ground!\n",
	  room_list[i]);
	room_list[i]->move_living("M", MARSH+"falling");
	set_alarm(10.0,0.0,"do_land",room_list[i]);
    }
}
*/



/* Makes moving about in the marsh difficult */
int
marsh_move()
{
    genrand1=random(15);
    genrand2=(genrand1 * genrand1);
    if (genrand2 > STR(TP))
    {
	write("You struggle to move through the mire, but "
	  +"your feet are caught firmly.\n");
	TP->add_fatigue(-5);
	return 1;
    }
    write("You trudge through the wet earth and fog.\n");
    return 0;
}

/* macro-functions for movement from the rooms */
int
hill_upmove()
{
    write("You climb up the steep hill.\n");
    return 0;
}

int
hill_downmove()
{
    write("You descend the steep hill.\n");
    return 0;
}

int
path_say()
{
    write("You stumble along the rough cobblestones.\n");
    return 0;
}

int
pathhill_say()
{
    write("You step off the path and onto the hillside.\n");
    return 0;
}

int
marsh_entr()
{
    write("You step off the path onto the moors.\n");
    if(!UND(TP)) 
    {
	write("You are immediatly overwhelmed by a sense "
	  +"of unease.\n");
	TP->add_panic(random(40));
	return 0;
    }    
    else
    {
	write("You feel quite at home here among the dead.\n");
	return 0;
    }
    return 0;
}


/* Add_edits for the various rooms. */

void
am(string locus,string dir)
{
    add_exit(MARSH+"marsh"+locus,dir,"@@marsh_move",4);
}

void
ahup(string locus,string dir)
{
    add_exit(locus,dir,"@@hill_upmove",5);
}

void
ahdown(string locus,string dir)
{
    add_exit(locus,dir,"@@hill_downmove",1);
}

void
apath(string locus,string dir)
{
    add_exit(PATH+"path"+locus,dir,0,1);
}

void
ashore(string locus,string dir)
{
    add_exit(PATH+"shore"+locus,dir,0,1);
}

int
marsh_enter()
{
    write("You enter the dismal marshland.\nYou immediatly "
      +"feel the ground trying to pull you under.\n");
    return 0;
}

void
gomarsh(string locus,string dir)
{
    add_exit(MARSH+"marsh"+locus,dir,"@@marsh_enter",3);
}

void
path_marsh(string dir,string where)
{
    AE(MARSH+"marsh"+where,dir,"@@marsh_entr",2);
    AI(({dir,"marsh","swamp","moor","downs"}),"The "
      +"grey marshes stretch out into the mist on "
      +"either side of the narrow path. An eminence "
      +"of unease seems to reach out from the fog, but "
      +"nothing can be seen without entering the "
      +"swamp.\n");
    AI(({"fog","mist"}),"The mist floating over the "
      +"marsh is grey and thick. It swirls into "
      +"eerie patterns and occassionally a patch "
      +"will float across the path.\n");

    add_tell("A thin tendril of mist reaches out "
      +"from the "+dir+" and floats across the path.\n");
    add_tell("You think you can see some movement in the "
      +"thick fog to the "+dir+".\n");
    add_tell("You hear a sudden piercing wail come out "
      +"of the moors.\n");
    add_tell("The mist from the swamps suddenly passes over "
      +"the path, obscuring your vision for a moment.\n");
    add_tell("A shallow breeze brings on it hollow and "
      +"ghostly voices.\n");
    add_tell("You suddenly hear whispers all around.\n");
    add_tell("A pleading female voice shouts: Come "+dir+"! "
      +"Quickly!\n");

    set_up_herbs(({ GET_ONE(st), GET_ONE(st), GET_ONE(st) }), 
      ({ "marsh","swamp","moor","downs" }), 5);   	
}

void 
path_exit(string dir,string where)
{
    AE(PATH+"path"+where,dir,"@@path_say",2);
    AI((dir),"To the "+dir+", the path continues "
      +"along.\n");

    add_tell("You think you hear soft footfalls to the "
      +dir+".\n");
}

void
path_hill(string dir,string where)
{
    AE(HILL+"hill"+where,dir,"@@pathhill_say",1);
    AI(({dir,"hill","hillside"}),"The barren hillside "
      +"slopes down on either side of the path, "
      +"decending down to the fog-stained moors "
      +"below.\n");
    AI(({"moor","moors","swamp","fen","mire","marsh"}),
      "The marsh at the bottom of the hill is "
      +"obscured by a thick layer of grey mist. There "
      +"seem to be shapes moving along the moors, but "
      +"you cannot make out any details at this "
      +"distance.\n");
    AI(({"shape","shapes"}),"The shapes below are "
      +"indiscernable from this height.\n");
    AI(({"fog","mist"}),"The thick grey mist on the "
      +"marsh below obscures your view of the "
      +"area.\n");
    AI(("view"),"Below you spreads out the marshes, covered "
      +"with fog. A narrow path winds down the hill to the "
      +"south to the edge of the island, where you can "
      +"just make out a ferry landing. To the north, there "
      +"appears to be a cairn of some sort, and far in the "
      +"distance to the east and west the water of the dark "
      +"sea stretches out. Another path runs along "
      +"the edge of the shoreline, around the eastern "
      +"and western sides of the island.\n");
    AI(({"sea","water","ocean"}),"The dark sea stretches out "
      +"to the east and west, its gentle waves lapping "
      +"against the shore of the island.\n");

    add_tell("You can make out some shapes moving in the "
      +"mist below.\n");
    add_tell("A thin hollow wailing suddenly rises up from "
      +"the moors.\n");
    add_tell("A cold wind suddenly blows across the hill, "
      +"bringing with it wisps of cold fog.\n");
    add_tell("You suddenly feel very uneasy.\n");
    add_tell("A strange singing can be heard from the fens "
      +"below.\n");

}

void
shore_exit(string dir,string where)
{
    AE(PATH+"shore"+where,dir,0,1);
}

void
shore_marsh(string dir,string where)
{
    AE(MARSH+"marsh"+where,dir,"@@marsh_entr",3);
    AI(({dir,"marsh","moor","moors","fen","fens","swamp"}),"The "
      +"grey and dismal marsh lies to the "+dir+", obscured "
      +"by a thick shroud of pale mist.\nA sense of "
      +"foreboding emanates from the moors.\n");
    AI(({"mist","fog","haze"}),"The fog on the moors is grey and "
      +"impenetrable, hiding whatever secrets may lie "
      +"beyond.\n");

    add_tell("You hear a hollow cry from the moors.\n");
    add_tell("A human female voice shouts: Come "+dir+"! Quickly!\n");
    add_tell("A wisp of fog floats across the path, wrapping "
      +"around your ankles before dissipating.\n");
    add_tell("A fierce wind suddenly starts to blow.\n");
    add_tell("You hear a wail of pain and anguish come over "
      +"the moors.\n");
}
