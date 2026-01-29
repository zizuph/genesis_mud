/* === cmawep.c ==========================================================
 * ======================================== Finwe & Raven 2001 Genesis ===
 *
 * Originally called the Bloody Steel Axe from Kalad, and coded by
 * Antharanos. Was given to the Shire when Kalad was slowly phased out.
 *
 * Altered so that it uses gems to get its strength and power. When gems
 * are spent, they crumble to dust and fall out of the handle. When that
 * happens, the wep becomes unenchanted, but can be re-enchanted with the
 * introduction of a gem to the handle. The rarest gems give it the most
 * power, but the majority of gems will give it limited powers.
 *
 * -- Finwe, August 2001
 *
 * Revisions:
 *  Enabled players to pry gems from the handle.
 *  -- Finwe, February 2002
 *  Moved gem functions into inheritable file gem_wep.c to be used by
 *  other weapons cloned by troll.
 *  -- Finwe , January 2004
 * Added syntax messages to weapon
 * -- Finwe, Jan 2008
 * =======================================================================
 * =============================================================== *** ===
 */

#include <cmdparse.h>
#include <tasks.h>
#include <wa_types.h>
#include "/d/Genesis/gems/gem.h"
#include "/d/Shire/sys/defs.h"

inherit "/std/weapon";

/*
 * === global variables ==================================================
 * =============================================================== *** ===
 */

#define WEP_RARITY_DESC \
        ({              \
          "waning",     \
          "mediocre",   \
          "strong",     \
          "very strong",\
        })

#define WEP_POINTS_DESC \
        ({              \
          "waning",     \
          "mediocre",   \
          "strong",     \
          "very strong",\
        })

#define GEM_CONFIG                                                       \
        ([                         /* hit pen    points       drain%*/   \
            GEM_EXTREMELY_RARE   : ({ 50, 50, 1500 + random(11), 10 }),  \
            GEM_VERY_RARE        : ({ 48, 48, 1000 + random(16), 12 }),  \
            GEM_RARE             : ({ 46, 46,  900 + random(11), 15 }),  \
            GEM_SOMEWHAT_RARE    : ({ 44, 44,  800 + random( 6), 17 }),  \
            GEM_SLIGHTLY_RARE    : ({ 42, 42,  500 + random( 6), 19 }),  \
            GEM_EXTREMELY_COMMON : ({ 40, 41,  200 + random( 6), 20 }),  \
        ])

#define NORMAL_HIT  35  // without gems in handle
#define NORMAL_PEN  35
#define HEAL_TEXT  "golughosh"

static string  wep_jewel;           /* the jewel short description      */
static int     wep_points,          /* the current points of wep        */
               max_points,          /* the max points for gem rarity    */
               wep_drain;           /* the drain of wep in percents     */

// following vars defined in individual weapon
public string wep_type;             /* what type of weapon              */
public string gem_place;            /* where gem is placed              */     
public int wt_type;                 /* wt_type value                    */
public int wep_skill;               /* weapon skill required to use     */

/*
 * === supporting functions ==============================================
 * =============================================================== *** ===
 */


string
query_wep_jewel()
{
    return wep_jewel;
}

string
query_jewel_desc()
{
    string  text = "", *desc;
    int     size, n;

    if (!this_object()->query_wep_jewel())
       return " The " + gem_place + " is empty, leaving the "+short()+" powerless. It looks like you can <insert [gem] into " + wep_type + ">.";
    
    /* this should be changed along with descs, just a skeleton so far   */
    /* compositing such a desc: A strong power emanates from the strong */
    /* glowing gem set in the hilt of the...                            */

    size = sizeof(desc = WEP_POINTS_DESC);
    
    n = (size * wep_points / max_points);
    n = (n < 0 ? 0 : (n > (size - 1) ? (size - 1) : n));

    text += (LANG_ADDART(desc[n]) + " evil power emanates from the ");

    size = sizeof(desc = WEP_RARITY_DESC);

// reveals how much power remains in the wep
//    n = (size * max_points / 1500);
    n = (size * max_points / wep_points);
    n = (n < 0 ? 0 : (n > (size - 1) ? (size - 1) : n));

    text += (desc[n] + " " + this_object()->query_wep_jewel() + " set in"+
            " the " + LANG_THESHORT(this_object())+
            ". It looks like it can be pried out");

    return (" " + capitalize(text) + ".");
}

void
destroy_wep_gem()
{
    string  gem;
    object  player = query_wielded();
    
    if (!(gem = this_object()->query_wep_jewel()))
       return;
    
    if (objectp(player) || living(player = environment(this_object())))
    {
       player->catch_tell("Suddenly the " + gem + " turns to dust " +
           "and falls out of the " + short() + "!\n");
       tell_room(environment(player), "Suddenly the " + gem + " on " +
           LANG_THESHORT(this_object()) + " held by " + QTNAME(player) +
           " turns into dust and falls out of the " + short() + "!\n", player);
    }
    else if (environment(this_object())->query_prop(ROOM_I_IS))
    {
       tell_room(environment(this_object()),"Suddenly the " + gem +
           " on " + LANG_THESHORT(this_object()) + " hilt turns into" +
           " dust and falls out of the " + short() + "!\n");
    }

    this_object()->set_wep_jewel(0, 0);
}


public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
                int phit, int dam)
{
    if (phit > 0) /* we actually hit something */
    {
       this_object()->add_wep_points(-1);

       if (this_object()->query_wep_points() <= 0)
          set_alarm(2.0, 0.0, destroy_wep_gem);
    }

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

int
action_wep_fortify()
{
    if (query_wielded() != this_player())
    {
       write("The presence from within the " + short() + " urges you to wield it.\n");
       return 1;
    }

    write("You feel power flow from within the " + short() + " to fortify you"       +
        " against any obstacle.\n");
    say(QCTNAME(this_player()) + " grasps the " + short() + " closely"  +
        " and looks fortified against any obstacle.\n");
    
    this_player()->command("$smile confid");

    return 1;
}

int
action_wep_fortify_hook(object player)
{
    /* we use this to get it right with alarm inside the notify_wield */

    if (!objectp(player) || (query_wielded() != player) ||
        player->query_ghost() || !query_wep_jewel())
       return 0;

    set_this_player(player);
    
    return action_wep_fortify();
}


void
notify_wield(object player)
{
    if (!objectp(player) || (query_wielded() != player) ||
        player->query_ghost() || !query_wep_jewel())
       return;

    set_this_player(player);
    
    write("The presence within the " + short() + " urges you to feed it some"        +
          " blood.\n");
    say(QCTNAME(this_player()) + " stares into space with a blank"       +
          " expression.\n");

    set_alarm(10.0, 0.0, &action_wep_fortify_hook(this_player()));
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
set_wep_points(int value)
{
    wep_points = (value<0 ? 0 : (value>max_points ? max_points : value));
}

void
add_wep_points(int value)
{
    set_wep_points(wep_points + value);
}

int
query_wep_points()
{
    return wep_points;
}

void
set_wep_drain(int value)
{
    wep_drain = value;
}

int
query_wep_drain()
{
    return wep_drain;
}

varargs void
set_wep_jewel(string jewel = 0, int rarity = 0)
{
    mapping config = GEM_CONFIG;
    int    *data;
    
    wep_jewel = jewel;

    if (!jewel)
       data = ({ 35, 35, 0, 0 });
    else if (!pointerp(data = config[rarity]))
       data = config[GEM_EXTREMELY_COMMON];
    
    set_hit(data[0]);
    set_pen(data[1]);
    set_max_points(data[2]);
    set_wep_points(query_max_points());
    set_wep_drain(data[3]);

    /* likely_break for default weapon is 10 so our would range from 0  */
    /* to 15 max, I think anything more would make it break too often   */
    
    set_likely_break( 15 * wep_points / 1500 );
    
    if (query_wielded())
       query_wielded()->update_weapon(this_object());
}


/*
 * === activating functions ==============================================
 * =============================================================== *** ===
 */

int
action_wep_command(string text)
{
    int heal;

    if (query_wielded() != this_player())
    {
       write("You must wield the " + short() + " first.\n");
       return 1;
    }

    
    if (!query_wep_jewel())
    {
        write("The power of " +LANG_THESHORT(this_object())+ 
        " cannot be summoned as no gem is in the " + short() + ".\n");
       return 0;
    }

    if (text != HEAL_TEXT)
    {
        write("You attempt to call up on powers of the " + short() + 
        " but fail miserably.\n");
        say(QCTNAME(this_player()) + " calls upon the power of " +
        LANG_THESHORT(this_object()) + "but fails.\n");
        return 0;
    }

    heal = (query_wep_drain() * query_max_points() / 100);
    heal = min(heal, query_wep_points());
    
    write("You call upon the power of " + LANG_THESHORT(this_object())   +
        ".\n");
    say(QCTNAME(this_player()) + " calls upon the power of "             +
        LANG_THESHORT(this_object()) + ".\n");

    if (heal <= 0)
    {
       write("The " + short() + " glows briefly, then becomes cold to the " +
            "touch. Nothing happens.\n");
       return 0;
    }

    write("The power of " + LANG_THESHORT(this_object()) + " flows into" +
        " you!\n");
    write("You feel your health rising.\n");
    say(QCTNAME(this_player()) + " appears healthier!\n");
    
    this_player()->heal_hp(heal);

    add_wep_points(-heal);
    
    if (query_wep_points() <= 0)
       set_alarm(2.0, 0.0, destroy_wep_gem);

    return 1;
}


int
action_wep_insert(string text)
{
    mixed   item, temp;
    string  desc;
    
    if (!text || !parse_command(text, ({}), "%s 'in' / 'into' [the] %s",
        item, temp) || 
        !sizeof(item = FIND_STR_IN_OBJECT(item, this_player())) ||
        !sizeof(temp = FIND_STR_IN_OBJECT(temp, this_player())) ||
        (temp[0] != this_object()))
    {
       notify_fail("Insert <gem> into " + wep_type + "?\n");
       return 0;
    }

    item = item[0];

    if (!item->query_gem() && !item->id("gem"))
    {
       /* id("gem") is a support for gems that arent inherit the module */
       /* in /d/Genesis/gems/                                           */
       notify_fail("Insert <gem> into " + wep_type + "?\n");
       return 0;
    }

    /* by now we already know that player refered to this wep and some  */
    /* gem, so no more notify fails                                     */
    
    if (query_wep_jewel())
    {
       write(capitalize(LANG_THESHORT(this_object())) + " already has" +
           " a gem set in it.\n");
       return 1;
    }

    if (item->query_prop(HEAP_I_IS))
       desc = item->singular_short();
    else
       desc = item->short();

    write("You insert " + LANG_ADDART(desc) + " into the " +
        LANG_THESHORT(this_object()) + ".\n");
    say(QCTNAME(TP) + " inserts " + LANG_ADDART(desc) + " into the " +
        this_player()->query_possessive() + " " + short() +
        ".\n");

    set_wep_jewel(desc, item->query_gem_rarity());
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
action_wep_impress()
{
    if (query_wielded() != this_player())
    {
       write("You must wield the " + short() + " first.\n");
       return 1;
    }

    write("You skillfully spin the " + short() + " from one hand to the other and"   +
        " then cut a massive swathe through the air before you! Quite"    +
        " impressive!\n");
    say(QCTNAME(this_player()) + " skillfully spins the " + short() + " from one"    +
        " hand to the other then " + this_player()->query_pronoun()      +
        " cuts a massive swath through the air! Quite impressive!\n");

    this_player()->command("$cackle");

    return 1;
}

int
action_wep_lick()
{
    if (query_wielded() != this_player())
    {
       write("You must wield the " + short() + " first.\n");
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
action_wep_shave()
{
    if (query_wielded() != this_player())
    {
       write("You must wield the " + short() + " first.\n");
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
action_wep_wipe()
{
    if (query_wielded() != this_player())
    {
       write("You must wield the " + short() + " first.\n");
       return 1;
    }

    write("You wipe some of the dry, flaky blood of the " + short() + 
        " onto the" + " ground.\n");
    say(QCTNAME(this_player()) + " wipes some of the dry, flaky blood"   +
        " of the " + short() + " onto the ground.\n");

    this_player()->command("grin devil");

    return 1;
}


mixed
wield(object what)
{
    int heal;

    if (sizeof(TP->query_weapon(-1)) == 2)
    {
        if (MASTER_OB(TP->query_weapon(-1)[0]) == "/d/Shire/common/trollsh/weapon/weapon" && MASTER_OB(TP->query_weapon(-1)[1]) == "/d/Shire/common/trollsh/weapon/weapon")

            return "You can only wield one of these at a time.\n";
    }   

    /* we will stop newbies to try to wield it */
    if (this_player()->query_base_stat(SS_STR) < 35)
    {
       write("You try to lift the " + short() + " enough to wield it, " + 
        "but fail!\n");
       say(QCTNAME(this_player()) + " tries to lift the " + short() +
             " high enough to wield it, but fails!\n");

       return "The " + short() + " is too heavy!\n";
    }


    if (!query_wep_jewel() || (query_wep_points() <= 0))
       return 0;
    
//    if ((this_player()->query_race_name() != "elf")      &&
       if((this_player()->query_skill(wep_skill) > 59)    &&
        (this_player()->query_skill(SS_SPELLCRAFT) > 19) &&
        (this_player()->resolve_task(TASK_DIFFICULT,({TS_STR,TS_DIS}))>0))
    {
        write("Straining your entire body and mind to the limit, you"    +
              " barely manage to gain control of the " + short() + ". A presence"    +
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
          " drained by the wep!\n");

    heal = (query_wep_drain() * query_max_points() / 10);

    this_player()->heal_hp(-heal);
    add_wep_points(heal);

    if (this_player()->query_hp() <= 0)
       this_player()->do_die(this_object());

    return "A portion of your life-force was drained by the " + short() + "!\n";
}

int
action_gem_pry(string str)
{
    string gem, desc;
    mixed   item, temp;


    if (!(gem = this_object()->query_wep_jewel()))
      return 1;

    if(str =="gem from " + wep_type || str =="jewel from " + wep_type)
    {
        if (query_wielded() == this_player())
        {
            write("You must unwield the "+short()+" first.\n");
            return 1;
        }
// let's rip the gem from the weapon...
        write("You pry at the gem.\n");
        destroy_wep_gem();
        this_player()->command("grin hap");
        log_file("gem_inserted",ctime(time())+ " " + 
            CAP(TP->query_real_name())+ " (" + TP->query_average_stat()+ 
            ") pried a " + gem + " from the "+short()+".\n");
        return 1;

    }
    else
    {
        write("Pry gem from " + wep_type + "?\n");
        return 1;
    }
    write("no gem.\n");
    return 0;
}

/*
 * === initiating functions ==============================================
 * =============================================================== *** ===
 */


create_weapon()
{
    wep_type = "sword";
    gem_place = "handle";
    wt_type  = W_AXE;
    wep_skill = SS_WEP_AXE;

    set_name(wep_type);
    set_pname(wep_type);
    add_name("_"+ wep_type);
    set_adj(({"corrupted", "mithril"}));
    set_short("corrupted mithril " + wep_type);
    set_pshort("corrupted mithril " + wep_type);

    set_long("This is a " + short() + " wicked, wicked sword, forged by the Smurfs.@@query_jewel_desc@@\n");


    set_hit(35);
    set_pen(35);

    set_wt(wt_type);
    set_hands(W_LEFT);
    set_dt(W_SLASH|W_IMPALE);
    set_wf(this_object());
    
    add_prop(OBJ_I_WEIGHT,  7500); /* lighter than because it's mithril */
    add_prop(OBJ_I_VOLUME, 20000);
    add_prop(OBJ_I_VALUE ,  1+random(10));
    add_prop(OBJ_M_NO_BUY,     1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);

}

void
init()
{
    ::init();

    add_action(action_wep_fortify, "fortify");
    add_action(action_wep_impress, "impress");
    add_action(action_wep_insert ,  "insert");
    add_action(action_wep_wipe   ,    "wipe");
    add_action(action_gem_pry   ,    "pry");
}
