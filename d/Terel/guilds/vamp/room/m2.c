//-*-C++-*-
// file name:      m2.c
// creator(s):     Lilith June 2008
// last update:    
// note: 
// bug(s): fixed interference with niche object
// to-do:
#include "../guild.h";

inherit ROOM_DIR+"vamp_room";

#include <ss_types.h>

object niche;

void reset_room();

public void create_vamp_room()
{

    set_short("west columbarium of mausoleum");
    set_long("This is an ancient mausoleum made of granite. "+
        "The dignity of death shrouds this place like the memory "+
        "of ancient times. The south "+
        "wall bears a deep inscription, while the east wall "+
        "is lined with shallow niches holding cinerary urns. "+
        "Beneath the high ceilings a series of frescoes have been "+
        "painted.\n");
    
    add_exit("m4", "north");
    add_exit("mausoleum", "east");
     
    add_item(({"inscription", "engraving","south wall", "words", "letters"}), 
        "Engraved deep into the granite is the following:\n"+
        "  Sunt lacrimae rerum et mentem mortalia tangunt\n");
        /* These are the tears of things, and our mortality cuts to the heart */
    add_item(({"granite", "quartz", "black stone"}), 
        "The granite is dark grey in colour "+
        "and speckled with black stone and bits of quartz.\n");
    add_item(({"walls", "band"}), 
        "A band of the granite walls have been plastered-over, extending "+
        "from the ceiling down about four feet. Frescoes have been painted "+
        "there.\n");
    add_item(({"ceiling", "ceilings", "ground", "floor"}), 
        "They are made of the same granite as the rest of the structure.\n");
    add_item(({"frescoes", "fresco", "painting", "paintings"}), 
        "The frescoes are so faded that most of the detail is gone, "+
        "however, it seems that they depict scenes of feasting and "+
        "celebration of the afterlife.\n");
    add_item(({"east wall", "columbarium"}), 
        "The columbarium begins on the east wall and continues north. "+
        "It is lined with niches, some empty, some filled with urns.\n");
    /* add_item("niche", "Which one did you wish to examine? There are nine.\n"); */
    add_item(({"markings", "names"}),
        "There are six names marked on the niches:\n"+
        "Tiberia, Cornelius, Horatia, Crititas, Telios, and Mecieni.\n");
    add_cmd_item(({"markings", "names", "niches"}), ({"read"}),
        "There are six names marked on the niches:\n"+
        "Tiberia, Cornelius, Horatia, Crititas, Telios, and Mecieni.\n");
    add_item(({"first urn", "first niche", "tiberia", "Tiberia", 
        "alabaster urn"}),
        "There is a large alabaster urn in the first niche. The name "+
        "Tiberia is inscribed on it.\n");
    add_item(({"second urn", "second niche", "cornelius", "Cornelius",
        "ornate jade urn", "jade urn"}), 
        "There is an ornate jade urn in the second niche. The name "+
        "Cornelius is inscribed on it.\n");
    add_item(({"third urn", "third niche", "horatia", "Horatia",
        "black marble urn", "marble urn"}), 
        "There is a black marble urn in the third niche. The name "+
        "Horatia is inscribed on it.\n");
    add_item(({"fourth urn", "fourth niche", "crititas", "Crititas",
        "wide golden urn", "golden urn"}), 
        "There is a wide golden urn in the fourth niche. The name "+
        "Crititas is inscribed on it.\n");
    add_item(({"fifth urn", "fifth niche", "telios", "Telios",
        "ancient iron urn", "iron urn"}),
        "There is an ancient iron urn in the fifth niche. The name "+
        "Telios is inscribed on it.\n");
    add_item(({"sixth urn", "sixth niche", "Mecieni", "mecieni",
        "pale amethyst urn", "amethyst urn"}),
        "There is a pale amethyst urn in the sixth niche. The name "+
        "Mecieni is inscribed on it.\n");
    add_item(({"first empty niche", "seventh niche", "eighth niche", 
        "second empty niche", "ninth niche", "third empty niche",
        "first unmarked niche", "second unmarked niche", 
        "third unmarked niche"}),
        "This is a columbarium niche. There is no name inscribed on it.\n");

    reset_room();
}

void
reset_room()
{
    if (!niche)
    {
        niche = clone_object(OBJ_DIR +"m2_niche");
        niche->move(TO, 1);
    }

    niche->fill_niche();
}

