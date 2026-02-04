#pragma save_binary

inherit "/std/room";
#include "/d/Terel/cedric/guild/guild_defs.h";
#include "/d/Terel/cedric/guild/guild_funs.c";

void
create_room()
{
   ::create_room();
   set_short("The Cycle's virtual meeting chamber");
       set_long(BS("This is a spacious room, removed from the bustle around "
		   + "the rest of the guilds.  Here, the Guildmaster, "
		   + "Assistant, and the Cycle can sit and discuss their plans "
                   + "for the guilds in peace.  It is constructed of pink "
                   + "granite, and with the bright blue skylights casting "
                   + "blue light about, as well as a few yellow portholes adding "
                   + "its own hue, the entire room is awash in bright colors.  "
                   + "The centerpiece of the room is a long table, made of "
                   + "the most intricatly carved and polished mahogany, it is "
                   + "where the great decisions are made.  "  
                   + "If you listen, you can hear the gentle "
		   + "music of the Muses, intertwined with the dark and brooding " 
                   + "song of the Sirens drifting through, encouraging the "
		   + "efforts of those within.\n"));
       add_exit(GUILD+"pri_office.c","north","@@check_minst");
       add_exit("/d/Terel/minstrels/dark/pri_office.c", "south", "@@check_dscpl");
       add_item(({"table", "Table"}), "This fine table is made from solid "
                   + "mahogany, polished to a rich hue that reflects the bright "
                   + "colors of this room well.  On one end of the table, a "
                   + "treble clef is carved.  On the other, the bass clef.  "
                   + "The center of the table is decorated with a carving of "
                   + "a single musical note.\n");
       add_item(({"skylight","Skylight","skylights","Skylights","porthole",
                  "portholes","Porthole","Portholes"}),
                     "These colored windows protect this meeting chamber from "
                   + "rain and the elements, and at the same time bathe the "
                   + "room in bright and beautiful colour.\n");       

       if(!present("board"))
	   fetch(GUILD+"ma_board.c");
       if(!present("dispenser"))
           fetch(GUILDOBJ+"dispenser.c");
}


void
init()
{
   ::init();
   add_action("listen","listen");
}

public int
listen()
{
   tell_object(TP(),BS("The Muses and Sirens intertwine their music and harmonies in "
	       + "ways that you never thought were possible.  The music "
	       + "seeps into your very soul, bringing you a peace "
	       + "deeper than you thought possible.\n"));
   return 1;
}

int check_minst()
{
   if (!(TP()->query_guild_member("The August Order of Minstrels")))
     {
      write("That exit is for those that serve the Muses.\n");
      return 1;
     }
   return 0;
}

int check_dscpl()
{
   if (!(TP()->query_guild_member("The Disciples of Dark Song")))
   {
      write("That exit is for those that serve the Sirens.\n");
      return 1;
   }
   return 0;
}