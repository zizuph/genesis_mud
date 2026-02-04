/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP   this_player()
#define TO   this_object()
#define TREASURY "/d/Terel/mecien/valley/guild/treasury"

static object elder=0;
int silver;

public void
reset_room()
{
   if (elder) return;
   
   elder = clone_object(GUILD_DIR + "cantor");
   elder->move_living("M", TO);
}

public void
init()
{
   ::init();
   add_action("pray", "pray");
   add_action("sacrifice", "sacrifice");
   add_action("start", "start");
}

public int
pray(string str)
{
   if (strlen(str)) return 0;
   
   write("You kneel down at the altar and pray quietly.\n");
   say(QCTNAME(TP) + " kneels before the altar and prays.\n");
   
   if (!MEMBER(TP)) {
       set_alarm(10.0, -1.0, "ancient", TP);
       return 1;
   }
   if (TP->query_alignment() <= -300) {
       TP->catch_msg("You feel uneasy.\n");
       set_alarm(10.0, -1.0, "doom", TP);
       return 1;
   }
   if (TP->query_alignment() >= 200) {
       set_alarm(10.0, -1.0, "peace", TP);
       return 1;
   }
   TP->catch_msg("The hall feels cold and silent.\n");
   return 1;
}

public void
peace(object who)
{
   int n = random(3);
   object ob;
   
   if (!who || environment(who) != TO) return;
   
   if (n == 0) {
      who->catch_msg("A feeling of peace descends upon you.\n");
   } else if (n == 1) {
      ob = clone_object(GUILD_DIR + "spells/pacis_anima");
      ob->set_name("spirit");
      ob->move_living("M", environment(who));
      tell_room(environment(who), QCTNAME(ob) +
                " arrives from its realm.\n", ob);
      ob->command("say I have heard your prayers, let peace go before you.");
      ob->command("emote whispers an ancient prayer.");
      set_alarm(6.0, -1.0, "depart", ob);
   } else {
      who->catch_msg("You sense some unknown presence pass over you.\n");
   }
   
   return;
}

public void
depart(object ob)
{
   if (!ob) return;
   ob->command("say We shall be with you.");
   ob->command("emote raises a hand.");
   ob->remove_object();
}

public void
doom(object who)
{
   object ob;
   
   if (!who) return;
   
   ob = clone_object(GUILD_DIR + "spells/angel");
   ob->move_living("M", environment(who));
   who->catch_msg("A shadow seems to fall over you.\n");
   tell_room(environment(who), "A shadow descends upon " + QTNAME(who) +
             ".\n", who);
   ob->set_name("spirit");
   ob->set_adj("dark");
   ob->set_short("dark spirit");
   ob->command("say I have come in answer to your prayer, Ye of dark heart.");
   ob->attack_object(who);
   
   set_alarm(20.0, -1.0, "go", ob);
}

public void
go(object ob)
{
   if (!ob) return;
   ob->command("say Let evil be no more.");
   ob->command("emote traces an ancient sign in the air " +
               "and disappears into the shadows.");
   ob->remove_object();
}

public int
sacrifice(string str){
  object coin;
   int num;
   int amount;
   if(!str) num = 1;
   coin = present("silver coin", TP);
   if(!coin){
   write("You have nothing appropriate for the ancient ways.\n");
   return 1;
   }
      
    amount = coin->num_heap();
  if(!num){
  if(!parse_command(str, TP, "%d [silver] [coins] [coin]", num)){
      write("Your offering was unsuccessful.\n");
   return 1;
}
   if(num > coin->num_heap()){
   write("You do not have that much to sacrifice.\n");
  return 1;
}
}

     
   write("You make a sacrificial offering to the sacred shrine.\n");
       say(QCTNAME(TP) + " makes a sacrificial offering to the sacred shrine.\n");
   coin->set_heap_size(amount - num);
    restore_object(TREASURY);
   silver = silver +num;
   save_object(TREASURY);
   set_alarmv(3.0, -1.0, "ancient", ({ TP, num }));
   return 1;
}

ancient(object me, int num){
  int n;
     if(random(100) > 10){
 me->catch_msg("The ancient spirits descend upon you with their glory.\n");
   n = me->query_skill(PIETY);
   me->set_skill(PIETY, n + 1 + random(num));
}
}


public int
start(string str)
{
   if (str != "here") return 0;
   
   if (!MEMBER(TP)) {
      write("Only those of the Order may make their origin here.\n");
      return 1;
   }
   
   TP->set_default_start_location(GUILD_DIR + "temple");
   write("Thy origin shall now be in this holy place.\n");
   say(QCTNAME(TP) + " says a prayer.\n");
   return 1;
}

public void
create_room()
{
   set_short("Temple");
   set_long("This the exalted hall is principal temple and convocation for "
      + "the mystics of this place. The assemblage gathers here like some "
      + "terrible host prepared for battle, though council and guidance "
      + "are the usual weapons arrayed in such conflicts. "
      + "Silver gleams from the vaulted ceiling and from the luminous "
      + "walls and pillars that have been layered in that precious "
      + "metal. Two pillars stand next to each of the four exits, like "
      + "sentinals protecting this holy place. The floor descends to form "
      + "step-like rows of seats in a semi-circle. At the bottom of this "
      + "theatre-like bowl is an altar.\n");

   add_exit(GUILD_DIR + "hall",      "west",  0);
   add_exit(GUILD_DIR + "e_hall",    "east",  0);
   add_exit(GUILD_DIR + "sanctuary", "north", 0);
   add_exit(GUILD_DIR + "gallery",   "south", 0);

   add_item("ceiling", "It is vaulted, covered with silver.\n");
   add_item("pillars", "These silver pillars, two at each exit, " +
      "support the high vaulted ceiling of this grand hall.\n");
   add_item(({"bowl", "seats", "rows", "steps"}), "The floor of the hall "
      + "descends in a circular pattern down to an altar, cut into rows "
      + "that tier down, much like an amphitheatre.\n");
   add_item("altar", "A large circular dias upon which rests a large "
      + "silvery-white stone table. The table is rectangular and "
      +"is inscribed with a white four-pointed star.\n");
   add_item("table", "It is the center of the altar, inscribed with a " +
      "four-pointed star.\n");
   add_item("star", "It is inscribed upon the altar table.\n");

   reset_room();
}
