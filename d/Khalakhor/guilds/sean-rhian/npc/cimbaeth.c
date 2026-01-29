/* Cimbaeth - manach in the kitchen of MacDunn Kirk; makes saltpeter
**            for players
**
**
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           1/5/98     Created
** Tapakah        08/2021    Refactored
*/
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "../objects/powder.h"
#include "../macdunnkirk/room/kkitchen.h"
#include "defs.h"

inherit  SR_NPC+"monkbase";

#define  TR (environment(this_object()))
#define  MAX_ING     3
#define  FLASK_NDX   0
#define  BLUBBER_NDX 1
string   pname="";
 
object*  ing=allocate(MAX_ING);
 
#define  VEST (({"robe","cincture","tonsure","scapular"}))
 
void
arm_me ()
{
  vest_me(VEST);
}
 
void
create_khalakhor_human ()
{
  ::create_khalakhor_human();
  add_name(({"monk","manach","cook"}));
  set_adj(({"plump","balding"}));
  set_long("He is a plump balding human, his food-stained habit "+
           "identifying him as a cook in the priory.\n");
  set_manach_stats((40+random(40)));
  set_size_descs("short","plump");
  add_prop(NPC_M_NO_ACCEPT_GIVE," says: I may not accept gifts from you.\n");
 
  set_act_time(30);
  add_act("emote sniffs of the stewpot hanging in the hearth.");
  add_act("emote wipes his food-stained hands on his scapular.");
  add_act("emote shines one of the pots on the wall with his scapular.");
  add_act("emote wipes the table with a damp rag.");
  add_act("emote stokes the fire in the hearth with an iron rod.");
  add_act("say The brathair's'll be expectin' thar dinner soon.");
  add_act("say Makin' the saltpeter tis a dirty chore.");
  add_act("say That stew could use a bit more spice.");
  add_act("emote stirs the stewpot with a long spoon.");
  add_act("emote dips his finger in the stewpot and takes a sniff.");
  set_cact_time(60);
  add_cact("say May ye be cast into hell demon!");
  add_cact("say A curse upon ye and your kin!");
  add_cact("say Ye won't escape alive, devil!");
 
 
  add_ask(({"oil","for oil","about oil"}),
          "say I ha' no oil for ye, but I can make it.",1);
  add_ask(({"blubber","whale blubber"}),
          "say Aye, bring me some whale blubber and an empty glass oil "+
          "flask an' I'll make ye some oil.",1);
  add_ask(({"whale","about whale","where whale"}),
          "say Well the whales live in the sea! Perhaps you "+
          "should go for swim and you'll meet one, but I'm not sure he'll be "+
          "willin' to give ye ought!",1);
  add_ask(({"for flask","about flask","flask"}),
          "say Ye'll need a special flask for the whale oil. "+
          "Ask brathair Garlon for one.",1);
  add_ask(({"Garlon","garlon","brathair garlon","brathair Garlon"}),
          "say Brathair Garlon is the kirk sacristan. He takes care of the "+
          "vessels and vestments and such.",1);
  add_ask(({"to make oil","to make me oil","to make oil for me",
            "make oil","make me oil","make oil for me"}),
          "@@ask_make_oil",0);
 
  add_ask(({"saltpeter","about saltpeter"}),
          "say Ah, a useful thing it is. I can tell you what it is "+
          "and how to get it.",1);
  add_ask(({"what saltpeter","what is saltpeter","what saltpeter is"}),
          "say Tis a powder which can burn, even explode. We "+
          "use it to make incense burn.",1);
  add_ask(({"get saltpeter","how get saltpeter","how to get saltpeter"}),
          "say Well the best source tis the droppings of "+
          "seagulls. If ye has some droppings, ask me to make saltpeter for "+
          "ye and I just might.",1);
  add_ask(({"to make saltpeter","make saltpeter","make saltpeter for me",
            "to make saltpeter for me"}),"@@ask_make_saltpeter",0);
 
  add_ask(({"gulls","gull","seagulls","gulls"}),
          "say The gulls hang about the beaches and piers near the "+
          "ocean, lookin' to be fed by someone if'n they "+
          "can't scavenge anythin'.\n",1);
  add_ask(({"droppings","gull droppings","seagull droppings",
            "bird droppings","about droppings"}),
          "say Gull droppings 'er a good source of saltpeter. "+
          "The gulls usually drop after they eat.",1);
 
  add_ask(({"tour","quest","job","task","for tour","for quest","for job",
            "for task"}),
          "say See abbot Semion 'bout that.",1);
  add_ask(({"for incense","incense","about incense"}),
          "say It has a heavenly aroma when burnt. "+
          "See the abbot or brathair Finegas 'bout it.",1);
 
  add_ask(({"semion","Semion","abbot Semion","Abbot Semion","abbot"}),
          "say Semion be the abbot of our kirk. He's usually in his "+
          "office.",1);
  add_ask(({"food","for food","for stew"}),
          "say Sorry but I have nothin' for ye to eat now.", 1);
  add_ask(({"stew","about stew","spice","about spice"}),
          "say Aye, the stew could use some spice, but the brathairs "+
          "like it bland.",1);
  add_ask(({"pot","for pot","about pot"}),"@@ask_pot",1);
  add_ask(({"help","for help","to help"}),
          "say How can I help ye? Can I make ye some "+
          "saltpeter?", 1);
  add_ask(({"ingredients","for ingredients","about ingredients"}),
          "say Ingredients? Ingredients for what?",1);
  add_ask(({"ingredients for saltpeter","for ingredients for saltpeter"}),
          "say Ah, well the best source is gull droppings.",1);
  add_ask(({"ingredients for incense","for ingredients for incense"}),
          "say See brathair Finegas 'bout that.",1);
  add_ask(({"ingredients for oil","for ingredients for oil"}),
          "say Well, ye can make it from a slab of whale blubber.",1);
  seteuid(getuid());
}
 
string
ask_pot ()
{
  return environment(TO)->query_step()
    ? "say It's in the fireplace o'er the flames, "+laddie(TP)+"."
    : "say I do'no have a pot I can give ye, "+laddie(TP)+".";
}
 
void
give_product (int pnum)
{
  object prod;
  string prshort;
  switch (pnum) {
  case PROD_SPETER:
    prod = clone_object(SR_OBJ+"powder");
    prod->set_powder(POWDER_SALTPETER);
    prod->move(TO);
    break;
  case PROD_WOIL:
    prod=present(SR_FLASK,TO);
    if (!objectp(prod))
      {
        command("ack");
        command("shout Someone has stolen me flask!");
        command("say Sorry "+laddie(TP)+", I ha' no oil for ye.");
        return;
      }
    prod->set_amt(5);    // 5 is full
    prod->set_oilid(1);  // plain unblessed oil
    break;
  default:
    command("say I'm a bit confused "+laddie(TP)+". Think I gotta bug.");
    command("say Better tell someone "+laddie(TP)+", I'm hurtin' bad.");
    return;
  }
  prshort=lower_case(prod->query_name());
  command("say Thar ye are, "+capitalize(pname)+"!");
  command("give "+prshort+" to "+pname);
  command("drop "+prshort);
  pname="";
  command("emote cleans the small copper pot and puts it away.");
}
 
//
// HAS_INGREDIENTS - does the player have the correct ingredients?
//
int
has_ingredients (int pnum)
{
  object *inv = all_inventory(TP);
  int i=0,numdrop=0;
 
  for (i=0; i<MAX_ING; i++)
    ing[i]=0; // clean out obj array
 
  switch (pnum) {
  case PROD_SPETER:
    // need three balls of droppings
    i = numdrop = 0;
    while ((i<sizeof(inv)) && (numdrop<3)) {
      if (inv[i]->id("doo")) {
        ing[numdrop]=inv[i];
        numdrop++;
      }
      i++;
    }
    if (numdrop<3) {
      command("say Ye'll need three balls of gull droppings, "+
              laddie(TP)+".");
      command("say I can 'naugh make it fer ye wi'out those.");
      return 0;
    }
    return 1;
 
  case PROD_WOIL:
    // need a slab of whale fat and an empty glass flask
    i=0;
    while ((i<sizeof(inv))&&
           ((!objectp(ing[BLUBBER_NDX]))||(!objectp(ing[FLASK_NDX])))) {
      if ((inv[i]->id(SR_FLASK))&&((inv[i]->query_amt())==0))
        ing[FLASK_NDX]=inv[i];
      else if (inv[i]->id(SR_WBLUBBER))
        ing[BLUBBER_NDX]=inv[i];
      i++;
    }
    if ((!objectp(ing[0])) || (!objectp(ing[1]))) {
      command("say Ye'll need an empty glass oil flask, an' a slab "+
              "of whale blubber, "+laddie(TP)+".");
      command("say I can 'naugh make it fer ye wi'out those.");
      return 0;
    }
    return 1;
  default:
    command("say I'm a bit dizzy "+laddie(TP)+". Think I gotta bug.");
    command("say Better tell someone "+laddie(TP)+", I'm hurtin' bad.");
    return 0;
  }
}
 
//
// ALLOWED - is player allowed to do have Cimbaeth make this for him?
//
int
allowed (int pnum)
{
  switch (pnum) {
  case PROD_SPETER:
    if (!(TP->query_prop(SEMIONS_BLESSING))) {
      command("say Ye'll need Abbot Semion's blessing, "+laddie(TP)+
              ".");
      command("say I can 'naugh make it fer ye without that.");
      return 0;
    }
    return 1;
  case PROD_WOIL:
    //add code later if want to restrict to guild members only
    return 1;
  default:
    command("say I'm a bit dizzy "+laddie(TP)+". Think I gotta bug.");
    command("say Better tell someone "+laddie(TP)+", I'm hurtin' bad.");
    return 0;
  }
}
 
//
// TAKE_INGREDIENTS - Cimbaeth takes the ingredients from the player
//
void
take_ingredients (int pnum)
{
  string oshort;
  int i;
  switch (pnum) {
  case PROD_SPETER: // take 3 bird doos
    for (i=0; i<3; i++)
      ing[i]->remove_object();
    TP->catch_msg(QCTNAME(TO)+" takes three balls of bird droppings "+
                  "from you.\n");
    tell_room(ENV(TO),QCTNAME(TO)+" takes three balls of bird "+
              "droppings from "+QTNAME(TP)+".\n",TP);
    break;
  case PROD_WOIL:
    oshort=(ing[BLUBBER_NDX])->query_short();
    TP->catch_msg(QCTNAME(TO)+" takes a "+oshort+" from you.\n");
    tell_room(ENV(TO),QCTNAME(TO)+" takes a "+oshort+" from "+
              QTNAME(TP)+".\n",TP);
    ing[BLUBBER_NDX]->remove_object();
 
    oshort=(ing[FLASK_NDX])->query_short();
    TP->catch_msg(QCTNAME(TO)+" takes an "+oshort+" from you.\n");
    tell_room(ENV(TO),QCTNAME(TO)+" takes an "+oshort+" from "+
              QTNAME(TP)+".\n",TP);
    ing[FLASK_NDX]->move(TO);
    break;
  default:
    command("say I'm a bit dizzy "+laddie(TP)+". Think I gotta bug.");
    command("say Better tell someone "+laddie(TP)+", I'm hurtin' bad.");
  }
}
 
//
// ASK_MAKE_PROD - player asked him to make a product
//
string
ask_make_prod (int pnum)
{
  /* he must be in the kitchen, not busy, and player have ingredients */
  if (!(TR->is_priory_kitchen())) {
    command("say Can't make it here, "+laddie(TP)+".");
    command("say Ask me later when I'm in the kitchen.");
  }
  else if (TR->query_step())
    command("say I'm busy right now "+laddie(TP)+", ask me later.");
  else if ((!has_ingredients(pnum))||(!allowed(pnum)))
    command("sigh deeply");
  else {
    command("say Aye, I'll do it for ye "+laddie(TP)+".");
    take_ingredients(pnum);
    pname=lower_case(TP->query_name());
    TR->start_process(pnum);
  }
  return "";
}

string
ask_make_saltpeter ()
{
  return ask_make_prod(PROD_SPETER);
}

string
ask_make_oil ()
{
  return (ask_make_prod(PROD_WOIL));
}
