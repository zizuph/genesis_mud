/*
  A big iron pot. Mortricia 920722
  Rehacked into a gizmo :)
  Janus 930218
  */
inherit "/std/container";
#include "/d/Terel/common/terel_std_rec.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()
#define GARD_DIR        JANUSDIR + "garden/"
#define ARM_DIR         JANUSDIR + "armor/"
#define WEP_DIR         JANUSDIR + "weapons/"
int sprayloads;
init()
{
  add_action("mix", "mix");
  add_action("do_spray", "spray");
  sprayloads=0;
  ::init();
}

create_container()
{
  set_name("gizmo");
  set_short("strange gizmo");
  set_pshort("strange gizmoes");
  set_long(break_string("A strange gizmo. "+
		 "It seems that you could mix things in it and also spray "+
		 "the room with anything that the gizmo contains.\n",70));
  set_adj(({"strange"}));
  
  add_prop(OBJ_I_VALUE, 20 + random(20));
  
  add_prop(CONT_I_WEIGHT, 1000);
  add_prop(CONT_I_MAX_WEIGHT, 1500);
  add_prop(CONT_I_VOLUME, 1500);
  add_prop(CONT_I_MAX_VOLUME, 2500);
  add_prop(CONT_I_TRANSP, 1);
  add_prop(CONT_I_RIGID, 1);
}

mix(string how)
{
  object item1, item2, item3, item4, item5, item6, item7;
  object *saker, parsl;
  int notok, i, ok;
  item1 = present("black flower");
  item2 = present("octarine flower");
  item3 = present("green flower");
  item4 = present("red fruit");
  item5 = present("leaf");
  item6 = present("bulb");
  if (item1 && item2 && item3 && item4 && item5 && item6){
    ok=1;
    item1 -> remove_object();
    item2 -> remove_object();
    item3 -> remove_object();
    item4 -> remove_object();
    item5 -> remove_object();
    item6 -> remove_object();
  }
  saker = all_inventory(TO);
  notok=sizeof(saker);
for (i=0; i<sizeof(saker);i++) {
   if(saker[i]->query_prop("is_mixable")==1 || saker[i]->query_prop(
      "set_herb_value")>=0){
      saker[i]-> remove_object();
   }
}
  if (notok==0 && ok==1) {
    sprayloads=10;
    write(BS("You managed to mix the ingredients, there is now "+
	     "greenish liquid in the gizmo. Use 'spray' to disperse "+
	     "some of the liquid in the air.\n"));
    add_item(({"liquid","green liquid","greenish liquid"}),BS(
                  "The liquid smells quite strange. Judging from the size "+
                  "of the bottle you estimate that a fully filled gizmo "+
                  "should be sufficient to produce about 10 sprays.\n"));
    say(QCTNAME(this_player()) + " is mixing something in the gizmo.\n");
    return 1;
}
   if (notok>0){
    sprayloads=-1;
    write(BS("You grind the stuff together, there is now a purple "+
	     "fluid in the gizmo. \n"));
    add_item(({"liquid","purple liquid"}),BS(
	     "The liquid smells quite strange. Judging from the size "+
	     "of the bottle you estimate that a fully filled gizmo "+
	     "should be sufficient to produce about 10 sprays.\n"));
    say(QCTNAME(this_player()) + " is mixing something in the gizmo.\n");
    return 1;
  } else {
    write(BS("Don't you think that you should put something into "+
             "gizmo before you try to mix? \n"));
  }
  return 1;
}

do_spray(string what)
{
  
  object *obarr, *elist;
  string namn;
  int i, count, dutt2;
  
  obarr = all_inventory(environment(TP));
  count = 0;
  if(sprayloads < 0 && sprayloads >= -10){
    sprayloads--;
    write("You spray the room with the purple liquid.\n");
    say(BS(QCTNAME(TP)+" uses a strange gizmo, and "+
	   "the surrounding area is covered in a fine purple mist.\n"));
    return 1;
  }
  if(sprayloads>0){
    sprayloads--;
    write("You spray the room with the green liquid.\n");
    say(BS(QCTNAME(TP)+" uses a strange gizmo, and "+
	   "the surrounding area is covered in a fine green mist.\n"));
    elist = TP ->query_enemy(-1);
    if (!sizeof(elist))
        return 1;
    TP->stop_fight(elist);
    for (i = 0; i < sizeof(obarr); i++) {
      if (!function_exists("query_enemy", obarr[i])) continue;
      elist = obarr[i]->query_enemy(-1);
      if (!sizeof(elist)) continue;
      if(obarr[i]->query_prop("_janus_peace_") == 1){
   	obarr[i]->stop_fight(elist);
	dutt2=1;
      }
    }
    if(dutt2 == 1){
      write("The bugs seems to be a bit dazed.\n");
      say("The bugs seems to be a bit dazed. \n");
    }
    return 1;
  }
  write("There is no liquid left.\n");
  return 1;
}
