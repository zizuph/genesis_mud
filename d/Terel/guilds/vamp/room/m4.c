// file name:      m4.c
// creator(s):     Lilith June 2008
// last update:    
// note: 
// bug(s): fixed interference with niche object
// to-do:

#include "../guild.h";

inherit ROOM_DIR+"vamp_room";

#include <ss_types.h>

object niche;

public void create_vamp_room()
{

    set_short("northwest columbarium");
    set_long("This is an ancient granite mausoleum. Hand-high letters have "+
        "been engraved into the north wall, while the east wall is "+
        "lined with columbarium niches filled with urns. There is a "+
        "remarkably well-preserved mosaic on the west wall. "+
        "The dignity of death shrouds this place like the memory "+
        "of ancient times.\n");
    

    add_exit("m2", "south");
    
    add_item(({"inscription", "engraving","north wall", "letters"}), 
        "Engraved deep into the granite is the following:\n"+
        "  Maxima debetur puero reverentia\n");
        /* We owe the greatest respect to a child.  */
    add_item(({"mosaic", "child", "dragon", "black dragon"}),
        "The entire west wall features a large "+
        "mosaic that is still vivid despite its antiquity. It depicts "+
        "various scenes of a child's life, beginning with infancy and "+
        "ending with her sacrifice to a huge black dragon.\n");
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
        "It is lined with niches filled with urns.\n");
    /* add_item("niche", "Which one did you wish to examine? There are nine.\n"); */
    add_item(({"names"}), "The columbarium niches are marked with the "+
        "following names: Sorsimim, Portia, Leonidas, Artemisia, Isabella, "+
        "Paulis, Noloric, Sempera, and Baldrhys.\n");
    add_cmd_item(({"names"}), ({"read"}),
        "The columbarium niches are marked with the "+
        "following names: Sorsimim, Portia, Leonidas, Artemisia, Isabella, "+
        "Paulis, Noloric, Sempera, and Baldrhys.\n");
    add_item(({"first urn", "first niche", "sorsimim", "Sorsimim",
        "striped chalcedony urn", "striped urn", "chalcedony urn"}),
        "There is a striped chalcedony urn in the first niche. The name "+
        "Sorsimim is inscribed on it.\n");
    add_item(({"second urn", "second niche", "portia", "Portia",
        "speckled bloodstone urn", "speckled urn","bloodstone urn"}), 
        "There is an speckled bloodstone urn in the second niche. The name "+
        "Portia is inscribed on it.\n");
    add_item(({"third urn", "third niche", "leonidas", "Leonidas",
        "silver and mithril urn", "silver urn", "mithril urn"}), 
        "There is a silver and mithril urn in the third niche. The name "+
        "Leonidas is inscribed on it.\n");
    add_item(({"fourth urn", "fourth niche", "artemisia", "Artemisia",
        "lapis-lazuli urn", "lapis urn"}), 
        "There is a lapis-lazuli urn in the fourth niche. The name "+
        "Artemsia is inscribed on it.\n");
    /* Isabella's urn and niche are in the m4_niche */
    add_item(({"sixth urn", "sixth niche", "paulis", "Paulis",
        "round jasper urn", "round urn"," jasper urn"}),
        "There is a round jasper urn in the sixth niche. The name "+
        "Paulis is inscribed on it.\n");
    add_item(({"seventh urn", "seventh niche", "Noloric", "noloric",
        "black onyx urn", "black urn", "onyx urn"}),
        "There is a black onyx urn in the seventh niche. The name "+
        "Noloric is inscribed on it.\n");
    add_item(({"eighth urn", "eighth niche", "sempera", "Sempera",
        "garnet-encrusted gold urn", "garnet-encrusted urn", "gold urn"}),
        "There is a garnet-encrusted gold urn in the eighth niche. The name "+
        "Sempera is inscribed on it.\n");
    add_item(({"ninth urn", "ninth niche", "Baldrhys", "baldrhys",
        "milk-white quartz urn", "milk-white urn", "quartz urn"}),
        "There is a milk-white quartz urn in the ninth niche. The name "+
        "Baldrhys is inscribed on it.\n");

    reset_room();
 

}

void
reset_room()
{
    if (!niche)
    {
        niche = clone_object(OBJ_DIR +"m4_niche");
        niche->move(TO, 1);
    }

}

