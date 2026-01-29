/* cloak.c created by Shiva@Genesis
 * This is the "guild object" for the vampire guild
 */

#pragma save_binary

#include "../guild.h"

inherit "/std/armour";
inherit "/cmd/std/command_driver";
inherit VAMP_LIB_DIR + "help";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

#define TPPOS this_player()->query_possessive()
#define TPPRO this_player()->query_pronoun()
#define TPOBJ this_player()->query_objective()

static mapping emote_map = ([]);
static int hood_up = 0;

mixed no_drop();
string emotes_help();
void add_emote(string cmd, string fun);

void create_armour()
{
    remove_name("armour");
    set_adj("jet-black");
    set_name( ({ "cloak", GUILD_EMBLEM_ID }) );
    set_long("A finely made, heavy cloak.  A slightly dark aura surrounds " +
	  "it, as if it were absorbing a bit of the light around it.\n" +
          "@@vamp_help@@");
  
    set_default_armour(3, A_ROBE, ({ -2, -1, 3 }), TO);

    set_likely_break(0);

    add_prop(OBJ_I_VALUE,  2500);
    add_prop(OBJ_I_VOLUME,  500);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_M_NO_BUY,    1);
    add_prop(OBJ_M_NO_SELL,   1);

    add_prop(MAGIC_AM_ID_INFO, ({
        "The cloak is somehow enchanted.\n", 5,
        "The cloak is enchanted to be extremely sturdy.\n", 15,
        "It also seems to absorb small amounts of light in a very " +
        "short radius, shielding the wearer from the light.\n", 20 }));

    add_prop(OBJ_M_NO_DROP, no_drop);

    set_help_type(({ "vcloak" }));

    add_help("emotes", emotes_help);

    add_emote("vcbats", "vcbats");
    add_emote("vchood", "vchood");
    add_emote("vcwrap", "vcwrap");

    add_emote("help", "_help");     
}

string vamp_help()
{
    if (IS_MEMBER(this_player()))
    {
        return "Use \"help vcloak\" for more information.\n";
    }

    return "";
}

mixed no_drop()
{
    if (IS_MEMBER(this_player()) && 
        (this_interactive() != this_player()))
    {
        return 1;
    }

    return 0;
}
        
int wear(object ob)
{
    this_player()->add_sunlight_resistance(SUNLIGHT_DAMAGE(1));
    return 0;
}

int remove(object ob)
{
    this_player()->add_sunlight_resistance(-SUNLIGHT_DAMAGE(1));
    hood_up = 0;
    return 0;
}

void config_cloak(string *adjs)
{
    if (!sizeof(adjs))
    {
        return;
    }

    remove_adj(query_adjs());
    add_adj(adjs);
}

string query_auto_load()
{
    if (IS_MEMBER(environment()))
    {
        return MASTER + ":" + implode(query_adjs() - ({ "worn" }), ",");
    }

    return 0;
}

void init_arg(string arg)
{
    config_cloak(explode(arg, ",") - ({ "" }));
}

string 
query_recover()
{
    return 0;
}

varargs int
got_hit(int hid, int ph, object att, int dt, int dam)
{
    // This does not call ::got_hit() intentionally
    return 0;
}

void
add_emote(string cmd, string fun)
{
    emote_map[cmd] = fun;
}

string *
parse_adverb_with_space(string str, string def_adv, int trail)
{
    string *adv = ::parse_adverb_with_space(str, def_adv, trail);

    if (adv[1] == " ")
    {
	adv[1] = "";
    }

    return adv;
}

varargs void
my_target(string str, object *oblist, string adverb = "")
{
    int index = -1;
    int size;
    object *npcs;

    npcs = oblist - FILTER_PLAYERS(oblist);
    if (sizeof(npcs))
    {
	npcs->emote_hook(query_verb(), this_player(), adverb, oblist);
	oblist -= npcs;
    }

    oblist->catch_msg(str + "\n");
}

varargs void
my_all2actbb(string str, object *oblist, string str1, string adverb = "")
{
    object *livings;
    object *npcs;

    /* This filter will also reject non-livings because non-livings cannot
     * see in the room.
     */
    livings =
        FILTER_CAN_SEE_IN_ROOM(all_inventory(environment(this_player())) -
        oblist - ({ this_player() }) );
    npcs = livings - FILTER_PLAYERS(livings);
    if (sizeof(npcs))
    {
	npcs->emote_hook_onlooker(query_verb(), this_player(), adverb, oblist);
    }

    /* Only bother if there are players left in the room. */
    livings -= npcs;
    if (sizeof(livings))
    {
	livings->catch_msg(str + " " +
			   desc_many(oblist) +
			   (strlen(str1) ? (str1 + "\n") : ".\n"));
    }
}

string
emotes_help()
{
    string *funs = filter(m_values(emote_map),
        &operator(!=)('_') @ &operator([])(, 0));

    map(sort_array(funs), &call_other(this_object(), , "?"));
    return "";
}

int
vcbats(string str)
{
    object *oblist;
    string extra1, extra2;

    if (str == "?")
    {
        write("Vcbats <target>\n");
        return 1;
    }

    if (!query_worn())
    {
        notify_fail("You aren't wearing your " + short() + ".\n");
        return 0;
    }

    notify_fail(capitalize(query_verb()) + " whom?\n");

    if (!strlen(str))
    {
        return 0;
    }

    if (sizeof(oblist = parse_this(str, "[at] [the] %l")) != 1)
    {
        return 0;
    }

    if (IS_MEMBER(oblist[0]) || oblist[0]->query_wiz_level())
    {
        extra1 = "Suddenly a cloud of illusionary bats flies from the folds.";
        extra2 = "";
    }
    else
    {
        extra1 = "Suddenly a cloud of bats streams out from the folds, " +
                 "coming straight at you!\n" +
                 "You close your eyes instinctively, and when you open " +
                 "them again, the bats are gone.";
        extra2 = "\nA look of panic passes over " + 
                 QTNAME(oblist[0]) + ".";
    }

    actor("You pull back your " + short() + " and concentrate on", oblist,
        ", projecting the image of a cloud of bats to " + oblist[0]->query_possessive() + " mind.");
    targetbb(" pulls back " + TPPOS + " " + short() + ".  " + extra1, oblist);
    all2actbb(" turns toward", oblist, " and pulls back " + TPPOS + " " +
        short() + "." + extra2);

    return 1;
}

int
vchood(string str)
{
    if (str == "?")
    {
        write("Vchood up/down\n");
        return 1;
    }

    if (!query_worn())
    {
        notify_fail("You aren't wearing your " + short() + ".\n");
        return 0;
    }

    if ((str == "up") || (str == "on"))
    {
        if (hood_up)
	{
            write("Your hood is already up.\n");
            return 1;
	}

        hood_up = 1;
        write("You pull up the hood of your " + short() + ".\n");
        allbb(" pulls up the hood of " + TPPOS + " " + short() +
            ", concealing " + TPPOS + " face in shadow.");

        return 1;
    }

    if ((str == "down") || (str == "off"))
    {
        if (!hood_up)
	{
            write("Your hood is not up.\n");
            return 1;
	}
            
        hood_up = 0;
        write("You pull down the hood of your " + short() + ".\n");
        allbb("'s face emerges from the shadow of " + TPPOS + " " +
            short() + " as " + TPPRO + " pulls down its hood.");
        
        return 1;
    }

    notify_fail(capitalize(query_verb()) + " up or down?\n");
    return 0;
}

int
vcwrap(string str)
{
    object *oblist;

    if (str == "?")
    {
        write("Vcwrap [<target>]\n");
        return 1;
    }

    if (!query_worn())
    {
        notify_fail("You aren't wearing your " + short() + ".\n");
        return 0;
    }

    if (strlen(str))
    {
        if (!sizeof(oblist = parse_this(str, "[the] %l")))
	{
            notify_fail(capitalize(query_verb()) + " whom?\n");
            return 0;
	}

        if (sizeof(oblist) > 1)
	{
            write("You cannot get your cloak around that many!\n");
            return 1;
	}

        write("With a flamboyant sweep of your arms, you wrap your " +
            short() + " around " + oblist[0]->query_the_name(this_player()) +
            ".\n");
        my_all2actbb(" With a flamboyant sweep of " + TPPOS + " arms, " + QTNAME(this_player()) +
            " wraps " + TPPOS + " " + short() + " around", oblist, ".");
        my_target("With a flamboyant sweep of " + TPPOS + " arms, " +
            this_player()->query_the_name(oblist[0]) + " wraps " + TPPOS +
            " " + short() + " around you.", oblist);
        return 1;
    }

    write("With a flamboyant sweep of your arms, you wrap your " +
        short() + " around you.\n");
    allbb(" wraps " + TPPOS + " " + short() + " around " + TPOBJ +
        "self with a flamboyant sweep of " + TPPOS + " arms.");
    return 1;
}

void
init()
{
    string *cmds;
    int i;

    ::init();

    if ((this_player() != environment()) ||
        !IS_MEMBER(this_player()))
    {
        return 0;
    }

    cmds = m_indices(emote_map);
    for (i = 0; i < sizeof(cmds); i++)
    {
        add_action(mkfunction(emote_map[cmds[i]], this_object()), cmds[i]);
    }
}

/* Too many armour breaking routines fail to check for likely_break == 0 */
varargs void
remove_broken(int silen)
{
}
