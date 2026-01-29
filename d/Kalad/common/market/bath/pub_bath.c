inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()
{
    ::create_room();
    add_prop(ROOM_I_INSIDE,1);

    set_short("Public Bath");
    set_long(BS(
      "This is the public bath of the Dirty Swine. " +
      "It is a long room filled almost entirely by a shallow " +
      "basin of water. The basin is packed with naked bathers, " +
      "half emersed in the water, scrubbing furiously at " +
      "different parts of their bodies. " +
      "There is a small sign on the wall. " +
      "\n"));

    add_exit(MARKET(bath/hall),"south","@@s_block",0); /*inside*/

    add_prop(MRKT_IN_NO_HEAR,1);

    add_item(({"sign","small sign"}),
      "The sign is so small, its hard to read. But go ahead and try.\n");
    add_item(({"bath","public bath","basin"}), BS(
      "This huge water filled basin almost entirely " +
      "fills the room. It is packed with naked bathers, " +
      "cleaning themselves.\n"));
    add_item("water",BS(
      "This is the water used by hundreds of Kabalis to " +
      "remove the filth of the past days and weeks. " +
      "Needless to say, the water doesn't look that " +
      "clean and there are various unidentifiable " +
      "oddments floating in it. You assume that it is " +
      "changed daily but it is best not to think about. " +
      "After all, if you were really concerned about the " +
      "quality of the water, you would have put out the " +
      "extra coin for a private bath. The water is quite warm.\n"));
    add_cmd_item("water",({"drink","smell"}),
      ({"You take one look at the water and reconsider.\n",
      "It smells about as good as filthy water should smell.\n"}));
    add_item(({"naked bathers","bathers"}),"@@bathers");
}

s_block()
{
    if(TP->query_prop(IN_WATER))
    {
      write("You have to exit the water first.\n");
      return 1;
    }
    else
      return 0;
}



read(str)
{
    NF("Read what?\n");
    if(str != "sign" && str != "small sign")
      return 0;

    write(
      "*********************************************\n" +
      "*                                           *\n" +
      "*  NOTICE:                                  *\n" +
      "*     No Singing! No Swimming! No Refunds!  *\n" +
      "*     The Water Is Changed Daily.           *\n" +
      "*                                           *\n" +
      "*     The Management May Not Be Held        *\n" +
      "*      Liable For Health Of Clients.        *\n" +
      "*                                           *\n" +
      "*********************************************\n" +
      "");

    return 1;
}

go_water(str)
{
    NF(C(query_verb()) + " what?\n");
    if (str != "water" && str != "basin" && str != "bath")
      return 0;

    if( TP->query_prop(IN_WATER) )
      write("You're already in the water.\n");
    else
    {
      TP->add_prop(IN_WATER,1);
      write(BS(
        "You step in to the basin and the warm water " +
        "reaches your waist.\n"));
      say(QCTNAME(TP) + " steps into the water.\n");
    }

    return 1;
}

out_water(str)
{
    if (query_verb() == "climb")
    {
      NF("Climb what?\n");
      if(str!="out of water"&&str!="out of basin"&&str!="out of bath")
        return 0;
    }
    else
    {
      NF("Exit what?\n");
      if (str != "water" && str != "basin" && str != "bath")
        return 0;
    }

    if (TP->query_prop(IN_WATER) != 1)
      write("You aren't in the water.\n");
    else
    {
      TP->add_prop(IN_WATER,0);
      write(BS("You climb out of the warm water and shiver " +
        "as the cool air touches your skin.\n"));
      say(QCTNAME(TP) + " climbs out of the water and shivers.\n");
    }

    return 1;
}

no_swim(str)
{
    if (str)
      return 0;

    if (!TP->query_prop(IN_WATER))
    {
      write("You can't swim unless you're in the water.\n");
      return 1;
    }

    write(BS(
      "You start to splash around in the water but a burly " +
      "attendant stops you, saying: 'This isn't a pool, buddy!'\n"));
    say(BS(QCTNAME(TP) + " starts splashing around in the water " +
      "but a burly attendant warns " + TP->query_pronoun() +
      " to stop.\n"));
    return 1;
}

sing(str)
{
    if (!str)
      str = "RUBBER DUCKY, YOUR THE ONE..." +
        "YOU MAKE THE BATHTUB, SO MUCH FUN...";

    write(BS("You start singing: '" + str + "....'" +
      " but a furious redfaced attendant comes running " + 
      "out screaming: 'I told you guys I was gonna murder " +
      "the next bum who started singing!'. He scans the room " +
      "but luckily didn't notice you.\n"));
    say(BS( QCTNAME(TP) + " starts singing: '" + str + "....'" +
      " but a furious redfaced attendant comes running " +
      "out screaming: 'I told you guys I was gonna murder " +
      "the next bum who started singing!'. He scans the room " +
      "but couldn't see who did it.\n"));

    return 1;
}

bathe(str)
{
    object *ob;
    int i;

    if(str)
      if( str != "me" && str != "self" && str != "myself")
        return 0;

    if(!TP->query_prop(IN_WATER))
    {
      write("You can't bathe until you enter the water.\n");
      return 1;
    }

    if (TP->query_prop(LIVE_I_DIRTY) == 0)
        write(BS("You bathe yourself in the relaxing warm " +
          "water, though you were already clean.\n"));
    else
        write(BS("You scrub yourself thoroughly and layers " +
          "of filth come off in the warm water. " +
          "You're now clean as whistle!\n"));

    say(QCTNAME(TP) +
      " bathes in the water. You realize it was about time.\n");

    TP->add_prop(LIVE_I_DIRTY,0);

    ob = deep_inventory(TP);
    for (i = 0; i < sizeof(ob); i++)
      if (ob[i]->id("dirty"))
        ob[i]->remove_object();

    return 1;
}

bathers()
{
    string str;

    str = BS(
      "Naked bathers of all varieties fill the basin. " +
      "You don't think they appreciate your inspection " +
      "of them, as half of them stop and glare at you. " +
      "One man, however, gives you an over-friendly smile. " +
      "You start to blush and quickly look away.\n");

    say(BS(QCTNAME(TP) + " starts to look at the naked bathers " +
      "but gets caught. " + C(TP->query_pronoun()) +
      " blushes and quickly turns away.\n"));

    return str;
}
int
do_emote(string str)
{
  notify_fail("Emote what?\n");
  if(!str)
    return 0;

  say( QCTNAME(this_player()) + " " +str+ "\n" );
  write("You emote: " +METNAME+ " " +str+ "\n");
  return 1;
}
init()
{
    ::init();
    AA(bathe,bathe);
    AA(bathe,scrub);
    AA(bathe,clean);
    AA(bathe,wash);
    AA(no_swim,swim);
    AA(sing,sing);
    AA(go_water,enter);
    AA(go_water,go);
    AA(out_water,exit);
    AA(out_water,climb);
    AA(read,read);
    add_action(do_emote, "emote");
}