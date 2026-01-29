/*
**   ARGOS - City; Entrance Arch/bridge
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   1/30/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "toequest.c"
 
/* room definition */
void
create_room()
{
   set_short("Entrance Arch of Argos");
   set_long(
       "Your footsteps echo from the marble walls and towering ceiling " +
       "of the massive arch beneath which you are walking.  The arch " +
       "covers a wide bridge that spans the rushing river encircling " +
       "the city of Argos.  Towering pillars line the walls of the arch, "   +
       "like sentinels guarding this gateway to the city.  Small windows " +
       "between the pillars afford a breathtaking view of the surrounding " +
       "forest and river below, as well as some of the marble pillared " +
       "structures within the city. A statue of a man stands atop a pedestal "+
       "in the center of the bridge, a focal point of this shrine-like "+
       "structure. To the west stand enormous golden " +
       "gates through which you may leave into the forest, while " +
       "Lambdos Road leads east into the city.\n");
 
    add_item("walls",
       "Buttressed by towering pillars, the walls are constructed with "  +
       "small windows which afford a view of the surrounding territory. " +
       "\n");
 
    add_item("ceiling",
        "The ceiling towers high above you, supported by rows of " +
        "pillars on each side.  A masterfully-painted fresco adorns " +
        "the ceiling of the arch.\n");
    add_item("fresco",
        "Stretching the long length of the ceiling of the arch, this " +
        "fresco portrays two gods and a goddess, suspended in clouds, " +
        "encircling a crest to which all three are pointing.\n");
    add_item("crest",
        "It is a shield emblazoned with a winged horse, surmounted by " +
        "a crown adorned with three jewels.\n");
    add_item("arch",
        "This elaborately decorated arch serves as a gateway into the " +
        "city of Argos.  It stands atop a wide bridge which spans " +
        "the river below.  The heighth of the arch, its pillars, and " +
        "the fresco painted on the ceiling combine to make this " +
        "arch a monument of the city of Argos, welcoming visitors " +
        "from all lands.\n");
    add_item("bridge",
        "Constructed of smooth slabs of marble, this bridge spans "+
        "the river below, linking the city of Argos to the " +
        "territories outside.  The bridge is covered with a " +
        "massive arch, a monument of the city.\n");
    add_item("pillars",
        "Towering columns of white marble, surmounted by elaborately " +
        "sculpted capitals, these pillars stand in two long rows " +
        "along the walls of the arch, supporting the ceiling above.\n");
    add_item(({"windows","window"}), break_string(
        "The windows cut into the walls between the pillars afford " +
        "a spectacular view of the surrounding areas.  Below, you " +
        "can see the rushing torrents of the river as it cascades " +
        "over boulders and along the banks.   To the east " +
        "you can make out some of the marble columned temples and " +
        "structures which make up the city of Argos, while to " +
        "the north and west, you see the surrounding forest of " +
        "hardwoods, interspersed with flowering trees of pink and " +
        "white.\n",70));
    add_item(({"river","forest","structure","city","temple"}),
        "You can see it through the windows.\n");
    add_item(({"structures","temples","trees"}),
        "You can see them through the windows.\n");
    add_item(({"gates","gate"}),
        "The gates stand open at the western end of the arch, "+
        "cast of gold and emblazoned with the crest of Argos.  They " +
        "seem as if they could hold off any attack once closed.\n");
    add_item("pedestal",
        "It is an ornately sculpted marble block serving to elevate "+
        "the statue from the floor of the arch. There is an inscription "+
        "sculpted into the face of the pedestal.\n");
    add_item("inscription",
        "It is sculpted into the face of the pedestal. Perhaps you can "+
        "read it.\n");
    add_cmd_item("inscription","read",
        "It reads: COSMOPOLITUS : NINTH MONARCH OF ARGOS : 266AT.\n");
    add_item("statue",
        "It is the statue of a bearded middle-aged man, dressed in "+
        "regal adornments including a crown. His hands are stretched "+
        "out toward the gates in a welcoming motion.\n");
    add_item(({"toe","statue toe","toe of statue","toe on statue"}),
        "The toe of the royal statue peeps from beneath the regal "+
        "robes.\n");
 
    /* exits */
    add_exit(NWTERR_DIR+"rooms/r27","west",0);
    add_exit(ROOM_DIR+"lroad1","east",0);
    toe_quest_set_statue_prop(TOE_QUEST_COSMOPOLITUS);
}
