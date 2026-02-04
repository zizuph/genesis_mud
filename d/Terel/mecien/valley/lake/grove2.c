inherit "/std/room";
#define PATH "/d/Terel/mecien/valley/lake/"
#define GUILD_TYPE1 "occupational"
#define GUILD_TYPE2 "layman"
#define GUILD_STYLE "cleric"
#define GUILD_NAME  "Sacred Order of Druids"
#define SHADOW_OCC  "/d/Avenir/sood/sood_occ_sh"
#define SHADOW_LAY  "/d/Avenir/sood/sood_lay_sh"

create_room()
{
   set_short("Sacred Grove");
   set_long(
      "Shrouded in a living canopy of emerald, jade and aquamarine\n"
      +"leaves, this ancient grove whispers with the breeze. Silent\n"
      +"trees circle the area, creating an enclosure of sanctity. The\n"
      +"ground is coated with a blue-gray moss, except in the center\n"
      +"of the grove, where an ominous stone altar stands. An archway\n"
      +"of branches opens a passage to the south. To the north of the\n"
      +"grove, a strange stone arch leads further into the depths.\n"
   );

   add_item("altar", 
"An item of mysterious beauty, this altar is inscribed with arcane\n"+
"symbols climbing up the sides. A sense of living warmth eminates\n"+
"from it.\n");   

   add_exit(PATH + "entry", "south");
}

init()
{
   ::init();
   add_action("join", "join");
   add_action("my_leave", "abandon");
   add_action("list", "list");
   add_action("leave_both", "disavow");
}

join(string str)
{
   object shadow, shadow2;
   int result;
   
   if(!str) return 0;
   if(str == "dedicated"){
      
      notify_fail("The spirits will not accept you.\n");
      if (!do_I_want_this_player_in_my_guild(this_player()))
         return 0;
      
      notify_fail("The spirits will not accept you.\n");
      if (!do_I_accept_the_guilds_this_player_has_joined(this_player()))
         return 0;
      
      notify_fail("For unknown reason the spirits will not accept you " +
            "to the Order.\n");
      shadow = clone_object(SHADOW_OCC);
      if ((result = shadow->shadow_me(this_player(), GUILD_TYPE1,
                  GUILD_STYLE, GUILD_NAME)) != 1)
      {
         /* result = -1 (no name), -2 (wrong type), -3 (no style set),
         -4 (the guild the player already joined don't want this guild.)
         -5 (couldn't shadow the player, security problems. )
         Probably they have set the notify_fail() appropriate.
            0 (already member or player wasn't set properly) */
         
         /* This is one of the few times you destruct is OK to use... */
         "/secure/master"->do_debug("destroy", shadow);
         return 0;
      }
     
      shadow2 = clone_object(SHADOW_LAY);
      if ((result = shadow2->shadow_me(this_player(), GUILD_TYPE2,
          GUILD_STYLE, GUILD_NAME)) != 1)
      {
        "/secure/master"->do_debug("destroy", shadow);
        "/secure/master"->do_debug("destroy", shadow2);
	return 0;
      }

 
      write("You place your hands upon the stone altar.\n");
      write("A burning sensation is felt in your hands.\n");
      write("The spirits of the grove enter you.\n");
      return 1;                            
   }
   
}

do_I_want_this_player_in_my_guild(player)
{
   if (this_player()->query_race_name() == "goblin")
      {
      notify_fail("Goblins may not even enter the sacred grove.\n");
      return 0;
   }
   
   if (player->query_guild_member(GUILD_NAME))
      {
      notify_fail("You are already a member of our Order.\n");
      return 0;
   }
   
   /* You could test if the player has solved the guild quest or anything... */
      return 1;
}

do_I_accept_the_guilds_this_player_has_joined(player)
{
   if (this_player()->query_guild_member(GUILD_TYPE1))
      {
      notify_fail("You are already a member of another " + 
            GUILD_TYPE1 + " guild.\n"); 
      return 0;
   }
   if (this_player()->query_guild_member(GUILD_TYPE2))
   {
     notify_fail("You are already a member of another " +
         GUILD_TYPE2 + " guild.\n");
     return 0;
   }
   
   return 1;
}

list()
{
   string str;
   
   str = this_player()->list_mayor_guilds();
   if (str)
      write("You belong to these guilds.\n" + str);
   else
      write("You are not a member of any guild.\n");
   
   return 1;
}

my_leave(string str) 
{
   if(!str) return 0;
   if(str == "order"){
      notify_fail("You are not of the Order.\n");
      if (this_player()->query_guild_name_occ() != GUILD_NAME)
         return 0;
      
      if (this_player()->remove_guild_occ())
         write("You abandon your vows before the stone altar.\n");
      else
         write("A strange unknown cause keeps you with the Order.\n");
      
      return 1;
   }
  }

leave_both(string str)
  {
    if(!str) return 0;
    if(str == "dedication")
     {
       notify_fail("You are not of the Order.\n");
       if (this_player()->query_guild_name_occ() != GUILD_NAME)
          return 0;
   
       if (this_player()->remove_guild_occ())
         write("You abandon your occupational vows before the altar.\n");
       else
         write("A strange unknown force keeps you tied occupationally.\n");

       if (this_player()->remove_guild_lay())
	 write("You abandon your layman vows before the altar.\n");
       else
	 write("A strange unknown force keeps you tied as a layman.\n");
 
      return 1;
   }
 
   
}

