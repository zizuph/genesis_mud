// file name: crypt_s7
// creator: Ilyian (September 1, 1995)
// last update:   Lilith & Zizuph, May-July 2021: finishing area for launch
// purpose:       Room in the underground crypts
// note:          Most of the code for these rooms is in
//                dead.c - see that file for info on these rooms.
// bug(s):
// to_do:
// updates:  Lilith June 2021 : Added an exit to the Mascarvin 
//               quest area.

inherit "/d/Avenir/common/dead/crypt_base";
#include "../dead.h"
#define SLIT  DEAD +"mascarvin/spots"

string see_slit_check();
int enter_slit();

void
create_crypt_room()
{
    acat("36","northwest");
    add_exit(SLIT, "enter", enter_slit, 1, 50);
    add_exit(SLIT, "squeeze", enter_slit, 1, 50);
    add_exit(SLIT, "slit", enter_slit, 1, 50);

    /* Default is the standard random description. */
    crypt_long("\n  Very different from the nearby tunnels, this chamber is " 
      +"both a tomb and an ossuary. Long bones have been stacked neatly against "
      +"the walls, knobbed ends out, and interspersed with numerous skulls "
      +"in a beautiful yet macabre display. Bowls filled with oil are "
      +"suspended from the vaulted ceiling, their light causing the "
      +"limestone to glow and sparkle. "
      +"Beams of kesoit wood, with gold rubbed into the grain, act as "
      +"extravagantly decorative supports for row upon row of bones. "
      +"The ever-present mist flows thickly upon the polished stone "
      +"floor.");

    AI(({"bowls", "bowl", "bowls of oil", "lamp", "lamps", "light", "lights", 
	"ceiling", "glass bowls", "ceiling"}),
      "Large glass bowls filled with oil have been suspended with chains " 
      +"from the ceiling. From below, the light they cast is faint, but "
      +"they provide enough illumination to cause the smooth, pure "
      +"white limestone of the ceiling to sparkle and glow. You find "
      +"yourself wondering what mortal hands tend these lamps.\n");
    AI(({"bone", "bones", "long bones", "wall", "back wall","ossuary"}),
      "These bones have all been cleaned and dried and stacked neatly, "
      +"perhaps even reverently, in aesthetically pleasing patterns "
      +"along the walls of this chamber, from floor to ceiling. "
      +"@@see_slit_check@@");
    AI(({"skull", "skulls"}),
      "Everywhere you look, skulls grin back at you. They shine a bit "
      +"as if they have been polished.\n");		
    AI(({"rows", "rows of bones", "row", "row of bones", "beam", "beams",
	  "kesoit beams", "gilded beams", "kesoit", "kesoit wood"}),
      "The bones and skulls are stacked neatly, perhaps even reverently, "
      +"in rows supported by gilded beams of kesoit wood.\n");	  
    AI(({"slit", "hole"}),
      "@@see_slit_check@@ Some of the mist seems to be sinking "
      +"toward a slit in the wall, near the floor.\n");

    reset_domain_room();
}

void
reset_domain_room()
{
    add_prop(ROOM_I_LIGHT, 2);

    set_searched(0);    ::reset_domain_room();
}

int 
enter_slit()
{
    object   slit = find_object(SLIT);

    if(CHECK_QUEST_MASQ(TP))
    {
	write("You suddenly doubt that Mascarvin would be pleased "
	  +"to see you again.\n");
	return 1;
    }
    if(slit && sizeof(filter(all_inventory(slit), interactive)))
    {
	write("There is someone already squeezed into the "
	  +"slit, so you cannot fit in there.\n");
	return 1;
    }
    //Player needs to help the Hegemon's ghost first.
    if(!CHECK_QUEST_HEG(TP))
    {
	write("Something about the slit repulses you, as if your "
	  +"death awaits should you try to push your way any farther...\n");
	return 1;
    }		
    write("You squeeze into the slit in the wall.\n"
      +"The mist swirls around your legs as you "
      +"wriggle eastward, pulling yourself through "
      +"by your fingertips.\n");
    say(QCTNAME(TP) + " squeezes into a slit in the wall of bones.\n");
    return 0;
}

string
see_slit_check()
{
    object   slit = find_object(SLIT);
    // They've already been down this path and met Mascarvin.
    if(CHECK_QUEST_MASQ(TP))
    {
	return "\n";
    }
    //They haven't helped the Hegemon yet. There's nothing to see here.
    if(!CHECK_QUEST_HEG(TP))
    {
	return "\n";
    }		
    // There is already someone in there.
    if(slit && sizeof(filter(all_inventory(slit), interactive)))
    {
	return "It looks like someone has squeezed themselves into a "
	+"narrow slit in the wall of bones.\n";
    }
    return "It may just be a trick of the shadows, but there seems  "
    +"to be a tall, narrow slit in the wall of bones at the very "
    +"back of the chamber."
    +"\n";
}	
