/*
 *
 * Modified:
 * Louie April 2006 - Set the steed object in the cavalry shadow for
 *          easy reference (namely for ksummon).
 */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solamn/vin/knight/guild.h"
#include <std.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <config.h>
#include <filter_funs.h>

inherit IN_BASE;

string *adjectives = ({ "feisty", "spirited", "steady", "powerful",
  "majestic", "magnificent", "robust", "aggressive", "restless",
  "proud", "skittish", "grand", "noble", "mighty", "foul-tempered",
  "sleek", "well-trained", "large", "impressive", "vicious", "grey-tailed",
  "black-tailed", "white-tailed", "yellow-tailed", "brown-tailed",
  "black-maned", "white-maned", "yellow-maned", "brown-maned",
  "grey-maned", "loyal" });

string *colours = ({ "midnight-black", "black", "white", "ivory",
  "snow-white", "pure-white", "coal-black", "steel-grey",
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
    return "Knights of Solamnia who are enlisted in the Solamnian "+
    "Cavalry may choose their mounts here or retire here. To "+
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
      "warhorse, assuming you are a member of the Solamnian "+
      "Cavalry.\n"+
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
    add_action("enlist_cavalry", "enlist");
    add_action("leave_cavalry", "retire");
    add_action("leave_cavalry", "withdraw");

    ::init();
}

int return_horse(string str)
{
    object *all, steed;
    int i;

    if (TP->query_steed()->query_owner() == TP->query_name())
    steed = TP->query_steed();
    else
    {
    all = FILTER_LIVE(all_inventory(TO));
    all -= ({ TP });

    for (i = 0; i < sizeof(all); i++)
    {
        if (all[i]->query_owner() == TP->query_name())
        steed = all[i];
    }
    }

    if (!steed)
    return 0;

    taken_horses -= ({ TP->query_name() });
    if (TP->query_steed() == steed)
    steed->do_dismount(TP, 1);

    steed->remove_object();

    write("You return your mount to be cared for and fed.\n");
    say(QCTNAME(TP)+" returns "+POSSESSIVE(TP)+" mount, to be "+
      "cared for and fed.\n");
    return 1;
}

int retrieve_horse(string str)
{
    object ob, me = TP;
    string name = TP->query_name();

    NF("Retrieve what?\n");
    if (!str || str != "horse" && str != "warhorse")
    return 0;

    if (!(ADMIN)->query_cavalry(TP->query_name()))
    return 0;
    mounts = restore_map(MOUNT_FILE);

    NF("You have no chosen mount yet, you must have a mount to "+
      "retrieve, before you may retrieve it.\n");
    if (member_array(name, m_indexes(mounts)) == -1)
    return 0;

    /*
    NF("You've already retrieved your mount, and not returned it.\n");
    if (member_array(name, taken_horses) >= 0)
        return 0;
    */

    ob = clone_object(VOBJ + "steed");
    ob->set_short(mounts[name][0]+" "+mounts[name][1]+" warhorse");
    ob->set_gender((mounts[name][2] == "male" ? 0 : 1 ));
    ob->add_adj(mounts[name][0]);
    ob->add_adj(mounts[name][1]);
    ob->set_owner(me);
    ob->move(TO);

    //Louie - Set the steed object in the cavalry shadow
    me->set_solamnian_steed(ob);

    taken_horses += ({ name });

    me->catch_tell("You motion to a nearby squire to retrieve your mount. "+
      "The squire returns shortly, leading your mount, and hands "+
      "you the reins.\n");
    tell_room(E(me), QCTNAME(me)+" motions to a squire, who then leaves into "+
      "one of the stalls. The squire returns shortly, leading a "+
      ob->short()+", and hands the reigns to "+QTNAME(me)+".\n", me);
    return 1;
}

int outfit_horse(string str)
{
    object *all, steed;
    int i;

    restore_object(CREST);
    if (member_array(TP->query_name(), m_values(lords)) == -1)
    return 0;

    all = FILTER_LIVE(all_inventory(TO));
    all -= ({ TP });

    NF("There is no horse here for you to outfit.\n");
    if (!sizeof(all))
    return 0;

    for (i = 0; i < sizeof(all); i++)
    {
    if (all[i]->query_owner() == TP->query_name())
        steed = all[i];
    }

    NF("You have no horse here.\n");
    if (!steed)
    return 0;

    NF("Your "+steed->short()+" is already outfitted with barding.\n");
    if (steed->query_barding())
    return 0;

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
      "         chestnut.\n");
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
    return 0;
    sscanf(str, "%s %s %s", adj1, adj2, gen);

    if (!MEMBER(TP) || TP->query_knight_level() < 3)
    return 0;

    NF("You are not enlisted in the Cavalry yet!\n");
    if (!(ADMIN)->query_cavalry(TP->query_name()))
    return 0;

    NF("The format is: choose 'adjective' 'colour' 'male/female' \n");
    if (!adj1 || !adj2 || !gen)
    return 0;

    NF("The adjective in your selection was not found, please try again using "+
      "the syntax: 'choose adjective colour male/female'.\n");
    if (member_array(adj1, adjectives) == -1)
      return 0;

    NF("The colour in your selection was not found, please try again using "+
      "the syntax: 'choose adjective colour male/female'.\n");
    if (member_array(adj2, colours) == -1 )
      return 0;

    NF("There are only male and females as gender, please try again "+
      "the syntax: 'choose adjective colour male/female'.\n");
    if (gen != "male" && gen != "female")
      return 0;

    mounts = restore_map(MOUNT_FILE);
    mounts[TP->query_name()] = ({ adj1, adj2, gen });
    save_map(mounts, MOUNT_FILE);

    write("You have chosen a "+adj1+" "+adj2+" "+gen+" warhorse as "+
      "your mount. You may 'retrieve' your warhorse here from now "+
      "on. To return your horse, simply have a Squire bring it "+
      "here from the courtyard when you arrive by 'return'ing it.\n");
    return 1;
}


/* Join and leave functions */
int leave_cavalry(string str)
{
    string tmp;

    NF("Retire from what? The Solamnian Cavalry.\n");
    if (!str)
    return 0;

    if (!parse_command(str, ({ }), "[from] [the] [Solamnian] [solamnian] 'cavalry' / 'Cavalry'"))
    return 0;

    NF("You are not a member of the Solamnian Cavalry.\n");
    if (!(ADMIN)->query_cavalry(TP->query_name()))
    return 0;

    (ADMIN)->remove_cavalry(TP->query_name());

    TP->remove_guild_lay();
    TP->set_guild_pref(SS_LAYMAN, 0);
    TP->clear_guild_stat(SS_LAYMAN);

    mounts = restore_map(MOUNT_FILE);
    mounts = m_delete(mounts, TP->query_name());
    save_map(mounts, MOUNT_FILE);

    write_file(KLOG + "cavalry", ctime(time()) + " "+
      TP->query_name()+" retired from the Solamnian Cavalry\n");

    write("You retire from the Solamnian Cavalry.\n");
    say(QCTNAME(TP)+" retires from the Solamnian Cavalry.\n");
    return 1;
}

int enlist_cavalry(string str)
{
    object shadow;
    string tmp;

    NF("Enlist in what? The Solamnian Cavalry?\n");
    if (!str)
    return 0;

    if (!parse_command(str, ({ }), "[in] [the] [solamnian] [Solamnian] 'cavalry' / 'Cavalry'"))
    return 0;

    NF("You are not a Knight of Solamnia.\n");
    if (!MEMBER(TP))
    return 0;

    NF("You are not ready to enlist in the Cavalry of Solamnia.\n");
    if (TP->query_knight_level() < 3)
    return 0;

    NF("You have already enlisted in the Cavalry!\n");
    if ((ADMIN)->query_cavalry(TP->query_name()))
    return 0;

    NF("You seem to have other loyalties, leaving you without the "+
      "time necessary to devote yourself to the Solamnian Cavalry.\n");
    if (TP->query_guild_name_lay())
    return 0;

    (ADMIN)->add_cavalry(TP->query_name());

    shadow = clone_object(CAVALRY_SHADOW);
    shadow->shadow_me(TP, "layman", "fighter", "Solamnian Cavalry");

    TP->clear_guild_stat(SS_LAYMAN);
    write_file(KLOG + "cavalry", ctime(time()) + " "+
      TP->query_name()+" joined the Solamnian Cavalry\n");

    write("You enlist in the Solamnian Cavalry, and are now allowed to "+
      "train with Santos in the arts of mounted combat.\n");
    say(QCTNAME(TP)+" enlists in the Solamnian Cavalry.\n");
    return 1;
}

