#include <money.h>
#include "rom.h"

object silver, gold, shield, armour;


make_treasure()
{
    int i;
    if(!silver || !present(silver))
    {
	silver = clone_object("/std/coins");
	silver ->set_heap_size(random(10)+random(10)+1);
	silver ->set_coin_type("silver");
	silver ->move(this_object());
    }
    if(!gold || !present(gold))
    {
	gold = clone_object("/std/coins");
	gold ->set_heap_size(random(5)+random(3)+1);
	gold ->set_coin_type("gold");
	gold ->move(this_object());
    }
    if(!present("armour", TO)) for(i=0;i<6;i++)
	clone_object(ARM_DIR+"wtrplate")->move(TO);

    /* I have made elfblade the only weapon in the treasure */

    if(!present("elfblade", TO)) 
	clone_object("/d/Shire/common/weapon/elfblade")->move(TO);

}

create_rom() {
    object door;

    set_short("Trolls treasure chamber");
    set_long(
        "You seem to have entered the treasure chamber of the cave troll! "+
	"Utterly dim, it seems to be the perfect place to hide treasures. ");
    door = clone_object(HOLLIN_DIR + "trolldoor");
    door -> set_pass_command(({"w","west"}));
    door -> set_other_room(HOLLIN_DIR + "round_room");
    door -> move(this_object());
  
    make_treasure();

    add_prop(ROOM_I_INSIDE, 1);
}

reset_rom() 
{
  make_treasure();
}
