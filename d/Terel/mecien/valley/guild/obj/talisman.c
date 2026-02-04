/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/armour";
#include <macros.h>
#include <stdproperties.h>
#define EN environment

#define TP this_player()
#define GUILD "The Ancient Mystic Order"
#define PATH "/d/Terel/mecien/valley/guild/"

int process;

create_armour(){
   
   set_name("talisman");
   add_adj("silver");
   set_long("It is a mysterious talisman, shaped like a serpent\n"
      + "coiled about a crystal of deep purple.\n");
}

init(){
   add_action("magnify", "magnify");
   add_action("grace", "grace");
   add_action("speech", "speech");
   add_action("haunt", "haunt");
   add_action("glow", "glow");
   add_action("spirit", "spirit");
   add_action("cer", "cer");
   add_action("misery", "misery");
   ::init();
}

glow(){
   tell_room(environment(this_player()), "The twelve statues seem to glow.\n");
   return 1;
}

misery(){
  object ob;
   switch(process){
   case 0: 
   TP->command("weep");
   break;
   case 1:
     ob= present("elder");
     ob->command("comfort mecien");
  break;
   case 3:
    ob->command("say Let not Darkness rule Thy Wise heart Mecien, for Mystery abides with Thee and in Time, some Light might find its way inward");
   break;
   case 4:
    TP->command("weep");
  break;
default:
  process = 0;
}

    process ++;
return 1;
}

cer(){
  int n;
  object ob;
  n = random(3);
  ob = present("cantor", EN(TP));
  if(ob){
   write("Calling ceremony.\n");
   if(n == 0) ob->do_cer();
  if(n == 1) ob->do_dead();
  if(n == 2) ob->do_fire();
}
return 1;
}


magnify(string str){
int piety;
object who;

if(!str) return 0;
who = find_living(str);


if(!who) return "Magnify who?\n";
  piety = who->stat_to_exp(1 + who->query_stat(7));
write("You cast your glory upon " + who->query_name() + ".\n");
say(QCTNAME(TP) + " sings some ancient song, known only to those of Mystery.\n");
  who->set_guild_stat(7, piety + 2000);
return 1;
}
grace(string str){
int piety;
object who;

if(!str) return 0;
who = find_living(str);


if(!who) return "Grace who?\n";
piety = who->query_skill(130005);
write("You cast your eminence upon " + who->query_name() + ".\n");
say(QCTNAME(TP) + " reaches out to the Ancient world.\n");
who->set_skill(130005, piety + 10);
return 1;
}

speech(string msg){
   object *userlist, sec, inv;
   int i, n;
   string dom;
   
   if(!msg) return 0;
   if(this_player()->query_guild_name_occ()!=GUILD){
      write("Nothing happens.\n");
      return 1;
   }
   userlist = users();
   for (i = 0; i< sizeof(userlist); i++)
   if (userlist[i]->query_guild_member(GUILD) &&
         present("Mystic_ring", userlist[i]))
   tell_object(userlist[i], 
      "The voice of " + this_player()->query_name() + " whispers from " +
   "the shadows saying:\n" + msg + "\n", this_player());
   
   this_player()->catch_msg("You speak to the Order.\n");
   return 1;
}

haunt(string str){
   object mystic;
   if (!str) return 0;
   mystic = find_living(str);
   write("You send a call out.\n");
   if(!mystic){
      write("The spirits whisper: Master, we have searched but cannot find...\n");
      return 1;
   }
   mystic->catch_tell("You feel called by the Ancients.\n");
   return 1;
}

spirit(string str){
   object mystic, ROOM;
   if(!str) return 0;
   mystic = find_living(str);
   if(!mystic){
      write("The spirits whisper: Master, we have searched but cannot find...\n");
      return 1;
   }
   ROOM = environment(mystic);
   mystic->catch_msg("You feel an eerie presence approaching.\n");
   set_alarmv(3.0, -1.0, "presence", ({ mystic, ROOM }));
   return 1;
}

presence(object mystic, object ROOM){
   
   tell_room(ROOM, "A darkened figure, hooded and robed appears.\n");
   tell_room(ROOM, "The dark and hooded figure says: Greetings, " + mystic->query_name() + "\n");
   mystic->catch_msg("The dark and hooded figure looks into your eyes. You see his eyes, which peer from beneath his hood, they shine bright like stars!\n");
   tell_room(ROOM, "The dark and hooded figure fades away.\n");
   return 1;
}

