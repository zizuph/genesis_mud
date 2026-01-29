inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_room() {

  set_short("Road");
  set_long("You wander the ruins of Annuminas. The rubble of destroyed "
          +"buildings lays strewn over the road, and delapidated "
          +"homes are scattered all around. A dense mist covers the ground, "
          +"blocking everything nearby from sight, "
          +"but to the north towers a building not completely ruined. Behind "
          +" lies the arch which marked the way into the city. "
          +"Being here, in this abandoned city, feels strange, as if "
          +"some presence is lurking in every shadow.\n");
  add_item(({"street","streets"}),"The streets were once made of "
                                 +"finely crafted cobles, but now "
                                 +"lay in shambles, covered in "
                                 +"rubble.\n");
  add_item(({"rubble","piles"}),"These small piles of rubble look "
                    +"like the remnants of buildings.\n");
  add_item(({"mist"}),"This is a thick, moist mist that floats just "
                   +"above the ground. It obscures your vision "
                   +"just enough so you can't make out details in "
                   +"the distance.\n");
  add_item(({"arch"}),"This is a huge ruined arch that once marked "
                     +"the entrance to the ruined city you have entered. "
                     +"Even though ruined, it still towers above your "
                     +"head, a huge monolith in the otherwise plain "
                     +"ruins.\n");
  add_exit(ANNUM_DIR + "am11", "northeast", 0);
  add_exit(ANNUM_DIR + "am12", "northwest", 0);
  add_exit(ANNUM_DIR + "am9", "south", 0);
}
