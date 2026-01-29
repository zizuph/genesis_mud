/* /d/Shire/michel/npc/boar.c
 * The carrier of Brunhilda's missing ball
 * 11/28/95 by Dunstable
 *
 * Check added so a boar can only drop one ball. Glaurung 3-14-96
 * Added more colors to ball - Finwe September 2003
 */
 

inherit "/std/creature";

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/std/combat/unarmed";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/common/lib/goodkill.h"
#include "/d/Shire/common/defs.h"

/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  0
#define A_LPAW  1
#define A_RPAW  2
#define A_LHPAW 3
#define A_RHPAW 4

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

/* Some definitions used to mass produce these suckers ;)
 * Dunstable, Jan 30, 1995
*/

#define NAME1 "boar"
#define NAME2 "pig"
#define NAME3 "wild boar"
#define PNAME "boars"

#define ADJ1 "large"
#define ADJ2 "sharp-tusked"
#define ALIGN 55
#define WEIGH 15500
#define MOUT "ambles"
#define AMIN "ambles in."   /* Don't forget the period. :) */
#define FIGHT1 80   /* Unarmed */
#define FIGHT2 60  /* Defence */
#define RM 8   /* Random move */
#define EMOTE "emote grunts loudly."
#define ACTTIME 7
#define ACT1 "emote paws the ground with both hooves."
#define ACT2 "emote sniffs the air for danger."
#define ACT3 "emote roots around, looking for food."

static string color;
static int colorgone;
string get_color();

void
create_creature()
{

   color = get_color();
  set_name(NAME1);
  add_name(({NAME2,NAME3}));
  set_pname(PNAME);
  set_long("@@my_long");
  set_adj(({ADJ1,ADJ2}));
  set_race_name(NAME1);
  set_alignment(ALIGN-random(50));
   set_stats(({23+random(8),15+random(6),34+random(7),5+random(5),5+random(10),20+random(5)}));

  set_gender(random(2));
  set_skill(SS_UNARM_COMBAT, FIGHT1+random(10));
  set_skill(SS_DEFENCE,FIGHT2+random(10));
  set_whimpy(50 + random(50));
  set_random_move(RM);
  add_prop(CONT_I_WEIGHT,WEIGH+random(2500));
  add_prop(CONT_I_VOLUME,TO->query_prop(CONT_I_WEIGHT)*75/100);
  seq_new("do_first");
  seq_addfirst("do_first",({"@@arm_me",EMOTE}));
  set_act_time(ACTTIME);
  add_act(ACT1);
  add_act(ACT2);
  add_act(ACT3);
  colorgone = 0;

}

void
init_living()
{
    ::init_living();
    add_action("do_tickle","tickle");
    add_action("do_tickle","poke");
}

string
get_color()
{
    string *colors;
    int ran;

    ran = random(28);

// How I love my coat of many colors, it was
    colors = ({"red", "yellow", "green", "brown", "scarlet", "black", 
        "ochre", "peach", "ruby", "olive", "violet", "fawn", "lilac", 
        "gold", "chocolate", "mauve", "cream", "crimson", "silver", 
        "rose", "azure", "lemon", "russet", "grey", "purple", "white", 
        "pink", "orange", "blue"});

//   ran = random(7);
//   colors = ({"blue","green","red","yellow","white","pink","purple","black"});
    return colors[ran];
}

string
query_color()
{
   return color;
}

string
my_long()
{
   if(!colorgone)
   return "This large, sharp-tusked boar holds a small "+color+" colored "+
   "ball in its mouth.\n";
   else
   return "This large, sharp-tusked boar grunts at you warily.\n";
}

public int
do_tickle(string str)
{

   object ball;

   if((!str) && (str != "boar") && (str != "pig"))
   {
    return 0;
    }

   if (!colorgone)
   {
     ball = clone_object("/std/object");
     ball->set_short(color + " ball");
     ball->set_long("A "+color+" ball. It is round and made from scraps " +
        "of material. The dominate color of the ball is " + 
        color + ", plus other colored fabrics sewn together. " +
        "The ball is soft, and not good for much other than tossing " +
        "around and catching it.\n");
     ball->set_name("_brunhilda_ball_");
     ball->add_name(({"ball"}));
     ball->add_prop(OBJ_I_WEIGHT, 10);
     ball->add_prop(OBJ_I_VOLUME, 10);
     ball->add_prop(OBJ_I_VALUE, 1);
     ball->add_prop("_ball_color_",color);
     ball->move(environment(TO));
     TP->catch_msg("You "+query_verb()+ " the large boar.\n");
     say(QCTNAME(TP) + " "+ query_verb()+ "s the large boar.\n",TP);
     command("emote grunts happily.");
     command("emote drops something.");
     command("emote squeals and runs away.");
     TO->remove_object();
     colorgone = 1;
     return 1;
   }

   else
   {   
     TP->catch_msg("You "+query_verb()+" the large boar.\n");
     say(QCTNAME(TP) +" "+query_verb()+"s the large boar.\n",TP);
     command("emote grunts happily.");
     return 1;
   }
}


public void
do_die(object killer)
{
    object remains;

  if(!colorgone)
  {
    remains = clone_object("/std/object");
    remains->set_name("remains");
    remains->add_name("ball");
    remains->add_prop(OBJ_I_WEIGHT, 10);
    remains->add_prop(OBJ_I_VOLUME, 10);
    remains->set_adj("messy");
    remains->add_adj("shredded");
    remains->set_short("messy shredded remains");
    remains->set_long("This used to be a child's toy ball. It no longer "+
    "looks like such a thing, however.\n");
    remains->add_prop(OBJ_I_VALUE, 1);
    command("emote groans in sharp pain and anguish.");
    command("emote chews hard on a "+color+" colored ball.");
    command("emote gasps for breath, swallowing hard.");
    remains->move(TO);
  }
   ::do_die(killer);
   return;
}

void
arm_me()
{
  seteuid(getuid(TO));
  set_m_out(MOUT);
  set_m_in(AMIN);
}

/*
 * Here we add attacks and hitlocations:
 *     add_attack(int wchit, int wcpen, int damtype, int prcuse, int id)
 *     add_hitloc(int *ac, int prchit, string desc, int id)
 *
 * *ac == ({ ac-impale, ac-slash, ac-bludgeon })
 */
public void
cr_configure()
{
    add_attack(5+random(5),5+random(5),W_IMPALE,30,A_BITE);
    add_attack(5+random(5),5+random(5),W_SLASH,20,A_LPAW);
    add_attack(5+random(5),5+random(5),W_SLASH,20,A_RPAW);
    add_attack(5+random(5),5+random(5),W_SLASH,15,A_LHPAW);
    add_attack(5+random(5),5+random(5),W_SLASH,15,A_RHPAW);

    add_hitloc(({5+random(5),5+random(5),5+random(5)}),20,"head",H_HEAD);
    add_hitloc(({5+random(5),5+random(5),5+random(5)}),50,"body",H_BODY);
    add_hitloc(({5+random(5),5+random(5),5+random(5)}),30,"legs",H_LEGS);
}

/*
 * Give description of each attack. We could also redefine the entire
 * hitdescription by redefining 'cr_did_hit'
 */
public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BITE:return "snout";
    case A_LPAW:return "left hoof";
    case A_RPAW:return "right hoof";
    case A_LHPAW:return "left hind hoof";
    case A_RHPAW:return "right hind hoof";
    }
    return "mind"; /* should never occur */
}

query_combat_file()
{
  return "/std/combat/cplain";
}

