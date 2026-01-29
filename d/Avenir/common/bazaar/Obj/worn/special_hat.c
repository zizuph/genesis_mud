// file name:    ~Avenir/common/bazaar/Obj/worn/special_hat
// creator(s):    Grace  Nov  1995
// last update:   Cirion Feb  1996    
//                 -added emotes to the hat, took away
//                   weight/volume penalties     
//                Most of the emotes just masks of, and similiar
//                   to, /cmd/std/soul_cmd
// purpose:       used for hats made in the hatshop tent
// note:                   
// bug(s):                 
// to-do:                                           

inherit "/d/Avenir/inherit/cloth_arm";
inherit "/lib/commands";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <adverbs.h>
#include <cmdparse.h>
#include <const.h>
#include <filter_funs.h>
#include <language.h>
#include <living_desc.h>
#include <macros.h>
#include <ss_types.h>
 
#define SOULDESC(x)       (this_player()->add_prop(LIVE_S_SOULEXTRA, (x)))
#define HIS                this_player()->query_possessive()

string adj1, adj2, adj3, type;

void set_adj1(string str)
{
  adj1 = str;
}

void set_adj2(string str)
{
  adj2 = str;
}

void set_adj3(string str)
{
  adj3 = str;
}

void set_type(string str)
{
  type = str;
}

void initialize_hat()
{
  if(!adj1) adj1 = "faded";
  if(!adj2) adj2 = "old";
  if(!adj3) adj3 = "grey";
  if(!type) type = "hat";

  set_short(""+adj1+" "+adj2+" "+adj3+" "+type+"");

  set_long("This is a fine "+type+". The quality of the craftsmanship "+
           "is consistent with what one would expect of a hat made "+
           "by Heboba of Sybarus.\nThere is a small green tag "+
           "sewn to the inside of it.\n");

  add_item(({"tag"}), "The tag reads: "
           +"Hats are a joy for all, \n"
           +"and they affect the way we live.\n"
           +"Don't forget to be polite\n"
           +"and tip your hat to "
           +"strangers.\n");

  set_name(type);
  set_adj(({adj1, adj2, adj3}));
  return;
}

void create_armour()
{
  initialize_hat();

  add_name("hat");
  add_name("_heboba_hat_from_avenir");
  add_pname(({"clothes", "clothing"}));
  add_adj(({"custom", "sybarun"}));

  set_ac(2);     
  set_am(({-1,-1,2})); // Better by a tiny bit against clubs, etc.

  set_at(A_HEAD); 
     
  add_prop(OBJ_I_WEIGHT, 100); 
  add_prop(OBJ_I_VOLUME, 100); 
}

string query_recover()
{
  string rec;
  rec = MASTER + ":";

  rec += "#type#" + type;
  rec += "#adj1#" + adj1;
  rec += "#adj2#" + adj2;
  rec += "#adj3#" + adj3;

  rec += query_arm_recover();
  return rec;
}

void init_recover(string arg)
{
  string dummy;
  int i_check;

  sscanf(arg, "%s#type#%s#%s", dummy, type, dummy);
  sscanf(arg, "%s#adj1#%s#%s", dummy, adj1, dummy);
  sscanf(arg, "%s#adj2#%s#%s", dummy, adj2, dummy);
  sscanf(arg, "%s#adj3#%s#%s", dummy, adj3, dummy);

  init_arm_recover(arg);

  initialize_hat();

  return;
}

/*
 * string hat() gives back a description of the hat
 * using only one of its adjectives, so that you
 * don't get ugly too-long descriptions. Picks only from
 * the first 3 adjectives.
 */
string hat()
{
  string *adj = query_adjs();

  adj -= ({"worn"});

  if(sizeof(adj) < 3) return " " + adj[0] + " " + query_name();

  return " " + adj[random(3)]
             + " " + query_name();
}

/*
 * Add/mask emotions to make them more fun!
 */
init()
{
  ::init();

  add_action("read_tag", "read");
  add_action("bat", "bat");
  add_action("tip", "tip");
  add_action("cheer", "bow");
  add_action("bow", "bow");
  add_action("bounce", "bounce");
  add_action("cheer","cheer");
  add_action("cower","cower");
  add_action("curtsey","curtsey");
  add_action("smile","smile");
}

int read_tag(string str)
{
  if(!str || str == "") return 0;

  notify_fail("Read what?\n");

  if(str == "tag" || str == "the tag")
    {
      write("The tag reads: "
           +"Hats are a joy for all, \n"
           +"and they affect the way we live.\n"
           +"Don't forget to be polite\n"
           +"and tip your hat to "
           +"strangers.\n");
       return 1;
     }
  return 0;
}

/*
 * Most of these emotions simply copied
 * from the standard emotion soul and
 * modified slightly.
 */
int bat(string str)
{
    object *oblist;
    string *how;

    if(!query_worn()) return 0;

    how = parse_adverb_with_space(str, "coyly", 0);
 
    if (!strlen(how[0]))
    {
        write("You bat your eyelashes" + how[1] + ", peering "
             +"out from under your"+hat()+".\n");
        allbb(" bats " + HIS +
            " eyelashes" + how[1] + ", peering out from under"
            + HIS + hat()+".");
        return 1;
    }
 
    oblist = parse_this(how[0], "[eyelashes] [at] [the] %l");
 
    if (!sizeof(oblist))
    {
        notify_fail("Bat your eyelashes [how] at whom?\n");
        return 0;
    }
 
    targetbb(" bats " + this_player()->query_possessive() +
        " eyelashes" + how[1] + " at you, peering out from "+
        "under "+ this_player()->query_possessive() +
        hat()+".", oblist);
    actor("You bat your eyelashes" + how[1] + " at", oblist, ", peering "+
          "out from under your"+hat()+"."); 
    all2actbb(" bats " + this_player()->query_possessive() +
        " eyelashes" + how[1] + " at", oblist, ", peering out from "+
        "under "+ this_player()->query_possessive() +hat()+".");
    return 1;
}

int
bounce(string str)
{
    str = check_adverb_with_space(str, "joyfully");
 
    if(!query_worn()) return 0;

    if (str == NO_ADVERB_WITH_SPACE)
    {
        notify_fail("Bounce how?\n");
        return 0;
    }
 
    write("You bounce around" + str + ".\n"
       +"Your"+hat()+" nearly fell off!\n");
    all(" bounces around" + str + ", almost making "+HIS+hat()+
        " fall off.");
    return 1;
}
 
int
bow(string str)
{
    object *oblist;
    string *how;
 
    if(!query_worn()) return 0;

    how = parse_adverb_with_space(str, "charmingly", 0);
 
    if (!strlen(how[0]))
    {
        write("You bow" + how[1] + ", removing your"+hat()+
              " and twirling it with a flourish.\n");
        allbb(" bows" + how[1] + ", removing "+HIS+hat()+
              " and twirling it with a flourish.");
        return 1;
    }
 
    oblist = parse_this(how[0], "[to] / [before] [the] %l");
 
    if (!sizeof(oblist))
    {
        notify_fail("Bow [how] to whom?\n");
        return 0;
    }
 
    targetbb(" bows" + how[1] + " before you, removing "+HIS+hat()+
              " and twirling it with a flourish.", oblist);
    actor("You bow" + how[1] + " to", oblist, ", removing your"+hat()+
              " and twirling it with a flourish.");
    all2actbb(" bows" + how[1] + " to", oblist, ", removing "+HIS+hat()+
              " and twirling it with a flourish.");
    return 1;
}
 
int
cheer(string str)
{
    object *oblist;
    string *how;
 
    if(!query_worn()) return 0;

    how = parse_adverb_with_space(str, "wildly", 0);
 
    if (!strlen(how[0]))
    {
        write("You cheer" + how[1] + ", waving your"+hat()+
           " around in the air.\n");
        all(" cheers" + how[1] + ", waving "+HIS+hat()+
           " around in the air.");
        SOULDESC("cheering" + how[1] + " and waving a"+hat());
        return 1;
    }
 
    oblist = parse_this(how[0], "[at] [the] %l");
 
    if (!sizeof(oblist))
    {
        notify_fail("Cheer [how] at whom?\n");
        return 0;
    }
 
    SOULDESC("cheering" + how[1] + " and waving a" + hat());
    target(" cheers" + how[1] + " at you, waving "+HIS+hat()+
           " around in the air.", oblist);
    actor("You cheer" + how[1] + " at", oblist,",waving your"+hat()+
           " around in the air");
    all2act(" cheers" + how[1] + " at", oblist,",waving "+HIS+hat()+
           " around in the air");
    return 1;
}


int
cower(string str)
{
    if(!query_worn()) return 0;

    if (strlen(str))
    {
        notify_fail("Cower what?\n");
        return 0;
    }
 
    write("You try to cower beneath your"+hat()+".\n");
    allbb(" tries to cower beneath "+HIS+hat()+".");
    return 1;
}
 
int
curtsey(string str)
{
    object *oblist;
    string *how;
 
    if(!query_worn()) return 0;

    how = parse_adverb_with_space(str, "briefly", 0);
 
    if (!strlen(how[0]))
    {
        write("You curtsey" + how[1] + ", raising your"+hat()+
              " as you do so.\n");
        all(" curtseys" + how[1] + ", raising "+HIS+hat()+
              " as "+this_player()->query_pronoun()+" does so.");
        return 1;
    }
 
    oblist = parse_this(how[0], "[to] / [before] [the] %l");
 
    if (!sizeof(oblist))
    {
        notify_fail("Curtsey [how] to whom?\n");
        return 0;
    }
 
    targetbb(" curtseys" + how[1] + " to you, raising "+HIS+hat()+
              " as "+this_player()->query_pronoun()+" does so.", oblist);
    actor("You curtsey" + how[1] + " to", oblist, ", raising your"+hat()+
              " as you do so");
    all2actbb(" curtseys" + how[1] + " to", oblist,", raising "+HIS+hat()+
              " as "+this_player()->query_pronoun()+" does so");
    return 1;
}
 
int
smile(string str)
{
    object *oblist;
    string *how;
 
    if(!query_worn()) return 0;

    how = parse_adverb_with_space(str, "amusedly", 0);
 
    if (!strlen(how[0]))
    {
        write("You smile" + how[1] + ", your"+hat()+" falling over "
             +"one eye.\n");
        allbb(" smiles" + how[1] + ", "+HIS+hat()+" falling over "
             +"one eye.");
        SOULDESC("smiling" + how[1]);
        return 1;
    }
 
    oblist = parse_this(how[0], "[at] [the] %l");
 
    if (!sizeof(oblist))
    {
        notify_fail("Smile [how] at whom?\n");
        return 0;
    }
 
    SOULDESC("smiling" + how[1]);
    targetbb(" smiles" + how[1] + " at you, "+HIS+hat()+" falling over "
             +"one eye.", oblist);
    actor("You smile" + how[1] + " at", oblist,", your"+hat()+" falling "
             +"over one eye");
    all2actbb(" smiles" + how[1] + " at", oblist,", "+HIS+hat()+" falling over "
             +"one eye");
    return 1;
}
 
int tip(string str)
{
    object *oblist;
    string *how;

    if(!query_worn()) return 0;

    how = parse_adverb_with_space(str, "politely", 0);
 
    if (!strlen(how[0]))
    {
        write("You" + how[1] + " tip your"+hat()
             +" to everyone.\n");
        allbb(how[1]+" tips "+HIS + hat()
             +" to everyone.");
        SOULDESC("tipping a hat to everyone");
        return 1;
    }
 
    oblist = parse_this(how[0], "[my] [hat] [to] [the] %l");
 
    if (!sizeof(oblist))
    {
        notify_fail("Tip your hat [how] to whom?\n");
        return 0;
    }
 
    targetbb(how[1]+" tips " + HIS + hat()
         + " to you.", oblist);

    actor("You"+how[1]+" tip your"+hat() + " to", oblist, ".");
 
    all2actbb(how[1] + " tips " + HIS + hat() + 
        " to", oblist, ".");

    SOULDESC("tipping a"+hat());
    return 1;
}


 






 



