#pragma save_binary

inherit "/std/room";
#include "/d/Terel/cedric/guild/guild_defs.h";
#include "/d/Terel/cedric/guild/guild_funs.c";

void
create_room()
{
   ::create_room();
   set_short("The Guildmaster's Private Office");
       set_long(BS("This is a spacious office, removed from the bustle around "
		   + "the rest of the guild.  Here, the Guildmaster and "
		   + "Assistant can sit and discuss their plans for the "
		   + "guild in peace.  If you listen, you can hear the gentle "
		   + "music of the Muses drifting through, encouraging the "
		   + "efforts of those within.  To the south, you can enter "
                   + "the door to take you to the virtual Cycle meeting room." 
                   + "\n") + "Notice the box.\n");

       add_exit(GUILD+"office.c","north",0);
       add_item("box",BS("This box contains the original Book of Songs. There "
			 + "is a large button attached to the box.\n"));
       add_item("button","This is a large button attached to a large box "
		         + "marked: Reset Song Books.\n");
       add_cmd_item(({"button","button"}),({"push","press"}),"@@book_rset");

       
}

int book_rset()
{
    return BOOK_RESET();
}

void
init()
{
   ::init();
   add_action("listen","listen");
   add_action("enter","enter");
}

public int
enter(string str)
{
   if(!str || str != "door")
      {
      return_fail("You can only enter the door.\n");
   }
   else
      {
      if(TP()->query_real_name()==GUILDMASTER
	 || TP()->query_real_name()==ASSISTANT
	 || TP()->query_special_title(TP()->query_real_name()))
         {
	     TP()->move_living("retiring to the Cycle meeting room.",
			       "/d/Terel/cedric/guild/virt_office.c",1,0);
	     return 1;
	 }
      else
         return_fail("This is a private area.  Please do not disturb.\n");
   }
}

public int
listen()
{
   tell_object(TP(),BS("The Muses intertwine their music and harmonies in "
	       + "ways that you never thought were possible.  The music "
	       + "seeps into your very soul, bringing you a peace "
	       + "deeper than you thought possible.\n"));
   return 1;
}

