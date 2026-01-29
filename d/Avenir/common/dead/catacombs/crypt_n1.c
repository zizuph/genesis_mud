// file name: crypt1
// creator: Ilyian (September 1, 1995)
// last update:   Lilith & Zizuph, May-July 2021: finishing area for launch
//                Lilith Oct 2021: fixed path error on exit.
// purpose: Room in the underground crypts
// note: Most of the code for these rooms is in
//         dead.c - see that file for info on these rooms.
// bug(s):
// to_do:

inherit "/d/Avenir/common/dead/crypt_base";
inherit "/d/Avenir/inherit/sair_wall";
#include "../dead.h"

void
create_crypt_room()
{
  add_exit(CRYPT +"crypt4", "out");
  
/* Default is the standard random description. */
    niche_long("You feel like you can rest here for a little while. ");
    add_prop(ROOM_M_NO_ATTACK, 1);
    add_prop(ROOM_M_NO_MAGIC_ATTACK, 1);
    add_prop(ROOM_M_NO_SCRY, 1);
    add_item(({"wall", "walls", "limestone"}), "The walls of the niche "+
	    "are carved from the limestone of the island.\n");
    add_sair_wall();
	set_sair_dest(({BARROW +"barrow0", CRYPT +"crypt_n5",
	        "/d/Avenir/common/bazaar/extr/centr"}));

  reset_domain_room();
 }

void
reset_domain_room()
 {
   set_searched(0);    ::reset_domain_room();
 }


public void
init()
{
    ::init();
    sair_init();  
}
