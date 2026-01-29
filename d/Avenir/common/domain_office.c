// Tower of Realms Office  /d/Avenir/common/domain_office.c
// creator(s):   Lilith    01/28/97  
// revisions:    Lil, 02/16/97: added statserv.    
//		 Denis, Mar'97: Cosmetic updates.
//		 Lucius, Apr'08: Some cleanup, removed statserv,
//		                 added quest orb.
// purpose:      Room for mortals to visit to pique their interest.
// note:         This room is designed to depict the Source at a 
//               mortal's level of comprehension.
// bug(s):
// to-do:        
#pragma strict_types

#include <stdproperties.h>
#include "/d/Genesis/start/human/town/tower.h"

inherit TOWER_OFFICE;
inherit "/d/Avenir/inherit/room_tell";

public static string *rooms = ({
    "/d/Avenir/common/bazaar/extr/hill",
    "/d/Avenir/common/bazaar/intr/alcove",
    "/d/Avenir/common/bazaar/museum/gallery3",
    "/d/Avenir/common/dark/l3/altar",
    "/d/Avenir/common/dark/lair/lair",
    "/d/Avenir/common/dead/hill/cairn",
    "/d/Avenir/common/holm/jungle/lf11",
    "/d/Avenir/common/outpost/cave1",
    "/d/Avenir/common/park/grotto",
    "/d/Avenir/common/port/pub",
});      

private string
long_desc(void)
{
    return "This is a place of powerful, arcane magic. One "+
	"where you are suspended in the center of a giant "+
	"multi-faceted crystal. Light pulses at near-painful "+
	"intensity, forcing you to squint in order to see. "+
	"The throbbing light is focused at a point just below "+
	"your feet and flows into the blackness of a large, "+
	"underground cavern far below. Cradled in the waters "+
	"of a dark and restless sea, the islands of Sybarus glow "+
	"like gemstones illuminated in a shadowy room. "+
	"The very air vibrates with a low-pitched hum which "+
	"tickles the flesh of your face and hands and causes "+
	"your ears to ring. Various images form and dematerialize "+
	"within the facets of the crystal, revealing with "+
	"god-like omniscience the activities of the denizens "+
	"of the Avenir Demesne.\nA sign framed in fluid, golden "+
	"light wavers before your eyes, inviting you to read it.\n";
}

#ifdef Genesis
#include <language.h>
private void
quest_orb(object orb)
{
    orb->set_orb_domain("Avenir");
    orb->set_no_show_composite(1);

    add_my_desc("Hovering in mid-air is "+ LANG_ADDART(orb->short()) +
	". It refracts none of the surrounding luminance, creating "+
	"instead a pocket of absence. Whichever way you turn, the orb "+
	"remains before you, at chest-height and still as a corpse's "+
	"breath. Something within you is drawn to the darkened "+
	"crystal. It beckons to you with almost sinister intent "+
	"everytime your eyes pass over its subdued facets.\n", orb);
}
#endif

public int
facet_image(string str)
{
    string room = one_of_list(rooms);

    if (str == "facets" || str == "facet" || str == "image" || 
        str == "images" || str == "crystal")
    {
        write("Looking at the image in the crystal, you experience "+
            "a fleeting disorientation as you are momentarily "+
            "transported through the facet and into the scene:\n\n");
	write(room->long(0));
        write("\nThe image fades and a new one replaces it.\n");
        return 1;
    }

    return notify_fail(capitalize(query_verb()) + " what?\n");
}

public string
facet_exa(void)
{
    facet_image("facet");
    return "";
}

public string 
sign_exa(void)
{
    return "You have the following commands at your disposal:\n"+
        "    [view images]                -Shows what is in the facets.\n"+
	"    [wizards]                    -Lists the wizards of Avenir.\n"+
        "    [projects]  <avenir/wizard>  -Lists the current projects.\n";
/*
	"    Please visit our Embassy at: "+
	"http://www.genesismud.org/d/Avenir\n\n";
 */
}

public void
create_tower_office(void)
{
    set_short("Avenir Demesne");
    set_long(long_desc());

    add_item(({"facet", "facets", "image", "images", "crystal"}), facet_exa);
    add_item("light", "It is yellowish in colour and gloriously "+
        "bright, yet without warmth. It emanates from within "+
        "this crystal and focuses downward.\n");
    add_item(({"down", "downward", "islands", "gemstones", "Sybarus"}),
        "Through the transparent facet beneath your feet, you "+
        "can see the Islands of Sybarus far below, illuminated "+
        "by the very light which streams through this crystal.\n");
    add_item("sign", sign_exa);
    add_cmd_item("sign", "read", sign_exa);
   
    add_prop(ROOM_M_NO_ATTACK, 1);
    add_prop(ROOM_M_NO_MAGIC_ATTACK, 1);
    add_prop(ROOM_S_MAP_FILE, "domain_office.txt");

    set_project_dir("/d/Avenir/open/project/");
    add_tower_link("darkness");

    set_tell_time(300);
      add_tell("There is a swirling in one of the facets, and "+
         "you can see the image of a giant worm dwarfing a "+
         "humanoid figure.\n");
      add_tell("The low-pitched hum increases in intensity, "+
         "causing the hair on your arms to stand on end.\n");
      add_tell("The glorious yellow light streams through "+
         "you like a caress.\n");
      add_tell("A tiny ball of concentrated light forms before "+
         "you, then bounces away.\n");
      add_tell("A giant face hovers before you.\nThe great eyes "+
         "blink, then fade away.\n");
      add_tell("There is a brilliant burst of rainbow colours, "+
         "leaving black-spot afterimages in your eyes.\n");
      add_tell("A facet surface ripples like water in wind.\n");

#ifdef Genesis
    enable_reset(200);
    add_object(QUEST_ORB, 1, quest_orb);
#endif
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (query_interactive(ob))
	start_room_tells();
}

public void
init(void)
{
    ::init();
    add_action(facet_image, "view");
}
