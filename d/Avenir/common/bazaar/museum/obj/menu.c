// -*-C++-*-
// file name:	menu.c	
// creator(s): 	sirra march 98
// last update:	
//   Manat on Sep 2002 - fixed the prices to match the shop.
// purpose:	menu to be given by npc in coffee_room.c
// note:		
// bug(s):
// to-do:     	edit the write() in the do_read().


inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

int do_read(string str);

void
create_object()
{
    set_name("menu");
    add_name("_museum_cafe_menu");
    set_short("artfully decorated menu");
    set_long("Lavishly transcribed onto parched webcloth, "
        + "the calligraphy is not so decorative that you "
	+ "cannot read it.\n");
}

int
do_read(string str)
{
    if (!str)   
	return 0;    

    if (str == "menu")
    {
        write("The menu reads:\n\n"
            +"        Welcome to GoatFeathers Cafe.\n"
            +"    Mishel icu Llin, under-chef in the kitchens\n"
            +"    of the former High Inquisitor, is your cook.\n\n"
            +"    Today, he is pleased to offer the following:\n\n"
            +"        Hot Sybarun Kahve .............. 40 cc\n"
			+"        Spiked Hot Kahve .............. 250 cc\n\n"
            +"        Sardines in Grape-leaves ......  36 cc\n"
            +"        Plate of Tabuele .............. 120 cc\n"
	        +"        Loaf of Zuccarrot Bread ....... 160 cc\n"
	        +"        Stuffed Eggplant .............. 425 cc\n"
            +"        Rose Jelly ..................... 12 cc\n"
            +"\n    Please return menu to server after ordering.\n\n");

        tell_room(environment(this_player()), QCTNAME(this_player()) 
            +" reads "+ this_player()->query_possessive()
            +" menu.\n", this_player());
        return 1;
    }
    return 0;
}

void
init()
{
    ::init();
    add_action(do_read, "read");
}

void
enter_env(object inv, object from)
{
   ::enter_env(inv, from);
    if (!from)
        return;
 
    if (inv->query_prop(ROOM_I_IS))
    {
        tell_room(inv, "The "+ short() +" takes wing on a "+
            "breeze and floats away.\n");
        set_alarm(1.0, 0.0, &remove_object(this_object()));
        return;
    }
}

