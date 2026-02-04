inherit "/std/container";

#include "/sys/stdproperties.h";
#include <money.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

#define PATH "/d/Terel/mecien/mountains/"
#define TP this_player()
#define TO this_object()
#define ENV environment(TO)

init()
{
   ::init();
   add_action("do_worsh", "worship");
   add_action("do_al_kiss", "kiss");
   add_action("mutilate", "mutilate");
   add_action("touch", "touch");
   add_prop("pray", "pray");
}

pray()
{
   write("You sense evil.\n");
   return 1;
}

touch(string str)
{
   object torch;
   
   if (!str)
      return 0;
   if (parse_command(str, all_inventory(TP), "[the] %o 'to' [the] 'altar'", torch) ||
         parse_command(str, all_inventory(TP), "[the] 'altar' 'with' [the] %o", torch))
   if (torch->query_prop(OBJ_I_LIGHT) && TO->query_prop("bloodied")) {
      remove_prop("bloodied");
      TP->catch_msg("You touch the torch to the altar.\n");
  tell_room(ENV, QCTNAME(TP) + " touches the altar with a burning torch.\n", TP);
      tell_room(ENV, "The altar begins to burn with a charnal smoke!\n");
   call_out("burn", 15);
      return 1;
   }
   TP->catch_msg("Nothing happens.\n");
   return 1;
}

burn(){
tell_room(ENV, "The altar burns brightly until all traces " +
    "of blood are gone from its face.\n");
  add_prop("proper", 1);
}

do_al_kiss(string str)
{
   object book;
   
   if (!str)
      return 0;
   if (str == "the altar") {
      TP->catch_msg("You kiss the altar.\n");
      tell_room(ENV, QCTNAME(TP) + " kisses the altar.\n", TP);
         book = present("book_of_darkness", ENV);
if(book){
      if (TP->query_prop("bloodied") || TO->query_prop("proper")) {
         tell_room(ENV, "A darkness settles over this place!\n");
   book->call_out("remove_seal", 10);
         return 1;
       }
}
      return 1;
   }
}

mutilate(string str)
{
   object corp;
   
   if (!str)
      return 0;
   corp = present("corpse", ENV);
   if (str != "corpse") {
      TP->catch_msg("Mutilate what?\n");
      return 1;
   }
   if (!present("corpse", ENV)) {
      TP->catch_msg("Mutilate what?\n");
      return 1;
   }
   TP->catch_msg("You mutilate the corpse over the black altar!\n");
   tell_room(environment(TP),
      QCTNAME(TP) + " mutilates " + corp->query_name() + 
      " over the black altar!\n", TP);
   corp->remove_object();
   if(TP->query_prop("bloodied")) {
      TP->catch_msg("You have already shared a victim to the darkness!\n");
      return 1;
   }
   if (TP->query_prop("thunder")) {
      TP->catch_msg("The blood on thy hands shall be glory to the darkness.\n");
      TP->add_prop("bloodied", 1);
      add_prop("bloodied", 1);
   }
   return 1;
}

do_worsh(string str)
{
   object book;
   
   if (str == "before the altar") {
      write("You kneel down and worship before the ancient black altar.\n");
      say(QCTNAME(TP) + " kneels down and worships before the black altar.\n");
      disturbance();
      book = present("book_of_darkness", ENV);
      if (book) {
         TP->catch_msg("A feeling of dread seems to overtake this place.\n");
         call_out("thunder", random(12));
       }
      return 1;
   }
}

thunder()
{
   tell_room(ENV, "Thunder sounds through the dark and twisted stormlit sky!\n");
   if (TP->query_prop("thunder")) {
      TP->catch_msg("Lightning strikes you!\n");
      TP->heal_hp(-100);
      tell_room(ENV, QCTNAME(TP) + " is struck by lightning!\n", TP);
      return 1;
   }
   TP->add_prop("thunder", 1);
   TP->catch_msg("You feel very strong!\n");
}

disturbance()
{
   object *userlist;
   int i;
   
   userlist = users();
   for (i=0; i<sizeof(userlist); i ++)
   if (userlist[i]->query_guild_member("The Ancient Mystic Order"))
      userlist[i]->catch_msg("You sense a disturbance in the ancient world.\n");
}

create_container()
{
   object skull;
   
   set_name("altar");
   set_short("altar");
   set_pshort("altars");
   set_long("A long black obsidian altar, it has a small niche.\n");
   add_prop(CONT_I_WEIGHT,     90000);   /* It weighs 1 Kg            */
   add_prop(CONT_I_MAX_WEIGHT, 195000);   /* It can contain up to 5 Kg  */
   add_prop(CONT_I_VOLUME,     200000);   /* It measures 3 Ltr         */
   add_prop(CONT_I_MAX_VOLUME, 275000);   /* It can contain 10 Ltr       */
   add_prop(CONT_I_RIGID, 0);            /* It is not a rigid object       */
   add_prop(CONT_I_CLOSED, 0);
   add_prop(CONT_I_LOCK, 0);
   add_prop(OBJ_I_NO_GET, 1);
   add_prop(OBJ_I_INVIS, 0);
   add_prop(CONT_I_TRANSP, 1);
   seteuid(getuid(this_object()));
   skull=clone_object("/d/Terel/mecien/mountains/skull");
   skull->move(this_object());
   
   /*
   *  enable_commands();
   */
}
