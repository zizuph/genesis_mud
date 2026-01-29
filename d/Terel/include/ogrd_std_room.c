/* A std room for the old garden in the Terel mansion.
 * This file is inherited by all ogrd*.c rooms
 * Mortricia 5/94
 * Herbs added 9/00, Shinto
 */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;
inherit "/d/Terel/std/herbsearch";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <money.h>
#include "/d/Terel/include/herb_arrs.h"
#include "/d/Terel/inclide/quest_bits.h"

#define DEF_ITEMS   ({"sword", "helmet", "bag", 20})
#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))]) 

static int PLANTSTR;
static int NOOFPLANTS=0;
static int NOOFTOOLS=0;
static int BIGMAMA;
static int SKULL=0;
static object skull;

void   create_ogrd_room();
string do_hitw();
string do_search();
void   do_entangle();
int    gogo();
int    gogoN();
mixed *setup_search();

void
reset_room()
{
    NOOFPLANTS = 3;
    NOOFTOOLS = sizeof(setup_search());
    if (skull) skull = 0;
    BIGMAMA = 0;
}

void
create_room()
{
    create_ogrd_room();

    add_item(({"vine","vines","thorny vines","thorny vine"}),
               BS("The vines have large, "+
               "sharp, and barbed thorns. They move very slowly as if seeking"+
               " for something.\n"));
    add_item(({"area","ground","garden"}),BS("This place looks quite desolate"+
               " snow and vines cover the ground.\n"));
    add_item(({"bush","bushes","thorny bush","thorny bushes"}),
               BS("The bushes still have most of their leaves left. The "+ 
               "leaves are small and have a dark green reddish color. Most of"+
               " the bushes have large, "+
               "sharp, and barbed thorns.\n"));
    add_cmd_item(({"vine","vines","thorny vines","thorny vine"}),
                ({"hit", "cut"}),({"@@do_hitw", "@@do_hitw"}));
    add_prop(OBJ_I_SEARCH_TIME, 20);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    set_alarm(10.0, -1.0, "do_entangle");

    set_up_herbs( ({ ONE_OF_LIST(GARDEN_HERBS),
                     ONE_OF_LIST(GARDEN_HERBS),
                     "/d/Terel/common/herbs/sebre",}),
                  ({"vines","bushes"}) , 3 );

    reset_room();    
}

string
do_search()
{
  int i, j, nsc;
  mixed *items;
  object item, ob1, ob2;

  i = TP->query_skill(SS_AWARENESS) - 15;
  
  if (i <= 0)
      return "Maybe you should train your observational skills.\n";
  if (NOOFPLANTS > 0 || BIGMAMA > 0)
      return "The vines are in the way. You need to cut them to " +
              "continue your search.\n";
  if ((ob1 = present("vine")) || (ob2 = present("koekkenmoddig"))) {
      if (ob1) ob1->attack_object(TP);
      if (ob2) ob2->attack_object(TP);
      return "The vines are in the way. You need to kill them to " +
             "continue your search.\n";
  }
  if (NOOFTOOLS <= 0)
      return "It looks pretty empty here.\n";

  items = setup_search();
  j = random(NOOFTOOLS);
  if (j >= 0 && j < sizeof(items)) {
      seteuid(getuid(TO));
      if (SKULL == 1 && !skull) {
         if (!(TP->test_bit("Terel", QUEST_WIT_GROUP, QUEST_WIT_BIT))) {
	     skull = clone_object(MANSION + "chapel/skull");
	     skull->add_prop("_skull_finder", TP->query_name());
	     skull->move(TO);
         }
      }
      NOOFTOOLS--;
      if (stringp(items[j])) {
          item = clone_object(MANSION + "grd/" + items[j]);
          item->move(TO);
          return "Hidden beneath some vines you find a " + item->short() +
		". You see something glint beneath some refuse, maybe " +
		"there is something more here?\n";
      } else if (intp(items[j])) {
          nsc = items[j];
          MONEY_MAKE_SC(1+random(nsc))->move(TO);
          return "Hidden under some refuse you find some money.\n";
      }
  }
  return "It looks pretty empty here.\n";
}

string
do_hitw()
{
    object vine;

    if (NOOFPLANTS > 0) {
        seteuid(getuid(TO));
        vine = clone_object(MANSION + "grd/tangler");
        vine->move_living("M", TO);
        write("As you hack your way through the vines, one strangling "+ 
              "vine animates and attacks you.\n");
        vine->attack_object(TP);
        say("One of the vines on the ground suddenly comes to life and "+
            "attacks "+QCNAME(TP)+".\n");
        NOOFPLANTS--;
    } else if (BIGMAMA > 0) {
         seteuid(getuid(TO));
         vine = clone_object(MANSION + "grd/roper");
         vine->move_living("M", TO);
	 tell_room(TO, "The earth erupts as a huge shape rises out " +
	               "of the ground.\n");
         vine->attack_object(TP);
         BIGMAMA--;
    } else {
         write("You cut some of the vines to pieces.\n");
         say(QCTNAME(TP) + " cuts some vines to pieces.\n");
    }
    return "";
}

void
do_entangle()
{
    int i, j;
    object ob;
    object *victims, victim;
    object *enemies;

    ob = present("vine");
    if (ob) {
        enemies = ob->query_enemy(-1);
	j=0;
	for (i=0; i<sizeof(enemies); i++) {
	    if (environment(enemies[i]) == environment(ob)) j++;
	}
        if (j == 0) {
           NOOFPLANTS++;
           tell_room(TO, "The strangling vine becomes quiscent again.\n");
           ob->remove_object();
	}
    }
    ob = present("koekkenmoddig");
    if (ob) {
        enemies = ob->query_enemy(-1);
	j=0;
	for (i=0; i<sizeof(enemies); i++) {
	    if (environment(enemies[i]) == environment(ob)) j++;
	}
        if (j == 0) {
           BIGMAMA++;
           tell_room(TO, "The strangling vine becomes quiscent again.\n");
           ob->remove_object();
	}
    }
    
    if (NOOFPLANTS < 1 && BIGMAMA < 1) {
        set_alarm(60.0, -1.0, "do_entangle");
        return;
    }

    victims = all_inventory(TO);
    for (i=0; i<sizeof(victims); i++) {
        victim = victims[i];
        if (!living(victim)) continue;
        if (MASTER_OB(victim) == MANSION + "grd/tangler") continue;
        if (MASTER_OB(victim) == MANSION + "grd/roper") continue;
         
        if (victim->query_skill(SS_AWARENESS) > random(20) + 5) {
            victim->catch_msg("You notice that some of the vines are gently " +
                  "wrapping themselves around your legs and start to " +
                  "suck blood from you.\n");      
	}
        ob = present("wrappernote", victim);
        if (ob) {
            victim->reduce_hit_point(victim->query_max_hp()/22);
            j = ob->query_value() + 3*(NOOFPLANTS + BIGMAMA);
            ob->add_prop(OBJ_I_VALUE, j);
            if (victim->query_hp() <= 0) victim->do_die(TO);
        } else {     
            seteuid(getuid(TO));
            clone_object("/d/Terel/janus/other/wrappernote")->move(victim);
        }
    }
    set_alarm(33.0, -1.0, "do_entangle");
}   
   
int
gogo()
{
    object ob3;
    ob3 = present("wrappernote", TP);
    if (ob3) {
        PLANTSTR = ob3->query_value();
    } else {
        PLANTSTR = 3;
    }
    if (random(TP->query_stat(SS_STR)) < random((BIGMAMA+NOOFPLANTS)*PLANTSTR)){
        write("The strangling vines has wrapped themselves around your " +
              "legs. Unless you can break free, or cut yourself free you "+
              "will become fertilizer for the plants.\n");
        say(QCTNAME(TP)+" tries to leave but the strangling vines has "+
               TP->query_objective()+" securely wrapped up.\n");
        TP->add_fatigue(-5);
	return 1;
     } else {
        if (ob3) ob3->remove_object();
        write("You manage to break free from the strangler vines and "+
                 "leave.\n");
    }   
    return 0;
}

int
gogoN()
{
    object ob3;
    
    ob3 = present("wrappernote", TP);
    if (ob3) {
        PLANTSTR= ob3->query_value();
    } else {
        PLANTSTR=3;
    }
    if (BIGMAMA >= 1 || present("koekkenmoddig")) {
        write("The way north is blocked by a living wall of vines. You "+
                 "will have to cut a path through the vines to go north.\n");
        say(QCTNAME(TP)+" tries to leave north but the way is blocked " +
                           "by the vines.\n");
        TP->add_fatigue(-5);
        return 1;
    }
    if (random(TP->query_stat(SS_STR)) < random((BIGMAMA+NOOFPLANTS)*PLANTSTR)) {
        write("The strangling vines has wrapped themselves around your " +
              "legs. Unless you can break free, or cut yourself free you "+
              "will become fertilizer for the plants.\n");
        say(QCTNAME(TP)+" tries to leave. But the strangling vines has "+
               TP->query_objective()+" sequrely wrapped up.\n");
        TP->add_fatigue(-5);
	return 1;
    } else {
        if (ob3) ob3->remove_object();
        write("You manage to break free from the strangler vines and "+
                 "leave.\n");
    }   
    return 0;
}

mixed *
setup_search()
{
    return DEF_ITEMS;
}

void
create_ogrd_room()
{
}
