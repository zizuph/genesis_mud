inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

int flakes;

reset_room()
{
     flakes = 3;
}

create_room()
{
    object pot1, pot2;
    
    set_short("cottage kitchen.");
    set_long(
	"You have entered a small kitchen. A rusty wood stove sits in one " +
	"corner. " +
	"The flagstone floor is covered with crumbs, withered vegetables " +
        "and dust. There are dirty dishes piled on a counter area. The " +
        "remains of a laquered door hang off broken hinges. The doorway " +
	"leads out into the backyard. The ceiling of the kitchen is " +
	"covered with a sooty black residue.\n"
    );

    add_item(({"dishes"}), 
	"The dishes are covered with sticky hardened noodles.\n"
    );

    add_item(({"door", "laquered door", "door remains", "doorway"}), 
        "The door looks like it was ripped apart.  You can see what appear " +
        "to be claw marks on the ragged boards where chipped wood flakes " +
	"away from deep scratches in the surface.\n"
    );


    add_cmd_item(({"stove", "wood stove"}),
		 ({"examine", "exa", "look at", "scrape"}),
		 ({"@@stove_desc", "@@stove_desc","@@stove_desc", "@@scrape"}));

    add_item(({"ceiling", "soot", "residue"}),
        "The sooty residue looks very greasy.  It doesn't look like it " +
	"could have been produced from burning wood.\n"
    );

    add_prop(ROOM_I_INSIDE, 1);

    pot1 = clone_object(TOMBDIR + "pot");
    pot1->move(TO);

    pot2 = clone_object(TOMBDIR + "pot");
    pot2->move(TO);    
    
    add_exit(TOMBDIR + "cottage_garden", "out", 0);
    add_exit(TOMBDIR + "cottage_bedroom01", "east", 0);
    add_exit(TOMBDIR + "cottage_bedroom02", "west", 0);
    add_exit(TOMBDIR + "cottage_in", "south", 0);

    reset_room();
}

stove_desc()
{
     write("The stove looks like it has not been used in some time. " +
	       "It is made of blackened cast iron that has rusted " +
	       "considerably over the years.  The rust is so bad that " +
               "pieces of the stove are beginning to flake off. " +
	       "You might be able to scrape some rust from the stove.\n"
	  );
     return 1;
}

scrape()
{
     if (flakes > 0) {
	  say(QCTNAME(TP) +
	      " scrapes some rust from the rust wood stove.\n");
	  write("You scrape some rust from the old rusty stove.\n");
	  clone_object(TOMBDIR + "rust_flakes")->move(environment(TP));
	  --flakes;
     }
     else {
	    say(QCTNAME(TP) + " scrapes the stove.\n");
	    write("You scrape the stove.\n");
       }
     return 1;
}
          

