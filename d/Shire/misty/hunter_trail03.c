
#include "local.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
    set_short("An animal trail");
    set_long("You continue along the animal trail through the foothills "+
      "of the Misty mountains. The brush begins to thin out here allowing " +
      "you to see the blue waters of the River Bruinen, and the Great " +
      "Road below you to the southeast. The rocky path is steeper here, as " +
      "continues up the trail to the northwest.\n");
      
    add_item(({"river", "bruinen"}),
       "Also called the Loudwater, the river rises from the Misty Mountains " +
       "east of Rivendell, and joins the Mitheithel (Hoarwell) to form the " +
       "River Gwathló or Greyflood..\n");
      
    add_item(({"great road", "road"}),
       "You can see the great road below from High Pass, stretching throughout " +
       "Grey Havens.\n");
       
    add_item(({"trail", "animal trail", "path"}), 
       "The path is little more than trampled brush, grass and weeds. It continues " +
       "up the foothills to the northwest or through the brush to the southeast.\n");
    
    add_item(({"bushes", "brush"}),
       "You're in the middle of dense brush and bushes. Mostly green and brown. " +
       "Some have thorns, while the brush lining the path seem safe to pass.\n");
    
    add_item(({"foothills", "hills"}),
       "Rocky, brush filled foothills can be seen rising to the north from here.\n");
       
    add_item(({"high pass", "pass", "Cirith Forn en Andrath"}),
       "The High Pass, also named Cirith Forn en Andrath, is an important " +
       "mountain pass over the Misty Mountains.\n");
    
    add_prop(ROOM_I_INSIDE, 0);
   
    set_room_tell_time(600);
    add_room_tell("Cricket sounds can be heard coming from the brush.");
    add_room_tell("The wind blows through the trail, causing you to shiver slightly.");
    add_room_tell("You hear a 'chriping' sound coming from the bushes nearby.");


    /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR + "hunter_trail02", "southeast", 0, 2, 1);
    add_exit(MISTY_DIR + "hunter_trail04", "northwest", 0, 2, 1);

}
