// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc

#include "/d/Terel/include/Terel.h"
inherit STDROOM;
#include "../local.h"

int flakes;

void
reset_room()
{
     flakes = 4;
}

void
create_room()
{
   
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

    add_item(({"dishes", "noodles"}), 
	"The dishes are covered with sticky hardened noodles.\n"
    );

    add_item(({"door", "laquered door", "door remains", "doorway"}), 
        "The door looks like it was ripped apart.  You can see what appear " +
        "to be claw marks on the ragged boards where chipped wood flakes " +
    	"away from deep scratches in the surface.\n"
    );

    add_item(({"stove", "wood stove"}), "@@stove_desc");

    add_item(({"rust", "rust on stove" }), 
        "The rust on the stove has made it useless for cooking.\n"
	);
    
	add_item(({"ceiling", "soot", "residue"}),
        "The sooty residue looks very greasy.  It doesn't look like it " +
	"could have been produced from burning wood.\n"
    );

    add_prop(ROOM_I_INSIDE, 1);

    add_object(OBJDIR +"pot", 2);
    
    add_exit("cottage_garden", "north", 0);
    add_exit("cottage_bedroom01", "east", 0);
    add_exit("cottage_bedroom02", "west", 0);
    add_exit("cottage_in", "south", 0);

    reset_room();
}

string
stove_desc()
{
	if (!flakes)
	{
        write("This old cast iron stove looks like it has not been used "+
            "in a long time. So long, in fact, that it is badly rusted.\n");
        return "";
	}
    write("The stove looks like it has not been used in some time. " +
        "It is made of blackened cast iron that has rusted " +
	    "considerably over the years. The rust is so bad that " +
        "pieces of the stove are beginning to flake off. " +
	    "You might be able to scrape some rust from the stove.\n"
	);
    return "";
}

int
do_scrape(string str)
{
    notify_fail(capitalize(query_verb()) +" what?\n");
    if (!str || !strlen(str))    
        return 0;
    
    if (!parse_command(str, ({ }),
    "[the] [some] 'rust' [from] / [off] / [on] [the] [rusty] [cast] [iron] "+
    "[wood] 'stove'", str))
		return 0;
		
    if (!flakes)
    {		
	    write("The remaining rust doesn't seem to want to come off.\n");	
        return 1;
	}

    say(QCTNAME(TP) +" scrapes some rust from the stove.\n");
	write("You scrape some rust from the stove. It falls on the floor.\n");
	clone_object(OBJDIR +"rust_flakes")->move(environment(TP));
	--flakes;
    return 1;
}
          

void init()
{
    ::init();
    add_action(do_scrape,    "scrape");
    add_action(do_scrape,    "scratch");
}
