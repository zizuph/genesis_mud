inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <formulas.h>
#include "/std/combat/combat.h"

object monster,places;

void
reset_room()
{
  set_searched(0);

  if(!monster)
  {
    clone_object(MONSTER+"mosquito")->move(TO);
    clone_object(MONSTER+"mosquito")->move(TO);
    clone_object(MONSTER+"mosquito")->move(TO);
    clone_object(MONSTER+"mosquito")->move(TO);
    clone_object(MONSTER+"mosquito")->move(TO);
    tell_room(TO,"A lotsa mosquitoes arrives.\n");
  }
}

void create_room()
{
  int herb;

  set_short("In a jungle");
  set_long(break_string(
           "You are standing in a thick jungle. All around you there's "+
           "vegetation and the sun is shadowed by the leaves of the "+
           "large trees that are growing here. The air is very humid "+
           "and thick enough to eat. Every step causes a cloud of hungry "+
           "mosquitoes, hungry for your blood. You feel very uncomfortable "+
           "here, but you haven't got a clue where to go.\n",60));

  set_noshow_obvious(1);             

  add_item("jungle","It's thick, it's green, it's wet.\n");
  add_item("vegetation","There's lot of different flowers, bushes and trees "+
           "growing here.\n");
  add_item(({"tree","trees"}),"There's a lot of them here. A lot.\n");
  add_item(({"leaf","leaves"}),"The leaves are like a roof over your head, "+
             "dimming the sun and shadowing the ground.\n");
  add_item("air","How?");
  add_item("sun","You can't see the sun because of the leaves of the large "+
           "trees that is growing here.\n");
  add_item(({"cloud","mosquito","mosquitoes"}),"They're small, many and "+
             "hungry.\n");
  add_item(({"track","tracks"}),"You can't see any, perhaps if you search "+
             "carefully.\n");

  OUTSIDE;

  if(random(100)>50)
  {
    herb = random(5);
    write(herb);

    if(herb==0) add_herb_file(OBJ+"herb_iunora");
    else if(herb==1) add_herb_file(OBJ+"herb_unisk");
    else if(herb==2) add_herb_file(OBJ+"herb_gizsha");
    else if(herb==3) add_herb_file(OBJ+"herb_wizsha");
    else if(herb==4) add_herb_file(OBJ+"herb_mortia");

    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  }

  add_exit(JUNGLE+"j08","northwest","@@work");
  add_exit(JUNGLE+"j10","north","@@work");
  add_exit(JUNGLE+"road/r3","northeast","@@work");
  add_exit(JUNGLE+"j10","west","@@work");
  add_exit(JUNGLE+"j10","east","@@work");
  add_exit(JUNGLE+"j10","southwest","@@work");
  add_exit(JUNGLE+"j10","south","@@work");
  add_exit(JUNGLE+"j10","southeast","@@work");

  reset_room();
}

init()
{
  ::init();
  add_action("search","search");
}

int
search(string str)
{
  mixed words;

  if (!strlen(str)) return 0;
  if (str != "here for tracks")
  if (member_array("tracks",explode(str," ")) == -1)
    return 0;
  else
  {
    notify_fail("Search for what?\n");
    return 0;
  }
  write("You kneel down and start to search for tracks on the "+
        "ground.\n");

  set_alarm(5.0,-1.0,"tracks");
  
  return 1;
}

int
tracks()
{

  int trck,ntrck,aware,locsns;

  trck   = TP->query_skill(SS_TRACKING);
  aware  = TP->query_skill(SS_AWARENESS);
  locsns = TP->query_skill(SS_LOC_SENSE);
  ntrck  = 45+random(15);

  if(trck>ntrck && aware>45 && locsns>45)
    TP->catch_msg(break_string(
          "After looking carefully on the ground, you think there's "+
          "exits northwest and northeast.\n",60));
  else
    TP->catch_msg(
          "You find nothing special...\n");

 
  return 1;

}

herb_search(object player, string str)
{
  string place, what;
  if (parse_command(str,TO,"%s 'for' 'herbs' / 'herb'",place))
    return search_for_herbs(player);
  return "";
}

int
work()
{

  if(TP->query_fatigue()<10)
  {
    write("You are too tired to walk.\n");
    return 1;
  }

  TP->add_fatigue(-10);
  write("You make your way through the thick vegetation.\n");

  return 0;
}