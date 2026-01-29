// -*-C++-*-
// file name:	tabuele.c	
// creator(s): 	Sirra March 98
// last update:	
// purpose:		yum-yum
// note:
// bug(s):	
// to-do:     

inherit "/std/food.c";

void
create_food()
{
    set_name("plate of tabuele");
    add_name(({"tabuele", "plate", "food"}));
    set_pname("plates of tabuele");
    set_short("plate of tabuele");
    set_pshort("plates of tabuele");
    set_long("A hot plate of fine rice spiced with green "
        +"clover and olive oil. As far as food is concerned, "
        +"it looks like the image of perfection.\n");
    set_amount(250);

}
