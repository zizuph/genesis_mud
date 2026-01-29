// file name: crypt19
// creator: Ilyian (September 1, 1995)
// last update:   Lilith & Zizuph, May-July 2021: finishing area for launch
// purpose: Room in the underground crypts
// note: 
// bug(s):
// to_do:

inherit "/d/Avenir/common/dead/crypt_base";
inherit "/d/Avenir/inherit/sair_wall";
#include "../dead.h"

void
create_crypt_room()
{
  acat("21","north");
  acat("18","west");
  acat("20","east");

    crypt_long(crypt_desc[random(sizeof(crypt_desc))] +" "+ crypt_desc2[random(sizeof(crypt_desc2))]);

 	add_sair_wall();
	set_sair_dest(({CRYPT+"crypt_entr", CRYPT+"crypt66", PATH+"entry"}));

    reset_domain_room();
 }

void
reset_domain_room()
 {
  set_searched(0);    ::reset_domain_room();
 }


void init()
{
    sair_init();
    ::init();
}
