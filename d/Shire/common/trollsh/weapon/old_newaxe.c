/* === cmaaxe.c ==========================================================
 * ======================================== Finwe & Raven 2001 Genesis ===
 *
 * Originally called the Bloody Steel Axe from Kalad, and coded by
 * Antharanos. Was given to the Shire when Kalad was slowly phased out.
 *
 * Altered so that it uses gems to get its strength and power. When gems
 * are spent, they crumble to dust and fall out of the handle. When that
 * happens, the axe becomes unenchanted, but can be re-enchanted with the
 * introduction of a gem to the handle. The rarest gems give it the most
 * power, but the majority of gems will give it limited powers.
 *
 * -- Finwe, August 2001
 *
 * =======================================================================
 * =============================================================== *** ===
 */

#include <cmdparse.h>
#include <tasks.h>
#include <wa_types.h>
#include "/d/Genesis/gems/gem.h"
#include "/d/Shire/sys/defs.h"

inherit "/std/weapon";
inherit "/lib/keep";

/*
 * === global variables ==================================================
 * =============================================================== *** ===
 */

#define AXE_RARITY_DESC \
        ({              \
          "waning",     \
          "mediocre",   \
          "strong",     \
          "very strong",\
        })

#define AXE_POINTS_DESC \
        ({              \
          "waning",     \
          "mediocre",   \
          "strong",     \
          "very strong",\
        })

#define GEM_CONFIG                                                       \
        ([                         /* hit pen    points       drain%*/   \
            GEM_EXTREMELY_RARE   : ({ 53, 50, 1500 + random(11), 10 }),  \
            GEM_VERY_RARE        : ({ 51, 49, 1000 + random(16), 12 }),  \
            GEM_RARE             : ({ 49, 47,  900 + random(11), 15 }),  \
            GEM_SOMEWHAT_RARE    : ({ 47, 45,  800 + random( 6), 17 }),  \
            GEM_SLIGHTLY_RARE    : ({ 45, 43,  500 + random( 6), 19 }),  \
            GEM_EXTREMELY_COMMON : ({ 40, 40,  200 + random( 6), 20 }),  \
        ])

#define NORMAL_HIT  35  // without gems in handle
#define NORMAL_PEN  35
#define HEAL_TEXT  "golughosh"

static string  axe_jewel;   /* the jewel short description              */
static int     axe_points,  /* the current points of axe                */
               max_points,  /* the max points for gem rarity            */
               axe_drain;   /* the drain of axe in percents             */

/*
 * === supporting functions ==============================================
 * =============================================================== *** ===
 */

string
query_jewel_desc()
{
    string  text = "", *desc;
    int     size, n;

    if (!this_object()->query_axe_jewel())
       return " The handle is empty, leaving the "+short()+" powerless.";
    
    /* this gotto be changed along with descs, just a sceleton so far   */
    /* compositing such a desc: A strong power emanates from the strong */
    /* glowing gem set in the hilt of the...                            */

    size = sizeof(desc = AXE_POINTS_DESC);
    
    n = (size * axe_points / max_points);
    n = (n < 0 ? 0 : (n > (size - 1) ? (size - 1) : n));

    text += (LANG_ADDART(desc[n]) + " unholy power emanates from the ");

    size = sizeof(desc = AXE_RARITY_DESC);

// reveals how much power remains in the axe
//    n = (size * max_points / 1500);
    n = (size * max_points / axe_points);
    n = (n < 0 ? 0 : (n > (size - 1) ? (size - 1) : n));

    text += (desc[n] + " " + this_object()->query_axe_jewel() + " set in"+
            " the handle of " + LANG_THESHORT(this_object()));

    return (" " + capitalize(text) + ".");
}

void
destroy_axe_gem()
{
    string  gem;
    object  player = query_wielded();
    
    if (!(gem = this_object()->query_axe_jewel()))
       return;
    
    if (objectp(player) || living(player = environment(this_object())))
    {
       player->catch_tell("Suddenly the " + gem + " on " +
           LANG_THESHORT(this_object()) + " hilt turns to dust " +
           "and falls out of the axe handle!\n");
       tell_room(environment(player), "Suddenly the " + gem + " on " +
           LANG_THESHORT(this_object()) + " held by " + QTNAME(player) +
           " turns into dust and falls out of the axe handle!\n", player);
    }
    else if (environment(this_object())->query_prop(ROOM_I_IS))
    {
       tell_room(environment(this_object()),"Suddenly the " + gem +
           " on " + LANG_THESHORT(this_object()) + " hilt turns into" +
           " dust and falls out of the axe handle!\n");
    }

    this_object()->set_axe_jewel(0, 0);
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
                int phit, int dam)
{
    if (phit > 0) /* we actually hit something */
    {
       this_object()->add_axe_points(-1);

       if (this_object()->query_axe_points() <= 0)
          set_alarm(2.0, 0.0, destroy_axe_gem);
    }

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

/*
 * === definition functions ==============================================
 * =============================================================== *** ===
 */

void
set_max_points(int value)
{
    max_points = value;
}

int
query_max_points()
{
    return max_points;
}

void
set_axe_points(int value)
{
    axe_points = (value<0 ? 0 : (value>max_points ? max_points : value));
}

void
add_axe_points(int value)
{
    set_axe_points(axe_points + value);
}

int
query_axe_points()
{
    return axe_points;
}

void
set_axe_drain(int value)
{
    axe_drain = value;
}

int
query_axe_drain()
{
    return axe_drain;
}

varargs void
set_axe_jewel(string jewel = 0, int rarity = 0)
{
    mapping config = GEM_CONFIG;
    int    *data;
    
    axe_jewel = jewel;

    if (!jewel)
       data = ({ 35, 35, 0, 0 });
    else if (!pointerp(data = config[rarity]))
       data = config[GEM_EXTREMELY_COMMON];
    
    set_hit(data[0]);
    set_pen(data[1]);
    set_max_points(data[2]);
    set_axe_points(query_max_points());
    set_axe_drain(data[3]);

    /* likely_break for default weapon is 10 so our would range from 0  */
    /* to 15 max, I think anything more would make it break too often   */
    
    set_likely_break( 15 * axe_points / 1500 );
    
    if (query_wielded())
       query_wielded()->update_weapon(this_object());
}

string
query_axe_jewel()
{
    return axe_jewel;
}


/*
 * === activating functions ==============================================
 * =============================================================== *** ===
 */

int
action_axe_command(string text)
{
    int heal;

    if (query_wielded() != this_player())
    {
       write("You must wield the axe first.\n");
       return 1;
    }

    
    if (!query_axe_jewel())
    {
        write("The power of " +LANG_THESHORT(this_object())+ 
        " cannot be summoned as no gem is in the handle.\n");
       return 0;
    }

    if (text != HEAL_TEXT)
    {
        write("You attempt to call up on dark powers but fail miserably.\n");
        say(QCTNAME(this_player()) + " calls upon the power of " +
        LANG_THESHORT(this_object()) + "but fails.\n");
        return 0;
    }

    heal = (query_axe_drain() * query_max_points() / 100);
    heal = min(heal, query_axe_points());
    
    write("You call upon the power of " + LANG_THESHORT(this_object())   +
        ".\n");
    say(QCTNAME(this_player()) + " calls upon the power of "             +
        LANG_THESHORT(this_object()) + ".\n");

    if (heal <= 0)
    {
       write("The axe glows briefly, then becomes cold to the " +
            "touch. Nothing happens.\n");
       return 0;
    }

    write("The power of " + LANG_THESHORT(this_object()) + " flows into" +
        " you!\n");
    write("You feel your health rising.\n");
    say(QCTNAME(this_player()) + " appears healthier!\n");
    
    this_player()->heal_hp(heal);

    add_axe_points(-heal);
    
    if (query_axe_points() <= 0)
       set_alarm(2.0, 0.0, destroy_axe_gem);

    return 1;
}

int
action_axe_fortify()
{
    if (query_wielded() != this_player())
    {
       write("The presence from within the axe urges you to wield it.\n");
       return 1;
    }

    write("You feel power flow from within the axe to fortify you"       +
        " against any obstacle.\n");
    say(QCTNAME(this_player()) + " grasps the "+short()+" closely"  +
        " and looks fortified against any obstacle.\n");
    
    this_player()->command("$smile confid");

    return 1;
}

int
action_axe_fortify_hook(object player)
{
    /* we use this to get it right with alarm inside the notify_wield */

    if (!objectp(player) || (query_wielded() != player) ||
        player->query_ghost() || !query_axe_jewel())
       return 0;

    set_this_player(player);
    
    return action_axe_fortify();
}

int
action_axe_insert(string text)
{
    mixed   item, temp;
    string  desc;
    
    if (!text || !parse_command(text, ({}), "%s 'in' / 'into' [the] %s",
        item, temp) || 
        !sizeof(item = FIND_STR_IN_OBJECT(item, this_player())) ||
        !sizeof(temp = FIND_STR_IN_OBJECT(temp, this_player())) ||
        (temp[0] != this_object()))
    {
       notify_fail("Insert what into what?\n");
       return 0;
    }

    item = item[0];

    if (!item->query_gem() && !item->id("gem"))
    {
       /* id("gem") is a support for gems that arent inherit the module */
       /* in /d/Genesis/gems/                                           */
       notify_fail("Insert what into what?\n");
       return 0;
    }

    /* by now we already know that player refered to this axe and some  */
    /* gem, so no more notify fails                                     */
    
    if (query_axe_jewel())
    {
       write(capitalize(LANG_THESHORT(this_object())) + " already has" +
           " a gem set.\n");
       return 1;
    }

    if (item->query_prop(HEAP_I_IS))
       desc = item->singular_short();
    else
       desc = item->short();

    write("You insert " + LANG_ADDART(desc) + " into the hilt of " +
        LANG_THESHORT(this_object()) + ".\n");
    say(QCTNAME(TP) + " inserts " + LANG_ADDART(desc) + " into the" +
        " hilt of " + this_player()->query_possessive() + " " + short() +
        ".\n");

    set_axe_jewel(desc, item->query_gem_rarity());
    log_file("gem_inserted",ctime(time())+ " " + CAP(TP->query_real_name())+ " (" + TP->query_average_stat()+ ") inserted " + LANG_ADDART(desc) + " into "+short()+".\n");

    if (item->query_prop(HEAP_I_IS))
    {
       item->restore_heap();
       item->set_heap_size(item->num_heap() - 1);
    }
    else
    {
       item->remove_object();
    }          

    return 1;
}

int
action_axe_impress()
{
    if (query_wielded() != this_player())
    {
       write("You must wield the axe first.\n");
       return 1;
    }

    write("You skillfully spin the axe from one hand to the other and"   +
        " then cut a massive swath through the air before you! Quite"    +
        " impressive!\n");
    say(QCTNAME(this_player()) + " skillfully spins the axe from one"    +
        " hand to the other then " + this_player()->query_pronoun()      +
        " cuts a massive swath through the air! Quite impressive!\n");

    this_player()->command("$cackle");

    return 1;
}

int
action_axe_lick()
{
    if (query_wielded() != this_player())
    {
       write("You must wield the axe first.\n");
       return 1;
    }

    write("You slowly lick some of the blood from "                      +
        LANG_THESHORT(this_object()) + ", an unstable glint flashing in" +
        " your eyes.\n");
    say(QCTNAME(this_player()) + " slowly licks some of the blood from " +
        LANG_THESHORT(this_object()) + ", an unstable glint in "         +
        this_player()->query_possessive() + " eyes.\n");

    this_player()->command("$grin dem");

    return 1;
}

int
action_axe_shave()
{
    if (query_wielded() != this_player())
    {
       write("You must wield the axe first.\n");
       return 1;
    }

    write("With surgeon-like precision, you carefully trim your"         +
        " whiskers.\n");
    say("With surgeon-like precision, " + QCTNAME(this_player())         +
        " carefully trims " + this_player()->query_possessive()          +
        " whiskers.\n");

    this_player()->command("$smile");

    return 1;
}

int
action_axe_wipe()
{
    if (query_wielded() != this_player())
    {
       write("You must wield the axe first.\n");
       return 1;
    }

    write("You wipe some of the dry, flaky blood of the axe onto the"    +
        " ground.\n");
    say(QCTNAME(this_player()) + " wipes some of the dry, flaky blood"   +
        " of the axe onto the ground.\n");

    this_player()->command("$grin devil");

    return 1;
}

void
notify_wield(object player)
{
    if (!objectp(player) || (query_wielded() != player) ||
        player->query_ghost() || !query_axe_jewel())
       return;

    set_this_player(player);
    
    write("The presence within the axe urges you to feed it some"        +
          " blood.\n");
    say(QCTNAME(this_player()) + " stares into space with a blank"       +
          " expression.\n");
// a carry over from the old BSA. Since this is the Elf Breaker, 
// it attacks now automatically attacks elves. Gotta hate that, 
// poor elves. ;)
/*

    TP->command("$shout Death to the First-born!");
    TP->command("$spit");
    write("The axe takes control of you, searching for an enemy " +
        "to kill.\n");
    TP->command("$kill elf");
//    command("kill elf");
    write("The struggle diminishes as you gain control of the axe.\n");
*/

    set_alarm(10.0, 0.0, &action_axe_fortify_hook(this_player()));
}

mixed
wield(object what)
{
    int     heal;
    
    /* we will stop newbies to try to wield it */
    if (this_player()->query_base_stat(SS_STR) < 35)
    {
       write("You try to lift the axe enough to wield it, but fail!\n");
       say(QCTNAME(this_player()) + " tries to lift the " + short() +
             " high enough to wield it, but fails!\n");

       return "The axe is too heavy!\n";
    }


    if (!query_axe_jewel() || (query_axe_points() <= 0))
       return 0;
    
//    if ((this_player()->query_race_name() != "elf")      &&
       if((this_player()->query_skill(SS_WEP_AXE) > 59)    &&
        (this_player()->query_skill(SS_SPELLCRAFT) > 19) &&
        (this_player()->resolve_task(TASK_DIFFICULT,({TS_STR,TS_DIS}))>0))
    {
        write("Straining your entire body and mind to the limit, you"    +
              " barely manage to gain control of the axe. A presence"    +
              " from within it seems to have accepted you as its new"    +
              " owner.\n");
        say(QCTNAME(this_player()) + " breaks out into a sweat as "      +
              this_player()->query_pronoun() + " attempts to gain"       +
              " control of the " + short() + ".\n");
    
        set_alarm(10.0, 0.0, &notify_wield(this_player()));
        return 0;
    }

    write("You strain with all your might but are simply not worthy"     +
          " enough. An unholy power curses you and takes a portion of"   +
          " your life from you!\n");
    say("A portion of " + QCTNAME(this_player()) + "'s life-force is"    +
          " drained by the axe!\n");

    heal = (query_axe_drain() * query_max_points() / 10);

    this_player()->heal_hp(-heal);
    add_axe_points(heal);

    if (this_player()->query_hp() <= 0)
       this_player()->do_die(this_object());

    return "A portion of your life-force was drained by the axe!\n";
}

/*
 * === initiating functions ==============================================
 * =============================================================== *** ===
 */

void
create_weapon()
{
    set_name("axe");
    set_pname("axes");
    set_adj(({"corrupted", "mithril"}));
    set_short("corrupted mithril axe");
    set_pshort("corrupted mithril axes");

    set_long("This is a corrupted mithril axe, once forged by " +
        "the elves of Lindon. It was used in countless battles " +
        "against the Dark One, but was stolen " +
        "during one of their battles. The Dark One took the axe " +
        "and twisted it to his own designs and now it is corrupted " +
        "and full of evil powers. In fairer days, the axe was " +
        "named 'Cleaver of Dark Foes', but is now named " +
        "Golughosh, 'The Elf Breaker'. Dark and evil runes cover " +
        "the once fair axe.@@query_jewel_desc@@\n");

    add_item(({"cryptic runes","runes","rune"}), "The runes decorate the"+
       " handle and the head of the axe, They are evil looking and seem"  +
       " to shine with a dark power.\n");
    add_item(({"axe head", "head of axe", "head of the axe"}),
        "The head of the axe is made of two mithril blades that " +
        "are half oval in shape and magically attached to the " +
        "blade. The edges of the blades are razor sharp and look " +
        "like they can easily cut through anything. Cryptic runes " +
        "decorate the head of the axe.\n");
    add_item(({"axe handle", "handle"}),
        "The axe handle is made of mithril, round and very smooth. " +
        "At the top of the handle is attached the head of the axe. " +
        "The base of the handle is wrapped in leather to give the " +
        "wielder a better grip on the handle.@@query_jewel_desc@@\n");
    add_item(({"leather on axe handle", "axe handle leather"}),
        "The leather is from some beast. It is brown and wrapped " +
        "around the base of the axe handle, to help the user get " +
        "a better grip on the handle.\n");
    add_item(({"mithril","true silver", "silver-steel", 
            "moria-silver","grey-gleam"}),
        "The mithril is the rarest metal in all the world. It is " +
        "lightweight yet durable, retaining its edge agaisnt the " +
        "hardest objects. It makes up the handle and blades, " +
        "making the axe very light yet deadly in the right hands.\n");

    set_hit(35);
    set_pen(35);

    set_wt(W_AXE);
    set_hands(W_LEFT);
    set_dt(W_SLASH|W_IMPALE);
    set_wf(this_object());

// starting gem
    set_axe_jewel("jade", GEM_SLIGHTLY_RARE);
    
    add_prop(OBJ_I_WEIGHT,  7500); /* lighter than because it's mithril */
    add_prop(OBJ_I_VOLUME, 20000);
    add_prop(OBJ_I_VALUE ,  1+random(10));
    add_prop(OBJ_M_NO_BUY,     1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);

    add_prop(MAGIC_AM_MAGIC, ({ 75, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,({"The axe is magically enchanted.\n", 5,
       "Dark runes cover the handle of the axe of Golughosh. " +
       "They pierce your mind, saying that it may be commanded " +
       "or be fortified by it. You may also impress others with " +
       "Golughosh or wipe its blade clean.", 25, "The enchanted " +
       "axe has greater hit and penetration than normal weapons " +
       "and has several unique  abilities. Failure to wield it " +
       "may result in bodily harm.\n",
       55}));

    add_prop(OBJ_S_WIZINFO, "The axe is enchanted by use of gems that"   +
       " players must insert into the handle. When no gems are inserted,"+
       " the axe loses its power and becomes an ordinary axe. To wield"  +
       " the axe, the wielder must have > 100 str, > 100 dis, 60 or"     +
       " better in the axe skill and 20 or better in the spellcraft"     +
       " skill. Since the axe is made of mithril, it is lighter than a"  +
       " standard steel axe, and therefore can be wielded by any race."  +
       " The axe may heal the wielder, but at a cost from the inserted"  +
       " gems. When a player attempts to wield the axe and fails, a"     +
       " portion of their life is taken from them.\n\tInserted gems are" +
       " what gives the axe its power, the rarer the gem group, the"     +
       " longer the power lasts. Also, as the axe is used to heal, this" +
       " takes a portion of the power from the axe. When the power is"   +
       " used up, the gem crumbles and the axe becomes 'normal' with no" +
       " powers. The wielder must insert a new gem to into the handle"   +
       " to recharge it. Inserted gems cannot be removed.\n");
}

void
init()
{
    ::init();
//    add_action(action_axe_command, "command");
    add_action(action_axe_fortify, "fortify");
    add_action(action_axe_impress, "impress");
    add_action(action_axe_insert ,  "insert");
//    add_action(action_axe_lick   , "axelick");
//    add_action(action_axe_shave  ,   "shave");
    add_action(action_axe_wipe   ,    "wipe");
//    add_action(action_gem_pry   ,    "pry");
}

