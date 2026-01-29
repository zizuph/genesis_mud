/*
 *
 * Modified:
 * Louie April 2006 - Set the steed object in the cavalry shadow for
 *          easy reference (namely for ksummon).
 */

#include <std.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <config.h>
#include <filter_funs.h>
#include "/d/Krynn/common/defs.h"
#include "../../guild.h"

inherit IN_BASE;
inherit (KLIB + "knight_utility");

string *adjectives = ({ "feisty", "spirited", "steady", "powerful",
  "majestic", "magnificent", "robust", "aggressive", "restless",
  "proud", "skittish", "grand", "noble", "mighty", "foul-tempered",
  "sleek", "well-trained", "large", "impressive", "vicious", "grey-tailed",
  "black-tailed", "white-tailed", "yellow-tailed", "brown-tailed",
  "black-maned", "white-maned", "yellow-maned", "brown-maned",
  "grey-maned", "loyal" });

string *colours = ({ "midnight-black", "black", "white", "ivory",
  "snow-white", "pure-white", "coal-black", "steel-grey","dapple-grey",
  "dark-grey", "light-grey", "grey", "brown", "light-brown",
  "dark-brown", "tan", "beige", "spotted", "auburn", "chestnut" });

string *taken_horses = ({ });

mapping lords = ([ ]);
mapping members = ([ ]);
mapping colour = ([ ]);
mapping crest = ([ ]);
static mapping mounts = ([ ]);

void remove_taken(string str) { taken_horses -= ({ str }); }

void
reset_vin_room()
{
}

public void
create_vin_room()
{
    set_short("Stable of Vingaard Keep");
    set_long("This is a stable, used by the Knights of Solamnia " +
      "to keep their warhorses. Several draft horses are kept " +
      "as well, for hunts, honoured guests and couriers. Orderly " +
      "stalls line the sides of the stable, and there is an open " +
      "area where undoubtedly food is kept. Troughs are placed " +
      "against the stalls. There is a sign on "+
      "the wall here. An exit leads back west to the street.\n");
    AI("straw", "The straw is all over the floor, in great heaps.\n");
    AI(({"stalls","orderly stalls"}),"The stalls line the sides of " +
      "the stable. Each stall is clean at the moment. The " +
      "stalls are large enough to comfortably keep a warhorse.\n");
    AI("stall","Each stall appears roughly the same.\n");
    AI("stable","The stable is kept compact, yet with enough room " +
      "to move about freely.\n");
    AI("floor", "The floor of the stable is covered with golden "+
      "straw, presumably for when the horses arrive.\n");
    AI("ceiling","The ceiling of the stable is fairly low, perhaps " +
      "to give the horses a sense of security.\n");
    AI("walls","The walls of the stable are a mixture of rock and " +
      "wood.\n");
    AI("wall","One wall looks the same as the rest.\n");
    AI("rock","It appears to be granite.\n");
    AI("wood","The wood is definitely pine.\n");
    AI(({"open area","area"}),"This is where food for the horses " +
      "will be placed.\n");
    AI("trough","Its filled with water for the horses to drink from.\n");
    ACI("sign", "read", "@@sign_desc");
    AI("sign", "@@sign_desc");

    add_prop("_room_i_allow_steed", 1);
    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_search(({"floor","straw"}), 1, KROBJECT + "straw_blade", -10);

    add_prop("_room_i_allow_horse", 1);
    AE(VROOM + "es5", "west", 0);
}

string sign_desc()
{
    return "Knights of Solamnia may choose their mounts here. To "+
    "receive instructions on this, Knights of Solamnia may use "+
    "the <mounthelp> feature. Knights who have already chosen "+
    "a mount may <retrieve> their mount here, and Knights who "+
    "are Lords of a Solamnian household may <outfit> their "+
    "mounts here, in the colours and crest of their family. "+
    "Additionally, if you wish for your steed to be "+
    "cared for and fed, you may <return> it to the stables.\n";
}

int mounthelp(string str)
{
    write("The following commands will help you configure your "+
      "warhorse.\n"+
      " - choose <adjective> <colour> <male/female> warhorse\n"+
      " - list <adjectives/colours>\n"+
      "Please note that Knights are meant to stay with their "+
      "mounts, not flippantly swap from horse to horse. Knights "+
      "who show no respect for this tradition may very well "+
      "find themselves without a mount at all. Think carefully "+
      "before making your decision.\n");
    return 1;
}

void
init()
{
    add_action("mounthelp", "mounthelp");
    add_action("choose_horse", "choose");
    add_action("list_stuff", "list");
    add_action("outfit_horse", "outfit");
    add_action("retrieve_horse", "retrieve");
    add_action("return_horse", "return");

    ::init();
}

int return_horse(string str)
{
    object steed;
    int i;

    setuid();
    seteuid(getuid());
    steed = MOUNT_MANAGER->query_solamnian_steed(TP);

    if (!steed || environment(steed) != environment(TP))
    {
        return 0;
    }

    taken_horses -= ({ TP->query_name() });

    // Remove all the riders
    steed->dismount_all();
    steed->remove_object();

    write("You return your mount to be cared for and fed.\n");

    say(QCTNAME(TP)+" returns "+POSSESSIVE(TP)+" mount, to be "+
        "cared for and fed.\n");
    return 1;
}

int retrieve_horse(string str)
{
    object ob, me = TP, steed;

    NF("Retrieve what?\n");
    if (!str || str != "horse" && str != "warhorse")
    {
        return 0;
    }

    setuid();
    seteuid(getuid());
    steed = MOUNT_MANAGER->retrieve_solamnian_steed(me);
    if (!steed)
    {
        // Notify fail messages given in retrieve_solamnian_steed
        return 0;
    }
    
    me->catch_tell("You motion to a nearby squire to retrieve your mount. "+
                   "The squire returns shortly, leading your mount, and hands "+
                   "you the reins.\n");
    tell_room(E(me), QCTNAME(me)+" motions to a squire, who then leaves into "+
             "one of the stalls. The squire returns shortly leading a warhorse"+
             ", and hands the reigns to "+QTNAME(me)+".\n", me);
    return 1;
}

int outfit_horse(string str)
{
    object *all, steed;
    int i;

    restore_object(CREST);
    if (member_array(TP->query_name(), m_values(lords)) == -1)
    {
        return 0;
    }

    all = FILTER_LIVE(all_inventory(TO));
    all -= ({ TP });

    NF("There is no horse here for you to outfit.\n");
    if (!sizeof(all))
    {
        return 0;
    }

    for (i = 0; i < sizeof(all); i++)
    {
        if (all[i]->query_owner() == TP->query_name())
        {
            steed = all[i];
        }
    }

    NF("You have no horse here.\n");
    if (!steed)
    {
        return 0;
    }

    NF("Your "+steed->short()+" is already outfitted with barding.\n");
    if (steed->query_barding())
    {
        return 0;
    }

    steed->set_barding(colour[members[TP->query_name()]]+ " barding, "+
                      "decorated with a crest of "+crest[members[TP->query_name()]]);
    write("You outfit your "+steed->short()+" with the barding "+
          "of House "+members[TP->query_name()]+".\n");
 
   say(QCTNAME(TP)+" outfits "+POSSESSIVE(TP)+" "+steed->short()+
       " with the barding of House "+members[TP->query_name()]+
       ".\n");
    return 1;
}

int list_stuff(string str)
{
    int i = 1;

    if (str == "adjectives")
    {
        TP->catch_tell("\n"+
                       "                   -=> Adjectives <=-\n\n"+
                       "General: feisty, spirited, steady, powerful, majestic, magnificent\n"+
                       "         robust, aggressive, restless, proud, skittish, grand, \n"+
                       "         noble, mighty, foul-tempered, sleek, large, impressive,\n"+
                       "         vicious, loyal, brave, well-trained.\n\n"+
                       "Tail and Mane Colours: grey-tailed, white-tailed, black-tailed,\n"+
                       "         yellow-tailed, brown-tailed, grey-maned, white-maned,\n"+
                       "         black-maned, yellow-maned, brown-maned.\n");
        return 1;
    }

    if (str == "colours")
    {
        TP->catch_tell("\n"+
                       "                   -=> Colours <=-\n\n"+
                       "Colours: midnight-black, black, coal-black, white, ivory, snow-white,\n"+
                       "         pure-white, steel-grey, dark-grey, light-grey, grey, brown,\n"+
                       "         light-brown, dark-brown, tan, beige, spotted, auburn,\n"+
                       "         chestnut, dapple-grey.\n");
        return 1;
    }

    write("List what? Adjectives or Colours?\n");
    return 1;
}


int choose_horse(string str)
{
    string adj1, adj2, gen;

    NF("Choose what?\n");
    if (!str)
    {
        return 0;
    }
    sscanf(str, "%s %s %s", adj1, adj2, gen);

    if (TP->query_knight_level() < 3)
    {
        return 0;
    }

    NF("The format is: choose 'adjective' 'colour' 'male/female' \n");
    if (!adj1 || !adj2 || !gen)
    {
        return 0;
    }
    NF("The adjective in your selection was not found, please try again using "+
      "the syntax: 'choose adjective colour male/female'.\n");

    if (member_array(adj1, adjectives) == -1)
    {
        return 0;
    }

    NF("The colour in your selection was not found, please try again using "+
       "the syntax: 'choose adjective colour male/female'.\n");
 
    if (member_array(adj2, colours) == -1 )
    {
        return 0;
    }
    NF("There are only male and females as gender, please try again "+
      "the syntax: 'choose adjective colour male/female'.\n");
  
    if (gen != "male" && gen != "female")
    {
        return 0;
    }

    mounts = restore_map(MOUNT_FILE);
    mounts[TP->query_name()] = ({ adj1, adj2, gen });
    save_map(mounts, MOUNT_FILE);

    write("You have chosen a "+adj1+" "+adj2+" "+gen+" warhorse as "+
          "your mount. You may 'retrieve' your warhorse here from now "+
          "on. To return your horse, simply have a Squire bring it "+
          "here from the courtyard when you arrive by 'return'ing it.\n");
    return 1;
}

